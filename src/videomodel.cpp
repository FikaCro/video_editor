#include "include/videomodel.h"
#include "include/helpers.h"

#include <QFile>

VideoModel::VideoModel(QObject* parent) : QAbstractListModel(parent) {}

QVariant VideoModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }
  if (index.row() < 0 || index.row() >= videos.size())
  {
    return QVariant();
  }
  switch (role)
  {
  case PathRole:
    if (isValid(index.row()))
    {
      return QVariant(videos.at(index.row()).path);
    }
    const_cast<VideoModel*>(this)->removeVideo(index.row());
    return QVariant();
  case ThumbnailRole:
    return QVariant(videos.at(index.row()).thumbnail);
  default:
    return QVariant();
  }
}

bool VideoModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  Q_UNUSED(index)
  Q_UNUSED(value)
  Q_UNUSED(role)
  return false;
}

QHash<int, QByteArray> VideoModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[PathRole] = "path";
  roles[ThumbnailRole] = "thumbnail";
  return roles;
}

int VideoModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent)
  return videos.size();
}

bool VideoModel::getEditable() const { return editable; }

void VideoModel::setEditable(bool value) { emit editableChanged(editable = value); }

QString VideoModel::getPath(int index) const
{
  if (index < 0 || index >= videos.size())
  {
    return QString();
  }
  return videos[index].path;
}

QImage VideoModel::getThumbnail(int index) const
{
  if (index < 0 || index >= videos.size())
  {
    return QImage();
  }
  return videos[index].thumbnail;
}

void VideoModel::addVideo(QString path)
{
  Video video;
  if (!path.startsWith("file://"))
  {
    path = path.insert(0, "file://");
  }
  video.path = path;
  video.thumbnail = Helper::videoThumbnail(video.path);

  addVideo(video);
}

void VideoModel::addVideo(const Video& video)
{
  beginInsertRows(QModelIndex(), videos.size(), videos.size());

  videos.push_back(std::move(video));

  endInsertRows();
  emit dataChanged(QModelIndex(), QModelIndex());
}

bool VideoModel::isValid(int index) const
{
  auto path = videos[index].path;
  return QFile::exists(path.remove("file://"));
}

void VideoModel::removeVideo(int index)
{
  beginRemoveRows(QModelIndex(), index, index);

  videos.removeAt(index);

  endRemoveRows();

  emit dataChanged(QModelIndex(), QModelIndex());
}
