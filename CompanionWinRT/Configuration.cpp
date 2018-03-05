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

#include "Configuration.h"
#include "utils\CompanionError.h"

using namespace CompanionWinRT;

void Configuration::setProcessing(ObjectDetection^ detection)
{
    this->detection = detection;
    this->configurationObj.setProcessing(this->detection->getProcessing(&this->configurationObj));
}

void Configuration::setResultCallback(ResultDelegate^ callback, ColorFormat colorFormat)
{
    Companion::ColorFormat colorForm = getColorFormat(colorFormat);
    this->configurationObj.setResultHandler([callback](std::vector<Companion::Model::Result*> results, cv::Mat image)
    {
        Vector<Result^>^ resultsCX = ref new Vector<Result^>();
        Result^ resultCX;
        Frame^ frameCX;

        Companion::Model::Result* result;
        Companion::Draw::Frame* frame;

        // Process all positive results
        for (size_t i = 0; i < results.size(); i++)
        {
            result = results.at(i);
            frame = dynamic_cast<Companion::Draw::Frame*>(result->getModel());
            
            // Draw a frame around the detected object
            frame->draw(image);

            // Draw the id of the detected object
            cv::putText(image,
                        std::to_string(result->getId()),
                        frame->getTopRight(),
                        cv::FONT_HERSHEY_DUPLEX,
                        2,
                        frame->getColor(),
                        frame->getThickness());

            // Capsule the result data into ABI friendly C++/CX objects
            frameCX = ref new Frame(Point{ frame->getTopLeft().x,     frame->getTopLeft().y     },
                                    Point{ frame->getTopRight().x,    frame->getTopRight().y    },
                                    Point{ frame->getBottomRight().x, frame->getBottomRight().y },
                                    Point{ frame->getBottomLeft().x,  frame->getBottomLeft().y  });
            resultCX = ref new Result(result->getId(), result->getScoring(), frameCX);
            resultsCX->Append(resultCX);
        }

        // Copy image data to a byte[] so it can be passed across the ABI
        Platform::Array<uint8>^ imageData = ref new Platform::Array<uint8>(image.data, image.step.buf[1] * image.cols * image.rows);

        // Invoke callback
        callback->Invoke(resultsCX, imageData);

        // Release data
        image.release();
        results.clear();
    }, colorForm);
}

void Configuration::setErrorCallback(ErrorDelegate^ callback)
{
    this->configurationObj.setErrorHandler([callback](Companion::Error::Code code)
    {
        callback->Invoke(ss2ps(Companion::Error::getError(code)));
    });
}

void Configuration::setSkipFrame(int skipFrame)
{
    this->configurationObj.setSkipFrame(skipFrame);
}

void Configuration::setImageBuffer(int imageBuffer)
{
    this->configurationObj.setImageBuffer(imageBuffer);
}

int Configuration::getSkipFrame()
{
    return this->configurationObj.getSkipFrame();
}

void Configuration::setSource(ImageStream^ stream)
{
    this->stream = stream;
    this->configurationObj.setSource(this->stream->getStream());
}

ImageStream^ Configuration::getSource()
{
    return this->stream;
}

void Configuration::addModel(FeatureMatchingModel^ model)
{
    this->models->Append(model);
    if (!this->configurationObj.addModel(model->getModel()))
    {
        int hresult = static_cast<int>(ErrorCode::model_not_added);
        throw ref new Platform::Exception(hresult);
    }
}

IVector<FeatureMatchingModel^>^ Configuration::getModels()
{
    return this->models;
}

void Configuration::removeModel(int modelID)
{
    for (int i = 0; i < this->models->Size; i++)
    {
        if (this->models->GetAt(i)->getModel()->getID() == modelID)
        {
            this->configurationObj.removeModel(modelID);
            this->models->RemoveAt(i);
        }
    }
}

void Configuration::clearModels()
{
    this->configurationObj.clearModels();
    this->models->Clear();
}

void Configuration::run()
{
    this->configurationObj.run();
}

void Configuration::stop()
{
    this->configurationObj.stop();
}

/* Videos as source are not supported right now. You have to build FFMpeg for OpenCV and WinRT.
 * Use these instructions (tricky, because some are outdated):
 * - build FFMpeg for WinRT: https://trac.ffmpeg.org/wiki/CompilationGuide/WinRT
 * - include FFMpeg to OpenCV source and build OpenCV: https://github.com/opencv/opencv/tree/3.0.0/3rdparty/ffmpeg (outdated)
 * - this may be helpful: http://www.answers.opencv.org/question/124858/how-to-build-opencv_ffmpegdll-from-patched-ffmpeg-source/
 * - Attention: You have to build OpenCV for WinRT as well:
 *    - https://github.com/opencv/opencv/tree/master/platforms/winrt (outdated)
 *    - get necessary changes from here: https://github.com/sylvain-prevost/opencv-hololens
 */
//Platform::String^ Configuration::loadVideo(Platform::String^ videoPath) {
//
//    Platform::String^ output = "";
//
//    cv::VideoCapture cap(ps2ss(videoPath));
//    if (!cap.isOpened()) {
//        output += "The file could not be opened for video capture\n";
//    } else {
//        output += "The file was opened for video capture\n";
//    }
//
//    Companion::Input::Stream *stream = new Companion::Input::Video(ps2ss(videoPath));
//
//    return output;
//}
