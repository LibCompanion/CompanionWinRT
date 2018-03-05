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

#include <codecvt>

#include "CompanionUtils.h"

Companion::ColorFormat CompanionWinRT::getColorFormat(CompanionWinRT::ColorFormat colorFormat)
{
    Companion::ColorFormat format = Companion::ColorFormat::RGB;

    switch (colorFormat)
    {
        case CompanionWinRT::ColorFormat::RGB:
            format = Companion::ColorFormat::RGB;
            break;
        case CompanionWinRT::ColorFormat::RGBA:
            format = Companion::ColorFormat::RGBA;
            break;
        case CompanionWinRT::ColorFormat::BGR:
            format = Companion::ColorFormat::BGR;
            break;
        case CompanionWinRT::ColorFormat::BGRA:
            format = Companion::ColorFormat::BGRA;
            break;
        case CompanionWinRT::ColorFormat::GRAY:
            format = Companion::ColorFormat::GRAY;
            break;
    }

    return format;
}

Companion::SCALING CompanionWinRT::getScaling(CompanionWinRT::Scaling scaling)
{
    Companion::SCALING compScaling = Companion::SCALING::SCALE_2048x1152;

    switch (scaling)
    {
        case CompanionWinRT::Scaling::SCALE_2048x1152:
            compScaling = Companion::SCALING::SCALE_2048x1152;
            break;
        case CompanionWinRT::Scaling::SCALE_1920x1080:
            compScaling = Companion::SCALING::SCALE_1920x1080;
            break;
        case CompanionWinRT::Scaling::SCALE_1600x900:
            compScaling = Companion::SCALING::SCALE_1600x900;
            break;
        case CompanionWinRT::Scaling::SCALE_1408x792:
            compScaling = Companion::SCALING::SCALE_1408x792;
            break;
        case CompanionWinRT::Scaling::SCALE_1344x756:
            compScaling = Companion::SCALING::SCALE_1344x756;
            break;
        case CompanionWinRT::Scaling::SCALE_1280x720:
            compScaling = Companion::SCALING::SCALE_1280x720;
            break;
        case CompanionWinRT::Scaling::SCALE_1152x648:
            compScaling = Companion::SCALING::SCALE_1152x648;
            break;
        case CompanionWinRT::Scaling::SCALE_1024x576:
            compScaling = Companion::SCALING::SCALE_1024x576;
            break;
        case CompanionWinRT::Scaling::SCALE_960x540:
            compScaling = Companion::SCALING::SCALE_960x540;
            break;
        case CompanionWinRT::Scaling::SCALE_896x504:
            compScaling = Companion::SCALING::SCALE_896x504;
            break;
        case CompanionWinRT::Scaling::SCALE_800x450:
            compScaling = Companion::SCALING::SCALE_800x450;
            break;
        case CompanionWinRT::Scaling::SCALE_768x432:
            compScaling = Companion::SCALING::SCALE_768x432;
            break;
        case CompanionWinRT::Scaling::SCALE_640x360:
            compScaling = Companion::SCALING::SCALE_640x360;
            break;
    }

    return compScaling;
}

Platform::String^ CompanionWinRT::ss2ps(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return ref new Platform::String(converter.from_bytes(str).c_str());
}

std::string CompanionWinRT::ps2ss(Platform::String^ str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.to_bytes(str->Data());
}
