#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../Screen Manager/Screen.h"

class GameObject;
class Level;
class UIFont;

class Game : public Screen
{
public:
  Game();
  ~Game();

  //Game lifecycle methods
  void update(double delta);
  void paint();
  void reset();

  //Screen name, must be implemented, it's a pure
  //virtual method in the Screen class
  const char* getName();

  void loadLevel(const char* levelName);
  
  Level* getLevel();

private:
  //Mouse Events
  void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
  void mouseLeftClickUpEvent(float positionX, float positionY);
  void keyUpEvent(int keyCode);

  //Level pointer
  Level* m_Level;
    
  //Temp font pointer
    UIFont* m_Font;
};

#endif