import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import PersianCalendar 1.0
Item {
    property int cols: 7
    property int rows: 6
    property int cellw: each_month.width/cols
    property int cellh: each_month.height/rows

    function selected_day(text){
        console.log("selected")
    }

    function get_years(){
        var years = [1400]
        for(var i=1;i<50;i++){
            years.push(1400+i)
        }
        return years
    }

    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 5
        Item{
            Layout.preferredHeight: 100
            Layout.fillWidth: true
            ColumnLayout{
                anchors.fill: parent
                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    RowLayout{
                        anchors.fill: parent
                        ComboBox {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            id:month_selector
                            onCurrentIndexChanged: {
                                pcalendar.selectMonth=(currentIndex+1)
                            }
                            font.family: "B Nazanin"
                            font.pointSize: 14
                            model: ["فروردین" , "اردیبهشت", "خرداد", "تیر", "اَمرداد", "شهریور", "مهر", "آبان", "آذر", "دی", "بهمن", "اسفند" ]
                        }
                        ComboBox {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            id:year_selector
                            onCurrentIndexChanged: {
                                pcalendar.selectYear=parseInt(currentText)
                            }
                            font.family: "B Nazanin"
                            font.pointSize: 14
                            model: get_years()
                        }
                    }
                }
                Item {
                    id: cal_info
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    RowLayout{
                        anchors.fill: parent
                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Label{
                                anchors.fill: parent
                                id:to_label
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.family: "B Nazanin"
                                font.bold: true
                                font.pointSize: 12
                            }
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Label{
                                anchors.fill: parent
                                id:from_label
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.family: "B Nazanin"
                                font.bold: true
                                font.pointSize: 12
                            }
                        }
                    }
                }
            }
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: pcalendar.month+"\n"+pcalendar.year_
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "B Nazanin"
            font.bold: true
            font.pointSize: 68
            color: "#eeeeee"
            id:each_month
            Column{
                anchors.fill: parent
                Repeater{
                    model:PersianCalendar{
                        id:pcalendar
                        selectMonth: 1
                        onFrom_dayChanged: {
                            if(from_day.length>0){
                                from_label.text="از تاریخ:"+from_day
                            }else{
                                from_label.text=""
                            }
                        }

                        onTo_dayChanged: {
                            if(to_day.length>0){
                                to_label.text="تا تاریخ:"+to_day
                            }else{
                                to_label.text=""
                            }
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
                                Item{
                                    anchors.fill: parent
                                    anchors.margins: dataModel[index].isheader===true?0:dataModel[index].margin
                                    anchors.topMargin: 6
                                    anchors.bottomMargin: 6
                                    layer.enabled: true
                                    opacity: dataModel[index].boxOpacity
                                    Rectangle{
                                        anchors.fill: parent
                                        id:day_rect
                                        radius: dataModel[index].radius
                                        border.color:dataModel[index].borderColor
                                        color: dataModel[index].boxColor
                                    }
                                    Rectangle{
                                        color: dataModel[index].boxColor
                                        anchors.fill: parent
                                        anchors.rightMargin: dataModel[index].is_from ===true ? parent.width/2 : 0
                                        anchors.leftMargin: dataModel[index].is_to ===true ? parent.width/2 : 0
                                        visible: dataModel[index].is_current===true?false:true
                                    }
                                }
                                Item{
                                    anchors.fill: parent
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
                                                pcalendar.select_date_(dataModel[index].day,(month_selector.currentIndex+1),pcalendar.year_)
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
