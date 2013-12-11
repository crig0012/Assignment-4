#include "Game.h"
#include "GameObject.h"
#include "Level.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include "../Utils/Utils.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Math/GDRandom.h"
#include "../Math/GDRandomSearch.h"

Game::Game()
{
    //Create the level object
    m_Level = new Level();
	
	//Log::trace("%f, %f", m_Font->getWidth(), m_Font->getHeight());
    
    //Reset everything
    reset();
}

Game::~Game()
{
    //Delete the level object
    if(m_Level != NULL)
    {
        delete m_Level;
        m_Level = NULL;
    }
}

void Game::update(double delta)
{
    if(m_Level != NULL)
    {
        m_Level->update(delta);
    }
    
    
}

void Game::paint()
{
    if(m_Level != NULL)
    {
        m_Level->paint();
    }
}

void Game::reset()
{
    if(m_Level != NULL)
    {
        m_Level->reset();
    }
}

const char* Game::getName()
{
	return GAME_SCREEN_NAME;
}

Level* Game::getLevel()
{
    return m_Level;
}

void Game::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{


	if(m_Level != NULL)
	{
		m_Level->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
	}
}

void Game::mouseLeftClickUpEvent(float positionX, float positionY)
{
    if(m_Level != NULL)
    {
        m_Level->mouseLeftClickUpEvent(positionX, positionY);
    }
}

void Game::keyDownEvent(int keyCode)
{
    if(m_Level != NULL)
    {
        m_Level->keyDownEvent(keyCode);
    }
}

void Game::keyUpEvent(int keyCode)
{
    if(m_Level != NULL)
    {
        m_Level->keyUpEvent(keyCode);
    }

	if(keyCode == KEYCODE_E)
	{
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
		m_Level->reset();
	}
}

void Game::loadLevel(const char* levelName)
{
    m_Level->load(levelName);
}