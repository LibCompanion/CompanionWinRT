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

#include "Configuration.h"
#include "utils\CompanionError.h"

using namespace CompanionWinRT;

void Configuration::setProcessing(ObjectDetection^ detection)
{
    this->detection = detection;
    this->configurationObj.setProcessing(this->detection->getProcessing(&this->configurationObj));
}

void Configuration::setResultCallback(ResultDelegate^ callback)
{
    this->configurationObj.setResultHandler([callback](std::vector<std::pair<Companion::Draw::Drawable*, int>> objects, cv::Mat image)
    {
        std::vector<Frame^> frames;
        Companion::Draw::Drawable *drawable;

        for (size_t i = 0; i < objects.size(); i++)
        {
            // Mark the detected object
            drawable = objects.at(i).first;
            drawable->draw(image);

            // Cast the drawables to lines
            Companion::Draw::Lines *dLines = dynamic_cast<Companion::Draw::Lines*>(drawable);
            if (dLines != nullptr)
            {
                // Draw the id of the detected object
                std::vector<Companion::Draw::Line*> lines = dLines->getLines();
                cv::putText(image, std::to_string(objects.at(i).second), lines.at(0)->getEnd(), cv::FONT_HERSHEY_DUPLEX, 2, cv::Scalar(0, 255, 0), 4);
            
                // Capsule the pixel data into ABI friendly 'Frame' objects
                Frame^ frame = ref new Frame(lines.at(0)->getStart(), lines.at(0)->getEnd(), lines.at(3)->getStart(), lines.at(3)->getEnd());
                frames.push_back(frame);
            }
        }

        // Add alpha channel (required for WritableBitmap)
        cv::Mat markedImage = cv::Mat(image.rows, image.cols, CV_8UC4);
        cv::cvtColor(image, markedImage, CV_BGR2BGRA);

        // Copy image data to a byte[] so it can be passed across the ABI
        Platform::Array<uint8>^ imageData = ref new Platform::Array<uint8>(markedImage.data, markedImage.step.buf[1] * markedImage.cols * markedImage.rows);

        // Create a sutable vector type that can be passed across the ABI
        Platform::Collections::Vector<Frame^>^ frameVector = ref new Platform::Collections::Vector<Frame^>(frames);

        // Invoke callback
        callback->Invoke(frameVector, imageData);
    });
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
    this->models.push_back(model);
    if (!this->configurationObj.addModel(model->getModel()))
    {
        int hresult = static_cast<int>(ErrorCode::model_not_added);
        throw ref new Platform::Exception(hresult);
    }
}

void Configuration::run()
{
    std::queue<cv::Mat> queue;
    Companion::Thread::StreamWorker ps(queue);
    this->configurationObj.run(ps);
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
