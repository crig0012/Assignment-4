//
//  LevelEditor.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "LevelEditor.h"
#include "../Constants/Constants.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../UI/UIToggle.h"




LevelEditor::LevelEditor() :
    m_TilesMenu(NULL),
	m_TilesMenu2(NULL),
    m_Level(NULL),
    m_IsMouseDown(false),
    m_SelectedTileIndex(-1)
{
    //Create the Tiles menu items
    m_TilesMenu = new UISideMenu(this, SideMenuRight);
    m_TilesMenu->addButton(new UIToggle("MenuTileGround"));
	m_TilesMenu->addButton(new UIToggle("MenuTileGrass"));
	m_TilesMenu->addButton(new UIToggle("MenuTileWater"));
	m_TilesMenu->addButton(new UIToggle("MenuTileRock"));
	m_TilesMenu->addButton(new UIToggle("MenuTileHole"));
	m_TilesMenu->addButton(new UIToggle("MenuTileTree"));

	m_TilesMenu2 = new UISideMenu(this, SideMenuLeft);
	m_TilesMenu2->addButton(new UIButton("MenuTileLoad"));
	m_TilesMenu2->addButton(new UIButton("MenuTileSave"));
	m_TilesMenu2->addButton(new UIButton("MenuTileExit"));
    
    //Create the level object
    m_Level = new Level(true);
    
    //Reset everything
    reset();
}

LevelEditor::~LevelEditor()
{
    if(m_Level != NULL)
    {
        delete m_Level;
        m_Level = NULL;
    }
    
    if(m_TilesMenu != NULL)
    {
        delete m_TilesMenu;
        m_TilesMenu = NULL;
    }

	if(m_TilesMenu2 != NULL)
    {
        delete m_TilesMenu2;
        m_TilesMenu2 = NULL;
    }
}

const char* LevelEditor::getName()
{
    return LEVEL_EDITOR_SCREEN_NAME;
}

void LevelEditor::update(double delta)
{
    if(m_Level != NULL)
    {
        m_Level->update(delta);
    }

    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->update(delta);
    }

	if(m_TilesMenu2 != NULL)
    {
        m_TilesMenu2->update(delta);
    }
}

void LevelEditor::paint()
{
    if(m_Level != NULL)
    {
        m_Level->paint();
    }

    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->paint();
    }

	if(m_TilesMenu2 != NULL)
    {
        m_TilesMenu2->paint();
    }
}

void LevelEditor::reset()
{
    if(m_Level != NULL)
    {
        m_Level->reset();
    }
}

void LevelEditor::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{    
    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }
    
    if(m_TilesMenu2 != NULL)
    {
        m_TilesMenu2->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }
    
    if(m_Level != NULL)
    {        
        if(m_SelectedTileIndex != -1 && m_IsMouseDown == true)
        {
			TileType types[] = {TileTypeGround, TileTypeGrass, TileTypeWater, TileTypeRock, TileTypeHole, TileTypeTree};
			TileType type = types[m_SelectedTileIndex];
            m_Level->setTileTypeAtPosition(type, positionX, positionY);
        }
    }
}

void LevelEditor::mouseLeftClickDownEvent(float positionX, float positionY)
{
    //Set the mouse down flag
    m_IsMouseDown = true;
}

void LevelEditor::mouseLeftClickUpEvent(float positionX, float positionY)
{
    //Set the mouse up flag
    m_IsMouseDown = false;
    
    //Safety check the level pointer, then set the new tile type in the index
    if(m_Level != NULL)
    {
        if(m_SelectedTileIndex != -1 && m_TilesMenu->isShowing() == false)
        {
			TileType types[] = {TileTypeGround, TileTypeGrass, TileTypeWater, TileTypeRock, TileTypeHole, TileTypeTree};
			TileType type = types[m_SelectedTileIndex];
            m_Level->setTileTypeAtPosition(type, positionX, positionY);
        }
    }
    
    //Notify the tiles menu of the mouse event
    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->mouseLeftClickUpEvent(positionX, positionY);
    }

	if(m_TilesMenu2 != NULL)
    {
        m_TilesMenu2->mouseLeftClickUpEvent(positionX, positionY);
    }
}

void LevelEditor::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_TAB)
    {
        if(m_TilesMenu != NULL && m_TilesMenu2 != NULL)
        {
            m_TilesMenu->isShowing() == true ? m_TilesMenu->hide() : m_TilesMenu->show();
			m_TilesMenu2->isShowing() == true ? m_TilesMenu2->hide() : m_TilesMenu2->show();
        }
    }
	//else if(keyCode == KEYCODE_S)// Temp, Only for ICA 12, remove during options menu implementation
	//{
	//	if(m_Level != NULL)
	//	{
	//		ScreenManager::getInstance()->switchScreen(SAVE_MENU_SCREEN_NAME);
	//	}
	//}
	//else if(keyCode == KEYCODE_L)
	//{
	//	if(m_Level != NULL)
	//	{
	//		ScreenManager::getInstance()->switchScreen(LOAD_MENU_SCREEN_NAME);
	//	}
	//}
	//else if(keyCode == KEYCODE_E)
	//{
	//	if(m_Level != NULL)
	//	{
	//		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
	//	}
	//}
	else if(keyCode == KEYCODE_T)
	{
		if(m_Level != NULL)
		{
			m_Level->setPickupTypeAtIndex(PickupTypeAmmo, 101);
		}
	}
	else if(keyCode == KEYCODE_Y)
	{
		if(m_Level != NULL)
		{
			m_Level->setPickupTypeAtIndex(PickupTypeUnknown, 101);
		}
	}
    else
    {
        if(m_Level != NULL)
        {
            m_Level->keyUpEvent(keyCode);
        }
    }
}

void LevelEditor::saveLevel(const char* levelName)
{
    m_Level->save(levelName);
}

void LevelEditor::loadLevel(const char* levelName)
{
    m_Level->load(levelName);
}

void LevelEditor::sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex)
{
	
			if(m_TilesMenu2->getIndexForButton(button) == 0)
			{
				ScreenManager::getInstance()->switchScreen(LOAD_MENU_SCREEN_NAME);
			}
			else if(m_TilesMenu2->getIndexForButton(button) == 1)
			{
				ScreenManager::getInstance()->switchScreen(SAVE_MENU_SCREEN_NAME);
			}
			else if(m_TilesMenu2->getIndexForButton(button) == 2)
			{
				ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
			}
	

		m_TilesMenu->hide();
		m_TilesMenu2->hide();
	
}

void LevelEditor::sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex)
{
    if(sideMenu == m_TilesMenu)
    {
        //Un-toggled the previously selected toggle
        UIToggle* previousToggle = (UIToggle*)m_TilesMenu->getButtonForIndex(m_SelectedTileIndex);
        if(previousToggle != NULL)
        {
            previousToggle->setIsToggled(false);
        }
    
        //Set the selected tile index
        m_SelectedTileIndex = toggle->isToggled() == true ? toggleIndex : -1;
        
        //Hide the options and tiles menus
        m_TilesMenu->hide();
		m_TilesMenu2->hide();
    }

}
