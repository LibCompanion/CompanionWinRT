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

#include <collection.h>
#include <codecvt>

#include "CompanionUtils.h"

Platform::String^ CompanionWinRT::ss2ps(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    Platform::String^ str = ref new Platform::String(r.c_str());
    return str;
}

std::string CompanionWinRT::ps2ss(Platform::String^ str)
{
    std::wstring s(str->Data());
    int len;
    int slength = (int)s.length();// +1;
    len = WideCharToMultiByte(CP_UTF8, 0, s.c_str(), slength, 0, 0, 0, 0);
    std::string r(len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, s.c_str(), slength, &r[0], len, 0, 0);
    return r;

    //std::wstring wstring = input->Data();

    //int slength = (int)wstring.length() + 1;
    //int size = WideCharToMultiByte(CP_UTF8, 0, wstring.c_str(), slength, 0, 0, 0, 0);
    //std::string r(size, '\0');
    //WideCharToMultiByte(CP_UTF8, 0, wstring.c_str(), slength, &r[0], size, 0, 0);
    //return r;
}

//cv::String ConvertPath(Platform::String^ path)
//{
//    std::wstring localPathW(path->Begin());
//
//    // Opt #1
//    //std::string localPath(localPathW.begin(), localPathW.end());
//
//    // Opt #2
//    //std::string localPath(StrToWStr(localPathW));
//
//    // Opt #3
//    size_t outSize = localPathW.length() + 1;
//    char* localPathC = new char[outSize];
//    size_t charsConverted = 0;
//    wcstombs_s(&charsConverted, localPathC, outSize, localPathW.c_str(), localPathW.length());
//    cv::String localPath(localPathC);
//
//    // Implicit conversion from std::string to cv::String
//    return localPath;
//}

std::string CompanionWinRT::StrToWStr(Platform::String^ input)
{
    if (input->IsEmpty())
    {
        return std::string();
    }

    std::wstring wstring = input->Data();

    int size = WideCharToMultiByte(CP_UTF8, 0, &wstring[0], (int)wstring.size(), NULL, 0, NULL, NULL);
    std::string result(size, 0);

    WideCharToMultiByte(CP_UTF8, 0, &wstring[0], (int)wstring.size(), &result[0], size, NULL, NULL);

    return result;
}

std::wstring s2ws(const std::string& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

std::string ws2s(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}