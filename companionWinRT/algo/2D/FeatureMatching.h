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

#pragma once

#include <companion\algo\2D\FeatureMatching.h>

namespace CompanionWinRT
{
    /**
     * Enumeration class for feature matching algorithms.
     */
    public enum class FeatureDetector
    {
        BRISK,
        ORB
    };

    /**
     * OpenCV DescriptorMatcher types.
     */
    public enum class DescriptorMatcher
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
     * This class provides a WinRT wrapper for the 'FeatureMatching' functionality of the Companion project (CPU only).
     *
     * Note 1:
     * This is a minimum construction -- it has to be extended to provide the same flexability as the Companion native code.
     *
     * Note 2:
     * Public inheritance is not possible in a Windows Runtime context (with very few exceptions). We can not mirror the
     * plausible abstract class 'ImageRecognition' for this wrapper.
     *
     * @author Dimitri Kotlovsky
     */
    public ref class FeatureMatching sealed
    {
        public:

            /**
             * Creates a 'FeatureMatching' wrapper with the provided feature matching algorithm.
             *
             * @param detector      desired feature detector
             * @param matcherType   type of the desired descriptor matcher
             */
            FeatureMatching(FeatureDetector detector, DescriptorMatcher matcherType)
                : FeatureMatching(detector, matcherType, 60, 2000, 10, 40, true, 3.0, 500, EstimationAlgorithm::RANSAC)
            {};

            /**
             * Creates an 'FeatureMatching' wrapper with the provided feature matching algorithm.
             *
             * @param detector              desired feature detector
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
            FeatureMatching(FeatureDetector detector, DescriptorMatcher matcherType, int thresh, int nfeatures, int minSideLength,
                            int countMatches, bool useIRA, double reprojThreshold, int ransacMaxIters, EstimationAlgorithm findHomographyMethod);

            /**
             * Destructs this instance.
             */
            virtual ~FeatureMatching();

        private:

            /**
             * The native 'FeatureMatching' object of this instance.
             */
            Companion::Algorithm::FeatureMatching* featureMatchingObj;
            
            /**
             * The descriptor matcher of this feature matching configuration.
             */
            cv::Ptr<cv::DescriptorMatcher> matcher;
            
            /**
             * The feature detector and descriptor extractor of this feature matching configuration.
             *
             * ToDo:
             * The User should be able to choose between different detectors and extractors. This is a minimum construction.
             */
            cv::Ptr<cv::Feature2D> feature;

        internal:

            /**
             * Internal method to provide the native 'ImageRecognition' object (in this case a 'FeatureMatching' object).
             *
             * Note:
             * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
             * plausible abstract class 'ImageRecognition' for this wrapper.
             *
             * @return Pointer to the native 'ImageRecognition' object
             */
            Companion::Algorithm::Matching* getMatching();
    };
}
