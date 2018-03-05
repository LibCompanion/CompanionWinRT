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

#include <companion\model\result\Result.h>

#include "companionWinRT\draw\Frame.h"

namespace CompanionWinRT
{
    /**
     * This class represents a model to store object detection results.
     *
     * @author Dimitri Kotlovsky
     */
    public ref class Result sealed
    {
    public:

        /**
         * Creates a 'Result' object.
         */
        Result(int id, int scoring, Frame^ frame);

        /**
         * Returns the ID of this model.
         *
         * @return ID of this model
         */
        int getId();

        /**
         * Returns the matching score of this model.
         *
         * @return matching score
         */
        int getScore();

        /**
         * Returns the pixel frame of this model.
         *
         * @return pixel frame
         */
        Frame^ getFrame();

    private:

        /**
         * The ID of this model.
         */
        int id;

        /**
         * Matching score (0% - 100%).
         */
        int score;

        /**
         * A pixel frame representing the detected object.
         */
        Frame^ frame;
    };
}