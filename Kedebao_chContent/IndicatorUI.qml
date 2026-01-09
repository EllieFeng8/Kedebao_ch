

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls

Rectangle {
    id: indicator
    width: 58
    height: 58
    color: "#00ffffff"
    property int statusColor: 0 // Can be 0 or 1
    Image {
        id: signalUi
        source: indicator.statusColor === 1 ? "assets/rectangle_12" : "assets/rectangle_14"
    }
}
