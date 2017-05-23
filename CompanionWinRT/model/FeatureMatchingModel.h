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

#include <opencv2\imgcodecs\imgcodecs.hpp>

#include <companion\model\FeatureMatchingModel.h>

namespace CompanionWinRT
{
    /**
     * This class provides a WinRT wrapper for the 'FeatureMatchingModel' functionality of the Companion project.
     *
     * Note:
     * Public inheritance is not possible in a Windows Runtime context (with very few exceptions). We can not mirror the
     * plausible abstract class 'ImageRecognitionModel' for this wrapper.
     *
     * @author Dimitri Kotlovsky
     */
    public ref class FeatureMatchingModel sealed
    {
    public:

        /**
         * Creates an 'FeatureMatchingModel' wrapper with the provided image path.
         *
         * @param imagePath path of the image that is going to be a feature matching model
         */
        FeatureMatchingModel(Platform::String^ imagePath);

        /**
         * Destructs this instance.
         */
        virtual ~FeatureMatchingModel();

    private:

        /**
         * The native 'FeatureMatchingModel' object of this instance.
         */
        Companion::Model::FeatureMatchingModel* featureMatchingModelObj;

        /**
         * The native 'cv:Mat' object of this model.
         */
        cv::Mat imageModel;

    internal:

        /**
         * Internal method to provide the native 'ImageRecognitionModel' object (in this case an 'FeatureMatchingModel' object).
         *
         * Note:
         * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
         * plausible abstract class 'ImageRecognitionModel' for this wrapper.
         *
         * @return Pointer to the native 'ImageRecognitionModel' object
         */
        Companion::Model::ImageRecognitionModel* getModel();
    };
}
