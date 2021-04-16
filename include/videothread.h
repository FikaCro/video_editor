#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <QThread>

class VideoThread : public QThread
{
  Q_OBJECT

public:
  VideoThread(QObject* parent = nullptr);

  void run() Q_DECL_OVERRIDE;
  void abort();

private:
  QString videoPath;
  bool abortCalled{false};

signals:
  void videoEditingAborted();
  void videoEditingProcessed(double value);
  void videoEditingFinished(const QString& path);
};


#endif // VIDEOTHREAD_H
