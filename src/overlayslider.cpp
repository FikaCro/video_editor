#include "include/overlayslider.h"

#include <QCheckBox>
#include <QPainter>
#include <QStyleOptionSlider>
#include <QStylePainter>

OverlaySlider::OverlaySlider(int videoFps, int changeTimeMiliseconds, const QPointF& initialPoint)
    : OverlayBase(videoFps, changeTimeMiliseconds, initialPoint)
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
  opt.rect = QRect(QPoint(static_cast<int>(point.x()), static_cast<int>(point.y())),
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
