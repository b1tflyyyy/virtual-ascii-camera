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

import CppEnums 1.0

import "../../dialogs/default-message"
import "../../additional-components"
import "../../panel/settings-side-panel"

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

    // Creating default messages
    
    // Device connection successful message
    DefaultMessage {
        id: _deviceSuccessfulConnection

        title: qsTr("Success")

        width: parent.width * 0.60
        height: parent.height * 0.20

        textSize: 14
        description: qsTr("Device connected successfully!")
    }

    // Device connection failure message
    DefaultMessage {
        id: _deviceFailureConnection

        title: qsTr("Failure")

        width: parent.width * 0.60
        height: parent.height * 0.20

        textSize: 14
        description: qsTr("Device connection failed!")
    }

    // Device disconnection successful message
    DefaultMessage {
        id: _deviceSuccessfulDisconnection

        title: qsTr("Success")

        width: parent.width * 0.60
        height: parent.height * 0.20

        textSize: 14
        description: qsTr("Device disconnected successfully!")
    }

    // Device disconnection failure message
    DefaultMessage {
        id: _deviceFailureDisconnection

        title: qsTr("Failure")

        width: parent.width * 0.60
        height: parent.height * 0.20

        textSize: 14
        description: qsTr("Device disconnection failed!")
    }

    // Input device error message
    DefaultMessage {
        id: _inputDeviceError

        title: qsTr("Failure")

        width: parent.width * 0.60
        height: parent.height * 0.25

        textSize: 14
        description: qsTr("Input device error getting frame,\nplease check your input device and retry!")
    }    

    // Output device error message
    DefaultMessage {
        id: _outputDeviceError

        title: qsTr("Failure")

        width: parent.width * 0.60
        height: parent.height * 0.25

        textSize: 14
        description: qsTr("Output device error writing frame,\nplease check your output device and retry!")
    }

    // Output device error message: "The input device must be connected before the output device"
    DefaultMessage {
        id: _outputDeviceWrongOrderError

        title: qsTr("Failure")

        width: parent.width * 0.60
        height: parent.height * 0.25

        textSize: 14
        description: qsTr("The input device must be connected before the output device!")
    }

    // Output device error: "Failed to set the resolution for the output device, try checking the device or restarting the program!"
    DefaultMessage {
        id: _outputDeviceSettingResolutionError

        title: qsTr("Failure")

        width: parent.width * 0.60
        height: parent.height * 0.25

        textSize: 14
        description: qsTr("Failed to set the resolution for the output device,\ntry checking the device or restarting the program!")
    }

    // Default message for dynamic creation
    Component {
        id: _dynamicDialogComponent

        DefaultMessage {
            id: _outputDeviceSettingResolutionError

            width: parent.width * 0.60
            height: parent.height * 0.25

            textSize: 14

            onAccepted: function() {
                Qt.callLater(destroy)
            }
        }
    }

    // Setup connections
    Connections {
        target: frameProcessingModel
        
        function onInputDeviceError() {
            frameProcessingController.StopBroadcasting()
            _processingImageAnimation.running = false
            _inputDeviceError.open()
        }

        function onOutputDeviceError() {
            frameProcessingController.StopBroadcasting()
            _processingImageAnimation.running = false
            _outputDeviceError.open()
        }
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

    // Output device status
    DeviceStatus {
        id: _outputDeviceStatus

        statusWidth: 350
        statusHeight: 30

        statusText: qsTr("Output Device Status")
        statusTextColor: "black"

        textSize: 18

        imagePath: virtualCameraModel.connectionStatus ? "qrc:/resources/device-connected.png" : "qrc:/resources/device-disconnected.png"

        anchors {
            top: parent.top 
            topMargin: parent.height * 0.40

            left: parent.left
            leftMargin: 50
        }        
    }

    // Output device text field
    InputField {
        id: _outputDeviceInputField

        fieldWidth: 350
        fieldHeight: 50

        textSize: 18
        displayedPlaceholderText: qsTr("Enter the output device ...")

        textFieldColor: "black"

        anchors {
            left: _outputDeviceStatus.left

            top: _outputDeviceStatus.bottom
            topMargin: 20
        }        
    }

    // Connect output device button
    AnimatedButton {
        id: _outputDeviceConnectButton

        // _outputDeviceDisconnectButton.anchors.leftMargin -> space between 1'st and 2'nd buttons
        buttonWidth: (_outputDeviceInputField.width - _outputDeviceDisconnectButton.anchors.leftMargin) / 2
        buttonHeight: _outputDeviceInputField.height

        buttonRadius: 5

        buttonTextSize: 18
        buttonText: qsTr("Connect")
        buttonTextColor: "white"

        getButtonColorFunc: function(containsMouse) {
            if (!virtualCameraModel.connectionStatus) {
                return containsMouse ? "lightgreen" : "green"
            }

            return "gray"            
        }

        getDynamicCursorShapeFunc: function (containsMouse) {
            if (virtualCameraModel.connectionStatus) {
                return Qt.ArrowCursor
            }

            return containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor            
        }

        onAnimatedButtonClicked: function() {
            if (!virtualCameraModel.connectionStatus) {
                console.log(_outputDeviceInputField.text)
                if (inputVideoModel.connectionStatus) { 
                    if (virtualCameraController.TryConnectToDevice(_outputDeviceInputField.text)) {
                        let width = inputVideoController.GetVideoWidth()
                        let height = inputVideoController.GetVideoHeight()

                        if (virtualCameraController.SetupVideoResolution(width, height)) {
                            let message = qsTr("Successfully connected to output device.\nDefault resolution: %1x%2")
                            let successMessage = _dynamicDialogComponent.createObject(_mainPage, {
                                title: qsTr("Success"),
                                description: message.arg(width).arg(height)
                            })

                            successMessage.open()
                        } else {
                            _outputDeviceSettingResolutionError.open()
                        }
                    }                    
                } else {
                    _outputDeviceWrongOrderError.open()
                }
            } 
        }
        
        anchors {
            left: _outputDeviceInputField.left
            top: _outputDeviceInputField.bottom

            topMargin: 10
        }
    }

    // Disconnect output device button
    AnimatedButton {
        id: _outputDeviceDisconnectButton

        buttonWidth: _outputDeviceConnectButton.width 
        buttonHeight: _outputDeviceConnectButton.height

        buttonRadius: 5
        
        buttonTextSize: 18
        buttonText: qsTr("Disconnect")

        getButtonColorFunc: function(containsMouse) {
            if (virtualCameraModel.connectionStatus) {
                return containsMouse ? "#E6676B" : "red"
            }

            return "gray"
        }

        getDynamicCursorShapeFunc: function(containsMouse) {
            if (!virtualCameraModel.connectionStatus) {
                return Qt.ArrowCursor
            }

            return containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor            
        }

        onAnimatedButtonClicked: function() {
            if (virtualCameraModel.connectionStatus) {
                if (virtualCameraController.TryDisconnectFromDevice()) {
                    _deviceSuccessfulDisconnection.open()
                } else {
                    _deviceFailureDisconnection.open()
                }
            }            
        }

        anchors {
            left: _outputDeviceConnectButton.right
            top: _outputDeviceConnectButton.top

            leftMargin: 20
        }        
    }

    // Input device status
    DeviceStatus {
        id: _inputDeviceStatus

        statusWidth: 350
        statusHeight: 30

        statusText: qsTr("Input Device Status")
        statusTextColor: "black"

        textSize: 18

        imagePath: inputVideoModel.connectionStatus ? "qrc:/resources/device-connected.png" : "qrc:/resources/device-disconnected.png"       

        anchors {
            top: parent.top 
            topMargin: parent.height * 0.40

            right: parent.right
            rightMargin: 50
        }   
    }

    // Input device field
    InputField {
        id: _inputDeviceInputField

        fieldWidth: 350
        fieldHeight: 50

        textSize: 18
        displayedPlaceholderText: qsTr("Enter the input device ...")

        textFieldColor: "black"

        anchors {
            left: _inputDeviceStatus.left

            top: _inputDeviceStatus.bottom
            topMargin: 20
        } 
    }

    // Input device connect button
    AnimatedButton {
        id: _inputDeviceConnectButton

        buttonWidth: (_inputDeviceInputField.width - _inputDeviceDisconnectButton.anchors.leftMargin) / 2
        buttonHeight: _inputDeviceInputField.height

        buttonRadius: 5

        buttonTextSize: 18
        buttonText: qsTr("Connect")
        buttonTextColor: "white"

        getButtonColorFunc: function(containsMouse) {
            if (!inputVideoModel.connectionStatus) {
                return containsMouse ? "lightgreen" : "green"
            }

            return "gray"
        }

        getDynamicCursorShapeFunc: function(containsMouse) {
            if (inputVideoModel.connectionStatus) {
                return Qt.ArrowCursor
            }

            return containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor            
        }

        onAnimatedButtonClicked: function() {
            if (!inputVideoModel.connectionStatus) {
                if (inputVideoController.TryOpenInputSource(_inputDeviceInputField.text)) {
                    _deviceSuccessfulConnection.open()
                } else {
                    _deviceFailureConnection.open()
                }
            }           
        }

        anchors {
            top: _inputDeviceInputField.bottom
            topMargin: 10

            left: _inputDeviceInputField.left
        }
    }

    // Input device disconnect button
    AnimatedButton {
        id: _inputDeviceDisconnectButton

        buttonWidth: _inputDeviceConnectButton.buttonWidth
        buttonHeight: _inputDeviceConnectButton.height 

        buttonRadius: 5

        buttonTextSize: 18
        buttonText: qsTr("Disconnect")
        buttonTextColor: "white"

        getButtonColorFunc: function(containsMouse) {
            if (inputVideoModel.connectionStatus) {
                return containsMouse ? "#E6676B" : "red"
            }

            return "gray"
        }

        getDynamicCursorShapeFunc: function(containsMouse) {
            if (!inputVideoModel.connectionStatus) {
                return Qt.ArrowCursor
            }

            return containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor            
        }

        onAnimatedButtonClicked: function() {
            if (inputVideoModel.connectionStatus) {
                inputVideoController.CloseInputSource()
                _deviceSuccessfulDisconnection.open()
            }           
        }

        anchors {
            top: _inputDeviceConnectButton.top
            
            left: _inputDeviceConnectButton.right
            leftMargin: 10
        }
    }

    // Start broadcasting button
    AnimatedButton {
        id: _startBroadcastingButton

        buttonWidth: 250
        buttonHeight: 50

        buttonRadius: 5

        buttonTextSize: 18
        buttonText: qsTr("Start broadcasting")
        buttonTextColor: "white"

        getButtonColorFunc: function(containsMouse) {
            if (!inputVideoModel.connectionStatus || !virtualCameraModel.connectionStatus || (frameProcessingModel.broadcastingState === ProcessingState.BROADCASTING)) {
                return "gray"
            }

            return containsMouse ? "#ed02cd" : "#7c006c" 
        }

        getDynamicCursorShapeFunc: function(containsMouse) {
            if (!inputVideoModel.connectionStatus || !virtualCameraModel.connectionStatus || (frameProcessingModel.broadcastingState === ProcessingState.BROADCASTING)) {
                return Qt.ArrowCursor
            }

            return containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor   
        }

        onAnimatedButtonClicked: function() {
            if (inputVideoModel.connectionStatus && virtualCameraModel.connectionStatus && (frameProcessingModel.broadcastingState === ProcessingState.WAITING)) {
                frameProcessingController.StartBroadcasting()
                _processingImageAnimation.running = true
            }
        }

        anchors {
            left: parent.left
            leftMargin: (parent.width - _stopBroadcastingButton.anchors.leftMargin) / 2 - buttonWidth

            bottom: parent.bottom
            bottomMargin: 20
        }
    }

    // Stop broadcasting button
    AnimatedButton {
        id: _stopBroadcastingButton

        buttonWidth: _startBroadcastingButton.width
        buttonHeight: _startBroadcastingButton.height 

        buttonRadius: 5

        buttonTextSize: 18
        buttonText: qsTr("Stop broadcasting")
        buttonTextColor: "white"

        getButtonColorFunc: function(containsMouse) {
            if (!inputVideoModel.connectionStatus || !virtualCameraModel.connectionStatus || (frameProcessingModel.broadcastingState === ProcessingState.WAITING)) {
                return "gray"
            }

            return containsMouse ? "#4502fc" : "#22017f" 
        }

        getDynamicCursorShapeFunc: function(containsMouse) {
            if (!inputVideoModel.connectionStatus || !virtualCameraModel.connectionStatus || (frameProcessingModel.broadcastingState === ProcessingState.WAITING)) {
                return Qt.ArrowCursor
            }

            return containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor   
        }

        onAnimatedButtonClicked: function() {
            if (inputVideoModel.connectionStatus && virtualCameraModel.connectionStatus && (frameProcessingModel.broadcastingState === ProcessingState.BROADCASTING)) {
                frameProcessingController.StopBroadcasting()
                _processingImageAnimation.running = false
            }
        }

        anchors {
            left: _startBroadcastingButton.right
            leftMargin: 20

            top: _startBroadcastingButton.top
        }
    }

    Rectangle {
        id: _broadcastingStatusContainer

        width: 400
        height: 40

        color: "transparent"

        anchors {
            bottom: _startBroadcastingButton.top
            bottomMargin: 5

            left: _startBroadcastingButton.left
        }

        Text {
            id: _broadcastingStatusText

            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
            }

            font {
                pointSize: 16
            }

            text: qsTr("Broadcasting: ")
        }

        Image {
            id: _processingImage

            width: 32
            height: 32

            anchors {
                top: _broadcastingStatusText.top
                
                left: _broadcastingStatusText.right 
                leftMargin: 5
            }

            fillMode: Image.PreserveAspectFit
            source: "qrc:/resources/loading.png"

            PropertyAnimation on rotation {
                id: _processingImageAnimation
                
                from: 0
                to: 360

                loops: Animation.Infinite
                duration: 2000
            
                running: false
            }
        }
    }

    // Settings side panel
    SettingsSidePanel {
        id: _settingsSidePanel
    }

    // Output virtual camera settings 
    Image {
        id: _outputSettings

        width: 32
        height: 32 

        anchors {
            left: parent.left
            leftMargin: 30

            bottom: parent.bottom
            bottomMargin: 30
        }

        fillMode: Image.PreserveAspectFit

        source: "qrc:/resources/setting.png"

        MouseArea {
            id: _outputSettingsMouseArea

            anchors {
                fill: parent
            }

            hoverEnabled: true
            cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor

            onClicked: function() {
                _settingsSidePanel.open()
            }
        }
    }
}