//������ģ�
#include <iostream>
#include <conio.h>
#include<windows.h>  
#include<Mmsystem.h> 
#pragma comment(lib,"winmm.lib")
#include <fstream>
#include <string>
#include <cstdio>//��������remove����ɾ�����Ƶ��ļ�
#include <vector>
#include <algorithm>//�����㷨sort�����õ���
/*
    ����̨ͷ�ļ�
    ����ͷ�ļ�
*/
// �Ƿ񲥷�����/��Ч 0��ʾ������, 1��ʾ����
extern int isSound = 1;
extern int isMusic = 1;
#define viewBGM == 0//������Ч ��Ҫ����¿�ɾ����ʵ��
#define gameBGM == 1//��Ϸ��Ч
#define collision == 2//ײǽ��ײ����Ч
#define eat == 3//��ʳ����Ч
#define colorA snakeA.color
#define colorB snakeB.color

//�����ļ���·��
const wchar_t musicPath[4][128] = {
    L".\\music\\viewBGM.wav",
    L".\\music\\gameBGM.wav",
    L".\\music\\collision.wav",
    L".\\music\\eat.wav"
};

using namespace std;

int flag = 0; //ʤ����ʶ�� flag = 1 ��ʾA��ʤ��
              //           flag = 2 ��ʾB��ʤ��

int gameMode = 1; //��Ϸģʽ 1��ʾ����ģʽ 2��ʾ˫��ģʽ
int OBSTACLE_COUNT = 10; //�ϰ�������
int current_music = 0;

bool isAccelerating = false; // �Ƿ����ڼ���

//string colorA = "blue";  //�ߵ���ɫ
//string colorB = "yellow";

bool soundEffects = true; //��Ч�Ŀ���
bool music = true; //���ֵĿ���
bool going = 0;

const TCHAR* COLLISION_SOUND = TEXT("sound2.wav"); //ײǽ��Ч
const TCHAR* FOOD_COLLISION_SOUND = TEXT("sound1.wav"); //��ʳ����Ч

#define  WIDE 60
#define  HIGH 25
#define DX 5
#define DY 2

int sleep_time = 100; // 200 milliseconds ̰�����ٶ�


// -------------------- ������� --------------------
/*
    ����һ���ߵĽṹ��
*/

struct SNAKE {
    struct BODY * body; // ��̬���飬���ڴ洢�ߵ����岿��
    int length;  // �ߵĳ���
    char direction; // ��ǰ�ƶ�����
    string color; //��ɫ
    int score; //����
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
    ��ͼ
*/
int map[25][60];

string col[7] = { "red","yellow","green","blue","purple","cyan","white" };
// -------------------- ������� --------------------
// -------------------- service�������� --------------------

/*
    ������: ��ҹ
    ����: ��ʼ����Ϸ����
          ����ͼ�ϰ����ʳ�̰���߳���λ�á��ٶ����ݳ�ʼ��
          ��������ʼ��Ϊ��
          �޾�ģʽ��ʱ���ʼ��Ϊ��
    ����: void
    ����ֵ: void
*/
void init();
/*
    ������: ����
    ����: ���Զ��ƶ�
    ����: void
    ����ֵ: void
*/
void run();
/*
    ������: �ź�
    ����: �������ƶ��ķ���
    �ÿ���̨������ʵ��
    ������A��wasd���п���
    ������B���������ҽ��п���
    ����: void
    ����ֵ: void
*/
void changeDirection();
/*
    ������: ��˹��
    ����: �ϰ�����������
    ����: void
    ����ֵ: void
*/
void generateObstacle();
/*
    ������: ��˹��
    ����: ʳ���������� �����һ��ʳ�ﱻ���� �������µ�ʳ��
            ���������λ�ò��ܳ������ϰ����ʳ���λ����
    ����: void
    ����ֵ: void
*/
void generateFood();
/*
    ������: �ź�
    ����: �����ߵ���ײ����ж���Ϸ�Ƿ����
    ����:
    ����ֵ:
        0��ʾû�н���
        1��ʾA��ʤ��
        2��ʾB��ʤ��

*/
int isWin();
/*
    ������: ����
    ����: �ж������κε�λ�Ƿ���ײ
    ����:
    ����ֵ:
        1��ʾ�߷�����ײ
        0��ʾ��û�з�����ײ

*/
bool checkCollision();
/*
    ������: ����
    ����: �ж��������ʳ����ײ ͨ����ɫ���� buff ��debuffЧ��
    ����:
    ����ֵ:
*/
int checkFood();
/*
    ������: ��˹��
    ����: �������ʳ����ײ������䳤
    ����:
    ����ֵ:
*/
void snakeGrow();
/*
    ������: �ź�
    ����: �ж�ײ������ʳ���������λ
    ����:
    ����ֵ:
        0��ʾû��ײ��
        1��ʾײ����
*/
int checkOtherCollision();
/*
    ������: ����
    ����: ����checkCollision�������ʳ����ײ ����յ�ǰʳ��
    ����:
    ����ֵ:
        1��ʾ�߷�����ײ
        0��ʾ��û�з�����ײ

*/
bool clearFood();
/*
    ������: ����
    ����: ���߼���
          �ڵ���ģʽ�� ��E���м���
          ��˫��ģʽ�� �����¼������ʹ��1���м���
    ����:
    ����ֵ:
*/
void accelerate();
/*
    ������: ����
    ����: ����checkCollision()����1ʱ
            �ж���ײ��������ʲô
            �����food ������Ч1
            ������ ������Ч2 ��ʾײǽ��������
    ����:
    ����ֵ:
*/
void playCollisionSound();
/*
    ������: ����
    ����: ��������
    ����:
    ����ֵ:
*/
int playMusic(int choose);
int stopMusic();
/*
    ������: ����
    ����: ����Ϸ����ʱ ��¼score���ı��ļ�
    ����:
    ����ֵ:
*/
void writeScore();
/*
    ������: ����
    ����: �������а�ʱ����ȡ�ı��ļ��еķ�����Ϣ
    ����:
    ����ֵ:
*/
void readScore();
void gotoXY(int x, int y);// ��������, ������ƶ���ָ������
void setPrintColor(int color); // ������ʾָ������

// -------------------- view�������� --------------------

/*
    ������: MADAO
    ����: չʾѡ��, ��ҿ���������ѡ�������Ϸ, �������û����а�����˳���Ϸ
           ����ڸý���ͨ��ws�ƶ����, �س�ȷ��ѡ��
        ������Ϸ: ������Ϸ���溯��choiceView();
        ��������: ����gameSet();
        �������а�:����leaderboard();
        �˳���Ϸ: ����exit(0);
*/
void menuView();
/*
    ������: ����
    ����: չʾѡ��, ��ҿ���������ѡ����Ϸģʽ
            �����޾�
            ˫���޾�
            ����ڸý���ͨ��ws�ƶ����, �س�ȷ��ѡ��
            ��esc  ������һ��(������ҳ)
            �з���ֵ ����ģʽʱ���� 1 ˫��ģʽʱ����2
        ������Ϸ: ������Ϸ���溯��gameView();
        ������һ��: ����menuView();
*/
int choiceView();
/*
    ������: �ź�
    ����: ��Ϸ����
            ��ҿ���ͨ��ws�ƶ����
            ad�޸�ѡ��
            �޸�̰������ɫ
            �޸���Ч��������Ϸ���ֺ���Ч�Ŀ����رա������ĵ��ڡ��������ֵ�ѡ��
            esc�˳�����

*/
void gameSet();
/*
    ������: ��ҹ
    ����: ��ʼ�����ɵ�ͼ ����ǽ�ں��ϰ��� �̶�λ��������ʵ��
    �ֱ������ϽǺ����Ͻ�չʾ˫������ �����Ϸ����м�չʾ����ʱ������ʱ
    ����: void
    ����ֵ: void
*/
void gameView_ShowMap();
/*
    ������: ����
    ����: ����flag��ֵ  ��ӡ��Ϸʤ������  �û����԰�������ص����˵�
    ����: void
    ����ֵ: void
*/
int winView();
/*
    ������: ��˹��
    ����: ��Ϸ��������
        ��ʼ����Ϸ����(���ú���init())
        ���������������ߵķ���
    ����: void
    ����ֵ: void
*/
void gameView();
/*
    ������: kami
    ����: ��Ϸ��ͣ���� ��ͣ����
    ����WS�ƶ�ѡ���꣬��enterȷ��
    ������Ϸ������gameview();
    ������Ϸ���ã�����gameSet();
    �˳���Ϸ������menuView();
    ����: void
    ����ֵ: void
*/
void pauseView();
/*
    ������: ����
    ����: ���а����
    ��ҿ���ͨ��ad��ҳ
    esc�˳����а�
    �˳���Ϸ������menuView();
    ����: void
    ����ֵ: void
*/
void leaderboard();