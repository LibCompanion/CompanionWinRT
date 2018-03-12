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

#include <companion\input\Image.h>

namespace CompanionWinRT
{
    /**
     * This class provides a WinRT wrapper for the 'ImageStream' functionality of the Companion framework.
     *
     * Note:
     * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
     * We can not mirror the plausible interface / abstract class 'Stream' for this wrapper.
     *
     * @author Dimitri Kotlovsky, Andreas Sekulski
     */
    public ref class ImageStream sealed
    {
        public:

            /**
             * Create an 'ImageStream' wrapper with the provided maximum amount of images that can be loaded at the same time.
             *
             * @param maxImages     maximum amount of images that can be loaded at the same time
             */
            ImageStream(int maxImages);
            
            /**
             * Destruct this instance.
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
             * Internal method to provide the native 'ImageStream' object.
             *
             * @return Pointer to the native 'ImageStream' object
             */
            Companion::Input::Image* getImageStream();
    };
}
