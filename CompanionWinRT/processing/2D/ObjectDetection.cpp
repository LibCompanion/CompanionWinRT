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

#include "ObjectDetection.h"
#include "companionWinRT\utils\CompanionError.h"

using namespace CompanionWinRT;

ObjectDetection::ObjectDetection(FeatureMatching^ matchingAlgo, Scaling scaling)
{
    if (matchingAlgo != nullptr)
    {
        this->matchingAlgo = matchingAlgo;
        this->scaling = scaling;
    }
    else
    {
        int hresult = static_cast<int>(ErrorCode::recognition_not_found);
        throw ref new Platform::Exception(hresult);
    }
}

ObjectDetection::~ObjectDetection()
{
    delete this->objectDetectionObj;
    this->objectDetectionObj = nullptr;
}

Companion::Processing::ImageProcessing* ObjectDetection::getProcessing(Companion::Configuration* configuration)
{
    if ((configuration == nullptr) || (this->matchingAlgo == nullptr))
    {
        int hresult = static_cast<int>(ErrorCode::config_or_recognition_not_found);
        throw ref new Platform::Exception(hresult);
    }

    this->objectDetectionObj = new Companion::Processing::ObjectDetection(configuration, this->matchingAlgo->getMatching(), getScaling(this->scaling));

    return this->objectDetectionObj;
}
