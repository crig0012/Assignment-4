



#include "Menu.h"


class SaveMenu : public Menu
{
public:
    SaveMenu();
    ~SaveMenu();
    
    const char* getName();

private:
    void buttonAction(UIButton* button);
};



