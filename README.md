# CompanionWinRT

CompanionWinRT wraps the [libCompanion](https://github.com/LibCompanion/libCompanion/) CV library in a Windows Runtime Component. Since it uses C++/CX the WinRT Component can be used in Universal Windows Platform (UWP) apps that are written in C#, Visual Basic, JavaScript, and other languages that support the Windows Runtime.

# Dependencies

* OpenCV 3.x (you've got to build it for UWP first - will be provided as a submodule in near future)
* libCompanion (provided as a submodule)

# Building CompanionWinRT

1. To begin with, you will need to build OpenCV 3.x for UWP. This README will be updated in near future to provide some help with doing that.
2. Simply use cmake or cmake-gui to build CompanionWinRT.

## Building OpenCV 3.x for UWP

* TODO...

# Getting started

Feel free to use the provided sample app as a starting point. Unfortunately CMake is currently not able to integrate the C# project to the generated Visual Studio Solution automatically. Follow these steps to do that manually:
1. Open the generated Solution "_\<build_dir\>\\CompanionWinRT.sln_" in Visual Studio.
2. `File` > `Open` > `Project/Solution...` Select the project file _CompanionUWPSample.csproj_ from "_\<build_dir\>\\CompanionUWPSample\\_" and choose `Add to Solution`.
> Be aware that the sample project is being copied to the build directory so it won't be under version control.
3. Add the CompanionWinRT project as a reference to the CompanionUWPSample project: right click on the project name and choose `Add` > `Reference...`.
4. Right click on `CompanionUWPSample` and choose `Set as StartUp Project`.
5. Add your own image samples and an image source folder to the project assets (video as a source is not supported at the moment).
6. Add your OpenCV-DLLs to the project by right clicking on `CompanionUWPSample` and choosing `Add` > `Existing Item...`.

# Known Issues
* Currently the sample app is only working when using the debug build.

# License

This program is a Windows Runtime wrapper for the Companion CV library.
            https://github.com/LibCompanion/libCompanion

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
