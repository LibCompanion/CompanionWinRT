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
         * A reference to the 'Assets' folder of this app (read only).
         */
        private StorageFolder assets;

        /**
         * A reference to the image samples folder that is used as an input source for the Companion processing example.
         */
        private StorageFolder imageFolder;

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
         * States whether it's save to start companion.
         */
        private bool isReady;

        /**
         * A 'Configuration' wrapper object to provide configuration data to the companion cv library.
         */
        private CW.Configuration configuration;

        /**
         * Constructs this main page.
         */
        public MainPage()
        {
            this.InitializeComponent();
            Reset();
            this.isRunning = false;
            this.isReady = false;
        }

        /**
         * Set an initial image file and create the 'WritableBitmap' that is going to be the destination for the companion processing output.
         * 
         * ToDo: Examine why this is not working properly after the button click. This should not be done here with an image that is not
         * directly from the source.
         * 
         * @param e navigation event data
         */
        async protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            // Initialize the 'Assets' folder
            try
            {
                this.assets = await Windows.ApplicationModel.Package.Current.InstalledLocation.GetFolderAsync("Assets");
            }
            catch (System.IO.FileNotFoundException ex)
            {
                this.UpdateUIOutput("No 'Assets' folder found.");
                return;
            }

            // Initialize the image source folder
            try
            {
                this.imageFolder = await this.assets.GetFolderAsync("Muelheim_HBF");
            }
            catch (System.IO.FileNotFoundException ex)
            {
                this.UpdateUIOutput("No image source folder found.");
                return;
            }

            // Get the size of the images for the WriteableBitmap constructor.
            try
            {
                IReadOnlyList<StorageFile> fileList = await this.imageFolder.GetFilesAsync();
                StorageFile file = fileList[0];
                ImageProperties props = await file.Properties.GetImagePropertiesAsync();
                this.m_bm = new WriteableBitmap((int)props.Height, (int)props.Width);
                m_bm.SetSource(await file.OpenReadAsync());
                this.image.Source = m_bm;
                this.isReady = true;
            }
            catch (Exception ex)
            {
                this.UpdateUIOutput("Image sources not found.");
            }
        }

        /**
         * Start a Companion creation and configuration on button click.
         * 
         * @param sender    sender of the event
         * @param e         routed event data
         */
        private async void startButton_Click(object sender, RoutedEventArgs e)
        {
            if (!this.isRunning && isReady)
            {
                this.isRunning = true;

                try
                {
                    // Create a configuration object of the Companion library
                    await this.CreateConfiguration();

                    // Create a WritableBitmap as the output destination for Companion
                    //this.CreateBitmap(new Uri(this.imageSourceURI, "Muelheim_HBF 001.jpg"));

                    // Set pixel buffer of this App's WritableBitmap (has to be done on the UI thread)
                    CW.Configuration.setPixelBuffer(this.m_bm.PixelBuffer);

                    // Subscribe to event so the bitmap can be redrawn after the bytes have been replaced
                    CW.Configuration.featuresFoundEvent += () =>
                    {
                        this.m_bm.Invalidate();
                    };


                    // Run Companion on a background thread
                    await this.RunCompanion();

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
                    //        this.UpdateUIOutput("WORKER THREAD GESCHLOSSEN!");
                    //    }));
                    //});

                }
                catch (Exception ex)
                {
                    this.handleException(ex);
                }
            }
            else if (this.isReady)
            {
                this.UpdateUIOutput("Processing has already started.");
            }
        }

        /**
         * Cancel the companion processing.
         * 
         * @param sender    sender of the event
         * @param e         routed event data
         */
        private async void cancelButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.isRunning)
            {
                try
                {
                    await this.StopCompanion();
                    this.UpdateUIOutput("Processing has been stopped.");
                    this.isRunning = false;
                }
                catch (Exception ex)
                {
                    this.handleException(ex);
                }
            }
        }

        /**
         * Creates a 'Configuration' wrapper object.
         * 
         * @return Returns a 'Configuration' wrapper object asynchronously.
         */
        private IAsyncAction CreateConfiguration()
        {
            return Task.Run(async () =>
            {
                this.configuration = new CW.Configuration();

                // Configure image recognition
                CW.CPUFeatureMatching feature = new CW.CPUFeatureMatching(CW.CPUFeatureDetector.BRISK, CW.DescriptorMatcher.BRUTEFORCE_HAMMING);

                // Configure image processing
                CW.ObjectDetection objectDetection = new CW.ObjectDetection(feature);
                this.configuration.setProcessing(objectDetection);

                // Set number of frames to skip
                this.configuration.setSkipFrame(0);



                /**********************************************************************************
                 * Set input source (image folder because video source is not supported right now)
                 **********************************************************************************/

                // Save the source image paths to a list for the 'ImageStream' object
                List<String> imagePathList = new List<String>();
                IReadOnlyList<StorageFile> fileList = await this.imageFolder.GetFilesAsync();
                foreach (StorageFile file in fileList)
                {
                    imagePathList.Add(file.Path);
                }

                // Add source to configuaration
                CW.ImageStream stream = new CW.ImageStream(imagePathList);
                this.configuration.setSource(stream);



                /**********************************************************
                 * Create and add feature matching models to configuration
                 **********************************************************/

                // Create feature matching models
                CW.FeatureMatchingModel model1 = new CW.FeatureMatchingModel(this.assets.Path + "\\Sample_Left.jpg");
                CW.FeatureMatchingModel model2 = new CW.FeatureMatchingModel(this.assets.Path + "\\Sample_Middle.jpg");
                CW.FeatureMatchingModel model3 = new CW.FeatureMatchingModel(this.assets.Path + "\\Sample_Right.jpg");

                // Add feature matching models
                this.configuration.addModel(model1);
                this.configuration.addModel(model2);
                this.configuration.addModel(model3);

            }).AsAsyncAction();
        }

        /**
         * Starts the companion processing with the provided 'Configuration' wrapper object.
         * 
         * @param config    a 'Configuration' wrapper object
         * @return Returns a awaitable asynchronous action.
         */
        private IAsyncAction RunCompanion()
        {
            return Task.Run(() =>
            {
                this.configuration.run();
            }).AsAsyncAction();
        }

        /**
         * Stops the companion processing.
         * 
         * @param config    a 'Configuration' wrapper object
         * @return Returns a awaitable asynchronous action.
         */
        private IAsyncAction StopCompanion()
        {
            return Task.Run(() =>
            {
                this.configuration.stop();
            }).AsAsyncAction();
        }

        /**
         * Handles Companion exceptions and prints corresponding error messages.
         * 
         * @param ex    exception that was thrown
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
         * 
         * @param s message that should be displayed for the user
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
