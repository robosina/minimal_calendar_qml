import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import PersianCalendar 1.0
Item {
    property int cols: 7
    property int rows: 6
    property int cellw: each_month.width/cols
    property int cellh: 500/rows


    function selected_day(text){
        console.log("selected")
    }

    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 5
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
//                Item {
//                    Layout.fillHeight: true
//                    Layout.fillWidth: true
//                    Button{
//                        anchors.fill: parent
//                        text: "ماه قبلی"
//                        font.family: "B Nazanin"
//                        font.bold: true
//                        onClicked: {
//                            pcalendar.prev_month()
//                        }
//                    }
//                }
               Item {
                    id: cal_info
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    ColumnLayout{
                        anchors.fill: parent
                        Label{
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            id:from_label
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.family: "B Nazanin"
                            font.bold: true
                            font.pointSize: 12
                        }
                        Label{
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            id:to_label
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.family: "B Nazanin"
                            font.bold: true
                            font.pointSize: 12
                        }
                        Label{
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            id:year_label
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.family: "B Nazanin"
                            font.bold: true
                        }
                    }
                }
//               Item {
//                   Layout.fillHeight: true
//                   Layout.fillWidth: true
//                   Button{
//                       anchors.fill: parent
//                       text: "سال بعدی"
//                       font.family: "B Nazanin"
//                       font.bold: true
//                       onClicked: {
//                           pcalendar.next_month()
//                       }
//                   }
//               }
            }
        }

        ListView{
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: 2
            model: 12
            spacing: 10
            id:each_month
            clip: true
            delegate: Item{
                width: parent.width
                height: 500
                property int indexOfThisDelegate: index
                Text {
                    anchors.fill: parent
                    text: pcalendar.month+"\n"+pcalendar.year_
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: "B Nazanin"
                    font.bold: true
                    font.pointSize: 68
                    color: "#eeeeee"
                    Column{
                        anchors.fill: parent
                        Repeater{
                            model:PersianCalendar{
                                id:pcalendar
                                selectMonth: indexOfThisDelegate+1
                                onFrom_dayChanged: {
                                    from_label.text=from_day
                                }

                                onTo_dayChanged: {
                                    to_label.text=to_day
                                }
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
                                            id:day_rect
                                            anchors.fill: parent
                                            anchors.margins: dataModel[index].isheader===true?0:5
                                            radius: dataModel[index].isheader===true?0:8
                                            border.width: 4
                                            border.color:dataModel[index].borderColor
                                            color: dataModel[index].boxColor
                                            opacity: dataModel[index].boxOpacity
                                            Text {
                                                anchors.fill: parent
                                                text: dataModel[index].day
                                                horizontalAlignment: Text.AlignHCenter
                                                verticalAlignment: Text.AlignVCenter
                                                font.pointSize: dataModel[index].is_current===true?18:18
                                                color: dataModel[index].textColor
                                                font.family: "B Nazanin"
                                                font.bold: true
                                                MouseArea{
                                                    anchors.fill: parent
                                                    onClicked: {
                                                        pcalendar.select_date_(dataModel[index].day,(indexOfThisDelegate+1),pcalendar.year_)
                                                    }
                                                }
                                            }
                                        }
                                    }
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
