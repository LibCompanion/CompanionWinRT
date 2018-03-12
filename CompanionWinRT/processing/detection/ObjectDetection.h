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

#pragma once

#include <collection.h>
#include <companion\processing\detection\ObjectDetection.h>

#include "CompanionWinRT\algo\detection\ShapeDetection.h"
#include "CompanionWinRT\utils\CompanionUtils.h"

using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace CompanionWinRT
{
    /**
     * This class provides a WinRT wrapper for the 'ObjectDetection' functionality of the Companion framework.
     *
     * Note 1:
     * This is a minimum construction -- it has to be extended to provide the same flexability as the Companion native code.
     *
     * Note 2:
     * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
     * We can not mirror the plausible interface / abstract class 'ImageProcessing' for this wrapper.
     *
     * @author Dimitri Kotlovsky, Andreas Sekulski
     */
    public ref class ObjectDetection sealed
    {
    public:

        /**
         * Create an 'ObjectDetection' wrapper.
         *
         * Note:
         * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
         * We can not mirror the plausible interface / abstract class 'Detection' for this wrapper.
         *
         * ToDo:
         * The user should be able to choose between different detection algorithms. This is a minimum construction.
         *
         * @param detectionAlgo detection algorithm to use, for example shape detection
         */
        ObjectDetection(ShapeDetection^ detectionAlgo);

        /**
         * Destruct this instance.
         */
        virtual ~ObjectDetection();

    private:

        /**
         * The native 'ObjectDetection' object of this instance.
         */
        Companion::Processing::Detection::ObjectDetection* objectDetectionObj;

        /**
         * A handle to the desired detection algorithm.
         *
         * Note:
         * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
         * We can not mirror the plausible interface / abstract class 'Detection' for this wrapper.
         *
         * ToDo:
         * The user should be able to choose between different detection algorithms. This is a minimum construction.
         */
        ShapeDetection^ detectionAlgo;

    internal:

        /**
         * Internal method to provide the native 'ObjectDetection' object.
         *
         * @return pointer to the native 'ObjectDetection' object
         */
        Companion::Processing::Detection::ObjectDetection* getObjectDetection();
    };
}
