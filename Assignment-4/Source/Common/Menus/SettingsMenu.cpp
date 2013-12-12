#include "SettingsMenu.h"
#include "../UI/UIButton.h"
#include "../UI/UIToggle.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


SettingsMenu::SettingsMenu() : Menu(NULL, NULL),
	m_SelectedTileIndex(-1)
{
    addButton(new UIToggle("Difficulty", 3));	  //TODO: Make these
	addButton(new UIToggle("Tile", 10));
	addButton(new UIToggle("Tile", 10));
    
    m_Difficulty = 2;

	addButton(new UIButton("Back"));
}

SettingsMenu::~SettingsMenu()
{
	if(m_ButtonMenu != NULL)
	{
		delete m_ButtonMenu;
		m_ButtonMenu = NULL;
	}

	if(m_ToggleMenu != NULL)
	{
		delete m_ToggleMenu;
		m_ToggleMenu = NULL;
	}
}

const char* SettingsMenu::getName()
{
    return SETTINGS_MENU_SCREEN_NAME;
}

void SettingsMenu::toggleAction(UIToggle* toggle)
{
	int index = getIndexForButton(toggle);

	if(index == 0)
    {
		toggle->isToggled();
        
        if(m_Difficulty == 2)
        {
            m_Difficulty = 3;
        }
        else if(m_Difficulty == 1)
        {
            m_Difficulty = 2;
        }
        
        else if(m_Difficulty == 3)
        {
            m_Difficulty = 1;
        }
        ((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->getLevel()->setDifficulty(m_Difficulty);
    }
	else if(index == 1)
	{
		index = getIndexForButton(scoreLimit);
	}
    else if(index == 2)
    {
		toggle->isToggled();
    }
}

void SettingsMenu::buttonAction(UIButton* button)
{
    int index = getIndexForButton(button);

	if (index == 3)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
}

void SettingsMenu::saveSettings()
{
    
}
