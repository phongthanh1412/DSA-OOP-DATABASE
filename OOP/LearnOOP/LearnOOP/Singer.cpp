#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class NgaySinh {
private:
    int ngay, thang, nam;
public:
    NgaySinh();
    NgaySinh(int ngay, int thang, int nam);
    bool operator>(NgaySinh);
    bool operator<(NgaySinh);
};

class Casi {
private:
    string ID, ngheDanh, tenThat;
    NgaySinh ngaysinh;
    float catXe;
    int soLuongShow;
public:
    Casi();
    Casi(string ID, string ngheDanh, string tenThat, NgaySinh ngaysinh, float catXe, int soLuongShow);
    Casi(const Casi&);
    Casi& operator++();
    Casi& operator--();
    bool operator>(Casi);
    bool operator<(Casi);
    float tinhTongCatXe() const; // Thêm phương thức tính tổng cát-xê
};

class DanhSach {
private:
    Casi* ds;
    int size;
public:
    DanhSach();
    DanhSach(int size);
    ~DanhSach();
    void nhap();
    void sapXep();
    float tongTien();
};

// Định nghĩa các phương thức của lớp NgaySinh
NgaySinh::NgaySinh() : ngay(0), thang(0), nam(0) {}

NgaySinh::NgaySinh(int ngay, int thang, int nam) : ngay(ngay), thang(thang), nam(nam) {}

bool NgaySinh::operator>(NgaySinh other) {
    return (nam > other.nam) || (nam == other.nam && thang > other.thang) ||
        (nam == other.nam && thang == other.thang && ngay > other.ngay);
}

bool NgaySinh::operator<(NgaySinh other) {
    return (nam < other.nam) || (nam == other.nam && thang < other.thang) ||
        (nam == other.nam && thang == other.thang && ngay < other.ngay);
}

// Định nghĩa các phương thức của lớp Casi
Casi::Casi() : ID(""), ngheDanh(""), tenThat(""), ngaysinh(), catXe(0), soLuongShow(0) {}

Casi::Casi(string ID, string ngheDanh, string tenThat, NgaySinh ngaysinh, float catXe, int soLuongShow)
    : ID(ID), ngheDanh(ngheDanh), tenThat(tenThat), ngaysinh(ngaysinh), catXe(catXe), soLuongShow(soLuongShow) {}

Casi::Casi(const Casi& other)
    : ID(other.ID), ngheDanh(other.ngheDanh), tenThat(other.tenThat), ngaysinh(other.ngaysinh), catXe(other.catXe), soLuongShow(other.soLuongShow) {}

Casi& Casi::operator++() {
    catXe += 10;
    return *this;
}

Casi& Casi::operator--() {
    catXe -= 10;
    return *this;
}

bool Casi::operator<(Casi other) {
    return ngaysinh < other.ngaysinh;
}

bool Casi::operator>(Casi other) {
    return ngaysinh > other.ngaysinh;
}

float Casi::tinhTongCatXe() const {
    return catXe * soLuongShow;
}

// Định nghĩa các phương thức của lớp DanhSach
DanhSach::DanhSach() : ds(nullptr), size(0) {}

DanhSach::DanhSach(int size) : size(size) {
    ds = new Casi[size];
}

DanhSach::~DanhSach() {
    delete[] ds;
}

void DanhSach::nhap() {
    for (int i = 0; i < size; i++) {
        string ID, ngheDanh, tenThat;
        float catxe;
        int soLuongShow;
        int ngay, thang, nam;
        cout << "Nhap thong tin ca si thu " << i + 1 << ":\n";
        cout << "ID: "; cin >> ID;
        cout << "Nghe danh: "; cin.ignore(); getline(cin, ngheDanh);
        cout << "Ten that: "; getline(cin, tenThat);
        cout << "Ngay sinh (ngay thang nam): "; cin >> ngay >> thang >> nam;
        cout << "Cat xe: "; cin >> catxe;
        cout << "So luong show: "; cin >> soLuongShow;
        ds[i] = Casi(ID, ngheDanh, tenThat, NgaySinh(ngay, thang, nam), catxe, soLuongShow);
    }
}

void DanhSach::sapXep() {
    sort(ds, ds + size);
}

float DanhSach::tongTien() {
    float tong = 0;
    for (int i = 0; i < size; i++) {
        tong += ds[i].tinhTongCatXe();
    }
    return tong;
}

int main() {
    int n;
    cout << "Nhap so luong ca si: ";
    cin >> n;
    DanhSach ds(n);
    ds.nhap();
    ds.sapXep();
    cout << "Tong tien cac ca si khi tham gia show: " << ds.tongTien() << " trieu dong\n";
    return 0;
}
