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
#include <companion\processing\recognition\HashRecognition.h>

#include "CompanionWinRT\algo\detection\ShapeDetection.h"
#include "CompanionWinRT\algo\recognition\hashing\LSH.h"
#include "CompanionWinRT\utils\CompanionUtils.h"

using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace CompanionWinRT
{
    /**
     * This class provides a WinRT wrapper for the 'HashRecognition' functionality of the Companion framework.
     *
     * Note 1:
     * This is a minimum construction -- it has to be extended to provide the same flexability as the Companion native code.
     *
     * Note 2:
     * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
     * We can not mirror the plausible interface / abstract class 'ImageProcessing' for this wrapper.
     *
     * @author Dimitri Kotlovsky, Andreas Sekulski
     */
    public ref class HashRecognition sealed
    {
    public:

        /**
         * Create a 'HashRecognition' wrapper.
         *
         * Note:
         * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
         * We can not mirror the plausible interface / abstract class 'Hashing' for this wrapper.
         *
         * ToDo:
         * The user should be able to choose between different hashing algorithms. This is a minimum construction.
         *
         * @param shapeDetection    shape detection handle
         * @param hashingAlgo       hashing algorithm to use, for example LSH
         */
        HashRecognition(ShapeDetection^ shapeDetection, LSH^ hashingAlgo) : HashRecognition(shapeDetection, hashingAlgo, Size { 50, 70 })
        {};

        /**
         * Create a 'HashRecognition' wrapper.
         *
         * Note:
         * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
         * We can not mirror the plausible interface / abstract class 'Hashing' for this wrapper.
         *
         * ToDo:
         * The user should be able to choose between different hashing algorithms. This is a minimum construction.
         *
         * @param shapeDetection    shape detection handle
         * @param hashingAlgo       hashing algorithm to use, for example LSH
         * @param modelSize         size of the image hash model in pixels during the processing
         */
        HashRecognition(ShapeDetection^ shapeDetection, LSH^ hashingAlgo, Size modelSize);

        /**
         * Add an image hash model to this hash recognition.
         *
         * @param imagePath path of the image that is going to be the image hash model
         * @param id        the ID of the image hash model
         */
        void addModel(Platform::String^ imagePath, int id);

        /**
         * Destruct this instance.
         */
        virtual ~HashRecognition();

    private:

        /**
         * The native 'HashRecognition' object of this instance.
         */
        Companion::Processing::Recognition::HashRecognition* hashRecognitionObj;

        /**
         * A handle to the shape detection algorithm.
         */
        ShapeDetection^ shapeDetection;

        /**
         * A handle to the desired hashing algorithm.
         *
         * Note:
         * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
         * We can not mirror the plausible interface / abstract class 'Hashing' for this wrapper.
         *
         * ToDo:
         * The user should be able to choose between different hashing algorithms. This is a minimum construction.
         */
        LSH^ hashingAlgo;

        /**
         * List of all image hash models.
         */
        std::vector<cv::Mat> models;

    internal:

        /**
         * Internal method to provide the native 'HashRecognition' object.
         *
         * @return pointer to the native 'HashRecognition' object
         */
        Companion::Processing::Recognition::HashRecognition* getHashRecognition();
    };
}
