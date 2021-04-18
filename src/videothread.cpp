#include "include/videothread.h"
#include "include/helpers.h"

#include <QFileInfo>

VideoThread::VideoThread(QObject* parent) : QThread(parent) {}

VideoThread::~VideoThread()
{
  // stop thread execution in appropriate way
  abortCalled = true;
  quit();
  wait();
}

void VideoThread::setVideoPath(QString value)
{
  const QString fileString("file://");
  if (!isRunning()) // must be set before running the thread
  {
    if (value.startsWith(fileString))
    {
      value = value.remove(0, fileString.length()); // remove file at the beginning of the string
    }
    videoCapture = cv::VideoCapture(value.toStdString()); // create video capture object

    // define path to the new edited path as "$FILE_NAME"_edited."$FILE_EXTENSION"
    QFileInfo fileInfo(value);
    editedVideoPath = fileInfo.absoluteFilePath().insert(
        fileInfo.absoluteFilePath().length() - fileInfo.suffix().length() - 1, "_edited");
  }
}

void VideoThread::setOverlay(const OverlayEffects::Type& type, int changeTimeMiliseconds, double xPercentage,
                             double yPercentage)
{
  if (!isRunning())
  {
    if (auto overlay = OverlayFactory::overlay(type, static_cast<int>(videoCapture.get(cv::CAP_PROP_FPS)),
                                               changeTimeMiliseconds, QPointF(xPercentage, yPercentage)))
    {
      overlays.push_back(overlay); // add overlay which will be burned to the video
    }
  }
}

void VideoThread::abort() { abortCalled = true; }

void VideoThread::run()
{
  if (!videoCapture.isOpened() || overlays.empty())
  {
    emit videoEditingAborted();
    return; // stop thread execution if no overlays or if openning video failed
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
      return; // remove file and stop thread execution if reading video frame fails
    }

    QImage image = Helper::cvMatToQImage(frame);     // convert current frame to the qimage
    paintOverlays(frameIndex, image);                // paint overlays to the image
    videoWriter.write(Helper::qImageToCvMat(image)); // convert qimage back to the opencv frame

    // emit current video editing percentage
    emit videoEditingProcessed(
        static_cast<int>(static_cast<double>(frameIndex) / static_cast<double>(frameCount) * 100.0));
    frameIndex++;

    if (frameIndex == frameCount) // stop editing on last frame
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
  // create new video writer based on the video which is being edited and its properties
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
