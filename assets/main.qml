/*
 * Copyright (c) 2011-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Copyright (c) 2014, Florian Limberger <flo@snakeoilproductions.net>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

import bb.cascades 1.2

TabbedPane {
    showTabsOnActionBar: true
    Tab {
        title: qsTr("Automatic") + Retranslate.onLocaleOrLanguageChanged
        Page {
            Container {
                topPadding: 20
                rightPadding: topPadding
                bottomPadding: topPadding
                leftPadding: topPadding
                layout: DockLayout {}

                Container {
                    property string message
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    
                    Label { // part already sent
                        id: sentChars
                        text: ""
                        
                        textStyle {
                            base: SystemDefaults.TextStyles.BigText
                            textAlign: TextAlign.Right
                        }
                    
                    } // Label
                    Label { // current character
                        id: currentChar
                        text: ""
                        
                        textStyle {
                            base: SystemDefaults.TextStyles.BigText
                            color: Color.Red
                            textAlign: TextAlign.Center
                        }
                    } // Label
                    Label { // part not yet sent
                        id: remainingChars
                        text: ""
                        
                        textStyle {
                            base: SystemDefaults.TextStyles.BigText
                            textAlign: TextAlign.Left
                        }
                    } // Label
                    
                    onCreationCompleted: {
                        _sender.sendingChanged.connect(setText);
                        _sender.currentCharIdxChanged.connect(showChar);
                    }
                    
                    function setText(sending) {
                        if (sending) {
                            message = messageField.text;
                        } else {
                            sentChars.text = "";
                            currentChar.text = "";
                            remainingChars.text = "";
                        }
                    }
                    
                    function showChar(charIdx) {
                        if (message == "") {
                            console.log("MessageView warning: message is empty");
                        }
                        if (charIdx > 0) {
                            sentChars.text = message.substring(0, charIdx);
                        } else {
                            sentChars.text = "";
                        }
                        currentChar.text = message.charAt(charIdx);
                        if (charIdx < message.length - 1) {
                            remainingChars.text = message.substring(charIdx + 1, message.length);
                        } else {
                            remainingChars.text = "";
                        }
                    }
                } // Container

                TextField {
                    id: messageField
                    hintText: "Message"
                    inputMode: TextFieldInputMode.Text
                    visible: !_sender.sending
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Bottom

                    input {
                        submitKey: SubmitKey.Send

                        onSubmitted: {
                            _sender.sendSignal(messageField.text);
                        }
                    }
                } // TextField

                Button {
                    id: abortButton
                    text: "Abort transmission"
                    visible: _sender.sending
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Bottom

                    onClicked: {
                        _sender.abortTransmission();
                    }
                } // Button
            } // Container
        } // Page
    } // Tab
    Tab {
        // Localized text with the dynamic translation and locale updates support
        title: qsTr("Manual") + Retranslate.onLocaleOrLanguageChanged
        Page {
            Container {
                topPadding: 20
                rightPadding: topPadding
                bottomPadding: topPadding
                leftPadding: topPadding
                layout: DockLayout {}

                Button {
                    text: qsTr("Light") + Retranslate.onLocaleOrLanguageChanged
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Bottom

                    onClicked: {
                        _appUI.toggleLight();
                    }
                }
            } // Container
        } // Page
    } // Tab

    Menu.definition: MenuDefinition {
        settingsAction: SettingsActionItem {
            onTriggered: {
                settingsSheet.open();
            }
        }
    }

    attachedObjects: [
        SettingsSheet {
            id: settingsSheet
        }
    ]
} // TabbedPane
