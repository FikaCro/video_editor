#include "include/overlaynumber.h"

#include <QPainter>

OverlayNumber::OverlayNumber(int videoFps, int changeTimeMiliseconds, const QPointF& initialPoint)
    : OverlayBase(videoFps, changeTimeMiliseconds, initialPoint)
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

  painter.drawText(point, QString::number(number));
}
