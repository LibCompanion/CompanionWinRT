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

#include "FeatureMatchingModel.h"
#include "..\utils\CompanionError.h"

#include <opencv2\imgcodecs\imgcodecs.hpp>

using namespace CompanionWinRT;

FeatureMatchingModel::FeatureMatchingModel(Platform::String^ imagePath)
{
    if (imagePath != nullptr)
    {
        this->featureMatchingModelObj = new Companion::Model::FeatureMatchingModel();
        this->featureMatchingModelObj->setImage(cv::imread(ps2ss(imagePath), cv::IMREAD_GRAYSCALE)); // ToDO: should the user be able to change IMREAD value?
        
        /* ToDo for wrapper: construct 'FeatureMatchingModel' with a reference to 'CPUFeatureMatching' */
        // Only works on CPU -- ToDo Exception Handling if wrong type?
        //object->calculateKeyPointsAndDescriptors(feature, feature);
    }
    else
    {
        int hresult = static_cast<int>(ErrorCode::model_path_not_set);
        throw ref new Platform::Exception(hresult);
    }
}

FeatureMatchingModel::~FeatureMatchingModel()
{
    delete this->featureMatchingModelObj;
    this->featureMatchingModelObj = nullptr;
}

Companion::Model::ImageRecognitionModel* FeatureMatchingModel::getModel()
{
    return this->featureMatchingModelObj;
}
