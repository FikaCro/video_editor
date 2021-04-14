#include "include/videomodel.h"

VideoModel::VideoModel(QObject* parent) : QAbstractListModel(parent) {}

QVariant VideoModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }
  if (index.row() < 0 || index.row() >= videos_.size())
  {
    return QVariant();
  }
  switch (role)
  {
  case PathRole:
    return QVariant(videos_.at(index.row()).path);
  case ThumbnailRole:
    return QVariant(videos_.at(index.row()).thumbnail);
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
  return videos_.size();
}

bool VideoModel::getEditable() const { return editable; }

void VideoModel::setEditable(bool value) { emit editableChanged(editable = value); }

void VideoModel::addVideo(const QString& path)
{
  Video video;
  video.path = path;
  // TODO: add thumbnail setup
  addVideo(video);
}

void VideoModel::addVideo(const Video& video)
{
  beginInsertRows(QModelIndex(), videos_.size(), videos_.size());

  videos_.push_back(std::move(video));

  endInsertRows();
  emit dataChanged(QModelIndex(), QModelIndex());
}
