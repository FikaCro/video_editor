#ifndef OVERLAYFACTORY_H
#define OVERLAYFACTORY_H

#include "overlaybase.h"

#include <QPointF>

#include <memory>

namespace OverlayEffects
{
Q_NAMESPACE
enum Type
{
  Number = 0,
  Rectangle,
  Slider
};
Q_ENUMS(Type)
} // namespace OverlayEffects

class OverlayFactory
{
public:
  static std::shared_ptr<OverlayBase> overlay(const OverlayEffects::Type& type, int videoFps, int changeTimeMiliseconds,
                                              const QPointF& pointPercentage);
};

Q_DECLARE_METATYPE(OverlayEffects::Type)

#endif // OVERLAYFACTORY_H
