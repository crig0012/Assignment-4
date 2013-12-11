#include "Menu.h"

class Splash : public Menu
{
	public:
    Splash();
    ~Splash();

	void keyUpEvent(int keyCode);
    
    const char* getName();

private:
    void buttonAction(UIButton* button);
};