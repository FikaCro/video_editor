#ifndef OVERLAYFACTORY_H
#define OVERLAYFACTORY_H

#include "overlaybase.h"

#include <QPointF>

#include <memory>

namespace OverlayEffects
{
Q_NAMESPACE
/*!
 * \brief The Overlay type enum
 *
 * Currently supports Number, Rectangle and Slider, used for creating the Overlay object
 */
enum Type
{
  Number = 0,
  Rectangle,
  Slider
};
Q_ENUMS(Type)
} // namespace OverlayEffects

/*!
 * \brief The OverlayFactory class
 *
 * Class used for creating the Overlay object based on the provided Overlay type
 */
class OverlayFactory
{
public:
  /*!
   * \brief Create the Overlay object based on the provided Overlay type
   * \param type Overlay object type, look at the enum Type definition
   * \param videoFps Frames per second rate of the video
   * \param changeTimeMiliseconds Desired effect change time in miliseconds
   * \param pointPercentage Desired effect position defined as percentage of the video width and height
   * \return Shared pointer to the created Overlay object or nullptr in case of undefined overlay type argument
   */
  static std::shared_ptr<OverlayBase> overlay(const OverlayEffects::Type& type, int videoFps, int changeTimeMiliseconds,
                                              const QPointF& pointPercentage);
};

Q_DECLARE_METATYPE(OverlayEffects::Type)

#endif // OVERLAYFACTORY_H
