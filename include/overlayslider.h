#ifndef OVERLAYSLIDER_H
#define OVERLAYSLIDER_H

#include "overlaybase.h"

/*!
 * \brief The OverlaySlider class
 *
 * The slider overlay class used for painting the changing value slider at the desired position
 * Slider value changes with the desired change time but the position stays the same
 */
class OverlaySlider : public OverlayBase
{
public:
  /*!
   * \brief Contructor for creating slider overlay object
   * \param videoFps Frames per second rate of the video
   * \param changeTimeMiliseconds Desired effect change time in miliseconds
   * \param pointPercentage Desired effect position defined as percentage of the video width and height
   */
  OverlaySlider(int videoFps, int changeTimeMiliseconds, const QPointF& pointPercentage);

  /*!
   * \brief Method used for painting the slider effect to the image
   * \param frameIndex Current video frame index
   * \param image Image for applying the effect
   */
  void paint(int frameIndex, QImage& image) Q_DECL_OVERRIDE;

private:
  /// Last slider position value
  int number{0};
  /// Current slider increment, can be 1 or -1
  int increment{1};
};

#endif // OVERLAYSLIDER_H
