#include <iostream>
#include "Material.h"

Material::Material()
{
    this->id = "";
    this->name = "";
    this->unit = "";
}
Material::Material(string _id, string _name, string _unit)
{
    this->id = _id;
    this->name = _name;
    this->unit = _unit;
}
string Material::getId()
{
    return this->id;
}
string Material::getName()
{
    return this->name;
}
string Material::getUnit()
{
    return this->unit;
}
void Material::setId(string _id)
{
    this->id = _id;
}
void Material::setName(string _name)
{
    this->name = _name;
}
void Material::setUnit(string _unit)
{
    this->unit = _unit;
}
