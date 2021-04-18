#include "include/videomodel.h"
#include "include/helpers.h"

#include <QFile>

VideoModel::VideoModel(QObject* parent) : QAbstractListModel(parent) {}

QVariant VideoModel::data(const QModelIndex& index, int role) const
{
  // return undefined data if invalid index
  if (!index.isValid() || index.row() < 0 || index.row() >= videos.size())
  {
    return QVariant();
  }
  switch (role)
  {
  case PathRole:
    if (isValid(index.row()))
    {
      return QVariant(videos.at(index.row()).path); // return video path if the video exists
    }
    const_cast<VideoModel*>(this)->removeVideo(index.row()); // remove video from the model if path invalid
    return QVariant(); // return undefined data if video does not exist at the path
  case ThumbnailRole:
    return QVariant(videos.at(index.row()).thumbnail); // return video thumbnail
  default:
    return QVariant(); // return undefined data if invalid role
  }
}

bool VideoModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  Q_UNUSED(index)
  Q_UNUSED(value)
  Q_UNUSED(role)
  return false; // not supported
}

QHash<int, QByteArray> VideoModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[PathRole] = "path";
  roles[ThumbnailRole] = "thumbnail";
  return roles; // supported properties
}

int VideoModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent)
  return videos.size(); // model size
}

bool VideoModel::getEditable() const { return editable; }

void VideoModel::setEditable(bool value) { emit editableChanged(editable = value); }

QString VideoModel::getPath(int index) const
{
  if (index < 0 || index >= videos.size())
  {
    return QString();
  }
  return videos[index].path; // path to the video or empty string if index invalid
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
  // create video object with its path and thumbnail and save it to the model
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
  // add video to the model and call functions used for updating the view
  beginInsertRows(QModelIndex(), videos.size(), videos.size());

  videos.push_back(std::move(video));

  endInsertRows();
  emit dataChanged(QModelIndex(), QModelIndex());
}

bool VideoModel::isValid(int index) const
{
  // check video validity (file existence)
  auto path = videos[index].path;
  return QFile::exists(path.remove("file://"));
}

void VideoModel::removeVideo(int index)
{
  if (index < 0 || index >= videos.size())
  {
    return;
  }
  // remove video from the model if its validity has changed and call functions used for updating the view
  beginRemoveRows(QModelIndex(), index, index);

  videos.removeAt(index);

  endRemoveRows();

  emit dataChanged(QModelIndex(), QModelIndex());
}
