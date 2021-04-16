#include "include/overlayrect.h"

#include <QPainter>

OverlayRect::OverlayRect(int videoFps, int changeTimeMiliseconds, const QPointF& initialPoint)
    : OverlayBase(videoFps, changeTimeMiliseconds, initialPoint)
{
  gradient.setColorAt(0, Qt::white);
  gradient.setColorAt(1, Qt::black);
}

void OverlayRect::paint(int frameIndex, QImage& image)
{
  const double sizeScale{0.1};

  if (frameIndex % changeFps == 0)
  {
    point = QPointF(static_cast<double>(rand() % 100) / 100.0 * image.width() * (1. - sizeScale),
                    static_cast<double>(rand() % 100) / 100.0 * image.height() * (1. - sizeScale));

    const double hueRandom = static_cast<double>(rand() % 100) / 100.0;
    const double lightnessRandom = static_cast<double>(rand() % 100) / 100.0;
    gradient = QLinearGradient(point, +point + QPointF(image.width() * sizeScale, image.height() * sizeScale));
    gradient.setColorAt(0, QColor::fromHslF(hueRandom, 1., lightnessRandom, 1.));
    gradient.setColorAt(1, QColor::fromHslF(1.0 - hueRandom, 1., 1 - lightnessRandom, 1.));
  }

  QPainter painter(&image);
  painter.fillRect(QRectF(point, QSizeF(image.width() * sizeScale, image.height() * sizeScale)), gradient);
}
