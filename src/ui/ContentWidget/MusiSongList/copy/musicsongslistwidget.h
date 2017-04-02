#ifndef MUSICSONGSLISTWIDGET_H
#define MUSICSONGSLISTWIDGET_H

#include "musicabstracttablewidget.h"
class QAction;

class MusicSongsListWidget : public MusicAbstractTableWidget
{
    Q_OBJECT
public:
    explicit MusicSongsListWidget(QWidget *parent = 0);
    ~MusicSongsListWidget();
    
private:
    void initForm();
    void initAction();
    void initConnect();
protected:
    virtual void contextMenuEvent(QContextMenuEvent *);
Q_SIGNALS:
    void signalPlayMusic();
    void signalAddMusic();
    void signalAddMusicFolder();
    void signalDeleteMusic();
    void signalDeleteAllMusic();

public Q_SLOTS:
    virtual void listCellEntered(int row, int column);
    virtual void listCellClicked(int row, int column);

private:

    QColor m_defaultBkColor;
    int m_previousColorRow;
    int m_previousClickRow;

    QMenu *m_menu;
    QAction *m_actionPlayMusic;          //播放音乐
    QAction *m_actionAddMusic;           //添加歌曲
    QAction *m_actionAddMusicFolder;     //添加歌曲文件夹
    QAction *m_actionDeleteMusic;        //删除音乐
    QAction *m_actionDeleteAll;          //删除所有的音乐
    
};

#endif // MUSICSONGSLISTWIDGET_H
