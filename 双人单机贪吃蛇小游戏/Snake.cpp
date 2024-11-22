#include "Snake.h"
// -------------------- service函数定义 --------------------

void init() {
    // 初始化蛇A
    snakeA.length = 3;
    snakeA.direction = 'd'; // 默认向右
    snakeA.score = 0;

    // 为蛇A的身体分配内存并初始化
    snakeA.body = (struct BODY*)malloc(sizeof(struct BODY) * snakeA.length);
    for (int i = 0; i < snakeA.length; i++) {
        snakeA.body[i].x = 5 - i; // 蛇A初始位置
        snakeA.body[i].y = 5;
    }
    if (gameMode == 2) {
        // 初始化蛇B
        snakeB.length = 3;
        snakeB.direction = 'd'; // 默认向左
        snakeB.score = 0;

        // 为蛇B的身体分配内存并初始化
        snakeB.body = (struct BODY*)malloc(sizeof(struct BODY) * snakeB.length);
        for (int i = 0; i < snakeB.length; i++) {
            snakeB.body[i].x = 5 - i; // 蛇B初始位置
            snakeB.body[i].y = 15;
        }
    }
    generateFood();// 生成食物
    for (int i = 1; i <= 60; i++) {
        generateObstacle();
    }
}

void run() {
    // 蛇A移动
    for (int i = snakeA.length - 1; i > 0; i--) {
        snakeA.body[i].x = snakeA.body[i - 1].x;
        snakeA.body[i].y = snakeA.body[i - 1].y;
    }
    switch (snakeA.direction) {
    case 'w':
        snakeA.body[0].y -= 1;
        break;
    case 's':
        snakeA.body[0].y += 1;
        break;
    case 'a':
        snakeA.body[0].x -= 1;
        break;
    case 'd':
        snakeA.body[0].x += 1;
        break;
    default:
        break;
    }

    // 蛇B移动
    for (int i = snakeB.length - 1; i > 0; i--) {
        snakeB.body[i].x = snakeB.body[i - 1].x;
        snakeB.body[i].y = snakeB.body[i - 1].y;
    }
    switch (snakeB.direction) {
    case 'w':
        snakeB.body[0].y -= 1;
        break;
    case 's':
        snakeB.body[0].y += 1;
        break;
    case 'a':
        snakeB.body[0].x -= 1;
        break;
    case 'd':
        snakeB.body[0].x += 1;
        break;
    default:
        break;
    }
}

//void changeDirection() {
//    bool is_input = 0, going = 1;
//    int input = 0;
//    while (going)
//    {
//        is_input = _kbhit();
//        if (is_input)
//        {
//            input = _getch();
//            switch (input)
//            {
//            case 119:
//            case 87:
//                if (snakeA.direction == 's')
//                    break;
//                else snakeA.direction = 'w';
//                break;
//            case 97:
//            case 65:
//                if (snakeA.direction == 'd')
//                    break;
//                else snakeA.direction = 'a';
//                break;
//            case 115:
//            case 83:
//                if (snakeA.direction == 'w')
//                    break;
//                else snakeA.direction = 's';
//                break;
//            case 100:
//            case 68:
//                if (snakeA.direction == 'a')
//                    break;
//                else snakeA.direction = 'd';
//                /*
//                手动加速不好做，能整体运行后再设计和调整
//                */
//            case 27:
//                pauseView();
//                break;
//            case 'e':
//            case 'E':
//            case 1:
//                break;
//            case 72:
//                if (snakeB.direction == 's') break;
//                else snakeB.direction = 'w';
//                break;
//            case 80:
//                if (snakeB.direction == 'w') break;
//                else snakeB.direction = 's';
//                break;
//            case 75:
//                if (snakeB.direction == 'd') break;
//                else snakeB.direction = 'a';
//            case 77:
//                if (snakeB.direction == 'a') break;
//                else snakeB.direction = 'd';
//                break;
//            }
//        }
//    }
//}

void generateObstacle()//每次生成一个
{
    bool ok = 0;
    int len1 = snakeA.length, len2 = snakeB.length;
    int px, py;
    while (!ok)
    {
        px = rand() % 58 + 1;//[1,58]
        py = rand() % 23 + 1;//[1,23]
        //食物
        if (px == food.x && py == food.y) continue;
        //障碍
        int f = 0;
        for (int i = 0; i < OBSTACLE_COUNT && !f; i++)
            if (px == obstacles[i].x && py == obstacles[i].y)
                f = 1;
        //蛇
            //避免生成在脸上
        if (abs(snakeA.body[0].x - px) + abs(snakeA.body[0].y - py) < 4) f = 1;
        for (int i = 0; i < len1 && !f; i++)
            if (snakeA.body[i].x == px && snakeA.body[i].y == py)
                f = 1;
        if (gameMode == 2)
        {
            if (abs(snakeB.body[0].x - px) + abs(snakeB.body[0].y - py) < 4) f = 1;
            for (int i = 0; i < len2 && !f; i++)
                if (snakeB.body[i].x == px && snakeB.body[i].y == py)
                    f = 1;
        }
        if (!f) ok = 1;
    }

    obstacles[OBSTACLE_COUNT++] = { px,py };
}

void generateFood()//判定吃到食物时调用本函数
{
    int px, py;
    int len1 = snakeA.length, len2 = snakeB.length;
    bool ok = 0;
    while (!ok)
    {
        px = rand() % 58 + 1;//[1,58]
        py = rand() % 23 + 1;//[1,23]
        //障碍
        int f = 0;
        for (int i = 0; i < OBSTACLE_COUNT && !f; i++)
            if (px == obstacles[i].x && py == obstacles[i].y)
                f = 1;
        //蛇
        for (int i = 0; i < len1 && !f; i++)
            if (snakeA.body[i].x == px && snakeA.body[i].y == py)
                f = 1;
        if (gameMode == 2)
            for (int i = 0; i < len2 && !f; i++)
                if (snakeB.body[i].x == px && snakeB.body[i].y == py)
                    f = 1;
        if (!f) ok = 1;
    }
    string col = (rand() % 2 ? "green" : "red");
    food = { px,py,col };
}

int isWin()//0 游戏继续 1 A获胜/B失败 2 B获胜/A失败/游戏结束(单人) 3平局
{
    int len1 = snakeA.length, px = snakeA.body[0].x, py = snakeA.body[0].y;
    //墙
    if (!px || px == 59 || !py || py == 24)
    {
        playMusic(2);
        return 2;
    }
    //A身
    for (int i = 1; i < len1; i++)
        if (snakeA.body[i].x == px && snakeA.body[i].y == py)
        {
            playMusic(2);
            return 2;
        }
    //障碍
    for (int i = 0; i < OBSTACLE_COUNT; i++)
        if (obstacles[i].x == px && obstacles[i].y==py)
        {
            playMusic(2);
            return 2;
        }
    if (gameMode == 2)
    {
        int len2 = snakeB.length, ppx = snakeB.body[0].x, ppy = snakeB.body[0].y;
        //拼分
        if (px == ppx && py == ppy)
        {
            int score1 = snakeA.score, score2 = snakeB.score;
            if (score1 > score2)
            {
                playMusic(2);
                return 1;
            }
            else if (score1 < score2)
            {
                playMusic(2);
                return 2;
            }
            else
            {
                playMusic(2);
                return 3;
            }
        }
        //A碰到B
        for (int i = 1; i < len2; i++)
            if (px == snakeB.body[i].x && py == snakeB.body[i].y)
            {
                playMusic(2);
                return 2;
            }
        //墙
        if (!ppx || ppx == 59 || !ppy || ppy == 24)
        {
            playMusic(2);
            return 1;
        }
        //B身
        for (int i = 1; i < len2; i++)
            if (snakeB.body[i].x == ppx && snakeB.body[i].y == ppy)
            {
                playMusic(2);
                return 1;
            }
        //障碍
        for (int i = 0; i < OBSTACLE_COUNT; i++)
            if (obstacles[i].x == ppx && obstacles[i].y == ppy)
            {
                playMusic(2);
                return 1;
            }
    }
    return 0;
}

bool checkCollision()
{   //蛇A的蛇头碰到蛇B
    while (snakeB.length > 1)
    {
        for (int i = 0; i + 1 <= snakeB.length; i++) {
            if (snakeA.body[0].x == snakeB.body[i].x && snakeA.body[0].y == snakeB.body[i].y)
            {
                return 1;
            }
        }
    }
    //蛇B的蛇头碰到蛇A
    while (snakeA.length > 1)
    {
        for (int i = 0; i <= snakeA.length; i++) {
            if (snakeB.body[0].x == snakeA.body[i].x && snakeB.body[0].y == snakeA.body[i].y)
            {
                return 1;
            }
        }
    }
    //蛇A碰到obstacle
    for (int j = 0; j <= 9; j++)
    {
        if (snakeA.body[0].x == obstacles[j].x && snakeA.body[0].y == obstacles[j].y)
            return 1;
    }
    //蛇A碰到墙
    if (snakeA.body[0].x == 25 || snakeA.body[0].x == 0 || snakeA.body[0].y == 60 || snakeA.body[0].y == 0)
    {
        return 1;
    }
    //蛇A碰到food
    else if (snakeA.body[0].x == food.x && snakeA.body[0].y == food.y)//food为食物的数组
    {
        return 1;
    }
    //蛇A碰到自己的身体
    else if (snakeA.length > 1) {
        for (int i = 1; i <= snakeA.length; i++) {
            if (snakeA.body[0].x == snakeA.body[i].x && snakeA.body[0].y == snakeA.body[i].y)
            {
                return 1;
            }
        }
    }
    else { return 0; }
    //蛇B碰到obstacle
    for (int j = 0; j <= 9; j++)
    {
        if (snakeB.body[0].x == obstacles[j].x && snakeB.body[0].y == obstacles[j].y)
            return 1;
    }
    //蛇B碰到墙
    if (snakeB.body[0].x == 25 || snakeB.body[0].x == 0 || snakeB.body[0].y == 60 || snakeB.body[0].y == 0)
    {
        return 1;
    }
    //蛇B碰到food
    else if (snakeA.body[0].x == food.x && snakeA.body[0].y == food.y)//food食物的数组
    {
        return 1;
    }
    //蛇B碰到自己的身体
    else if (snakeB.length > 1) {
        for (int i = 1; i <= snakeB.length; i++) {
            if (snakeB.body[0].x == snakeB.body[i].x && snakeB.body[0].y == snakeB.body[i].y)
            {
                return 1;
            }
        }
    }
    else { return 0; }

}

int checkFood()//返回值非0则吃到东西
{
    struct SNAKE* snake = &snakeA;
    struct SNAKE* snake1 = &snakeB;

    if (snake->body->x == food.x && snake->body->y == food.y) return 1;
    if (gameMode == 2 && snake1->body->x == food.x && snake1->body->y == food.y) return 1;
    return 0;
}

void snakeGrow()//调用了就一定有食物被吃
{
    if (snakeA.body[0].x == food.x && snakeA.body[0].y == food.y)
    {
        snakeA.score += 1 + (food.color == "red");
        snakeA.length++;
        snakeA.body = (struct BODY*)realloc(snakeA.body, sizeof(struct BODY) * (snakeA.length));
        snakeA.body[snakeA.length - 1].x = snakeA.body[snakeA.length - 2].x + 1;
        snakeA.body[snakeA.length - 1].y = snakeA.body[snakeA.length - 2].y + 1;
        //if (snakeA.score % 15 > 13) generateObstacle();
    }
    else
    {
        snakeB.score += 1 + (food.color == "red");
        snakeB.length++;
        snakeB.body = (struct BODY*)realloc(snakeB.body, sizeof(struct BODY) * (snakeB.length));
        snakeB.body[snakeB.length - 1] = snakeB.body[snakeB.length - 2];
        snakeB.body[snakeB.length - 1].x = snakeB.body[snakeB.length - 2].x + 1;
        snakeB.body[snakeB.length - 1].y = snakeB.body[snakeB.length - 2].y + 1;
        //if (snakeB.score % 15 > 13) generateObstacle();
    }
}

int checkOtherCollision() {
    // 首先检查是否与任何单位相撞
    if (checkCollision()) {
        // 如果与某个单位相撞，进一步检查是否是食物
        if (checkFood() == 0) {
            // 如果不是食物，则表示撞到了其他单位
            return 1; // 返回1表示撞到了非食物的其他单位
        }
    }
    return 0; // 如果没有碰撞或碰撞的是食物，则返回0
}

bool clearFood() {
    if (checkCollision()) {
        if ((snakeA.body[0].x == food.x && snakeA.body[0].y == food.y) ||
            (snakeB.body[0].x == food.x && snakeB.body[0].y == food.y)) { // 蛇A或蛇B碰到食物
            food.x = -1; // 将食物位置设置为无效值
            food.y = -1;

            generateFood(); // 重新生成食物
            return true;
        }
    }
    return false;
}

void accelerate() {//按住即加速
    sleep_time = 5;
}


// 播放指定音乐
int playMusic(int choose) {
    if (!isMusic) return 0;
    wchar_t cmd[MAX_PATH + 10];
    if (choose >= 0 && choose <= 3) {
        if (choose == 0) {
            // 如果是背景音乐 则循环播放
            wsprintf(cmd, L"open %s alias viewBGM type mpegvideo", musicPath[0]);
            if (mciSendString(cmd, NULL, 0, NULL) != 0) {
                return 0;
            }
            if (mciSendString(L"play viewBGM repeat", NULL, 0, NULL) != 0) {
                return 0;
            }
        }
        else if (choose == 1) {
            // 如果是背景音乐 则循环播放
            wsprintf(cmd, L"open %s alias gameBGM type mpegvideo", musicPath[1]);
            if (mciSendString(cmd, NULL, 0, NULL) != 0) {
                return 0;
            }
            if (mciSendString(L"play gameBGM repeat", NULL, 0, NULL) != 0) {
                return 0;
            }
        }
        else {
            // 否则 只播放一次
            wsprintf(cmd, L"play %s", musicPath[choose]);
            if (mciSendString(cmd, NULL, 0, NULL) != 0) {
                MessageBox(NULL, L"Failed to play sound", L"Error", MB_OK);
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

void playCollisionSound() {
    static bool lastCollisionState = false; // 用于跟踪上一次的碰撞状态
    bool isCollided = checkOtherCollision();

    if (isCollided != lastCollisionState) {
        if (isCollided) {
            playMusic(2); // 播放蛇、墙壁或障碍物碰撞音效
        }
        else {
            playMusic(3); // 播放食物碰撞音效
        }
        lastCollisionState = isCollided; // 更新上一次的碰撞状态
    }
}

int stopMusic(int choose) {
    wchar_t cmd[MAX_PATH + 10];
    if (choose == 0) {
        return mciSendString(L"close viewBGM", NULL, 0, NULL);
    }
    else if (choose == 1) {
        return mciSendString(L"close gameBGM", NULL, 0, NULL);
    }
    else if (choose >= 0 && choose <= 3) {
        wsprintf(cmd, L"stop %s", musicPath[choose]);
        return mciSendString(cmd, NULL, 0, NULL);
    }
    return -1; // Return an error code if choose is out of range
}

void writeScore(int newScore) {//该函数实现了检查分数文件是否存在、读取文件内容、添加分数并对分数排序、写回文件等一系列完整的操作
    const string globalFileName = "score_source.txt"; // 用于记录分数的全局文件名
    vector<int> scores; // 用于存储分数的容器

    // 检查文件是否存在，如果不存在则创建一个空文件
    ifstream fileCheck(globalFileName);//创建一个输入文件流对象 fileCheck，并尝试打开 globalFileName 指定的文件。如果文件打开成功，fileCheck.is_open() 返回 true；如果失败，返回 false。
    if (!fileCheck.is_open()) {//检查文件是否未能打开
        ofstream fileCreate(globalFileName);
        if (!fileCreate.is_open()) {
            cerr << "无法创建分数文件。" << endl;
            return;
        }
        fileCreate.close(); // 创建空文件后关闭
    }
    else {
        // 如果文件存在，读取文件中的所有分数
        string line;
        while (getline(fileCheck, line)) {
            scores.push_back(stoi(line)); // 将字符串转换为整数并添加到容器中
        }
        fileCheck.close();
    }

    // 添加新的分数
    scores.push_back(newScore);

    // 对分数进行降序排序
    sort(scores.begin(), scores.end(), greater<int>());//使用 sort 函数对 scores 向量进行排序。greater<int>() 作为第三个参数，指定排序为降序。

    // 清空原文件内容
    ofstream fileWrite(globalFileName);
    if (fileWrite.is_open()) {
        // 将排序后的分数写回文件
        for (int score : scores) {//遍历 scores 向量中的每个分数。
            fileWrite << score << endl;
        }
        fileWrite.close();
    }
    else {
        cerr << "无法打开分数文件进行写入。" << endl;
    }
}

void readScore() {//将记录分数的文件复制一份用于后续操作
    // 定义源文件和目标文件的文件名
    string srcFileName = "score_source.txt";
    string destFileName = "scores.txt";

    // 检查源文件是否存在
    ifstream srcFile(srcFileName);
    if (!srcFile.is_open()) {
        cout << "无法打开源分数文件：" << srcFileName << endl;
        return;
    }

    // 尝试创建或覆盖目标文件
    ofstream destFile(destFileName);
    if (!destFile.is_open()) {
        cout << "无法创建目标分数文件：" << destFileName << endl;
        srcFile.close();
        return;
    }

    string line;
    while (getline(srcFile, line)) {
        destFile << line << endl;
    }

    srcFile.close();
    destFile.close();

    cout << "分数文件复制完成。" << endl;
}

// -------------------- view 函数声明 --------------------//

int main() {
    colorA = "blue", colorB = "yellow";
    menuView();
}

void ShowCursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 20, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}//隐藏光标

void gotoXY(int x, int y) {  // 传入坐标, 将光标移动到指定坐标
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setPrintColor(int color) {  // 高亮显示指定文字
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void menuView() {
    int menuChoice = 0;
    system("cls");
    ShowCursor();
    current_music = 0;
    playMusic(current_music);

    while (true) {
        gotoXY(50, 4);
        cout << "主菜单";
        if (menuChoice == 0) setPrintColor(0x9f);
        gotoXY(50, 7);
        cout << "进入游戏";
        setPrintColor(0x0f);
        if (menuChoice == 1) setPrintColor(0x9f);
        gotoXY(50, 10);
        cout << "进入设置";
        setPrintColor(0x0f);
        if (menuChoice == 2) setPrintColor(0x9f);
        gotoXY(50, 13);
        cout << "排行榜";
        setPrintColor(0x0f);
        if (menuChoice == 3) setPrintColor(0x9f);
        gotoXY(50, 16);
        cout << "退出游戏";
        setPrintColor(0x0f);
        gotoXY(36, 21);
        cout << "通过 ws 键上下移动，按 Enter 键确认";
        char input = _getch();
        switch (input) {
        case 'w':
            menuChoice -= 1;
            if (menuChoice == -1) menuChoice = 3;
            break;
        case 's':
            menuChoice = (menuChoice + 1) % 4;
            break;
        case '\r':
            switch (menuChoice) {
            case 0:
                choiceView();
                break;
            case 1:
                gameSet();
                break;
            case 2:
                leaderboard();
                break;
            case 3:
                exit(0);
                break;
            }
            break;
        }
    }
}

int choiceView() {
    int userChoose = 0;
    system("cls");
    ShowCursor();
    while (true) {
        gotoXY(50, 4);
        cout << "游戏模式选择";
        if (userChoose == 0) setPrintColor(0x9f);
        gotoXY(50, 7);
        cout << "单人无尽";
        setPrintColor(0x0f);
        if (userChoose == 1) setPrintColor(0x9f);
        gotoXY(50, 10);
        cout << "双人无尽";
        setPrintColor(0x0f);
        if (userChoose == 2) setPrintColor(0x9f);
        gotoXY(50, 13);
        cout << "返回上一级";
        setPrintColor(0x0f);
        gotoXY(36, 21);
        cout << "通过 ws 键上下移动，按 Enter 键确认";
        char input = _getch();
        switch (input) {
        case 'w':
            userChoose -= 1;
            if (userChoose == -1) userChoose = 2;
            break;
        case 's':
            userChoose = (userChoose + 1) % 3;
            break;
        case '\r':
            switch (userChoose) {
            case 0:  // 单人无尽
                gameMode = 1;
                gameView();
                break;
            case 1:  // 双人无尽
                gameMode = 2;
                gameView();
                break;
            case 2:  // 返回上一级
                menuView();
                break;
            }
            break;
        }
    }
}

int winView() {
    system("cls"); // 清屏
    ShowCursor();
    gotoXY(50, 5);
    cout << "游戏结束！" << endl;
    // 根据游戏模式显示胜利信息
    switch (gameMode) {
        case 1: // 单人模式
            gotoXY(50, 8);
                cout << "分数: " << snakeA.score << endl;
                // 调用记录函数记录分数
                writeScore(snakeA.score);
                
                cout << "按任意键返回主菜单..." << endl;
                Sleep(2000);
                while (!_kbhit()) {} // 等待按键
                _getch();
                menuView(); // 返回主菜单
                break;
        case 2: // 双人模式  
                // 根据 flag 的值显示胜利信息
                flag = isWin();
                if (flag == 1) {
                    cout << "恭喜A蛇获得胜利！" << endl;
                }
                else if (flag == 2) {
                    cout << "恭喜B蛇获得胜利！" << endl;
                }
                else {
                    cout << "游戏平局！" << endl;
                }
                // 显示分数
                cout << "A蛇分数: " << snakeA.score << endl;
                cout << "B蛇分数: " << snakeB.score << endl;

                writeScore(snakeA.score);
                writeScore(snakeB.score);
                
                cout << "按任意键返回主菜单..." << endl;
                Sleep(2000);
                while (!_kbhit()) {} // 如果按了键盘
                _getch();
                menuView(); // 返回主菜单
                break;
        case 0: // 退出游戏
            cout << "退出游戏。" << endl;
            return 1; // 确保有返回值
        default:
            cout << "无效选择，请重新选择。" << endl;
            return 1; // 确保有返回值
        }
}

void gameSet() {
    int userChoose = 0; // 用户当前选择
    bool staticc = 0;//enter固定行
    while (true) {
        system("cls");
        gotoXY(50, 4);
        cout << "游 戏 设 置";

        if (userChoose == 0)
            if (staticc) setPrintColor(0x2f);
            else setPrintColor(0x9f);
        else setPrintColor(0x0f);
        gotoXY(50, 7);
        cout << "颜 色 A: " << colorA;

        if (userChoose == 1)
            if (staticc) setPrintColor(0x2f);
            else setPrintColor(0x9f);
        else setPrintColor(0x0f);
        gotoXY(50, 10);
        cout << "颜 色 B: " << colorB;
        setPrintColor(0x0f);

        if (userChoose == 2)
            if (staticc) setPrintColor(0x2f);
            else setPrintColor(0x9f);
        gotoXY(50, 13);
        cout << "音 效： " << (isSound ? "开" : "关");
        setPrintColor(0x0f);

        if (userChoose == 3)
            if (staticc) setPrintColor(0x2f);
            else setPrintColor(0x9f);
        gotoXY(50, 16);
        cout << "音 乐： " << (isMusic ? "开" : "关");
        setPrintColor(0x0f);

        gotoXY(20, 21);
        cout << "通过 ws 键上下移动，通过 ad 键选择（颜色只能向右），按 Enter 键确认，按 Esc 键退出";
        gotoXY(48, 23);
        cout << "选中选项变绿底";
        char input;
        if (staticc)
        {
            input = _getch();
            if (input == 13) staticc = !staticc;
            else if(staticc)
            switch (userChoose) {
            case 0: // 修改颜色 A
                if (input == 'd')
                    if (colorA == "red") colorA = "yellow";
                    else if (colorA == "yellow") colorA = "green";
                    else if (colorA == "green") colorA = "blue";
                    else if (colorA == "blue") colorA = "purple";
                    else if (colorA == "purple") colorA = "cyan";
                    else if (colorA == "cyan") colorA = "white";
                    else if (colorA == "white") colorA = "red";
                break;
            case 1: // 修改颜色 B
                if(input=='d')
                    if (colorB == "red") colorB = "yellow";
                    else if (colorB == "yellow") colorB = "green";
                    else if (colorB == "green") colorB = "blue";
                    else if (colorB == "blue") colorB = "purple";
                    else if (colorB == "purple") colorB = "cyan";
                    else if (colorB == "cyan") colorB = "white";
                    else if (colorB == "white") colorB = "red";
                    break;
            case 2: // 修改音效
                if(input=='a' || input == 'd')
                    isSound = !isSound;
                    break;
            case 3: // 修改音乐
                if(input=='a' || input == 'd')
                    isMusic = !isMusic;
                    break;
            }
        }
        else {
            input = _getch();
            switch (input) {
            case 'w':
                userChoose -= 1;
                if (userChoose == -1) userChoose = 3;
                break;
            case 's':
                userChoose = (userChoose + 1) % 4;
                break;
            case 13:
                staticc = !staticc;
                break;
            case 27: // Esc 键退出设置
                if (going) pauseView();
                else menuView();
                break;
            }
        }
    }
}

void gameView_ShowMap() {
    //system("cls");
    gotoXY(DX+2, 1);
    cout << "玩家1分数: " << snakeA.score;
    if (gameMode == 2) gotoXY(DX+30,1),cout << "  玩家2分数: " << snakeB.score;
    cout << endl;
    gotoXY(DX + 65, 25);
    cout << "按空格暂停... ...";
    for (int i = 0; i < 25; i++) {

        for (int j = 0; j < 60; j++) {
            if (i == 0 || i == 24 || j == 0 || j == 59) {
                gotoXY(DX + j, DY + i);
                cout << "#"<<' '; // 墙壁
            }
            else if (i == food.y && j == food.x) {
                // 根据食物颜色打印
                if (food.color == "green") {
                    setPrintColor(0x0a); // 绿色
                }
                else {
                    setPrintColor(0x0c); // 红色
                }
                gotoXY(DX + j, DY + i);
                cout << "★"; // 食物
                setPrintColor(0x07); // 重置颜色为默认
            }
            else {
                bool printed = false; // 标志变量，用于标记是否打印过
                // 打印蛇A
                for (int k = 0; k < snakeA.length; k++) {
                    if (snakeA.body[k].x == j && snakeA.body[k].y == i) {
                        gotoXY(DX + j, DY + i);
                        int id = 0;
                        while (id < 7 && col[id] != snakeA.color) id++;
                        switch (id)
                        {
                        case 0:
                            setPrintColor(0x0c);
                            break;
                        case 1:
                            setPrintColor(0x0e);
                            break;
                        case 2:
                            setPrintColor(0x0a);
                            break;
                        case 3:
                            setPrintColor(0x09);
                            break;
                        case 4:
                            setPrintColor(0x0d);
                            break;
                        case 5:
                            setPrintColor(0x0b);
                            break;
                        case 6:
                            setPrintColor(0x07);
                            break;
                        }
                        cout << "*"; // 蛇A
                        printed = true;
                        break;
                    }
                }

                // 打印蛇B
                if(gameMode==2)
                if (!printed) { // 只在没有打印蛇A的情况下检查蛇B
                    for (int k = 0; k < snakeB.length; k++) {
                        if (snakeB.body[k].x == j && snakeB.body[k].y == i) {
                            gotoXY(DX + j, DY + i);
                            int id = 0;
                            while (id < 7 && col[id] != snakeB.color) id++;
                            switch (id)
                            {
                            case 0:
                                setPrintColor(0x0c);
                                break;
                            case 1:
                                setPrintColor(0x0e);
                                break;
                            case 2:
                                setPrintColor(0x0a);
                                break;
                            case 3:
                                setPrintColor(0x09);
                                break;
                            case 4:
                                setPrintColor(0x0d);
                                break;
                            case 5:
                                setPrintColor(0x0b);
                                break;
                            case 6:
                                setPrintColor(0x07);
                                break;
                            }
                            cout << "O"; // 蛇B
                            printed = true;
                            break;
                        }
                    }
                }

                // 打印障碍物
                if (!printed) { // 只在没有打印过蛇情况下检查障碍物
                    for (int k = 0; k < OBSTACLE_COUNT; k++) {
                        if (obstacles[k].x == j && obstacles[k].y == i) {
                                    gotoXY(DX + j, DY + i);
                                    cout << "#"; // 障碍物
                                    printed = true;
                                    break; // 
                        }
                    }
                }

                // 如果没有打印蛇、食物或障碍物，则打印空格
                if (!printed) {
                    gotoXY(DX + j, DY + i);
                    cout << " "; // 空地
                }
            }
            setPrintColor(0x07); // 找完一个位置就重置颜色为默认
        }
    }

}

void pauseView() {
    Sleep(500);
    //用户当前选择
    int userChoose = 0;
    system("cls");
    //打印边框？
    while (1) {
        gotoXY(50, 4);
        cout << "游 戏 已 暂 停";
        if (userChoose == 0) setPrintColor(0x9f);
        gotoXY(50, 7);
        cout << "继续游戏";
        setPrintColor(0x0f);
        if (userChoose == 1) setPrintColor(0x9f);
        gotoXY(50, 10);
        cout << "游戏设置";
        setPrintColor(0x0f);
        if (userChoose == 2) setPrintColor(0x9f);
        gotoXY(50, 13);
        cout << "返回菜单";
        setPrintColor(0x0f);
        gotoXY(36, 21);
        cout << "通过 ws 键上下移动，按 Enter 键确认";
        char input = _getch();
        switch (input) {
        case 'w':
            userChoose -= 1;
            if (userChoose == -1)userChoose = 2;
            break;

        case 's':
            userChoose = (userChoose + 1) % 3;
            break;

        case '\r':
            switch (userChoose) {
            case 0:  //返回游戏
                gameView();
                break;
            case 1:  // 游戏设置
                gameSet();
                break;
            case 2:  // 返回菜单
                going = 0;
                menuView();
                break;
            }
            break;
        }
    }
}

void gameView()
{
    system("cls");
    ShowCursor();
    if(!going) init();
    gameView_ShowMap();
    stopMusic(current_music);
    current_music = 1;
    playMusic(current_music);
    //移动
    bool is_input = 0;
    int input = 0;
    going = 1;
    while (going)
    {
        is_input = _kbhit();
        if (is_input)
        {
            input = _getch();
            switch (input)
            {
            case 119:
            case 87:
                if (snakeA.direction == 's')
                    break;
                else snakeA.direction = 'w';
                break;
            case 97:
            case 65:
                if (snakeA.direction == 'd')
                    break;
                else snakeA.direction = 'a';
                break;
            case 115:
            case 83:
                if (snakeA.direction == 'w')
                    break;
                else snakeA.direction = 's';
                break;
            case 100:
            case 68:
                if (snakeA.direction == 'a')
                    break;
                else snakeA.direction = 'd';
                break;
            case 32:
                pauseView();
                break;
            case 72:
                if (snakeB.direction == 's') break;
                else snakeB.direction = 'w';
                break;
            case 80:
                if (snakeB.direction == 'w') break;
                else snakeB.direction = 's';
                break;
            case 75:
                if (snakeB.direction == 'd') break;
                else snakeB.direction = 'a';
            case 77:
                if (snakeB.direction == 'a') break;
                else snakeB.direction = 'd';
                break;
            case 116:
            case 47:
                accelerate();
                break;
            }
        }
        run();
        gameView_ShowMap();
        if (isWin())
        {
            going = 0;
            winView();
        }
        else
        {
            //playCollisionSound();
            if (checkFood()) playMusic(3),snakeGrow(), generateFood();
        }
        Sleep(sleep_time);
        sleep_time = 150;
    }
}

void leaderboard()
{
    ShowCursor();
    readScore();//假设readscore是将源文件名为 scores_source.txt，复制为一个新文件名为 scores.txt，我们此后及对score.txt文件进行操作
    ifstream file("scores.txt");//假设前期的记录分数函数已经生成了一个每行只有一个分数（并且已经排好了大小顺序）的记录文件
    if (!file.is_open()) {
        cout << "无法打开分数文件。" << endl;
        return;
    }

    system("cls");//清屏为打印排行榜做准备
    cout << "排行榜" << endl;

    int page = 0;
    int scores_per_page = 10; // 假设每页显示10个分数
    string line;
    int score_count = 0;

    // 计算总分数数量
    file.seekg(0, ios::beg); // 回到文件开头
    while (getline(file, line)) {//循环读取文件中记录总条数
        score_count++;
    }
    int total_page = score_count / scores_per_page;//总条数除以每页个数得到总页数
    if (score_count % scores_per_page != 0)//确保了即使最后一页没有完全填满，也会被计算在内
    {
        total_page++;
    }



    // 等待用户输入
    char input;
    do {
        system("cls"); // 清屏
        // 显示排行榜头部
        cout << "=========================" << endl;
        cout << "  排名   分数" << endl;
        cout << "=========================" << endl;
        score_count = page * scores_per_page; // 重置分数计数器到当前页的起始分数

        // 显示当前页的分数
        file.clear(); // 清除文件流状态
        file.seekg(0, ios::beg); // 回到文件开头
        while (getline(file, line) && score_count < (page + 1) * scores_per_page) {//while用来检测是否属于下一页之前的记录
            if (score_count >= page * scores_per_page) {//if用来筛选属于当前页的记录才用于打印
                cout << "   " << (score_count - page * scores_per_page + 1);
                if (score_count - page * scores_per_page + 1 < 10) cout << ' ';
                cout << "     " << line << endl;
            }
            score_count++;
        }

        // 显示排行榜尾部
        cout << "=========================" << endl;
        cout << "按 'a' 向前翻页，按 'd' 向后翻页，按 Esc 退出排行榜" << endl;
        cout << "=========================" << endl;

        input = _getch(); // 获取用户输入
        switch (input) {
        case 'a': // 向前翻页
            if (page > 0) //保证了page的有效性
            {
                page--;
            }
            break;
        case 'd': // 向后翻页
            if (page < total_page - 1)//保证了page的有效性
            {
                page++;
            }
            break;
        case 27: // Esc 键
            break; // 退出循环
        default:
            break; // 忽略其他输入
        }
    } while (input != 27); // 循环直到用户按下 Esc 键

    file.close(); // 关闭文件
    remove("scores.txt");//readscore拷贝的文件
    menuView();//当用户输入esc，停止循环关闭文件删除拷贝再调用menuview回到主菜单
}