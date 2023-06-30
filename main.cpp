#include<Game.h>

int main()
{
    try
    {
        Game game;
        game.setCaption("PACMAN");
        game.Setup();
        game.Run();
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << "\n";
    }
    return 0;
}