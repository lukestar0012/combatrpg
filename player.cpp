#include "player.h"
#include <iostream>
#include <stdlib.h>
#include <map> 
using namespace std; 


struct player 
{
    int x, y, playermaxdist; 
    int strength, stamina, maxstamina, health, maxhealth, armor, dexterity;
    map<string, int> directions; 
    player(int locx, int locy, int worldsize)
    {
        x = locx, y = locy, playermaxdist = worldsize; 
            //mapping controlls to wasd
        directions["w"] = -1, directions["s"] = 1;
        directions["a"] = -1, directions["d"] = 1;
       maxhealth = health = 40, strength = 14, armor = 12, maxstamina = stamina = 6, dexterity = 3; 
    }  
    void movement ()
    {
        cout <<"W | north\n";
        cout <<"S | south\n";
        cout <<"D | east\n";
        cout <<"A | west\n";
        cout <<"Enter the direction you would like to move...\n";
        string wasd; 
        cin >>wasd;
        
        if (wasd == "w" || wasd == "s")
        {
            y += directions[wasd]; 
            if (y < 0 || y >= playermaxdist)
            {
                y -= directions[wasd]; 
                cout <<"you've gone too far, we'll turn you around!\n";
            }
            return;
        }
        if (wasd == "a" || wasd == "d")
        {
            x += directions[wasd]; 
            if (x < 0 || x >= playermaxdist)
            {
                x -= directions[wasd];
                cout <<"you've gone too far, we'll turn you around!\n";
            }
            return;
        }
        else
        {
            cout <<"invalid input. Please try again.\n";
            return;
        }
    }
        //players combat options
    int* attack()
    {
        static int attack[4] = {0,0,0,0};
        for (int x = 1; x <=4; x++)
            attack[x] = 0;       
        int decision;
        cout << "What would you like to do?" <<endl;
        cout << "1 = light attack\n2 = heavy attack \n3 = rest\n4 = run\n"; 
        cin >> decision;
        if (decision == 1)        //light attack
        {
            attack[0] = rand() %20+1+(int)strength/4; 
            attack[1] = rand() %8+1+(int)strength/4;
           stamina--;
            return attack;
        }
        else if (decision == 2)        //heavy attack     
        {
            attack[0] = rand() %20+1+(int)strength/4; 
            attack[1] = rand() %12+1+(int)strength/4;
            stamina-= 2;
            return attack;
        }
        else if (decision == 3)        //rest
        {
            cout << "You rest. \n";
            attack[2]=1;
            stamina += 2;
            if (stamina > maxstamina)
            {
                stamina = maxstamina;
                cout <<"Stamina is at max. \n";
            }
            return attack;
        }
        else if (decision == 4)         //run
        {
            cout <<"You try to escape. and... \n";
            attack[3] = 1;
            return attack; 
        }
        else 
        {
            cout <<"invalid input \n";
            attack[2] = 1;
            return attack; 
        }
    }
};