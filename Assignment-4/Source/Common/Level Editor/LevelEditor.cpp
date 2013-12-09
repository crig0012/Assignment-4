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
#include "../UI/UIFont.h"


LevelEditor::LevelEditor() :
m_TilesMenu(NULL),
m_OptionsMenu(NULL),
m_Level(NULL),
m_IsMouseDown(false),
m_SelectedTileIndex(-1),
m_SaveMenu(NULL),
m_LoadMenu(NULL),
m_TileSize(EMPTY_LEVEL_TILE_SIZE)
{
    m_Font = new UIFont("BitmapFont");
    //m_Font->setText("TEXTY TEXT texts .,()!?:%");
    
    //Log::trace("%f, %f", m_Font->getWidth(), m_Font->getHeight());
    
	//Create the Tiles menu items
	m_TilesMenu = new UISideMenu(this, SideMenuRight);
	m_TilesMenu->addButton(new UIToggle("MenuTileGround"));
	m_TilesMenu->addButton(new UIToggle("MenuTileWater"));
	m_TilesMenu->addButton(new UIToggle("MenuTileTree"));
	m_TilesMenu->addButton(new UIToggle("MenuTileWall"));
	m_TilesMenu->addButton(new UIToggle("MenuTileTower"));
	m_TilesMenu->addButton(new UIToggle("MenuTileChest"));
    
    m_PickupsMenu = new UISideMenu(this, SideMenuRight);
    m_PickupsMenu->addButton(new UIToggle("Health"));
	m_PickupsMenu->addButton(new UIToggle("AmmoV2"));
	m_PickupsMenu->addButton(new UIToggle("Coin"));
    
	m_OptionsMenu = new UISideMenu(this, SideMenuLeft);
	m_OptionsMenu->addButton(new UIButton("MenuOptionSave"));
	m_OptionsMenu->addButton(new UIButton("MenuOptionLoadV2"));
	m_OptionsMenu->addButton(new UIButton("MenuOptionClear"));
	m_OptionsMenu->addButton(new UIButton("MenuOptionExit"));
    
	m_SaveMenu = new UISideMenu(this, SideMenuRight);
	m_SaveMenu->addButton(new UIButton("Slot1"));
	m_SaveMenu->addButton(new UIButton("SaveSlots"));
	m_SaveMenu->addButton(new UIButton("Slot3"));
	m_SaveMenu->addButton(new UIButton("Slot4"));
	m_SaveMenu->addButton(new UIButton("Slot5"));
	m_SaveMenu->addButton(new UIButton("Slot6"));
	m_SaveMenu->addButton(new UIButton("Back"));
    
	m_LoadMenu = new UISideMenu(this, SideMenuLeft);
	m_LoadMenu->addButton(new UIButton("Slot1"));
	m_LoadMenu->addButton(new UIButton("SaveSlots"));
	m_LoadMenu->addButton(new UIButton("Slot3"));
	m_LoadMenu->addButton(new UIButton("Slot4"));
	m_LoadMenu->addButton(new UIButton("Slot5"));
	m_LoadMenu->addButton(new UIButton("Slot6"));
	m_LoadMenu->addButton(new UIButton("Back"));
    
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
    
	if(m_SaveMenu != NULL)
	{
		delete m_SaveMenu;
		m_SaveMenu = NULL;
	}
    
	if(m_OptionsMenu != NULL)
	{
		delete m_OptionsMenu;
		m_OptionsMenu = NULL;
	}
    
	if(m_LoadMenu != NULL)
	{
		delete m_LoadMenu;
		m_LoadMenu = NULL;
	}
    
    if(m_PickupsMenu != NULL)
	{
		delete m_PickupsMenu;
		m_PickupsMenu = NULL;
	}
    
    if(m_Font != NULL)
    {
        delete m_Font;
        m_Font = NULL;
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
    
	if(m_OptionsMenu != NULL)
	{
		m_OptionsMenu->update(delta);
	}
    
	if(m_SaveMenu != NULL)
	{
		m_SaveMenu->update(delta);
	}
    
	if(m_LoadMenu != NULL)
	{
		m_LoadMenu->update(delta);
	}
    
    if(m_PickupsMenu != NULL)
	{
		m_PickupsMenu->update(delta);
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
    
	if(m_OptionsMenu != NULL)
	{
		m_OptionsMenu->paint();
	}
    
	if(m_SaveMenu != NULL)
	{
		m_SaveMenu->paint();
	}
    
	if(m_LoadMenu != NULL)
	{
		m_LoadMenu->paint();
	}
    
    if(m_Font != NULL)
    {
        m_Font->draw(100.0f, 100.0f);
    }
    
    if(m_PickupsMenu != NULL)
    {
        m_PickupsMenu->paint();
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
    setMouseCoordinates(positionX, positionY);
    
	if(m_TilesMenu != NULL)
	{
		m_TilesMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
	}
    
	if(m_OptionsMenu != NULL)
	{
		m_OptionsMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
	}
    
	if(m_SaveMenu != NULL)
	{
		m_SaveMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
	}
    
	if(m_LoadMenu != NULL)
	{
		m_LoadMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
	}
    
    if(m_PickupsMenu != NULL)
    {
        m_PickupsMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }
    
	if(m_Level != NULL)
	{
		if(m_SelectedTileIndex != -1 &&
           m_IsMouseDown == true &&
           m_TilesMenu->isShowing() == false &&
           m_OptionsMenu->isShowing() == false &&
           m_SaveMenu->isShowing() == false &&
           m_LoadMenu->isShowing() == false &&
           m_PickupsMenu->isShowing() == false)
		{
            TileType types[] = {TileTypeGround, TileTypeWater, TileTypeTree, TileTypeWall, TileTypeTower, TileTypeChest};
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
		if(m_SelectedTileIndex != -1 &&
           m_TilesMenu->isShowing() == false &&
           m_OptionsMenu->isShowing() == false &&
           m_SaveMenu->isShowing() == false &&
           m_LoadMenu->isShowing() == false &&
           m_PickupsMenu->isShowing() == false)
		{
            TileType types[] = {TileTypeGround, TileTypeWater, TileTypeTree, TileTypeWall, TileTypeTower, TileTypeChest};
            TileType type = types[m_SelectedTileIndex];
            
			m_Level->setTileTypeAtPosition(type, positionX, positionY);
		}
	}
    
	//Notify the tiles menu of the mouse event
	if(m_TilesMenu != NULL)
	{
		m_TilesMenu->mouseLeftClickUpEvent(positionX, positionY);
	}
    
	if(m_OptionsMenu != NULL)
	{
		m_OptionsMenu->mouseLeftClickUpEvent(positionX, positionY);
	}
    
	if(m_SaveMenu != NULL)
	{
		m_SaveMenu->mouseLeftClickUpEvent(positionX, positionY);
	}
    
	if(m_LoadMenu != NULL)
	{
		m_LoadMenu->mouseLeftClickUpEvent(positionX, positionY);
	}
    
    if(m_PickupsMenu != NULL)
    {
        m_PickupsMenu->mouseLeftClickUpEvent(positionX, positionY);
    }
}

void LevelEditor::keyUpEvent(int keyCode)
{
	if(keyCode == KEYCODE_TAB)
	{
		if(m_TilesMenu != NULL)
		{
			if(m_SaveMenu->isShowing() == true)
				m_SaveMenu->hide();
            if(m_PickupsMenu->isShowing() == true)
                m_PickupsMenu->hide();
            
			m_TilesMenu->isShowing() == true ? m_TilesMenu->hide() : m_TilesMenu->show();
		}
	}
    
	else if(keyCode == KEYCODE_ESCAPE)
	{
		if(m_LoadMenu->isShowing() == true)
			m_LoadMenu->hide();
        
		m_OptionsMenu->isShowing() == true ? m_OptionsMenu->hide() : m_OptionsMenu->show();
	}
    
	else if(keyCode == KEYCODE_C)
	{
		m_Level->randomizeLevel();
	}
    
	else if(keyCode == KEYCODE_S)
	{
		if(m_TilesMenu->isShowing() == true)
			m_TilesMenu->hide();
        if(m_PickupsMenu->isShowing() == true)
            m_PickupsMenu->hide();
        
		m_SaveMenu->isShowing() == true ? m_SaveMenu->hide() : m_SaveMenu->show();
	}
    
	else if(keyCode == KEYCODE_L)
	{
		if(m_OptionsMenu->isShowing() == true)
			m_OptionsMenu->hide();
        
		m_LoadMenu->isShowing() == true ? m_LoadMenu->hide() : m_LoadMenu->show();
	}
    
    else if(keyCode == KEYCODE_P)
    {
        if(m_TilesMenu->isShowing() == true)
			m_TilesMenu->hide();
        if(m_SaveMenu->isShowing() == true)
			m_SaveMenu->hide();
        
        if(m_Level != NULL)
        {
            m_PickupsMenu->isShowing() == true ? m_PickupsMenu->hide() : m_PickupsMenu->show();
        }
    }
    
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

void LevelEditor::setMouseCoordinates(float positionX, float positionY)
{
    m_MouseX = positionX / m_TileSize;
    m_MouseY = positionY / m_TileSize;
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
	if(sideMenu == m_SaveMenu)
	{
		if(buttonIndex == 0)
		{
			m_Level->save("Slot1.bin");
		}
        
		if(buttonIndex == 1)
		{
			m_Level->save("Slot2.bin");
		}
        
		if(buttonIndex == 2)
		{
			m_Level->save("Slot3.bin");
		}
        
		if(buttonIndex == 3)
		{
			m_Level->save("Slot4.bin");
		}
        
		if(buttonIndex == 4)
		{
			m_Level->save("Slot5.bin");
		}
        
		if(buttonIndex == 5)
		{
			m_Level->save("Slot6.bin");
		}
        
		if(buttonIndex == 6)
		{
			m_SaveMenu->hide();
		}
        
		m_LoadMenu->hide();
		m_SaveMenu->hide();
		m_OptionsMenu->hide();
	}
    
	if(sideMenu == m_LoadMenu)
	{
		if(buttonIndex == 0)
		{
			m_Level->load("Slot1.bin");
		}
        
		if(buttonIndex == 1)
		{
			m_Level->load("Slot2.bin");
		}
        
		if(buttonIndex == 2)
		{
			m_Level->load("Slot3.bin");
		}
        
		if(buttonIndex == 3)
		{
			m_Level->load("Slot4.bin");
		}
        
		if(buttonIndex == 4)
		{
			m_Level->load("Slot5.bin");
		}
        
		if(buttonIndex == 5)
		{
			m_Level->load("Slot6.bin");
		}
        
		if(buttonIndex == 6)
		{
			m_LoadMenu->hide();
		}
        
		m_LoadMenu->hide();
		m_SaveMenu->hide();
		m_TilesMenu->hide();
	}
    
	if(sideMenu == m_OptionsMenu)
	{
		if(buttonIndex == 0)
		{
            ScreenManager::getInstance()->switchScreen(SAVE_MENU_SCREEN_NAME);
			keyUpEvent(KEYCODE_S);
			//m_SaveMenu->show();
			//m_OptionsMenu->hide();
		}
        
		if(buttonIndex == 1)
		{
            ScreenManager::getInstance()->switchScreen(LOAD_MENU_SCREEN_NAME);
			//m_LoadMenu->show();
			//m_OptionsMenu->hide();
		}
        
		if(buttonIndex == 2)
		{
			m_Level->load(NULL);
		}
        
		if(buttonIndex == 3)
		{
			ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
		}
        
		if(buttonIndex != 1)
		{
			m_LoadMenu->hide();
			m_OptionsMenu->hide();
			m_TilesMenu->hide();
		}
	}
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
		m_LoadMenu->hide();
		m_TilesMenu->hide();
		m_OptionsMenu->hide();
	}
    
    if(sideMenu == m_PickupsMenu)
    {
        UIToggle* previousToggle = (UIToggle*)m_TilesMenu->getButtonForIndex(m_SelectedTileIndex);
		if(previousToggle != NULL)
		{
			previousToggle->setIsToggled(false);
		}
        
		//Set the selected tile index
		m_SelectedTileIndex = toggle->isToggled() == true ? toggleIndex : -1;
        
		//Hide the options and tiles menus
		m_LoadMenu->hide();
		m_TilesMenu->hide();
		m_OptionsMenu->hide();
        
    }
    
}