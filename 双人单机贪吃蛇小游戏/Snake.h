//我是真的！
#include <iostream>
#include <conio.h>
#include<windows.h>  
#include<Mmsystem.h> 
#pragma comment(lib,"winmm.lib")
#include <fstream>
#include <string>
#include <cstdio>//用来调用remove函数删除复制的文件
#include <vector>
#include <algorithm>//排序算法sort函数用到了
/*
    控制台头文件
    音乐头文件
*/
// 是否播放音乐/音效 0表示不播放, 1表示播放
extern int isSound = 1;
extern int isMusic = 1;
#define viewBGM == 0//界面音效 必要情况下可删除不实现
#define gameBGM == 1//游戏音效
#define collision == 2//撞墙、撞蛇音效
#define eat == 3//吃食物音效
#define colorA snakeA.color
#define colorB snakeB.color

//音乐文件的路径
const wchar_t musicPath[4][128] = {
    L".\\music\\viewBGM.wav",
    L".\\music\\gameBGM.wav",
    L".\\music\\collision.wav",
    L".\\music\\eat.wav"
};

using namespace std;

int flag = 0; //胜利标识符 flag = 1 表示A蛇胜利
              //           flag = 2 表示B蛇胜利

int gameMode = 1; //游戏模式 1表示单人模式 2表示双人模式
int OBSTACLE_COUNT = 10; //障碍物数量
int current_music = 0;

bool isAccelerating = false; // 是否正在加速

//string colorA = "blue";  //蛇的颜色
//string colorB = "yellow";

bool soundEffects = true; //音效的开启
bool music = true; //音乐的开启
bool going = 0;

const TCHAR* COLLISION_SOUND = TEXT("sound2.wav"); //撞墙音效
const TCHAR* FOOD_COLLISION_SOUND = TEXT("sound1.wav"); //吃食物音效

#define  WIDE 60
#define  HIGH 25
#define DX 5
#define DY 2

int sleep_time = 100; // 200 milliseconds 贪吃蛇速度


// -------------------- 数据设计 --------------------
/*
    定义一个蛇的结构体
*/

struct SNAKE {
    struct BODY * body; // 动态数组，用于存储蛇的身体部分
    int length;  // 蛇的长度
    char direction; // 当前移动方向
    string color; //颜色
    int score; //分数
}snakeA, snakeB;

struct BODY {
    int x;
    int y;
    BODY* next;
};

struct Food {
    int x;
    int y;
    string color;
}food;

struct obstacle {
    int x;
    int y;
}obstacles[10];

/*
    地图
*/
int map[25][60];

string col[7] = { "red","yellow","green","blue","purple","cyan","white" };
// -------------------- 数据设计 --------------------
// -------------------- service函数声明 --------------------

/*
    负责人: 极夜
    功能: 初始化游戏数据
          将地图障碍物和食物、贪吃蛇长度位置、速度数据初始化
          将分数初始化为零
          无尽模式将时间初始化为零
    参数: void
    返回值: void
*/
void init();
/*
    负责人: 忽晚
    功能: 蛇自动移动
    参数: void
    返回值: void
*/
void run();
/*
    负责人: 嗯哼
    功能: 控制蛇移动的方向
    用控制台光标进行实现
    对于蛇A由wasd进行控制
    对于蛇B由上下左右进行控制
    参数: void
    返回值: void
*/
void changeDirection();
/*
    负责人: 汉斯特
    功能: 障碍物的随机生成
    参数: void
    返回值: void
*/
void generateObstacle();
/*
    负责人: 汉斯特
    功能: 食物的随机生成 如果上一个食物被清理 则生成新的食物
            事物的生成位置不能出现在障碍物和食物的位置上
    参数: void
    返回值: void
*/
void generateFood();
/*
    负责人: 嗯哼
    功能: 根据蛇的碰撞体积判断游戏是否结束
    参数:
    返回值:
        0表示没有结束
        1表示A蛇胜利
        2表示B蛇胜利

*/
int isWin();
/*
    负责人: 忽晚
    功能: 判断蛇与任何单位是否相撞
    参数:
    返回值:
        1表示蛇发生碰撞
        0表示蛇没有发生碰撞

*/
bool checkCollision();
/*
    负责人: 忽晚
    功能: 判断蛇与何种食物相撞 通过颜色区分 buff 和debuff效果
    参数:
    返回值:
*/
int checkFood();
/*
    负责人: 汉斯特
    功能: 蛇与何种食物相撞后蛇身变长
    参数:
    返回值:
*/
void snakeGrow();
/*
    负责人: 嗯哼
    功能: 判断撞到除了食物的其他单位
    参数:
    返回值:
        0表示没有撞到
        1表示撞到了
*/
int checkOtherCollision();
/*
    负责人: 金洋
    功能: 调用checkCollision如果蛇与食物相撞 则清空当前食物
    参数:
    返回值:
        1表示蛇发生碰撞
        0表示蛇没有发生碰撞

*/
bool clearFood();
/*
    负责人: 克林
    功能: 将蛇加速
          在单人模式中 用E进行加速
          在双人模式中 对于新加入的蛇使用1进行加速
    参数:
    返回值:
*/
void accelerate();
/*
    负责人: 金洋
    功能: 调用checkCollision()返回1时
            判断碰撞的物体是什么
            如果是food 播放音效1
            其他则 播放音效2 表示撞墙死亡反馈
    参数:
    返回值:
*/
void playCollisionSound();
/*
    负责人: 昭熙
    功能: 开关音乐
    参数:
    返回值:
*/
int playMusic(int choose);
int stopMusic();
/*
    负责人: 克林
    功能: 当游戏结束时 记录score到文本文件
    参数:
    返回值:
*/
void writeScore();
/*
    负责人: 克林
    功能: 当打开排行榜时，读取文本文件中的分数信息
    参数:
    返回值:
*/
void readScore();
void gotoXY(int x, int y);// 传入坐标, 将光标移动到指定坐标
void setPrintColor(int color); // 高亮显示指定文字

// -------------------- view函数声明 --------------------

/*
    负责人: MADAO
    功能: 展示选项, 玩家可以在这里选择进入游戏, 进入设置或排行榜或者退出游戏
           玩家在该界面通过ws移动光标, 回车确认选项
        进入游戏: 调用游戏界面函数choiceView();
        进入设置: 调用gameSet();
        进入排行榜:调用leaderboard();
        退出游戏: 调用exit(0);
*/
void menuView();
/*
    负责人: 昭熙
    功能: 展示选项, 玩家可以在这里选择游戏模式
            单人无尽
            双人无尽
            玩家在该界面通过ws移动光标, 回车确认选项
            按esc  返回上一级(返回首页)
            有返回值 单人模式时返回 1 双人模式时返回2
        进入游戏: 调用游戏界面函数gameView();
        返回上一级: 调用menuView();
*/
int choiceView();
/*
    负责人: 嗯哼
    功能: 游戏设置
            玩家可以通过ws移动光标
            ad修改选项
            修改贪吃蛇颜色
            修改音效（包含游戏音乐和音效的开启关闭、音量的调节、背景音乐的选择）
            esc退出设置

*/
void gameSet();
/*
    负责人: 极夜
    功能: 初始化生成地图 包含墙壁和障碍物 固定位置生成蛇实体
    分别在左上角和右上角展示双方分数 界面上方的中间展示倒计时或正计时
    参数: void
    返回值: void
*/
void gameView_ShowMap();
/*
    负责人: 金洋
    功能: 根据flag的值  打印游戏胜利界面  用户可以按任意键回到主菜单
    参数: void
    返回值: void
*/
int winView();
/*
    负责人: 汉斯特
    功能: 游戏界面整合
        初始化游戏数据(调用函数init())
        根据玩家输入控制蛇的方向
    参数: void
    返回值: void
*/
void gameView();
/*
    负责人: kami
    功能: 游戏暂停界面 暂停界面
    输入WS移动选项光标，按enter确认
    继续游戏：调用gameview();
    更改游戏设置：调用gameSet();
    退出游戏：调用menuView();
    参数: void
    返回值: void
*/
void pauseView();
/*
    负责人: 克林
    功能: 排行榜界面
    玩家可以通过ad翻页
    esc退出排行榜
    退出游戏：调用menuView();
    参数: void
    返回值: void
*/
void leaderboard();