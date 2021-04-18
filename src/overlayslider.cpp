#include "include/overlayslider.h"

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

  // defined slider size scale compared to the image width and height
  const double rectDimensionScale{0.2};

  // create slider style object
  QStyleOptionSlider opt;
  opt.minimum = 0;
  opt.maximum = changeFps / 2; // maximum value as hald of the change fps so the min is reached with the desired rate
  opt.sliderValue = number + increment; // value and position increments each frame
  opt.sliderPosition = number + increment;
  // calculate slider position but taking account for it to stay inside image rectangle
  opt.rect =
      QRect(QPoint(static_cast<int>(std::min(pointPercentage.x() / 100., 1. - rectDimensionScale) * image.width()),
                   static_cast<int>(std::min(pointPercentage.y() / 100., 1. - rectDimensionScale) * image.height())),
            QSize(static_cast<int>(image.width() * rectDimensionScale),
                  static_cast<int>(image.width() * rectDimensionScale)));

  // create slider object and update its min, max and current value
  QSlider slider;
  slider.setMinimum(opt.minimum);
  slider.setMaximum(opt.maximum);
  slider.setValue(opt.sliderValue);

  // update last slider position and increment on reacing minimum / maximum value
  number = slider.value();
  increment *= (number == opt.maximum || number == opt.minimum) ? -1 : 1;

  // draw slider to the image
  QPainter p(&image);
  slider.style()->drawComplexControl(QStyle::CC_Slider, &opt, &p, &slider);
}
