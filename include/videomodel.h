#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H

#include <QAbstractListModel>
#include <QImage>
#include <opencv2/opencv.hpp>
struct Video
{
  QString path;
  QImage thumbnail;
};

class VideoModel : public QAbstractListModel
{
  Q_OBJECT

  Q_PROPERTY(bool editable READ getEditable WRITE setEditable NOTIFY editableChanged)

public:
  enum Roles
  {
    PathRole = Qt::UserRole,
    ThumbnailRole
  };

  VideoModel(QObject* parent = nullptr);

  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
  QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
  int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

  bool getEditable() const;
  void setEditable(bool value);

  Q_INVOKABLE void addVideo(const QString& path);
  void addVideo(const Video& video);

private:
  QList<Video> videos_;
  bool editable{false};

signals:
  void editableChanged(bool value);
};

#endif // VIDEOMODEL_H
