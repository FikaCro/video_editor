#ifndef OVERLAYFACTORY_H
#define OVERLAYFACTORY_H

#include "overlaybase.h"

#include <QPointF>

#include <memory>

class OverlayFactory
{
public:
  static std::shared_ptr<OverlayBase> overlay(const QString& type, int videoFps, int changeTimeMiliseconds,
                                              const QPointF& initialPoint);
};

#endif // OVERLAYFACTORY_H
