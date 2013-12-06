




#include "Menu.h"

class MainMenu;

class LoadedMenu : public Menu
{
public:
    LoadedMenu();
    ~LoadedMenu();
    
    const char* getName();

private:
    void buttonAction(UIButton* button);
	MainMenu* m_Main;
};