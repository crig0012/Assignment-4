//
//  LevelEditor.h
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__LevelEditor__
#define __GAM_1514_OSX_Game__LevelEditor__

#include "../Screen Manager/Screen.h"
#include "../UI/UISideMenu.h"
#include "../UI/UIFont.h"

class UISideMenu;
class Level;
class Save;

class LevelEditor : public Screen, public UISideMenuListener
{
public:
    LevelEditor();
    ~LevelEditor();
    
    const char* getName();
    
    void update(double delta);
    void paint();
    void reset();
    
    void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    void mouseLeftClickDownEvent(float positionX, float positionY);
    void mouseLeftClickUpEvent(float positionX, float positionY);
    void setMouseCoordinates(float positionX, float positionY);
    void keyUpEvent(int keyCode);
    
    void loadLevel(const char* levelName);
    void saveLevel(const char* levelName);
    
private:
    void sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex);
    void sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex);
    
    UISideMenu* m_TilesMenu;
	UISideMenu* m_OptionsMenu;
    UISideMenu* m_PickupsMenu;
	UISideMenu* m_SaveMenu;
	UISideMenu* m_LoadMenu;
    Level* m_Level;
    
    bool m_IsMouseDown;
    int m_SelectedTileIndex;
    unsigned int m_TileSize;
    UIFont* m_Font;
    
    float m_MouseX;
    float m_MouseY;
};

#endif /* defined(__GAM_1514_OSX_Game__LevelEditor__) */
