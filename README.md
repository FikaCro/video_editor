# Qt Video Browser & After Effects Application
QtQuick Application with video browsing, playing and editing functionalities.

## Description and usage
Upon opening the application user is able to select one of the following options:
- Raw videos
- Edited videos

Upon slection, new view comes up with thumbnail video browsing by sliding left or right. Each video is represented with its thumbnail and name. If raw videos option is selected, user is able to load videos directly from file path by pressing the button. User is also able to go back from both of the views, raw and edited.
Each video thumbnail within raw videos selection has additional edit option next to it. Upon slecting the option, new popup appears with 3 different animating QML element overlays:
- Numerical value text element which is randomly changing every 300 ms
- Rectangle shape with applied gradient which is randomly changing gradient color and shape position every 1000 ms
- Slider control which is incrementing until max and decrementing until min value every 500 ms

User is able to see visualization of each overlay, apply each of them by selecting the checkbox next to their preview and input their position by entering x and y coordinates. After selecting overlays and their properties user is able to click Apply button which initiates video editing process. Resulting outcome of the editing is the new video file with overlays burned into the file on top of the original video. While the process is being carried over, popup with progress bar indicating the video editing percentage appears with the option to cancel the video editing process at any time. After the process is done, new video appears in the edited videos section of the application which is playable in the same manner as raw video. User is able to play each video visible in both sections by clicking on its thumbnail. Videos are then played in application full screen and are stopped by clicking anywhere in the application while reproduction.

## Dependencies
- C++17
- Qt5 (Qml, Quick, Widgets)
- OpenCV

## Build and usage
- Clone the project ```https://github.com/FikaCro/video_editor.git```
- Navigate inside the project ```cd video_editor```
- Open project file ```video_editor.pro``` with the desired editor
- Edit lines ```INCLUDEPATH``` and ```LIBS``` so the build is able to find [OpenCV](https://opencv.org/) library
- Build project using ```qmake```
- Run application

## Additional info
- Application tested on Ubuntu 18.04 only
- Build tested using Qt Creator only
