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

#include "FeatureMatching.h"

using namespace CompanionWinRT;

FeatureMatching::FeatureMatching(FeatureDetector detector, DescriptorMatcher matcherType, int thresh, int nfeatures,
                                 int countMatches, bool useIRA)
{
    // Create descriptor matcher
    int type = (int) matcherType;
    this->matcher = cv::DescriptorMatcher::create(type);

    // Create feature matching configuration with the desired algorithm and parameters
    switch (detector)
    {
        case FeatureDetector::BRISK :
            this->feature = cv::BRISK::create(thresh);
            this->featureMatchingObj = new Companion::Algorithm::FeatureMatching(this->feature, this->feature, this->matcher, type, countMatches, useIRA);
            break;
        case FeatureDetector::ORB :
            this->feature = cv::ORB::create(nfeatures);
            this->featureMatchingObj = new Companion::Algorithm::FeatureMatching(this->feature, this->feature, this->matcher, type);
            break;
        default:
            break;
            this->matcher.release();
            this->featureMatchingObj = nullptr;
    }
}

FeatureMatching::~FeatureMatching()
{
    this->matcher.release();
    if (this->feature)
    {
        this->feature.release();
    }
    delete this->featureMatchingObj;
    this->featureMatchingObj = nullptr;
}

Companion::Algorithm::Matching* FeatureMatching::getMatching()
{
    return this->featureMatchingObj;
}
