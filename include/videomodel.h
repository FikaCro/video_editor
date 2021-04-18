#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H

#include <QAbstractListModel>
#include <QImage>

/*!
 * \brief The Video structure
 *
 * Structure used for storing the video path and it's thumbnail
 */
struct Video
{
  QString path;
  QImage thumbnail;
};

/*!
 * \brief The VideoModel class
 *
 * Video model used for loading, playing or adding the videos
 * The model itself can be editable which means that effects can be applied to videos
 */
class VideoModel : public QAbstractListModel
{
  Q_OBJECT

  // bool editable property can be set and read from the Qml
  Q_PROPERTY(bool editable READ getEditable WRITE setEditable NOTIFY editableChanged)

public:
  /*!
   * \brief The Roles enum
   *
   * Supported roles used for data reading: video path and video thumbnail image
   */
  enum Roles
  {
    PathRole = Qt::UserRole,
    ThumbnailRole
  };

  /*!
   * \brief Constructor used for creating the video model
   * \param parent Parent object
   */
  VideoModel(QObject* parent = nullptr);

  /*!
   * \brief Read video data based on the provided index and the role
   * \param index Video index for getting the data
   * \param role Desired video property (look at Roles enum)
   * \return Data defining the desired video property or invalid value if index or role is invalid or if video removed
   */
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  /*!
   * \brief Data changing is not allowed, this function does nothing
   * \param index Irrelevant
   * \param value Irrelevant
   * \param role Irrelevant
   * \return Always false
   */
  bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
  /*!
   * \brief Allowed property values and their names for the view representation
   * \return Property carriers and their names (look at Roles enum)
   */
  QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
  /*!
   * \brief Number of videos in the model
   * \param parent Irrelevant (model is 1D)
   * \return Number of videos in the model
   */
  int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

  /*!
   * \brief Read current editable property value (video editing allowed or forbidden)
   * \return Editable property value
   */
  bool getEditable() const;
  /*!
   * \brief Update editable property value (allow or forbid video editing)
   * \param value Desired editable property value
   */
  void setEditable(bool value);
  /*!
   * \brief Read desired path to the video file
   * \param index Video index
   * \return Path to the video or empty string if invalid index
   */
  Q_INVOKABLE QString getPath(int index) const;
  /*!
   * \brief Read thumbnail image of the video file
   * \param index Video index
   * \return Thumbnail image of the video or null image if invalid index
   */
  Q_INVOKABLE QImage getThumbnail(int index) const;
  /*!
   * \brief Add new video to the model at the passed file path
   * \param path Path to the video file
   */
  Q_INVOKABLE void addVideo(QString path);

private:
  /*!
   * \brief Add video to the model
   * \param video Video to be added (using std::move)
   */
  void addVideo(const Video& video);
  /*!
   * \brief Check whether the video at the current index still exists
   * \param index Video index used for validity check
   * \return Video path validity (false if video doesn't exist)
   */
  bool isValid(int index) const;
  /*!
   * \brief Remove video at the index from the model
   * \param index Video index used for video removing
   */
  void removeVideo(int index);

  /// Currently loaded videos
  QList<Video> videos;
  /// Defines wether videos are editable or not
  bool editable{false};

signals:
  /*!
   * \brief Signal emitted when editable property changes
   * \param value Current editable property value
   */
  void editableChanged(bool value);
};

#endif // VIDEOMODEL_H
