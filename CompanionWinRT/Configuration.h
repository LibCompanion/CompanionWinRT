/*
 * This program is a Windows Runtime wrapper for the Companion CV library.
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

#pragma once

#include <collection.h>

#include "processing\2D\ObjectDetection.h"
#include "input\ImageStream.h"
#include "model\FeatureMatchingModel.h"

using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::Storage::Streams;

namespace CompanionWinRT
{
    /**
     * Delegate for the 'featuresFoundEvent' to update a listener that a new image is available.
     */
    public delegate void FeaturesFoundHandler();
    
    /* Test */
    private delegate void GetDataDelegate(std::vector<Companion::Draw::Drawable*> objects, cv::Mat frame);

    /**
     * This class provides WinRT compatible functionality wrapped around the Companion project code.
     *
     * @author Dimitri Kotlovsky
     */
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class Configuration sealed
    {
        public:

            /**
             * Creates an 'Configuration' wrapper.
             */
            Configuration();

            /**
             * Sets the image processing configuration.
             *
             * Note:
             * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
             * plausible abstract class 'ImageProcessing' for this wrapper. This is a minum construct and has to be
             * further developed to provide the same flexability as the Companion native DLL.
             */
            void setProcessing(ObjectDetection^ detection);

            /**
             * Sets the number of frames to skip.
             *
             * @param skipFrame number of frames which should be skipped after one image processing cycle
             */
            void setSkipFrame(int skipFrame);

            /**
             * Sets the source.
             *
             * Note:
             * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
             * plausible abstract class 'Stream' for this wrapper. This is a minum construct and has to be
             * further developed to provide the same flexability as the Companion native DLL.
             */
            void setSource(ImageStream^ stream);

            /**
             * Adds a 'FeatureMatchingModel' object to this companion configuration.
             *
             * @param model feature matching model that is going to be added to this companion configuration
             */
            void addModel(FeatureMatchingModel^ model);

            /**
             * Starts processing of the Companion library.
             */
            void run();

            /**
             * Stops processing of the Companion library.
             */
            void stop();

            /**
             * Static event to update a listener that a new image is available.
             */
            static event FeaturesFoundHandler^ featuresFoundEvent;

            /*********************************************************************************************************
             * Retrieves the raw pixel data from the provided IBuffer object of a WritableBitmap (UI thread required).
             * The mutable bytes are used to update image information as the output of the companion processing.
             *
             * @param pixelBuffer   Buffer of a WritableBitmap that includes the mutable bytes for companion output
             *********************************************************************************************************/
            static void setPixelBuffer(IBuffer^ pixelBuffer);

            //static Platform::String^ loadVideo(Platform::String^ videoPath);

            /**
             * Returns the skip frame rate.
             * @return number of frames that are skipped after each processed frame
             */
            int getSkipFrame();

        private:
        
            /**
             * The native 'Configuration' object of this instance.
             */
            Companion::Configuration configurationObj;

            /**
             * A handle to the 'ObjectDetection' wrapper object.
             */
            ObjectDetection^ detection;

            /**
             * A handle to the 'ImageStream' wrapper object.
             */
            ImageStream^ stream;

            /**
             * A collection of all feature matching models.
             */
            std::vector<FeatureMatchingModel^> models;

            /*********************************************************************************************************
             * Raw pixel data (bytes) of the WritableBitmap that represents the companion output ont the UI thread.
             *********************************************************************************************************/
            static uint8* pixels;

            /*********************************************************************************************************
             * Static dispatcher that is responsible to dispathc the triggered 'featuresFoundEvent' to get delivered
             * to the right thread (in this current context that is the UI thread).
             *********************************************************************************************************/
            static CoreDispatcher^ dispatcher;

            /**
             * Static callback function to obtain errors from companion processing.
             *
             * @param code  error code that represents the error
             */
            static void error(Companion::Error::Code code);

            /**
             * Static callback function to obtain results from companion processing.
             *
             * @param objects   drawable objects to represent the processing results in the image
             * @param frame     actual image
             */
            static void callback(std::vector<Companion::Draw::Drawable*> objects, cv::Mat frame);

            /* Test */
            static void GetDataImpl(std::vector<Companion::Draw::Drawable*> objects, cv::Mat frame);
            void GetDataImpl2(std::vector<Companion::Draw::Drawable*> objects, cv::Mat frame);
            static event GetDataDelegate^ getDataEvent;
        };
}
