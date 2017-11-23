# companionWinRT

Windows Runtime Component wrapper for [Companion](https://github.com/LibCompanion/libCompanion/). Since the WinRT Component uses C++/CX it can be used in *Universal Windows Platform* (UWP) apps that are written in C#, Visual Basic, JavaScript, and other languages that support the Windows Runtime.

## Dependencies

* OpenCV 3 for WinRT/UWP: [opencvWinRT](https://github.com/LibCompanion/opencvWinRT/)

## Building companionWinRT

1. To begin with, you will need to build OpenCV 3 for WinRT/UWP: [opencvWinRT](https://github.com/LibCompanion/opencvWinRT/)
2. Simply use cmake or cmake-gui to build companionWinRT.

## Getting started

Feel free to use the provided sample app as a starting point. Unfortunately CMake is currently not able to integrate the C# project to the generated Visual Studio Solution automatically. Follow these steps to do that manually:

1. Open the generated project file `CompanionWinRT.sln` in Visual Studio.
2. Go to `File` > `Open` > `Project/Solution...`, select the project file `<build_dir>\CompanionUWPSample\CompanionUWPSample.csproj` and choose `Add to Solution`.
> Be aware that the sample project is being copied to the build directory so it won't be under version control.

3. Add the `CompanionWinRT` project as a reference to the `CompanionUWPSample` project: right click on the project name and choose `Add` > `Reference...`.
4. Right click on `CompanionUWPSample` and choose `Set as StartUp Project`.
5. Add your own image samples and an image source folder to the project assets (video is not supported at the moment).
6. Add your OpenCV-DLLs to the project by right clicking on `CompanionUWPSample` and choosing `Add` > `Existing Item...`.

## License

```
CompanionWinRT is a Windows Runtime wrapper for Companion.
Copyright (C) 2017 Dimitri Kotlovsky

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
```
