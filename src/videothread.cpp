#include "include/videothread.h"

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
      fileInfo.absoluteFilePath().length() - fileInfo.completeSuffix().length() - 1, "_edited");
}

void VideoThread::setOverlay(const OverlayEffects::Type& type, int changeTimeMiliseconds, double xPercentage,
                             double yPercentage)
{
  overlays.push_back(OverlayFactory::overlay(type, static_cast<int>(videoCapture.get(cv::CAP_PROP_FPS)),
                                             changeTimeMiliseconds, QPointF(xPercentage, yPercentage)));
}

void VideoThread::run()
{
  if (!videoCapture.isOpened())
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

    QImage image = cvMatToQImage(frame);
    paintOverlays(frameIndex, image);
    videoWriter.write(qImageToCvMat(image));

    emit videoEditingProcessed(static_cast<double>(frameIndex) / static_cast<double>(frameCount));
    frameIndex++;

    if (frameIndex == frameCount)
    {
      break;
    }
  }

  emit videoEditingFinished(editedVideoPath);
}

void VideoThread::abort() { abortCalled = true; }

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

QImage VideoThread::cvMatToQImage(const cv::Mat& mat) const
{
  cv::Mat tmp;
  cv::cvtColor(mat, tmp, CV_BGR2RGB);
  return QImage(static_cast<uchar*>(mat.data), mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888);
}

cv::Mat VideoThread::qImageToCvMat(const QImage& image) const
{
  cv::Mat res(image.height(), image.width(), CV_8UC3, (uchar*)image.bits(), static_cast<ulong>(image.bytesPerLine()));
  cv::cvtColor(res, res, CV_BGR2RGB);
  return res;
}

void VideoThread::paintOverlays(int frameIndex, QImage& image)
{
  for (auto& overlay : overlays)
  {
    overlay->paint(frameIndex, image);
  }
}
