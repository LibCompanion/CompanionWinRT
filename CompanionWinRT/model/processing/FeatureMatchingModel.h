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

#include <opencv2\imgcodecs\imgcodecs.hpp>
#include <companion\model\processing\FeatureMatchingModel.h>

namespace CompanionWinRT
{
    /**
     * This class provides a WinRT wrapper for the 'FeatureMatchingModel' functionality of the Companion framework.
     *
     * @author Dimitri Kotlovsky, Andreas Sekulski
     */
    public ref class FeatureMatchingModel sealed
    {
        public:

            /**
             * Create a 'FeatureMatchingModel' wrapper with the provided image path.
             *
             * @param imagePath path of the image that is going to be a feature matching model
             * @param id        the ID of this model
             */
            FeatureMatchingModel(Platform::String^ imagePath, int id);

            /**
             * Destruct this instance.
             */
            virtual ~FeatureMatchingModel();

        private:

            /**
             * The native 'FeatureMatchingModel' object of this instance.
             */
            Companion::Model::Processing::FeatureMatchingModel* featureMatchingModelObj;

            /**
             * The native 'cv:Mat' object of this model.
             */
            cv::Mat imageModel;

        internal:

            /**
             * Internal method to provide the native 'FeatureMatchingModel' object.
             *
             * @return pointer to the native 'FeatureMatchingModel' object
             */
            Companion::Model::Processing::FeatureMatchingModel* getFeatureMatchingModel();
    };
}
