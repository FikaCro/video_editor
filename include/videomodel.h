#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H

#include <QAbstractListModel>
#include <QImage>
#include <opencv2/opencv.hpp>
struct Video
{
  bool editable{false};
  QString path;
  QImage thumbnail;
};

class VideoModel : public QAbstractListModel
{
  Q_OBJECT

public:
  enum Roles
  {
    EditableRole = Qt::UserRole,
    PathRole,
    ThumbnailRole
  };

  VideoModel(QObject* parent = nullptr);

  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
  QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
  int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

  Q_INVOKABLE void addVideo(const QString& path);
  void addVideo(const Video& video);

private:
  QList<Video> videos_;
};

#endif // VIDEOMODEL_H
