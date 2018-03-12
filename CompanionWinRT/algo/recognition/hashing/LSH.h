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

#include <companion\algo\recognition\hashing\LSH.h>

namespace CompanionWinRT
{
    /**
     * This class provides a WinRT wrapper for the 'LSH' functionality of the Companion framework (CPU only).
     *
     * Note 1:
     * This is a minimum construction -- it has to be extended to provide the same flexability as the Companion native code.
     *
     * Note 2:
     * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
     * We can not mirror the plausible interface / abstract class 'Hashing' for this wrapper.
     *
     * @author Dimitri Kotlovsky, Andreas Sekulski
     */
    public ref class LSH sealed
    {
        public:

            /**
             * Create an 'LSH' wrapper.
             */
            LSH();

            /**
             * Destruct this instance.
             */
            virtual ~LSH();

        private:

            /**
             * The native 'LSH' object of this instance.
             */
            Companion::Algorithm::Recognition::Hashing::LSH* lshObj;

        internal:

            /**
             * Internal method to provide the native 'LSH' object.
             *
             * @return pointer to the native 'LSH' object
             */
            Companion::Algorithm::Recognition::Hashing::LSH* getLSH();
    };
}
