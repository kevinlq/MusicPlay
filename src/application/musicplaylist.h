/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-03-13
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:基于Qt的音乐播放器--播放队列的实现
Function:
**************************************************/
#ifndef MUSICPLAYLIST_H
#define MUSICPLAYLIST_H

#include <QObject>
#include <QStringList>

class MusicPlayList : public QObject
{
    Q_OBJECT
public:
    explicit MusicPlayList(QObject *parent = 0);
    ~MusicPlayList();

    //void setPlaybackMode(MusicObject::SongPlayType mode);

    int currentIndex() const;
    QString currentMediaString() const;
    int mediaCount() const;
    bool isEmpty() const;
    bool clear();

    void addMedia(const QString &content);
    void addMedia(const QStringList &items);
    bool insertMedia(int index, const QString &content);
    bool insertMedia(int index, const QStringList &items);
    bool removeMedia(int pos);
    bool removeMedia(int start, int end);

Q_SIGNALS:
        void removeCurrentMedia();

public Q_SLOTS:
    void appendMedia(const QString &content);
    void appendMedia(const QStringList &items);

protected:
    QStringList m_mediaList;
    int m_currentIndex;
private:
};

#endif // MUSICPLAYLIST_H
