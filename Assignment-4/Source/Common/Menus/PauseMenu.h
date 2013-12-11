#include "Menu.h"

class PauseMenu : public Menu
{
public:
    PauseMenu();
    ~PauseMenu();

    const char* getName();

private:
    void buttonAction(UIButton* button);
};