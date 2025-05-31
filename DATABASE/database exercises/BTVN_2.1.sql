--Họ tên: Nguyễn Thanh Phong
--MSSV: 23120154
--Lớp: 23CTT2
--Đề: Quản lý bán hàng siêu thị

create database QLBHST

GO
USE QLBHST
GO

-- Tạo bảng Loại Sản Phẩm
CREATE TABLE LoaiSanPham (
    MaLoai CHAR(1) PRIMARY KEY,
    TenLoai NVARCHAR(12) NOT NULL
);

-- Tạo bảng Sản Phẩm
CREATE TABLE SanPham (
    MaSP CHAR(4) PRIMARY KEY,
    Ten NVARCHAR(27) NOT NULL,
    GiaTien INT NOT NULL,
    SoLuongTon SMALLINT NOT NULL,
    DonViTinh NVARCHAR(3) NOT NULL,
    MaLoai CHAR(1),
    CONSTRAINT FK_SanPham_Loai FOREIGN KEY (MaLoai) REFERENCES LoaiSanPham(MaLoai)
);

-- Tạo bảng Khách Hàng
CREATE TABLE KhachHang (
    MaKH CHAR(4) PRIMARY KEY,
    HoTen NVARCHAR(17) NOT NULL,
    DiaChi NVARCHAR(11) NOT NULL,
    DienThoai VARCHAR(15) NOT NULL,
    NamSinh SMALLINT NOT NULL,
    GioiTinh NVARCHAR(3) NOT NULL
);

-- Tạo bảng Hóa Đơn
CREATE TABLE HoaDon (
    MaHD CHAR(4) PRIMARY KEY,
    NgayLap DATE NOT NULL,
    MaKH CHAR(4) NOT NULL,
    CONSTRAINT FK_HoaDon_KhachHang FOREIGN KEY (MaKH) REFERENCES KhachHang(MaKH)
);

-- Tạo bảng Chi Tiết Hóa Đơn
CREATE TABLE ChiTietHoaDon (
    MaHD CHAR(4),
    MaSP CHAR(4),
    SoLuong SMALLINT NOT NULL,
    DonGia SMALLINT NOT NULL,
    PRIMARY KEY (MaHD, MaSP),
    CONSTRAINT FK_ChiTietHoaDon_HoaDon FOREIGN KEY (MaHD) REFERENCES HoaDon(MaHD),
    CONSTRAINT FK_ChiTietHoaDon_SanPham FOREIGN KEY (MaSP) REFERENCES SanPham(MaSP)
);

-- Thêm dữ liệu vào Loại Sản Phẩm
INSERT INTO LoaiSanPham (MaLoai, TenLoai) VALUES
('A', N'Đồ dùng'),
('B', N'Nồi cơm điện'),
('C', N'Đèn điện');

-- Thêm dữ liệu vào Sản Phẩm
INSERT INTO SanPham (MaSP, Ten, GiaTien, SoLuongTon, DonViTinh, MaLoai) VALUES
('SP01', N'Bột giặt Omo', 30, 70, N'túi', 'A'),
('SP02', N'Bột giặt Tide', 25, 200, N'túi', 'A'),
('SP03', N'Đèn bàn Rạng Đông', 100, 90, N'cái', 'C'),
('SP04', N'Nồi cơm điện SHARP 3041', 2500, 10, N'cái', 'B'),
('SP05', N'Bàn chải đánh răng PS', 12, 12, N'cái', 'A'),
('SP06', N'Nồi cơm điện PANASONIC 2097', 2000, 8, N'cái', 'B'),
('SP07', N'Bàn chải đánh răng Colgate', 16, 100, N'cái', 'A');

-- Thêm dữ liệu vào Khách Hàng
INSERT INTO KhachHang (MaKH, HoTen, DiaChi, DienThoai, NamSinh, GioiTinh) VALUES
('KH01', N'Nguyễn Thanh Tùng', N'Hồ Chí Minh', '9-9091-2233', 1984, N'Nam'),
('KH02', N'Lê Nhật Nam', N'Hồ Chí Minh', '9-1234-2134', 1972, N'Nữ'),
('KH03', N'Nguyễn Thị Thanh', N'Cà Mau', '9-2222-3333', 1981, N'Nữ'),
('KH04', N'Lê Thị Lan', N'Bình Dương', '9-1111-1111', 1984, N'Nữ'),
('KH05', N'Trần Minh Quang', N'Đồng Nai', '9-2222-5555', 1984, N'Nam'),
('KH06', N'Lê Văn Hải', N'Hồ Chí Minh', '9-1234-4321', 1970, N'Nam'),
('KH07', N'Dương Văn Hai', N'Đồng Nai', '9-1111-0000', 1988, N'Nam');

-- Thêm dữ liệu vào Hóa Đơn
INSERT INTO HoaDon (MaHD, NgayLap, MaKH) VALUES
('HD01', '2011-03-20', 'KH01'),
('HD02', '2011-02-15', 'KH02'),
('HD03', '2011-01-18', 'KH05'),
('HD04', '2010-09-16', 'KH01'),
('HD05', '2011-02-27', 'KH02');

-- Thêm dữ liệu vào Chi Tiết Hóa Đơn
INSERT INTO ChiTietHoaDon (MaHD, MaSP, SoLuong, DonGia) VALUES
('HD01', 'SP01', 2, 30),
('HD01', 'SP02', 2, 25),
('HD02', 'SP01', 3, 30),
('HD03', 'SP02', 3, 25),
('HD03', 'SP03', 1, 90),
('HD03', 'SP01', 3, 30),
('HD04', 'SP04', 1, 2400),
('HD05', 'SP06', 1, 2000),
('HD05', 'SP01', 5, 30);

-- Kiểm tra dữ liệu
SELECT * FROM LoaiSanPham;
SELECT * FROM SanPham;
SELECT * FROM KhachHang;
SELECT * FROM HoaDon;
SELECT * FROM ChiTietHoaDon;

-- Xóa bảng theo đúng thứ tự nếu cần thiết
--DROP TABLE ChiTietHoaDon;
--DROP TABLE HoaDon;
--DROP TABLE KhachHang;
--DROP TABLE SanPham;
--DROP TABLE LoaiSanPham;

--Yêu cầu 1
---Cho ds các sản phẩm được tất cả khách hàng TPHCM mua
select CTHD.MaSP, SP.Ten
from ChiTietHoaDon CTHD
JOIN SanPham SP on CTHD.MaSP = SP.MaSP
JOIN HoaDon HD on CTHD.MaHD = HD.MaHD
JOIN KhachHang KH on HD.MaKH = KH.MaKH
where KH.DiaChi = N'Hồ Chí Minh'
group BY CTHD.MaSP, SP.Ten
having count(distinct HD.MaKH) = (select count(*) from KhachHang where DiaChi = N'Hồ Chí Minh');
--Yêu cầu 2
--Cho ds các khách hàng chưa mua sản phẩm bột giặt loại A nào
select * from KhachHang kh
where not exists (
  select * from HoaDon hd
  join ChiTietHoaDon cthd on cthd.MaHD = hd.MaHD
  join SanPham sp on sp.MaSP = cthd.MaSP
  where kh.MaKH = hd.MaKH and sp.Ten like N'Bột giặt%' and sp.MaLoai = 'A'  
)
--Yêu cầu 3
---Cho ds các sản phẩm chưa bán được trong 3 tháng trở lại đây
select * from SanPham sp
where not exists (
  select cthd.MaSp from ChiTietHoaDon cthd
  join HoaDon hd on hd.MaHD = cthd.MaHD
  where cthd.MaSP = sp.MaSP and hd.NgayLap >= DATEADD (MONTH, -3, GETDATE())
)
--Yêu cầu 4
--CHo ds khách hàng mua nhiều lượt nhất trong năm nay
select KH.MaKH, KH.HoTen, count(CTHD.MaSP) as SoLuotMua
from ChiTietHoaDon CTHD 
join HoaDon HD on CTHD.MaHD = HD.MaHD
join KhachHang KH on HD.MaKH = KH.MaKH
where year(HD.NgayLap) = year(GETDATE())
group by KH.MaKH, KH.HoTen
having count(CTHD.MaSP) = (
	select top 1 count(CTHD.MaSP) as SoLuotMua
	from ChiTietHoaDon CTHD 
	join HoaDon HD on CTHD.MaHD = HD.MaHD
	join KhachHang KH on HD.MaKH = KH.MaKH
	where year(HD.NgayLap) = year(GETDATE())
	group by KH.MaKH
	order by SoLuotMua desc
)
--Yêu cầu 5
---Cho ds các khách hàng có tổng tiền mua hàng nhiều nhất
  select kh.MaKH, KH.HoTen, sum(CTHD.DonGia * CTHD.SoLuong) 
  from KhachHang KH, HoaDon HD, ChiTietHoaDon CTHD
  where KH.MaKH = HD.MaKH and HD.MaHD = CTHD.MaHD

  group by KH.MaKH, Kh.HoTen
  having sum(CTHD.DonGia * CTHD.SoLuong)
	>= all (
	select sum(CTHD.SoLuong * CTHD.DonGia)
	from HoaDon HD, ChiTietHoaDon CTHD
	where HD.MaHD = CTHD.MaHD
	group by HD.MaKH
	)
--Yêu cầu 6
---cho ds các sản phẩm được mua nhiều nhất
select sp.MaSP, sp.ten, sum(cthd.SoLuong) as SoLuongDuocMua
from ChiTietHoaDon cthd 
join SanPham sp on sp.MaSP = cthd.MaSP
group by sp.MaSP, sp.ten
having sum(cthd.SoLuong) = (
  select top 1 sum(cthd.SoLuong) as SoLuongDuocMua
  from ChiTietHoaDon cthd 
  join SanPham sp on sp.MaSP = cthd.MaSP
  group by sp.MaSP, sp.ten
  order by SoLuongDuocMua desc)
--Yêu cầu 7
---cho ds các sản phẩm có doanh thu thấp nhất
select sp.MaSP, sp.ten, sum(cthd.DonGia*cthd.SoLuong) as DoanhThu
from ChiTietHoaDon cthd 
join SanPham sp on sp.MaSP = cthd.MaSP
group by sp.MaSP, sp.ten
having sum(cthd.DonGia*cthd.SoLuong) = (
  select top 1 sum(cthd.DonGia*cthd.SoLuong) as DoanhThu
  from ChiTietHoaDon cthd 
  join SanPham sp on sp.MaSP = cthd.MaSP
  group by sp.MaSP, sp.ten
  order by DoanhThu asc)
