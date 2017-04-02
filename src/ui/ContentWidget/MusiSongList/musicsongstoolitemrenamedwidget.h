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
#ifndef MUSICSONGSTOOLITEMRENAMEDWIDGET_H
#define MUSICSONGSTOOLITEMRENAMEDWIDGET_H

#include <QLineEdit>

class MusicSongsToolItemRenamedWidget : public QLineEdit
{
    Q_OBJECT
public:
    explicit MusicSongsToolItemRenamedWidget(int offset, const QString &originText,
                                             QWidget *parent = 0);
protected:
    virtual void focusOutEvent(QFocusEvent *event);

signals:
    void signalRenameFinished(const QString &text);

public slots:
    void slotRenameFinished();
    
};

#endif // MUSICSONGSTOOLITEMRENAMEDWIDGET_H
