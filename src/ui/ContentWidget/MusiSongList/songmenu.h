#ifndef SONGMENU_H
#define SONGMENU_H

#include <QMenu>
class QAction;

class SongMenu : public QMenu
{
    Q_OBJECT
public:
    explicit SongMenu(QWidget *parent = 0);
    ~SongMenu();
private:
    void initForm();
    void initAction();
    void initConnect();
Q_SIGNALS:
    void signalAddNewList();
    void signalAddMusic();
    void signalAddMusiFolder();
    void signalDeleteList();
    void signalRename();
private Q_SLOTS:

private:
    QAction *m_actionAddNewList;        //添加新列表
//    QAction *m_actionAddMusic;          //添加歌曲
//    QAction *m_actionAddMusicFolder;    //添加歌曲文件夹
    QAction *m_actionDeleteList;        //删除列表
    QAction *m_actionReName;            //重命名
};

#endif // SONGMENU_H
