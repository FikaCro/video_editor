#ifndef OVERLAYSLIDER_H
#define OVERLAYSLIDER_H

#include "overlaybase.h"

class OverlaySlider : public OverlayBase
{
public:
  OverlaySlider(int videoFps, int changeTimeMiliseconds, const QPointF& initialPoint);

  void paint(int frameIndex, QImage& image) Q_DECL_OVERRIDE;

private:
  int number{0};
  int increment{1};
};

#endif // OVERLAYSLIDER_H
