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

#include <companion\input\Image.h>

namespace CompanionWinRT
{
    /**
     * This class provides a WinRT wrapper for the 'ImageStream' functionality of the Companion project.
     *
     * Note:
     * Public inheritance is not possible in a Windows Runtime context (with very few exceptions). We can not mirror the
     * plausible abstract class 'Stream' for this wrapper.
     *
     * @author Dimitri Kotlovsky
     */
    public ref class ImageStream sealed
    {
        public:

            /**
             * Creates an 'ImageStream' wrapper with the provided maximum amount of images that can be loaded at the same time.
             *
             * @param maxImages     maximum amount of images that can be loaded at the same time
             */
            ImageStream(int maxImages);
            
            /**
             * Destructs this instance.
             */
            virtual ~ImageStream();

            /**
             * Load an image that is going to be processed.
             *
             * @param imgPath   path of the image that is going to be processed
             * @return <code>true</code> if image was added successfully, <code>false</code> otherwise
             */
            bool addImage(Platform::String^ imgPath);

            /**
             * Load an image that is going to be processed.
             *
             * @param width     width of the image that is going to be processed
             * @param height    height of the image that is going to be processed
             * @param type      type of the image that is going to be processed (i.e. OpenCV image types)
             * @param data      data of the image that is going to be processed
             * @return <code>true</code> if image was added successfully, <code>false</code> otherwise
             */
            bool addImage(int width, int height, int type, const Platform::Array<uint8>^ data);

        private:

            /**
             * The native 'ImageStream' object of this instance.
             */
            Companion::Input::Image* imageStreamObj;

        internal:

            /**
             * Internal method to provide the native 'Stream' object (in this case an 'ImageStream' object).
             *
             * Note:
             * Public inheritance is not possible in a WinRT context (with very few exceptions). We can not mirror the
             * plausible abstract class 'Stream' for this wrapper.
             *
             * @return Pointer to the native 'Stream' object
             */
            Companion::Input::Stream* getStream();
    };
}
