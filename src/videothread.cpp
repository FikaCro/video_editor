#include "include/videothread.h"
#include "include/helpers.h"

#include <QFileInfo>

VideoThread::VideoThread(QObject* parent) : QThread(parent) {}

VideoThread::~VideoThread()
{
  abortCalled = true;
  quit();
  wait();
}

void VideoThread::setVideoPath(QString value)
{
  value = value.remove("file://");
  videoCapture = cv::VideoCapture(value.toStdString());

  QFileInfo fileInfo(value);
  editedVideoPath = fileInfo.absoluteFilePath().insert(
      fileInfo.absoluteFilePath().length() - fileInfo.suffix().length() - 1, "_edited");
}

void VideoThread::setOverlay(const OverlayEffects::Type& type, int changeTimeMiliseconds, double xPercentage,
                             double yPercentage)
{
  if (auto overlay = OverlayFactory::overlay(type, static_cast<int>(videoCapture.get(cv::CAP_PROP_FPS)),
                                             changeTimeMiliseconds, QPointF(xPercentage, yPercentage)))
  {
    overlays.push_back(overlay);
  }
}

void VideoThread::abort() { abortCalled = true; }

void VideoThread::run()
{
  if (!videoCapture.isOpened() || overlays.empty())
  {
    emit videoEditingAborted();
    return;
  }

  cv::VideoWriter videoWriter = createVideoWriter();

  int frameCount{static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_COUNT))};
  int frameIndex{0};
  while (true)
  {
    cv::Mat frame;
    if (!videoCapture.read(frame) || abortCalled)
    {
      removeFileAndAbort();
      return;
    }

    QImage image = Helper::cvMatToQImage(frame);
    paintOverlays(frameIndex, image);
    videoWriter.write(Helper::qImageToCvMat(image));

    emit videoEditingProcessed(
        static_cast<int>(static_cast<double>(frameIndex) / static_cast<double>(frameCount) * 100.0));
    frameIndex++;

    if (frameIndex == frameCount)
    {
      break;
    }
  }
  videoWriter.release();
  emit videoEditingFinished(editedVideoPath);
}

void VideoThread::removeFileAndAbort()
{
  QFile file(editedVideoPath);
  file.remove();
  emit videoEditingAborted();
}

cv::VideoWriter VideoThread::createVideoWriter() const
{
  double fourcc = videoCapture.get(cv::CAP_PROP_FOURCC);
  double fps = videoCapture.get(cv::CAP_PROP_FPS);
  double width = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
  double height = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);

  return cv::VideoWriter(editedVideoPath.toStdString(), static_cast<int>(fourcc), fps,
                         cv::Size(static_cast<int>(width), static_cast<int>(height)));
}

void VideoThread::paintOverlays(int frameIndex, QImage& image)
{
  for (auto& overlay : overlays)
  {
    overlay->paint(frameIndex, image);
  }
}
