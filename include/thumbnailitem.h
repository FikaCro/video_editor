#ifndef THUMBNAILITEM_H
#define THUMBNAILITEM_H

#include <QQuickPaintedItem>
#include <QImage>

class ThumbnailItem : public QQuickPaintedItem
{
  Q_OBJECT
  Q_PROPERTY(QImage thumbnail READ getThumbnail WRITE setThumbnail NOTIFY thumbnailChanged)
  QML_ELEMENT

public:
  ThumbnailItem(QQuickItem* parent = nullptr);

  void setThumbnail(const QImage& thumbnail);
  QImage getThumbnail() const;

  void paint(QPainter* painter);

private:
  QImage thumbnail;

signals:
  void thumbnailChanged(const QImage& thumbnail);
};

#endif // THUMBNAILITEM_H
