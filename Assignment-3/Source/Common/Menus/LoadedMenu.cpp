



#include "LoadedMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Level Editor/LevelEditor.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Menus/MainMenu.h"


LoadedMenu::LoadedMenu() : Menu(NULL, NULL)
{
    addButton(new UIButton("ButtonLoadFile1"));
    addButton(new UIButton("ButtonLoadFile2"));
    addButton(new UIButton("ButtonLoadFile3"));
	addButton(new UIButton("ButtonLoadFile4"));
    addButton(new UIButton("ButtonLoadFile5"));
    addButton(new UIButton("ButtonLoadFile6"));
}

LoadedMenu::~LoadedMenu()
{

}

const char* LoadedMenu::getName()
{
    return LOAD_MENU_SCREEN_NAME;
}

void LoadedMenu::buttonAction(UIButton* button)
{
	//if(m_Main->getMode() == false)
	//{
		int index = getIndexForButton(button);
		if(index == 0)
		{
			((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->loadLevel("Level-1.bin");
			((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-1.bin");
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
		else if(index == 1)
		{
			((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->loadLevel("Level-2.bin");
			((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-2.bin");
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
		else if (index == 2)
		{
			((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->loadLevel("Level-3.bin");
			((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-3.bin");
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
		else if (index == 3)
		{
			((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->loadLevel("Level-4.bin");
			((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-4.bin");
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
		else if (index == 4)
		{
			((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->loadLevel("Level-5.bin");
			((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-5.bin");
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
		else if (index == 5)
		{
			((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->loadLevel("Level-6.bin");
			((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-6.bin");
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
	/*}
	else
	{
		int index = getIndexForButton(button);
		if(index == 0)
		{
			((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-1.bin");
			ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
		}
		else if(index == 1)
		{
			((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->loadLevel("Level-2.bin");
			((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-2.bin");
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
		else if (index == 2)
		{
			((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->loadLevel("Level-3.bin");
			((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-3.bin");
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
		else if (index == 3)
		{
			((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->loadLevel("Level-4.bin");
			((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-4.bin");
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
		else if (index == 4)
		{
			((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->loadLevel("Level-5.bin");
			((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-5.bin");
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
		else if (index == 5)
		{
			((LevelEditor*)ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME))->loadLevel("Level-6.bin");
			((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->loadLevel("Level-6.bin");
			ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
		}
	}*/
}