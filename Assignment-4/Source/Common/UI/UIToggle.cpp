//
//  UIToggle.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "UIToggle.h"
#include "../OpenGL/OpenGL.h"
#include "../Input/Input.h"
#include <sstream>


UIToggle::UIToggle(const char* textureFile, int howManyToggles) : UIButton(textureFile),
    m_ToggledState(NULL),
	m_WhichToggle(0),
    m_IsToggled(false),
	m_MultiToggle(false)
{
	if(howManyToggles != -1)
	{
		m_MultiToggle = true;

		std::stringstream ss;

		for(int i = 0; i < howManyToggles; i++)
		{
			std::string tempName = std::string(textureFile);

			ss<< i;
			std::string temp = ss.str();
			tempName += temp; 

			m_ToggleVector.push_back(new OpenGLTexture(tempName.c_str()));

			ss.str(std::string());
			ss.clear();
		}

		return;
	}

    //There should be a large texture of the same name with
    //'-Toggled' appended to it for the selected state
    std::string toggledTextureFile = std::string(textureFile);
    toggledTextureFile += "-Toggled";
    
    //Create the selected state texture object
    m_ToggledState = new OpenGLTexture(toggledTextureFile.c_str());
}

UIToggle::~UIToggle()
{
	m_MultiToggle = false;
	m_WhichToggle = 0;

    if(m_ToggledState != NULL)
    {
        delete m_ToggledState;
        m_ToggledState = NULL;
    }

	for(int i = 0; i < m_ToggleVector.size(); i++)
	{
		delete m_ToggleVector.at(i);
		m_ToggleVector.at(i) = NULL;
	}
					 
	m_ToggleVector.clear();
}

void UIToggle::paint()
{
	if(m_MultiToggle == true)
	{
		float x = m_CenterPositionX - m_ToggleVector.at(m_WhichToggle)->getSourceWidth() / 2.0f;
        float y = m_CenterPositionY - m_ToggleVector.at(m_WhichToggle)->getSourceHeight() / 2.0f;
		OpenGLRenderer::getInstance()->drawTexture(m_ToggleVector.at(m_WhichToggle), x, y);	
		return;
	}

    if(isToggled() == true)
    {
        float x = m_CenterPositionX - m_ToggledState->getSourceWidth() / 2.0f;
        float y = m_CenterPositionY - m_ToggledState->getSourceHeight() / 2.0f;
        OpenGLRenderer::getInstance()->drawTexture(m_ToggledState, x, y);
    }
    else
    {
        UIButton::paint();
    }
}

bool UIToggle::isToggled()
{
    return m_IsToggled;
}

void UIToggle::setIsToggled(bool isToggled)
{
	if(m_MultiToggle == true)
	{
		m_WhichToggle++;

		if(m_WhichToggle > m_ToggleVector.size())
		{
			m_WhichToggle = 0;
		}

		return;
	}

    m_IsToggled = isToggled;
}

void UIToggle::mouseLeftClickUpEvent(float positionX, float positionY)
{
    float left = m_CenterPositionX - m_SelectedState->getSourceWidth() / 2.0f;
    float right = m_CenterPositionX + m_SelectedState->getSourceWidth() / 2.0f;
    float top = m_CenterPositionY - m_SelectedState->getSourceHeight() / 2.0f;
    float bottom = m_CenterPositionY + m_SelectedState->getSourceHeight() / 2.0f;
    
    if(positionX >= left && positionX <= right && positionY >= top && positionY <= bottom)
    {
        //
        setIsToggled(!isToggled());
    
        //
        if(m_Listener != NULL)
        {
            ((UIToggleListener*)m_Listener)->buttonWasToggled(this);
        }
    }
}

void UIToggle::keyUpEvent(int keyCode)
{
    if(m_IsSelected == true)
    {
        if(keyCode == KEYCODE_RETURN)
        {
            if(m_Listener != NULL)
            {
                ((UIToggleListener*)m_Listener)->buttonWasToggled(this);
            }
        }
    }
}