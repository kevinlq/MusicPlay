#include "iconhelper.h"
#include "myhelper.h"
#include "app.h"
#include <QPainter>
#include <QSettings>

IconHelper *IconHelper::_instance = 0;
IconHelper::IconHelper(QObject *):
    QObject(qApp)
{
    int fontId = QFontDatabase::addApplicationFont(":/image/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    iconFont = QFont(fontName);

    icoSize = QSize(16, 16);
    icoTextColor = Qt::red;
    icoTextSize = App::AppFontSize;
}

void IconHelper::SetIcon(QLabel *lab, QChar c)
{
    SetIcon(lab, c, App::AppFontSize);
}

void IconHelper::SetIcon(QAbstractButton *btn, QChar c)
{
    SetIcon(btn, c, App::AppFontSize);
}

void IconHelper::SetIcon(QLabel *lab, QChar c, int size)
{
    iconFont.setPointSize(size);
    lab->setFont(iconFont);
    lab->setText(c);
}

void IconHelper::SetIcon(QAbstractButton *btn, QChar c, int size)
{
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setText(c);
}

void IconHelper::SetIcoMain(QLabel *labMain)
{
    SetIcoMain(labMain, App::AppFontSize);
}

void IconHelper::SetIcoMenu(QAbstractButton *btnMenu)
{
    SetIcoMenu(btnMenu, App::AppFontSize);
}

void IconHelper::SetIcoMin(QAbstractButton *btnMin)
{
    SetIcoMin(btnMin, App::AppFontSize);
}

void IconHelper::SetIcoNormal(QAbstractButton *btnNormal)
{
    SetIcoNormal(btnNormal, App::AppFontSize);
}

void IconHelper::SetIcoClose(QAbstractButton *btnClose)
{
    SetIcoClose(btnClose, App::AppFontSize);
}

void IconHelper::SetIcoMain(QLabel *labMain, int size)
{
    iconFont.setPointSize(size);
    labMain->setFont(iconFont);
    labMain->setText(QChar(App::IcoMain));
}

void IconHelper::SetIcoMenu(QAbstractButton *btnMenu, int size)
{
    iconFont.setPointSize(size);
    btnMenu->setFont(iconFont);
    btnMenu->setText(QChar(App::IcoMenu));
}

void IconHelper::SetIcoMin(QAbstractButton *btnMin, int size)
{
    iconFont.setPointSize(size);
    btnMin->setFont(iconFont);
    btnMin->setText(QChar(App::IcoMin));
}

void IconHelper::SetIcoNormal(QAbstractButton *btnNormal, int size)
{
    iconFont.setPointSize(size);
    btnNormal->setFont(iconFont);
    btnNormal->setText(QChar(App::IcoNormal));
}

void IconHelper::SetIcoClose(QAbstractButton *btnClose, int size)
{
    iconFont.setPointSize(size);
    btnClose->setFont(iconFont);
    btnClose->setText(QChar(App::IcoClose));
}

QIcon IconHelper::IcoMenu()
{
    return Ico(QChar(App::IcoMenu), icoTextSize);
}

QIcon IconHelper::IcoMin()
{
    return Ico(QChar(App::IcoMin), icoTextSize);
}


QIcon IconHelper::IcoNormal()
{
    return Ico(QChar(App::IcoNormal), icoTextSize);
}

QIcon IconHelper::IcoClose()
{
    return Ico(QChar(App::IcoClose), icoTextSize);
}

QIcon IconHelper::Ico(QChar c)
{
    return Ico(c, icoTextSize);
}

QIcon IconHelper::Ico(QChar c, int size)
{
    QImage image(icoSize, QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);

    QPen pen = painter.pen();
    pen.setColor(icoTextColor);
    iconFont.setPixelSize(size);
    painter.setPen(pen);
    painter.setFont(iconFont);

    painter.drawText(image.rect(), Qt::AlignCenter, c);
    return QIcon(QPixmap::fromImage(image));
}
