create database De_03
go 
use De_03
go

create table DOI (
  IDDoi int,
  TenDoi nvarchar(12),
  DoiTruong int,
  SoLuong int,
  primary key (IDDoi)
)

create table THANHVIEN (
  IDThanhVien int,
  HoTen nvarchar(16),
  SoCMND char(9),
  DiaChi nvarchar(10),
  NgaySinh date,
  primary key (IDThanhVien)
)

create table BOTRI (
  IDDoi int,
  IDThanhVien int,
  DiaChi nvarchar(22),
  NhiemVu nvarchar(24),
  QuanLi int,
  primary key (IDDoi, IDThanhVien)
)

alter table BOTRI add foreign key (IDDoi) references DOI (IDDoi)
alter table BOTRI add foreign key (IDThanhVien) references THANHVIEN (IDThanhVien)
alter table DOI add foreign key (DoiTruong) references THANHVIEN (IDThanhVien)
alter table BOTRI add foreign key (QuanLi) references THANHVIEN (IDThanhVien)

insert into THANHVIEN (IDThanhVien, HoTen, SoCMND, DiaChi, NgaySinh) values
(1, N'Nguyễn Quan Tùng', '240674018', 'TPHCM', '2000/1/30'),
(2, N'Lưu Phi Nam', '240674027', N'Quảng Nam', '2001/3/12'),
(3, N'Lê Quang Bảo', '240674063', N'Quảng Ngãi', '1999/5/14'),
(4, N'Hà Ngọc Thúy', '240674504', 'TPHCM', '1998/7/26'),
(5, N'Trương Thị Minh', '240674405', N'Hà Nội', Null),
(6, N'Ngô Thị Thủy', '240674306', null, '2000/9/18')

insert into DOI(IDDoi, TenDoi, DoiTruong) values
(2, N'Đôi Tân Phú', 1),
(7, N'Đội Bình Phú', 2)	

insert into BOTRI (IDDOI, IDThanhVien, DiaChi, NhiemVu, QuanLi) values
(2, 2, N'123 Vườn Lài Tân Phú', N'Trực khu vực vòng xoay 1', 1),
(2, 1, N'45 Phú Thọ Hòa Tân Phú', N'Theo dõi hoạt động', 1),
(7, 3, N'11 Chợ lớn Bình Phú', null, 2),
(7, 4, N'2 Bis Nguyễn Văn Cừ Q5', Null, 5)


select * from DOI
select * from BOTRI
select * from THANHVIEN

--Cho biết tên đội, tên đội trưởng của các thành viên thực hiện nhiệm vụ
--tại địa chỉ Tân Phú
select d.TenDoi, tv.HoTen
from DOI d 
join THANHVIEN tv on d.DoiTruong = tv.IDThanhVien
join BOTRI bt on bt.IDDoi = d.IDDoi
where bt.DiaChi like N'% Tân Phú'	
group by d.TenDoi, tv.HoTen

--cho biết tên quản lý và số lượng thành viên có cung cấp ngày sinh do
--người này quản lý.
select ql.HoTen as TenQL, COUNT(tv.IDThanhVien) as SoLuongTV
from THANHVIEN tv 
join BOTRI bt on bt.IDThanhVien = tv.IDThanhVien
join THANHVIEN ql on bt.QuanLi = ql.IDThanhVien
where tv.NgaySinh is not null
group by ql.HoTen