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

#include "Configuration.h"
#include "utils\CompanionError.h"

#include <ppltasks.h>
#include <Robuffer.h>

using namespace CompanionWinRT;
using namespace Concurrency;

/**
 * Initialize static data members (because static data members must be explicitly defined in exactly one compilation unit).
 *
 * Note:
 * Another approach is to use GetDataDelegate/getDataEvent to throw a static event to a instance method. But it will be received
 * by all instances and it increases the overhead (should be further examined).
 */
uint8* Configuration::pixels = nullptr;
CoreDispatcher^ Configuration::dispatcher = nullptr;




Configuration::Configuration()
{
    this->configurationObj = new Companion::Configuration();

    // Define callback functions
    //std::function<void(std::vector<Companion::Draw::Drawable*>, cv::Mat)> callback = std::bind(&CallbackWrapper::callback, this->callbackWrapper, std::placeholders::_1, std::placeholders::_2);
    //std::function<void(std::vector<Companion::Draw::Drawable*>, cv::Mat)> callback = std::bind(&Configuration::callback, this, std::placeholders::_1, std::placeholders::_2);
    this->configurationObj->setResultHandler(Configuration::callback);
    //std::function<void(Companion::Error::Code)> error = std::bind(&Configuration::error, this, std::placeholders::_1);
    this->configurationObj->setErrorHandler(Configuration::error);
}

Configuration::~Configuration()
{
    delete this->configurationObj;
    this->configurationObj = nullptr;
}

IAsyncAction^ Configuration::setProcessing(ObjectDetection^ detection)
{
    return create_async([this, detection]()
    {
        this->configurationObj->setProcessing(detection->getProcessing(this->configurationObj));
    });
}

IAsyncAction^ Configuration::setSkipFrame(int skipFrame)
{
    return create_async([this, skipFrame]()
    {
        this->configurationObj->setSkipFrame(0);
    });
}

void Configuration::setPixelBuffer(IBuffer^ pixelBuffer)
{
    // Query the IBufferByteAccess interface.  
    Microsoft::WRL::ComPtr<IBufferByteAccess> bufferByteAccess;
    reinterpret_cast<IInspectable*>(pixelBuffer)->QueryInterface(IID_PPV_ARGS(&bufferByteAccess));

    // Retrieve the buffer data.  
    uint8* pixels = nullptr;
    bufferByteAccess->Buffer(&pixels);
    Configuration::pixels = pixels;
}

IAsyncAction^ Configuration::setSource(ImageStream^ stream)
{
    return create_async([this, stream]()
    {
        this->configurationObj->setSource(stream->getStream());
    });
}

IAsyncAction^ Configuration::addModel(FeatureMatchingModel^ model)
{
    return create_async([this, model]()
    {
        if (!this->configurationObj->addModel(model->getModel()))
        {
            int hresult = static_cast<int>(ErrorCode::model_not_added);
            throw ref new Platform::Exception(hresult);
        }
    });
}

IAsyncAction^ Configuration::run()
{
    // Define dispatcher for the UI thread
    Configuration::dispatcher = CoreWindow::GetForCurrentThread()->Dispatcher;

    return create_async([this]()
    {
        std::queue<cv::Mat>* queue = new std::queue<cv::Mat>();
        Companion::Thread::StreamWorker* ps = new Companion::Thread::StreamWorker(*queue);

        Configuration::getDataEvent += ref new GetDataDelegate(this, &Configuration::GetDataImpl2);

        try
        {
            this->configurationObj->run(*ps);
        }
        catch (Companion::Error::Code errorCode)
        {
            Configuration::error(errorCode);
        }
    });
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

void Configuration::error(Companion::Error::Code code)
{
    int hresult = static_cast<int>(getErrorCode(code));
    throw ref new Platform::Exception(hresult);
}

void Configuration::callback(std::vector<Companion::Draw::Drawable*> objects, cv::Mat frame)
{
    Companion::Draw::Drawable *drawable;

    for (int x = 0; x < objects.size(); x++)
    {
        drawable = objects.at(x);
        drawable->draw(frame);
    }

    // Add alpha channel (required for WritableBitmap)
    cv::Mat image = cv::Mat(frame.rows, frame.cols, CV_8UC4);
    try
    {
        cvtColor(frame, image, CV_BGR2BGRA);
    }
    catch (cv::Exception ex)
    {
        OutputDebugString(ss2ps(ex.msg)->Data());
    }

    // Copy new data to raw pixel bytes of the WritableBitmap pixelbuffer
    memcpy(Configuration::pixels, image.data, image.step.buf[1] * image.cols*image.rows);

    //uint8* temp = _pixels;
    //const unsigned int width = 1920;
    //const unsigned int height = 1080;

    //for (unsigned int k = 0; k < height; k++)
    //{
    //    for (unsigned int i = 0; i < (width * 4); i += 4)
    //    {
    //        int pos = k * (width * 4) + (i);
    //        temp[pos] = image.data[pos];
    //        temp[pos + 1] = image.data[pos + 1];
    //        temp[pos + 2] = image.data[pos + 2];
    //        temp[pos + 3] = image.data[pos + 3];
    //    }
    //}

    // Release frames
    frame.release();
    image.release();

    Configuration::dispatcher->RunAsync(CoreDispatcherPriority::High, ref new DispatchedHandler([]()
    {
        featuresFoundEvent();

    }, Platform::CallbackContext::Any));
}




/***********************************************************************************************
 *+++ TEST +++
 ***********************************************************************************************/
void Configuration::GetDataImpl(std::vector<Companion::Draw::Drawable*> objects, cv::Mat frame)
{
    Configuration::getDataEvent(objects, frame);
}

void Configuration::GetDataImpl2(std::vector<Companion::Draw::Drawable*> objects, cv::Mat frame)
{
    Companion::Draw::Drawable *drawable;

    for (int x = 0; x < objects.size(); x++)
    {
        drawable = objects.at(x);
        drawable->draw(frame);
    }

    // Add alpha channel (required for WritableBitmap)
    cv::Mat image = cv::Mat(frame.rows, frame.cols, CV_8UC4);
    try
    {
        cvtColor(frame, image, CV_BGR2BGRA);
    }
    catch (cv::Exception ex)
    {
        OutputDebugString(ss2ps(ex.msg)->Data());
    }

    // Copy new data to raw pixel bytes of the WritableBitmap pixelbuffer
    memcpy(Configuration::pixels, image.data, image.step.buf[1] * image.cols*image.rows);

    //uint8* temp = _pixels;
    //const unsigned int width = 1920;
    //const unsigned int height = 1080;

    //for (unsigned int k = 0; k < height; k++)
    //{
    //    for (unsigned int i = 0; i < (width * 4); i += 4)
    //    {
    //        int pos = k * (width * 4) + (i);
    //        temp[pos] = image.data[pos];
    //        temp[pos + 1] = image.data[pos + 1];
    //        temp[pos + 2] = image.data[pos + 2];
    //        temp[pos + 3] = image.data[pos + 3];
    //    }
    //}

    // Release frames
    frame.release();
    image.release();

    Configuration::dispatcher->RunAsync(CoreDispatcherPriority::High, ref new DispatchedHandler([]()
    {
        Configuration::featuresFoundEvent();

    }, Platform::CallbackContext::Any));
}
