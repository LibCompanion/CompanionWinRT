/*
 * This program is a C#/UWP sample app for the Companion WinRT wrapper.
 *          https://github.com/LibCompanion/libCompanion
 *
 * Copyright (C) 2017 Dimitri Kotlovsky
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

using System;
using System.Collections.Generic;
using Windows.Foundation;
using Windows.Storage;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;
using Windows.Storage.FileProperties;
using System.Threading.Tasks;

namespace CompanionUWPSample
{
    using CW = CompanionWinRT;

    /**
     * This is the main page of the test application for the Companion library WinRT wrapper.
     */
    public sealed partial class MainPage : Page
    {
        /**
         * The path to the assets folder of this app (read only).
         */
        private String assetPath = Windows.ApplicationModel.Package.Current.InstalledLocation.Path + "\\Assets";

        /**
         * The path to the temp folder of this app to store temporary data.
         */
        private String tempPath = ApplicationData.Current.TemporaryFolder.Path;

        /**
         * The path to the image folder that is used as an input source for the Companion processing example.
         */
        private String imageFolderPath = Windows.ApplicationModel.Package.Current.InstalledLocation.Path + "\\Assets\\Muelheim_HBF";

        /**
         * Cached working item on working thread so it can be cancled by the user.
         */
        private IAsyncAction m_workItem;

        /**
         * Output destination for the obtained images from the companion library.
         */ 
        private WriteableBitmap m_bm;

        /**
         * Saves current run state of the companion processing.
         */
        private bool isRunning;

        /**
         * Constructs this main page.
         */
        public MainPage()
        {
            this.InitializeComponent();
            Reset();
            this.isRunning = false;
        }

        /**
         * Set an initial image file and create the WritableBitmap that is going to be the destination for the companion processing output.
         * 
         * ToDo: Examine why this is not working properly after the button click. This should not be done here with an image that is not
         * directly from the source.
         */
        async protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            try
            {
                // Get the size of the images for the WriteableBitmap constructor.
                StorageFolder folder = await StorageFolder.GetFolderFromPathAsync(this.imageFolderPath);
                IReadOnlyList<StorageFile> fileList = await folder.GetFilesAsync();
                StorageFile file = fileList[0];
                ImageProperties props = await file.Properties.GetImagePropertiesAsync();
                this.m_bm = new WriteableBitmap((int)props.Height, (int)props.Width);
                m_bm.SetSource(await file.OpenReadAsync());
                this.image.Source = m_bm;
            }
            catch (System.Exception ex)
            {
                UpdateUIOutput("Image source not found.");
            }
        }

        /**
         * Start a Companion creation and configuration on button click.
         */
        private async void startButton_Click(object sender, RoutedEventArgs e)
        {
            if (!this.isRunning)
            {
                this.isRunning = true;

                try
                {
                    // Create a configuration object of the Companion library
                    CW.Configuration configuration = await this.CreateConfiguration();

                    // Configure image recognition
                    CW.CPUFeatureMatching feature = await this.CreateCPUFeatureMatching(CW.CPUFeatureDetector.BRISK,
                        CW.DescriptorMatcher.BRUTEFORCE_HAMMING);

                    // Configure image processing
                    CW.ObjectDetection objectDetection = await this.CreateObjectDetection(feature);
                    await configuration.setProcessing(objectDetection);

                    // Set number of frames to skip (only video???)
                    await configuration.setSkipFrame(40);

                    // Create a WritableBitmap as the output destination for Companion
                    //this.CreateBitmap(new Uri(this.imageSourceURI, "Muelheim_HBF 001.jpg"));

                    // Set pixel buffer of this App's WritableBitmap (has to be done on the UI thread)
                    CW.Configuration.setPixelBuffer(this.m_bm.PixelBuffer);

                    // Subscribe to event so the bitmap can be redrawn after the bytes have been replaced
                    CW.Configuration.featuresFoundEvent += () =>
                    {
                        this.m_bm.Invalidate();
                    };

                    // Set input source (image folder because video source is not supported right now)
                    CW.ImageStream stream = await this.CreateImageStream(this.imageFolderPath);
                    await configuration.setSource(stream);

                    // Create feature matching models
                    CW.FeatureMatchingModel model1 = await this.CreateFeatureMatchingModel(this.assetPath + "\\Sample_Left.jpg");
                    CW.FeatureMatchingModel model2 = await this.CreateFeatureMatchingModel(this.assetPath + "\\Sample_Middle.jpg");
                    CW.FeatureMatchingModel model3 = await this.CreateFeatureMatchingModel(this.assetPath + "\\Sample_Right.jpg");

                    // Add feature matching models
                    await configuration.addModel(model1);
                    await configuration.addModel(model2);
                    await configuration.addModel(model3);

                    // Run Companion on a background thread
                    await configuration.run();

                    // A reference to the work item is cached so that we can trigger a cancellation when the user presses the Cancel button.
                    //this.m_workItem = Windows.System.Threading.ThreadPool.RunAsync((workItem) =>
                    //{
                    //    // Subscribe to event so the bitmap can be redrawn after the bytes have been replaced
                    //    CW.Configuration.GetDataEvent += () =>
                    //    {
                    //        //this.m_bm.Invalidate();
                    //    };

                    //    // Run Companion on a background thread
                    //    configuration.run();
                    //});

                    //this.m_workItem.Completed = new AsyncActionCompletedHandler((IAsyncAction asyncInfo, AsyncStatus asyncStatus) =>
                    //{
                    //    if (asyncStatus == AsyncStatus.Canceled)
                    //    {
                    //        return;
                    //    }

                    //    // Update the UI thread with the CoreDispatcher.
                    //    CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.High, new DispatchedHandler(() =>
                    //    {
                    //        UpdateUIOutput("WORKER THREAD GESCHLOSSEN!");
                    //    }));
                    //});

                }
                catch (Exception ex)
                {
                    this.handleException(ex);
                }

                this.isRunning = false;
            }
            else
            {
                this.UpdateUIOutput("Processing has already started.");
            }
        }

        /**
         * Cancel the companion processing.
         */
        private void cancelButton_Click(object sender, RoutedEventArgs e)
        {
            // ToDo
            this.UpdateUIOutput("Cancelation is currently not supported.");
        }

        /**
         * Creates a Companion/Configuration wrapper object.
         */
        private IAsyncOperation<CW.Configuration> CreateConfiguration()
        {
            return Task.Run(() =>
            {
                return new CW.Configuration();
            }).AsAsyncOperation<CW.Configuration>();
        }

        /**
         * Creates a CPUFeatureMatching wrapper object.
         */
        private IAsyncOperation<CW.CPUFeatureMatching> CreateCPUFeatureMatching(CW.CPUFeatureDetector detector, CW.DescriptorMatcher matcher)
        {
            return Task.Run(() =>
            {
                return new CW.CPUFeatureMatching(detector, matcher);
            }).AsAsyncOperation<CW.CPUFeatureMatching>();
        }

        /**
         * Creates an ObjectDetection wrapper object.
         */
        private IAsyncOperation<CW.ObjectDetection> CreateObjectDetection(CW.CPUFeatureMatching feature)
        {
            return Task.Run(() =>
            {
                return new CW.ObjectDetection(feature);
            }).AsAsyncOperation<CW.ObjectDetection>();
        }

        /**
         * Creates an ImageStream wrapper object.
         */
        private IAsyncOperation<CW.ImageStream> CreateImageStream(String folderPath)
        {
            return Task.Run(async () =>
            {
                // Retrieve images form the provided image folder
                StorageFolder folder = await StorageFolder.GetFolderFromPathAsync(folderPath);

                // Save the image paths to a list for the 'ImageStream' object
                List<String> imagePathList;
                if (folder != null)
                {
                    imagePathList = new List<String>();
                    IReadOnlyList<StorageFile> fileList = await folder.GetFilesAsync();
                    foreach (StorageFile file in fileList)
                    {
                        imagePathList.Add(file.Path);
                    }
                }
                else
                {
                    throw new Exception("The folder does not exist.");
                }

                return new CW.ImageStream(imagePathList);

            }).AsAsyncOperation<CW.ImageStream>();
        }

        /**
         * Creates and a 'FeatureMatchingModel' wrapper object from the provided image.
         */
        private IAsyncOperation<CW.FeatureMatchingModel> CreateFeatureMatchingModel(String imagePath)
        {
            return Task.Run(() =>
            {
                return new CW.FeatureMatchingModel(imagePath);

            }).AsAsyncOperation<CW.FeatureMatchingModel>();
        }

        /**
         * Handles Companion exceptions and prints corresponding error messages.
         */
        private void handleException(Exception ex)
        {
            String message = "";
            Type errorType = typeof(CW.ErrorCode);

            if (Enum.IsDefined(errorType, ex.HResult))
            {
                CW.ErrorCode errorCode = (CW.ErrorCode)Enum.ToObject(errorType, ex.HResult);
                message = CW.CompanionErrorUWP.getError(errorCode);
            }
            else
            {
                message = ex.Message;
            }

            this.UpdateUIOutput(message);
        }

        /**
         * Update UI output.
         */
        private void UpdateUIOutput(String s)
        {
            this.textBlock.Text += s + "\n";
        }

        /**
         * Reset UI output.
         */
        public void Reset()
        {
            this.UpdateUIOutput("Output:\n");
        }

        ///**
        // * Example with ThreadPool access
        // */
        //private void button3_Click(object sender, RoutedEventArgs e)
        //{
        //    // The nth prime number to find.
        //    const uint n = 100;

        //    // A shared pointer to the result.
        //    // We use a shared pointer to keep the result alive until the thread is done.
        //    ulong nthPrime = 0;

        //    // A reference to the work item is cached so that we can trigger a cancellation when the user presses the Cancel button.
        //    this.m_workItem = Windows.System.Threading.ThreadPool.RunAsync((workItem) =>
        //    {
        //        int i = 0;

        //        while (i < n)
        //        {
        //            if (workItem.Status == AsyncStatus.Canceled)
        //            {
        //                break;
        //            }

        //            String updateString = "Progress\n";

        //            // Update the UI thread with the CoreDispatcher.
        //            CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.High, new DispatchedHandler(() =>
        //            {
        //                UpdateUIOutput(updateString);
        //            }));

        //            i++;
        //        }

        //        // wenn fertig
        //        nthPrime = 2;
        //    });

        //    this.m_workItem.Completed = new AsyncActionCompletedHandler((IAsyncAction asyncInfo, AsyncStatus asyncStatus) =>
        //    {
        //        if (asyncStatus == AsyncStatus.Canceled)
        //        {
        //            return;
        //        }

        //        String updateString = "\n" + "The " + n + "th prime number is " + nthPrime + ".\n";

        //        // Update the UI thread with the CoreDispatcher.
        //        CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.High, new DispatchedHandler(() =>
        //        {
        //            UpdateUIOutput(updateString);
        //        }));
        //    });
        //}

        ///**
        // * CANCEL EXAMPLE
        // */
        //private void button4_Click(object sender, RoutedEventArgs e)
        //{
        //    // <SnippetCancellationHandler>
        //    if (m_workItem != null)
        //    {
        //        m_workItem.Cancel();
        //    }
        //    // </SnippetCancellationHandler>

        //    Reset();
        //}
    }
}
