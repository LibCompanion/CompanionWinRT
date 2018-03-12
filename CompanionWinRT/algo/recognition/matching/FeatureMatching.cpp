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

#include "FeatureMatching.h"

using namespace CompanionWinRT;

FeatureMatching::FeatureMatching(FeatureDetector detector, DescriptorMatcherType matcherType, int thresh, int nfeatures, int minSideLength, int countMatches,
                                 bool useIRA, double reprojThreshold, int ransacMaxIters, EstimationAlgorithm findHomographyMethod)
{
    // Create descriptor matcher
    int type = (int) matcherType;
    this->matcher = cv::DescriptorMatcher::create(type);

    // Create feature matching configuration with the desired algorithm and parameters
    switch (detector)
    {
        case FeatureDetector::BRISK :
            this->detector = cv::BRISK::create(thresh);
            this->featureMatchingObj = new Companion::Algorithm::Recognition::Matching::FeatureMatching(this->detector, this->detector, this->matcher, type, minSideLength, countMatches,
                                                                                                        useIRA, reprojThreshold, ransacMaxIters, (int) findHomographyMethod);
            break;
        case FeatureDetector::ORB :
            this->detector = cv::ORB::create(nfeatures);
            this->featureMatchingObj = new Companion::Algorithm::Recognition::Matching::FeatureMatching(this->detector, this->detector, this->matcher, type, minSideLength, countMatches,
                                                                                                        useIRA, reprojThreshold, ransacMaxIters, (int) findHomographyMethod);
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
    if (this->detector != nullptr)
    {
        this->detector.release();
    }
    delete this->featureMatchingObj;
    this->featureMatchingObj = nullptr;
}

Companion::Algorithm::Recognition::Matching::FeatureMatching* FeatureMatching::getFeatureMatching()
{
    return this->featureMatchingObj;
}
