#include "SettingsMenu.h"
#include "../UI/UIButton.h"
#include "../UI/UIToggle.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


SettingsMenu::SettingsMenu() : Menu(NULL, NULL),
	m_SelectedTileIndex(-1)
{
    //TODO: Make toggles
	m_ButtonMenu = new UISideMenu(this, SideMenuLeft);
    m_ButtonMenu->addButton(new UIToggle("ButtonDifficulty"));	  //TODO: Make these
	m_ButtonMenu->addButton(new UIToggle("ButtonScoreLimit"));
	m_ButtonMenu->addButton(new UIToggle("ButtonTimeLimit"));
    
	m_ToggleMenu = new UISideMenu(this, SideMenuRight);
	m_ToggleMenu->addButton(new UIToggle("Tile", 9));

	addButton(new UIButton("Back"));

	m_ButtonMenu->show();
	m_ToggleMenu->show();
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
    }
	else if(index == 1)
	{
		index = getIndexForButton(scoreLimit);
	}
    else if(index == 2)
    {
		toggle->isToggled();
    }
    else if (index == 3)
    {
		toggle->isToggled();
    }
}

void SettingsMenu::sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex)
{		 

}
void SettingsMenu::sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex)
{
	if(sideMenu == m_ToggleMenu)
	{
		//Un-toggled the previously selected toggle
		UIToggle* previousToggle = (UIToggle*)m_ToggleMenu->getButtonForIndex(m_SelectedTileIndex);
		if(previousToggle != NULL)
		{
			previousToggle->setIsToggled(false);
		}
        
		//Set the selected tile index
		m_SelectedTileIndex = toggle->isToggled() == true ? toggleIndex : -1;
	}    
}

void SettingsMenu::buttonAction(UIButton* button)
{
    int index = getIndexForButton(button);

	if (index == 0)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
}
