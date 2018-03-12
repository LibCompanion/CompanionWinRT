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

#include "FeatureMatchingModel.h"
#include "CompanionWinRT\utils\CompanionUtils.h"
#include "CompanionWinRT\utils\CompanionError.h"

using namespace CompanionWinRT;

FeatureMatchingModel::FeatureMatchingModel(Platform::String^ imagePath, int id)
{
    if (imagePath != nullptr)
    {
        this->featureMatchingModelObj = new Companion::Model::Processing::FeatureMatchingModel();
        this->imageModel = cv::imread(Utils::ps2ss(imagePath), cv::IMREAD_GRAYSCALE);
        this->featureMatchingModelObj->setImage(this->imageModel);
        this->featureMatchingModelObj->setID(id);
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

Companion::Model::Processing::FeatureMatchingModel* FeatureMatchingModel::getFeatureMatchingModel()
{
    return this->featureMatchingModelObj;
}
