#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "HandleMaterial.h"
using namespace std;

const string FILE_MATERIAL = "Data/vattu.csv";

// Chuyển đổi dữ liệu từ file csv thành vector
vector<Material> HandleMaterial::convertData(vector<Material> materials)
{
    ifstream fileInput(FILE_MATERIAL);
    string line;
    while (getline(fileInput, line))
    {
        stringstream lineData(line);
        string item;
        Material material;
        while (getline(lineData, item, '|'))
        {
            material.setId(item);
            getline(lineData, item, '|');
            material.setName(item);
            getline(lineData, item, '|');
            material.setUnit(item);
        }
        materials.push_back(material);
    }

    fileInput.close();
    return materials;
}

// Giển thị menu để thực hiện các thao tác trên bảng vật tư
void HandleMaterial::displayMenu()
{
   cout << endl
     << right << setw(30) << "DANH SACH VAT TU" << endl;
    cout << "1. Hien thi tat ca thong tin cua danh sach vat tu.\n";
    cout << "2. Them mot vat tu vao danh sach.\n";
    cout << "3. Xoa mot vat tu khoi danh sach.\n";
    cout << "4. Chinh sua thong tin vat tu trong danh sach.\n";
    cout << "0. Vui long chon 0 tu ban phim neu ban muon ket thuc chuong trinh. \n";
    cout << "Vui long chon chuc nang de thuc thi chuong trinh: ";

}

// Hiển thị danh sách dữ liệu đã qua chuyển hóa
void HandleMaterial::displayDataList(vector<Material> materials)
{
    cout << left << setw(8) << "ID"
         << "| "
         << left << setw(30) << "Ten"
         << "| "
        << left << "Don vi" << endl;


    for (auto &material : materials)
    {
        cout << left << setw(8) << material.getId()
             << "| "
             << left << setw(30) << material.getName()
             << "| "
             << left << material.getUnit() << endl;
    }
}

// Chèn dữ liệu mới vào file csv
void HandleMaterial::insertRow()
{
    string id, name, unit;
    cin.ignore();
    cout << "Ma vat tu: ";
    getline(cin, id);
    cout << "Ten vat tu: ";
    getline(cin, name);
    cout << "Don vi vat tu: ";
    getline(cin, unit);


    vector<string> newLine;
    newLine.push_back(id);
    newLine.push_back(name);
    newLine.push_back(unit);

    ofstream fileOutput(FILE_MATERIAL, ios::app);
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
void HandleMaterial::deleteRow(string lineToRemove)
{
    vector<string> lines;
    ifstream fileInput(FILE_MATERIAL);
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
void HandleMaterial::updateRow(string lineToUpdate)
{
    string name, unit, line, valueUpdate;
    vector<string> lines;
    ifstream fileInput(FILE_MATERIAL);

    while (getline(fileInput, line))
    {
        if (lineToUpdate == line)
        {
            stringstream lineData(line);
            string item;
            getline(lineData, item, '|');
            cout << "Ma vat lieu: " << item << endl;
            cout << "Ten vat lieu: ";
            cin.ignore();
            getline(cin, name);
            cout << "Don vi vat lieu: ";

            getline(cin, unit);

            valueUpdate = item + "|" + name + "|" + unit;
            line = valueUpdate;
        }
        lines.push_back(line);
    }
    fileInput.close();

    rewriteFile(lines);
}

// Tìm dòng dữ liệu bằng mã vật tư -> thao tác update, delete
string HandleMaterial::findLineDataById(vector<Material> materials, string materialId)
{
    string result = "";
    for (auto &material : materials)
    {
        if (materialId == material.getId())
        {
            result = material.getId() + "|" + material.getName() + "|" + material.getUnit();
            break;
        }
    }
    return result;
}

// Ghi lại dữ liệu cho file sau khi xóa hoặc cập nhật dữ liệu
void HandleMaterial::rewriteFile(vector<string> lines)
{
    ofstream fileOutput(FILE_MATERIAL, ios::trunc | ios::out);
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

// Tìm vật tư bằng mã vật tư
Material HandleMaterial::findMaterialById(vector<Material> materials, string materialId)
{
    Material material;
    for (auto &item : materials)
    {
        if (materialId == item.getId())
        {
            material = item;
        }
    }
    return material;
}

// Hiển thị thông tin của vật tư và số lượng bán ra của sản phẩm đó
void HandleMaterial::displayInfoMaterialAndSold(string materialId, int sold)
{
    vector<Material> materials;
    materials = convertData(materials);
    for (auto &material : materials)
    {
        if (materialId == material.getId())
        {
            cout << left << setw(8) << material.getId()
                 << "| "
                 << left << setw(30) << material.getName()
                 << "| "
                 << left << setw(10) << material.getUnit()
                 << "| "
                 << left << sold << endl;
        }
    }
}
