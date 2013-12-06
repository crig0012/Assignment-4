



#include "LevelSelectMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


LevelSelectMenu::LevelSelectMenu() : Menu(NULL, NULL)
{
    addButton(new UIButton("ButtonLevel1"));
    addButton(new UIButton("ButtonLevel2"));
	addButton(new UIButton("ButtonLevel3"));
    addButton(new UIButton("ButtonBack"));
}

LevelSelectMenu::~LevelSelectMenu()
{

}

const char* LevelSelectMenu::getName()
{
    return LEVEL_SELECT_MENU_SCREEN_NAME;
}

void LevelSelectMenu::buttonAction(UIButton* button)
{
    int index = getIndexForButton(button);
    if(index == 0)
    {
		((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-1.bin");
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
        
    }
    else if(index == 1)
    {
		((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-2.bin");
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
    else if (index == 2)
    {
        ((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-3.bin");
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
	else if (index == 3)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
}
