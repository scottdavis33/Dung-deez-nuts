// CSCI 1300 Fall 2022
// Author: Jared Preyer && Scott Davis 
// Recitation: 105 - Reagan Rychecky && 308 - Baljot Kaur
// Project 3 - Class Monster
#include <iostream>
#include <fstream>
#include "Monster.h"
#include "Group.h"
#include <string>

using namespace std;


Monster::Monster()
{
    name_ = "";
    level_ = 0;
}

Monster::Monster(string name, int level)
{
    name_ = name;
    level_ = level;
}

void Monster::setLevel(int level)
{
    level_ = level;
}

int Monster::getLevel()
{
    return level_;
}

void Monster::setName(string name)
{
    name_ = name;
}

string Monster::getName()
{
    return name_;
}

