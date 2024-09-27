import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Controls.Basic

Rectangle
{
    id:window;
    color:"white";

    signal changeSavePath();


    function initSetting(path)
    {
        showpath.text=path;
    }

    Rectangle
    {
        id:backgroundRec
        anchors.fill: parent;
        color:"white";

        Text
        {
            id:pathtext
            anchors.top: parent.top;
            anchors.left: parent.left;
            anchors.topMargin: 30;
            anchors.leftMargin: 10;
            text:"保存路径:";
            font.pixelSize: 20;
            font.bold: true;
        }

        Rectangle
        {
            id:textrec;
            anchors.left: pathtext.right;
            anchors.top: pathtext.top;
            anchors.leftMargin: 20;
            radius: 5;
            width: 200;
            height: pathtext.implicitHeight+10;
            color:"transparent";

            Text
            {
                id:showpath;

                property bool isTextBorder: false;

                anchors.fill: parent;
                anchors.margins: 1;
                text: "";
                elide:Text.ElideRight;
                verticalAlignment: Text.AlignVCenter;

                onTextChanged:
                {
                    if(implicitWidth>width)
                        isTextBorder=true;
                    else isTextBorder=false;
                }

                MouseArea
                {
                    anchors.fill: parent;
                    hoverEnabled: true;
                    onEntered:
                    {
                        popupRec.opacity=1;
                    }
                    onExited:
                    {
                        popupRec.opacity=0;
                    }
                }
            }

        }


        Rectangle
        {
            id:popupRec;
            anchors.top: backgroundRec.top;
            anchors.horizontalCenter: backgroundRec.horizontalCenter;
            height: 25;
            width: (recText.implicitWidth+10<backgroundRec.width-10?recText.implicitWidth+10:backgroundRec.width-10);
            color:"#F5F5F5";
            radius: 5;
            opacity: 0;
            visible: showpath.isTextBorder;
            Text
            {
                id: recText;
                text: showpath.text;
                anchors.centerIn: parent;
                elide: Text.ElideRight;
            }

            Behavior on opacity
            {
                NumberAnimation
                {
                    duration: 100;
                }
            }
        }

        Image
        {
            id: checkImage
            source: "/new/prefix1/res/PencilSquare.svg";
            anchors.left: textrec.right;
            anchors.top: textrec.top;
            anchors.leftMargin: 20;
            height: pathtext.height;
            width: height;
            MouseArea
            {
                anchors.fill: parent;
                cursorShape: Qt.PointingHandCursor;
                onClicked:
                {
                    changeSavePath();
                }
            }
        }

    }
}
