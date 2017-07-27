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

#include <companion/util/Util.h>

namespace CompanionWinRT
{
    /**
     * Enumeration class for color formats.
     */
    public enum class ColorFormat
    {
        RGB,
        RGBA,
        BGR,
        BGRA,
        GRAY
    };

    /**
     * Enumeration class for scaling.
     */
    public enum class Scaling
    {
        SCALE_2048x1152,
        SCALE_1920x1080,
        SCALE_1600x900,
        SCALE_1408x792,
        SCALE_1344x756,
        SCALE_1280x720,
        SCALE_1152x648,
        SCALE_1024x576,
        SCALE_960x540,
        SCALE_896x504,
        SCALE_800x450,
        SCALE_768x432,
        SCALE_640x360
    };

    /**
     * Returns the Companion color format for the given winRT color format.
     *
     * @param colorFormat   WinRT color format.
     * @return Companion color format.
     */
    Companion::ColorFormat getColorFormat(ColorFormat colorFormat);

    /**
     * Returns the Companion scaling value for the given winRT scaling value.
     *
     * @param scaling   WinRT scaling value.
     * @return Companion scaling value.
     */
    Companion::SCALING getScaling(Scaling scaling);

    /**
     * Converts std::string to Platform::String.
     *
     * @param str   the std::string to be converted
     * @return winRT compatible Platform::String
     */
    Platform::String^ ss2ps(const std::string& str);

    /**
     * Converts Platform::String to std::string.
     *
     * @param str   the Platform::String to be converted
     * @return native c++ compatible std::string
     */
    std::string ps2ss(Platform::String^ str);
}
