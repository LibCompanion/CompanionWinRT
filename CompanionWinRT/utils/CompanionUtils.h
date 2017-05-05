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

#pragma once

namespace CompanionWinRT
{
    std::string StrToWStr(Platform::String^ input);
    //cv::String ConvertPath(Platform::String^ path);

    /**
     * Converts std::string to Platform::String.
     *
     * @param s The std::string to convert.
     * @return WinRT compatible String.
     */
    Platform::String^ ss2ps(const std::string& s);

    /**
     * Converts Platform::String to std::string.
     *
     * @param s The Platform::String to convert.
     * @return std::string.
     */
    std::string ps2ss(Platform::String^ str);
}

std::wstring s2ws(const std::string& str);
std::string ws2s(const std::wstring& wstr);
