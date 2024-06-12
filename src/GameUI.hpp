#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include <SFML/Graphics.hpp>
//#include "TableUI.hpp"
//#include "KitchenUI.hpp"
#include <vector>

using namespace sf;
using namespace std;

class Game {
public:
    //Game(const Font& font);
    void handleEvent(RenderWindow& window, Event& event);
    void update();
    void draw(RenderWindow& window);
    void changeWaitressPosition(int tableNumber);
    void setTablePeople(int tableNumber, int peopleNumber);
    void setTableCenterVisible(int tableNumber, bool visible);

private:
    Texture player1Texture;
    Texture player2Texture;
    Texture waitressTexture;
    Texture kitchenTexture;
    Texture floorTexture;
    Texture centerTexture;
    Sprite floorSprite;
    Font font;
    int currentWaitressTable;
    bool waitressInKitchen;
    float earnings; 
    Text earningsText; 
};

#endif