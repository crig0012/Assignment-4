



#include "Menu.h"


class LevelSelectMenu : public Menu
{
public:
    LevelSelectMenu();
    ~LevelSelectMenu();

    const char* getName();

private:
    void buttonAction(UIButton* button);
};