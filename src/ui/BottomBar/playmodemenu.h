#ifndef PLAYMODEMENU_H
#define PLAYMODEMENU_H

#include <QMenu>
class QAction;

class PlayModeMenu : public QMenu
{
    Q_OBJECT
public:
    explicit PlayModeMenu(QWidget*parent = 0);
    ~PlayModeMenu();

private:
    void initForm();
    void initAction();
    void initConnect();
Q_SIGNALS:
    void signalSendPlayMode(int);

private Q_SLOTS:
    void slotOrderPlay(bool);
    void slotListCirtual(bool);
    void slotSingleCirtual(bool);
    void slotSinglePlay(bool);
    void slotRadomPlay(bool);

private:
    QAction *m_pOrderPlay;      //顺序播放
    QAction *m_pListCircual;    //列表循环
    QAction *m_pSingleCircual;  //单曲循环
    QAction *m_pSnglePlay;      //单曲播放
    QAction *m_pRadomPlay;      //随机播放
};

#endif // PLAYMODEMENU_H
