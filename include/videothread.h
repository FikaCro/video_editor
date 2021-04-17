#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include "overlaybase.h"
#include "overlayfactory.h"

#include <QThread>

#include <opencv2/opencv.hpp>

class VideoThread : public QThread
{
  Q_OBJECT

public:
  VideoThread(QObject* parent = nullptr);
  ~VideoThread() Q_DECL_OVERRIDE;

  Q_INVOKABLE void setVideoPath(QString value);
  Q_INVOKABLE void setOverlay(const OverlayEffects::Type& type, int changeTimeMiliseconds, double xPercentage,
                              double yPercentage);
  Q_INVOKABLE void abort();
  void run() Q_DECL_OVERRIDE;

private:
  void removeFileAndAbort();
  cv::VideoWriter createVideoWriter() const;
  void paintOverlays(int frameIndex, QImage& image);

  QString editedVideoPath;
  cv::VideoCapture videoCapture;
  bool abortCalled{false};
  QList<std::shared_ptr<OverlayBase>> overlays;

signals:
  void videoEditingAborted();
  void videoEditingProcessed(int percentage);
  void videoEditingFinished(const QString& path);
};

#endif // VIDEOTHREAD_H
