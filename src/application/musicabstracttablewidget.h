#ifndef MUSICABSTRACTTABLEWIDGET_H
#define MUSICABSTRACTTABLEWIDGET_H

#include <QTableWidget>
#include <QHeaderView>

class  MusicAbstractTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit MusicAbstractTableWidget(QWidget *parent = 0);
    ~MusicAbstractTableWidget();

    void clear();

public Q_SLOTS:
    void listCellEntered(int row, int column);
    virtual void listCellClicked(int row, int column) = 0;

protected:
    void setTransparent(int angle);
    void setRowColor(int row, const QColor &color) const;

    QColor m_defaultBkColor;
    int m_previousColorRow;
    int m_previousClickRow;

};

#endif // MUSICABSTRACTTABLEWIDGET_H
