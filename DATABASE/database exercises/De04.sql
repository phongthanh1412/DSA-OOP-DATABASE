create database De_04_1
go 
use De_04_1
go

create table LOPHOC (
  IDLopHoc char(3),  NamBD int,  ChuNhiem char(4),  IDKhoa int,  SoLuong int,
  primary key (IDLopHoc)
)

create table GIAOVIEN (
  IDKhoa int,
  IDMaGV char(4),
  HoTen nvarchar(16),
  SoCMND char(9),
  NgaySinh date,
  IDQuanLi char(4),
  primary key (IDKhoa, IDMaGV)
)

create table LICHDAY (
  IDLop char(3),
  IDThuTiet varchar(8),
  IDPhongHoc int,
  GiaoVien char(4),
  IDKhoa int,
  ThoiLuong int,
  primary key (IDLop, IDThuTiet, IDPhongHoc)
)

alter table LICHDAY add foreign key (IDLop) references LOPHOC (IDLopHoc)
alter table LICHDAY add foreign key (IDKhoa, GiaoVien) references GIAOVIEN (IDKhoa, IDMaGV)
alter table LOPHOC add foreign key (IDKhoa, ChuNhiem) references GIAOVIEN (IDKhoa, IDMaGV)
alter table GIAOVIEN add foreign key (IDKhoa, IDQuanLi) references GIAOVIEN (IDKhoa, IDMaGV)

insert GIAOVIEN (IDKhoa, IDMaGV, HoTen, SoCMND, NgaySinh, IDQuanLi) values
(1, '1716', N'Nguyễn Quan Tùng', '240674018', '1988/2/1', '0753'),
(2, '0357', N'Lưu Phi Nam', '240674027', '1980/7/20', '1716'),
(2, '1716', N'Lê Quang Bảo', '240674063', null, null),
(1, '0753', N'Hà Ngọc Thúy', '240674504', '1990/5/2', null),
(1, '0357', N'Trương Thị Minh', '240674405', Null, '0753'),
(1, '1718', N'Ngô Thị Thủy', '240674306', null, '0357')

insert LOPHOC (IDLopHoc, NamBD, ChuNhiem, IDKhoa) values
('L01', 2015, '0357', 2),
('L02', 2013, '1716', 1)

insert LICHDAY (IDLop, IDThuTiet, IDPhongHoc, GiaoVien, IDKhoa, ThoiLuong) values
('L01', 'T2(1-6)', 2, '1718', 1, 10),
('L02', 'T2(7-12)', 1, '0753', 1, 30),
('L01', 'T4(4-6)', 5, '0357', 2, 25)

select *from LOPHOC
select *from LICHDAY
select *from GIAOVIEN
