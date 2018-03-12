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

#include "HybridRecognition.h"
#include "CompanionWinRT\utils\CompanionError.h"

using namespace CompanionWinRT;

HybridRecognition::HybridRecognition(HashRecognition^ hashRecognition, FeatureMatching^ matchingAlgo, int resize)
{
    if ((hashRecognition != nullptr) && (matchingAlgo != nullptr))
    {
        this->hashRecognition = hashRecognition;
        this->matchingAlgo = matchingAlgo;
        this->hybridRecognitionObj = new Companion::Processing::Recognition::HybridRecognition(this->hashRecognition->getHashRecognition(), this->matchingAlgo->getFeatureMatching(), resize);
    }
    else
    {
        int hresult = static_cast<int>(ErrorCode::handle_is_null);
        throw ref new Platform::Exception(hresult);
    }
}

HybridRecognition::~HybridRecognition()
{
    this->models.clear();
    delete this->hybridRecognitionObj;
    this->hybridRecognitionObj = nullptr;
}

void HybridRecognition::addModel(Platform::String^ imagePath, int id)
{
    if (imagePath != nullptr)
    {
        cv::Mat model = cv::imread(Utils::ps2ss(imagePath), cv::IMREAD_GRAYSCALE);
        this->models.push_back(model);
        this->hybridRecognitionObj->addModel(model, id);
    }
    else
    {
        int hresult = static_cast<int>(ErrorCode::model_path_not_set);
        throw ref new Platform::Exception(hresult);
    }
}

Companion::Processing::Recognition::HybridRecognition* HybridRecognition::getHybridRecognition()
{
    return this->hybridRecognitionObj;
}
