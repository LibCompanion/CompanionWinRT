/*
 * CompanionWinRT is a Windows Runtime wrapper for libCompanion.
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

#include "processing\2D\ObjectDetection.h"
#include "input\ImageStream.h"
#include "model\processing\FeatureMatchingModel.h"
#include "model\result\Result.h"

using namespace Windows::Foundation::Collections;

namespace CompanionWinRT
{
    /**
     * A delegate that defines a result callback function for the client app.
     *
     * @param results   vector of 'Result' object references that represent the detected objects
     * @param image     byte array reference of the processed image 
     */
    public delegate void ResultDelegate(IVector<Result^>^ results, const Platform::Array<uint8>^ image);

    /**
     * A delegate that defines an error callback function for the client app.
     *
     * @param errorMessage  a message to describe the error
     */
    public delegate void ErrorDelegate(Platform::String^ errorMessage);

    /**
     * This class provides WinRT compatible functionality wrapped around the Companion project code.
     *
     * @author Dimitri Kotlovsky
     */
    public ref class Configuration sealed
    {
        public:

            /**
             * Sets the image processing configuration.
             *
             * @param detection an object detection configuration for this companion configuration
             *
             * Note:
             * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
             * plausible abstract class 'ImageProcessing' for this wrapper. This is a minimum construct and has to be
             * further developed to provide the same flexability as the Companion native DLL.
             */
            void setProcessing(ObjectDetection^ detection);

            /**
             * Sets a function as a result callback for the companion processing.
             *
             * @param callback  a concrete function that works as a callback for the processing result
             */
            void setResultCallback(ResultDelegate^ callback);

            /**
             * Sets a function as an error callback for the companion processing.
             *
             * @param callback  a concrete function that works as an error callback
             */
            void setErrorCallback(ErrorDelegate^ callback);

            /**
             * Sets the number of frames to skip.
             *
             * @param skipFrame number of frames which should be skipped after one image processing cycle
             */
            void setSkipFrame(int skipFrame);

            /**
             * Returns the skip frame rate.
             *
             * @return number of frames that are skipped after each processed frame
             */
            int getSkipFrame();

            /**
             * Sets the source.
             *
             * @param stream    an image stream as the processing source
             *
             * Note:
             * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
             * plausible abstract class 'Stream' for this wrapper. This is a minimum construct and has to be
             * further developed to provide the same flexability as the Companion native DLL.
             */
            void setSource(ImageStream^ stream);

            /**
             * Returns the image stream.
             *
             * @return the image stream of this configurtion
             *
             * Note:
             * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
             * plausible abstract class 'Stream' for this wrapper. This is a minimum construct and has to be
             * further developed to provide the same flexability as the Companion native DLL.
             */
            ImageStream^ getSource();

            /**
             * Adds a 'FeatureMatchingModel' object to this companion configuration.
             *
             * @param model a feature matching model for this companion configuration
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

        private:

            /**
             * Reference o a concrete result callback function.
             */
            ResultDelegate^ resultDelegate;

            /**
             * Rreference o a concrete error callback function.
             */
            ErrorDelegate^ errorDelegate;
           
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
        };
}
