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
     * Result types.
     */
    public enum class ResultType {
        RECOGNITION,
        DETECTION
    };

    /**
     * This class represents a model to store object detection or recognition results.
     *
     * Note 1:
     * This is a minimum construction -- it has to be extended to provide the same flexability as the Companion native code.
     *
     * Note:
     * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
     * We can not mirror the plausible abstract class 'Result' for this wrapper.
     *
     * @author Dimitri Kotlovsky, Andreas Sekulski
     */
    public ref class Result sealed
    {
        public:

            /**
             * Create a 'Result' object.
             *
             * @param resultType    result type
             * @param id            id of the recognized object (recognition result) or -1 if this is a detection result
             * @param score         matching score
             * @param frame         pixel frame that represents the detected or recognized object
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
             * We can not mirror the plausible abstract class 'Result' for this wrapper.
             */
            Result(ResultType resultType, Frame^ frame, int id, int score) : Result(resultType, frame, id, "", score)
            {};

            /**
             * Create a 'Result' object.
             *
             * @param resultType    result type
             * @param objectType    object type (detection result) of empty string if this is a recognition result
             * @param score         matching score
             * @param frame         pixel frame that represents the detected or recognized object
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
             * We can not mirror the plausible abstract class 'Result' for this wrapper.
             */
            Result(ResultType resultType, Frame^ frame, Platform::String^ objectType, int score) : Result(resultType, frame, -1, objectType, score)
            {};

            /**
             * Create a 'Result' object.
             *
             * @param resultType    result type
             * @param id            id of the recognized object (recognition result) or -1 if this is a detection result
             * @param objectType    object type (detection result) of empty string if this is a recognition result
             * @param score         matching score
             * @param frame         pixel frame that represents the detected or recognized object
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
             * We can not mirror the plausible abstract class 'Result' for this wrapper.
             */
            Result(ResultType resultType, Frame^ frame, int id, Platform::String^ objectType, int score);

            /**
             * Destruct this instance.
             */
            virtual ~Result();

            /**
             * Return the result type.
             *
             * @return result type
             */
            ResultType getType();

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

            /**
             * Return the ID of the recognized object if this is a recognition result.
             *
             * @return ID of the recognized object
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
             * We can not mirror the plausible abstract class 'Result' for this wrapper.
             */
            int getID();

        private:

            /**
             * Result type.
             */
            ResultType resultType;

            /**
             * Detection or recognition score (0% - 100%).
             */
            int score;

            /**
             * A pixel frame representing the detected or recognized object.
             */
            Frame^ frame;

            /**
             * Object type.
             */
            Platform::String^ objectType;

            /**
             * The ID of the recognized object if this is a recognition result.
             *
             * Note:
             * Native code in interfaces and public inheritance are not possible in a Windows Runtime context (with very few exceptions).
             * We can not mirror the plausible abstract class 'Result' for this wrapper.
             */
            int id;
    };
}