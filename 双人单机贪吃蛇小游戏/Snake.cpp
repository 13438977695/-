#include "Snake.h"
// -------------------- service�������� --------------------

void init() {
    // ��ʼ����A
    snakeA.length = 3;
    snakeA.direction = 'd'; // Ĭ������
    snakeA.score = 0;

    // Ϊ��A����������ڴ沢��ʼ��
    snakeA.body = (struct BODY*)malloc(sizeof(struct BODY) * snakeA.length);
    for (int i = 0; i < snakeA.length; i++) {
        snakeA.body[i].x = 5 - i; // ��A��ʼλ��
        snakeA.body[i].y = 5;
    }
    if (gameMode == 2) {
        // ��ʼ����B
        snakeB.length = 3;
        snakeB.direction = 'd'; // Ĭ������
        snakeB.score = 0;

        // Ϊ��B����������ڴ沢��ʼ��
        snakeB.body = (struct BODY*)malloc(sizeof(struct BODY) * snakeB.length);
        for (int i = 0; i < snakeB.length; i++) {
            snakeB.body[i].x = 5 - i; // ��B��ʼλ��
            snakeB.body[i].y = 15;
        }
    }
    generateFood();// ����ʳ��
    for (int i = 1; i <= 60; i++) {
        generateObstacle();
    }
}

void run() {
    // ��A�ƶ�
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

    // ��B�ƶ�
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
//                �ֶ����ٲ����������������к�����ƺ͵���
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

void generateObstacle()//ÿ������һ��
{
    bool ok = 0;
    int len1 = snakeA.length, len2 = snakeB.length;
    int px, py;
    while (!ok)
    {
        px = rand() % 58 + 1;//[1,58]
        py = rand() % 23 + 1;//[1,23]
        //ʳ��
        if (px == food.x && py == food.y) continue;
        //�ϰ�
        int f = 0;
        for (int i = 0; i < OBSTACLE_COUNT && !f; i++)
            if (px == obstacles[i].x && py == obstacles[i].y)
                f = 1;
        //��
            //��������������
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

void generateFood()//�ж��Ե�ʳ��ʱ���ñ�����
{
    int px, py;
    int len1 = snakeA.length, len2 = snakeB.length;
    bool ok = 0;
    while (!ok)
    {
        px = rand() % 58 + 1;//[1,58]
        py = rand() % 23 + 1;//[1,23]
        //�ϰ�
        int f = 0;
        for (int i = 0; i < OBSTACLE_COUNT && !f; i++)
            if (px == obstacles[i].x && py == obstacles[i].y)
                f = 1;
        //��
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

int isWin()//0 ��Ϸ���� 1 A��ʤ/Bʧ�� 2 B��ʤ/Aʧ��/��Ϸ����(����) 3ƽ��
{
    int len1 = snakeA.length, px = snakeA.body[0].x, py = snakeA.body[0].y;
    //ǽ
    if (!px || px == 59 || !py || py == 24)
    {
        playMusic(2);
        return 2;
    }
    //A��
    for (int i = 1; i < len1; i++)
        if (snakeA.body[i].x == px && snakeA.body[i].y == py)
        {
            playMusic(2);
            return 2;
        }
    //�ϰ�
    for (int i = 0; i < OBSTACLE_COUNT; i++)
        if (obstacles[i].x == px && obstacles[i].y==py)
        {
            playMusic(2);
            return 2;
        }
    if (gameMode == 2)
    {
        int len2 = snakeB.length, ppx = snakeB.body[0].x, ppy = snakeB.body[0].y;
        //ƴ��
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
        //A����B
        for (int i = 1; i < len2; i++)
            if (px == snakeB.body[i].x && py == snakeB.body[i].y)
            {
                playMusic(2);
                return 2;
            }
        //ǽ
        if (!ppx || ppx == 59 || !ppy || ppy == 24)
        {
            playMusic(2);
            return 1;
        }
        //B��
        for (int i = 1; i < len2; i++)
            if (snakeB.body[i].x == ppx && snakeB.body[i].y == ppy)
            {
                playMusic(2);
                return 1;
            }
        //�ϰ�
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
{   //��A����ͷ������B
    while (snakeB.length > 1)
    {
        for (int i = 0; i + 1 <= snakeB.length; i++) {
            if (snakeA.body[0].x == snakeB.body[i].x && snakeA.body[0].y == snakeB.body[i].y)
            {
                return 1;
            }
        }
    }
    //��B����ͷ������A
    while (snakeA.length > 1)
    {
        for (int i = 0; i <= snakeA.length; i++) {
            if (snakeB.body[0].x == snakeA.body[i].x && snakeB.body[0].y == snakeA.body[i].y)
            {
                return 1;
            }
        }
    }
    //��A����obstacle
    for (int j = 0; j <= 9; j++)
    {
        if (snakeA.body[0].x == obstacles[j].x && snakeA.body[0].y == obstacles[j].y)
            return 1;
    }
    //��A����ǽ
    if (snakeA.body[0].x == 25 || snakeA.body[0].x == 0 || snakeA.body[0].y == 60 || snakeA.body[0].y == 0)
    {
        return 1;
    }
    //��A����food
    else if (snakeA.body[0].x == food.x && snakeA.body[0].y == food.y)//foodΪʳ�������
    {
        return 1;
    }
    //��A�����Լ�������
    else if (snakeA.length > 1) {
        for (int i = 1; i <= snakeA.length; i++) {
            if (snakeA.body[0].x == snakeA.body[i].x && snakeA.body[0].y == snakeA.body[i].y)
            {
                return 1;
            }
        }
    }
    else { return 0; }
    //��B����obstacle
    for (int j = 0; j <= 9; j++)
    {
        if (snakeB.body[0].x == obstacles[j].x && snakeB.body[0].y == obstacles[j].y)
            return 1;
    }
    //��B����ǽ
    if (snakeB.body[0].x == 25 || snakeB.body[0].x == 0 || snakeB.body[0].y == 60 || snakeB.body[0].y == 0)
    {
        return 1;
    }
    //��B����food
    else if (snakeA.body[0].x == food.x && snakeA.body[0].y == food.y)//foodʳ�������
    {
        return 1;
    }
    //��B�����Լ�������
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

int checkFood()//����ֵ��0��Ե�����
{
    struct SNAKE* snake = &snakeA;
    struct SNAKE* snake1 = &snakeB;

    if (snake->body->x == food.x && snake->body->y == food.y) return 1;
    if (gameMode == 2 && snake1->body->x == food.x && snake1->body->y == food.y) return 1;
    return 0;
}

void snakeGrow()//�����˾�һ����ʳ�ﱻ��
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
    // ���ȼ���Ƿ����κε�λ��ײ
    if (checkCollision()) {
        // �����ĳ����λ��ײ����һ������Ƿ���ʳ��
        if (checkFood() == 0) {
            // �������ʳ����ʾײ����������λ
            return 1; // ����1��ʾײ���˷�ʳ���������λ
        }
    }
    return 0; // ���û����ײ����ײ����ʳ��򷵻�0
}

bool clearFood() {
    if (checkCollision()) {
        if ((snakeA.body[0].x == food.x && snakeA.body[0].y == food.y) ||
            (snakeB.body[0].x == food.x && snakeB.body[0].y == food.y)) { // ��A����B����ʳ��
            food.x = -1; // ��ʳ��λ������Ϊ��Чֵ
            food.y = -1;

            generateFood(); // ��������ʳ��
            return true;
        }
    }
    return false;
}

void accelerate() {//��ס������
    sleep_time = 5;
}


// ����ָ������
int playMusic(int choose) {
    if (!isMusic) return 0;
    wchar_t cmd[MAX_PATH + 10];
    if (choose >= 0 && choose <= 3) {
        if (choose == 0) {
            // ����Ǳ������� ��ѭ������
            wsprintf(cmd, L"open %s alias viewBGM type mpegvideo", musicPath[0]);
            if (mciSendString(cmd, NULL, 0, NULL) != 0) {
                return 0;
            }
            if (mciSendString(L"play viewBGM repeat", NULL, 0, NULL) != 0) {
                return 0;
            }
        }
        else if (choose == 1) {
            // ����Ǳ������� ��ѭ������
            wsprintf(cmd, L"open %s alias gameBGM type mpegvideo", musicPath[1]);
            if (mciSendString(cmd, NULL, 0, NULL) != 0) {
                return 0;
            }
            if (mciSendString(L"play gameBGM repeat", NULL, 0, NULL) != 0) {
                return 0;
            }
        }
        else {
            // ���� ֻ����һ��
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
    static bool lastCollisionState = false; // ���ڸ�����һ�ε���ײ״̬
    bool isCollided = checkOtherCollision();

    if (isCollided != lastCollisionState) {
        if (isCollided) {
            playMusic(2); // �����ߡ�ǽ�ڻ��ϰ�����ײ��Ч
        }
        else {
            playMusic(3); // ����ʳ����ײ��Ч
        }
        lastCollisionState = isCollided; // ������һ�ε���ײ״̬
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

void writeScore(int newScore) {//�ú���ʵ���˼������ļ��Ƿ���ڡ���ȡ�ļ����ݡ���ӷ������Է�������д���ļ���һϵ�������Ĳ���
    const string globalFileName = "score_source.txt"; // ���ڼ�¼������ȫ���ļ���
    vector<int> scores; // ���ڴ洢����������

    // ����ļ��Ƿ���ڣ�����������򴴽�һ�����ļ�
    ifstream fileCheck(globalFileName);//����һ�������ļ������� fileCheck�������Դ� globalFileName ָ�����ļ�������ļ��򿪳ɹ���fileCheck.is_open() ���� true�����ʧ�ܣ����� false��
    if (!fileCheck.is_open()) {//����ļ��Ƿ�δ�ܴ�
        ofstream fileCreate(globalFileName);
        if (!fileCreate.is_open()) {
            cerr << "�޷����������ļ���" << endl;
            return;
        }
        fileCreate.close(); // �������ļ���ر�
    }
    else {
        // ����ļ����ڣ���ȡ�ļ��е����з���
        string line;
        while (getline(fileCheck, line)) {
            scores.push_back(stoi(line)); // ���ַ���ת��Ϊ��������ӵ�������
        }
        fileCheck.close();
    }

    // ����µķ���
    scores.push_back(newScore);

    // �Է������н�������
    sort(scores.begin(), scores.end(), greater<int>());//ʹ�� sort ������ scores ������������greater<int>() ��Ϊ������������ָ������Ϊ����

    // ���ԭ�ļ�����
    ofstream fileWrite(globalFileName);
    if (fileWrite.is_open()) {
        // �������ķ���д���ļ�
        for (int score : scores) {//���� scores �����е�ÿ��������
            fileWrite << score << endl;
        }
        fileWrite.close();
    }
    else {
        cerr << "�޷��򿪷����ļ�����д�롣" << endl;
    }
}

void readScore() {//����¼�������ļ�����һ�����ں�������
    // ����Դ�ļ���Ŀ���ļ����ļ���
    string srcFileName = "score_source.txt";
    string destFileName = "scores.txt";

    // ���Դ�ļ��Ƿ����
    ifstream srcFile(srcFileName);
    if (!srcFile.is_open()) {
        cout << "�޷���Դ�����ļ���" << srcFileName << endl;
        return;
    }

    // ���Դ����򸲸�Ŀ���ļ�
    ofstream destFile(destFileName);
    if (!destFile.is_open()) {
        cout << "�޷�����Ŀ������ļ���" << destFileName << endl;
        srcFile.close();
        return;
    }

    string line;
    while (getline(srcFile, line)) {
        destFile << line << endl;
    }

    srcFile.close();
    destFile.close();

    cout << "�����ļ�������ɡ�" << endl;
}

// -------------------- view �������� --------------------//

int main() {
    colorA = "blue", colorB = "yellow";
    menuView();
}

void ShowCursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 20, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}//���ع��

void gotoXY(int x, int y) {  // ��������, ������ƶ���ָ������
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setPrintColor(int color) {  // ������ʾָ������
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
        cout << "���˵�";
        if (menuChoice == 0) setPrintColor(0x9f);
        gotoXY(50, 7);
        cout << "������Ϸ";
        setPrintColor(0x0f);
        if (menuChoice == 1) setPrintColor(0x9f);
        gotoXY(50, 10);
        cout << "��������";
        setPrintColor(0x0f);
        if (menuChoice == 2) setPrintColor(0x9f);
        gotoXY(50, 13);
        cout << "���а�";
        setPrintColor(0x0f);
        if (menuChoice == 3) setPrintColor(0x9f);
        gotoXY(50, 16);
        cout << "�˳���Ϸ";
        setPrintColor(0x0f);
        gotoXY(36, 21);
        cout << "ͨ�� ws �������ƶ����� Enter ��ȷ��";
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
        cout << "��Ϸģʽѡ��";
        if (userChoose == 0) setPrintColor(0x9f);
        gotoXY(50, 7);
        cout << "�����޾�";
        setPrintColor(0x0f);
        if (userChoose == 1) setPrintColor(0x9f);
        gotoXY(50, 10);
        cout << "˫���޾�";
        setPrintColor(0x0f);
        if (userChoose == 2) setPrintColor(0x9f);
        gotoXY(50, 13);
        cout << "������һ��";
        setPrintColor(0x0f);
        gotoXY(36, 21);
        cout << "ͨ�� ws �������ƶ����� Enter ��ȷ��";
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
            case 0:  // �����޾�
                gameMode = 1;
                gameView();
                break;
            case 1:  // ˫���޾�
                gameMode = 2;
                gameView();
                break;
            case 2:  // ������һ��
                menuView();
                break;
            }
            break;
        }
    }
}

int winView() {
    system("cls"); // ����
    ShowCursor();
    gotoXY(50, 5);
    cout << "��Ϸ������" << endl;
    // ������Ϸģʽ��ʾʤ����Ϣ
    switch (gameMode) {
        case 1: // ����ģʽ
            gotoXY(50, 8);
                cout << "����: " << snakeA.score << endl;
                // ���ü�¼������¼����
                writeScore(snakeA.score);
                
                cout << "��������������˵�..." << endl;
                Sleep(2000);
                while (!_kbhit()) {} // �ȴ�����
                _getch();
                menuView(); // �������˵�
                break;
        case 2: // ˫��ģʽ  
                // ���� flag ��ֵ��ʾʤ����Ϣ
                flag = isWin();
                if (flag == 1) {
                    cout << "��ϲA�߻��ʤ����" << endl;
                }
                else if (flag == 2) {
                    cout << "��ϲB�߻��ʤ����" << endl;
                }
                else {
                    cout << "��Ϸƽ�֣�" << endl;
                }
                // ��ʾ����
                cout << "A�߷���: " << snakeA.score << endl;
                cout << "B�߷���: " << snakeB.score << endl;

                writeScore(snakeA.score);
                writeScore(snakeB.score);
                
                cout << "��������������˵�..." << endl;
                Sleep(2000);
                while (!_kbhit()) {} // ������˼���
                _getch();
                menuView(); // �������˵�
                break;
        case 0: // �˳���Ϸ
            cout << "�˳���Ϸ��" << endl;
            return 1; // ȷ���з���ֵ
        default:
            cout << "��Чѡ��������ѡ��" << endl;
            return 1; // ȷ���з���ֵ
        }
}

void gameSet() {
    int userChoose = 0; // �û���ǰѡ��
    bool staticc = 0;//enter�̶���
    while (true) {
        system("cls");
        gotoXY(50, 4);
        cout << "�� Ϸ �� ��";

        if (userChoose == 0)
            if (staticc) setPrintColor(0x2f);
            else setPrintColor(0x9f);
        else setPrintColor(0x0f);
        gotoXY(50, 7);
        cout << "�� ɫ A: " << colorA;

        if (userChoose == 1)
            if (staticc) setPrintColor(0x2f);
            else setPrintColor(0x9f);
        else setPrintColor(0x0f);
        gotoXY(50, 10);
        cout << "�� ɫ B: " << colorB;
        setPrintColor(0x0f);

        if (userChoose == 2)
            if (staticc) setPrintColor(0x2f);
            else setPrintColor(0x9f);
        gotoXY(50, 13);
        cout << "�� Ч�� " << (isSound ? "��" : "��");
        setPrintColor(0x0f);

        if (userChoose == 3)
            if (staticc) setPrintColor(0x2f);
            else setPrintColor(0x9f);
        gotoXY(50, 16);
        cout << "�� �֣� " << (isMusic ? "��" : "��");
        setPrintColor(0x0f);

        gotoXY(20, 21);
        cout << "ͨ�� ws �������ƶ���ͨ�� ad ��ѡ����ɫֻ�����ң����� Enter ��ȷ�ϣ��� Esc ���˳�";
        gotoXY(48, 23);
        cout << "ѡ��ѡ����̵�";
        char input;
        if (staticc)
        {
            input = _getch();
            if (input == 13) staticc = !staticc;
            else if(staticc)
            switch (userChoose) {
            case 0: // �޸���ɫ A
                if (input == 'd')
                    if (colorA == "red") colorA = "yellow";
                    else if (colorA == "yellow") colorA = "green";
                    else if (colorA == "green") colorA = "blue";
                    else if (colorA == "blue") colorA = "purple";
                    else if (colorA == "purple") colorA = "cyan";
                    else if (colorA == "cyan") colorA = "white";
                    else if (colorA == "white") colorA = "red";
                break;
            case 1: // �޸���ɫ B
                if(input=='d')
                    if (colorB == "red") colorB = "yellow";
                    else if (colorB == "yellow") colorB = "green";
                    else if (colorB == "green") colorB = "blue";
                    else if (colorB == "blue") colorB = "purple";
                    else if (colorB == "purple") colorB = "cyan";
                    else if (colorB == "cyan") colorB = "white";
                    else if (colorB == "white") colorB = "red";
                    break;
            case 2: // �޸���Ч
                if(input=='a' || input == 'd')
                    isSound = !isSound;
                    break;
            case 3: // �޸�����
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
            case 27: // Esc ���˳�����
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
    cout << "���1����: " << snakeA.score;
    if (gameMode == 2) gotoXY(DX+30,1),cout << "  ���2����: " << snakeB.score;
    cout << endl;
    gotoXY(DX + 65, 25);
    cout << "���ո���ͣ... ...";
    for (int i = 0; i < 25; i++) {

        for (int j = 0; j < 60; j++) {
            if (i == 0 || i == 24 || j == 0 || j == 59) {
                gotoXY(DX + j, DY + i);
                cout << "#"<<' '; // ǽ��
            }
            else if (i == food.y && j == food.x) {
                // ����ʳ����ɫ��ӡ
                if (food.color == "green") {
                    setPrintColor(0x0a); // ��ɫ
                }
                else {
                    setPrintColor(0x0c); // ��ɫ
                }
                gotoXY(DX + j, DY + i);
                cout << "��"; // ʳ��
                setPrintColor(0x07); // ������ɫΪĬ��
            }
            else {
                bool printed = false; // ��־���������ڱ���Ƿ��ӡ��
                // ��ӡ��A
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
                        cout << "*"; // ��A
                        printed = true;
                        break;
                    }
                }

                // ��ӡ��B
                if(gameMode==2)
                if (!printed) { // ֻ��û�д�ӡ��A������¼����B
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
                            cout << "O"; // ��B
                            printed = true;
                            break;
                        }
                    }
                }

                // ��ӡ�ϰ���
                if (!printed) { // ֻ��û�д�ӡ��������¼���ϰ���
                    for (int k = 0; k < OBSTACLE_COUNT; k++) {
                        if (obstacles[k].x == j && obstacles[k].y == i) {
                                    gotoXY(DX + j, DY + i);
                                    cout << "#"; // �ϰ���
                                    printed = true;
                                    break; // 
                        }
                    }
                }

                // ���û�д�ӡ�ߡ�ʳ����ϰ�����ӡ�ո�
                if (!printed) {
                    gotoXY(DX + j, DY + i);
                    cout << " "; // �յ�
                }
            }
            setPrintColor(0x07); // ����һ��λ�þ�������ɫΪĬ��
        }
    }

}

void pauseView() {
    Sleep(500);
    //�û���ǰѡ��
    int userChoose = 0;
    system("cls");
    //��ӡ�߿�
    while (1) {
        gotoXY(50, 4);
        cout << "�� Ϸ �� �� ͣ";
        if (userChoose == 0) setPrintColor(0x9f);
        gotoXY(50, 7);
        cout << "������Ϸ";
        setPrintColor(0x0f);
        if (userChoose == 1) setPrintColor(0x9f);
        gotoXY(50, 10);
        cout << "��Ϸ����";
        setPrintColor(0x0f);
        if (userChoose == 2) setPrintColor(0x9f);
        gotoXY(50, 13);
        cout << "���ز˵�";
        setPrintColor(0x0f);
        gotoXY(36, 21);
        cout << "ͨ�� ws �������ƶ����� Enter ��ȷ��";
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
            case 0:  //������Ϸ
                gameView();
                break;
            case 1:  // ��Ϸ����
                gameSet();
                break;
            case 2:  // ���ز˵�
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
    //�ƶ�
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
    readScore();//����readscore�ǽ�Դ�ļ���Ϊ scores_source.txt������Ϊһ�����ļ���Ϊ scores.txt�����Ǵ˺󼰶�score.txt�ļ����в���
    ifstream file("scores.txt");//����ǰ�ڵļ�¼���������Ѿ�������һ��ÿ��ֻ��һ�������������Ѿ��ź��˴�С˳�򣩵ļ�¼�ļ�
    if (!file.is_open()) {
        cout << "�޷��򿪷����ļ���" << endl;
        return;
    }

    system("cls");//����Ϊ��ӡ���а���׼��
    cout << "���а�" << endl;

    int page = 0;
    int scores_per_page = 10; // ����ÿҳ��ʾ10������
    string line;
    int score_count = 0;

    // �����ܷ�������
    file.seekg(0, ios::beg); // �ص��ļ���ͷ
    while (getline(file, line)) {//ѭ����ȡ�ļ��м�¼������
        score_count++;
    }
    int total_page = score_count / scores_per_page;//����������ÿҳ�����õ���ҳ��
    if (score_count % scores_per_page != 0)//ȷ���˼�ʹ���һҳû����ȫ������Ҳ�ᱻ��������
    {
        total_page++;
    }



    // �ȴ��û�����
    char input;
    do {
        system("cls"); // ����
        // ��ʾ���а�ͷ��
        cout << "=========================" << endl;
        cout << "  ����   ����" << endl;
        cout << "=========================" << endl;
        score_count = page * scores_per_page; // ���÷�������������ǰҳ����ʼ����

        // ��ʾ��ǰҳ�ķ���
        file.clear(); // ����ļ���״̬
        file.seekg(0, ios::beg); // �ص��ļ���ͷ
        while (getline(file, line) && score_count < (page + 1) * scores_per_page) {//while��������Ƿ�������һҳ֮ǰ�ļ�¼
            if (score_count >= page * scores_per_page) {//if����ɸѡ���ڵ�ǰҳ�ļ�¼�����ڴ�ӡ
                cout << "   " << (score_count - page * scores_per_page + 1);
                if (score_count - page * scores_per_page + 1 < 10) cout << ' ';
                cout << "     " << line << endl;
            }
            score_count++;
        }

        // ��ʾ���а�β��
        cout << "=========================" << endl;
        cout << "�� 'a' ��ǰ��ҳ���� 'd' ���ҳ���� Esc �˳����а�" << endl;
        cout << "=========================" << endl;

        input = _getch(); // ��ȡ�û�����
        switch (input) {
        case 'a': // ��ǰ��ҳ
            if (page > 0) //��֤��page����Ч��
            {
                page--;
            }
            break;
        case 'd': // ���ҳ
            if (page < total_page - 1)//��֤��page����Ч��
            {
                page++;
            }
            break;
        case 27: // Esc ��
            break; // �˳�ѭ��
        default:
            break; // ������������
        }
    } while (input != 27); // ѭ��ֱ���û����� Esc ��

    file.close(); // �ر��ļ�
    remove("scores.txt");//readscore�������ļ�
    menuView();//���û�����esc��ֹͣѭ���ر��ļ�ɾ�������ٵ���menuview�ص����˵�
}