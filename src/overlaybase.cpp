#include "include/overlaybase.h"

OverlayBase::OverlayBase(int videoFps, int changeTimeMiliseconds, const QPointF& initialPoint) : point(initialPoint)
{
  changeFps = static_cast<int>(static_cast<double>(videoFps * changeTimeMiliseconds) / 1000.0);
}

OverlayBase::~OverlayBase() {}
