#ifndef OVERLAYNUMBER_H
#define OVERLAYNUMBER_H

#include "overlaybase.h"

class OverlayNumber : public OverlayBase
{
public:
  OverlayNumber(int videoFps, int changeTimeMiliseconds, const QPointF& pointPercentage);

  void paint(int frameIndex, QImage& image) Q_DECL_OVERRIDE;

private:
  int number{};
};

#endif // OVERLAYNUMBER_H
