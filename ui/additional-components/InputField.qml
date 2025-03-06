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

TextField {
    id: _customTextField

    property int fieldWidth: 0
    property int fieldHeight: 0

    property int textSize: 0
    property string displayedPlaceholderText: ""

    property color textFieldColor: "black"

    width: fieldWidth
    height: fieldHeight

    font {
        pointSize: textSize
    }

    placeholderText: displayedPlaceholderText

    color: textFieldColor
    clip: true

    Image {
        id: _deviceInputTextIcon

        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 15
        }

        visible: _customTextField.text === ""

        height: parent.height

        fillMode: Image.PreserveAspectFit
        source: "qrc:/resources/write.png"
    }

    MouseArea {
        anchors.fill: _customTextField
        hoverEnabled: true

        cursorShape: containsMouse ? Qt.IBeamCursor : Qt.ArrowCursor
        onClicked: {
            _customTextField.forceActiveFocus()
        }
    }
}
