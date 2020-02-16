#include <iostream>
#include <string>
#include <cstdio>
#include <conio.h>
class Square
{
public:
    bool hasBomb = false;
    int nearBombNum = int();
    bool hidden = true;
    bool fence = false;
    int chosen()
    {
        if (hasBomb == true)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    std::string print()
    {
        if (fence == false)
        {
            if (hidden)
            {
                return "[]";
            }
            else
            {
                if (hasBomb)
                {
                    return "B ";
                }
                else
                {
                    return std::to_string(nearBombNum)+" ";
                }

            }
        }
        else
        {
            return "";
        }
    }
};
void show(Square map[6][6])
{
    for (int i = 0; i <= 5; i++)
    {
        for (int j = 0; j <= 5; j++)
        {
            std::cout << map[i][j].print();
        }
        std::cout << std::endl;
    }
}
int main()
{
    Square map[6][6];
    map[1][2].hasBomb = true;
    map[2][3].hasBomb = true;
    map[3][2].hasBomb = true;
    int bombNum = 3;
    for (int x = 0; x <= 5; x++)
    {
        for (int y = 0; y <= 5; y++)
        {
            if (x == 0 || y == 0 || x == 5 || y == 5)
            {
                map[x][y].nearBombNum = 0;
                map[x][y].fence = true;
            }
        }
    }
    for (int x = 1; x <= 4; x++)
    {
        for (int y = 1; y <= 4; y++)
        {
            if (!map[x][y].hasBomb)
            {
                int num = int();
                for (int x1 = x - 1; x1 <= x + 1; x1++)
                {
                    for (int y1 = y - 1; y1 <= y + 1; y1++)
                    {
                        if (map[x1][y1].hasBomb)
                        {
                            num += 1;
                        }
                    }
                }
                map[x][y].nearBombNum = num;
            }
        }
    }

    int x = int(), y = int(), times = 0;
    for (;;)
    {
        show(map);
        std::cin >> x;
        std::cin >> y;
        map[x+1][y+1].hidden = false;
        if (map[x+1][y+1].hasBomb)
        {
            system("cls");
            show(map);
            std::cout << std::endl << "暴雷" << std::endl;
            system("pause");
            exit(0);
        }
        else
        {
            map[x+1][y+1].hidden = false;
            times += 1;
            system("cls");
        }
        if (times == 13)
        {
            show(map);
            std::cout << std::endl << "成了" << std::endl;
            system("pause");
            exit(0);
        }
    }
}

