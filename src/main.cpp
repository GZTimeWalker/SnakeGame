#include "Game.h"

#include <iostream>
#include <Windows.h>

using namespace GZ;

int main()
{
    Utils::Init();
    try
    {
        Game* game = new Game();
        game->Main();
    }
    catch (std::exception e)
    {
        MessageBox(NULL, (LPCWSTR)e.what(), TEXT("已触发异常"), MB_OK);
    }
    return 0;
}
