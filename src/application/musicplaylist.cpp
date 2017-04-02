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
#include "musicplaylist.h"


MusicPlayList::MusicPlayList(QObject *parent) : QObject(parent)
{

}

MusicPlayList::~MusicPlayList()
{

}

int MusicPlayList::currentIndex() const
{
    return m_currentIndex;
}

QString MusicPlayList::currentMediaString() const
{
    if(m_currentIndex == -1 || m_currentIndex >= m_mediaList.count())
    {
        return QString();
    }
    return m_mediaList.isEmpty() ? QString()
                                 : m_mediaList[m_currentIndex];
}

int MusicPlayList::mediaCount() const
{
    return m_mediaList.count();
}

bool MusicPlayList::isEmpty() const
{
    return m_mediaList.isEmpty();
}

bool MusicPlayList::clear()
{
    m_mediaList.clear();
    return isEmpty() ? true : false;
}

void MusicPlayList::addMedia(const QString &content)
{
    m_mediaList = QStringList(content);
}

void MusicPlayList::addMedia(const QStringList &items)
{
    m_mediaList = items;
}

bool MusicPlayList::insertMedia(int index, const QString &content)
{
    if( index < 0 || index > m_mediaList.count())
    {
        return false;
    }
    m_mediaList.insert(index,content);
    return true;
}

bool MusicPlayList::insertMedia(int index, const QStringList &items)
{
    if( index < 0 || index > m_mediaList.count())
    {
        return false;
    }
    for(int i = 0; i < items.count(); ++i)
    {
        m_mediaList.insert(m_mediaList.count() + i, items[i]);
    }
    return true;
}

bool MusicPlayList::removeMedia(int pos)
{
    if( pos < 0 || pos >= m_mediaList.count())
    {
        return false;
    }
    m_mediaList.removeAt(pos);
    emit removeCurrentMedia();
    return true;
}

bool MusicPlayList::removeMedia(int start, int end)
{
    if( start > end || (start < 0 || end >= m_mediaList.count()) )
    {
        return false;
    }
    for(int i = 0; i < end - start; ++i)
    {
        m_mediaList.removeAt(start);
    }
    return true;
}

void MusicPlayList::appendMedia(const QString &content)
{
    m_mediaList.append(content);
}

void MusicPlayList::appendMedia(const QStringList &items)
{
    m_mediaList.append(items);
}

