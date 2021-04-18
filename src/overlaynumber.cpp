#include "include/overlaynumber.h"

#include <QPainter>

OverlayNumber::OverlayNumber(int videoFps, int changeTimeMiliseconds, const QPointF& pointPercentage)
    : OverlayBase(videoFps, changeTimeMiliseconds, pointPercentage)
{
  number = rand() % 100; // generate first random number
}

void OverlayNumber::paint(int frameIndex, QImage& image)
{
  if (frameIndex % changeFps == 0) // number changes with the desired time rate which is recalculated to the fps rate
  {
    number = rand() % 100;
  }

  // create red pen with the desired width
  QPen pen;
  pen.setWidth(10);
  pen.setColor(Qt::red);

  // create font and set its size
  QFont font;
  font.setPointSize(16);

  // create and set painter's font and pen
  QPainter painter(&image);
  painter.setPen(pen);
  painter.setFont(font);

  // draw number as text, calculating max in order for the number to still be visible when percentages equal zero
  painter.drawText(QPointF(std::max(font.pointSizeF(), pointPercentage.x() / 100.0 * image.width()),
                           std::max(font.pointSizeF(), pointPercentage.y() / 100.0 * image.height())),
                   QString::number(number));
}
