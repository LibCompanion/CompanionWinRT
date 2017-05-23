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

#include <companion\algo\cpu\CPUFeatureMatching.h>

namespace CompanionWinRT
{
    /**
     * Enumeration class for feature matching algorithms (CPU).
     */
    public enum class CPUFeatureDetector
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
     * This class provides a WinRT wrapper for the 'CPUFeatureMatching' functionality of the Companion project.
     *
     * Note 1:
     * This is a minimum construction -- it has to be extended to provide the same flexability as the Companion native DLL.
     *
     * Note 2:
     * Public inheritance is not possible in a Windows Runtime context (with very few exceptions). We can not mirror the
     * plausible abstract class 'ImageRecognition' for this wrapper.
     *
     * @author Dimitri Kotlovsky
     */
    public ref class CPUFeatureMatching sealed
    {
        public:

            /**
             * Creates a 'CPUFeatureMatching' wrapper with the provided feature matching algorithm.
             *
             * @param detector      desired feature detector
             * @param matcherType   type of the desired descriptor matcher
             */
            CPUFeatureMatching(CPUFeatureDetector detector, DescriptorMatcher matcherType)
                : CPUFeatureMatching(detector, matcherType, 60, 2000, 40, true)
            {};

            /**
             * Creates an 'CPUFeatureMatching' wrapper with the provided feature matching algorithm.
             *
             * @param detector      desired feature detector
             * @param matcherType   type of the desired descriptor matcher
             * @param thresh        (used by BRISK) AGAST detection threshold score
             * @param nfeatures     (used by ORB) The maximum number of features to retain
             * @param countMatches  how many matches should be found for a good matching result
             * @param useIRA        indicator to use IRA algorithm to use last detected objects from last scene
             */
            CPUFeatureMatching(CPUFeatureDetector detector, DescriptorMatcher matcherType, int thresh, int nfeatures,
                               int countMatches, bool useIRA);

            /**
             * Destructs this instance.
             */
            virtual ~CPUFeatureMatching();

        private:

            /**
             * The native 'FeatureMatching' object of this instance.
             */
            Companion::Algorithm::CPU::FeatureMatching* featureMatchingObj;
            
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
             * Internal method to provide the native 'ImageRecognition' object (in this case a 'CPUFeatureMatching' object).
             *
             * Note:
             * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
             * plausible abstract class 'ImageRecognition' for this wrapper.
             *
             * @return Pointer to the native 'ImageRecognition' object
             */
            Companion::Algorithm::ImageRecognition* getRecognition();
    };
}
