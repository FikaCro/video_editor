import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtMultimedia 5.12

import ThumbnailItem 1.0
import VideoModel 1.0
import VideoThread 1.0

Item {
    id: root

    property variant model: model

    signal backTriggered()
    signal loadVideoTriggered()
    signal videoEditingFinished(string path)

    PathView {
        id: pathView

        anchors.fill: parent
        anchors.topMargin: buttonBack.y + buttonBack.height / 2

        pathItemCount: 9
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        highlightRangeMode: PathView.StrictlyEnforceRange

        model: root.model

        delegate: Rectangle {
            height: parent.height * 0.5
            width: parent.width * 0.25

            color: "transparent"

            z: PathView.iconOrder
            scale: PathView.iconScale

            Rectangle {
                width: parent.width
                height: parent.height * 0.7

                anchors.top: parent.top

                color: "transparent"

                border.color: "black"
                border.width: 1

                ThumbnailItem {
                    width: parent.width
                    height: parent.height * 0.8

                    anchors.bottom: parent.bottom

                    thumbnail: pathView.model.getThumbnail(index)
                }

                Label {
                    text: fileName(path)

                    width: parent.width * 0.8
                    height: parent.height * 0.2

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top

                    wrapMode: "Wrap"

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    font.pointSize: 72
                    minimumPointSize: 8
                    fontSizeMode: Text.Fit

                    function fileName(path)
                    {
                        return path.slice(path.lastIndexOf("/")+1);
                    }
                }
                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        if (path && path.length !== 0) {
                            var video = videoFactory.createObject(root, {source: path, visible: true});
                            video.play();

                            video.stopped.connect(function(){
                                video.destroy();
                            });
                        }
                    }
                }
            }

            Button {
                visible: pathView.model.editable && pathView.currentIndex == index

                Label {
                    text: "Edit"

                    width: parent.width * 0.8
                    height: parent.height * 0.8

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    font.pointSize: 72
                    fontSizeMode: Text.Fit
                }

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom

                width: parent.width / 3.0
                height: parent.height * 0.2

                onClicked: {
                    var popup = popupOverlaysFactory.createObject(root, {});
                    popup.open();
                }
            }
        }

        path: Path {
            startX: 0
            startY: parent.height / 2
            PathAttribute {
                name: "iconScale"
                value: 0.3
            }
            PathAttribute {
                name: "iconOrder"
                value: 0
            }

            PathLine {
                x: parent.width / 2
                y: parent.height / 2
            }
            PathAttribute {
                name: "iconScale"
                value: 1.2
            }
            PathAttribute {
                name: "iconOrder"
                value: 10
            }

            PathLine {
                x: parent.width
                y: parent.height / 2
            }
        }
    }

    RoundButton {
        id: buttonBack
        x: 20
        y: 20

        text: "Back"

        onClicked: backTriggered()
    }

    RoundButton {
        id: buttonLoadVideo

        x: parent.width - 20 - width
        y: 20

        visible: model.editable

        text: "Load video"

        onClicked: loadVideoTriggered()
    }

    Component {
        id: videoFactory

        Video {
            id: video

            anchors.fill: parent

            fillMode: VideoOutput.Stretch

            muted: true

            MouseArea {
                anchors.fill: parent

                onClicked: video.stop();
            }
        }
    }

    Component {
        id: videoThreadFactory

        VideoThread {
        }
    }

    Component {
        id: popupOverlaysFactory

        VideoOverlaysPopup {
            onOverlaysApplyTriggered:
            {
                var videoThread = videoThreadFactory.createObject(root, {});

                videoThread.setVideoPath(root.model.getPath(pathView.currentIndex));
                for (let i=0; i <overlays.length; ++i)
                {
                    videoThread.setOverlay(overlays[i][0], overlays[i][1], overlays[i][2], overlays[i][3]);
                }

                var popupProgress = popupProgressFactory.createObject(root, {});
                popupProgress.open();

                popupProgress.abortTriggered.connect(function(){
                    videoThread.abort();
                });

                videoThread.videoEditingAborted.connect(function(){
                    videoThread.destroy();
                    popupProgress.close();
                });
                videoThread.videoEditingFinished.connect(function(arg){
                    videoThread.destroy();
                    popupProgress.close();
                    root.videoEditingFinished(arg);
                });
                videoThread.videoEditingProcessed.connect(function(arg){
                    popupProgress.progress = arg;
                })

                videoThread.start();
            }

            onOpened: parent.enabled = false;
            onClosed:
            {
                parent.enabled = true;
                // destroy(); // causes strange behavior when uncommented (reference root is not defined)
            }
        }
    }

    Component {
        id: popupProgressFactory

        AbortableProgressPopup {
            x: parent.width * 0.4
            y: parent.height * 0.4
            width: parent.width * 0.2
            height: parent.height * 0.2

            onOpened: parent.enabled = false;
            onClosed:
            {
                parent.enabled = true;
               // destroy(); // causes strange behavior when uncommented (reference root is not defined)
            }
        }
    }
}
