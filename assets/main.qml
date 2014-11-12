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

import bb.cascades 1.2

TabbedPane {
    showTabsOnActionBar: true
    Tab { //First tab
        // Localized text with the dynamic translation and locale updates support
        title: qsTr("Tab 1") + Retranslate.onLocaleOrLanguageChanged
        Page {
            Container {
                Button {
                    text: qsTr("Light") + Retranslate.onLocaleOrLanguageChanged
                    
                    onClicked: {
                        _appUI.toggleLight();
                    }
                }
            }
        }
    } //End of first tab
    Tab { //Second tab
        title: qsTr("Tab 2") + Retranslate.onLocaleOrLanguageChanged
        Page {
            Container {
                TextField {
                    id: messageField
                    hintText: "Message"
                    inputMode: TextFieldInputMode.Text
                    
                    input {
                        submitKey: SubmitKey.Send
                        
                        onSubmitted: {
                            _appUI.send(messageField.text);
                        }
                    }
                }
            }
        }
    } //End of second tab
}
