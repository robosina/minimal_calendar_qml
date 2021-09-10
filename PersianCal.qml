import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import PersianCalendar 1.0
Item {
    property int cols: 7
    property int rows: 6
    property int cellw: grid.width/cols
    property int cellh: grid.height/rows


    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 10
        Item{
            Layout.preferredHeight: 60
            Layout.fillWidth: true
            RowLayout{
                anchors.fill: parent
//                Item {
//                    Layout.fillHeight: true
//                    Layout.fillWidth: true
//                    Button{
//                        anchors.fill: parent
//                        text: "previous year"
//                        onClicked: {
//                            pcalendar.prev_month()
//                        }
//                    }
//                }
                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Button{
                        anchors.fill: parent
                        text: "ماه قبلی"
                        font.family: "B Nazanin"
                        font.bold: true
                        onClicked: {
                            pcalendar.prev_month()
                        }
                    }
                }
               Item {
                    id: cal_info
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    ColumnLayout{
                        anchors.fill: parent
                        Label{
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            id:day_label
                            text: pcalendar.day_s
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.family: "B Nazanin"
                            font.bold: true
                        }
                        Label{
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            id:month_label
                            text: pcalendar.month
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.family: "B Nazanin"
                            font.bold: true
                        }
                        Label{
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            id:year_label
                            text: pcalendar.year_
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.family: "B Nazanin"
                            font.bold: true
                        }
                    }
                }
               Item {
                   Layout.fillHeight: true
                   Layout.fillWidth: true
                   Button{
                       anchors.fill: parent
                       text: "ماه بعدی"
                       font.family: "B Nazanin"
                       font.bold: true
                       onClicked: {
                           pcalendar.next_month()
                       }
                   }
               }
//               Item {
//                   Layout.fillHeight: true
//                   Layout.fillWidth: true
//                   Button{
//                       anchors.fill: parent
//                       text: "previous year"
//                       onClicked: {
//                           pcalendar.prev_month()
//                       }
//                   }
//               }
            }
        }

        Column{
            Layout.fillHeight: true
            Layout.fillWidth: true

            id:grid
            Repeater{
                model:PersianCalendar{
                    id:pcalendar
                }

                Row{
                    width: parent.width
                    height: cellh
                    property var dataModel: modelData
                    Repeater{
                        model:7
                        delegate: Item{
                            width: cellw
                            height: dataModel[index].isheader===true?cellh*0.8:cellh
                            Rectangle{
                                anchors.fill: parent
                                anchors.margins: dataModel[index].isheader===true?0:5
                                radius: dataModel[index].isheader===true?0:4
                                border.width: 4
                                border.color:dataModel[index].borderColor
                                color: dataModel[index].isheader===true?"gray":"transparent"
                                Text {
                                    anchors.fill: parent
                                    text: dataModel[index].day
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    font.pointSize: dataModel[index].is_current===true?18:18
                                    color: dataModel[index].textColor
                                    font.family: "B Nazanin"
                                    font.bold: true
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    function prev_month(){
        pcalendar.prev_month()
    }

    function next_month(){
        pcalendar.next_month()
    }
}
