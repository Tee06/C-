#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
#include "HandleDeliveryNoteDetail.h"
using namespace std;

const string FILE_DELIVERY_NOTE_DETAIL = "Data/chitietphieugiao.csv";

// Chuyển đổi dữ liệu từ file csv thành vector
vector<DeliveryNoteDetail> HandleDeliveryNoteDetail::convertData(vector<DeliveryNoteDetail> list)
{
    ifstream fileInput(FILE_DELIVERY_NOTE_DETAIL);
    string line;
    while (getline(fileInput, line))
    {
        stringstream lineData(line);
        string item;
        DeliveryNoteDetail dnd;
        while (getline(lineData, item, '|'))
        {
            dnd.setDeliveryNoteId(item);
            getline(lineData, item, '|');
            dnd.setMaterialId(item);
            getline(lineData, item, '|');
            dnd.setQuantity(stoi(item));
            getline(lineData, item, '|');
            dnd.setPrice(stoi(item));
        }
        list.push_back(dnd);
    }

    fileInput.close();
    return list;
}

// Hiển thị menu để thực hiện các thao tác trên bảng chi tiết phiếu giao
void HandleDeliveryNoteDetail::displayMenu()
{
        cout << endl
        << right << setw(40) << "DANH SACH CHI TIET PHIEU GIAO HANG" << endl;
        cout << "1. Hien thi tat ca thong tin cua danh sach chi tiet phieu giao hang.\n";
        cout << "2. Them mot chi tiet phieu giao hang vao danh sach.\n";
        cout << "3. Xoa mot chi tiet phieu giao hang khoi danh sach.\n";
        cout << "4. Chinh sua thong tin chi tiet phieu giao hang trong danh sach.\n";
        cout << "0. Vui long chon 0 tu ban phim neu ban muon ket thuc chuong trinh. \n";
        cout << "Vui long chon chuc nang de thuc thi chuong trinh: ";

}

// Hiển thị danh sách dữ liệu đã qua chuyển hóa
void HandleDeliveryNoteDetail::displayDataList(vector<DeliveryNoteDetail> list)
{
   cout << left << setw(18) << "Ma phieu giao hang"
     << "| "
     << left << setw(13) << "Ma vat tu"
     << "| "
     << left << setw(10) << "So luong"
     << "| "
     << left << "Gia"
     << endl;


    for (auto &item : list)
    {
        cout << left << setw(18) << item.getDeliveryNoteId()
             << "| "
             << left << setw(13) << item.getMaterialId()
             << "| "
             << left << setw(10) << item.getQuantity()
             << "| "
             << left << item.getPrice()
             << endl;
    }
}

// Chèn dữ liệu mới vào file csv
void HandleDeliveryNoteDetail::insertRow()
{
    string deliveryNoteId, materialId, quantity, price;
    cin.ignore();
        cout << "Ma phieu giao hang: ";
        getline(cin, deliveryNoteId);
        cout << "Ma vat tu: ";
        getline(cin, materialId);
        cout << "So luong: ";
        cin >> quantity;
        cout << "Gia: ";
        cin >> price;


    vector<string> newLine;
    newLine.push_back(deliveryNoteId);
    newLine.push_back(materialId);
    newLine.push_back(quantity);
    newLine.push_back(price);

    ofstream fileOutput(FILE_DELIVERY_NOTE_DETAIL, ios::app);
    if (fileOutput.is_open())
    {
        fileOutput << endl;
        for (auto &item : newLine)
        {
            if (item == newLine.at(newLine.size() - 1))
            {
                fileOutput << item;
                break;
            }
            fileOutput << item << "|";
        }
        fileOutput.close();
    }
    else
    {
       cout << "Khong the mo file!";

    }
}

// Xóa dữ liệu khỏi file csv
void HandleDeliveryNoteDetail::deleteRow(string lineToRemove)
{
    vector<string> lines;
    ifstream fileInput(FILE_DELIVERY_NOTE_DETAIL);
    string line;
    while (getline(fileInput, line))
    {
        if (lineToRemove != line)
        {
            lines.push_back(line);
        }
    }
    fileInput.close();
    rewriteFile(lines);
}

// Cập nhật lại dữ liệu cho file csv
void HandleDeliveryNoteDetail::updateRow(string lineToUpdate)
{
    string line, valueUpdate;
    int quantity, price;
    vector<string> lines;
    ifstream fileInput(FILE_DELIVERY_NOTE_DETAIL);

    while (getline(fileInput, line))
    {
        if (lineToUpdate == line)
        {
            stringstream lineData(line);
            string item;
            getline(lineData, item, '|');
            cout << "Ma phieu giao hang: " << item << endl;
            valueUpdate = item + "|";
            getline(lineData, item, '|');
            cout << "Ma vat tu: " << item << endl;
            cout << "So luong: ";
            cin >> quantity;
            cout << "Gia: ";
            cin >> price;


            valueUpdate += item + "|" + to_string(quantity) + "|" + to_string(price);
            line = valueUpdate;
        }
        lines.push_back(line);
    }
    fileInput.close();

    rewriteFile(lines);
}

// Tìm dòng dữ liệu bằng mã phiếu giao hàng và mã vật tư -> thao tác update, delete
string HandleDeliveryNoteDetail::findLineDataById(vector<DeliveryNoteDetail> list, string materialId, string deliveryNoteId)
{
    string result = "";
    for (auto &item : list)
    {
        if (materialId == item.getMaterialId() && deliveryNoteId == item.getDeliveryNoteId())
        {
            result = item.getDeliveryNoteId() + "|" + item.getMaterialId() + "|" + to_string(item.getQuantity()) + "|" + to_string(item.getPrice());
            break;
        }
    }
    return result;
}

// Ghi lại dữ liệu cho file sau khi xóa hoặc cập nhật dữ liệu
void HandleDeliveryNoteDetail::rewriteFile(vector<string> lines)
{
    ofstream fileOutput(FILE_DELIVERY_NOTE_DETAIL, ios::trunc | ios::out);
    for (auto &str : lines)
    {
        if (str == lines.at(lines.size() - 1))
        {
            fileOutput << str;
            break;
        }
        fileOutput << str << endl;
    }
    fileOutput.close();
}

// Sắp xếp mã vật tư có giá giảm dần
vector<string> HandleDeliveryNoteDetail::ascMaterialByPrice(vector<DeliveryNoteDetail> list, int quantity)
{
    for (int i = 0; i < list.size() - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < list.size(); j++)
        {
            if (list.at(min_index).getPrice() < list.at(j).getPrice())
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            DeliveryNoteDetail temp = list.at(min_index);
            list.at(min_index) = list.at(i);
            list.at(i) = temp;
        }
    }

    vector<string> strList;
    for (int i = 0; i < list.size(); ++i)
    {
        if (i == 0 || list.at(i).getMaterialId() != list.at(i - 1).getMaterialId())
        {
            strList.push_back(list.at(i).getMaterialId());
        }
    }

    if (quantity > list.size())
    {
        quantity = list.size();
    }
    return vector<string>(strList.begin(), strList.begin() + quantity);
}

// Tính tổng tiền của 1 phiếu giao có trong chi tiết phiếu giao
int HandleDeliveryNoteDetail::totalOfDeliveryNote(vector<DeliveryNoteDetail> list, string deliveryNoteId)
{
    int result = 0;
    for (auto &item : list)
    {
        if (item.getDeliveryNoteId() == deliveryNoteId)
        {
            result += item.getTotalPrice();
        }
    }
    return result;
}

// Lấy ra số lượng đã bán của một vật tư nào đó
int HandleDeliveryNoteDetail::getSoldByMaterialId(vector<DeliveryNoteDetail> list, string material)
{
    int result = 0;
    map<string, int> frequencyMap;
    for (auto &item : list)
    {
        frequencyMap[item.getMaterialId()] += item.getQuantity();
    }

    vector<pair<string, int>> sortedByValue(frequencyMap.begin(), frequencyMap.end());

    for (auto &item : sortedByValue)
    {
        if (material == item.first)
        {
            result = item.second;
            return result;
        }
        
    }
    return result;
}