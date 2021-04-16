#include "include/overlayslider.h"

#include <QCheckBox>
#include <QPainter>
#include <QStyleOptionSlider>
#include <QStylePainter>

OverlaySlider::OverlaySlider(int videoFps, int changeTimeMiliseconds, const QPointF& pointPercentage)
    : OverlayBase(videoFps, changeTimeMiliseconds, pointPercentage)
{
}

void OverlaySlider::paint(int frameIndex, QImage& image)
{
  Q_UNUSED(frameIndex)

  QStyleOptionSlider opt;
  opt.minimum = 0;
  opt.maximum = changeFps / 2;
  opt.sliderValue = number + increment * 1;
  opt.sliderPosition = number + increment * 1;
  opt.rect = QRect(QPoint(static_cast<int>(pointPercentage.x() / 100.0 * image.width()),
                          static_cast<int>(pointPercentage.y() / 100.0 * image.height())),
                   QSize(static_cast<int>(image.width() * 0.2), static_cast<int>(image.width() * 0.2)));

  QSlider slider;
  slider.setMinimum(opt.minimum);
  slider.setMaximum(opt.maximum);
  slider.setValue(opt.sliderValue);

  number = slider.value();
  increment *= (number == opt.maximum || number == opt.minimum) ? -1 : 1;

  QPainter p(&image);
  slider.style()->drawComplexControl(QStyle::CC_Slider, &opt, &p, &slider);
}
