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

#include "MatchRecognition.h"
#include "CompanionWinRT\utils\CompanionError.h"

using namespace CompanionWinRT;

MatchRecognition::MatchRecognition(FeatureMatching^ matchingAlgo, Scaling scaling)
{
    if (matchingAlgo != nullptr)
    {
        this->matchingAlgo = matchingAlgo;
        this->matchRecognitionObj = new Companion::Processing::Recognition::MatchRecognition(this->matchingAlgo->getFeatureMatching(), Utils::getScaling(scaling));
    }
    else
    {
        int hresult = static_cast<int>(ErrorCode::handle_is_null);
        throw ref new Platform::Exception(hresult);
    }
}

MatchRecognition::~MatchRecognition()
{
    delete this->matchRecognitionObj;
    this->matchRecognitionObj = nullptr;
}

void MatchRecognition::addModel(FeatureMatchingModel^ model)
{
    this->models->Append(model);
    if (!this->matchRecognitionObj->addModel(model->getFeatureMatchingModel()))
    {
        int hresult = static_cast<int>(ErrorCode::model_not_added);
        throw ref new Platform::Exception(hresult);
    }
}

IVector<FeatureMatchingModel^>^ MatchRecognition::getModels()
{
    return this->models;
}

void MatchRecognition::removeModel(int modelID)
{
    for (int i = 0; i < this->models->Size; i++)
    {
        if (this->models->GetAt(i)->getFeatureMatchingModel()->getID() == modelID)
        {
            this->matchRecognitionObj->removeModel(modelID);
            this->models->RemoveAt(i);
        }
    }
}

void MatchRecognition::clearModels()
{
    this->matchRecognitionObj->clearModels();
    this->models->Clear();
}

Companion::Processing::Recognition::MatchRecognition* MatchRecognition::getMatchRecognition()
{
    return this->matchRecognitionObj;
}
