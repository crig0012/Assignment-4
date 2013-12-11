#include "LevelSelectMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


LevelSelectMenu::LevelSelectMenu() : Menu(NULL, NULL)
{
    addButton(new UIButton("Slot1"));
	addButton(new UIButton("SaveSlots"));
	addButton(new UIButton("Slot3"));
	addButton(new UIButton("Slot4"));
	addButton(new UIButton("Slot5"));
	addButton(new UIButton("Slot6"));
	addButton(new UIButton("Back"));
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
		((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Slot1.bin");
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
        
    }
    else if(index == 1)
    {
		((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Slot2.bin");
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
    }
    else if (index == 2)
    {
        ((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Slot3.bin");
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
    }
    else if (index == 3)
    {
        ((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Slot4.bin");
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
    }
    else if (index == 4)
    {
        ((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Slot5.bin");
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
    }
    else if (index == 5)
    {
        ((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Slot5.bin");
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
    }
	else if (index == 6)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
}
