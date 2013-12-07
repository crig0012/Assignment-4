
//
//  UIFont.cpp
//  GAM-1514 OSX Game
//
//  Created by Nikolai Morincull on 2013-11-13.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "UIFont.h"
#include "../OpenGL/OpenGL.h"
#include "../Libraries/jsoncpp/json.h"
#include "../Utils/Utils.h"
#include <fstream>
#include <algorithm>
#include <ctype.h>
#include <math.h>


UIFont::UIFont(const char* fontName, float spaceAmount) :
m_Font(NULL),
m_Text(""),
m_Width(0.0f),
m_Height(0.0f),
m_SpaceAmount(spaceAmount)
{
    // Create the font object
    m_Font = new OpenGLTexture(fontName);
    
    // Parse the font data file (json)
    parseFontData(fontName);
}

UIFont::~UIFont()
{
    //Delete the font texture object
    if(m_Font != NULL)
    {
        delete m_Font;
        m_Font = NULL;
    }
    
    //Cycle through and delete ALL the fontFrame objects in the m_FontData map
    for(std::map<std::string, UIFontFrame*>::iterator it = m_FontData.begin(); it != m_FontData.end(); ++it)
    {
        if(it->second != NULL)
        {
            delete it->second;
            it->second = NULL;
        }
    }
    //Clear the font data map
    m_FontData.clear();
}

void UIFont::draw(float x, float y)
{
    for(int i = 0; i < m_Text.length(); i++)
    {
        //get the character
        std::string character = m_Text.substr(i, 1);
        
        //Is the character a space?
        if(character == " ")
        {
            x += m_SpaceAmount;
            continue;
        }
        
        //get the font frame
        UIFontFrame* fontFrame = getFontFrame(character);
        if(fontFrame != NULL)
        {
            //Set the font textures source frame, based on the fonts frame
            m_Font->setSourceFrame(fontFrame->x, fontFrame->y, fontFrame->width, fontFrame->height);
            
            //Draw the font texture
            OpenGLRenderer::getInstance()->drawTexture(m_Font, x, y + (m_Height - fontFrame->height));
            
            //Increment the x value
            x += fontFrame->width;
        }
    }
}

void UIFont::setText(const char* text)
{
    //Set the text string
    m_Text.assign(text);
    
    //Calculate the text's size based on the font data
    calculateSize();
}

const char* UIFont::getText()
{
    return m_Text.c_str();
}

float UIFont::getWidth()
{
    return m_Width;
}

float UIFont::getHeight()
{
    return m_Height;
}

void UIFont::parseFontData(const char* fontName)
{
    std::string jsonPath = ResourceUtils::getPathForResource(fontName, "json");
    std::ifstream inputStream;
    inputStream.open(jsonPath.c_str());
    
    // Did the input stream open?
    if(inputStream.is_open() == true)
    {
        Json::Value root;
        Json::Reader reader;
        if(reader.parse(inputStream, root) == true)
        {
            Json::Value frames = root["frames"];
            for(int i = 0; i < frames.size(); i++)
            {
                // get the character and the frame data
                std::string character = frames[i] ["filename"].asString();
                Json::Value frame = frames[i] ["frame"];
                
                //Create a new UIFontFrame object
                UIFontFrame* fontFrame = new UIFontFrame();
                fontFrame->x = frame["x"].asUInt();
                fontFrame->y = frame["y"].asUInt();
                fontFrame->width = frame["w"].asUInt();
                fontFrame->height = frame["h"].asUInt();
                
                // Set the font data
                m_FontData[character] = fontFrame;
            }
        }
    }
    //Don't forget to close the input stream
    inputStream.close();
}

void UIFont::calculateSize()
{
    m_Width = 0.0f;
    m_Height = 0.0f;
    
    //safety check the legnth of the text, make sure there is something to process
    if(m_Text.length() > 0)
    {
        for(int i = 0; i < m_Text.length(); i++)
        {
            // Get the character
            std::string character = m_Text.substr(i,1);
            
            //Is the character a space?
            if(character == " ")
            {
                m_Width += m_SpaceAmount;
                continue;
            }
            //Get the font frame
            UIFontFrame* fontFrame = getFontFrame(character);
            if(fontFrame != NULL)
            {
                m_Width += fontFrame->width;
                m_Height = fmaxf(m_Height, fontFrame->height);
            }
        }
    }
}

UIFont::UIFontFrame* UIFont::getFontFrame(std::string character)
{
    UIFontFrame* fontFrame = m_FontData[character];
    
    //If the font frame is null, try changing it to upper case
    if(fontFrame == NULL && islower(character.at(0)) > 0)
    {
        transform(character.begin(), character.end(), character.begin(), ::toupper);
        fontFrame = m_FontData[character];
    }
    
    //If the font frame is still NULL, try changing to lower case
    if(fontFrame == NULL && isupper(character.at(0)) > 0);
    {
        transform(character.begin(), character.end(), character.begin(),::toupper);
        fontFrame = m_FontData[character];
    }
    
    //There is still a chance that fontFrame is NULL, so always
    //saftey check the return value of this function
    
    
    return fontFrame;
}