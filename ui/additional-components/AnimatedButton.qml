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

Rectangle {
    id: _animatedButton

    property int buttonWidth: 0
    property int buttonHeight: 0

    property int buttonRadius: 0

    property int buttonTextSize: 0
    property string buttonText: ""
    property color buttonTextColor: "white"

    // signature -> function (containsMouse) { return "color" }
    property var getButtonColorFunc: null

    // signature -> function (containsMouse) { return "color" }
    property var getDynamicCursorShapeFunc: null

    signal animatedButtonClicked()

    color: getButtonColorFunc(_animatedButtonMouseArea.containsMouse)

    width: buttonWidth
    height: buttonHeight

    radius: buttonRadius

    Text {
        anchors.centerIn: parent

        font {
            pointSize: buttonTextSize
        }

        text: buttonText
        color: buttonTextColor
    }

    MouseArea {
        id: _animatedButtonMouseArea

        anchors.fill: parent
        hoverEnabled: true
        cursorShape: getDynamicCursorShapeFunc(containsMouse)
        onClicked: {
            animatedButtonClicked()
        }
    }
}