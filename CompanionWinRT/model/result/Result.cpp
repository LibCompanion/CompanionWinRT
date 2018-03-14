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

#include "Result.h"

using namespace CompanionWinRT;

Result::Result(ResultType resultType, Frame^ frame, int id, Platform::String^ objectType, int score) : resultType(resultType), frame(frame), id(id), objectType(objectType), score(score)
{
}

Result::~Result()
{
}

ResultType Result::getType()
{
    return this->resultType;
}

int Result::getScore()
{
    return this->score;
}

Frame^ Result::getFrame()
{
    return this->frame;
}

Platform::String^ Result::getDescription()
{
    return (this->resultType == ResultType::RECOGNITION) ? this->id.ToString() : this->objectType;
}

int Result::getID()
{
    return this->id;
}
