#include "Splash.h"
#include "../UI/UIButton.h"
#include "../Screen Manager/ScreenManager.h"


Splash::Splash() : Menu(NULL, NULL)
{
	addButton(new UIButton("ButtonLoadLevel"));	   //TODO: Make this an actual press space button
}

Splash::~Splash()
{

}

const char* Splash::getName()
{
    return SPLASH_MENU_SCREEN_NAME;
}

void Splash::keyUpEvent(int keyCode)
{
	if(keyCode == KEYCODE_SPACE)
	{
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
	}
}

void Splash::buttonAction(UIButton* button)
{
	int index = getIndexForButton(button);
    if(index == 0)
    {
		ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
}