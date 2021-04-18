#ifndef HELPERS_H
#define HELPERS_H

#include <QImage>
#include <opencv2/opencv.hpp>

namespace Helper
{
/*!
 * \brief Convert OpenCv Mat image to Qt QImage
 * \param mat OpenCv image to be converted
 * \return Converted QImage
 */
inline QImage cvMatToQImage(const cv::Mat& mat)
{
  return QImage(static_cast<uchar*>(mat.data), mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_BGR888);
}

/*!
 * \brief Convert Qt QImage to OpenCv Mat image
 * \param image Qt image to be converted
 * \return Converted OpenCv Mat image
 */
inline cv::Mat qImageToCvMat(const QImage& image)
{

  return cv::Mat(image.height(), image.width(), CV_8UC3, (uchar*)image.bits(),
                 static_cast<ulong>(image.bytesPerLine()));
}

/*!
 * \brief Create video thumbnail image based on provided video path
 * \param videoPath Path to video file, must stard with "file://"
 * \return Video thumbnail image or null image if any error occured
 */
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
