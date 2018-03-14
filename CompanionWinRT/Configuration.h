/*
 * CompanionWinRT is a Windows Runtime wrapper for Companion.
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

#pragma once

#include <collection.h>
#include "processing\detection\ObjectDetection.h"
#include "processing\recognition\HashRecognition.h"
#include "processing\recognition\HybridRecognition.h"
#include "processing\recognition\MatchRecognition.h"
#include "input\ImageStream.h"
#include "model\result\Result.h"
#include "utils\CompanionUtils.h"

using namespace Platform::Collections;
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
     * This class provides WinRT compatible functionality wrapped around the Companion framework code.
     *
     * @author Dimitri Kotlovsky, Andreas Sekulski
     */
    public ref class Configuration sealed
    {
        public:

            /**
             * Set the image processing algorithm.
             *
             * @param processing    an image processing algorithm
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a WinRT context (with very few exceptions).
             * We can not mirror the plausible interface / abstract class 'ImageProcessing' for this wrapper.
             */
            void setProcessing(MatchRecognition^ processing);

            /**
             * Set the image processing algorithm.
             *
             * @param processing    an image processing algorithm
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a WinRT context (with very few exceptions).
             * We can not mirror the plausible interface / abstract class 'ImageProcessing' for this wrapper.
             */
            void setProcessing(HashRecognition^ processing);

            /**
             * Set the image processing algorithm.
             *
             * @param processing    an image processing algorithm
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a WinRT context (with very few exceptions).
             * We can not mirror the plausible interface / abstract class 'ImageProcessing' for this wrapper.
             */
            void setProcessing(HybridRecognition^ processing);

            /**
             * Set the image processing algorithm.
             *
             * @param processing    an image processing algorithm
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a WinRT context (with very few exceptions).
             * We can not mirror the plausible interface / abstract class 'ImageProcessing' for this wrapper.
             */
            void setProcessing(ObjectDetection^ processing);

            /**
             * Set a function as a result callback for processing.
             *
             * @param callback      a concrete function that works as a callback for the processing result
             * @param colorFormat   color format of the returned result image
             */
            void setResultCallback(ResultDelegate^ callback, ColorFormat colorFormat);

            /**
             * Set a function as an error callback for processing.
             *
             * @param callback  a concrete function that works as an error callback
             */
            void setErrorCallback(ErrorDelegate^ callback);

            /**
             * Set the number of frames to skip.
             *
             * @param skipFrame number of frames which should be skipped after one image processing cycle
             */
            void setSkipFrame(int skipFrame);

            /**
             * Set the maximum number of images to be loaded into a buffer.
             *
             * @param imageBuffer   maximum number of images to be loaed into a buffer
             */
            void setImageBuffer(int imageBuffer);

            /**
             * Return the skip frame rate.
             *
             * @return number of frames that are skipped after each processed frame
             */
            int getSkipFrame();

            /**
             * Set the source.
             *
             * @param stream    an image stream as the processing source
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a WinRT context (with very few exceptions).
             * We can not mirror the plausible interface / abstract class 'Stream' for this wrapper.
             */
            void setSource(ImageStream^ stream);

            /**
             * Return the image stream.
             *
             * @throws Platform::Exception if the source is not set
             * @return the image stream of this configurtion
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a WinRT context (with very few exceptions).
             * We can not mirror the plausible interface / abstract class 'Stream' for this wrapper.
             */
            ImageStream^ getSource();

            /**
             * Start the image processing.
             *
             * @throws Platform::Exception if the configuration is invalid
             */
            void run();

            /**
             * Stop the image processing.
             */
            void stop();

        private:

            /**
             * Handle to the result callback function.
             */
            ResultDelegate^ resultDelegate;

            /**
             * Handle to the error callback function.
             */
            ErrorDelegate^ errorDelegate;
           
            /**
             * The native 'Configuration' object of this instance.
             */
            Companion::Configuration configurationObj;

            /**
             * A handle to the 'MatchRecognition' wrapper object.
             */
            MatchRecognition^ matchRecognition;

            /**
             * A handle to the 'HashRecognition' wrapper object.
             */
            HashRecognition^ hashRecognition;

            /**
             * A handle to the 'HybridRecognition' wrapper object.
             */
            HybridRecognition^ hybridRecognition;

            /**
             * A handle to the 'ObjectDetection' wrapper object.
             */
            ObjectDetection^ objectDetection;

            /**
             * A handle to the 'ImageStream' wrapper object.
             */
            ImageStream^ stream;
    };
}
