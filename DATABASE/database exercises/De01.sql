create database De_01
go 
use De_01
go

create table BAIHAT (
  IDTheLoai char(10),
  IDBaiHat char(10),
  TenBaiHat nvarchar(30),
  IDTacGia int,
  primary key (IDTheLoai, IDBaiHat)
)

create table TACGIA (
  IDTacGia int,
  HoTen nvarchar(30),
  IDTheLoaiSoTruongNhat char(10),
  IDBaiHatTieuBieuNhat char(10),
  primary key (IDTacGia)
)

create table THELOAI (
  IDTheLoai char(10),	
  Ten nvarchar(30),
  IDTheLoaiCha char(10),
  IDBaiHatTieuBieu char(10),
  primary key (IDTheLoai)
)

alter table BAIHAT add foreign key (IDTheLoai) references THELOAI (IDTheLoai)
alter table BAIHAT add foreign key (IDTacGia) references TACGIA (IDTacGia)
alter table THELOAI add foreign key (IDTheLoai, IDBaiHatTieuBieu) references BAIHAT (IDTheLoai, IDBaiHat)
alter table THELOAI add foreign key (IDTheLoaiCha) references THELOAI (IDTheLoai)
alter table TACGIA add foreign key (IDTheLoaiSoTruongNhat, IDBaiHatTieuBieuNhat) references BAIHAT (IDTheLoai, IDBaiHat)

insert THELOAI (IDTheLoai, Ten, IDTheLoaiCha, IDBaiHatTieuBieu) values
('TL01', N'Nhạc trữ tình', 'TL00', NULL),
('TL02', N'Nhạc cách mạng', 'TL00', NULL),
('TL00', N'Nhạc Việt Nam', NULL, NULL)

insert BAIHAT (IDTheLoai, IDBaiHat, TenBaiHat, IDTacGia) values
('TL01', 'BH01', N'Ngẫu hứng lý qua cầu', NULL),
('TL01', 'BH02', N'Chuyến đò quê hương', NULL),
('TL02', 'BH01', N'Du kích sông Thao', NULL),
('TL02', 'BH02', N'Sợi nhớ sợi thương', NULL)

insert TACGIA (IDTacGia, HoTen, IDTheLoaiSoTruongNhat, IDBaiHatTieuBieuNhat) values
(1, N'Trần Tiến', 'TL01', 'BH01'),
(2, N'Đỗ Nhuận', 'TL02', 'BH01'),
(3, N'Phan Huỳnh Điểu', 'TL02', 'BH02'),
(4, N'Vi Nhật Tảo', 'TL01', 'BH02')

update BAIHAT set IDTacGia = 1 where IDTheLoai = 'TL01' and IDBaiHat = 'BH01'
update BAIHAT set IDTacGia = 4 where IDTheLoai = 'TL01' and IDBaiHat = 'BH02'
update BAIHAT set IDTacGia = 2 where IDTheLoai = 'TL02' and IDBaiHat = 'BH01'
update BAIHAT set IDTacGia = 3 where IDTheLoai = 'TL02' and IDBaiHat = 'BH02'

update THELOAI set IDBaiHatTieuBieu = 'BH01' where IDTheLoai = 'TL01'
update THELOAI set IDBaiHatTieuBieu = 'BH02' where IDTheLoai = 'TL02'

select * from THELOAI
select * from BAIHAT
select * from TACGIA

--Cho danh sách bài hát thuộc thể loại “nhạc trữ tình” của tác giả Đỗ Nhuận
select bh.IDBaiHat, bh.TenBaiHat
from BAIHAT bh
join THELOAI tl on bh.IDTheLoai = tl.IDTheLoai
join TACGIA tg on bh.IDTacGia = tg.IDTacGia
where tl.Ten = N'nhạc trữ tình' and tg.HoTen = N'Đỗ Nhuận'

--Cho danh sách các thể loại chưa có bài hát nào trong thể loại đó
select tl.IDTheLoai, tl.Ten
from THELOAI tl
left join BAIHAT bh on tl.IDTheLoai = bh.IDTheLoai
where bh.IDBaiHat is null

select tl.IDTheLoai, tl.Ten
from THELOAI tl
except
select tl.IDTheLoai,tl.Ten
from BAIHAT bh join THELOAI tl on bh.IDTheLoai = tl.IDTheLoai

--Cho danh sách tác giả (mã, họ tên, số bài hát) của mỗi tác giả.
select tg.IDTacGia, tg.HoTen, COUNT (bh.IDBaiHat) as SoBaiHat
from TACGIA tg
left join BAIHAT bh on bh.IDTacGia = tg.IDTacGia
group by tg.IDTacGia, tg.HoTen

