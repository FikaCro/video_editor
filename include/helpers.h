#ifndef HELPERS_H
#define HELPERS_H

#include <QImage>
#include <opencv2/opencv.hpp>

namespace Helper
{
inline QImage cvMatToQImage(const cv::Mat& mat)
{
  return QImage(static_cast<uchar*>(mat.data), mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_BGR888);
}

inline cv::Mat qImageToCvMat(const QImage& image)
{

  return cv::Mat(image.height(), image.width(), CV_8UC3, (uchar*)image.bits(),
                 static_cast<ulong>(image.bytesPerLine()));
}

inline QImage videoThumbnail(const QString& videoPath)
{
  cv::VideoCapture videoCapture(videoPath.toStdString());
  if (!videoCapture.isOpened())
  {
    return QImage();
  }
  videoCapture.set(cv::CAP_PROP_POS_FRAMES, videoCapture.get(cv::CAP_PROP_FRAME_COUNT) / 2);
  cv::Mat frame;
  if (!videoCapture.read(frame))
  {
    return QImage();
  }
  return cvMatToQImage(frame);
}

} // namespace Helper

#endif // HELPERS_H
