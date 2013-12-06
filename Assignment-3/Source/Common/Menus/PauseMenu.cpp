




#include "PauseMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Game/Player.h"
#include "../Screen Manager/ScreenManager.h"


PauseMenu::PauseMenu() : Menu(NULL, NULL)
{
	addButton(new UIButton("ButtonResume"));
    addButton(new UIButton("ButtonQuit"));
}

PauseMenu::~PauseMenu()
{

}

const char* PauseMenu::getName()
{
    return PAUSE_MENU_SCREEN_NAME;
}

void PauseMenu::buttonAction(UIButton* button)
{
    int index = getIndexForButton(button);
    if(index == 0)
    {
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
    }
    else if(index == 1)
    {
        Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
        game->getLevel()->reset();
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
       
    }
}