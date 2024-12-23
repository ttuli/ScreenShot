import QtQuick
import QtQuick.Controls

Rectangle
{
    id:window;
    color: "white";

    property int btnlength:30

    property string currentState: "cursor";

    property int cursorChoice:0;
    property int lineChoice: cursorChoice+1;
    property int drawChoice: cursorChoice+2;
    property int textChoice: cursorChoice+3;

    signal choiceSig(int choice);
    signal pinSig();

    width: btnlength*5+20+4*5;
    height: btnlength+20;

    function getCurrentState()
    {
        return currentState;
    }
    function initCurrentState()
    {
        cursorbtn.isChosed=true;
        cursorbtn.color="#DCDCDC";

        linebtn.isChosed=false;
        linebtn.color="white";

        drawbtn.isChosed=false;
        drawbtn.color="white";

        textbtn.isChosed=false;
        textbtn.color="white";
    }

    Row
    {
        id:rowLayout;
        spacing: 5;
        anchors.fill: parent;
        anchors.margins: 10;
        width: btnlength*5+4*5;
        height: btnlength;
        Rectangle
        {
            id:cursorbtn;
            width: btnlength;
            height: btnlength;
            color:"#DCDCDC";
            radius: 10;

            property bool isChosed: false;

            Image
            {
                anchors.fill: parent;
                source: "/new/prefix1/res/cursor.svg"
            }
            MouseArea
            {
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked:
                {
                    parent.isChosed=true;
                    parent.color="#DCDCDC";

                    linebtn.isChosed=false;
                    linebtn.color="white";

                    drawbtn.isChosed=false;
                    drawbtn.color="white";

                    textbtn.isChosed=false;
                    textbtn.color="white";

                    choiceSig(cursorChoice);
                }
                onEntered:
                {
                    if(!parent.isChosed)
                    parent.color="#F5F5F5"
                }
                onExited:
                {
                    if(!parent.isChosed)
                        parent.color="white";
                }
            }
        }
        Rectangle
        {
            id:drawbtn;
            width: btnlength;
            height: btnlength;
            color:"white";
            radius: 10;

            property bool isChosed: false;

            Image
            {
                anchors.fill: parent;
                source: "/new/prefix1/res/draw.svg"
            }
            MouseArea
            {
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked:
                {
                    parent.isChosed=true;
                    parent.color="#DCDCDC";

                    linebtn.isChosed=false;
                    linebtn.color="white";

                    cursorbtn.isChosed=false;
                    cursorbtn.color="white";

                    textbtn.isChosed=false;
                    textbtn.color="white";

                    choiceSig(drawChoice);
                }
                onEntered:
                {
                    if(!parent.isChosed)
                    parent.color="#F5F5F5"
                }
                onExited:
                {
                    if(!parent.isChosed)
                        parent.color="white";
                }
            }
        }
        Rectangle
        {
            id:linebtn;
            width: btnlength;
            height: btnlength;
            color:"white";
            radius: 10;

            property bool isChosed: false;

            Image
            {
                anchors.fill: parent;
                source: "/new/prefix1/res/line.svg"
            }
            MouseArea
            {
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked:
                {
                    parent.isChosed=true;
                    parent.color="#DCDCDC";

                    drawbtn.isChosed=false;
                    drawbtn.color="white";

                    cursorbtn.isChosed=false;
                    cursorbtn.color="white";

                    textbtn.isChosed=false;
                    textbtn.color="white";

                    choiceSig(lineChoice);
                }
                onEntered:
                {
                    if(!parent.isChosed)
                    parent.color="#F5F5F5"
                }
                onExited:
                {
                    if(!parent.isChosed)
                        parent.color="white";
                }
            }
        }

        Rectangle
        {
            id:textbtn;
            width: btnlength;
            height: btnlength;
            color:"white";
            radius: 10;

            property bool isChosed: false;

            Image
            {
                anchors.fill: parent;
                anchors.margins: 5;
                source: "/new/prefix1/res/text.svg"
            }
            MouseArea
            {
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked:
                {
                    parent.isChosed=true;
                    parent.color="#DCDCDC";

                    drawbtn.isChosed=false;
                    drawbtn.color="white";

                    cursorbtn.isChosed=false;
                    cursorbtn.color="white";

                    linebtn.isChosed=false;
                    linebtn.color="white";

                    choiceSig(textChoice);
                }
                onEntered:
                {
                    if(!parent.isChosed)
                    parent.color="#F5F5F5"
                }
                onExited:
                {
                    if(!parent.isChosed)
                        parent.color="white";
                }
            }
        }
        Rectangle
        {
            id:pinbtn;
            width: btnlength;
            height: btnlength;
            color:"white";
            radius: 10;

            property bool isChosed: false;

            Image
            {
                anchors.fill: parent;
                source: "/new/prefix1/res/pin.svg"
            }
            MouseArea
            {
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked:
                {
                    pinSig();
                }
                onPressed:
                {
                    parent.color="#DCDCDC"
                }
                onReleased:
                {
                    parent.color="white";
                }

                onEntered:
                {
                    if(!parent.isChosed)
                    parent.color="#F5F5F5"
                }
                onExited:
                {
                    if(!parent.isChosed)
                        parent.color="white";
                }
            }
        }
    }//end Row

}
