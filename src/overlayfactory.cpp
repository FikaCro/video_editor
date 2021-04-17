#include "include/overlayfactory.h"
#include "include/overlaynumber.h"
#include "include/overlayrect.h"
#include "include/overlayslider.h"

std::shared_ptr<OverlayBase> OverlayFactory::overlay(const OverlayEffects::Type& type, int videoFps,
                                                     int changeTimeMiliseconds, const QPointF& pointPercentage)
{
  using namespace OverlayEffects;
  switch (type)
  {
  case Number:
    return std::make_shared<OverlayNumber>(videoFps, changeTimeMiliseconds, pointPercentage);
  case Rectangle:
    return std::make_shared<OverlayRect>(videoFps, changeTimeMiliseconds, pointPercentage);
  case Slider:
    return std::make_shared<OverlaySlider>(videoFps, changeTimeMiliseconds, pointPercentage);
  }
  return nullptr;
}
