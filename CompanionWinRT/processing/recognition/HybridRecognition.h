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
#include <companion\processing\recognition\HybridRecognition.h>

#include "CompanionWinRT\algo\recognition\matching\FeatureMatching.h"
#include "CompanionWinRT\processing\recognition\HashRecognition.h"
#include "CompanionWinRT\utils\CompanionUtils.h"

using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace CompanionWinRT
{
    /**
     * This class provides a WinRT wrapper for the 'HybridRecognition' functionality of the Companion framework.
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
    public ref class HybridRecognition sealed
    {
    public:

        /**
         * Create a 'HybridRecognition' wrapper.
         *
         * Note:
         * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
         * We can not mirror the plausible interface / abstract class 'Matching' for this wrapper.
         *
         * ToDo:
         * The user should be able to choose between different matching algorithms. This is a minimum construction.
         *
         * @param hashRecognition   hash recognition handle
         * @param matchingAlgo      matching algorithm to use, for example feature matching
         */
        HybridRecognition(HashRecognition^ hashRecognition, FeatureMatching^ matchingAlgo) : HybridRecognition(hashRecognition, matchingAlgo, 100)
        {};

        /**
         * Create a 'HybridRecognition' wrapper.
         *
         * Note:
         * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
         * We can not mirror the plausible interface / abstract class 'Matching' for this wrapper.
         *
         * ToDo:
         * The user should be able to choose between different matching algorithms. This is a minimum construction.
         *
         * @param hashRecognition   hash recognition handle
         * @param matchingAlgo      matching algorithm to use, for example feature matching
         * @param resize            resize image factor from 1 to 100 (in percent). 100 is equal to 100% of the original scale
         */
        HybridRecognition(HashRecognition^ hashRecognition, FeatureMatching^ matchingAlgo, int resize);

        /**
         * Add an image model to this hybrid recognition.
         *
         * @param imagePath path of the image that is going to be the image model
         * @param id        the ID of the image model
         */
        void addModel(Platform::String^ imagePath, int id);

        /**
         * Destruct this instance.
         */
        virtual ~HybridRecognition();

    private:

        /**
         * The native 'HybridRecognition' object of this instance.
         */
        Companion::Processing::Recognition::HybridRecognition* hybridRecognitionObj;

        /**
         * A handle to the hash recognition.
         */
        HashRecognition^ hashRecognition;

        /**
         * A handle to the desired matching algorithm.
         *
         * Note:
         * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
         * We can not mirror the plausible interface / abstract class 'Matching' for this wrapper.
         *
         * ToDo:
         * The user should be able to choose between different matching algorithms. This is a minimum construction.
         */
        FeatureMatching^ matchingAlgo;

        /**
         * List of all image models.
         */
        std::vector<cv::Mat> models;

    internal:

        /**
         * Internal method to provide the native 'HybridRecognition' object.
         *
         * @return pointer to the native 'HybridRecognition' object
         */
        Companion::Processing::Recognition::HybridRecognition* getHybridRecognition();
    };
}
