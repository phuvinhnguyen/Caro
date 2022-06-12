#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <MMsystem.h>
#include <fstream>
#pragma comment (lib, "winmm.lib")
using namespace std;

int ize;
char upright = char(191), downleft = char(192), downmid = char(193), upmid = char(194), midleft = char(195), hori = char(196);
char mid = char(197), vert = char(179), midright = char(180), upleft = char(218), downright = char(217);
int game;//AI(2) hay PVP(1)
int step1 = 0, step2 = 0;
int playerwin = 0, aiwin = 0, player1win = 0, player2win = 0;
char mark1, mark2;
int pointtowin;
int movex = 2, movey = 11;
char space[20][20];
int difficulty;
int fpw = 0, fcw = 0, fp1w = 0, fp2w = 0;
int ppgame = 0, pcgame = 0;
int easyd = 0, normald = 0, hardd = 0, easyw = 0, normalw = 0, hardw = 0;
int soundon = 1, musicon = 1;



void changefontsize(int n, int m) {
    HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
    PCONSOLE_FONT_INFOEX font = new CONSOLE_FONT_INFOEX();
    font->cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(cons, 0, font);
    font->dwFontSize.X = n;//8
    font->dwFontSize.Y = m;//16
    SetCurrentConsoleFontEx(cons, 0, font);
}

void setcolor(int color) {// mau chu goc 7; nen goc 0
    HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleColor, color);
}

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

void intro() {                                // false
    for (int i = 0; i < 18; i++) {
        gotoxy(25, i);
        setcolor(i % 10 + 1);
        cout << "                                                                                         ";
        gotoxy(25, i + 1);
        cout << "      CCCCCCCCCCCC           AAA              RRRRRRRRRRRRR         OOOOOOOOO     ";
        gotoxy(25, i + 2);
        cout << "    CCCCCCCCCCCCCC          AA AA             RRRR         R       OOOOOOOOOOO    ";
        gotoxy(25, i + 3);
        cout << "    CCCCC                  AA   AA            RRRR          R     O           O   ";
        gotoxy(25, i + 4);
        cout << "    CCCC                  AA     AA           RRRR           R    OOOOOOOOOOOOO   ";
        gotoxy(25, i + 5);
        cout << "    CCCC                 AA       AA          RRRR          R     O           O   ";
        setcolor(i % 10 + 2);
        gotoxy(25, i + 6);
        cout << "    CCCC                AA         AA         RRRR         R      OOOOOOOOOOOOO   ";
        gotoxy(25, i + 7);
        cout << "    CCCC               AAAAAAAAAAAAAAA        RRRRRRRRRRRRR       O           O   ";
        gotoxy(25, i + 8);
        cout << "    CCCC              AAAAAAAAAAAAAAAAA       RRRRRRRRRRRR        OOOOOOOOOOOOO   ";
        gotoxy(25, i + 9);
        cout << "    CCCCC            AA               AA      RRRR      RRR       O           O   ";
        gotoxy(25, i + 10);
        cout << "    CCCCCCCCCCCCC   AA                 AA     RRRR       RRR       OOOOOOOOOOO    ";
        gotoxy(25, i + 11);
        cout << "      CCCCCCCCCCC  AA                   AA    RRRR        RRR       OOOOOOOOO     ";
        Sleep(250);
    }
}

void christmas(int x, int y) {
    for (int i = 0; i < 10; i++) {
        gotoxy(x - i, y + i);
        for (int j = 0; j < 2 * i + 1; j++)
            if (i == 3 || i == 9) {
                setcolor(4);
                cout << "X";
            }
            else if (i == 6) {
                setcolor(3);
                cout << "O";
            }
            else {
                setcolor(2);
                cout << char(127);
            }
    }
    setcolor(8);
    for (int i = 0; i < 3; i++) {
        gotoxy(x - 1, y + 10 + i);
        cout << "HHH";
    }
    setcolor(7);
}

void gameinfo() {
    int count = 100;
    setcolor(6);
    for (int i = 15; i < 24; i++) {
        gotoxy(55, i);
        cout << vert;
    }

    for (int i = 56; i < 110; i++) {
        gotoxy(i, 14);
        cout << hori;
    }

    for (int i = 56; i < 110; i++) {
        gotoxy(i, 24);
        cout << hori;
    }

    gotoxy(55, 24);
    cout << downleft;
    gotoxy(55, 14);
    cout << upleft;
    setcolor(7);

    char n = ' ';
    difficulty = 0;
    gotoxy(50, 15);
    cout << "\tchoose size of board:  ";
    gotoxy(77, 15);
    cout << " << " << count % 8 + 3 << " >>  ";
    while (1) {
        n = ' ';
        while (n != 'a' && n != 'd' && n != char(13)) {
            n = _getch();
        }
        if (n == 'a')
            count--;
        else if (n == 'd')
            count++;
        else {
            ize = count % 8 + 3;
            break;
        }
        gotoxy(77, 15);
        cout << " << " << count % 8 + 3 << " >>  ";
    }


    gotoxy(50, 17);
    cout << "\tchoose point to win: ";
    gotoxy(77, 17);
    if (ize != 3)
        cout << " << " << count % (ize - 2) + 3 << " >>  ";
    else cout << " << " << 3 << " >>  ";
    while (1) {
        n = ' ';
        while (n != 'a' && n != 'd' && n != char(13)) {
            n = _getch();
        }
        if (n == 'a')
            count--;
        else if (n == 'd')
            count++;
        else {
            pointtowin = count % (ize - 2) + 3;
            break;
        }
        gotoxy(77, 17);
        if (ize != 3)
            cout << " << " << count % (ize - 2) + 3 << " >>  ";
        else cout << " << " << 3 << " >>  ";
    }


    if (game == 1) {
        //         PLAYER 1
        gotoxy(50, 19);
        cout << "\tchoose player 1 mark: ";
        gotoxy(80, 19);
        cout << "<< X >>  ";
        mark1 = 'X';
        count = 123;
        while (1) {
            n = ' ';
            while (n != 'a' && n != 'd' && n != char(13)) {
                n = _getch();
            }
            if (n == 'a')
                count--;
            else if (n == 'd')
                count++;
            else {
                mark1 = char(count % 25 + 65);
                break;
            }
            gotoxy(80, 19);
            cout << "<< " << char(count % 25 + 65) << " >>  ";
        }
        //             PLAYER 2
        gotoxy(50, 21);
        cout << "\tchoose player 2 mark: ";
        gotoxy(80, 21);
        cout << " << O >>  ";
        mark2 = 'O';
        count = 114;
        while (1) {
            n = ' ';
            while (n != 'a' && n != 'd' && n != char(13)) {
                n = _getch();
            }
            if (n == 'a')
                count--;
            else if (n == 'd')
                count++;
            else {
                mark2 = char(count % 25 + 65);
                break;
            }
            gotoxy(80, 21);
            if (char(count % 25 + 65) != mark1)
                cout << " << " << char(count % 25 + 65) << " >>  ";
            else {
                count++;
                cout << " << " << char(count % 25 + 65) << " >>  ";
            }
        }
    }

    //                   THIS IS AI BOT GAME
    else {
        //                        PLAYER
        gotoxy(50, 19);
        cout << "\tchoose player mark: ";
        gotoxy(80, 19);
        cout << " << X >>  ";
        mark1 = 'X';
        count = 123;
        while (1) {
            n = ' ';
            while (n != 'a' && n != 'd' && n != char(13)) {
                n = _getch();
            }
            if (n == 'a')
                count--;
            else if (n == 'd')
                count++;
            else {
                mark1 = char(count % 25 + 65);
                break;
            }
            gotoxy(80, 19);
            cout << " << " << char(count % 25 + 65) << " >>  ";
        }

        //                 COMPUTER
        gotoxy(50, 21);
        cout << "\tchoose computer mark: ";
        gotoxy(80, 21);
        cout << " << O >>  ";
        mark2 = 'O';
        count = 114;
        while (1) {
            n = ' ';
            while (n != 'a' && n != 'd' && n != char(13)) {
                n = _getch();
            }
            if (n == 'a')
                count--;
            else if (n == 'd')
                count++;
            else {
                mark2 = char(count % 25 + 65);
                break;
            }
            gotoxy(80, 21);
            if (char(count % 25 + 65) != mark1)
                cout << " << " << char(count % 25 + 65) << " >>  ";
            else {
                count++;
                cout << " << " << char(count % 25 + 65) << " >>  ";
            }
        }

        //     DIFFICULTY
        gotoxy(50, 23);
        cout << "\tchoose difficulty: ";// 4 is not ready yet (boss)
        gotoxy(75, 23);
        cout << " << EASY >>  ";
        count = 99;
        while (1) {
            difficulty = count % 3 + 1;
            n = ' ';
            while (n != 'a' && n != 'd' && n != char(13)) {
                n = _getch();
            }
            if (n == 'a')
                count--;
            else if (n == 'd')
                count++;
            else {
                break;
            }
            gotoxy(75, 23);
            if (difficulty == 1)
                cout << " << NORMAL>>  ";
            else if (difficulty == 2)
                cout << " << HARD >>  ";
            else cout << " << EASY >>  ";
        }
    }//                            END OF AI
}

void rematch() {
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            space[i][j] = ' ';
}

void renew() {
    playerwin = 0; aiwin = 0; player1win = 0; player2win = 0;
    step1 = 0; step2 = 0; ppgame = 0; pcgame = 0;
    hardd = 0; easyd = 0; normald = 0;
}

void gameboard() {
    for (int i = 10; i < 2 * ize + 11; i++)
        for (int j = 0; j < 4 * ize + 1; j++) {
            gotoxy(j, i);
            if (i == 10) {
                if (j == 0)
                    cout << upleft;
                else if (j == 4 * ize)
                    cout << upright;
                else if (j % 4 == 0)
                    cout << upmid;
                else cout << hori;
            }
            else if (i == 2 * ize + 10) {
                if (j == 0)
                    cout << downleft;
                else if (j == 4 * ize)
                    cout << downright;
                else if (j % 4 == 0)
                    cout << downmid;
                else cout << hori;
            }
            else if (i % 2 == 0) {
                if (j == 0)
                    cout << midleft;
                else if (j == 4 * ize)
                    cout << midright;
                else if (j % 4 == 0)
                    cout << mid;
                else cout << hori;
            }
            else {
                if (j % 4 == 0)
                    cout << vert;
            }
        }
}

void scoreboard() {
    setcolor(5);
    for (int j = 0; j < 9; j++) {
        if (j == 0)
            for (int i = 0; i <= 80; i++) {
                gotoxy(i, j);
                if (i == 0) cout << upleft;
                else if (i == 20 || i == 40 || i == 60) cout << upmid;
                else if (i == 80) cout << upright;
                else cout << hori;
            }
        else if (j == 2)
            for (int i = 0; i <= 80; i++) {
                gotoxy(i, j);
                if (i == 0) cout << midleft;
                else if (i == 20 || i == 40 || i == 60) cout << mid;
                else if (i == 80) cout << midright;
                else cout << hori;
            }
        else if (j == 8)
            for (int i = 0; i <= 80; i++) {
                gotoxy(i, j);
                if (i == 0) cout << downleft;
                else if (i == 20 || i == 40 || i == 60) cout << downmid;
                else if (i == 80) cout << downright;
                else cout << hori;
            }
        else
            for (int i = 0; i <= 80; i++) {
                gotoxy(i, j);
                if (i == 0 || i == 20 || i == 40 || i == 60 || i == 80) cout << vert;
            }
    }
    setcolor(7);
    gotoxy(2, 1); cout << "GUIDE";
    gotoxy(22, 1); cout << "MOVE";
    gotoxy(42, 1); cout << "SCORE";
    gotoxy(62, 1); cout << "PLAYER'S MARK";

    gotoxy(2, 3); cout << "a: left";
    gotoxy(12, 3); cout << "s: down";
    gotoxy(2, 4); cout << "d: right";
    gotoxy(12, 4); cout << "w: up";
    gotoxy(2, 6); cout << "enter: choose";
    gotoxy(2, 7); cout << "g: surrender";
    if (game == 1) {
        gotoxy(62, 3); cout << "player 1: " << mark1;
        gotoxy(62, 5); cout << "player 2: " << mark2;
        gotoxy(22, 4); cout << "player 1: " << step1;
        gotoxy(22, 6); cout << "player 2: " << step2;
        gotoxy(42, 4); cout << "player 1: " << player1win;
        gotoxy(42, 6); cout << "player 2: " << player2win;
    }
    else {
        gotoxy(62, 3); cout << "player: " << mark1;
        gotoxy(62, 5); cout << "computer: " << mark2;
        gotoxy(22, 4); cout << "player: " << step1;
        gotoxy(22, 6); cout << "computer: " << step2;
        gotoxy(42, 4); cout << "player: " << playerwin;
        gotoxy(42, 6); cout << "computer: " << aiwin;
    }
    gotoxy(62, 7); cout << "point to win: " << pointtowin;
    gotoxy(movex, movey);
}

int mainboard() {
    system("cls");
    char n;
    setcolor(10);
    cout << "\t";
    for (int i = 0; i < 100; i++)
        cout << hori;
    setcolor(4);
    cout << "\n\n";
    cout << "\t\t  CCCCCCCCCCCC              AAAAAA             RRRRRRRRRRRR           OOOOOOOOOOO      \n";
    cout << "\t\tCCCC  CCCCCCCC             AAA  AAA            R  R        RR       OO     +     OO    \n";
    cout << "\t\tCCCC         C            AAA    AAA           R  R          RR   OO       +       OO  \n";
    cout << "\t\tCCCC                     AAA      AAA          R  R        RR     OO+++++++++++++++OO  \n";
    cout << "\t\tCCCC                    AAA        AAA         RRRRRRRRRRRR       OO       +       OO  \n";
    setcolor(11);
    cout << "\t\tCCCC                   AAAAAAAAAAAAAAAA        RRRR    RRR        OO       +       OO  \n";
    cout << "\t\tCCCC                  AAAAAAAAAAAAAAAAAA       RRRR     RRR       OO       +       OO  \n";
    cout << "\t\tCCCC         C       AAA              AAA      RRRR      RRR      OO       +       OO  \n";
    cout << "\t\tCCCC  CCCCCCCC     AAAA                AAAA    RRRR       RRR       OO     +      OO   \n";
    cout << "\t\t  CCCCCCCCCCCC    AAAAA                AAAAA   RRRR        RRR        OOOOOOOOOOO      \n";
    cout << "\n\t";
    setcolor(10);
    for (int i = 0; i < 100; i++)
        cout << hori;
    setcolor(7);
    cout << "\n\n";
    setcolor(112);
    changefontsize(11, 22);
    cout << "\t\t\tPlay PVP\n\n";
    cout << "\t\t\tPlay PVC\n\n";
    cout << "\t\t\tMusic\n\n";
    cout << "\t\t\tProcess\n\n";
    cout << "\t\t\tExit\n\n";
    setcolor(109);
    changefontsize(8, 16);
    gotoxy(20, 27); cout << ">>>>>  enter a s w d to move, enter to choose  <<<<<";
    setcolor(7);
    int count = 100;
    while (1) {
        n = ' ';
        while (n != 'w' && n != 's' && n != char(13)) {
            n = _getch();
        }
        gotoxy(35, 2 * (count % 5) + 15);
        cout << "             ";
        if (n == 's')
            count++;
        else if (n == 'w')
            count--;
        else {
            if (count % 5 == 0)
                game = 1;
            if (count % 5 == 1)
                game = 2;
            break;
        }
        gotoxy(35, 2 * (count % 5) + 15);
        cout << "<<====<<";
    }
    gotoxy(35, 2 * (count % 5) + 15);
    cout << "------------------>";
    int t = count % 5 + 1;
    return t;
}

void process() {
    setcolor(11);
    cout << "\t\tSSSSS  TTTTTTT      A      TTTTTTT  I   SSSSS  TTTTTTT  I  CCCCCC  SSSSS \n";
    cout << "\t\tS         T        A A        T     I   S         T     I  C       S     \n";
    cout << "\t\tSSSSS     T       AAAAA       T     I   SSSSS     T     I  C       SSSSS \n";
    cout << "\t\t    S     T      A     A      T     I       S     T     I  C           S \n";
    cout << "\t\tSSSSS     T     A       A     T     I   SSSSS     T     I  CCCCCC  SSSSS \n";
    cout << "\n\n";
    setcolor(12);
    for (int i = 0; i < 33; i++)
        cout << hori;
    cout << upright;
    cout << endl;
    cout << "\tPPPPP  V       V  PPPPP  " << vert << "        " << upleft << "\n";
    cout << "\tP   P   V     V   P   P  " << vert << "        " << vert << "    PLAYER 1 WIN:  " << player1win << endl;
    cout << "\tPPPPP    V   V    PPPPP  " << vert << ">>>>>>>>" << vert << "    PLAYER 2 WIN:  " << player2win << endl;
    cout << "\tP         V V     P      " << vert << "        " << vert << "    TOTAL PVP BATTLES: " << ppgame << endl;
    cout << "\tP          V      P      " << vert << "        " << downleft << "\n";
    for (int i = 0; i < 33; i++)
        cout << hori;
    cout << downright;
    cout << "\n\n";
    setcolor(13);
    for (int i = 0; i < 33; i++)
        cout << hori;
    cout << upright;
    cout << endl;
    cout << "\tPPPPP  V       V  CCCCC  " << vert << "        " << upleft << "                  \n";
    cout << "\tP   P   V     V   C      " << vert << "        " << vert << "    PLAYER WIN:  " << playerwin << endl;
    cout << "\tPPPPP    V   V    C      " << vert << ">>>>>>>>" << vert << "    COMPUTER WIN:  " << aiwin << endl;
    cout << "\tP         V V     C      " << vert << "        " << vert << "    TOTAL PVC BATTLES: " << pcgame << endl;
    cout << "\tP          V      CCCCC  " << vert << "        " << vert << "         + DEFEAT/LOSE EASY AI:  " << easyd << "/" << easyw << endl;
    for (int i = 0; i < 33; i++)
        cout << hori;
    cout << downright;
    cout << "        " << vert << "         + DEFEAT/LOSE NORMAL AI:  " << normald << "/" << normalw << endl;
    cout << "\t                                  " << vert << "         + DEFEAT/LOSE HARD AI:  " << hardd << "/" << hardw << endl;
    cout << "\t                                  " << downleft << endl;
}

void createfile() {
    ofstream file("data.txt");
    file << player1win << "\n";//0
    file << player2win << "\n";//1
    file << ppgame << "\n";//2
    file << playerwin << "\n";//3
    file << aiwin << "\n";//4
    file << pcgame << "\n";//5
    file << easyw << "\n";//6
    file << normalw << "\n";//7
    file << hardw << "\n";//8
    file << easyd << "\n";//9
    file << normald << "\n";//10
    file << hardd << "\n";//11
    file.close();//
}

int music(int choose) {
    if (choose == 1)//player
        if (soundon == 1)
            PlaySound(TEXT("Eye_Poke-Klocko-584660179.wav"), NULL, SND_LOOP);

    if (choose == 2)//menu music
        if (musicon == 1)
            PlaySound(TEXT("ChocoboRacingHouseOfBlack-HoaTau-3316636.wav"), NULL, SND_ASYNC);

    if (choose == 3)//win
        if (musicon == 1)
            PlaySound(TEXT("ChocoboRacingWin-HoaTau-3316611.wav"), NULL, SND_ASYNC);
    if (choose == 4)//lose
        if (musicon == 1)
            PlaySound(TEXT("ChocoboRacingLose-HoaTau-3316610.wav"), NULL, SND_ASYNC);
    return 0;
}

int result() {
    int i = 0;
    bool check = true;
    bool check1, check2, check3, check4;
    for (int t = 0; t < ize; t++) {
        for (int k = 0; k < ize; k++) {
            check1 = true; check2 = true; check3 = true; check4 = true;
            if (space[t][k] != ' ') {
                for (int a = 0; a < pointtowin; a++) {
                    if (space[t][k] != space[t + a][k + a]) { check1 = false; }
                    if (space[t][k] != space[t + a][k]) { check2 = false; }
                    if (space[t][k] != space[t - a][k + a]) { check3 = false; }
                    if (space[t][k] != space[t][k + a]) { check4 = false; }
                }
            }
            else {
                check1 = false;
                check2 = false;
                check3 = false;
                check4 = false;
            }
            if (space[t][k] == ' ') { check = false; }
            if (check1 == true || check2 == true || check3 == true || check4 == true) {
                if (space[t][k] == mark1) { i = 1; }
                else if (space[t][k] == mark2) { i = 2; }
            }
        }
    }
    if (check1 == false && check2 == false && check3 == false && check4 == false && check == true && i == 0) { i = 3; }
    return i;
}

bool move(int playerturn, int& surrender) {//1 hoac 2
    char icon = 'u';
    surrender = 0;
    while (icon != 'a' && icon != 's' && icon != 'd' && icon != 'w' && icon != char(13) && icon != 'g')
        icon = _getch();
    gotoxy(movex, movey);
    if (icon == 'a') {
        if (movex - 4 > 1) {
            movex -= 4;
            gotoxy(movex, movey);
        }
        return false;
    }

    if (icon == 's') {
        if (movey + 2 < 2 * ize + 10) {
            movey += 2;
            gotoxy(movex, movey);
        }
        return false;
    }

    if (icon == 'd') {
        if (movex + 4 < 4 * ize) {
            movex += 4;
            gotoxy(movex, movey);
        }
        return false;
    }

    if (icon == 'w') {
        if (movey - 2 > 10) {
            movey -= 2;
            gotoxy(movex, movey);
        }
        return false;
    }

    if (icon == 'g') {
        surrender = playerturn;
        return false;
    }

    if (icon == char(13) && space[movex / 4][(movey - 10) / 2] == ' ') {
        gotoxy(movex, movey);
        if (playerturn == 1) {
            setcolor(4);
            cout << mark1;
            space[movex / 4][(movey - 10) / 2] = mark1;
            step1++;
            setcolor(3);
        }
        else {
            setcolor(3);
            space[movex / 4][(movey - 10) / 2] = mark2;
            cout << mark2;
            step2++;
            setcolor(4);
        }
        return true;
    }
}

/*
int AIboss(int& turn, int& x, int& y) {
    int a, b;
    for (int i = 0; i < ize; i++)
        for (int j = 0; j < ize; j++) {
            if (space[i][j] == ' ') {
                if (turn == 1)
                    space[i][j] = mark1;
                else space[i][j] = mark2;
                if (result() == 1) {
                    space[i][j] = ' ';
                    return -10;
                }
            }
        }
    for (int i = 0; i < ize; i++)
        for (int j = 0; j < ize; j++) {
            if (space[i][j] == ' ') {
                if (turn == 1)
                    space[i][j] = mark1;
                else space[i][j] = mark2;
                if (result() == 2) {
                    x = i; y = j;
                    space[i][j] = ' ';
                    return 10;
                }
            }
        }
    for (int i = 0; i < ize; i++)
        for (int j = 0; j < ize; j++) {
            if (space[i][j] == ' ') {
                if (turn == 1)
                    space[i][j] = mark1;
                else space[i][j] = mark2;
                if (result() == 3) {
                    x = i; y = j;
                    space[i][j] = ' ';
                    return 0;
                }
            }
        }
    for (int i = 0; i < ize; i++)
        for (int j = 0; j < ize; j++) {
            if (space[i][j] == ' ') {
                if (turn == 1)
                    space[i][j] = mark1;
                else space[i][j] = mark2;
                if (result() == 0) {
                    int turn = turn % 2 + 1;
                    if (AIhard(turn, a, b) == -10)
                        goto pass;
                    if (AIhard(turn, a, b) == 10) {
                        x = i; y = j;
                        return 10;
                    }
                    if (AIhard(turn, a, b) == 0) {
                        x = i; y = j;
                        return 0;
                    }
                }
            pass:
                space[i][j] = ' ';
            }
        }
    return -10;
}
*/

void AI() {
    if (difficulty == 1) {//easy
        int x = 0, y = 0;
        srand(time(0));
        while (space[x][y] != ' ') {
            x = rand() % ize;
            y = rand() % ize;
        }
        gotoxy(4 * x + 2, 11 + y * 2);
        cout << mark2;
        space[x][y] = mark2;
    }
    else if (difficulty == 2) {//normal
        // win
        bool check = true;
        for (int i = 0; i < ize; i++)
            for (int j = 0; j < ize; j++) {
                if (space[i][j] == ' ') {
                    space[i][j] = mark2;
                    if (result() == 2) {
                        gotoxy(4 * i + 2, 11 + j * 2);
                        cout << mark2;
                        i = ize; j = ize; check = false;
                    }
                    else space[i][j] = ' ';
                }
            }
        // chan cuoi
        if (check == true) {
            for (int i = 0; i < ize; i++)
                for (int j = 0; j < ize; j++) {
                    if (space[i][j] == ' ') {
                        space[i][j] = mark1;
                        if (result() == 1) {
                            gotoxy(4 * i + 2, 11 + j * 2);
                            cout << mark2;
                            space[i][j] = mark2;
                            i = ize; j = ize; check = false;
                        }
                        else space[i][j] = ' ';
                    }
                }
        }
        // chan trc
        if (check == true) {
            bool check1, check2, check3, check4, check5, check6, check7, check8;
            for (int t = 0; t < ize; t++) {
                for (int k = 0; k < ize; k++) {
                    check1 = true; check2 = true; check3 = true; check4 = true; check5 = true; check6 = true; check7 = true; check8 = true;
                    if (space[t][k] == ' ') {
                        for (int a = 2; a < pointtowin - 1; a++) {
                            if (space[t + 1][k + 1] != space[t + a][k + a] || space[t + 1][k + 1] != mark1) { check1 = false; }
                            if (space[t + 1][k] != space[t + a][k] || space[t + 1][k] != mark1) { check2 = false; }
                            if (space[t - 1][k + 1] != space[t - a][k + a] || space[t - 1][k + 1] != mark1) { check3 = false; }
                            if (space[t][k + 1] != space[t][k + a] || space[t][k + 1] != mark1) { check4 = false; }
                            if (space[t - 1][k - 1] != space[t - a][k - a] || space[t - 1][k - 1] != mark1) { check5 = false; }
                            if (space[t - 1][k] != space[t - a][k] || space[t - 1][k] != mark1) { check6 = false; }
                            if (space[t + 1][k - 1] != space[t + a][k - a] || space[t + 1][k - 1] != mark1) { check7 = false; }
                            if (space[t][k - 1] != space[t][k - a] || space[t][k - 1] != mark1) { check8 = false; }
                        }
                    }
                    else {
                        check1 = false;
                        check2 = false;
                        check3 = false;
                        check4 = false;
                        check5 = false;
                        check6 = false;
                        check7 = false;
                        check8 = false;
                    }
                    if (check1 == true || check2 == true || check3 == true || check4 == true || check5 == true || check6 == true || check7 == true || check8 == true) {
                        space[t][k] = mark2;
                        gotoxy(4 * t + 2, 11 + k * 2);
                        cout << mark2;
                        t = ize; k = ize; check = false;
                    }
                }
            }
        }
        //random
        if (check == true) {
            int x = 0, y = 0;
            srand(time(0));
            while (space[x][y] != ' ') {
                x = rand() % ize;
                y = rand() % ize;
            }
            gotoxy(4 * x + 2, 11 + y * 2);
            cout << mark2;
            space[x][y] = mark2;
        }
    }

    /*
    else if (difficulty == 4) {//boss
        int turn = 2;
        int x, y;
        if (AIhard(turn, x, y) == 10) {
            gotoxy(4 * x + 2, 2 * y + 11); cout << mark2;
            space[x][y] = mark2;
        }
        else if (AIhard(turn, x, y) == 0) {
            gotoxy(4 * x + 2, 2 * y + 11); cout << mark2;
            space[x][y] = mark2;
        }
        else {
            int x = 0, y = 0;
            srand(time(0));
            while (space[x][y] != ' ') {
                x = rand() % ize;
                y = rand() % ize;
            }
            gotoxy(4 * x + 2, 11 + y * 2);
            cout << mark2;
            space[x][y] = mark2;
        }
    }
    */

    else if (difficulty == 3) {//hard
        // win
        bool check = true;
        for (int i = 0; i < ize; i++)
            for (int j = 0; j < ize; j++) {
                if (space[i][j] == ' ') {
                    space[i][j] = mark2;
                    if (result() == 2) {
                        gotoxy(4 * i + 2, 11 + j * 2);
                        cout << mark2;
                        i = ize; j = ize; check = false;
                    }
                    else space[i][j] = ' ';
                }
            }
        // chan cuoi
        if (check == true) {
            for (int i = 0; i < ize; i++)
                for (int j = 0; j < ize; j++) {
                    if (space[i][j] == ' ') {
                        space[i][j] = mark1;
                        if (result() == 1) {
                            gotoxy(4 * i + 2, 11 + j * 2);
                            cout << mark2;
                            space[i][j] = mark2;
                            i = ize; j = ize; check = false;
                        }
                        else space[i][j] = ' ';
                    }
                }
        }
        //tan cong
        if (check == true) {
            bool check1, check2, check3, check4, check5, check6, check7, check8;
            for (int t = 0; t < ize; t++) {
                for (int k = 0; k < ize; k++) {
                    check1 = true; check2 = true; check3 = true; check4 = true; check5 = true; check6 = true; check7 = true; check8 = true;
                    if (space[t][k] == ' ') {
                        for (int a = 2; a < pointtowin - 1; a++) {
                            if (space[t - 1][k - 1] != space[t + a - 1][k + a - 1] || space[t - 1][k - 1] != mark2) { check1 = false; }
                            if (space[t - 1][k] != space[t + a - 1][k] || space[t - 1][k] != mark2) { check2 = false; }
                            if (space[t + 1][k - 1] != space[t - a + 1][k + a - 1] || space[t + 1][k - 1] != mark2) { check3 = false; }
                            if (space[t][k - 1] != space[t][k + a - 1] || space[t][k - 1] != mark2) { check4 = false; }
                            if (space[t + 1][k + 1] != space[t - a + 1][k - a + 1] || space[t + 1][k + 1] != mark2) { check5 = false; }
                            if (space[t + 1][k] != space[t - a + 1][k] || space[t + 1][k] != mark2) { check6 = false; }
                            if (space[t - 1][k + 1] != space[t + a - 1][k - a + 1] || space[t - 1][k + 1] != mark2) { check7 = false; }
                            if (space[t][k + 1] != space[t][k - a + 1] || space[t][k + 1] != mark2) { check8 = false; }
                        }
                    }
                    else {
                        check1 = false;
                        check2 = false;
                        check3 = false;
                        check4 = false;
                        check5 = false;
                        check6 = false;
                        check7 = false;
                        check8 = false;
                    }
                    if (check1 == true || check2 == true || check3 == true || check4 == true || check5 == true || check6 == true || check7 == true || check8 == true) {
                        space[t][k] = mark2;
                        gotoxy(4 * t + 2, 11 + k * 2);
                        cout << mark2;
                        t = ize; k = ize; check = false;
                    }
                }
            }
        }
        if (check == true) {
            bool check1, check2, check3, check4, check5, check6, check7, check8;
            for (int t = 0; t < ize; t++) {
                for (int k = 0; k < ize; k++) {
                    check1 = true; check2 = true; check3 = true; check4 = true; check5 = true; check6 = true; check7 = true; check8 = true;
                    if (space[t][k] == ' ') {
                        for (int a = 2; a < pointtowin - 1; a++) {
                            if (space[t + 1][k + 1] != space[t + a][k + a] || space[t + 1][k + 1] != mark2) { check1 = false; }
                            if (space[t + 1][k] != space[t + a][k] || space[t + 1][k] != mark2) { check2 = false; }
                            if (space[t - 1][k + 1] != space[t - a][k + a] || space[t - 1][k + 1] != mark2) { check3 = false; }
                            if (space[t][k + 1] != space[t][k + a] || space[t][k + 1] != mark2) { check4 = false; }
                            if (space[t - 1][k - 1] != space[t + a][k + a] || space[t - 1][k - 1] != mark2) { check5 = false; }
                            if (space[t - 1][k] != space[t + a][k] || space[t - 1][k] != mark2) { check6 = false; }
                            if (space[t + 1][k - 1] != space[t - a][k + a] || space[t + 1][k - 1] != mark2) { check7 = false; }
                            if (space[t][k - 1] != space[t][k + a] || space[t][k - 1] != mark2) { check8 = false; }
                        }
                    }
                    else {
                        check1 = false;
                        check2 = false;
                        check3 = false;
                        check4 = false;
                        check5 = false;
                        check6 = false;
                        check7 = false;
                        check8 = false;
                    }
                    if (check1 == true || check2 == true || check3 == true || check4 == true || check5 == true || check6 == true || check7 == true || check8 == true) {
                        space[t][k] = mark2;
                        gotoxy(4 * t + 2, 11 + k * 2);
                        cout << mark2;
                        t = ize; k = ize; check = false;
                    }
                }
            }
        }
        // chan trc
        if (check == true) {
            bool check1, check2, check3, check4, check5, check6, check7, check8;
            for (int t = 0; t < ize; t++) {
                for (int k = 0; k < ize; k++) {
                    check1 = true; check2 = true; check3 = true; check4 = true; check5 = true; check6 = true; check7 = true; check8 = true;
                    if (space[t][k] == ' ') {
                        for (int a = 2; a < pointtowin - 1; a++) {
                            if (space[t - 1][k - 1] != space[t + a - 1][k + a - 1] || space[t - 1][k - 1] != mark1) { check1 = false; }
                            if (space[t - 1][k] != space[t + a - 1][k] || space[t - 1][k] != mark1) { check2 = false; }
                            if (space[t + 1][k - 1] != space[t - a + 1][k + a - 1] || space[t + 1][k - 1] != mark1) { check3 = false; }
                            if (space[t][k - 1] != space[t][k + a - 1] || space[t][k - 1] != mark1) { check4 = false; }
                            if (space[t + 1][k + 1] != space[t - a + 1][k - a + 1] || space[t + 1][k + 1] != mark1) { check5 = false; }
                            if (space[t + 1][k] != space[t - a + 1][k] || space[t + 1][k] != mark1) { check6 = false; }
                            if (space[t - 1][k + 1] != space[t + a - 1][k - a + 1] || space[t - 1][k + 1] != mark1) { check7 = false; }
                            if (space[t][k + 1] != space[t][k - a + 1] || space[t][k + 1] != mark1) { check8 = false; }
                        }
                    }
                    else {
                        check1 = false;
                        check2 = false;
                        check3 = false;
                        check4 = false;
                        check5 = false;
                        check6 = false;
                        check7 = false;
                        check8 = false;
                    }
                    if (check1 == true || check2 == true || check3 == true || check4 == true || check5 == true || check6 == true || check7 == true || check8 == true) {
                        space[t][k] = mark2;
                        gotoxy(4 * t + 2, 11 + k * 2);
                        cout << mark2;
                        t = ize; k = ize; check = false;
                    }
                }
            }
        }
        if (check == true) {
            bool check1, check2, check3, check4, check5, check6, check7, check8;
            for (int t = 0; t < ize; t++) {
                for (int k = 0; k < ize; k++) {
                    check1 = true; check2 = true; check3 = true; check4 = true; check5 = true; check6 = true; check7 = true; check8 = true;
                    if (space[t][k] == ' ') {
                        for (int a = 2; a < pointtowin - 1; a++) {
                            if (space[t + 1][k + 1] != space[t + a][k + a] || space[t + 1][k + 1] != mark1) { check1 = false; }
                            if (space[t + 1][k] != space[t + a][k] || space[t + 1][k] != mark1) { check2 = false; }
                            if (space[t - 1][k + 1] != space[t - a][k + a] || space[t - 1][k + 1] != mark1) { check3 = false; }
                            if (space[t][k + 1] != space[t][k + a] || space[t][k + 1] != mark1) { check4 = false; }
                            if (space[t - 1][k - 1] != space[t - a][k - a] || space[t - 1][k - 1] != mark1) { check5 = false; }
                            if (space[t - 1][k] != space[t - a][k] || space[t - 1][k] != mark1) { check6 = false; }
                            if (space[t + 1][k - 1] != space[t + a][k - a] || space[t + 1][k - 1] != mark1) { check7 = false; }
                            if (space[t][k - 1] != space[t][k - a] || space[t][k - 1] != mark1) { check8 = false; }
                        }
                    }
                    else {
                        check1 = false;
                        check2 = false;
                        check3 = false;
                        check4 = false;
                        check5 = false;
                        check6 = false;
                        check7 = false;
                        check8 = false;
                    }
                    if (check1 == true || check2 == true || check3 == true || check4 == true || check5 == true || check6 == true || check7 == true || check8 == true) {
                        space[t][k] = mark2;
                        gotoxy(4 * t + 2, 11 + k * 2);
                        cout << mark2;
                        t = ize; k = ize; check = false;
                    }
                }
            }
        }
        if (check == true) {
            int count = 0;
            bool check1, check2, check3, check4, check5, check6, check7, check8;
            for (int t = 0; t < ize; t++) {
                for (int k = 0; k < ize; k++) {
                    check1 = true; check2 = true; check3 = true; check4 = true; check5 = true; check6 = true; check7 = true; check8 = true;
                    if (space[t][k] == ' ') {
                        for (int a = 2; a < pointtowin - 2; a++) {
                            if (space[t - 1][k - 1] != space[t + a - 1][k + a - 1] || space[t - 1][k - 1] != mark1) { check1 = false; }
                            if (space[t - 1][k] != space[t + a - 1][k] || space[t - 1][k] != mark1) { check2 = false; }
                            if (space[t + 1][k - 1] != space[t - a + 1][k + a - 1] || space[t + 1][k - 1] != mark1) { check3 = false; }
                            if (space[t][k - 1] != space[t][k + a - 1] || space[t][k - 1] != mark1) { check4 = false; }
                            if (space[t + 1][k + 1] != space[t - a + 1][k - a + 1] || space[t + 1][k + 1] != mark1) { check5 = false; }
                            if (space[t + 1][k] != space[t - a + 1][k] || space[t + 1][k] != mark1) { check6 = false; }
                            if (space[t - 1][k + 1] != space[t + a - 1][k - a + 1] || space[t - 1][k + 1] != mark1) { check7 = false; }
                            if (space[t][k + 1] != space[t][k - a + 1] || space[t][k + 1] != mark1) { check8 = false; }
                        }
                    }
                    else {
                        check1 = false;
                        check2 = false;
                        check3 = false;
                        check4 = false;
                        check5 = false;
                        check6 = false;
                        check7 = false;
                        check8 = false;
                    }
                    if (check1 == true)
                        count++;
                    if (check2 == true)
                        count++;
                    if (check3 == true)
                        count++;
                    if (check4 == true)
                        count++;
                    if (check5 == true)
                        count++;
                    if (check6 == true)
                        count++;
                    if (check7 == true)
                        count++;
                    if (check8 == true)
                        count++;
                    if (count >= 3) {
                        space[t][k] = mark2;
                        gotoxy(4 * t + 2, 11 + k * 2);
                        cout << mark2;
                        t = ize; k = ize; check = false;
                    }
                }
            }
        }
        //random
        if (check == true) {
            int x = 0, y = 0;
            srand(time(0));
            while (space[x][y] != ' ') {
                x = rand() % ize;
                y = rand() % ize;
            }
            gotoxy(4 * x + 2, 11 + y * 2);
            cout << mark2;
            space[x][y] = mark2;
        }
    }
    step2++;
    setcolor(4);
}

void update() {
    int n;
    int t = 0;
    ifstream file("data.txt");
    if (file.fail()) {
        createfile();
    }
    else {
        while (!file.eof())
        {
            file >> n;
            if (t == 0)
                player1win = n;
            if (t == 1)
                player2win = n;
            if (t == 2)
                ppgame = n;
            if (t == 3)
                playerwin = n;
            if (t == 4)
                aiwin = n;
            if (t == 5)
                pcgame = n;
            if (t == 6)
                easyw = n;
            if (t == 7)
                normalw = n;
            if (t == 8)
                hardw = n;
            if (t == 9)
                easyd = n;
            if (t == 10)
                normald = n;
            if (t == 11)
                hardd = n;
            t++;
        }
        file.close();
    }
}

void WIN(int x, int y, int winner) {
    if (winner == 4)//player 1 wins
    {
        setcolor(4);
        gotoxy(x, y);     cout << "W           W  II  NN    N";
        gotoxy(x, y + 1); cout << " W         W   II  N N   N";
        gotoxy(x, y + 2); cout << "  W   W   W    II  N  N  N";
        gotoxy(x, y + 3); cout << "   W W W W     II  N   N N";
        gotoxy(x, y + 4); cout << "    W   W      II  N    NN";
        setcolor(7);
    }
    if (winner == 1)//player 1 wins
    {
        setcolor(4);
        gotoxy(x, y);   cout << "PPPPP    1    W           W  II  NN    N  SSSSS";
        gotoxy(x, y + 1); cout << "P   P   11     W         W   II  N N   N  S";
        gotoxy(x, y + 2); cout << "PPPPP  1 1      W   W   W    II  N  N  N  SSSSS";
        gotoxy(x, y + 3); cout << "P        1       W W W W     II  N   N N      S";
        gotoxy(x, y + 4); cout << "P      11111      W   W      II  N    NN  SSSSS";
        setcolor(7);
    }
    if (winner == 2)//player 2 wins
    {
        setcolor(3);
        gotoxy(x, y);   cout << "PPPPP  22222  W           W  II  NN    N  SSSSS";
        gotoxy(x, y + 1); cout << "P   P      2   W         W   II  N N   N  S";
        gotoxy(x, y + 2); cout << "PPPPP  22222    W   W   W    II  N  N  N  SSSSS";
        gotoxy(x, y + 3); cout << "P      2         W W W W     II  N   N N      S";
        gotoxy(x, y + 4); cout << "P      22222      W   W      II  N    NN  SSSSS";
        setcolor(7);
    }
    if (winner == 3)//player LOSE
    {
        setcolor(3);
        gotoxy(x, y);   cout << "L       OOOO   SSSSS  EEEEE";
        gotoxy(x, y + 1); cout << "L      O    O  S      E";
        gotoxy(x, y + 2); cout << "L      O    O  SSSSS  EEEEE";
        gotoxy(x, y + 3); cout << "L      O    O      S  E";
        gotoxy(x, y + 4); cout << "LLLLL   OOOO   SSSSS  EEEEE";
        setcolor(7);
    }
    if (winner == 0)//TIE
    {
        setcolor(2);
        gotoxy(x, y);   cout << "TTTTTTT  II  EEEEE";
        gotoxy(x, y + 1); cout << "   T     II  E";
        gotoxy(x, y + 2); cout << "   T     II  EEEEE";
        gotoxy(x, y + 3); cout << "   T     II  E";
        gotoxy(x, y + 4); cout << "   T     II  EEEEE";
        setcolor(7);
    }
}

int main() {
    music(2);
    intro();
    int surrender = 0;
    update();
menu:
    int t = 0;
    music(2);
    int type = mainboard();
    // PLAY GAME
    if (type == 1 || type == 2) {
        gameinfo();
        PlaySound(NULL, NULL, SND_ASYNC);
    rematch:
        system("cls");
        scoreboard();
        gameboard();
        rematch();

        setcolor(10);
        gotoxy(46, 13);
        for (int i = 0; i < 50; i++)
            cout << hori;
        cout << upright;
        gotoxy(46, 19);
        for (int i = 0; i < 50; i++)
            cout << hori;
        cout << downright;
        for (int i = 0; i < 5; i++) {
            gotoxy(96, 14 + i);
            cout << vert;
        }
        gotoxy(97, 16);
        cout << "<====<  RESULT";
        christmas(100, 1);
        setcolor(7);

        gotoxy(2, 11);
        //GAME
        while (1) {
            //PVP
            if (type == 1) {
                if (move(t % 2 + 1, surrender) == true) {
                    music(1);
                    t++;
                }
                gotoxy(50, 11);
                if (t % 2 + 1 == 1)
                {
                    setcolor(4);
                    cout << "PLAYER 1'S TURN !!!!";
                }
                else
                {
                    setcolor(3);
                    cout << "PLAYER 2'S TURN !!!!";
                }
            }
            //PVC
            if (type == 2) {
                if (move(1, surrender) == true && result() != 1 && result() != 3)
                {
                    AI();
                    music(1);
                }
            }

            scoreboard();
            //SURRENDER
            if (surrender == 1 && type == 1) {
                WIN(45, 14, 2);
                player2win++;
                ppgame++;
                music(3);
                break;
            }
            if (surrender == 2 && type == 1) {
                WIN(45, 14, 1);
                player1win++;
                ppgame++;
                music(3);
                break;
            }
            if (surrender == 1 && type == 2) {//         AI
                WIN(45, 14, 3);
                aiwin++;
                pcgame++;
                easyw++;
                music(4);
                break;
            }
            // RESULT
            if (result() != 0) {
                if (type == 1) { // PVP
                    if (result() == 1) {
                        WIN(45, 14, 1);
                        player1win++;
                    }
                    else if (result() == 2) {
                        WIN(45, 14, 2);
                        player2win++;
                    }
                    else WIN(45, 14, 0);
                    music(3);
                    ppgame++;
                    break;
                }
                if (type == 2) { //PVC
                    if (result() == 1) {
                        WIN(45, 14, 4);
                        playerwin++;
                        if (difficulty == 1)
                            easyd++;
                        else if (difficulty == 2)
                            normald++;
                        else hardd++;
                        music(3);
                        setcolor(7);
                    }
                    else if (result() == 2) {
                        WIN(45, 14, 3);
                        aiwin++;
                        if (difficulty == 1)
                            easyw++;
                        else if (difficulty == 2)
                            normalw++;
                        else hardw++;
                        music(4);
                        setcolor(7);
                    }
                    else WIN(45, 14, 0);;
                    pcgame++;
                    break;
                }
            }
        }
        //REMATCH
        gotoxy(50, 23);
        setcolor(6);
        cout << "DO YOU WANT TO REMATCH ???: ";
        setcolor(23);
        gotoxy(50, 25);
        cout << "press d to change decision, press enter to choose";
        int enter = 100;
        setcolor(14);
        gotoxy(80, 23); cout << "YES     ";
        while (1) {
            char yesorno = ' ';
            while (yesorno != 'd' && yesorno != char(13))
                yesorno = _getch();
            if (yesorno == 'd')
                enter++;
            else
            {
                if (enter % 2 == 0)
                {
                    PlaySound(NULL, NULL, SND_ASYNC);
                    goto rematch;
                }
                else
                {
                    PlaySound(NULL, NULL, SND_ASYNC);
                    system("cls");
                    goto menu;
                }
            }
            gotoxy(80, 23);
            setcolor(14);
            if (enter % 2 == 0) {
                cout << "YES     ";
            }
            else cout << "NO     ";
            setcolor(23);
            gotoxy(50, 25);
            cout << "press d to change decision, press enter to choose";
            setcolor(7);
        }
    }
    // STATISTICS
    if (type == 4) {
        system("cls");
        createfile();
        process();
        gotoxy(15, 25);
        setcolor(6);
        cout << "DO YOU WANT TO RENEW THE PROCESS ???: ";
        setcolor(23);
        gotoxy(20, 27);
        cout << "press d to change decision, press enter to choose";
        int enter = 100;
        setcolor(14);
        gotoxy(53, 25); cout << "YES     ";
        christmas(95, 10);
        while (1) {
            char yesorno = ' ';
            while (yesorno != 'd' && yesorno != char(13))
                yesorno = _getch();
            if (yesorno == 'd')
                enter++;
            else {
                if (enter % 2 == 0) {
                    renew();
                    createfile();
                    goto menu;
                }
                else {
                    system("cls");
                    goto menu;
                }
            }
            gotoxy(53, 25);
            setcolor(14);
            if (enter % 2 == 0) {
                cout << "YES     ";
            }
            else cout << "NO     ";
            setcolor(23);
            gotoxy(20, 27);
            cout << "press d to change decision, press enter to choose";
            setcolor(7);
        }
    }
    // MUSIC
    if (type == 3) {
        setcolor(6);
        for (int i = 0; i < 4; i++) {
            gotoxy(55, 17 + i);
            cout << vert;
        }
        gotoxy(55, 16); cout << upleft;
        gotoxy(55, 21); cout << downleft;
        for (int i = 0; i < 30; i++) {
            gotoxy(56 + i, 16);
            cout << hori;
        }
        for (int i = 0; i < 30; i++) {
            gotoxy(56 + i, 21);
            cout << hori;
        }

        int enter = 100;

        // SOUND
        setcolor(9);
        gotoxy(56, 18);
        cout << "on/off game sound: ";
        setcolor(14);
        gotoxy(76, 18); cout << "YES     ";
        setcolor(9);
        gotoxy(20, 27);
        cout << "       press d to change decision, press enter to choose        ";
        while (1) {
            char yesorno = ' ';
            while (yesorno != 'd' && yesorno != char(13))
                yesorno = _getch();
            if (yesorno == 'd')
                enter++;
            else {
                if (enter % 2 == 0) {
                    soundon = 1;
                }
                else {
                    soundon = 0;
                }
                break;
            }
            gotoxy(76, 18);
            setcolor(14);
            if (enter % 2 == 0) {
                cout << "YES     ";
            }
            else cout << "NO     ";
            setcolor(23);
            gotoxy(20, 27);
            cout << "       press d to change decision, press enter to choose        ";
            setcolor(7);
        }

        // MUSIC
        enter = 100;
        setcolor(9);
        gotoxy(56, 20);
        cout << "on/off music: ";
        setcolor(14);
        gotoxy(76, 20); cout << "YES     ";
        while (1) {
            char yesorno = ' ';
            while (yesorno != 'd' && yesorno != char(13))
                yesorno = _getch();
            if (yesorno == 'd')
                enter++;
            else {
                if (enter % 2 == 0) {
                    musicon = 1;
                    goto menu;
                }
                else {
                    musicon = 0;
                    PlaySound(NULL, NULL, SND_ASYNC);
                    goto menu;
                }
            }
            gotoxy(76, 20);
            setcolor(14);
            if (enter % 2 == 0)
                cout << "YES     ";
            else cout << "NO     ";
            setcolor(7);
        }
        setcolor(7);
    }
    return 0;
}