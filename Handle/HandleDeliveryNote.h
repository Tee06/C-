#ifndef HANDLE_DELIVERY_NOTE_H
#define HANDLE_DELIVERY_NOTE_H

#include "../Entity/DeliveryNote.h"
#include <vector>

class HandleDeliveryNote
{
public:
    vector<DeliveryNote> convertData(vector<DeliveryNote> deliveryNotes);
    void displayMenu();
    void displayDataList(vector<DeliveryNote> deliveryNotes);
    void insertRow();
    void deleteRow(string lineToRemove);
    void updateRow(string lineToUpdate);
    string findLineDataById(vector<DeliveryNote> deliveryNotes, string deliveryNoteId);
    void rewriteFile(vector<string> lines);
    int getYear(string time);
    int getMonth(string time);
    int getDay(string time);
    vector<DeliveryNote> getListByPeriod(vector<DeliveryNote> deliveryNotes, string beginTime, string endTime);
};

#endif