import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12


ApplicationWindow {
    title: qsTr("Calendar")
    width: 600
    height: 500
    visible: true

    PersianCal{
        anchors.fill: parent
        id:pcalendar
    }
}
