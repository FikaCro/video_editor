#include "include/overlayfactory.h"
#include "include/overlaynumber.h"
#include "include/overlayrect.h"
#include "include/overlayslider.h"

std::shared_ptr<OverlayBase> OverlayFactory::overlay(const QString& type, int videoFps, int changeTimeMiliseconds,
                                                     const QPointF& pointPercentage)
{
  if (type == "numberOverlay")
  {
    return std::make_shared<OverlayNumber>(videoFps, changeTimeMiliseconds, pointPercentage);
  }
  else if (type == "rectangleOverlay")
  {
    return std::make_shared<OverlayRect>(videoFps, changeTimeMiliseconds, pointPercentage);
  }
  else if (type == "sliderOverlay")
  {
    return std::make_shared<OverlaySlider>(videoFps, changeTimeMiliseconds, pointPercentage);
  }
  return nullptr;
}
