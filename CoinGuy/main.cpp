#include "Game.h"
#include "MenuState.h"

int main()
{
    Game game;
    game.getStateMachine().change(std::make_unique<MenuState>(game));
    game.getStateMachine().applyPending();
    game.run();

    return 0;
}