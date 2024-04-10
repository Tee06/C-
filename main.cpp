    // Bao gồm các định nghĩa hàm từ tệp "function.cpp"
#include "function.cpp"

int main()
{
    int chooseRequest; // Biến để lưu trữ sự lựa chọn của người dùng

    // Hiển thị menu và chấp nhận yêu cầu từ người dùng cho đến khi họ chọn thoát
    do
    {
        // Hiển thị các tùy chọn trong menu
       cout << endl << right << setw(30) << "MENU";
        cout << "\n1. Quan ly du lieu.";
        cout << "\n2. Thong ke N vat lieu co gia cao nhat.";
        cout << "\n3. Hien thi tong so tien cua mot phieu giao hang.";
        cout << "\n4. Thong ke phieu giao hang theo thoi gian.";
        cout << "\n5. Thong ke N vat lieu ban chay nhat.";
        cout << "\n6. Thong ke doanh thu tong cong trong mot khoang thoi gian.";
        cout << "\n7. Sao luu va khoi phuc du lieu.";
        cout << "\n0. Thoat.";
        cout << "\nVui long chon so de thuc hien chuong trinh: ";
        cin >> chooseEvent;


        // Xử lý các yêu cầu từ người dùng
        switch (chooseEvent)
        {
            case 1:
                case1(); // Gọi hàm thực hiện chức năng quản lý dữ liệu
                break;
            case 2:
                case2(); // Gọi hàm thực hiện thống kê N vật liệu có giá cao nhất
                break;
            case 3:
                case3(); // Gọi hàm thực hiện hiển thị tổng số tiền của một phiếu giao hàng
                break;
            case 4:
                case4(); // Gọi hàm thực hiện thống kê phiếu giao hàng theo thời gian
                break;
            case 5:
                case5(); // Gọi hàm thực hiện thống kê N vật liệu bán chạy nhất
                break;
            case 6:
                case6(); // Gọi hàm thực hiện thống kê doanh thu tổng cộng trong một khoảng thời gian
                break;
            case 7:
                case7(); // Gọi hàm thực hiện sao lưu và khôi phục dữ liệu
                break;
        }
    } while (chooseEvent != 0); // Lặp lại cho đến khi người dùng chọn thoát

    return 0;
}
