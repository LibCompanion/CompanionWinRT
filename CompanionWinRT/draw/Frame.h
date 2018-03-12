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

#include <opencv2/core/core.hpp>

namespace CompanionWinRT
{
    /**
     * This strcut represents a point in an image.
     */
    public value struct Point
    {
        int x;
        int y;
    };

    /**
     * This class represents a frame around a detected object in an image.
     *
     * @author Dimitri Kotlovsky, Andreas Sekulski
     */
    public ref class Frame sealed
    {
    public:

        /**
         * Create a 'Frame' object with the provided corners.
         *
         * @param upperLeft     upper left corner
         * @param upperRight    upper right corner
         * @param lowerRight    lower right corner
         * @param lowerLeft     lower left corner
         */
        Frame(Point upperLeft, Point upperRight, Point lowerRight, Point lowerLeft);
        
        /**
         * Return the upper left corner of this frame.
         *
         * @return upper left corner
         */
        Point getUpperLeftCorner();

        /**
         * Return the upper right corner of this frame.
         *
         * @return upper right corner
         */
        Point getUpperRightCorner();

        /**
         * Return the lower right corner of this frame.
         *
         * @return lower right corner
         */
        Point getLowerRightCorner();

        /**
         * Return the lower left corner of this frame.
         *
         * @return lower left corner
         */
        Point getLowerLeftCorner();

    private:

        /**
         * The four corners of the frame around the detected object.
         *
         *   0               1
         *   -----------------
         *   |               |
         *   |               |
         *   |               |
         *   |               |
         *   -----------------
         *   3               2
         */
        Point upperLeft, upperRight, lowerRight, lowerLeft;

    };
}
