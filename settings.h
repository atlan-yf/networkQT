#ifndef SETTINGS_H
#define SETTINGS_H

#include "commands.h"

//在这里修改ip地址
#define IP_Address "127.0.0.1"
#define Port       9999

//记录本机的玩家号
#define MyPlayer Player1 //在这里修改玩家(1/2)

//用bool类型储存玩家号
#define Player1 true
#define Player2 false

//方块的长和宽
#define RectangleWight  50.f
#define RectangleHeight 50.f

//窗口大小上限为999（三位数）
#define WindowWidth  800.f
#define WindowHeight 600.f

//边界线到屏幕边界线的宽度
#define EdgeWidth 5.f

//文字设置
#define TextContent   "Waiting for connect..."  //文字内容
#define TextFontSize  20                        //字体大小
#define TextPositionX 5                         //文字位置
#define TextPositionY 5

#endif // SETTINGS_H
