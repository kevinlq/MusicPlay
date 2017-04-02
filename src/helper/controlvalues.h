#ifndef CONTROLVALUES
#define CONTROLVALUES

#define SHADOW_WIDTH            5

#define SOFT_TITLE  "音乐播放器"          //软件标题
#define LOGO_OUT    1                   //输出日志文件
#define QDEBUG_OUT  1                   //输出调试信息
#define DEFAULT_SKIN                    "10.png"

#define NO_VOICE                0
#define VOICE_DEFAULT_VALUE     60      //默认播放器声音大小

//窗体的宽度和高度
#define WIDGET_HEIGHT           620
#define WIDGET_WIDTH            880

#define TITLE_HEIGHT            40  //标题栏宽度
#define BOTTOM_HEIGHT           70  //底部

//枚举播放或者暂停状态
enum PlayState{
    MUSIC_PLAY = 0,
    MUSIC_PAUSE,
    MUSIC_PLAY_END      //播放结束
};

//枚举歌曲播放模式
typedef enum PlayMode{
    ORDER_PLAY = 0,   //顺序播放
    LIST_CIRCUAL,     //列表循环
    SINGLE_CIRCUAL,   //单曲循环
    SINGLE_PLAY,      //单曲播放
    RADOM_PLAY        //随机播放
}PlayMode;
#define DEFAULT_PLAY_MODE ORDER_PLAY        //默认顺序播放
//显示或者隐藏桌面歌词
enum Lyrc{
    SHOW_LYRC,
    HIDE_LYRC
};

//默认三个播放列表
#define MUSIC_PLAY_LIST_NUM         3

#endif // CONTROLVALUES

