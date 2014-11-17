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
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Bottom
                    layout: StackLayout {}
                    
                    TextField {
                        id: messageField
                        hintText: "Message"
                        inputMode: TextFieldInputMode.Text
                        enabled: !_sender.sending
                        
                        input {
                            submitKey: SubmitKey.Send
                            
                            onSubmitted: {
                                _sender.sendSignal(messageField.text);
                            }
                        }
                    }
                    
                    Button {
                        id: abortButton
                        text: "Abort transmission"
                        enabled: _sender.sending
                        horizontalAlignment: HorizontalAlignment.Right
                        
                        onClicked: {
                            _sender.abortTransmission();
                        }
                    }
                }
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
                    horizontalAlignment: HorizontalAlignment.Center
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
                var settings = settingsSheetDefinition.createObject();
                
                settings.open();
            }
        } 
    }
    
    attachedObjects: [
        ComponentDefinition {
            id: settingsSheetDefinition
            
            SettingsPage {}
        }
    ]
} // TabbedPane
