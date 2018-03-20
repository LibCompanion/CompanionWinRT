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

 /// @file
#pragma once

#include <companion\algo\recognition\matching\FeatureMatching.h>

namespace CompanionWinRT
{
    /**
     * Feature detector and descritor extractor types.
     */
    public enum class FeatureDetector
    {
        BRISK,
        ORB
    };

    /**
     * OpenCV descriptor matcher types.
     */
    public enum class DescriptorMatcherType
    {
        FLANNBASED = cv::DescriptorMatcher::FLANNBASED,
        BRUTEFORCE = cv::DescriptorMatcher::BRUTEFORCE,
        BRUTEFORCE_L1 = cv::DescriptorMatcher::BRUTEFORCE_L1,
        BRUTEFORCE_HAMMING = cv::DescriptorMatcher::BRUTEFORCE_HAMMING,
        BRUTEFORCE_HAMMINGLUT = cv::DescriptorMatcher::BRUTEFORCE_HAMMINGLUT,
        BRUTEFORCE_SL2 = cv::DescriptorMatcher::BRUTEFORCE_SL2
    };

    /**
     * OpenCV estimation algorithm types.
     */
    public enum class EstimationAlgorithm
    {
        LMEDS = cv::LMEDS,
        RANSAC = cv::RANSAC,
        RHO = cv::RHO
    };

    /**
     * This class provides a WinRT wrapper for the 'FeatureMatching' functionality of the Companion framework (CPU only).
     *
     * Note 1:
     * This is a minimum construction -- it has to be extended to provide the same flexability as the Companion native code.
     *
     * Note 2:
     * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
     * We can not mirror the plausible interface / abstract class 'Matching' for this wrapper.
     *
     * @author Dimitri Kotlovsky, Andreas Sekulski
     */
    public ref class FeatureMatching sealed
    {
        public:

            /**
             * Create a 'FeatureMatching' wrapper.
             *
             * ToDo:
             * The user should be able to choose between different detectors and extractors. This is a minimum construction.
             *
             * @param detector      desired feature detector and descritor extractor
             * @param matcherType   type of the desired descriptor matcher
             */
            FeatureMatching(FeatureDetector detector, DescriptorMatcherType matcherType)
                : FeatureMatching(detector, matcherType, 60, 2000, 10, 40, true, 3.0, 500, EstimationAlgorithm::RANSAC)
            {};

            /**
             * Create an 'FeatureMatching' wrapper.
             *
             * ToDo:
             * The user should be able to choose between different detectors and extractors. This is a minimum construction.
             *
             * @param detector              desired feature detector and descritor extractor
             * @param matcherType           type of the desired descriptor matcher
             * @param thresh                (used by BRISK) AGAST detection threshold score
             * @param nfeatures             (used by ORB) The maximum number of features to retain
             * @param minSideLength         minimum length of the detected area's sides (in pixels)
             * @param countMatches          how many matches should be found for a good matching result
             * @param useIRA                indicator to use IRA algorithm to use last detected objects from last scene
             * @param reprojThreshold       homography parameter: maximum allowed reprojection error to treat a point pair as an inlier
             * @param ransacMaxIters        homography parameter: maximum number of RANSAC iterations (2000 is the maximum)
             * @param findHomographyMethod  method used to compute a homography matrix
             */
            FeatureMatching(FeatureDetector detector, DescriptorMatcherType matcherType, int thresh, int nfeatures, int minSideLength,
                            int countMatches, bool useIRA, double reprojThreshold, int ransacMaxIters, EstimationAlgorithm findHomographyMethod);

            /**
             * Destruct this instance.
             */
            virtual ~FeatureMatching();

        private:

            /**
             * The native 'FeatureMatching' object of this instance.
             */
            Companion::Algorithm::Recognition::Matching::FeatureMatching* featureMatchingObj;

            /**
             * The feature detector and descriptor extractor of this feature matching configuration.
             *
             * ToDo:
             * The user should be able to choose between different detectors and extractors. This is a minimum construction.
             */
            cv::Ptr<cv::Feature2D> detector;

            /**
             * The descriptor matcher of this feature matching configuration.
             */
            cv::Ptr<cv::DescriptorMatcher> matcher;

        internal:

            /**
             * Internal method to provide the native 'FeatureMatching' object.
             *
             * @return pointer to the native 'FeatureMatching' object
             */
            Companion::Algorithm::Recognition::Matching::FeatureMatching* getFeatureMatching();
    };
}
