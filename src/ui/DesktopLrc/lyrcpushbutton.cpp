#include "lyrcpushbutton.h"

LyrcPushButton::LyrcPushButton(QWidget *parent)
    :QPushButton(parent)
{
    initForm();
}

LyrcPushButton::~LyrcPushButton()
{

}

void LyrcPushButton::initForm()
{
    setFlat(true);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("QPushButton{background-color:rgb(174,216,230);"
                  "border:none;color:white;}"
                  "QPushButton::hover{background:qlineargradient(x1:0,y1:0,x2:0,"
                  "y2:1,stop:0 #3BA1E6,stop: 0.5 #3BA1E6,stop: 1.0 #3BA1E6);"
                  "border:none;}");
}

