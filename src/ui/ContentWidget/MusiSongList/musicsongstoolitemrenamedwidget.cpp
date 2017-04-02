/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-03-12
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:基于Qt的音乐播放器---歌曲列表信息重命名输入框
Function:在对播放列表进行重命名时，这个输入框会显示出来，在编辑完成后，发出对应的信号
**************************************************/
#include "musicsongstoolitemrenamedwidget.h"

MusicSongsToolItemRenamedWidget::MusicSongsToolItemRenamedWidget(
        int offset, const QString &originText, QWidget *parent)
    :QLineEdit(parent)
{
    setGeometry(1,offset,330,20);
    setText(originText);
    setFocus(Qt::MouseFocusReason);
    connect(this,SIGNAL(editingFinished()),this,SLOT(slotRenameFinished()));
}

//焦点移除输入框意味着编辑完成，发出编辑完成信号
void MusicSongsToolItemRenamedWidget::focusOutEvent(QFocusEvent *event)
{
     emit signalRenameFinished(text());
}


void MusicSongsToolItemRenamedWidget::slotRenameFinished()
{
    emit signalRenameFinished(text());
}
