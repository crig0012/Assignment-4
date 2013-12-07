




#include "Menu.h"


class SettingsMenu : public Menu
{
public:
    SettingsMenu();
    ~SettingsMenu();

    const char* getName();

private:
    void buttonAction(UIButton* button);
};