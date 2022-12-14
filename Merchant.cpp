// CSCI 1300 Fall 2022
// Author: Jared Preyer && Scott Davis 
// Recitation: 105 - Reagan Rychecky && Recitation 308 Baljot Kaur
// Project 3 - Class 1
#include <iostream>
#include <cstdlib>
#include "Merchant.h"
using namespace std;
/*
Pseudocode Merchant Menu default constructor
1. Make all variables set to zero
2. Except the gold at 100 and
*/
Merchant::Merchant()
{
    club_ = 0;
    spear_ = 0;
    rapier_ = 0;
    axe_ = 0;
    sword_ = 0;
    ingredients_ = 0;
    ceramic_pot_ = 0;
    frying_pan_ = 0;
    cauldron_ = 0;
    armor_ = 0;
    silver_ = 0;
    ruby_ = 0;
    emerald_ = 0;
    diamond_ = 0;
    gem_ = 0;
    gold_ = 100;
}
/*
Pseudocode Merchant getters
1. return the variables in the default contructor that are applicable
*/
int Merchant::getIngredients()
{
    return ingredients_;
}

int Merchant::getWeapons()
{
    return club_ + spear_ + rapier_ + axe_ + sword_;
}
// int Merchant::getCeramicPot()
// {
//     return ceramic_pot_;
// }
int Merchant::getCookware()
{
    // cout <<  "cer pot M" << ceramic_pot_ << endl;
    return ceramic_pot_ + frying_pan_ + cauldron_;
}

int Merchant::getArmor()
{
    return armor_;
}

int Merchant::getTreasures()
{
    return silver_ + ruby_ + emerald_ + diamond_ + gem_;
}
/*
Pseudocode Merchant setArmor
1. Make armor set to 0
2. prompt user for if they would purchace any
3. confirm purchase.
4. Each armor is worth 5 gold points
5. Subtract each armor that they get from their total amount of gold
6. After all reprompt user to the Inventory Menu that shows them how many goods they have
*/
void Merchant::setArmor(Group &G)

{
    int counter = 0;
    int choice7 = 0;
    int howmany7 = 0;
    char choice3;

    cout << "You have entered the armor section. Select the one that applys " << endl;
    cout << "1. Get Armor." << endl;
    cout << "2. Quit Menu." << endl;
    cin >> choice7;
    switch (choice7)
    {
    case 1:
    {
        cout << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)" << endl;
        cin >> howmany7;
        if (howmany7 < 1)
        {
            cout << "Invalid input." << endl;
            break;
        }
        else
        {
            cout << "You want to buy " << howmany7 << " suits(s) of armor for 25 Gold? (y/n)" << endl;
            cin >> choice3;
            if (choice3 == 'y')
            {
                if (howmany7 >= 1)
                {
                    if (gold_ - (howmany7 * 25) < 0)
                    {
                        cout << "Insufficient funds" << endl;
                    }
                    else if (armor_ + howmany7 > 5)
                    {
                        cout << "You can only purchase a maximum of 5 armor pieces, one per player." << endl;
                    }
                    else
                    {
                            for (int i = 0; i < 5; i++)
                            {
                                if (G.getPlayerAt(i).checkArmor() == false)
                                {
                                    G.setArmorAt(i);

                                    counter++;
                                    if (counter == howmany7)
                                    {
                                        break;
                                    }
                                }
                            }
                        G.setArmor2(howmany7);
                        gold_ = gold_ - (howmany7 * 25);
                        armor_ = armor_ + howmany7;
                        cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    }
                    return;
                }
            }
            else
            {
                cout << "You have choosen not to proceed with your purchase." << endl;
                break;
            }
        }
    }
    default:
        cout << endl;
        cout << "You have quit the menu." << endl;
        break;
    }
}
// int Merchant::setCeramicPot(int Ceramic_Pot);
// {
//     ceramic_pot_ = Cerma
// }
/*
Pseudocode Merchant setIngredients
1. Prompt user for how many kg they wish to purchase
2. The ratio is 1 gold/ 1 kg
3. Confirm there purchase
4. prompt User with there remainder goods with their Menu
*/
void Merchant::setIngredients()
{
    int choiceK = 0;
    int howmanyK = 0;
    char k;

    cout << "You have entered the ingredients. Select 1 or 2. " << endl;
    cout << "1. Get Ingredients." << endl;
    cout << "2. Quit." << endl;
    cin >> choiceK;
    switch (choiceK)
    {
    case 1:
    {
        cout << "How many kg of ingredients do you need [1 Gold/kg]? (Enter a positive multiple of 5, or 0 to cancel)" << endl;
        cin >> howmanyK;

        if (howmanyK <= 0 || howmanyK % 5 != 0)
        {
            cout << "Invalid input." << endl;
            return;
        }
        else
        {
            cout << "You want to buy " << howmanyK << " kg of ingredients for " << howmanyK << " Gold? (y/n)" << endl;
            cin >> k;

            if (k == 'y')
            {
                if (howmanyK >= 1)
                {
                    if ((gold_ - howmanyK) < 0)
                    {
                        cout << "Insufficient funds" << endl;
                    }
                    else
                    {
                        gold_ = gold_ - howmanyK;
                        ingredients_ = howmanyK;
                        cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    }
                    return;
                }
            }
            else
            {
                cout << "You have choosen not to proceed with your purchase." << endl;
                break;
            }
        }
    }
    }
}
/*
Pseudocode Merchant getCookware
1. Prompt user for which Pot they want
2. Declare variables for the do while loop
3. Use conditions for all 4 options
4. Use the random number generator. (Each pot has a probability of breaking. If remainder == 0 they have broke their pot)
5. If player tries to buy more then the actual gold they have prompt user with error message
6. After payments have been confirmed. Reprompt menu with updated purchases
*/
void Merchant::setCookware()
{
    int choice = 0;
    int choice1 = 0;
    char choice2;
    int howmany = 0;

    cout << "I have a several types of cookware, which one would you like? " << endl
         << "Each type has a different probability of breaking when used, marked with (XX%)." << endl;

    cout << "Choose one of the following: " << endl
         << " 1. (25%) Ceramic Pot [2 Gold] " << endl
         << " 2. (10%) Frying Pan [10 Gold] " << endl
         << " 3. ( 2%) Cauldron [20 Gold] " << endl
         << " 4. Cancel " << endl;
    cin >> choice1;
    switch (choice1)
    {
    case 1:
    {
        cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
        cin >> howmany;

        if (howmany <= 0)
        {
            cout << "Goodbye" << endl;
            return;
        }
        else
        {
            cout << "You want to buy " << howmany << " Cermaic Pot for 2 Gold? (y/n)" << endl;
            cin >> choice2;

            if (choice2 == 'y')
            {
                if (howmany >= 1)
                {
                    // cout << "how many pots we have before" << ceramic_pot_ << endl;

                    // ceramic_pot_ = howmany;
                    if (gold_ - (howmany * 2) < 0)
                    {
                        cout << "You're broke dumby" << endl;
                    }
                    else
                    {
                        gold_ = gold_ - (howmany * 2);
                        ceramic_pot_ = howmany;
                        cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    }
                    return;
                }
                // int random1 = rand()%3;
                // if(random1 == 0)
                // {
                //     ceramic_pot_ = "Pot Broken:";
                //     ceramic_pot_ --; // decrement items that is broken
                // }
                // else if(random1 == 1)
                // {
                //     ceramic_pot_ = "Cermic Pot is good:";
                //     ingredients_ = ingredients_ + ceramic_pot_; // Comment need to add ingredients into the pot

                // }
                // else if(random1 == 2)
                // {
                //     ceramic_pot_ = "Cermic Pot is gucci:";
                //     ceramic_pot_ = ceramic_pot_ + ingredients_;
                //     // comment need to add ingredients into the pot
                // }
            }
            else
            {
                cout << "You have choosen not to proceed with your purchase." << endl;
                break;
            }
        }
    }
    case 2:
    {

        cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
        cin >> howmany;

        if (howmany <= 0)
        {
            cout << "Goodbye" << endl;
            return;
        }
        else
        {
            cout << "You want to buy " << howmany << " Frying Pan for 10 Gold? (y/n)" << endl;
            cin >> choice2;

            if (choice2 == 'y')
            {
                if (howmany >= 1)
                {
                    if (gold_ - (howmany * 10) < 0)
                    {
                        cout << "Insufficient funds" << endl;
                    }
                    else
                    {
                        gold_ = gold_ - (howmany * 10);
                        frying_pan_ = howmany;
                        cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    }
                    return;
                }
            }
            else
            {
                cout << "You have choosen not to proceed with your purchase." << endl;
                break;
            }
        }
    }
    case 3:
    {
        cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
        cin >> howmany;

        if (howmany <= 0)
        {
            cout << "Goodbye" << endl;
            return;
        }
        else
        {
            cout << "You want to buy " << howmany << " Cauldron(s) for 20 Gold? (y/n)" << endl;
            cin >> choice2;
            if (choice2 == 'y')
            {
                if (howmany >= 1)
                {
                    if (gold_ - (howmany * 20) < 0)
                    {
                        cout << "Insufficient funds" << endl;
                    }
                    else
                    {
                        gold_ = gold_ - (howmany * 20);
                        cauldron_ = howmany;
                        cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    }
                    return;
                }
            }
            else
            {
                cout << "You have choosen not to proceed with your purchase." << endl;
                break;
            }
        }
        case 4:
        {
            return;
        }
    }
    default:
        cout << endl;
        cout << "Invalid input. Please select a valid input. " << endl;
        return;
    }
}

/*
Pseudocode Merchant setWeapons
1. Declare all variables
2. Prompt User with Menu needed
3. Prompt User with which item they would like to purchase
4. set up a do while which with conditions
5. Subtract how many every gold then want from there purchase
6. Reprompt them with the same options until gold is not suffient || they want to exit Menu
*/
void Merchant::setWeapons(Group &G)
{
    int choice = 0;
    int howmany1 = 0;
    int counter = 0;
    char setchoice;
    do
    {

        cout << "I have a plentiful collection of weapons to choose from, what would you like?" << endl
             << "Note that some of them provide you a special bonus in combat, marked by a (+X)." << endl;

        cout << "Choose one of the following:" << endl
             << "1. Stone Club [2 Gold]" << endl
             << "2. Iron Spear [2 Gold]" << endl
             << "3. (+1) Mythril Rapier [5 Gold]" << endl
             << "4. (+2) Flaming Battle-Axe [15 Gold]" << endl
             << "5. (+3) Vorpal Longsword [50 Gold]" << endl
             << "6. Cancel" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> howmany1;
            if (howmany1 <= 0)
            {
                cout << "Horrible input. Try again." << endl;
                return;
            }
            else
            {
                cout << "You want to buy " << howmany1 << " Stone Club(s) for 2 Gold each? (y/n)" << endl;
                cin >> setchoice;
                if (setchoice == 'y')
                {
                    if (howmany1 >= 1)
                    {
                        if (gold_ - (howmany1 * 2) < 0)
                        {
                            cout << "Insufficient funds" << endl;
                        }
                        else if (club_ + sword_ + rapier_ + spear_ + axe_ == 5)
                        {
                            cout << "You already have a weapon for each player" << endl;
                        }
                        else
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                if (G.getPlayerAt(i).getWeapon() == 0)
                                {
                                    G.setPlayerWeaponAt(i, 1);

                                    counter++;
                                    if (counter == howmany1)
                                    {
                                        break;
                                    }
                                }
                            }
                            weapons_++;

                            gold_ = gold_ - (howmany1 * 2);
                            club_ = club_ + howmany1;

                            cout << "Thank you for your patronage! What else can I get for you?" << endl;
                        }
                        return;
                    }
                }
                else
                {
                    cout << "You have choosen not to proceed with your purchase." << endl;
                    break;
                }
            }
        }
        case 2:
        {
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> howmany1;
            if (howmany1 <= 0)
            {
                cout << "Horrible input. Try again." << endl;
                return;
            }
            else
            {
                cout << "You want to buy " << howmany1 << " Iron Spear(s) for 2 Gold? (y/n)" << endl;
                cin >> setchoice;
                if (setchoice == 'y')
                {
                    if (howmany1 >= 1)
                    {
                        if (gold_ - (howmany1 * 2) < 0)
                        {
                            cout << "Insufficient funds" << endl;
                        }
                        else if (club_ + sword_ + rapier_ + spear_ + axe_ == 5)
                        {
                            cout << "You already have a weapon for each player" << endl;
                        }
                        else if(club_ + sword_ + rapier_ + spear_ + axe_ + howmany1 > 5 )
                        {
                            cout << "You don't have enough inventory space to buy that many more weapons" << endl;
                        }
                        else
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                if (G.getPlayerAt(i).getWeapon() == 0)
                                {
                                    G.setPlayerWeaponAt(i, 2);
                                    counter++;
                                    if (counter == howmany1)
                                    {
                                        break;
                                    }
                                }
                            }
                                weapons_++;
                                gold_ = gold_ - (howmany1 * 2);
                                spear_ = howmany1 + spear_;
                                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                            }
                            return;
                        }
                    }
                    else
                    {
                        cout << "You have choosen not to proceed with your purchase." << endl;
                        break;
                    }
                }
            }
        case 3:
        {
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> howmany1;
            if (howmany1 <= 0)
            {
                cout << "Horrible input. Try again." << endl;
                return;
            }
            else
            {
                cout << "You want to buy " << howmany1 << " Mythril Rapier(s) for 5 Gold? (y/n)" << endl;
                cin >> setchoice;
                if (setchoice == 'y')
                {
                    if (howmany1 >= 1)
                    {
                        if (gold_ - (howmany1 * 5) < 0)
                        {
                            cout << "Insufficient funds" << endl;
                        }
                        else if (club_ + sword_ + rapier_ + spear_ + axe_ == 5)
                        {
                            cout << "You already have a weapon for each player" << endl;
                        }
                        else if(club_ + sword_ + rapier_ + spear_ + axe_ + howmany1 > 5 )
                        {
                            cout << "You don't have enough inventory space to buy this many more weapons" << endl;
                        }
                        else
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                if (G.getPlayerAt(i).getWeapon() == 0)
                                {
                                    G.setPlayerWeaponAt(i, 3);
                                    counter++;
                                    if (counter == howmany1)
                                    {
                                        break;
                                    }
                                }
                            }
                                weapons_++;

                                gold_ = gold_ - (howmany1 * 5);
                                rapier_ = howmany1 + rapier_;
                                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                        }
                        return;
                    }
                }
                else
                {
                    cout << "You have choosen not to proceed with your purchase." << endl;
                    break;
                }
            }
        }
        case 4:
        {
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> howmany1;
            if (howmany1 <= 0)
            {
                cout << "Horrible input. Try again." << endl;
                return;
            }
            else
            {
                cout << "You want to buy " << howmany1 << " Flaming Battle-Axe(s) for 15 Gold? (y/n)" << endl;
                cin >> setchoice;
                if (setchoice == 'y')
                {
                    if (howmany1 >= 1)
                    {
                        if (gold_ - (howmany1 * 15) < 0)
                        {
                            cout << "Insufficient funds" << endl;
                        }
                        else if (club_ + sword_ + rapier_ + spear_ + axe_ == 5)
                        {
                            cout << "You already have a weapon for each player" << endl;
                        }
                        else if(club_ + sword_ + rapier_ + spear_ + axe_ + howmany1 > 5 )
                        {
                            cout << "You don't have enough inventory space to buy this many more weapons" << endl;
                        }
                        else
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                if (G.getPlayerAt(i).getWeapon() == 0)
                                {
                                    G.setPlayerWeaponAt(i, 4);
                                    counter++;
                                    if (counter == howmany1)
                                    {
                                        break;
                                    }
                                }
                            }
                            weapons_++;

                            gold_ = gold_ - (howmany1 * 15);
                            axe_ = howmany1 + axe_;
                            cout << "Thank you for your patronage! What else can I get for you?" << endl;
                        }
                        return;
                    }
                }
                else
                {
                    cout << "You have choosen not to proceed with your purchase." << endl;
                    break;
                }
            }
        }
        case 5:
        {
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> howmany1;
            if (howmany1 <= 0)
            {
                cout << "Horrible input. Try again." << endl;
                return;
            }
            else
            {
                cout << "You want to buy " << howmany1 << " Vorpal Longsword(s) for 50 Gold? (y/n)" << endl;
                cin >> setchoice;
                if (setchoice == 'y')
                {
                    if (howmany1 >= 1)
                    {
                        if (gold_ - (howmany1 * 50) < 0)
                        {
                            cout << "Insufficient funds" << endl;
                        }
                        else if (club_ + sword_ + rapier_ + spear_ + axe_ == 5)
                        {
                            cout << "You already have a weapon for each player" << endl;
                        }
                        else if(club_ + sword_ + rapier_ + spear_ + axe_ + howmany1 > 5 )
                        {
                            cout << "You don't have enough inventory space to buy this many more weapons" << endl;
                        }
                        else
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                if (G.getPlayerAt(i).getWeapon() == 0)
                                {
                                    G.setPlayerWeaponAt(i, 5);
                                    counter++;
                                    if (counter == howmany1)
                                    {
                                        break;
                                    }
                                }
                            }
                            

                            gold_ = gold_ - (howmany1 * 50);
                            sword_ = howmany1 + sword_;
                            cout << "Thank you for your patronage! What else can I get for you?" << endl;
                        }
                        return;
                    }
                }
                else
                {
                    cout << "You have choosen not to proceed with your purchase." << endl;
                    break;
                }
            }
        }
        case 6:
        {
            cout << "Goodbye." << endl;
            break;
        }
        default:
            cout << endl;
            cout << "Goodbye Loser!" << endl;
            break;
        }
        }
        while (choice != 6);
    }

    // 1. name is misleading, function refers to selling treasure
// 2. conditonal assures player has treasures to sell
// 3. for each case in the switch statement:
// 4. asks for input for how many player wishes to sell
// 5. adds respective gold for how much they choose to sell
// 6. deincrements amount of treasures player chooses to sell
   void Merchant::setsTreasures()
    {
        int select = 0;
        int silver = 0;
        int ruby = 0;
        int emerald = 0;
        int diamond = 0;
        int Gem = 0;

        cout << "Oh so found a treasure that you want to sell back? " << endl;
        cout << "1. To sell Silver ring (R) - 10 gold pieces each" << endl;
        cout << "2. To sell Ruby necklace (N) - 20 gold pieces each" << endl;
        cout << "3. To sell Emerald bracelet (B) - 30 gold pieces each" << endl;
        cout << "4. To sell Diamond circlet (C) - 40 gold pieces each" << endl;
        cout << "5. To sell Gem - encrusted goblet (G) - 50 gold pieces each" << endl;
        cin >> select;

        if(silver_ >= 1 || ruby_ >= 1 || emerald_ >= 1 || diamond_ >= 1 || gem_ >= 1)
        {
           switch (select)
            {
                case 1:
                {
                    cout << "Congrats on finding a Silver ring. How many would you like to sell? " << endl;
                    cin >> silver;
                    if (silver <= 0)
                    {
                        return;
                    }
                    else if (silver > 1)
                    {
                        gold_ += silver * 10;
                        silver_ = silver_ - silver;
                        cout << "Thank you for your transaction. Your deposit has been made. :)" << endl;
                        break;
                        // Update Merchant inventory for showing that merchant
                    }
                }
                case 2:
                {
                    cout << "Congrats on finding Ruby. How many would you like to sell? " << endl;
                    cin >> ruby;
                    if (ruby <= 0)
                    {
                        return;
                    }
                    else if (ruby > 1)
                    {
                        gold_ += ruby * 20;
                        ruby_ = ruby_ - ruby;
                        cout << "Thank you for your transaction. Your deposit has been made. :)" << endl;
                        break;
                    }
                }
                case 3:
                {
                    cout << "Congrats on finding a Emerald. How many would you like to sell? " << endl;
                    cin >> emerald;
                    if (emerald <= 0)
                    {
                        return;
                    }
                    else if (emerald > 1)
                    {
                        gold_ += emerald * 30;
                        emerald_ = emerald_ - emerald;
                        cout << "Thank you for your transaction. Your deposit has been made. :)" << endl;
                    }
                }
                case 4:
                {
                    cout << "Congrats on finding a Diamond. How many would you like to sell? " << endl;
                    cin >> diamond;
                    if (diamond <= 0)
                    {
                        return;
                    }
                    else if (diamond > 1)
                    {
                        gold_ += diamond * 40;
                        diamond_ = diamond_ - diamond;
                        cout << "Thank you for your transaction. Your deposit has been made. :)" << endl;
                    }
                }
                case 5:
                {
                    cout << "Congrats on finding a Gem. How many would you like to sell? " << endl;
                    cin >> Gem;
                    if (Gem <= 0)
                    {
                        return;
                    }
                    else if (Gem > 1)
                    {
                        gold_ += Gem * 50;
                        gem_ = gem_ - Gem;
                        cout << "Thank you for your transaction. Your deposit has been made. :)" << endl;
                    }
                }
                default:
                cout << "Goodbye." << endl;
                break;
            }
        }
        else
        {
            cout << "Insufficient funds. " << endl;
        }
    }
    /*
    Pseudocode Merchant displayMenu
    1. This Menu will be the general Menu that every setter User
    2. Updates all variables that have been purchased with the correct amount. In each shopping session
    3. This Menu will appear until User is done with purhcasing items
    */
    void Merchant::displayMenu()
    {

        cout << "+-------------+" << endl
             << "| INVENTORY   |" << endl
             << "+-------------+" << endl
             << "| Gold        | " << gold_ << endl
             << "| Ingredients | " << ingredients_ << " kg" << endl
             << "| Cookware    | Pots: " << ceramic_pot_ << " |  Frying Pans: " << frying_pan_ << "| Cauldrons: " << cauldron_ << endl
             << "| Weapons     | Clubs: " << club_ << " | Spears: " << spear_ << " | Rapiers: " << rapier_ << " | Axes: " << axe_ << " | Swords: " << sword_ << endl
             << "| Armor       | " << armor_ << endl
             << "| Treasures   | Silver: " << silver_ << " | Ruby: " << ruby_ << " | Emerald: " << emerald_ << " | Diamond: " << diamond_ << " | Ggem: " << gem_ << endl;
    }
    // deincrements ceramic pot and ingredients respectivly
    // assures ingredeints will never be 0
    void Merchant::breakCeramic(int Ceramic)
    {
        // Ceramic  = Ceramic * 5; // Taking the responsibilites of the input from cook and eat

        // ingredients_ = Ceramic;
        // cout << ingredients_ << endl;
        if(ingredients_ >= Ceramic)
        {
            ingredients_ = ingredients_ - Ceramic;
        }
        
        // cout << ingredients_ << endl;
        // cout << ceramic_pot_ << endl;
        ceramic_pot_--; // One cook for pot
        // cout << ceramic_pot_ << endl;
    }
    //deincrements frying pan and respective ingredients
    // conditional makes sure ingredients is never 0
    void Merchant::breakFrying(int Fry)
    {
        if(ingredients_ >= Fry)
        {
            ingredients_ = ingredients_ - Fry;
        }
        frying_pan_--;
    }
// breaks the cauldron and deincrements ingredients because event occurs when cooking
// conditional makes sure ingredients will never be negetive
    void Merchant::breakCauldron(int Cauld)
    {
        if(ingredients_ >= Cauld)
        {
            ingredients_ = ingredients_ - Cauld;
        }
        cauldron_--;

    }
//returns speae
    int Merchant::getSpear()
    {
        return spear_;
    }
//returns axe
    int Merchant::getAxe()
    {
        return axe_;
    }
//returns club
    int Merchant::getClub()
    {
        return club_;
    }
    //returns rapier
    int Merchant::getRapier()
    {
        return rapier_;
    }
    //returns sword
    int Merchant::getSword()
    {
        return sword_;
    }
// increments gold based on input
    void Merchant::addGold(int x)
    {
        gold_ = gold_ + x;
    }
    // adds ingredients based on paramter
    //also serves to deincrement ingredients if parameter is negetive, conditinoal makes sure ingredients will not be negetive
    void Merchant::addIngrediants(int x)
    {
        if(ingredients_ + x < 0)
        {
            ingredients_ = 0;
        }
        else
        {
            ingredients_ = ingredients_ + x;
        }
        
    }
// deincrements gold
    void Merchant::subGold(int x) 
    {
        gold_ = gold_ - x;
    }
// returns gold
    int Merchant::getGold()
    {
        return gold_;
    }
// increments silver
    void Merchant::addSilver()
    {
        silver_++;
    }
    //increments ruby
    void Merchant::addRuby()
    {
        ruby_++;
    }
    //increments emerald
    void Merchant::addEmerald()
    {
        emerald_++;
    }
    //increments diamond
    void Merchant::addDiamond_()
    {
        diamond_++;
    }
    //increments gem
    void Merchant::addGem()
    {
        gem_++;
    }
    //increments gold
    void Merchant::addGold()
    {
        gold_++;
    }
// prints the merchants shopping menu
    void Merchant::InventoryMenu()
    {
        cout << "Choose one of the following:" << endl
        << "1. Cookware: You will need something to cook those ingredients." << endl
        << "2. Ingredients: To make food, you have to cook raw ingredients." << endl
        << "3. Weapons: It's dangerous to go alone, take this!" << endl
        << "4. Armor: If you want to survive monster attacks, you will need some armor." << endl
        << "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl
        << "6. Leave: Make sure you get everything you need. I'm leaving after this sale!" << endl;
       
    }
/*
1. Informs the player that an unfortunate event has happened
2. Two variables are assigned numbers 0-9
3. if the robbed variables is 0, 1, or 2 the they will lose either armor, a pot, a frying pan, or a cauldron
4. if the player is supposed to lose a cauldron for example, but they don't have one to lose they will lose an armor instead
5. the same logic applies to items breaking but it is only if the random integer is one or two
6. unless the player has less than 10 ingredients, they will always lose 10 as well when a misforune occurs
*/
    void Merchant::misfortune()
    {
        cout << "Today isn't going your way..." << endl;
        int Robbed = rand()&10;
        int Breaks = rand()&10;
        if(Robbed < 3)
        {
            if(Robbed == 0)
            {
                if(ceramic_pot_ <= 0)
                {
                    armor_ --;
                    cout << "-1 Armor" << endl;
                }
                else
                {
                    ceramic_pot_ --;
                    cout << "They robbed your ceramic pot!" << endl;
                }

            }
            else if(Robbed == 1)
            {
                if(frying_pan_ <= 0)
                {
                    armor_--;
                }
                else
                {
                    frying_pan_--;
                    cout << "They robbed your frying pan!" << endl;
                }

            }
            else if(Robbed == 2)
            {
                if(cauldron_ <= 0)
                {
                    armor_--;
                }
                else
                {
                    cauldron_--;
                    cout << "They robbed your cauldron!" << endl;
                }
            }
            if(ingredients_ >= 10)
            {
                ingredients_-=10;
            }
            
        }
        
            else if(Breaks == 1)
            {
                if(frying_pan_ <= 0)
                {
                    armor_--;
                }
                else
                {
                    frying_pan_--;
                    cout << "Your frying pan broke!" << endl;
                }

            }
            else if(Breaks == 2)
            {
                if(cauldron_ <= 0)
                {
                    armor_--;
                }
                {
                    cauldron_--;
                    cout << "Your cauldron broke!" << endl;
                }
            }
            if(ingredients_ >= 10)
            {
                cout << "-10 Ingredients" << endl;
                ingredients_-=10;
            }

    }
