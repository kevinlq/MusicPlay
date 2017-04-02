#ifndef MUSICSONGSLISTWIDGET_H
#define MUSICSONGSLISTWIDGET_H

#include <QTableWidget>
class MusicListMenu;

class MusicSongsListWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit MusicSongsListWidget(QWidget *parent);
    ~MusicSongsListWidget();

    //向tablewidget中添加一条记录
    void addItemContent(QString content /*,int row, int column = 0*/);
    //删除鼠标选中的行
    void removeItem();
    //删除某个列表中的所有歌曲
    void removeAllItem();
    //获取当前鼠标点击的行的内容
    QString getSelectContent();

    //保存歌曲信息
    void saveMusicInfo(const QString &name,const QString &path);
    //获取歌曲路径
    QString getMusicPath(const QString& name);

    //返回tablewidget是否为空
    bool tableWidgetIsEmpty();

Q_SIGNALS:
    void signalPlayMusic();
    void signalAddMusic();
    void signalAddMusicFolder();
    void signalDeleteMusic();
    void signalDeleteAllMusic();

    void signalPlayMusic(const QString &musicName);

    //向下发送所要请求的歌曲信息
    void signalSendNextMusic(const QString &name);
    void signalSendPreviousMusic(const QString &naem);

    //向bottombar发送开始要播放的歌曲
    void signalSendFirstPlayMusic(const QString &);

    //向下发送所请求的播放歌曲
    void signalSendPlayCmdMusicInfo(const QString &);

private Q_SLOTS:
    void slotCellDoubleClicked(int,int);

public Q_SLOTS:
    //获取上一首
    void slotGetNextMusic();
    void slotGetPreviouseMusic();

    /*程序启动后，若按下底部控制按钮，播放歌曲，则要先判断列表中是否有歌曲，
     * 若有，则从返回第一手歌曲,若没有则返回空
    */
    void slotGetFirstPlayMusic();

    //根据播放模式，发送不同的歌曲信息
    void slotSendPlayCmd(int);
private:
    void initForm();
    void initConnect();

    void setRadomPlayMusic();       //设置随机播放

protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);

private:
    MusicListMenu *m_menu;
    QMap<QString,QString>m_musicInfo;           //歌曲信息
};

#endif // MUSICSONGSLISTWIDGET_H
