#include <map>
struct player 
{
    int x, y, playermaxdist, strength, stamina, maxstamina, health, maxhealth, armor, dexterity;
    std::map<string, int> directions; 
    player::player(int locx, int locy, int worldsize);
    void player::movement();
    int* player::attack();


};