import bb.cascades 1.2

Sheet {
    id: settingsSheet

    Page {
        titleBar: TitleBar {
            title: "LightBeacon Settings"
            
            dismissAction: ActionItem {
                title: "Close"
                
                onTriggered: {
                    settingsSheet.close();
                }
            }
            
            acceptAction: ActionItem {
                title: "Save"
                
                onTriggered: {
                    _sender.baseDuration = baseDurationField.text;
                    settingsSheet.close();
                }
            }
        }
        
        Container {
            topPadding: 20
            rightPadding: topPadding
            bottomPadding: topPadding
            leftPadding: topPadding
            layout: StackLayout {}
            
            Label {
                text: "Base signal duration (ms):"
            }
            
            TextField {
                id: baseDurationField
                hintText: "Base signal duration"
                text: _sender.baseDuration
            }
        }
    }    
}
