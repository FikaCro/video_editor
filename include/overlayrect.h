#ifndef OVERLAYRECT_H
#define OVERLAYRECT_H

#include "overlaybase.h"

#include <QGradient>

class OverlayRect : public OverlayBase
{
public:
  OverlayRect(int videoFps, int changeTimeMiliseconds, const QPointF& initialPoint);

  void paint(int frameIndex, QImage& image) Q_DECL_OVERRIDE;

private:
  QLinearGradient gradient;
};

#endif // OVERLAYRECT_H
