#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <ctime>
#include "HandleDeliveryNote.h"
using namespace std;

const string FILE_DELIVERY_NOTE = "Data/phieugiao.csv";
const string FILE_DELIVERY_NOTE_BACKUP = "Data/phieugiao";

// Chuyển đổi dữ liệu từ file csv thành vector
vector<DeliveryNote> HandleDeliveryNote::convertData(vector<DeliveryNote> deliveryNotes)
{
    ifstream fileInput(FILE_DELIVERY_NOTE);
    string line;
    while (getline(fileInput, line))
    {
        stringstream lineData(line);
        string item;
        DeliveryNote deliveryNote;
        while (getline(lineData, item, '|'))
        {
            deliveryNote.setId(item);
            getline(lineData, item, '|');
            deliveryNote.setDeliveryDate(item);
            getline(lineData, item, '|');
            deliveryNote.setDeliveryPlace(item);
            getline(lineData, item, '|');
            deliveryNote.setCustomerId(item);
        }
        deliveryNotes.push_back(deliveryNote);
    }

    fileInput.close();
    return deliveryNotes;
}

// Hiển thị menu để thực hiện các thao tác trên bảng phiếu giao
void HandleDeliveryNote::displayMenu()
{
    cout << endl
    << right << setw(30) << "MENU CUA PHIEU GIAO HANG" << endl;
    cout << "1. Hien thi tat ca thong tin cua danh sach phieu giao hang.\n";
    cout << "2. Them mot phieu giao hang vao danh sach.\n";
    cout << "3. Xoa mot phieu giao hang khoi danh sach.\n";
    cout << "4. Chinh sua thong tin phieu giao hang trong danh sach.\n";
    cout << "0. Vui long chon 0 tu ban phim neu ban muon ket thuc chuong trinh. \n";
    cout << "Vui long chon chuc nang de thuc thi chuong trinh: ";


}

// Hiển thị danh sách dữ liệu đã qua chuyển hóa
void HandleDeliveryNote::displayDataList(vector<DeliveryNote> deliveryNotes)
{
        cout << left << setw(8) << "ID"
            << "| "
            << left << setw(20) << "Ngay giao hang"
            << "| "
            << left << setw(40) << "Noi giao hang"
            << "| "
            << left << "Ma khach hang"
            << endl;


    for (auto &deliveryNote : deliveryNotes)
    {
        cout << left << setw(8) << deliveryNote.getId()
             << "| "
             << left << setw(20) << deliveryNote.getDeliveryDate()
             << "| "
             << left << setw(40) << deliveryNote.getDeliveryPlace()
             << "| "
             << left << deliveryNote.getCustomerId()
             << endl;
    }
}

// Chèn dữ liệu mới vào file csv
void HandleDeliveryNote::insertRow()
{
    string id, date, address, customerId;
    cin.ignore();
    cout << "Ma phieu giao hang: ";
    getline(cin, id);
    cout << "Ngay giao hang: ";
    getline(cin, date);
    cout << "Dia chi giao hang: ";
    getline(cin, address);
    cout << "Ma khach hang: ";
    getline(cin, customerId);


    vector<string> newLine;
    newLine.push_back(id);
    newLine.push_back(date);
    newLine.push_back(address);
    newLine.push_back(customerId);

    ofstream fileOutput(FILE_DELIVERY_NOTE, ios::app);
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
         cout << "Khong the mo tep!";

    }
}

// Xóa dữ liệu khỏi file csv
void HandleDeliveryNote::deleteRow(string lineToRemove)
{
    vector<string> lines;
    ifstream fileInput(FILE_DELIVERY_NOTE);
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
void HandleDeliveryNote::updateRow(string lineToUpdate)
{
    string date, address, customerId, line, valueUpdate;
    vector<string> lines;
    ifstream fileInput(FILE_DELIVERY_NOTE);

    while (getline(fileInput, line))
    {
        if (lineToUpdate == line)
        {
            stringstream lineData(line);
            string item;
            getline(lineData, item, '|');
            cout << "Ma phieu giao hang: " << item << endl;
            cin.ignore();
            cout << "Ngay giao hang: ";
            getline(cin, date);
            cout << "Noi giao hang: ";
            getline(cin, address);
            cout << "Ma khach hang: ";
            getline(cin, customerId);


            valueUpdate = item + "|" + date + "|" + address + "|" + customerId;
            line = valueUpdate;
        }
        lines.push_back(line);
    }
    fileInput.close();

    rewriteFile(lines);
}

// Tìm dòng dữ liệu bằng mã phiếu giao hang -> thao tác update, delete
string HandleDeliveryNote::findLineDataById(vector<DeliveryNote> deliveryNotes, string deliveryNoteId)
{
    string result = "";
    for (auto &deliveryNote : deliveryNotes)
    {
        if (deliveryNoteId == deliveryNote.getId())
        {
            result = deliveryNote.getId() + "|" + deliveryNote.getDeliveryDate() + "|" + deliveryNote.getDeliveryPlace() + "|" + deliveryNote.getCustomerId();
            break;
        }
    }
    return result;
}

// Ghi lại dữ liệu cho file sau khi xóa hoặc cập nhật dữ liệu
void HandleDeliveryNote::rewriteFile(vector<string> lines)
{
    ofstream fileOutput(FILE_DELIVERY_NOTE, ios::trunc | ios::out);
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

// Convert và lấy năm
int HandleDeliveryNote::getYear(string time)
{
    stringstream ss(time);
    string item;
    getline(ss, item, '-');
    return stoi(item);
}

// Convert và lấy tháng
int HandleDeliveryNote::getMonth(string time)
{
    stringstream ss(time);
    string item;
    getline(ss, item, '-');
    getline(ss, item, '-');
    return stoi(item);
}

// Convert và lấy ngày
int HandleDeliveryNote::getDay(string time)
{
    stringstream ss(time);
    string item;
    getline(ss, item, '-');
    getline(ss, item, '-');
    getline(ss, item, '-');
    return stoi(item);
}

// Lấy ra danh phiếu giao hàng trong khoảng thời gian bắt đầu đến khoảng thời gian kết thúc
vector<DeliveryNote> HandleDeliveryNote::getListByPeriod(vector<DeliveryNote> deliveryNotes, string beginTime, string endTime)
{
    vector<DeliveryNote> resultList;
    int beginYear = getYear(beginTime);
    int beginMonth = getMonth(beginTime);
    int beginDay = getDay(beginTime);
    int endYear = getYear(endTime);
    int endMonth = getMonth(endTime);
    int endDay = getDay(endTime);
    for (auto &item : deliveryNotes)
    {
        string date = item.getDeliveryDate();
        int dateYear = getYear(date);
        int dateMonth = getMonth(date);
        int dateDay = getDay(date);
        if ((dateYear > beginYear || (dateYear == beginYear && dateMonth > beginMonth) ||
             (dateYear == beginYear && dateMonth == beginMonth && dateDay >= beginDay)) &&
            (dateYear < endYear || (dateYear == endYear && dateMonth < endMonth) ||
             (dateYear == endYear && dateMonth == endMonth && dateDay <= endDay)))
        {
            resultList.push_back(item);
        }
    }
    return resultList;
}
