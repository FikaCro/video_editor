#ifndef OVERLAYBASE_H
#define OVERLAYBASE_H

#include <QImage>

/*!
 * \brief The OverlayBase class
 *
 * Abstract overlay class used for painting desired effect to the video frame
 * Paint method must be implemented in a desired way
 * Holds changeFps parameter for random effect changes
 */
class OverlayBase
{
public:
  /*!
   * \brief Contructor for creating Overlay object
   * \param videoFps Frames per second rate of the video
   * \param changeTimeMiliseconds Desired effect change time in miliseconds
   * \param pointPercentage Desired effect position defined as percentage of the video width and height
   */
  OverlayBase(int videoFps, int changeTimeMiliseconds, const QPointF& pointPercentage);
  /*!
   * \brief Base destructor does nothing
   */
  virtual ~OverlayBase();

  /*!
   * \brief Abstract method used for painting effect to the image
   * \param frameIndex Current video frame index
   * \param image Image for applying the effect
   */
  virtual void paint(int frameIndex, QImage& image) = 0;

protected:
  /// Value defining when to change some property based on video fps and desired change time
  int changeFps{};
  /// Position defined as percentage compared to the video width and height
  QPointF pointPercentage;
};

#endif // OVERLAYBASE_H
