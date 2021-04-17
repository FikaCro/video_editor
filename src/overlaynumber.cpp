#include "include/overlaynumber.h"

#include <QPainter>

OverlayNumber::OverlayNumber(int videoFps, int changeTimeMiliseconds, const QPointF& pointPercentage)
    : OverlayBase(videoFps, changeTimeMiliseconds, pointPercentage)
{
  number = rand() % 100;
}

void OverlayNumber::paint(int frameIndex, QImage& image)
{
  if (frameIndex % changeFps == 0)
  {
    number = rand() % 100;
  }

  QPen pen;
  pen.setWidth(10);
  pen.setColor(Qt::red);

  QFont font;
  font.setPointSize(16);

  QPainter painter(&image);
  painter.setPen(pen);
  painter.setFont(font);

  painter.drawText(QPointF(std::max(font.pointSizeF(), pointPercentage.x() / 100.0 * image.width()),
                           std::max(font.pointSizeF(), pointPercentage.y() / 100.0 * image.height())),
                   QString::number(number));
}
