#include "include/overlayrect.h"

#include <QPainter>

OverlayRect::OverlayRect(int videoFps, int changeTimeMiliseconds, const QPointF& pointPercentage)
    : OverlayBase(videoFps, changeTimeMiliseconds, pointPercentage)
{
  gradient.setColorAt(0, Qt::white);
  gradient.setColorAt(1, Qt::black);
}

void OverlayRect::paint(int frameIndex, QImage& image)
{
  const double sizeScale{0.1};

  QPointF topLeft(pointPercentage.x() / 100.0 * image.width(), pointPercentage.y() / 100.0 * image.height());
  QPointF size(image.width() * sizeScale, image.height() * sizeScale);

  if (frameIndex % changeFps == 0)
  {
    pointPercentage = QPointF(static_cast<double>(rand() % 100) * (1. - sizeScale),
                              static_cast<double>(rand() % 100) * (1. - sizeScale));

    topLeft = QPointF(pointPercentage.x() / 100.0 * image.width(), pointPercentage.y() / 100.0 * image.height());
    size = QPointF(image.width() * sizeScale, image.height() * sizeScale);

    const double hueRandom = static_cast<double>(rand() % 100) / 100.0;
    const double lightnessRandom = static_cast<double>(rand() % 100) / 100.0;
    gradient = QLinearGradient(topLeft, topLeft + size);
    gradient.setColorAt(0, QColor::fromHslF(hueRandom, 1., lightnessRandom, 1.));
    gradient.setColorAt(1, QColor::fromHslF(1.0 - hueRandom, 1., 1 - lightnessRandom, 1.));
  }

  QPainter painter(&image);
  painter.fillRect(QRectF(topLeft, topLeft + size), gradient);
}
