#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include "overlayfactory.h"

#include <QThread>

#include <opencv2/opencv.hpp>

/*!
 * \brief The VideoThread class
 *
 * Thread used for video editing (adding deised overlays)
 * Functions setVideoPath and setOverlay must be called before running the thread
 */
class VideoThread : public QThread
{
  Q_OBJECT

public:
  /*!
   * \brief Constructor used for creating the video editing thread
   * \param parent Parent object
   */
  VideoThread(QObject* parent = nullptr);
  /*!
   * \brief Thread destructor quits and terminats thread execution
   */
  ~VideoThread() Q_DECL_OVERRIDE;

  /*!
   * \brief Set the path to the video which is going to be edited
   * \param value Path to the existing video to be edited
   */
  Q_INVOKABLE void setVideoPath(QString value);
  /*!
   * \brief Set the desired overlay which should be added to new created video (must be called before thread execution)
   * \param type Overlay object type, look at the enum Type definition
   * \param changeTimeMiliseconds Desired effect change time in miliseconds
   * \param xPercentage Desired effect x position defined as percentage of the video width
   * \param yPercentage Desired effect y position defined as percentage of the video height
   */
  Q_INVOKABLE void setOverlay(const OverlayEffects::Type& type, int changeTimeMiliseconds, double xPercentage,
                              double yPercentage);
  /*!
   * \brief Abort thread execution and delete the new created file
   */
  Q_INVOKABLE void abort();
  /*!
   * \brief Start thread execution and its logic
   */
  void run() Q_DECL_OVERRIDE;

private:
  /*!
   * \brief Remove created video file and abort thread execution
   */
  void removeFileAndAbort();
  /*!
   * \brief Create OpenCv VideoWriter object based on the existing video
   * \return OpenCv VideoWriter object used for creating new video
   */
  cv::VideoWriter createVideoWriter() const;
  /*!
   * \brief Paint desired video overlays to the new video
   * \param frameIndex Current video frame index
   * \param image Current video frame for overlay painting
   */
  void paintOverlays(int frameIndex, QImage& image);

  /// Path to the new created edited video
  QString editedVideoPath;
  /// OpenCv object used for getting frames of the video which is being edited
  cv::VideoCapture videoCapture;
  /// Property used for thread stopping the thread execution
  bool abortCalled{false};
  /// Desired video overlays to be burned to the new video
  QList<std::shared_ptr<OverlayBase>> overlays;

signals:
  /*!
   * \brief Signal emitted when video editing is aborted (not finished cleanly)
   */
  void videoEditingAborted();
  /*!
   * \brief Signal emitted while video editting carrying the percentage done
   * \param percentage Video editing percentage done
   */
  void videoEditingProcessed(int percentage);
  /*!
   * \brief Signal emitted when video editing finishes cleanly
   * \param path Path to the new created video file
   */
  void videoEditingFinished(const QString& path);
};

#endif // VIDEOTHREAD_H
