#![Companion](https://nepitwin.github.io/libCompanion/images/logo.png "Companion")

[CompanionWinRTWrapper](https://nepitwin.github.io/libCompanion) wrapps the Companiom computer vision library (libCompanion) in a Windows Runtime Component. Since it uses C++/CX, the WinRT Component can be used in Universal Windows Apps that are written in C#, Visual Basic, JavaScript, and other languages that support the Windows Runtime.

# Dependencies

* OpenCV Version 3.x (you've got to build it for UWP first, v.i. - will be provided as a submodule in the future)
* libCompanion (provided as submodule)

# Using CMake

...
1. libCompanion is integraded as a submodul so cmake-gui will ask you if you want to use Cuda. Cuda is not supported for Windows Runtime.
...

## Build CompanionWinRTWrapper

Simply use cmake or cmake-gui to build CompanionWinRTWrapper for your platform.

# Getting started

### Build OpenCV 3.x for UWP

...
1. open project
2. add to solution
3. reference CompanionWinRT project
3. set as startup project
4. Add your own image samples and image source folder to the project assets
5. Unfortunately you will have to copy your opencv DLLs into the project by right
clicking on the project name and choose ```Add``` > ```Existing Item...```
...


# Known Bugs
* The sample app is currently only working when using the debug build.

### License

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
