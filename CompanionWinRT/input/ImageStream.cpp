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

#include "ImageStream.h"
#include "CompanionWinRT\utils\CompanionUtils.h"

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

bool ImageStream::addImage(Platform::String^ imgPath)
{
    return this->imageStreamObj->addImage(Utils::ps2ss(imgPath));
}

bool ImageStream::addImage(int width, int height, int type, const Platform::Array<uint8>^ data)
{
    return this->imageStreamObj->addImage(width, height, type, data->Data);
}

Companion::Input::Image* ImageStream::getImageStream()
{
    return this->imageStreamObj;
}
