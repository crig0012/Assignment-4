//
//  MainMenu.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "MainMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


MainMenu::MainMenu() : Menu(NULL, NULL)
{
	addButton(new UIButton("ButtonStart"));
    addButton(new UIButton("ButtonLevelEditor"));
	addButton(new UIButton("ButtonSettings"));
    addButton(new UIButton("ButtonExit"));
}

MainMenu::~MainMenu()
{

}

const char* MainMenu::getName()
{
    return MAIN_MENU_SCREEN_NAME;
}

void MainMenu::buttonAction(UIButton* button)
{
    int index = getIndexForButton(button);
    if(index == 0)
    {
		ScreenManager::getInstance()->switchScreen(LEVEL_SELECT_MENU_SCREEN_NAME);
    }
    //else if (index == 2)
    //{
        //ScreenManager::getInstance()->switchScreen(LEVEL_SELECT_MENU_SCREEN_NAME);
    //}
	else if (index == 1)
    {
        //setMode(false);
        ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
    }
	else if (index == 2)
    {
        ScreenManager::getInstance()->switchScreen(SETTINGS_MENU_SCREEN_NAME);
    }
	else if (index == 3)
    {
        exit(1);
    }
}

bool MainMenu::getMode()
{
	return m_GameMode;
}

void MainMenu::setMode(bool mode)
{
	m_GameMode = mode;
}