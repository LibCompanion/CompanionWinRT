/*
 * CompanionUWPSample is a UWP example app for CompanionWinRT.
 * Copyright (C) 2017-2018 Dimitri Kotlovsky, Andreas Sekulski
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
using System.Linq;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Storage;
using Windows.UI.Xaml;
using Windows.Foundation;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Xaml.Media.Imaging;
using Windows.Storage.FileProperties;
using CW = CompanionWinRT;

namespace CompanionUWPSample {

    /**
     * Image processing methods.
     */
    public enum ImageProcessingMethod {
        FEATUE_MATCHING,
        IMAGE_HASHING,
        HYBRID_MATCHING,
        SHAPE_DETECTION
    }

    /**
     * This is the main page of the example application for CompanionWinRT.
     */
    public sealed partial class MainPage : Page {

        /**
         * A reference to the 'Assets' folder of this app (read only).
         */
        private StorageFolder assets;

        /**
         * A reference to the image samples folder that is used as an input source for the Companion processing example.
         */
        private StorageFolder imageFolder;

        /**
         * Output destination for the obtained images from Companion.
         */
        private WriteableBitmap m_bm;

        /**
         * Saves current run state of the Companion processing.
         */
        private bool isRunning;

        /**
         * Indicates whether it's save to start Companion.
         */
        private bool isReady;

        /**
         * Indicates whether the Companion processing is beeing canceled.
         */
        private bool isCanceling;

        /**
         * A 'Configuration' wrapper object to provide configuration data to Companion.
         */
        private CW.Configuration configuration;

        /**
         * List of radio buttons to choose the image processing method.
         */
        private List<RadioButton> radioButtons;

        /**
         * Construct this main page.
         */
        public MainPage() {
            this.InitializeComponent();
            this.isRunning = false;
            this.isReady = false;
            this.isCanceling = false;
        }

        /**
         * Set an initial image file and create the 'WritableBitmap' that is going to be the destination for the companion processing output.
         * 
         * ToDo: Examine why this is not working properly after the button click. This should not be done here with an image that is not
         * directly from the source.
         * 
         * @param e navigation event data
         */
        async protected override void OnNavigatedTo(NavigationEventArgs e) {
            // Initialize the 'Assets' folder
            try {
                this.assets = await Windows.ApplicationModel.Package.Current.InstalledLocation.GetFolderAsync("Assets");
            } catch (System.IO.FileNotFoundException ex) {
                this.UpdateUIOutput("No 'Assets' folder found.");
                return;
            }

            // Initialize the image source folder
            try {
                this.imageFolder = await this.assets.GetFolderAsync("images");
            } catch (System.IO.FileNotFoundException ex) {
                this.UpdateUIOutput("No image source folder found.");
                return;
            }

            // Get the size of the images for the WriteableBitmap constructor
            try {
                IReadOnlyList<StorageFile> fileList = await this.imageFolder.GetFilesAsync();
                StorageFile file = fileList[0];
                ImageProperties props = await file.Properties.GetImagePropertiesAsync();
                this.m_bm = new WriteableBitmap((int) props.Width, (int) props.Height);
                this.m_bm.SetSource(await file.OpenReadAsync());
                this.image.Source = this.m_bm;
                this.isReady = true;
            } catch (Exception ex) {
                this.UpdateUIOutput("Image sources not found.");
            }

            // Fill radio button list
            this.radioButtons = new List<RadioButton> { this.fmRButton, this.ihRButton, this.hmRButton, this.sdRButton };
        }

        /**
         * Start Companion creation and configuration on button click.
         * 
         * @param sender    sender of the event
         * @param e         routed event data
         */
        private async void StartButton_Click(object sender, RoutedEventArgs e) {
            if (!this.isRunning && this.isReady) {
                this.isRunning = true;
                this.Reset();
                this.startButton.IsEnabled = false;
                this.radioButtons.ForEach(r => r.IsEnabled = false);

                try {
                    // Create a Companion configuration object
                    object tag = this.radioButtons.FirstOrDefault(r => (bool) r.IsChecked).Tag;
                    await this.CreateConfiguration((ImageProcessingMethod) Int32.Parse(tag.ToString()));

                    // Constantly import images as the source for processing
                    Task task = Task.Run(async () => {
                        
                        // Save the source image paths to a list for the 'ImageStream' object
                        IReadOnlyList<StorageFile> fileList = await this.imageFolder.GetFilesAsync();

                        for (int i = 0; (i < fileList.Count) && !this.isCanceling; i++) {
                            // Use this control to adjust the streaming rate
                            //await Task.Delay(TimeSpan.FromSeconds(2));

                            this.configuration?.getSource()?.addImage(fileList[i].Path);
                        }
                    });

                    // Activate the cancle button
                    this.cancelButton.IsEnabled = true;

                    // Run Companion on a background thread
                    await this.RunCompanion();

                    // Wait until the image thread has stopped or finished
                    await task;

                    // Reset the application
                    this.startButton.IsEnabled = true;
                    this.radioButtons.ForEach(r => r.IsEnabled = true);
                    this.isRunning = false;
                    this.isCanceling = false;
                    this.configuration = null;
                    this.UpdateUIOutput("Processing has been stopped.");

                } catch (Exception ex) {
                    this.HandleException(ex);
                }
            } else if (this.isReady) {
                this.UpdateUIOutput("Processing has already started.");
            }
        }

        /**
         * Cancel the companion processing.
         * 
         * @param sender    sender of the event
         * @param e         routed event data
         */
        private async void CancelButton_Click(object sender, RoutedEventArgs e) {
            if (this.isRunning) {
                this.isCanceling = true;
                this.cancelButton.IsEnabled = false;
                try {
                    await this.StopCompanion();
                } catch (Exception ex) {
                    this.HandleException(ex);
                }
            }
        }

        /**
         * Create a 'Configuration' wrapper object.
         * 
         * @param algorithm 
         * @return returns a 'Configuration' wrapper object asynchronously
         */
        private IAsyncAction CreateConfiguration(ImageProcessingMethod processingMethod) {
            return Task.Run(() => {
                this.configuration = new CW.Configuration();

                // Create algorithms
                CW.FeatureMatching feature = new CW.FeatureMatching(CW.FeatureDetector.BRISK, CW.DescriptorMatcherType.BRUTEFORCE_HAMMING);
                CW.LSH lsh = new CW.LSH();
                CW.ShapeDetection polygonDetection = new CW.ShapeDetection();
                CW.ShapeDetection quadDetection = new CW.ShapeDetection(4, 4, "Quad");

                // Configure image processing
                CW.MatchRecognition matchRecognition = new CW.MatchRecognition(feature, CW.Scaling.SCALE_640x360);
                CW.HashRecognition hashRecognition = new CW.HashRecognition(polygonDetection, lsh);
                CW.HybridRecognition hybridRecognition = new CW.HybridRecognition(hashRecognition, feature, 50);
                CW.ObjectDetection objectDetection = new CW.ObjectDetection(quadDetection);

                // Set callback methods (result image should have an alpha channel (required for WritableBitmap))
                this.configuration.setResultCallback(this.ResultCallback, CW.ColorFormat.BGRA);
                this.configuration.setErrorCallback(this.ErrorCallback);

                // Set number of frames to skip
                this.configuration.setSkipFrame(0);

                // Set image buffer
                this.configuration.setImageBuffer(5);

                // Add source to configuaration
                CW.ImageStream stream = new CW.ImageStream(30);
                this.configuration.setSource(stream);

                // Create image models
                string model0 = this.assets.Path + "\\poster_left.jpg";
                string model1 = this.assets.Path + "\\poster_right.jpg";
                matchRecognition.addModel(new CW.FeatureMatchingModel(model0, 0));
                matchRecognition.addModel(new CW.FeatureMatchingModel(model1, 1));
                hashRecognition.addModel(model0, 0);
                hashRecognition.addModel(model1, 1);
                hybridRecognition.addModel(model0, 0);
                hybridRecognition.addModel(model1, 1);

                // Choose processing method
                switch (processingMethod) {
                    case ImageProcessingMethod.FEATUE_MATCHING:
                        this.configuration.setProcessing(matchRecognition);
                        break;
                    case ImageProcessingMethod.IMAGE_HASHING:
                        this.configuration.setProcessing(hashRecognition);
                        break;
                    case ImageProcessingMethod.HYBRID_MATCHING:
                        this.configuration.setProcessing(hybridRecognition);
                        break;
                    case ImageProcessingMethod.SHAPE_DETECTION:
                        this.configuration.setProcessing(objectDetection);
                        break;
                    default:
                        throw new Exception("Image processing method not found.");
                }

            }).AsAsyncAction();
        }

        /**
         * Result callback method for the companion processing.
         * 
         * @param results   list of results that represent the detected objects
         * @param image     the processed image with visually markers for the detected objects
         */
        public void ResultCallback(IList<CW.Result> results, byte[] image) {
            Windows.ApplicationModel.Core.CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.High, async () => {
                try {
                    using (System.IO.Stream stream = this.m_bm.PixelBuffer.AsStream()) {
                        if (stream.CanWrite) {
                            await stream.WriteAsync(image, 0, image.Length);
                            stream.Flush();
                        }
                    }
                    this.m_bm.Invalidate();
                    for (int i = 0; i < results.Count; i++) {
                        CW.Point upperLeftCorner = results[i].getFrame().getUpperLeftCorner();
                        this.UpdateUIOutput("Obj " + i + ": x_" + upperLeftCorner.x + ", y_" + upperLeftCorner.y);
                    }
                } catch (Exception ex) {
                    this.UpdateUIOutput(ex.Message);
                }

            }).AsTask();
        }

        /**
         * Error callback method for the companion processing.
         * 
         * @param errorMessage  a specific error message
         */
        public void ErrorCallback(String errorMessage) {
            Windows.ApplicationModel.Core.CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, () => {
                this.UpdateUIOutput(errorMessage);
            }).AsTask();
        }

        /**
         * Start the companion processing with the provided 'Configuration' wrapper object.
         * 
         * @param config    a 'Configuration' wrapper object
         * @return returns a awaitable asynchronous action
         */
        private IAsyncAction RunCompanion() {
            return Task.Run(() => {
                this.configuration.run();
            }).AsAsyncAction();
        }

        /**
         * Stop the companion processing.
         * 
         * @param config    a 'Configuration' wrapper object
         * @return returns a awaitable asynchronous action
         */
        private IAsyncAction StopCompanion() {
            return Task.Run(() => {
                this.configuration.stop();
            }).AsAsyncAction();
        }

        /**
         * Handle Companion exceptions and prints corresponding error messages.
         * 
         * @param ex    exception that was thrown
         */
        private void HandleException(Exception ex) {
            String message = "";
            Type errorType = typeof(CW.ErrorCode);

            if (Enum.IsDefined(errorType, ex.HResult)) {
                CW.ErrorCode errorCode = (CW.ErrorCode) Enum.ToObject(errorType, ex.HResult);
                message = CW.CompanionError.getError(errorCode);
            } else {
                message = ex.Message;
            }

            this.UpdateUIOutput(message);
        }

        /**
         * Update UI output.
         * 
         * @param s message that should be displayed for the user
         */
        private void UpdateUIOutput(String s) {
            this.textBlock.Text += s + "\n";
        }

        /**
         * Reset UI output.
         */
        public void Reset() {
            this.textBlock.Text = "";
        }
    }
}
