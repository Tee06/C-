#include <iostream>
#include "DeliveryNoteDetail.h"

DeliveryNoteDetail::DeliveryNoteDetail()
{
    this->deliveryNoteId = "";
    this->materialId = "";
    this->quantity = 0;
    this->price = 0;
}
DeliveryNoteDetail::DeliveryNoteDetail(string _deliveryNoteId, string _materialId, int _quantity, int _price)
{
    this->deliveryNoteId = _deliveryNoteId;
    this->materialId = _materialId;
    this->quantity = _quantity;
    this->price = _price;
}
string DeliveryNoteDetail::getDeliveryNoteId()
{
    return this->deliveryNoteId;
}
string DeliveryNoteDetail::getMaterialId()
{
    return this->materialId;
}
int DeliveryNoteDetail::getQuantity()
{
    return this->quantity;
}
int DeliveryNoteDetail::getPrice()
{
    return this->price;
}
void DeliveryNoteDetail::setDeliveryNoteId(string _deliveryNoteId)
{
    this->deliveryNoteId = _deliveryNoteId;
}
void DeliveryNoteDetail::setMaterialId(string _materialId)
{
    this->materialId = _materialId;
}
void DeliveryNoteDetail::setQuantity(int _quantity)
{
    this->quantity = _quantity;
}
void DeliveryNoteDetail::setPrice(int _price)
{
    this->price = _price;
}
int DeliveryNoteDetail::getTotalPrice() {
    return price * quantity;
}