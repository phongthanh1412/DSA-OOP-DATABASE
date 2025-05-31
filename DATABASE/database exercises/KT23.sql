create database De_23
go 
use De_23
go

create table DOI_THI_DAU (
  IDDoi char(10),
  TenDoi nvarchar(40),
  KhauHieu nvarchar(100),
  IDDoiTruong int,
  IDDoiMuonGap char(10),
  primary key (IDDoi)
)

create table THANH_VIEN (
  IDDoi char(10),
  STT int,
  HoTen nvarchar(40),
  NgaySinh date,
  Email varchar(20),
  IDDoiPhongCach char(10),
  primary key (IDDoi, STT)
)

create table CT_TRAN_DAU (
  IDTranDau varchar(3),
  IDDoi char(10),
  DiemDatDuoc int,
  KetQua bit,
  primary key (IDTranDau, IDDoi)
)

alter table THANH_VIEN add foreign key (IDDoi) references DOI_THI_DAU (IDDoi)
alter table THANH_VIEN add foreign key (IDDoiPhongCach) references DOI_THI_DAU (IDDoi)
alter table CT_TRAN_DAU add foreign key (IDDoi) references DOI_THI_DAU (IDDoi)
alter table DOI_THI_DAU add foreign key (IDDoiMuonGap) references DOI_THI_DAU (IDDoi)

insert DOI_THI_DAU (IDDoi, TenDoi, KhauHieu, IDDoiTruong, IDDoiMuonGap) values
('AL', 'All41', N'All For One chiến thắng !!', 1, 'PH'),
('PH', 'PrizeHunters', N'PrizeHunters bách phát bách thắng.', 2, 'MI'),
('MI', 'MicroIdeas', N'MicroIdeas hãy đoàn kết giành cúp', 1, 'PH')

insert THANH_VIEN (IDDoi, STT, HoTen, NgaySinh, Email, IDDoiPhongCach) values
('AL', 1, N'Huy', '1987/1/1', 'huy@gmail.com', null),
('AL', 2, N'Bình', '1986/8/15', 'binh@gmail.com', 'PH'),
('PH', 1, N'Hà', '1986/4/20', 'ha@gmail.com', null),
('PH', 2, N'Ngọc', '1988/4/12', 'ngoc@gmail.com', 'AL'),
('MI', 1, N'Dũng', '1986/7/14', 'dung@gmail.com', 'AL')

insert CT_TRAN_DAU (IDTranDau, IDDoi, DiemDatDuoc, KetQua) values
('BK1', 'AL', 250, 0),
('BK1', 'PH', 350, 1),
('BK1', 'MI', 100, 0),
('CK', 'PH', 300, 1)

select * from DOI_THI_DAU
select * from THANH_VIEN
select * from CT_TRAN_DAU
