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
#include <companion\processing\recognition\MatchRecognition.h>

#include "CompanionWinRT\algo\recognition\matching\FeatureMatching.h"
#include "CompanionWinRT\model\processing\FeatureMatchingModel.h"
#include "CompanionWinRT\utils\CompanionUtils.h"

using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace CompanionWinRT
{
    /**
     * This class provides a WinRT wrapper for the 'MatchRecognition' functionality of the Companion framework.
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
    public ref class MatchRecognition sealed
    {
        public:

            /**
             * Create a 'MatchRecognition' wrapper with the provided matching algorithm.
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
             * We can not mirror the plausible interface / abstract class 'Matching' for this wrapper.
             *
             * ToDo:
             * The user should be able to choose between different matching algorithms. This is a minimum construction.
             *
             * @param matchingAlgo  matching algorithm to use, for example feature matching
             */
            MatchRecognition(FeatureMatching^ matchingAlgo) : MatchRecognition(matchingAlgo, Scaling::SCALE_1920x1080)
            {};

            /**
             * Create a 'FeatureDetection' wrapper with the provided matching algorithm.
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
             * We can not mirror the plausible interface / abstract class 'Matching' for this wrapper.
             *
             * ToDo:
             * The user should be able to choose between different matching algorithms. This is a minimum construction.
             *
             * @param matchingAlgo  matching algorithm to use, for example feature matching
             * @param scaling       scaling resolution for image processing
             */
            MatchRecognition(FeatureMatching^ matchingAlgo, Scaling scaling);

            /**
             * Add a feature matching model to this match recognition.
             *
             * @param model a feature matching model for this match recognition
             */
            void addModel(FeatureMatchingModel^ model);

            /**
             * Return a vector of all feature mathing models.
             *
             * @return all feature mathing models
             */
            IVector<FeatureMatchingModel^>^ getModels();

            /**
             * Remove the given model from match recognition. This function can only be used safetly while Companion is not processing.
             *
             * @param modelID   ID of the model
             */
            void removeModel(int modelID);

            /**
             * Clear all image processing models.
             */
            void clearModels();

            /**
             * Destruct this instance.
             */
            virtual ~MatchRecognition();

        private:

            /**
             * The native 'MatchRecognition' object of this instance.
             */
            Companion::Processing::Recognition::MatchRecognition* matchRecognitionObj;

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
             * A collection of all feature matching models.
             */
            Vector<FeatureMatchingModel^>^ models = ref new Vector<FeatureMatchingModel^>();

        internal:

            /**
             * Internal method to provide the native 'MatchRecognition' object.
             *
             * @return pointer to the native 'MatchRecognition' object
             */
            Companion::Processing::Recognition::MatchRecognition* getMatchRecognition();
    };
}
