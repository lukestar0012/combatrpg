#include <iostream>
#include <stdlib.h>
#include <map> 
using namespace std; 
                                        //debug (combat turns, 1st cell free of enemys (var) optional:cout)
string enemies [5] = {"ORC", "DWARF", "TROLL", "LEVIATHIN", "DRAGON"}; 

struct World 
{
    public: 
        string** terrain;
        int** population;

        int scale = 10; 
        string biomes [5] = {"VOLCANO", "FOREST", "OCEAN", "FLOWERFEILDS", "MOUNTAINS"};
                    //random number 0-4 decide what biome next, and random number 20-80 for size, possible other biomes (mesa, swamp, )
                    //other stuff: dungeon type table, loot table, randomencounter, villages, races (dragonborn, human, dwarve, elves, seaman,)
                    //ocean: size is doubled, if borders land add a beach
                    //forest: 0-5 for tree type (birch, spruce, oak, sakura, willow), 1/70% density, 
                    //volcano: always 1 large volcano, 30/70% chance of volcanoes being dorment, 1-100% charred/desolate land,
                    //if active 5% chance of eruption every hour, desity, dragons, lava pools
                    //flowerfields: density, size, variety 1-100% continue until full, 
                    //mountains:density, size 100-1000, anything above 850 contains snow,
                    //set world parameters to 10x10 using the vector abave, 

        World (int s)    //constructor
        {
            terrain = new string*[s];
            for(int i = 0; i < s; i++)
                terrain[i] = new string[s]; 
            population = new int*[s];
            for(int i = 0; i < s; i++)
                population[i] = new int[s];
            terraingen ();
            populationgen ();
        }

            //setting up the World and where everything is
        void terraingen()                                        //this works fine
        {
            for (int x = 0; x < scale; x++)
            {
                for (int y = 0; y < scale; y++)
                {
                    int randomterrain = rand () %100 + 1;
                    randomterrain = randomterrain / 25;
                    cout << randomterrain << endl;
                    terrain [x][y] = biomes [randomterrain]; 

                }
            }
    
        }
                            //whether or not somthing is there, not what
        void populationgen()
        {
            for (int x = 0; x < scale; x++)
            {
                for (int y = 0; y < scale; y++)
                {
                    if ((x) != scale/2, (y) != scale/2)
                    {
                        int occupied = rand () %2;                         
                        population [x][y] = occupied;
                    }
                    else 
                        population[x][y] = 0;
                }
            }
           
        }

            //going through with player
        void printWorld()
        {
            for (int x = 0; x < scale; x++)
            {
                for (int y = 0; y < scale; y++)
                {
                    cout << terrain [x][y] << endl; 
                }
            }
        } 
        
};
struct weapon
{
    int attackbonus; 
    string weapontype;
    weapon()
    {
        weapontype = "fist";
        attackbonus = 0;
    }
    weapon(string type)
        {
            weapontype = type;
            if(type == "fist")
            {
                attackbonus = 0;
            }
            else if(type == "sword")
            {
                attackbonus = 2; 
            }
            else 
            {
                attackbonus = 0;
            }
        }
};
struct inventory                            //player inventory
{
    weapon equippedweapon;
    string carriedweapons[2]; 

    inventory()
    {
        equippedweapon=weapon("fist"); 
    } 
    void displayweapons()
    {
        for(int i=0; i < sizeof(carriedweapons); i++)
        {
            cout << carriedweapons[i] <<endl;
        }
    }
    int findweapon(string weaponselection)
    {
        for(int i=0; i < sizeof(carriedweapons); i++)
        {
            if (weaponselection == carriedweapons[i])
            {
                return i; 
            }
        }
        return -1; 
    }
    void equipweapons()
    {
        displayweapons(); 
        string weaponselection;
        cout << "What would you like to equip?\n";
        cin >> weaponselection;
        int weoponfound = findweapon(weaponselection); 
        if (weoponfound > 0 )
        {
            string tempweapon = equipped; 
        }
    }
};
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
struct Enemy                                //enemy stats            dextarity is 1/2 stamina rounded down (for now)
{
    int strength, health, armor, stamina, dexterity, maxstamina; 
    string type; 
    Enemy() 
    {
        
        type = enemies [(int)((rand() %100/25))];  
        cout << "you encounter " + type <<endl; 
        if (type == enemies [0]) //orc
        {
            health = 60, strength = 16, armor = 10, maxstamina = stamina = 5, dexterity = 2;
        }
        if (type == enemies [1]) //dwarf
        {
            health = 45, strength = 14, armor = 15, maxstamina = stamina = 6, dexterity = 3;
        }
        if (type == enemies [2]) //troll
        {
            health = 50, strength = 16, armor = 12, maxstamina = stamina = 3, dexterity = 1;
        }
        if (type == enemies [3]) //leviathan
        {
            health = 100, strength = 17, armor = 12, maxstamina = stamina = 2, dexterity = 1;
        }
        if (type == enemies [4]) //dragon
        {
            health = 100, strength = 14, armor = 17, maxstamina = stamina = 4, dexterity = 2;
        }
    }
    
    int* attack()
    {
        static int attack[3];      
        for (int x = 1; x <=3; x++)
            attack[x] = 0;
        if(stamina <= 0)         //enemy rest
        {
            attack[2] = 1;
            stamina += maxstamina;  
            return attack; 
        }
        else                // enemy attack
        {
            attack[0] = rand() %20+1+(int)strength/4; 
            attack[1] = rand() %8+1+(int)strength/4;
            stamina--;
            return attack;
        }
    }   
};
int combat(player player, Enemy enemy)      //combat
{
    int playerinitiative = player.dexterity/4 + rand()%20;
    int enemyinitiative = enemy.dexterity/4 + rand()%20;
    bool playerturn = playerinitiative > enemyinitiative;
    while(player.health > 0 && enemy.health > 0) 
    {
        if(playerturn)
        {
            cout << "\n\nYour health is ";
            cout << player.health;
            cout << " out of"; 
            cout << player.maxhealth <<endl;

            cout << "Your stamina is ";
            cout << player.stamina;
            cout << " out of"; 
            cout << player.maxstamina <<endl;

            if (enemy.health <= 20)
                cout << "the enemy is bloody! \n\n"; 
            playerturn=false; 
            int* playerattack = player.attack(); 
            if(playerattack[3] == 1) 
            {
                if(player.stamina/4 + rand() %21 > enemy.stamina/4 + rand() %21)
                {
                    cout << " ...you managed to ecape. \n"; 
                    return 2;
                }
                else 
                {
                    cout << "... the " + enemy.type + " catches up. \n";
                }
            }
            else 
            {
                if(playerattack[0] >= enemy.armor )
                {
                    enemy.health -= playerattack[1];
                    cout << "you did ";
                    cout << playerattack[1];
                    cout << " damage! \n";
                }
            }
        }
        else            //enemy move
        {
            playerturn=true; 
            cout << "The " + enemy.type + " is attacking\n";
            int* enemyattack = enemy.attack();
            if (enemyattack[2] == 1)
                cout << "The " + enemy.type + " is resting. \n";
            else if (enemyattack[0] >= player.armor) 
            {
                player.health -= enemyattack[1]; 
                cout << "The " + enemy.type + " hit you for "; 
                cout << enemyattack[1]; 
                cout << " damage \n";
            }
            else 
            cout << "The " + enemy.type + " missed \n";
        }

    }

    if(enemy.health <= 0)
        return 1; 
    else 
        return 0;
}
int main ()
{ 
    int size = 10;
    cout << "blablabla" << endl;
    World World (size);

    player player ((int) size/2, (int) size/2, size);
    while (true)
    {
        if (World.population [player.x][player.y] == 0)
        {
        cout <<World.terrain[player.x][player.y]<< endl;
        player.movement ();
        }
        else 
        {
            Enemy Enemy; 
            int outcome = combat(player,Enemy); 
            if (outcome == 1)
            {
                World.population[player.x][player.y] = 0;
                cout <<"Wou Win\n";
            }
            else if(outcome == 0)
            {
                cout <<"You Lose!";
                break;
            }
            else if(outcome == 2)
            {
                player.movement(); 
            }
        }
    }
};