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

#include "ShapeDetection.h"

using namespace CompanionWinRT;

ShapeDetection::ShapeDetection(int minCorners, int maxCorners, Platform::String^ shapeDescription, double cannyThreshold, int dilateIteration, StructuringElement morphKernel,
    StructuringElement erodeKernel, StructuringElement dilateKernel)
{
    this->shapeDetectionObj = new Companion::Algorithm::Detection::ShapeDetection(minCorners, maxCorners, Utils::ps2ss(shapeDescription), cannyThreshold, dilateIteration,
        cv::getStructuringElement((int)morphKernel.shape, cv::Size(morphKernel.size.width, morphKernel.size.height)),
        cv::getStructuringElement((int)erodeKernel.shape, cv::Size(erodeKernel.size.width, erodeKernel.size.height)),
        cv::getStructuringElement((int)dilateKernel.shape, cv::Size(dilateKernel.size.width, dilateKernel.size.height))
    );
}

ShapeDetection::~ShapeDetection()
{
    delete this->shapeDetectionObj;
    this->shapeDetectionObj = nullptr;
}

Companion::Algorithm::Detection::ShapeDetection* ShapeDetection::getShapeDetection()
{
    return this->shapeDetectionObj;
}
