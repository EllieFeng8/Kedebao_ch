/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
pragma Singleton
import QtQuick
import QtQuick.Controls
import Core 1.0


QtObject {
    id: appStatus
    property bool isBig: true
    property int pageNum : 4;
}
