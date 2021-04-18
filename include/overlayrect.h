#ifndef OVERLAYRECT_H
#define OVERLAYRECT_H

#include "overlaybase.h"

#include <QGradient>

/*!
 * \brief The OverlayRect class
 *
 * The rectangle overlay class used for painting the rectangle using gradient with random colors and positions
 * Gradient positions and colors change with the desired change time
 */
class OverlayRect : public OverlayBase
{
public:
  /*!
   * \brief Contructor for creating rectangle overlay object
   * \param videoFps Frames per second rate of the video
   * \param changeTimeMiliseconds Desired effect change time in miliseconds
   * \param pointPercentage Desired effect position defined as percentage of the video width and height
   */
  OverlayRect(int videoFps, int changeTimeMiliseconds, const QPointF& pointPercentage);

  /*!
   * \brief Method used for painting the rectangle effect to the image
   * \param frameIndex Current video frame index
   * \param image Image for applying the effect
   */
  void paint(int frameIndex, QImage& image) Q_DECL_OVERRIDE;

private:
  /// Current gradient color used for painting rectangle
  QLinearGradient gradient;
};

#endif // OVERLAYRECT_H
