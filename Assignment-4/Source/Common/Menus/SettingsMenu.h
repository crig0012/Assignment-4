#include "Menu.h"
#include "../UI/UISideMenu.h"

class UIToggle;
class UISideMenu;

class SettingsMenu : public Menu, public UISideMenuListener
{
public:
    SettingsMenu();
    ~SettingsMenu();

    const char* getName();

	void sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex);
    void sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex);

private:
    void buttonAction(UIButton* button);
	void toggleAction(UIToggle* toggle);    

	UIToggle* scoreLimit;

	int m_SelectedTileIndex;

	UISideMenu* m_ButtonMenu;
	UISideMenu* m_ToggleMenu;
};