#ifndef PHIEUGIAO_H
#define PHIEUGIAO_H

#include <iostream>
using namespace std;

class DeliveryNote
{
private:
    string id, deliveryDate, deliveryPlace, customerId;

public:
    DeliveryNote();
    DeliveryNote(string _id, string _deliveryDate, string _deliveryPlace, string _customerId);
    string getId();
    string getDeliveryDate();
    string getDeliveryPlace();
    string getCustomerId();
    void setId(string _id);
    void setDeliveryDate(string _deliveryDate);
    void setDeliveryPlace(string _deliveryPlace);
    void setCustomerId(string _customerId);
    // int getYear();
    // int getMonth();
    // int getDay();
};

#endif