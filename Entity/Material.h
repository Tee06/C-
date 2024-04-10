#ifndef VATTU_H
#define VATTU_H

#include <iostream>
using namespace std;

class Material
{
private:
    string id, name, unit;
public:
    Material();
    Material(string _id, string _name, string _unit);
    string getId();
    string getName();
    string getUnit();
    void setId(string _id);
    void setName(string _name);
    void setUnit(string _unit);
};

#endif