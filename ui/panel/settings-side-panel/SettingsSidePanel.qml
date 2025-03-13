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

import "../../additional-components"

// TODO: rewrite !!!
// -------------------------------------->
Drawer {
    id: _settingsSidePanel

    width: parent.width * 0.40
    height: parent.height

    edge: Qt.LeftEdge
    interactive: true

    // Global mouse area
    MouseArea {
        anchors {
            fill: parent
        }

        onClicked: {
            parent.forceActiveFocus()
        }
    }

    // Virtual camera settings 
    Text {
        id: _topText

        anchors {
            horizontalCenter: parent.horizontalCenter

            top: parent.top
            topMargin: 10
        }

        font {
            pointSize: 16
        }

        text: qsTr("Virtual Camera Settings")
    }

    // Width setting text
    Text {
        id: _widthSettingText

        anchors {
            left: parent.left
            leftMargin: 10

            top: parent.top
            topMargin: 70
        }

        font {
            pointSize: 14
        }

        text: qsTr("Setup output width")
    }

    // Width input field
    InputField {
        id: _widthInputField

        fieldWidth: parent.width * 0.50
        fieldHeight: 40

        textSize: 14
        displayedPlaceholderText: qsTr("Width ...")

        textFieldColor: "black"

        validator: IntValidator { 
            bottom: 1
            top: 3840
        }

        anchors {
            left: _widthSettingText.left

            top: _widthSettingText.bottom
            topMargin: 5
        }
    }

    // Height setting text
    Text {
        id: _heightSettingText

        anchors {
            left: _widthInputField.left
            
            top: _widthInputField.bottom
            topMargin: 10
        }

        font {
            pointSize: 14
        }

        text: qsTr("Setup output height")
    }

    // Width input field
    InputField {
        id: _heightInputField

        fieldWidth: _widthInputField.fieldWidth
        fieldHeight: _widthInputField.fieldHeight

        textSize: 14
        displayedPlaceholderText: qsTr("Height ...")

        textFieldColor: "black"

        validator: IntValidator { 
            bottom: 1
            top: 3840
        }

        anchors {
            left: _heightSettingText.left

            top: _heightSettingText.bottom
            topMargin: 5
        }
    }

    // Apply button
    AnimatedButton {
        id: _applyButton

        buttonWidth: parent.width * 0.30
        buttonHeight: 30

        buttonRadius: 5

        buttonTextSize: 16
        buttonText: qsTr("Apply")
        buttonTextColor: "white"

        getButtonColorFunc: function(containsMouse) {
            return containsMouse ? "lightgreen" : "green"
        }

        getDynamicCursorShapeFunc: function(containsMouse) {
            return containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
        }

        onAnimatedButtonClicked: function() {
            let width = parseInt(_widthInputField.text)
            let height = parseInt(_heightInputField.text)

            if (virtualCameraController.SetupVideoFormat(width, height)) {
                console.log("format setup successfully")
            } else {
                console.log("format setup error")
            }
        }

        anchors {
            horizontalCenter: parent.horizontalCenter

            bottom: parent.bottom
            bottomMargin: 10
        }
    }
}