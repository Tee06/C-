#ifndef CHITIETPHIEUGIAO_H
#define CHITIETPHIEUGIAO_H

#include<iostream>
using namespace std;

class DeliveryNoteDetail
{
private:
    string deliveryNoteId, materialId;
    int quantity, price;
public:
    DeliveryNoteDetail();
    DeliveryNoteDetail(string _deliveryNoteId, string _materialId, int _quantity, int _price);
    string getDeliveryNoteId();
    string getMaterialId();
    int getQuantity();
    int getPrice();
    void setDeliveryNoteId(string _deliveryNoteId);
    void setMaterialId(string _materialId);
    void setQuantity(int _quantity);
    void setPrice(int _price);
    int getTotalPrice();
};

#endif