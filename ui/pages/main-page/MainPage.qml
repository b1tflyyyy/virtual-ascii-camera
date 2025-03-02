// MIT License
// 
// Copyright (c) 2025 @Who
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

import QtQuick 2.15
import QtQuick.Controls 2.15

import "../../dialogs/device"

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

    // Connection successful message
    DeviceSuccessfulConnection {
        id: _deviceSuccessfulConnection
    }

    // Connection failure message
    DeviceFailureConnection {
        id: _deviceFailureConnection
    }

    // Disconnection successful message
    DeviceSuccessfulDisconnection {
        id: _deviceSuccessfulDisconnection
    }

    // Disconnection failure message
    DeviceFailureDisconnection {
        id: _deviceFailureDisconnection
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

            text: qsTr("ASCII Realtime Virtual Camera")

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
                leftMargin: 10

                top: _deviceStatusText.top
            }

            fillMode: Image.PreserveAspectFit
            height: _deviceStatusText.height

            source: virtualCameraModel.connectionStatus ? "qrc:/resources/device-connected.png" : "qrc:/resources/device-disconnected.png"
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

        property color buttonColor: {
            if (!virtualCameraModel.connectionStatus) {
                return _connectButtonMouseArea.containsMouse ? "lightgreen" : "green"
            }

            return "gray"
        }

        anchors {
            left: _deviceInput.left
            top: _deviceInput.bottom

            topMargin: 10
        }

        color: buttonColor

        width: (_deviceInput.width - _disconnectDeviceButton.anchors.leftMargin) / 2
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
            
            property var currentCursorShape: {
                if (virtualCameraModel.connectionStatus) {
                    return Qt.ArrowCursor
                }

                return containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
            }
            
            anchors.fill: _connectDeviceButton
            hoverEnabled: true

            cursorShape: currentCursorShape

            onClicked: function() {
                if (!virtualCameraModel.connectionStatus) {
                    console.log(_deviceInput.text)
                    if (virtualCameraController.TryConnectToDevice(_deviceInput.text)) {
                        _deviceSuccessfulConnection.open()                    
                    } else {
                        _deviceFailureConnection.open()
                    }
                } 
            }
        }
    }

    // Disconnect button
    Rectangle {
        id: _disconnectDeviceButton

        property color buttonColor: {
            if (virtualCameraModel.connectionStatus) {
                return _disconnectButtonMouseArea.containsMouse ? "#E6676B" : "red"
            }

            return "gray"
        }

        anchors {
            left: _connectDeviceButton.right
            top: _connectDeviceButton.top

            leftMargin: 20
        }

        color: buttonColor

        width: _connectDeviceButton.width 
        height: _connectDeviceButton.height

        radius: _connectDeviceButton.radius

        Text {
            anchors.centerIn: _disconnectDeviceButton

            font {
                pointSize: 18
            }

            text: qsTr("Disconnect")
            color: "white"
        }

        MouseArea {
            id: _disconnectButtonMouseArea

            property var currentCursorShape: {
                if (!virtualCameraModel.connectionStatus) {
                    return Qt.ArrowCursor
                }

                return containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
            }

            anchors.fill: _disconnectDeviceButton
            hoverEnabled: true

            cursorShape: currentCursorShape

            onClicked: function() {
                if (virtualCameraModel.connectionStatus) {
                    if (virtualCameraController.TryDisconnectFromDevice()) {
                        _deviceSuccessfulDisconnection.open()
                    } else {
                        _deviceFailureDisconnection.open()
                    }
                }
            }
        }        
    }
}