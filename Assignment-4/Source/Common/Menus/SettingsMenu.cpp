



#include "SettingsMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


SettingsMenu::SettingsMenu() : Menu(NULL, NULL)
{
    addButton(new UIButton("ButtonDifficulty"));
    addButton(new UIButton("ButtonScoreLimit"));
	addButton(new UIButton("ButtonTimeLimit"));
    addButton(new UIButton("ButtonBack"));
}

SettingsMenu::~SettingsMenu()
{

}

const char* SettingsMenu::getName()
{
    return SETTINGS_MENU_SCREEN_NAME;
}

void SettingsMenu::buttonAction(UIButton* button)
{
    int index = getIndexForButton(button);
    if(index == 0)
    {
		
    }
    else if(index == 1)
    {
		
    }
    else if (index == 2)
    {
        
    }
	else if (index == 3)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
}
