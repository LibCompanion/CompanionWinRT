/*
 * This program is a Windows Runtime wrapper for the Companion CV library.
 *          https://github.com/LibCompanion/libCompanion
 *
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

#include <companion\Companion.h>
#include <companion\processing\2D\ObjectDetection.h>

#include "..\..\algo\CPUFeatureMatching.h"

namespace CompanionWinRT
{
    /**
     * This class provides a WinRT wrapper for the 'ObjectDetection' functionality of the Companion project.
     *
     * Note 1:
     * This is a minimum construction -- it has to be extended to provide the same flexability as the Companion native DLL.
     *
     * Note 2:
     * Public inheritance is not possible in a Windows Runtime context (with very few exceptions). We can not mirror the
     * plausible abstract class 'ImageProcessing' for this wrapper.
     *
     * @author Dimitri Kotlovsky
     */
    public ref class ObjectDetection sealed
    {
        public:

            /**
             * Creates an 'ObjectDetection' wrapper with the provided feature matching algorithm.
             *
             * Note:
             * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
             * plausible abstract class 'ImageProcessing' for this wrapper. To avoid circular dependencies (includes)
             * the companion/configuration reference has to be provided natively inside the 'Configuration' wrapper.
             *
             * ToDo:
             * User should be able to choose between different image recognition algorithms. This is a minimum construction.
             *
             * @param feature       Image recognition algorithm to use, for example feature matching.
             */
            ObjectDetection(CPUFeatureMatching^ feature) : ObjectDetection(feature, 0.5F)
            {};

            /**
             * Creates an 'ObjectDetection' wrapper with the provided feature matching algorithm.
             *
             * Note:
             * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
             * plausible abstract class 'ImageProcessing' for this wrapper. To avoid circular dependencies (includes)
             * the companion/configuration reference has to be provided natively inside the 'Configuration' wrapper.
             *
             * ToDo:
             * User should be able to choose between different image recognition algorithms. This is a minimum construction.
             *
             * @param feature       Image recognition algorithm to use, for example feature matching.
             * @param scale         scaling factor of frames
             */
            ObjectDetection(CPUFeatureMatching^ feature, float scale);

            /**
             * Destructs this instance.
             */
            virtual ~ObjectDetection();

        private:

            /**
             * The native 'ObjectDetection' object of this instance.
             */
            Companion::Processing::ObjectDetection* objectDetectionObj;

            /**
             * A handle to the desired image recognition algorithm.
             *
             * Note:
             * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
             * plausible abstract class 'ImageProcessing' for this wrapper.
             *
             * ToDo:
             * User should be able to choose between different image recognition algorithms. This is a minimum construction.
             */
            CPUFeatureMatching^ feature;

            /**
             * Scaling factor for frames.
             */
            float scale;

        internal:

            /**
             * Internal method to provide the native 'ImageProcessing' object (in this case a 'ObjectDetection' object).
             *
             * Note:
             * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
             * plausible abstract class 'ImageProcessing' for this wrapper. To avoid circular dependencies (includes)
             * the companion/configuration reference has to be provided natively inside the 'Configuration' wrapper.
             *
             * @return Pointer to the native 'ImageProcessing' object
             */
            Companion::Processing::ImageProcessing* getProcessing(Companion::Configuration* configuration);
    };
}
