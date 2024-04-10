#ifndef HANDLE_DELIVERY_NOTE_DETAIL_H
#define HANDLE_DELIVERY_NOTE_DETAIL_H

#include "../Entity/DeliveryNoteDetail.h"
#include <vector>

class HandleDeliveryNoteDetail
{
public:
    vector<DeliveryNoteDetail> convertData(vector<DeliveryNoteDetail> list);
    void displayMenu();
    void displayDataList(vector<DeliveryNoteDetail> list);
    void insertRow();
    void deleteRow(string lineToRemove);
    void updateRow(string lineToUpdate);
    string findLineDataById(vector<DeliveryNoteDetail> list, string materialId, string deliveryNoteId);
    void rewriteFile(vector<string> lines);
    vector<string> ascMaterialByPrice(vector<DeliveryNoteDetail> list, int quantity);
    int totalOfDeliveryNote(vector<DeliveryNoteDetail> list, string deliveryNoteId);
    int getSoldByMaterialId(vector<DeliveryNoteDetail> list, string material);
};

#endif