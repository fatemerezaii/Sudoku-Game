#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <limits>
#include <iomanip>
#include <algorithm>
#define DARK_BLUE "\033[38;5;17m"
#define NEON_BLUE "\033[38;5;33m"
#define PURPLE "\033[38;5;129m"
#define GREEN "\033[32m"
#define DARK GREEN "\033[92;42m"
#define DBLUE "\033[34m"
#define DBLUEBG "\033[44m"
#define PINK "\033[95m"
#define LIGHT PINK "\033[105m"
#define GOLD "\033[43m"
#define RED "\033[31m"
#define RESET "\033[0m"
#define HIGHLIGHT "\033[7m"
#define BLUEBG "\033[48;2;64;224;208m"
using namespace std;
struct Cell
{
    int value = 0;
    bool isFixed = false;
};
struct SudokuBoard
{
    Cell board[9][9];
    int emptyCells = 0;
    bool isSolved = false;
    string difficulty = "";
} sodo;
struct Player
{
    string username = "";
    int gamesPlayed = 0;
    int wins = 0;
    int losses = 0;
    int score = 0;
};
Player players[100000];
time_t startTime;
int cursorRow = 0, cursorCol = 0;
void loadScoreBoard()
{
    int count = 0;
    ifstream fin("scoreBoard.txt");
    if (!fin)
    {
        return;
    }

    fin >> count;
    for (int i = 0; i < count; i++)
    {
        fin >> players[i].wins >> players[i].losses;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(fin, players[i].username);
    }
    fin.close();
    return;
}
void UpdatePlayer(int index, bool win)
{
    int count = 0;
    ifstream fin("scoreBoard.txt");
    if (!fin)
    {
        return;
    }

    fin >> count;
    if (win)
    {
        players[index].wins++;
    }
    else
    {
        players[index].losses++;
    }
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (players[j].wins > players[i].wins || (players[j].wins == players[i].wins && players[j].losses < players[i].losses))
            {
                swap(players[i], players[j]);
            }
        }
    }
    fin.close();
    ofstream fout("scoreBoard.txt");
    fout << count << endl;
    for (int i = 0; i < count; i++)
    {
        fout << players[i].wins << " " << players[i].losses << " " << players[i].username << endl;
    }
    fout.close();
}
int SignIn()
{
    int count = 0;
    ifstream fin("scoreBoard.txt");
    if (!fin)
    {
        return 0;
    }

    fin >> count;
    for (int i = 0; i < count; i++)
    {
        fin >> players[i].wins >> players[i].losses;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(fin, players[i].username);
    }

    string username;
    cout << DBLUE << "Please enter your username: " << RESET;
    getline(cin, username);
    system("cls");
    for (int i = 0; i < count; i++)
    {
        if (players[i].username == username)
        {
            cout << PURPLE << username << DBLUE << " you're back! :> " << endl
                 << "Press any key to return..." << endl
                 << RESET << endl;
            _getch();
            return i;
        }
    }
    players[count].username = username;
    players[count].wins = 0;
    players[count].losses = 0;
    count++;
    ofstream fout("scoreBoard.txt");
    fout << count << endl;
    for (int i = 0; i < count; i++)
    {
        fout << players[i].wins << " "
             << players[i].losses << " "
             << players[i].username << endl;
    }
    fout.close();

    cout << PURPLE << username << DBLUE << " now you're one of us! :>" << endl
         << "Press any key to return..." << endl
         << RESET << endl;
    _getch();
    return count - 1;
}
void ScoreBoard()
{
    int count = 0;
    ifstream fin("scoreBoard.txt");
    if (!fin)
    {
        cout << "Failed to open file." << endl;
        _getch();
        return;
    }
    fin >> count;
    for (int i = 0; i < count; i++)
    {
        fin >> players[i].wins >> players[i].losses;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(fin, players[i].username);
    }
    fin.close();
    int nameWidth = 10;
    for (int i = 0; i < count; i++)
    {
        nameWidth = max(nameWidth, (int)players[i].username.length());
    }
    cout << "||====||" << string(nameWidth + 2, '=') << "||========||========||" << endl;
    cout << "|| #  || " << setw(nameWidth) << left << "PLAYER"
         << " || WINS   || LOSSES ||" << endl;
    cout << "||====||" << string(nameWidth + 2, '=') << "||========||========||" << endl;

    for (int i = 0; i < count; i++)
    {

        cout << "|| " << setw(2) << left << i + 1
             << " || " << setw(nameWidth) << left << players[i].username
             << " || " << setw(6) << left << players[i].wins
             << " || " << setw(6) << left << players[i].losses
             << " ||" << endl;
    }
    cout << "||====||" << string(nameWidth + 2, '=') << "||========||========||" << endl;

    cout << endl
         << "Press any key to return...";
    _getch();
}
int RunMenu(string options[], int count)
{
    int selected = 0;
    while (true)
    {
        system("cls");
        cout << DBLUE << "Choose one." << RESET << endl;

        for (int i = 0; i < count; i++)
        {
            if (i == selected)
            {
                cout << DBLUE << "> " << DBLUEBG << options[i] << RESET << endl;
            }
            else
                cout << "  " << DBLUE << options[i] << endl
                     << RESET;
        }

        int key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
            {
                selected--;
                if (selected < 0)
                {
                    selected = count - 1;
                }
            }
            else if (key == 80)
            {
                selected++;
                if (selected >= count)
                {
                    selected = 0;
                }
            }
        }
        else if (key == 13)
        {
            return selected;
        }
    }
    return selected;
}
void Print(SudokuBoard &s)
{
    time_t now = time(0);
    int elapsed = difftime(now, startTime);
    int minutes = elapsed / 60;
    int seconds = elapsed % 60;
    cout << GOLD << "Time: "
         << minutes << ":"
         << (seconds < 10 ? "0" : "") << seconds
         << RESET << endl;
    cout << DARK_BLUE << "===================================================" << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << DARK_BLUE << "||  " << RESET;
        for (int j = 0; j < 9; j++)
        {
            bool isCursor = (i == cursorRow && j == cursorCol);
            if (isCursor)
                cout << HIGHLIGHT;
            if (s.board[i][j].value == 0)
            {
                if (isCursor)
                {
                    if (j == 8)
                        cout << DARK_BLUE << HIGHLIGHT << "." << RESET << DARK_BLUE << "  ||" << RESET;
                    else if (j % 3 == 2)
                        cout << DARK_BLUE << HIGHLIGHT << "." << RESET << DARK_BLUE << "  || " << RESET;
                    else
                        cout << DARK_BLUE << HIGHLIGHT << "." << RESET << DARK_BLUE << "  | " << RESET;
                }
                else
                {
                    if (j == 8)
                        cout << DARK_BLUE << "." << "  ||" << RESET;
                    else if (j % 3 == 2)
                        cout << DARK_BLUE << "." << "  || " << RESET;
                    else
                        cout << DARK_BLUE << "." << "  | " << RESET;
                }
            }
            else
            {
                if (s.board[i][j].isFixed)
                {
                    if (j == 8)
                        cout << PURPLE << s.board[i][j].value << RESET << DARK_BLUE << "  ||" << RESET;
                    else if (j % 3 == 2)

                        cout << PURPLE << s.board[i][j].value << RESET << DARK_BLUE << "  || " << RESET;
                    else
                        cout << PURPLE << s.board[i][j].value << RESET << DARK_BLUE << "  | " << RESET;
                }
                else
                {
                    if (j == 8)
                        cout << NEON_BLUE << s.board[i][j].value << RESET << DARK_BLUE << "  ||" << RESET;
                    else if (j % 3 == 2)

                        cout << NEON_BLUE << s.board[i][j].value << RESET << DARK_BLUE << "  || " << RESET;
                    else
                        cout << NEON_BLUE << s.board[i][j].value << RESET << DARK_BLUE << "  | " << RESET;
                }
            }
        }
        if (i == 8)
        {
            cout << endl
                 << DARK_BLUE << "===================================================" << RESET << endl;
        }
        else if (i % 3 == 2)
        {
            cout << endl
                 << DARK_BLUE << "||===============||==============||==============||" << RESET << endl;
        }
        else
        {
            cout << endl
                 << DARK_BLUE << "||-----|----|----||----|----|----||----|----|----||" << RESET << endl;
        }
    }
    cout << endl
         << DBLUE << "Press Esc to return..." << RESET << endl;
}
void DeleteNumber(SudokuBoard &s, int &move)
{
    while (true)
    {
        system("cls");
        if (move > 1)
            cout << DBLUE << move << " moves left." << RESET << endl;
        else if (move == 1)
            cout << DBLUE << "Only one move left!" << RESET << endl;
        Print(sodo);
        int key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72 && cursorRow > 0)
            {
                cursorRow--;
            }
            else if (key == 80 && cursorRow < 8)
            {
                cursorRow++;
            }
            else if (key == 75 && cursorCol > 0)
            {
                cursorCol--;
            }
            else if (key == 77 && cursorCol < 8)
            {
                cursorCol++;
            }
        }
        else if (key == 13)
        {
            int row = cursorRow, col = cursorCol;
            if (s.board[row][col].isFixed)
            {
                cout << endl
                     << DBLUE << "This cell is fixed." << endl
                     << "Press any key..." << RESET << endl;
                move--;
                _getch();
            }
            else if (s.board[row][col].value == 0)
            {
                cout << endl
                     << DBLUE << "This cell is empty." << endl
                     << "Press any key..." << RESET << endl;
                move--;
                _getch();
            }
            else
            {
                s.board[row][col].value = 0;
                move--;
                Print(s);
                cout << endl
                     << endl;
                s.emptyCells++;
            }
        }
        else if (key == 27)
        {
            return;
        }
    }
    return;
}
bool CheckNumber(SudokuBoard &s, int number, int row, int col)
{
    for (int i = 0; i < 9; i++)
    {
        if (s.board[row][i].value == number)
        {
            return false;
        }
        if (s.board[i][col].value == number)
        {
            return false;
        }
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (s.board[startRow + i][startCol + j].value == number)
            {
                return false;
            }
        }
    }
    return true;
}
void EnterNumber(SudokuBoard &s, int &move)
{
    while (true)
    {
        system("cls");
        if (move == 0)
        {
            cout << RED << "--------------" << endl
                 << "| GAME OVER! |" << endl
                 << "--------------" << RESET << endl
                 << endl
                 << RED << "Difficulty: " << s.difficulty << RESET << endl
                 << endl;
            int index = SignIn();
            UpdatePlayer(index, false);
            return;
        }
        if (s.emptyCells == 0)
        {
            s.isSolved = true;
            cout << GREEN << "---------------" << endl
                 << "| YOU GOT IT! |" << endl
                 << "---------------" << endl
                 << endl
                 << RESET
                 << GREEN << "Difficulty: " << s.difficulty << endl
                 << endl
                 << move << " moves left" << RESET << endl
                 << endl;
            int index = SignIn();
            UpdatePlayer(index, true);
            return;
        }
        if (move > 1)
        {
            cout << DBLUE << move << " moves left." << RESET << endl;
        }
        else if (move == 1)
        {
            cout << DBLUE << "Only one move left!" << RESET << endl;
        }
        Print(s);
        int key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72 && cursorRow > 0)
            {
                cursorRow--;
            }
            else if (key == 80 && cursorRow < 8)
            {
                cursorRow++;
            }
            else if (key == 75 && cursorCol > 0)
            {
                cursorCol--;
            }
            else if (key == 77 && cursorCol < 8)
            {
                cursorCol++;
            }
        }
        else if (key >= '1' && key <= '9')
        {
            int row = cursorRow, col = cursorCol;
            if (s.board[row][col].isFixed)
            {
                cout << endl
                     << DBLUE << "This cell is fixed." << endl
                     << "Press any key..." RESET << endl;
                move--;
                _getch();
            }
            else if (s.board[row][col].value != 0)
            {
                cout << endl
                     << DBLUE << "This cell is not empty." << endl
                     << "Press any key..." << RESET << endl;
                move--;
                _getch();
            }
            else
            {
                if (key >= '1' && key <= '9')
                {
                    int number = key - '0';
                    if (CheckNumber(s, number, row, col))
                    {
                        s.board[row][col].value = number;
                        move--;
                        Print(s);
                        s.emptyCells--;
                        cout << endl
                             << endl;
                    }
                    else
                    {
                        cout << endl
                             << DBLUE << "This number already exists. " << endl
                             << "Press any key..." << RESET << endl;
                        move--;
                        _getch();
                    }
                }
                else
                {
                    cout << endl
                         << DBLUE << "Invalid!" << endl
                         << "Press any key..." RESET << endl;
                    move--;
                    _getch();
                }
            }
        }
        else if (key == 27)
        {
            cout << DBLUE << "We gotta get away from here..." << RESET << endl;
            return;
        }
    }
    return;
}
void SaveGame(SudokuBoard &s, int move)
{
    system("cls");
    ofstream fout("SavedGame.txt");
    if (!fout)
    {
        cout << "Failed to open the file.";
        return;
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fout << s.board[i][j].value << " ";
        }
        fout << endl;
    }
    fout << move << " " << s.emptyCells << endl;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fout << s.board[i][j].isFixed << " ";
        }
        fout << endl;
    }
    fout.close();
    cout << DBLUE << "Game is saved." << endl
         << "Press any key to return..." << RESET << endl;
    _getch();
    return;
}
bool FillBoard(SudokuBoard &s, int row, int col)
{
    if (row == 9)
    {
        return true;
    }
    if (col == 9)
    {
        return FillBoard(s, row + 1, 0);
    }
    if (s.board[row][col].value != 0)
    {
        return FillBoard(s, row, col + 1);
    }
    bool used[10] = {false};
    for (int i = 0; i < 9; i++)
    {
        int num = 0;
        do
        {
            num = rand() % 9 + 1;

        } while (used[num]);
        used[num] = true;
        if (CheckNumber(s, num, row, col))
        {
            s.board[row][col].value = num;
            if (FillBoard(s, row, col + 1))
            {
                return true;
            }
            s.board[row][col].value = 0;
        }
    }
    return false;
}
void CheckBoard(SudokuBoard &s)
{
    system("cls");
    SudokuBoard temp = s;
    FillBoard(temp, 0, 0);
    if (FillBoard(temp, 0, 0))
    {
        cout << DBLUE << "So far so good, keep going!" << endl
             << "Press any key to return..." << RESET << endl;
        _getch();
    }

    else
    {
        cout << DBLUE << "My spidey sense tells you're doing it wrong!" << endl
             << "Press any key to return..." << RESET << endl;
        _getch();
    }
}
void GamePlay(SudokuBoard &s, int &move)
{
    startTime = time(0);
    while (move != 0 && !s.isSolved)
    {
        time_t now = time(0);
        char key;
        string options[] = {"Enter Number", "Delete Number", "Check The Board", "Save The Game", "Exit"};
        int selected = RunMenu(options, 5);
        if (selected == 0)
        {
            EnterNumber(s, move);
        }
        else if (selected == 1)
        {
            DeleteNumber(s, move);
        }
        else if (selected == 2)
        {
            CheckBoard(s);
        }
        else if (selected == 3)
        {
            SaveGame(s, move);
        }
        else if (selected == 4)
        {
            return;
        }
    }

    return;
}
void ContinueGame(SudokuBoard &s)
{
    int fix = 0, move = 0;
    ifstream fin("SavedGame.txt");
    if (!fin)
    {
        cout << DBLUE << "Failed to open the file." << RESET << endl;
        _getch();
        return;
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fin >> s.board[i][j].value;
        }
    }
    fin >> move >> s.emptyCells;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fin >> fix;
            if (fix == 0)
            {
                s.board[i][j].isFixed = false;
            }
            else
            {
                s.board[i][j].isFixed = true;
            }
        }
    }
    fin.close();
    GamePlay(s, move);
}
void GenerateBoard(SudokuBoard &s)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            s.board[i][j].isFixed = true;
            s.board[i][j].value = 0;
        }
    }
    FillBoard(s, 0, 0);
    int removed = 0;
    while (removed < s.emptyCells)
    {
        int r = rand() % 9;
        int c = rand() % 9;
        if (s.board[r][c].value != 0)
        {
            s.board[r][c].value = 0;
            s.board[r][c].isFixed = false;
            removed++;
        }
    }
}
int main()
{
    while (true)
    {
        system("cls");
        cout << DBLUE << "Welcome! :)" << endl
             << "Press any key..." << RESET << endl;
        _getch();
        srand(time(0));
        string options[] = {"New Game", "Scoreboard", "Continue saved game", "Exit"};
        int selected = RunMenu(options, 4);
        int level = 0, move = 0;

        if (selected == 0)
        {
            string leveloptions[] = {"Easy (30 blank cells and 200 moves)", "Medium (40 blank cells and 150 moves)", "Hard (60 blank cells and 100 moves)"};
            int select = RunMenu(leveloptions, 3);
            system("cls");
            if (select == 0)
            {
                sodo.difficulty = "easy", sodo.emptyCells = 30, move = 200;
            }
            else if (select == 1)
            {
                sodo.difficulty = "medium", sodo.emptyCells = 40, move = 150;
            }
            else if (select == 2)
            {
                sodo.difficulty = "hard", sodo.emptyCells = 60, move = 100;
            }
            GenerateBoard(sodo);
            GamePlay(sodo, move);
        }
        else if (selected == 1)
        {
            ScoreBoard();
        }
        else if (selected == 2)
        {
            ContinueGame(sodo);
        }
        else if (selected == 3)
        {
            system("cls");
            cout << DBLUE << "See you later! :>" << RESET << endl;
            return 1;
        }
    }
    return 0;
}