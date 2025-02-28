import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs

Rectangle {
    id: _mainPage

    anchors.fill: parent

    // Global mouse area
    MouseArea {
        anchors.fill: parent

        onClicked: {
            _mainPage.forceActiveFocus();
        }
    }

    // Success message
    Dialog {
        id: dialog
        title: "Device successfully connected!"
        standardButtons: Dialog.Ok | Dialog.Cancel

        width: parent.width * 0.40
        height: parent.height * 0.15

        anchors.centerIn: parent
    }

    // Top Text Main Page
    Rectangle {
        id: _mainPageTextContainer

        width: 640
        height: 60

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        anchors.topMargin: 50

        border {
            color: "gray"
            width: 2
        }

        Text {
            anchors.centerIn: parent

            text: "ASCII Realtime Virtual Camera"

            font {
                bold: true
                pointSize: 18
            }
        }
    }

    // Device status
    Rectangle {
        id: _deviceStatus

        width: 350
        height: 30

        anchors {
            top: parent.top 
            topMargin: parent.height * 0.40

            left: parent.left
            leftMargin: 50
        }

        Text {
            id: _deviceStatusText

            text: "Device Status"
            color: "black"

            font {
                pointSize: 18
            }
        }

        Image {
            id: _deviceStatusIcon

            anchors {
                left: _deviceStatusText.right
                leftMargin: 15 
            }

            fillMode: Image.PreserveAspectFit
            height: _deviceStatusText.height

            source: _connectDeviceButton.isConnected ? "qrc:/resources/link.png" : "qrc:/resources/disruption.png"
        }
    }

    // Get Device
    TextField {
        id: _deviceInput

        anchors {
            left: _deviceStatus.left

            top: _deviceStatus.bottom
            topMargin: 20
        }

        width: 350
        height: 50

        font {
            pointSize: 18
        }

        placeholderText: "Enter here your device"

        color: "black"
        clip: true

        Image {
            id: _inputTextIcon

            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: 15
            }

            visible: _deviceInput.text === ""

            height: parent.height

            fillMode: Image.PreserveAspectFit
            source: "qrc:/resources/write.png"
        }

        MouseArea {
            anchors.fill: _deviceInput
            hoverEnabled: true

            cursorShape: containsMouse ? Qt.IBeamCursor : Qt.ArrowCursor
            onClicked: {
                _deviceInput.forceActiveFocus()
            }
        }
    }

    // Connect button
    Rectangle {
        id: _connectDeviceButton

        property bool isConnected: false

        anchors {
            left: _deviceInput.left
            top: _deviceInput.bottom

            topMargin: 10
        }

        color: _connectButtonMouseArea.containsMouse ? "lightgreen" : "green"

        width: _deviceInput.width / 2
        height: _deviceInput.height

        radius: 5

        Text {
            anchors.centerIn: _connectDeviceButton

            font {
                pointSize: 18
            }

            text: qsTr("Connect")
            color: "white"
        }

        MouseArea {
            id: _connectButtonMouseArea

            anchors.fill: _connectDeviceButton
            hoverEnabled: true

            cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor

            onClicked: function() {
                if (virtualCameraController.TryConnectToDevice(_deviceInput.text)) {
                    dialog.open()
                    _connectDeviceButton.isConnected = true                    
                    console.log("connection success")
                } else {
                    _connectDeviceButton.isConnected = false
                    console.log("connection failed")
                }

                console.log(_deviceInput.text)
            }
        }
    }
}