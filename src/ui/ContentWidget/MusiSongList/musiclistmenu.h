#ifndef MUSICLISTMENU_H
#define MUSICLISTMENU_H
#include <QMenu>
class QAction;

class MusicListMenu : public QMenu
{
    Q_OBJECT
public:
    MusicListMenu(QWidget *parent);
    ~MusicListMenu();

private:
    void initAction();
    void initConnect();

Q_SIGNALS:
    void signalPlayMusic();
    void signalAddMusic();
    void signalAddMusicFolder();
    void signalDeleteMusic();
    void signalDeleteAllMusic();

private:
    QAction *m_actionPlayMusic;          //播放音乐
    QAction *m_actionAddMusic;           //添加歌曲
//    QAction *m_actionAddMusicFolder;     //添加歌曲文件夹
    QAction *m_actionDeleteMusic;        //删除音乐
    QAction *m_actionDeleteAll;          //删除所有的音乐
};

#endif // MUSICLISTMENU_H
