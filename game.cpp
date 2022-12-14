// CSCI 1300 Fall 2022
// Author: Jared Preyer && Scott Davis 
// Recitation: 105 - Reagan Rychecky && 308 - Baljot Kaur
// Project 3 - Class Game
#include <iostream>
#include <vector>
#include <fstream>
#include "Map.h"
#include "Game.h"
#include "Monster.h"
#include "Player.h"
#include "Group.h"
#include "Merchant.h"

using namespace std;
   
int split(string input_string, char separator, string arr[], int arr_size)
{
    //initilize variable for number of pieces the string is split into
    int ind = 0;
    //if string is blank return 0
    if (input_string == "")
    {
        return 0;
    }
    
        //for loop that goes through the entire input string
    for(int i =0; i < input_string.length(); i++)
    {
        // when we dont find the seperator 
        if(input_string[i] != separator) 
        {
            if(ind >= arr_size) // in case the ind gets too big
            {
                return -1;
            }
            arr[ind] += input_string[i];
        }
        else // if we find the seperator add one to the index 
        {
            ind++;
        }
    }
    return ind + 1; // if index = 0 (never run into the seperator it'll return 1)
    
}
/*
Pseudocode Game
1. Declare variables
2. Read file
3. Use getline to read each line
4. Declare a variable to get the amount of splits
5. Use Monster object to push back on the vector
*/
Game::Game()
{

doorsCleared_ = 0;

//Fills a vector with all of the monsters
{
    ifstream fin;
    fin.open("./monster.txt");
    string line;
    Monster monster;
    
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            getline(fin, line);
            string temp_array[2];
            int j = split(line, ',', temp_array, 2);
            if(j == 2)
            {
                monster = Monster(temp_array[0], stoi(temp_array[1]));
                
                monsters_.push_back(monster);
            }
        }
    }    
}

// Defaults the sorcerer
{
    sorcerer_anger_ = 0;
}
// adds 5 rooms and 5 NPCs somwhere on the map
{
    srand(time(NULL));

    for(int i = 0; i < 5; i++)
    {
        map_.addNPC(rand()%12, rand()%12);
        map_.addRoom(rand()%12, rand()%12);
        NPCCount_++;
    }
}

{
    ifstream fin;
    fin.open("./riddles.txt");
    string line;
    string answer;
    
    
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            string temp_array[2];
            getline(fin, line);
            split(line, '~', temp_array, 2);
            riddles_.push_back(temp_array[0]);
            answers_.push_back(temp_array[1]);
        }
    }    
}
}
int Game::NPCCount()
{
    return NPCCount_;
}
/*
Pseudocode printMonsters
1. Use a for loop to get the name and the level of each monsters
*/
void Game::printMonsters()
{
    for(int i = 0; i < 21; i++)
    {
        cout << monsters_.at(i).getName() << endl;
        cout << monsters_.at(i).getLevel() << endl;

    }
}
/*
Pseudocdde setSorerer_anger
set the private variable to the parameter integer
*/
void Game::setSorcerer_anger(int anger)
{
    sorcerer_anger_ = anger;
}
/*
Pseudocode getSorcerer
1. Return the private variable
*/
int Game::getSorcerer_anger()
{
    return sorcerer_anger_;
}

/*
Pseudocode getMap
1. Return map
*/
Map Game::getMap()
{
    return map_;
}
/*
Pseudocdoe printRandomRiddle
1. declare variable
2. prompt the user at the object variables index
3. set the answer to the proper answer at the proper index
*/
void Game::printRandomRiddle()
{
    int x = rand()%20;

    cout << riddles_.at(x) << endl;

    answer_ = answers_.at(x);

}
/*
Pseudocode NPCEncounter
1. Prompt user 
2. Use condition statements to set each player location and player column to true
3. printRandomRiddles
4. prompt user to enter there answer
5. setAnswer to the correct answer
6. Re prompt user with the Inventory Menu options
7. If answered incorrectly it's a monster fight
*/
void Game::NPCEncounter(Group &G, Map &map)
{
    int choice;

    cout << "You have encountered a dungeon dweller! What would you like to do?" << endl;

    cout << "1. Move" << endl;
    cout << "2. Speak to them" << endl;
    cout << "3. Give up" << endl;
    cin >> choice;

    if(choice == 1)
    {
        char choice1;
        cout << "What direction would you like to move in? (wasd)" << endl;
        cin >> choice1;
        move(choice1, map);
        if(map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol()) == true) // get location set to true
        {
            NPCEncounter(G, map);
        }
        if(map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol()) == true)
        {
            G.groupDoor();

            if(G.getKeys() <= 0) // getKeys and check if it is less then or equal to 0
            {
                doorPuzzle(G, map);
            }
        }
    }
    else if(choice == 2)
    {
        string answer;
        cout << "You must solve a riddle, if it is my wares you seek" << endl;

        cout << endl;

        printRandomRiddle();

        cout << endl;

        cout << "Please enter your answer: " << endl;
        cin >> answer;

        if(answer == answer_)
        {
            char answer;
            cout << "You got the right answer!" << endl;
            cout << "Looks like you're worth selling to" << endl;

            int choice20 = 0;
            do{
            
            merchant_.InventoryMenu();
            cin >> choice20;
                switch(choice20)
                {
                    case 1:
                    {
                        merchant_.setCookware();
                        merchant_.displayMenu();
                        break;
                    }
                    case 2:
                    {
                        merchant_.setIngredients();
                        merchant_.displayMenu();
                        break;
                    }
                    case 3:
                    {
                        merchant_.setWeapons(G);
                        merchant_.displayMenu();
                        break;
                    }
                    case 4:
                    {
                        merchant_.setArmor(G);
                        merchant_.displayMenu();
                        break;
                    }
                    case 5:
                    {
                        merchant_.setsTreasures();
                        merchant_.displayMenu();
                        break;
                    }
                    default:
                    cout << "Enjoy your journey team!" << endl;
                    break;
                }
            }while(choice20 != 6);
        }
        else 
        {
            monsterFight(G, map);    
        }

        map.removeNPC(map.getPlayerRow(), map.getPlayerCol());
    }
}

/*
Pseudocode move
1. check if the correct characters are being checked
2. User the groupmove
3. Use map object to facilitate move
4. Use map object to display map
5. Invalid input
*/
void Game::move(char c, Map &m)
{
    if(c == 'w' || c == 'a' || c == 's' || c == 'd')
    {
        group_.groupmove();
        m.move(c);
        m.displayMap();
        
    } 
    else
    {
    cout << "Invalid input" << endl;
    }
}

/*
Pseudocode investigate 
1. Check the random variable. If so user Group object with groupInvest
2. prompt user to found hidden treature
3. Use merchant object to add different inventory
*/
void Game::investigate(Group &G)
{
    
    if(rand()%2 == 1)
    {
        G.groupInvest();
    }
    if(rand()%5 == 2)
    {
        cout << "You found hidden treasure!" << endl;
        if(doorsCleared_ == 1)
        {
            merchant_.addSilver();
            cout << "+1 silver" << endl;
        }
        else if(doorsCleared_ == 2)
        {
            merchant_.addRuby();
            cout << "+1 Ruby" << endl;
        }
        else if(doorsCleared_ == 3)
        {
            merchant_.addEmerald();
            cout << "+1 Emerald" << endl;
        }
        else if(doorsCleared_ == 4)
        {
            merchant_.addDiamond_();
            cout << +"+1 Diamond" << endl;
        }
        else if(doorsCleared_ ==  5)
        {
            cout << "+2 Diamond" << endl;
            cout << "+3 Emerald" << endl;

            merchant_.addDiamond_();
            merchant_.addDiamond_();

            merchant_.addEmerald();
            merchant_.addEmerald();
            merchant_.addEmerald();
        }
        
    }
    if(rand()%10 == 5)
    {
        cout << "You found a key!" << endl;
        G.addKey();
    }
    if(rand()%100 >= 1 || rand()%100 < 40)
    {
        merchant_.misfortune();
    }
}
/*
Pseudocode gatMonsterName
1. two varibles, name and x
2. checks how many rooms are cleared with conditionals
3. each conditional will pick a random monster from the vector with the level respective to how many rooms are cleared
4. sets the name variable to the selected monsters name
5. removes that monster from the vector so there are no repeat monsters
6. returns the name, it will be used in the monster fight function
*/
string Game::getMonsterName()
{
    int x = 0;
    string name;
    if(doorsCleared_ == 0)
    {
        x = rand() % 4;
        name = monsters_.at(x).getName();
        monsters_.erase(monsters_.begin()+x);
        return name;
    }
    else if(doorsCleared_ == 1)
    {
        x = rand()%4 + 4;
        name = monsters_.at(x).getName();
        monsters_.erase(monsters_.begin()+x);
        return name;
    }
    else if(doorsCleared_ == 2)
    {
        x = rand()%4 + 8;
        name = monsters_.at(x).getName();
        monsters_.erase(monsters_.begin()+x);
        return name;
    }
    else if(doorsCleared_ == 3)
    {
        x = rand()%4 + 12;
        name = monsters_.at(x).getName();
        monsters_.erase(monsters_.begin()+x);
        return name;      
    }
    else if(doorsCleared_ == 4)
    {
        x = rand()%4 + 16;
        name = monsters_.at(x).getName();
        monsters_.erase(monsters_.begin()+x);
        return name;      
    }
    return "bossTime";
}
/*
Pseudocode for RoomFight
1.  If priate variable equals 4
2. add private variable
3. Show monster name
4. Subtract private variable by 1
5. If private variable doesn't equal 4
6. add to to private variable
7. show monster name
*/
void Game::roomFight()
{
    if(doorsCleared_ == 4)
    {
        doorsCleared_ = doorsCleared_ +1;
        getMonsterName();
        doorsCleared_ = doorsCleared_ - 1;
    }
    else if(doorsCleared_ != 4)
    {   
        doorsCleared_ = doorsCleared_ + 2;
        getMonsterName();
        doorsCleared_ = doorsCleared_ - 2;
    }
}
/*
Pseudocdoe monsterFight
1. set string to monster name
2. prompt user the monster ahead
3. check if NumWeapons is greater then 0. then return
4. Prompt user if the want to fight or surrender
5. Check for invalid input
6. Calculate variable d
7 Declare variables
8. Calculate if the win the battle
9. If the surrender take the amount they are suppose to
*/
void Game::monsterFight(Group &G, Map &map)
{
    int choice;
    int d = 0;
    string y = getMonsterName();
    cout << y << " AHEAD! THEY LOOK HOSTILE!" << endl;

    // If the number of weapons in inventory is greater than 1
    if(G.getNumWeapons() == 0)
    {
        cout << "Sorry, you need at least one weapon to pick a fight with a monster" << endl;

        return;
    }

    cout << "1. Fight" << endl;
    cout << "2. Surrender" << endl;
    cin >> choice;
    

    while(!(choice == 1 || choice == 2))
    {
        cout <<"Invalid input" << endl;
        return;
    }



    // calculations for variable d
    if
    (
    G.getPlayerAt(0).getWeapon() != G.getPlayerAt(1).getWeapon() &&
    G.getPlayerAt(1).getWeapon() != G.getPlayerAt(2).getWeapon() &&
    G.getPlayerAt(2).getWeapon() != G.getPlayerAt(3).getWeapon() &&
    G.getPlayerAt(3).getWeapon() != G.getPlayerAt(4).getWeapon() 
    ) 
    {
        d = 4;
    }
    //Calculations for variable w
    int w = G.getNumWeapons() + G.getBonus(); 
    //Calculations for variable a
    int a = G.getArmor2();
    //Calculation for variable C
    int c = 1; // for now (Based on rooms cleared)
    //Calculation for variables r
    int r1 = rand()%6 + 1;
    int r2 = rand()%6 + 1;

    if(choice == 1)
    {
        
        if
        (((r1 * w + d) - ((r2*c)/(c))) > 0)
        {
            cout << "You have won the battle!" << endl;
        if(inARoom == true)
        {
            cout << "You cleared the room successfully!" << endl;
            map.removeRoom(map.getPlayerRow(), map.getPlayerCol());
            doorsCleared_++;
            inARoom = false;
        }
            cout << "You've earned " << 10*c << " gold!" << endl;
            cout << "You've earned " << 5*c << " ingredients!" << endl;
            merchant_.addGold(10*c);
            merchant_.addIngrediants(5 * c);
            if(rand()%10 == 2)
            {
                cout << "The monster was hiding a key!" << endl;
                G.addKey();
            }
        }
        else
        {
            int j = rand()%5;
            cout << "You have lost the battle" << endl;

            merchant_.subGold(merchant_.getGold() / 4);

            cout << "The monster took " << (merchant_.getGold() /4) << " gold from the group!" << endl;

            for(int i = 1; i < G.numPlayers(); i++)
            {
                if(G.getPlayerAt(i).checkArmor() == false)
                {
                    if(rand() % 10 == 3)
                    {
                        cout << "You'll forever be scarred from watching the monster dismember " << G.getPlayerAt(i).getName() << " limb for limb." << endl;
                        G.killPlayerAt(i);
                    }
                }
                else if (G.getPlayerAt(i).checkArmor() == true)
                {
                    if(rand() % 20 == 4)
                    {
                        cout << "In order to save yourself, you pushed " << G.getPlayerAt(i).getName() << " out of your way, the monster laughed as you watched them devour your old friend" << endl;
                        G.killPlayerAt(i);
                    }
                }
            }
 
            for(int i = 0; i < G.numPlayers(); i++)
            {
                if(rand()%2 == 1);
                G.getPlayerAt(i).setFullness(G.getPlayerAt(i).getFullness() - 1);
            }

            if(j == 0)
            {
                merchant_.addIngrediants(-5);
                cout << "You lost 5 kg of ingredients" << endl;
            }
            else if( j == 0)
            {
                merchant_.addIngrediants(-10);
                cout << "You lost 10 kg of ingredients" << endl;
            }
            else if(j == 1)
            {
                merchant_.addIngrediants(-15);
                cout << "You lost 15 kg of ingredients" << endl;
            }
            else if(j == 2)
            {
                merchant_.addIngrediants(-20);
                cout << "You lost 20 kg of ingredients" << endl;
            }
            else if(j == 3)
            {
                merchant_.addIngrediants(-25);
                cout << "You have lost 25 kg of ingredients" << endl;
            }
            else if (j ==4)
            {
                merchant_.addIngrediants(-30);
                cout << "You have lost 30 kg of ingredients" << endl;
            }

        }
        int q = rand()%10;

        if(q >= 0 && q < 4)
        {
            merchant_.misfortune();
        }
    }
    else if(choice == 2)
    {
        cout << "You lost the battle" << endl; // one random player is captured
        int a = rand()%4 + 1;
        cout << G.getPlayerAt(a).getName() << " called the monster a homophobic slur, resulting in him getting his face repeatedly bashed against the dungeon wall" << endl;
        G.killPlayerAt(a);
    }

}
/*
Psuedocode CookandEat
1. Prompt User
2. Use probability to check if pot break
3. decrement the pot if broken
4. Increase the amount of fullness 
*/
void Game::CookandEat(Group &G)
{
        // Needs to add the cookware increase in fullness if completed successfully
        int Ceramic = 0; // This function only
        int Frying = 0;
        int Cauldron = 0;
        int cook = 0;
        // cook and eat
        cout << "The cooking ratio is set at a 5(kg):1(ingredient)." << endl;
        cout << "Which cookware item would you like to use ? " << endl;
        cout << "1. Ceramic Pot. " << endl;
        cout << "2. Frying Pan. " << endl;
        cout << "3. Cauldron " << endl;
        cout << "4. Quit." << endl;
        cin >> cook;
        switch(cook)
        {
            case 1:
            {
                cout << "How many of kilograms of ingredients would you like to use with a 5(kg):1(fullness) ratio ? " << endl;
                cin >> Ceramic;
                
                // Need to add the 5:1 Ratio check

                if(Ceramic%5 == 0)
                {
                    int random1 = rand()%4;
                    if(random1 == 0)
                    {
                        cout << "You boke your ceramic!" << endl;
                        merchant_.breakCeramic(Ceramic);
                    }
                    else
                    {
                        for(int i = 0; i < Ceramic; i++)
                        {
                            G.groupEat();
                        }
                    }

                }
                else
                {
                    cout << "Invalid input" << endl;
                    return;
                }
                break;
               

            }
            case 2:
            {
                cout << "How many of kilograms of ingredients would you like to use with a 5(kg):1(fullness) ratio ? " << endl;
                cin >> Frying;


                if(Ceramic%5 == 0)
                {
                    int random1 = rand()%4;
                    if(random1 == 0)
                    {
                        cout << "You boke your frying pan!" << endl;
                        merchant_.breakFrying(Frying);
                    }
                    else
                    {
                        for(int i = 0; i < Frying; i++)
                        {
                            G.groupEat();
                        }
                    }

                }
                else
                {
                    cout << "Invalid input" << endl;
                    return; 
                }
                
            }
            case 3:
            {
                cout << "How many of kilograms of ingredients would you like to use with a 5(kg):1(fullness) ratio ? " << endl;
                cin >> Cauldron;
                
                
                if(Ceramic%5 == 0)
                {
                    int random1 = rand()%4;
                    if(random1 == 0)
                    {
                        cout << "You boke your cauldron!" << endl;
                        merchant_.breakCauldron(Cauldron);
                    }
                    else
                    {
                       for(int i = 0; i < Cauldron; i++)
                        {
                            G.groupEat();
                        }
                    }
                }
                else
                {
                    cout << "invalid input" << endl;
                    return;
                }
            }
            default:
            cout << "Incorrect Input. " << endl;
            return;
        }
}
/*
Pseudocode for printActionMenu
1. Prompt user
*/
void Game::printActionMenu()
{
    int choice;
    // do{
        cout << "Please select an action: " << endl;
        cout << endl;
        cout << "1. Move" << endl;
        cout << "2. Investigate" << endl;
        cout << "3. Pick a Fight" << endl;
        cout << "4. Cook and Eat" << endl;
        cout << "5. Give up" << endl;
}
/*
Pseudocode for doorPuzzle
1. variables for each throw in the game
2. conditional makes sure that player has no keys
3. conditionals check doors throw (random) and players throw (cin)
4. do while loop assures that after 3 ties the player loses
5. if the player wins a monster fight insues and a private variable updates letting telling other fucntions that the player is in a room for the sake of roomscleared incrementation
6. if the player loses they don't get to go into the room, and a monster fight ensues 
*/
void Game::doorPuzzle(Group &G, Map &map)

{
    int boulder = 0;
    int parchment = 1;
    int shears = 2;
    int counter = 0;
    bool winner = false;

    int play = 0;

    int doorPlay = rand()%3;

    if(G.getKeys() == 0)
    {
        cout << "You don't have any keys... Get ready for some Boulder Parchment Shears!" << endl;

        do{
            if(counter != 0)
            {
                cout << "Tie game! Play another round." << endl;
            }
            cout << "Enter your throw: (1: Boulder | 2: Parchment | 3: Shears)" << endl;
            cin >> play;

            if(play == 0 && doorPlay == 2)
            {
                cout << "The door played shears, you win!" << endl;
                winner = true;
                inARoom = true;
                monsterFight(G, map);
                return;
            }
            else if(play == 0 && doorPlay == 1)
            {
                cout << "The door played parchment, you lose!" << endl;
                monsterFight(G, map);
                return;
            }
            else if(play == 1 && doorPlay == 0)
            {
                cout << "The door played shears, you win!" << endl;
                winner = true;
                inARoom = true;
                monsterFight(G, map);
                return;
            }
            else if(play == 1 && doorPlay == 2)
            {
                cout << "The door played shears, you lose!" << endl;
                
                monsterFight(G, map);
                
                return;
            }
            else if(play == 2 && doorPlay == 1)
            {
                winner = true;
                cout << "The door played shears, you win!" << endl;
                inARoom = true;
                monsterFight(G, map);
                return;
            } 
            else if(play == 2 && doorPlay == 0)
            {
                cout << "The door played boulder, you lose!" << endl;
                monsterFight(G, map);
                return;
            }
        counter++;
        }while((doorPlay != play || counter != 2));

        if(counter == 2)
        {
            cout << "You're three attempts are up!" << endl;
        }
    }
}
// returns doors cleared
int Game::getDoorsCleared()
{
    return doorsCleared_;
}
