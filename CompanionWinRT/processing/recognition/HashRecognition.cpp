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

#include "HashRecognition.h"
#include "CompanionWinRT\utils\CompanionError.h"

using namespace CompanionWinRT;

HashRecognition::HashRecognition(ShapeDetection^ shapeDetection, LSH^ hashingAlgo, Size modelSize)
{
    if ((shapeDetection != nullptr) && (hashingAlgo != nullptr))
    {
        this->shapeDetection = shapeDetection;
        this->hashingAlgo = hashingAlgo;
        this->hashRecognitionObj = new Companion::Processing::Recognition::HashRecognition(cv::Size(modelSize.width, modelSize.height), this->shapeDetection->getShapeDetection(), this->hashingAlgo->getLSH());
    }
    else
    {
        int hresult = static_cast<int>(ErrorCode::handle_is_null);
        throw ref new Platform::Exception(hresult);
    }
}

HashRecognition::~HashRecognition()
{
    this->models.clear();
    delete this->hashRecognitionObj;
    this->hashRecognitionObj = nullptr;
}

void HashRecognition::addModel(Platform::String^ imagePath, int id)
{
    if (imagePath != nullptr)
    {
        cv::Mat model = cv::imread(Utils::ps2ss(imagePath), cv::IMREAD_GRAYSCALE);
        this->models.push_back(model);
        this->hashRecognitionObj->addModel(id, model);
    }
    else
    {
        int hresult = static_cast<int>(ErrorCode::model_path_not_set);
        throw ref new Platform::Exception(hresult);
    }
}

Companion::Processing::Recognition::HashRecognition* HashRecognition::getHashRecognition()
{
    return this->hashRecognitionObj;
}
