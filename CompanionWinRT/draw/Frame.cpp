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

#include "Frame.h"

using namespace CompanionWinRT;

Frame::Frame(Point upperLeft, Point upperRight, Point lowerRight, Point lowerLeft)
    : upperLeft(upperLeft), upperRight(upperRight), lowerRight(lowerRight), lowerLeft(lowerLeft)
{
}

Point Frame::getUpperLeftCorner()
{
    return this->upperLeft;
}

Point Frame::getUpperRightCorner()
{
    return this->upperRight;
}

Point Frame::getLowerRightCorner()
{
    return this->lowerRight;
}

Point Frame::getLowerLeftCorner()
{
    return this->lowerLeft;
}
