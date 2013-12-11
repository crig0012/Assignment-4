#include "SaveMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Level Editor/LevelEditor.h"
#include "../Screen Manager/ScreenManager.h"


SaveMenu::SaveMenu() : Menu(NULL, NULL)
{
    addButton(new UIButton("Slot1"));
	addButton(new UIButton("SaveSlots"));
	addButton(new UIButton("Slot3"));
	addButton(new UIButton("Slot4"));
	addButton(new UIButton("Slot5"));
	addButton(new UIButton("Slot6"));
	addButton(new UIButton("Back"));
}

SaveMenu::~SaveMenu()
{

}

const char* SaveMenu::getName()
{
    return SAVE_MENU_SCREEN_NAME;
}

void SaveMenu::buttonAction(UIButton* button)
{
	
    int index = getIndexForButton(button);
    if(index == 0)
    {
		((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->saveLevel("Slot1.bin");
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
    }
    else if(index == 1)
    {
        ((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->saveLevel("Slot2.bin");
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
    }
    else if (index == 2)
    {
        ((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->saveLevel("Slot3.bin");
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
    }
	else if (index == 3)
    {
        ((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->saveLevel("Slot4.bin");
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
    }
	else if (index == 4)
    {
        ((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->saveLevel("Slot5.bin");
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
    }
	else if (index == 5)
    {
        ((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->saveLevel("Slot6.bin");
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
    }
}




