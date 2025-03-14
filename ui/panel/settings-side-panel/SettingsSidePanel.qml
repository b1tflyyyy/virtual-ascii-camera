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

    // Blue level text
    Text {
        id: _blueLevelText

        anchors {
            top: parent.top
            topMargin: 80

            left: parent.left
            leftMargin: 25
        }

        font {
            pointSize: 16
        }

        text: qsTr("Blue level: %1".arg(_blueLevelSlider.value))
    }

    // Blue level slider
    Slider {
        id: _blueLevelSlider

        from: 0
        value: 128
        to: 255
        stepSize: 1

        width: parent.width / 2
        height: 20

        anchors {
            left: _blueLevelText.left

            top: _blueLevelText.bottom
            topMargin: 2
        }

        onMoved: function() {
            frameProcessingController.SetCbLevel(_blueLevelSlider.value)
        }
    }

    // Red level text
    Text {
        id: _redLevelText

        anchors {
            top: _blueLevelSlider.bottom
            topMargin: 30

            left: _blueLevelSlider.left
        }

        font {
            pointSize: 16
        }

        text: qsTr("Red level: %1".arg(_redLevelSlider.value))
    }

    // Red level slider
    Slider {
        id: _redLevelSlider

        from: 0
        value: 128
        to: 255
        stepSize: 1

        width: _blueLevelSlider.width
        height: _blueLevelSlider.height

        anchors {
            left: _redLevelText.left

            top: _redLevelText.bottom
            topMargin: 2
        }

        onMoved: function() {
            frameProcessingController.SetCrLevel(_redLevelSlider.value)
        }
    }
}