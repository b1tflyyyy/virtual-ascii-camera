import QtQuick 2.15
import QtQuick.Window 2.15

import "../pages/main-page"

Window {
    id: _mainWindow

    visible: true
    title: qsTr("Virtual ASCII Camera")

    width: Screen.width * 0.50
    height: Screen.height * 0.50

    minimumWidth: 680
    minimumHeight: 340

    MainPage { }
}