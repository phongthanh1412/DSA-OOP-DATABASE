create database QLCoVua
go 
use QLCoVua
go

create table CLB (
  IDCLB char(10),
  TenCLB nvarchar(50),
  DiaChi nvarchar(50),
  primary key (IDCLB)
) 

create table DOI (
  IDCLB char(10),
  IDDoi char(10),
  TenDoi nvarchar(30),
  IDDoiTruong char(10),
  primary key (IDCLB, IDDoi)
) 

create table HOIVIEN (
  IDCLB char(10),
  IDHoiVien char(10),
  HoTen nvarchar(30),
  NgaySinh date,
  IDDoi char(10),
  IDBanCungTapLuyen char(10),
  primary key (IDCLB, IDHoiVien)
) 

alter table DOI add foreign key (IDCLB) references CLB (IDCLB)
alter table DOI add foreign key (IDCLB, IDDoiTruong) references HOIVIEN (IDCLB, IDHoiVien)
alter table HOIVIEN add foreign key (IDCLB) references CLB (IDCLB)
alter table HOIVIEN add foreign key (IDCLB, IDDoi) references DOI (IDCLB, IDDoi)
alter table HOIVIEN add foreign key (IDCLB, IDBanCungTapLuyen) references HOIVIEN (IDCLB, IDHoiVien)

insert CLB (IDCLB, TenCLB, DiaChi) values
('C01', N'Câu lạc bộ Phan Đình Phùng', N'P1, Q 5, Hồ Chí Minh'),
('C02', N'Câu lạc bộ Võ Thị Sáu', N'P3, Q 1, Hồ Chí Minh')


insert DOI (IDCLB, IDDoi, TenDoi, IDDoiTruong) values
('C01', 'D01', N'Đội 1', NULL),
('C01', 'D02', N'Đội 2', NULL),
('C02', 'D01', N'Đội 1', NULL)


insert HOIVIEN (IDCLB, IDHoiVien, HoTen, NgaySinh, IDDoi, IDBanCungTapLuyen) values
('C01', 'H01', N'Tiến', '1984/7/15', 'D01', 'H03'),
('C01', 'H02', N'Tùng', '1983/9/26', 'D02', 'H04'),
('C01', 'H03', N'Bình', '1984/10/18', 'D01', 'H01'),
('C01', 'H04', N'Đông', '1987/12/9', 'D02', 'H02'),
('C02', 'H01', N'Nam', '1988/5/3', 'D01', 'H02'),
('C02', 'H02', N'Á', '1986/6/5', 'D01', 'H01')

update DOI set IDDoiTruong = 'H01' where IDDoi in ('D01')
update DOI set IDDoiTruong = 'H02' where IDDoi in ('D02')

select * from CLB
select * from DOI
select * from HOIVIEN

--Cho biết danh sách các đội (IDCLB, TênDoi) có học viên sinh từ năm 1988
--trở về sau
select d.IDCLB, d.TenDoi
from DOI d
join HOIVIEN hv on d.IDCLB = hv.IDCLB
where year(hv.NgaySinh) >= 1988

--Cho biết danh sách các học viên (IDCLB, HoTen) có người cùng tập luyện
--bằng tuổi.
select hv.IDCLB, hv.HoTen
from HOIVIEN hv 
join HOIVIEN ban on hv.IDBanCungTapLuyen = ban.IDHoiVien
where year(hv.NgaySinh) = year(ban.NgaySinh)
