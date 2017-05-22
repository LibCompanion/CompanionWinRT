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

#include "Frame.h"

using namespace CompanionWinRT;

Frame::Frame(cv::Point upperLeft, cv::Point upperRight, cv::Point lowerRight, cv::Point lowerLeft)
{
    this->p0 = { upperLeft.x, upperLeft.y };
    this->p1 = { upperRight.x, upperRight.y };
    this->p2 = { lowerRight.x, lowerRight.y };
    this->p3 = { lowerLeft.x, lowerLeft.y };
}

Point Frame::getUpperLeftCorner()
{
    return this->p0;
}

Point Frame::getUpperRightCorner()
{
    return this->p1;
}

Point Frame::getLowerRightCorner()
{
    return this->p2;
}

Point Frame::getLowerLeftCorner()
{
    return this->p3;
}
