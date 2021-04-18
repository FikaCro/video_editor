#ifndef OVERLAYNUMBER_H
#define OVERLAYNUMBER_H

#include "overlaybase.h"

/*!
 * \brief The OverlayNumber class
 *
 * The number overlay class used for painting the randomly generated number at the desired position
 * Number changes with the desired change time but the position stays the same
 */
class OverlayNumber : public OverlayBase
{
public:
  /*!
   * \brief Contructor for creating number overlay object
   * \param videoFps Frames per second rate of the video
   * \param changeTimeMiliseconds Desired effect change time in miliseconds
   * \param pointPercentage Desired effect position defined as percentage of the video width and height
   */
  OverlayNumber(int videoFps, int changeTimeMiliseconds, const QPointF& pointPercentage);

  /*!
   * \brief Method used for painting the number effect to the image
   * \param frameIndex Current video frame index
   * \param image Image for applying the effect
   */
  void paint(int frameIndex, QImage& image) Q_DECL_OVERRIDE;

private:
  /// Current number to be painted
  int number{};
};

#endif // OVERLAYNUMBER_H
