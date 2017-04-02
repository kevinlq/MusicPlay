#ifndef APP_H
#define APP_H

#include "controlvalues.h"
class QString;

class App
{
public:
    static QString AppPath;                 //应用程序路径
    static int AppFontSize;                 //应用程序字体大小
    static QString AppFontName;             //应用程序字体名称

    static int IcoMain;                     //左上角图标
    static int IcoMenu;                     //下来菜单图标
    static int IcoMin;                      //最小化图标
    static int IcoNormal;                   //正常图标
    static int IcoClose;                    //关闭图标

    static QString AppSkin;                 //软件皮肤
    static int AppPlayMode;                 //播放模式

    static QString AppTitle;                //界面标题
    static QString AppStyle;                //界面样式
    static bool AutoRun;                    //开机自动运行

    static bool IsPlaying;                  //播放器是否正在播放

    static void ReadConfig();               //读取配置文件
    static void WriteConfig();              //写入配置文件

};

#endif // APP_H
