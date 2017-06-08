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

#include "ImageStream.h"
#include "..\utils\CompanionError.h"

using namespace CompanionWinRT;

ImageStream::ImageStream(int maxImages)
{
    this->imageStreamObj = new Companion::Input::Image(maxImages);
}

ImageStream::~ImageStream()
{
    delete this->imageStreamObj;
    this->imageStreamObj = nullptr;
}

void ImageStream::addImage(Platform::String^ imgPath)
{
    this->imageStreamObj->addImage(ps2ss(imgPath));
}

Companion::Input::Stream* ImageStream::getStream()
{
    return this->imageStreamObj;
}
