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

#include <companion\algo\detection\ShapeDetection.h>

#include "CompanionWinRT\utils\CompanionUtils.h"

namespace CompanionWinRT
{
    /**
     * OpenCV morph shapes.
     */
    public enum class MorphShape
    {
        RECT = cv::MORPH_RECT,
        CROSS = cv::MORPH_CROSS,
        ELLIPSE = cv::MORPH_ELLIPSE
    };

    /**
     * This struct represents an OpenCV like structering element.
     */
    public value struct StructuringElement
    {
        /**
         * Shape of this structering element.
         */
        MorphShape shape;
            
        /**
         * Size of this structering element.
         */
        Size size;
    };

    /**
     * This class provides a WinRT wrapper for the 'ShapeDetection' functionality of the Companion framework (CPU only).
     *
     * Note 1:
     * This is a minimum construction -- it has to be extended to provide the same flexability as the Companion native code.
     *
     * Note 2:
     * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
     * We can not mirror the plausible interface / abstract class 'Detection' for this wrapper.
     *
     * @author Dimitri Kotlovsky, Andreas Sekulski
     */
    public ref class ShapeDetection sealed
    {
        public:

            /**
             * Create a 'ShapeDetection' wrapper.
             */
            ShapeDetection() : ShapeDetection(4, 20, "Polygon", 50.0, 3,
                StructuringElement{ MorphShape::RECT, Size{ 30, 30 } },
                StructuringElement{ MorphShape::RECT, Size{ 10, 10 } },
                StructuringElement{ MorphShape::RECT, Size{ 40, 40 } })
            {};

            /**
             * Create a 'ShapeDetection' wrapper.
             *
             * @param minCorners        minimum number of corners
             * @param maxCorners        maximum number of corners
             * @param shapeDescription  shape description
             */
            ShapeDetection(int minCorners, int maxCorners, Platform::String^ shapeDescription) : ShapeDetection(
                minCorners, maxCorners, shapeDescription, 50.0, 3,
                StructuringElement{ MorphShape::RECT, Size{ 30, 30 } },
                StructuringElement{ MorphShape::RECT, Size{ 10, 10 } },
                StructuringElement{ MorphShape::RECT, Size{ 40, 40 } })
            {};

            /**
             * Create a 'ShapeDetection' wrapper.
             *
             * @param minCorners        minimum number of corners
             * @param maxCorners        maximum number of corners
             * @param shapeDescription  shape description
             * @param cannyThreshold    canny threshold
             * @param dilateIteration   number of dilate iterations
             * @param morphKernel       morphology kernel size
             * @param erodeKernel       erode kernel size
             * @param dilateKernel      dilate kernel size
             */
            ShapeDetection(int minCorners, int maxCorners, Platform::String^ shapeDescription, double cannyThreshold, int dilateIteration, StructuringElement morphKernel,
                StructuringElement erodeKernel, StructuringElement dilateKernel);

            /**
             * Destruct this instance.
             */
            virtual ~ShapeDetection();

        private:

            /**
             * The native 'ShapeDetection' object of this instance.
             */
            Companion::Algorithm::Detection::ShapeDetection* shapeDetectionObj;

        internal:

            /**
             * Internal method to provide the native 'ShapeDetection' object.
             *
             * @return pointer to the native 'ShapeDetection' object
             */
            Companion::Algorithm::Detection::ShapeDetection* getShapeDetection();
    };
}
