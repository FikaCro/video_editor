#ifndef OVERLAYBASE_H
#define OVERLAYBASE_H

#include <QImage>

class OverlayBase
{
public:
  OverlayBase(int videoFps, int changeTimeMiliseconds, const QPointF& pointPercentage);
  virtual ~OverlayBase();

  virtual void paint(int frameIndex, QImage& image) = 0;

protected:
  int changeFps{};
  QPointF pointPercentage;
};

#endif // OVERLAYBASE_H
