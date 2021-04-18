#ifndef THUMBNAILITEM_H
#define THUMBNAILITEM_H

#include <QImage>
#include <QQuickPaintedItem>

/*!
 * \brief The ThumbnailItem class
 *
 * Object used for showing the thumbnail image in the Qml based frontend
 */
class ThumbnailItem : public QQuickPaintedItem
{
  Q_OBJECT
  // QImage thumbnail property which can be set and read from the Qml
  Q_PROPERTY(QImage thumbnail READ getThumbnail WRITE setThumbnail NOTIFY thumbnailChanged)
  QML_ELEMENT

public:
  /*!
   * \brief Constructor used for creating the object
   * \param parent Parent object
   */
  ThumbnailItem(QQuickItem* parent = nullptr);

  /*!
   * \brief Update current thumbnail
   * \param thumbnail Image to be set as a new thumbnail
   */
  void setThumbnail(const QImage& thumbnail);
  /*!
   * \brief Read current shown thumbnail
   * \return Current thumbnail image
   */
  QImage getThumbnail() const;

  /*!
   * \brief Paint current thumbnail image inside the object's bounding rectangle
   * \param painter Pointer to the QPainter object used for thumbnail painting
   */
  void paint(QPainter* painter);

private:
  /// Thumbnail image to be painted
  QImage thumbnail;

signals:
  /*!
   * \brief Signal emmited on the thumbnail change
   * \param thumbnail Current thumbnail
   */
  void thumbnailChanged(const QImage& thumbnail);
};

#endif // THUMBNAILITEM_H
