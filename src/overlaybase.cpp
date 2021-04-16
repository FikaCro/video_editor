#include "include/overlaybase.h"

OverlayBase::OverlayBase(int videoFps, int changeTimeMiliseconds, const QPointF& pointPercentage)
    : pointPercentage(pointPercentage)
{
  changeFps = static_cast<int>(static_cast<double>(videoFps * changeTimeMiliseconds) / 1000.0);
}

OverlayBase::~OverlayBase() {}
