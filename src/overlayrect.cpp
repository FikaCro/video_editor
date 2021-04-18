#include "include/overlayrect.h"

#include <QPainter>

OverlayRect::OverlayRect(int videoFps, int changeTimeMiliseconds, const QPointF& pointPercentage)
    : OverlayBase(videoFps, changeTimeMiliseconds, pointPercentage)
{
  // initial gradient color white and black
  gradient.setColorAt(0, Qt::white);
  gradient.setColorAt(1, Qt::black);
}

void OverlayRect::paint(int frameIndex, QImage& image)
{
  // defined rectangle size scale compared to the image width and height
  const double sizeScale{0.1};

  // calculate rectangle top left corner and its size
  QPointF topLeft(pointPercentage.x() / 100.0 * image.width() * (1. - sizeScale),
                  pointPercentage.y() / 100.0 * image.height() * (1. - sizeScale));
  QPointF size(image.width() * sizeScale, image.height() * sizeScale);

  if (frameIndex % changeFps == 0) // rectangle changes with the desired time rate which is recalculated to the fps rate
  {
    // generate random positions for the gradient color selection
    const double startPos = static_cast<double>(rand() % 100) / 100.0;
    const double endPos = static_cast<double>(rand() % 100) / 100.0;
    // generate random hue and lightness values for the gradient color selection
    const double hueRandom = static_cast<double>(rand() % 100) / 100.0;
    const double lightnessRandom = static_cast<double>(rand() % 100) / 100.0;
    // apply new gradient colors for the rectangle painting, colors at the opposite parts of spectre
    gradient = QLinearGradient(topLeft, topLeft + size);
    gradient.setColorAt(startPos, QColor::fromHslF(hueRandom, 1., lightnessRandom, 1.));
    gradient.setColorAt(endPos, QColor::fromHslF(1.0 - hueRandom, 1., 1 - lightnessRandom, 1.));
  }

  // paint the rectangle at the calculated position with the calculated gradient
  QPainter painter(&image);
  painter.fillRect(QRectF(topLeft, topLeft + size), gradient);
}
