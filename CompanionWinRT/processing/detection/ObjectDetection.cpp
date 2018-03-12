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

#include "ObjectDetection.h"
#include "CompanionWinRT\utils\CompanionError.h"

using namespace CompanionWinRT;

ObjectDetection::ObjectDetection(ShapeDetection^ detectionAlgo)
{
    if (detectionAlgo != nullptr)
    {
        this->detectionAlgo = detectionAlgo;
        this->objectDetectionObj = new Companion::Processing::Detection::ObjectDetection(this->detectionAlgo->getShapeDetection());
    }
    else
    {
        int hresult = static_cast<int>(ErrorCode::handle_is_null);
        throw ref new Platform::Exception(hresult);
    }
}

ObjectDetection::~ObjectDetection()
{
    delete this->objectDetectionObj;
    this->objectDetectionObj = nullptr;
}

Companion::Processing::Detection::ObjectDetection* ObjectDetection::getObjectDetection()
{
    return this->objectDetectionObj;
}
