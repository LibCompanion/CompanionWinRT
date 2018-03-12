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

#include "CompanionWinRT\draw\Frame.h"

namespace CompanionWinRT
{
    /**
     * This class represents a model to store object detection or recognition results.
     *
     * @author Dimitri Kotlovsky, Andreas Sekulski
     */
    public ref class Result sealed
    {
        public:

            /**
             * Create a 'Result' object.
             */
            Result(Platform::String^ description, int scoring, Frame^ frame);

            /**
             * Return the matching score of the detected or recognized object.
             *
             * @return matching score
             */
            int getScore();

            /**
             * Return the pixel frame of the detected or recognized object.
             *
             * @return pixel frame
             */
            Frame^ getFrame();

            /**
             * Return the object description. This may be the ID or the object type.
             *
             * @return object description
             */
            Platform::String^ getDescription();

        private:

            /**
             * The ID of the detected or recognized object.
             */
            int id;

            /**
             * Detection or recognition score (0% - 100%).
             */
            int score;

            /**
             * A pixel frame representing the detected or recognized object.
             */
            Frame^ frame;

            /**
             * The description of the detected or recognized object.
             */
            Platform::String^ description;
    };
}