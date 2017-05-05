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

#include <collection.h>

#include "ImageStream.h"
#include "..\utils\CompanionError.h"

using namespace CompanionWinRT;

ImageStream::ImageStream(IVector<Platform::String^>^ imagePathList)
{
    if ((imagePathList != nullptr) && (imagePathList->Size != 0) && (imagePathList->First() != nullptr))
    {
        this->imageStreamObj = new Companion::Input::Image();
        for each (Platform::String^ path in imagePathList)
        {
            this->imageStreamObj->addImagePath(ps2ss(path));
        }
    }
    else
    {
        int hresult = static_cast<int>(ErrorCode::image_path_list_not_set);
        throw ref new Platform::Exception(hresult);
    }
}

ImageStream::~ImageStream()
{
    delete this->imageStreamObj;
    this->imageStreamObj = nullptr;
}

Companion::Input::Stream* ImageStream::getStream()
{
    return this->imageStreamObj;
}
