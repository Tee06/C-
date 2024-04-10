#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include "Entity/Material.cpp"
#include "Handle/HandleMaterial.cpp"
#include "Entity/DeliveryNote.cpp"
#include "Handle/HandleDeliveryNote.cpp"
#include "Entity/DeliveryNoteDetail.cpp"
#include "Handle/HandleDeliveryNoteDetail.cpp"

using namespace std;

// Khai báo các đối tượng xử lý và danh sách dữ liệu
HandleMaterial handleMaterial;
vector<Material> materialList;
HandleDeliveryNote handleDeliveryNote;
vector<DeliveryNote> deliveryNoteList;
HandleDeliveryNoteDetail handleDeliveryNoteDetail;
vector<DeliveryNoteDetail> deliveryNoteDetailList;
int chooseEvent, chooseTable, quantity;
string materialId, deliveryNoteId, lineData, fileWantToRestore;

// Hàm sao lưu dữ liệu
void backupData(string fileNameRoot)
{
    // Mở tệp nguồn để sao lưu
    ifstream fileInput(fileNameRoot + ".csv");
    if (!fileInput.is_open())
    {
        cerr << "Khong the mo tep doc.\n";
        return;
    }

    // Lấy thời gian hiện tại
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    struct tm *timeinfo;
    char buffer[80];
    timeinfo = localtime(&now_c);
    strftime(buffer, sizeof(buffer), "%H-%M-%S_%d-%m-%Y", timeinfo);

    // Tạo tên tệp sao lưu mới
    string backupFileName = fileNameRoot + "_" + string(buffer) + ".csv";

    // Mở tệp sao lưu để ghi
    ofstream fileBackup(backupFileName);
    if (!fileBackup.is_open())
    {
        cerr << "Không thể mở tệp để sao lưu.\n";
        return;
    }

    string line, prevLine;
    // Sao chép dữ liệu từ tệp nguồn sang tệp sao lưu
    while (getline(fileInput, line))
    {
        if (!prevLine.empty())
        {
            fileBackup << prevLine << endl;
        }
        prevLine = line;
    }

    if (!prevLine.empty() && !line.empty())
    {
        fileBackup << prevLine;
    }

    cout << "Du lieu da duoc sao luu thanh cong vao " << backupFileName << ".\n";
    fileInput.close();
    fileBackup.close();
}

// Hàm khôi phục dữ liệu
void restoreData(string fileNameRoot, string fileNameBackup)
{
    ifstream fileInput(fileNameBackup + ".csv");
    if (!fileInput.is_open())
    {
        cerr << "Khong the mo tep khoi phuc.\n";
        return;
    }

    ofstream fileRoot(fileNameRoot);
    if (!fileRoot.is_open())
    {
        cerr << "Khong the mo tep ghi.\n";
        return;
    }

    string line, prevLine;
    // Sao chép dữ liệu từ tệp sao lưu sang tệp gốc
    while (getline(fileInput, line))
    {
        if (!prevLine.empty())
        {
            fileRoot << prevLine << endl;
        }
        prevLine = line;
    }

    if (!prevLine.empty() && !line.empty())
    {
        fileRoot << prevLine;
    }

    fileInput.close();
    fileRoot.close();
    cout << "Du lieu da dươc khoi phuc thành cong.\n";
}

// Câu 1: Thao tác CRUD trên các bảng
void case1()
{
    do
    {
        // Hiển thị menu lựa chọn bảng
        cout << endl << right << setw(10) << "BANG";
        cout << "\n1. Vat tu.";
        cout << "\n2. Phieu giao hang.";
        cout << "\n3. Chi tiet phieu giao hang.";
        cout << "\n0. Thoat.";
        cout << "\nVui long chon so de thuc thi chuong trinh: ";

        cin >> chooseTable;
        switch (chooseTable)
        {
        case 1:
        {
            do
            {
                // Chuyển đổi và hiển thị dữ liệu vật tư
                materialList = handleMaterial.convertData(materialList);
                handleMaterial.displayMenu();
                cin >> chooseEvent;
                switch (chooseEvent)
                {
                case 1:
                    handleMaterial.displayDataList(materialList);
                    break;
                case 2:
                    handleMaterial.insertRow();
                    break;
                case 3:
                   cout << "Nhap ma vat tu ban muon xoa: ";
                    cin >> materialId;
                    lineData = handleMaterial.findLineDataById(materialList, materialId);
                    if (lineData != "")
                    {
                        handleMaterial.deleteRow(lineData);
                        cout << "Xoa thanh cong!\n";
                    }
                    else
                    {
                        cout << "Ma vat tu khong ton tai trong co so du lieu!\n";
                    }
                    break;
                    case 4:
                        cout << "Nhap ma vat tu ban muon chinh sua: ";
                        cin >> materialId;
                        lineData = handleMaterial.findLineDataById(materialList, materialId);
                        if (lineData != "")
                        {
                            handleMaterial.updateRow(lineData);
                            cout << "Chinh sua thanh cong!\n";
                        }
                        else
                        {
                            cout << "Ma vat tu khong ton tai trong co so du lieu!\n";
                        }
                        break;

                }
                materialList.clear();
            } while (chooseEvent != 0);
        }
        break;
        case 2:
        {
            do
            {
                // Chuyển đổi và hiển thị dữ liệu phiếu giao hàng
                deliveryNoteList = handleDeliveryNote.convertData(deliveryNoteList);
                handleDeliveryNote.displayMenu();
                cin >> chooseEvent;
                switch (chooseEvent)
                {
                case 1:
                    handleDeliveryNote.displayDataList(deliveryNoteList);
                    break;
                case 2:
                    handleDeliveryNote.insertRow();
                    break;
                case 3:
                   cout << "Nhap ma phieu giao hang ban muon xoa: ";
                    cin >> deliveryNoteId;
                    lineData = handleDeliveryNote.findLineDataById(deliveryNoteList, deliveryNoteId);
                    if (lineData != "")
                    {
                        handleDeliveryNote.deleteRow(lineData);
                        cout << "Xoa thanh cong!\n";
                    }
                    else
                    {
                        cout << "Ma phieu giao hang khong ton tai trong co so du lieu!\n";
                    }
                    break;
                    case 4:
                        cout << "Nhap ma phieu giao hang ban muon chinh sua: ";
                        cin >> deliveryNoteId;
                        lineData = handleDeliveryNote.findLineDataById(deliveryNoteList, deliveryNoteId);
                        if (lineData != "")
                        {
                            handleDeliveryNote.updateRow(lineData);
                            cout << "Chinh sua thanh cong!\n";
                        }
                        else
                        {
                            cout << "Ma phieu giao hang khong ton tai trong co so du lieu!\n";
                        }
                        break;

                }
                deliveryNoteList.clear();
            } while (chooseEvent != 0);
        }
        break;
        case 3:
        {
            do
            {
                // Chuyển đổi và hiển thị dữ liệu chi tiết phiếu giao hàng
                deliveryNoteDetailList = handleDeliveryNoteDetail.convertData(deliveryNoteDetailList);
                handleDeliveryNoteDetail.displayMenu();
                cin >> chooseEvent;
                switch (chooseEvent)
                {
                case 1:
                    handleDeliveryNoteDetail.displayDataList(deliveryNoteDetailList);
                    break;
                case 2:
                    handleDeliveryNoteDetail.insertRow();
                    break;
                case 3:
                    cout << "Nhap ma phieu giao hang va ma vat tu ban muon xoa.";
                    cin.ignore();
                    cout << "\nMa phieu giao hang: ";
                    getline(cin, deliveryNoteId);
                    cout << "Ma vat tu: ";
                    getline(cin, materialId);
                    lineData = handleDeliveryNoteDetail.findLineDataById(deliveryNoteDetailList, materialId, deliveryNoteId);
                    if (lineData != "")
                    {
                        handleDeliveryNoteDetail.deleteRow(lineData);
                        cout << "Xoa thanh cong!\n";
                    }
                    else
                    {
                        cout << "Ma phieu giao hang hoac ma vat tu khong ton tai trong co so du lieu!\n";
                    }
                    break;
                    case 4:
                        cout << "Nhap ma phieu giao hang va ma vat tu ban muon chinh sua.";
                        cin.ignore();
                        cout << "\nMa phieu giao hang: ";
                        getline(cin, deliveryNoteId);
                        cout << "Ma vat tu: ";
                        getline(cin, materialId);
                        lineData = handleDeliveryNoteDetail.findLineDataById(deliveryNoteDetailList, materialId, deliveryNoteId);
                        if (lineData != "")
                        {
                            handleDeliveryNoteDetail.updateRow(lineData);
                            cout << "Chinh sua thanh cong!\n";
                        }
                        else
                        {
                            cout << "Ma phieu giao hang hoac ma vat tu khong ton tai trong co so du lieu!\n";
                        }
                        break;

                }
                deliveryNoteDetailList.clear();
            } while (chooseEvent != 0);
        }
        break;
        }
    } while (chooseTable != 0);
}

// Câu 2: Thống kê N vật liệu có giá cao nhất
void case2()
{
    materialList = handleMaterial.convertData(materialList);
    deliveryNoteDetailList = handleDeliveryNoteDetail.convertData(deliveryNoteDetailList);
    cout << "\nNhap so luong vat lieu ban muon thong ke co gia cao nhat ";
    cin >> quantity;
    vector<string> materialIdList = handleDeliveryNoteDetail.ascMaterialByPrice(deliveryNoteDetailList, quantity);
    vector<Material> resultList;
    for (auto &item : materialIdList)
    {
        resultList.push_back(handleMaterial.findMaterialById(materialList, item));
    }
    handleMaterial.displayDataList(resultList);
    materialList.clear();
    deliveryNoteDetailList.clear();
}

// Câu 3: Hiển thị tổng số tiền của một phiếu giao hàng
void case3()
{
    deliveryNoteDetailList = handleDeliveryNoteDetail.convertData(deliveryNoteDetailList);
cout << "\nNhap ma phieu giao hang de hien thi tong so tien cua phieu do: ";
cin >> deliveryNoteId;
cout << "Tong so tien cua phieu giao hang " << deliveryNoteId << " la: " << handleDeliveryNoteDetail.totalOfDeliveryNote(deliveryNoteDetailList, deliveryNoteId) << endl;
deliveryNoteDetailList.clear();

}

// Câu 4: Thống kê phiếu giao hàng theo thời gian
void case4()
{
    deliveryNoteList = handleDeliveryNote.convertData(deliveryNoteList);
    deliveryNoteDetailList = handleDeliveryNoteDetail.convertData(deliveryNoteDetailList);
    string beginTime, endTime;
    cin.ignore();
    cout << "Nhap thoi gian bat dau: (yyyy-mm-dd)";
    getline(cin, beginTime);
    cout << "Nhap thoi gian ket thuc: (yyyy-mm-dd)";
    getline(cin, endTime);
    vector<DeliveryNote> list = handleDeliveryNote.getListByPeriod(deliveryNoteList, beginTime, endTime);
    cout << left << setw(8) << "ID"
         << "| "
         << left << setw(20) << "Ngay giao hang"
         << "| "
         << left << setw(40) << "Dia diem giao hang"
         << "| "
         << left
             << "Tong gia"
         << endl;
    for (auto &item : list)
    {
        cout << left << setw(8) << item.getId()
             << "| "
             << left << setw(20) << item.getDeliveryDate()
             << "| "
             << left << setw(40) << item.getDeliveryPlace()
             << "| "
             << left << handleDeliveryNoteDetail.totalOfDeliveryNote(deliveryNoteDetailList, item.getId())
             << endl;
    }
    deliveryNoteList.clear();
    deliveryNoteDetailList.clear();
    list.clear();
}

// Câu 5: Thống kê N vật liệu bán chạy nhất
void case5()
{
    materialList = handleMaterial.convertData(materialList);
    deliveryNoteDetailList = handleDeliveryNoteDetail.convertData(deliveryNoteDetailList);
    cout << left << setw(8) << "ID"
         << "| "
         << left << setw(30) << "Ten vat lieu"
         << "| "
         << left << setw(10) << "Don vi"
         << "| "
         << left << "So luong da ban" << endl;

    for (auto &material : materialList)
    {
        cout << left << setw(8) << material.getId()
             << "| "
             << left << setw(30) << material.getName()
             << "| "
             << left << setw(10) << material.getUnit()
             << "| "
             << left << handleDeliveryNoteDetail.getSoldByMaterialId(deliveryNoteDetailList, material.getId()) << endl;
    }
  cout << "\nNhap so luong vat lieu ban muon hien thi la cac vat lieu ban chay nhat: ";
cin >> quantity;

    for (int i = 0; i < materialList.size() - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < materialList.size(); j++)
        {
            int min_valueSold = handleDeliveryNoteDetail.getSoldByMaterialId(deliveryNoteDetailList, materialList.at(min_index).getId());
            int valueSold = handleDeliveryNoteDetail.getSoldByMaterialId(deliveryNoteDetailList, materialList.at(j).getId());
            if (min_valueSold < valueSold)
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            Material temp = materialList.at(min_index);
            materialList.at(min_index) = materialList.at(i);
            materialList.at(i) = temp;
        }
    }

    if (quantity > materialList.size())
    {
        quantity = materialList.size();
    }
    materialList = vector<Material>(materialList.begin(), materialList.begin() + quantity);
    
    cout << left << setw(8) << "ID"
     << "| "
     << left << setw(30) << "Ten"
     << "| "
     << left << setw(10) << "Don vi"
     << "| "
     << left << "So luong da ban" << endl;


    for (auto &material : materialList)
    {
        handleMaterial.displayInfoMaterialAndSold(material.getId(), handleDeliveryNoteDetail.getSoldByMaterialId(deliveryNoteDetailList, material.getId()));
    }

    materialList.clear();
    deliveryNoteDetailList.clear();
}

// Câu 6: Thống kê doanh thu tổng cộng trong một khoảng thời gian
void case6()
{
    deliveryNoteList = handleDeliveryNote.convertData(deliveryNoteList);
    deliveryNoteDetailList = handleDeliveryNoteDetail.convertData(deliveryNoteDetailList);
    string beginTime, endTime;
    int totalRevenue = 0;
    cin.ignore();
    cout << "Nhap thoi gian bat dau: (yyyy-mm-dd)";
    getline(cin, beginTime);
    cout << "Nhap thoi gian ket thuc: (yyyy-mm-dd)";
    getline(cin, endTime);
    int beginYear = handleDeliveryNote.getYear(beginTime);
    int beginMonth = handleDeliveryNote.getMonth(beginTime);
    int beginDay = handleDeliveryNote.getDay(beginTime);
    int endYear = handleDeliveryNote.getYear(endTime);
    int endMonth = handleDeliveryNote.getMonth(endTime);
    int endDay = handleDeliveryNote.getDay(endTime);
    for (auto &item : deliveryNoteList)
    {
        string date = item.getDeliveryDate();
        int dateYear = handleDeliveryNote.getYear(date);
        int dateMonth = handleDeliveryNote.getMonth(date);
        int dateDay = handleDeliveryNote.getDay(date);
        if ((dateYear > beginYear || (dateYear == beginYear && dateMonth > beginMonth) ||
             (dateYear == beginYear && dateMonth == beginMonth && dateDay >= beginDay)) &&
            (dateYear < endYear || (dateYear == endYear && dateMonth < endMonth) ||
             (dateYear == endYear && dateMonth == endMonth && dateDay <= endDay)))
        {
            totalRevenue += handleDeliveryNoteDetail.totalOfDeliveryNote(deliveryNoteDetailList, item.getId());
        }
    }
    cout << "Tong doanh thu cho khoan thoi gian do la: " << totalRevenue;
    deliveryNoteList.clear();
    deliveryNoteDetailList.clear();
}

// Câu 7: Sao lưu và khôi phục dữ liệu
void case7()
{
    do
    {
        cout << endl << "THAO TAC SAO LUU VA KHOI PHUC DU LIEU TREN BANG";
        cout << "\n1. Sao luu du lieu bang vat tu";
        cout << "\n2. Sao luu du lieu bang phieu giao hang";
        cout << "\n3. Sao luu du lieu bang chi tiet phieu giao hang.";
        cout << "\n4. Khoi phuc du lieu bang vat tu";
        cout << "\n5. Khoi phuc du lieu bang phieu giao hang";
        cout << "\n6. Khoi phuc du lieu bang chi tiet phieu giao hang.";
        cout << "\nVui long chon so de thuc hien chuong trinh: ";
        cin >> chooseEvent;
        switch (chooseEvent)
        {
        case 1:
            backupData("Data/vattu");
            break;
        case 2:
            backupData("Data/phieugiao");
            break;
        case 3:
            backupData("Data/chitietphieugiao");
            break;
        case 4:
            cout << "Nhap ten tep du lieu ban muon khoi phuc: ";
            getline(cin, fileWantToRestore);
            restoreData("Data/vattu", fileWantToRestore);
            break;
        case 5:
            cout << "Nhap ten tep du lieu ban muon khoi phuc: ";
            getline(cin, fileWantToRestore);
            restoreData("Data/phieugiao", fileWantToRestore);
            break;
        case 6:
            cout << "Nhap ten tep du lieu ban muon khoi phuc: ";
            getline(cin, fileWantToRestore);
            restoreData("Data/chitietphieugiao", fileWantToRestore);
            break;
        }

    } while (chooseEvent);
}