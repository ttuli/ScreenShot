import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic

Rectangle
{
    id:window;
    color: "transparent";
    width: 250;
    height: 50;

    signal colorSig(int type,color choice);
    signal widthSig(int type,int level);

    property int ty: 0;
    property int up: 1;
    property int down: 0;
    property int triangle_position:down;

    function setType(t)
    {
        ty=t;
    }

    function setPosition(p)
    {
        triangle_position=p;
    }

    Rectangle
    {
        id:triangle;
        color:"white";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.topMargin: 10;
        anchors.bottomMargin: 10;
        anchors.top:triangle_position===down?parent.top:undefined;
        anchors.bottom: triangle_position===down?parent.bottom:undefined;
        rotation: 45;
        width: 20;
        height: 20;
    }

    Rectangle
    {
        id:outline;
        anchors.fill: parent;
        color: "white";
        anchors.topMargin: triangle_position===down?20:0;
        anchors.bottomMargin: triangle_position===down?0:20;

        property int btnWidth: 20;
        property int btnHeight: 20;

        Rectangle
        {
            id:redbtn;
            color: "red";
            width: parent.btnWidth;
            height: parent.btnHeight;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.left;
            anchors.leftMargin: 5;
            border.width: 2;
            border.color: "white";

            MouseArea
            {
                anchors.fill:parent;
                onClicked:
                {
                    parent.border.width=2;
                    parent.border.color="white";

                    greenbtn.border.width=0;
                    blackbtn.border.width=0;
                    bluebtn.border.width=0;

                    colorSig(ty,"red");
                }
            }
        }
        Rectangle
        {
            id:greenbtn;
            color: "green";
            width: parent.btnWidth;
            height: parent.btnHeight;
            anchors.left: redbtn.right;
            anchors.leftMargin: 5;
            anchors.verticalCenter: parent.verticalCenter;

            MouseArea
            {
                anchors.fill:parent;
                onClicked:
                {
                    parent.border.width=2;
                    parent.border.color="white";

                    redbtn.border.width=0;
                    blackbtn.border.width=0;
                    bluebtn.border.width=0;

                    colorSig(ty,Qt.color("green"));
                }
            }
        }
        Rectangle
        {
            id:blackbtn;
            color: "black";
            width: parent.btnWidth;
            height: parent.btnHeight;
            anchors.left: greenbtn.right;
            anchors.leftMargin: 5;
            anchors.verticalCenter: parent.verticalCenter;

            MouseArea
            {
                anchors.fill:parent;
                onClicked:
                {
                    parent.border.width=2;
                    parent.border.color="white";

                    greenbtn.border.width=0;
                    redbtn.border.width=0;
                    bluebtn.border.width=0;

                    colorSig(ty,Qt.color("black"));
                }
            }
        }
        Rectangle
        {
            id:bluebtn;
            color: "blue";
            width: parent.btnWidth;
            height: parent.btnHeight;
            anchors.left: blackbtn.right;
            anchors.leftMargin: 5;
            anchors.verticalCenter: parent.verticalCenter;

            MouseArea
            {
                anchors.fill:parent;
                onClicked:
                {
                    parent.border.width=2;
                    parent.border.color="white";

                    greenbtn.border.width=0;
                    blackbtn.border.width=0;
                    redbtn.border.width=0;

                    colorSig(ty,Qt.color("blue"));
                }
            }
        }

        Text
        {
            text: qsTr("宽度:");
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: bluebtn.right;
            anchors.leftMargin: 5;
        }

        Rectangle
        {
            id:sliderArea;
            anchors.left: bluebtn.right;
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.rightMargin: 5;
            anchors.leftMargin: 35;
            anchors.bottom: parent.bottom;


            Slider
            {
                id: control
                from:1;
                to:3;
                snapMode: Slider.SnapAlways;
                stepSize: 1;
                anchors.fill: parent;

                onMoved:function()
                {
                    widthSig(ty,control.value);
                }

                handle: Rectangle
                {
                    y:control.height/2-height/2;
                    x:control.position*control.availableWidth
                    width:15;
                    height:15;
                    radius:8;
                    border.width:1;
                    border.color:"gray";
                }


                background: Rectangle {
                        anchors.verticalCenter: control.verticalCenter;
                        width: control.width
                        height: 8;
                        radius: 3
                        color: "white";
                        border.color: "gray";
                        border.width: 1;

                        Rectangle {
                            y: control.horizontal ? 0 : control.visualPosition * parent.height
                            width: control.horizontal ? control.position * parent.width : parent.width
                            height: control.horizontal ? parent.height : control.position * parent.height
                            radius: 3
                            color: "green";
                        }
                    }
            }
        }
    }
}
