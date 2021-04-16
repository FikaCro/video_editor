#include "include/videothread.h"

#include <opencv2/opencv.hpp>

#include <QFileInfo>

#include <QDebug>

VideoThread::VideoThread(QObject* parent) : QThread(parent) {}

void VideoThread::run()
{
  videoPath = "/home/filipb/Downloads/video.mp4";
  if (videoPath.isEmpty() || videoPath.isNull())
  {
    emit videoEditingAborted();
    return;
  }

  cv::VideoCapture videoCapture(videoPath.toStdString());
  if (!videoCapture.isOpened())
  {
    emit videoEditingAborted();
    return;
  }

  QFileInfo fileInfo(videoPath);
  QString editedFilePath = fileInfo.absoluteFilePath().insert(
      fileInfo.absoluteFilePath().length() - fileInfo.completeSuffix().length() - 1, "_edited");

  double frameCount = videoCapture.get(cv::CAP_PROP_FRAME_COUNT);
  double fourcc = videoCapture.get(cv::CAP_PROP_FOURCC);
  double fps = videoCapture.get(cv::CAP_PROP_FPS);
  double width = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
  double height = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);

  cv::VideoWriter videoWriter(editedFilePath.toStdString(), static_cast<int>(fourcc), fps,
                              cv::Size(static_cast<int>(width), static_cast<int>(height)));

  double frameIndex = 0;
  while (!abortCalled)
  {
    cv::Mat frame;
    if (!videoCapture.read(frame))
    {
      emit videoEditingAborted();
      return;
    }

    videoWriter.write(frame);
    emit videoEditingProcessed(frameIndex / frameCount);
    frameIndex++;
  }
}

void VideoThread::abort() { abortCalled = true; }
