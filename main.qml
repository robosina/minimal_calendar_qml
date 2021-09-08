import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import PersianCalendar 1.0

ApplicationWindow {
    title: qsTr("Calendar")
    width: 600
    height: 700
    visible: true
    property int cols: 7
    property int rows: 6
    property int cellw: grid.width/cols
    property int cellh: grid.height/rows
    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 20
        GridView{
            id:grid
            Layout.fillHeight: true
            Layout.fillWidth: true
            cellWidth: cellw
            cellHeight: cellh
            model:PersianCalendar{
                id:pcalendar
            }

            delegate: Item{
                width: cellw*0.9
                height: cellh*0.9
                Rectangle{
                    anchors.fill: parent
                    color: "pink"
                    Material.elevation: model.day===0?0:2
                    Material.background: model.day===0?Material.background:Material.Pink
                    Text {
                        anchors.fill: parent
                        text: model.day===0?"":model.day
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 14
                        color: "black"
                    }
                }
            }
        }
        Item{
            Layout.preferredHeight: 60
            Layout.fillWidth: true
            RowLayout{
                anchors.fill: parent
                Button{
                    text: "prev month"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    onClicked: {
                        pcalendar.prev_month()
                    }
                }
                Button{
                    text: "next month"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    onClicked: {
                        pcalendar.next_month()
                    }
                }
            }
        }
    }
}
