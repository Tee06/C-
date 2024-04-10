#include <iostream>
#include <sstream>
#include "DeliveryNote.h"

DeliveryNote::DeliveryNote()
{
    this->id = "";
    this->deliveryDate = "";
    this->deliveryPlace = "";
    this->customerId = "";
}
DeliveryNote::DeliveryNote(string _id, string _deliveryDate, string _deliveryPlace, string _customerId)
{
    this->id = _id;
    this->deliveryDate = _deliveryDate;
    this->deliveryPlace = _deliveryPlace;
    this->customerId = _customerId;
}
string DeliveryNote::getId()
{
    return this->id;
}
string DeliveryNote::getDeliveryDate()
{
    return this->deliveryDate;
}
string DeliveryNote::getDeliveryPlace()
{
    return this->deliveryPlace;
}
string DeliveryNote::getCustomerId()
{
    return this->customerId;
}
void DeliveryNote::setId(string _id)
{
    this->id = _id;
}
void DeliveryNote::setDeliveryDate(string _deliveryDate)
{
    this->deliveryDate = _deliveryDate;
}
void DeliveryNote::setDeliveryPlace(string _deliveryPlace)
{
    this->deliveryPlace = _deliveryPlace;
}
void DeliveryNote::setCustomerId(string _customerId)
{
    this->customerId = _customerId;
}
