#include "titlewidget.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "controlvalues.h"
#include "searchlineedit.h"
#include "iconhelper.h"

//构造函数
TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent)
{
    initForm();
    initWidget();
    initLayout();
    initConnect();
}

//析构函数
TitleWidget::~TitleWidget()
{
    delete m_labelIcon;
    delete m_labelTitle;
    delete m_pbnSkin;
    delete m_pbnMin;
    delete m_pbnClose;
}

//样式初始化
void TitleWidget::initForm()
{
    //设置标题栏固定宽度
    setFixedHeight(TITLE_HEIGHT);
    //设置焦点策略
    setFocusPolicy(Qt::ClickFocus);
}

//界面初始化
void TitleWidget::initWidget()
{
    //程序图标
    m_labelIcon = new QLabel(this);
    //IconHelper::Instance()->SetIcoMain(m_labelIcon);
    //程序标题
    m_labelTitle  = new QLabel(this);
//    m_labelTitle->setText("音乐播放器");
    m_labelTitle->setPixmap(QPixmap(":/image/MusicTitle.png"));

    m_labelTitle->setFont(QFont("楷体", 11, QFont::Bold));
    m_labelTitle->setObjectName("whiteLabel");

    //搜索框
//    m_search = new SearchLineEdit(this);

    //皮肤按钮
    m_pbnSkin = new QPushButton(this);
    m_pbnSkin->setCursor(Qt::PointingHandCursor);
    m_pbnSkin->setToolTip("皮肤");
    m_pbnSkin->setObjectName("pbnSkin");
    //最小化
    m_pbnMin = new QPushButton(this);
    m_pbnMin->setFlat(true);
    m_pbnMin->setCursor(Qt::PointingHandCursor);
    m_pbnMin->setToolTip("最小化");
    m_pbnMin->setObjectName("pbnMin");
    //关闭
    m_pbnClose = new QPushButton(this);
    m_pbnClose->setFlat(true);
    m_pbnClose->setObjectName("pbnClose");
    m_pbnClose->setCursor(Qt::PointingHandCursor);
    m_pbnClose->setToolTip("关闭");

}

//布局初始化
void TitleWidget::initLayout()
{
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addSpacing(2);
    m_mainLayout->addWidget(m_labelIcon);
    m_mainLayout->addWidget(m_labelTitle);
    m_mainLayout->addStretch();
//    m_mainLayout->addWidget(m_search);
//    m_mainLayout->addStretch();
    m_mainLayout->addWidget(m_pbnSkin);
    m_mainLayout->addWidget(m_pbnMin);
    m_mainLayout->addWidget(m_pbnClose);
    m_mainLayout->setContentsMargins(0,0,0,0);
    setLayout(m_mainLayout);
}

//信号和槽初始化
void TitleWidget::initConnect()
{
    //依次为：皮肤、最小化、关闭按钮的信号关联
    connect(m_pbnSkin,SIGNAL(clicked()),
            this,SIGNAL(signalSkin()));
    connect(m_pbnMin,SIGNAL(clicked()),
            this,SIGNAL(signalMin()));
    connect(m_pbnClose,SIGNAL(clicked()),
            this,SIGNAL(signalClose()));
}
