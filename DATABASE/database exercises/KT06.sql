create database De06
go 
use De06
go

create table KHOA (
  IDKhoa varchar(4),
  TenKhoa nvarchar(19),
  TruongKhoa int,
  SoLuong int,
  primary key (IDKhoa)
)

create table GIAOVIEN (
  IDKhoa varchar(4),
  IDGiaoVien int,
  Hoten nvarchar(15),
  SoCMND char (10),
  IDCVChinh char (3),
  Stt int,
  primary key (IDKhoa, IDGiaoVien)
)

create table CONGVIEC (
  IDDuAn char(3),
  STTTo int,
  IDGV int,
  IDKhoa varchar(4),
  MoTa nvarchar (50),
  primary key (IDDuAn, STTTo)
)

alter table GIAOVIEN add foreign key (IDKhoa) references KHOA (IDKhoa)
alter table KHOA add foreign key (IDKhoa,TruongKhoa) references GIAOVIEN (IDKhoa, IDGiaoVien)
alter table GIAOVIEN add foreign key (IDCVChinh, Stt) references CONGVIEC (IDDuAn, STTTo)
alter table CONGVIEC add foreign key (IDKhoa, IDGV) references GIAOVIEN (IDKhoa, IDGiaoVien)

insert into KHOA (IDKhoa, TenKhoa, TruongKhoa, SoLuong) values 
('CNTT', N'Công nghệ thông tin', null, null),
('HH', N'Hóa học', null, null),
('SH', N'Sinh học', null, null)

insert into GIAOVIEN (IDKhoa, IDGiaoVien, Hoten, SoCMND, IDCVChinh, Stt) values 
('CNTT', 1, N'Nguyễn Văn A', '0123412441', NULL, 1),
('CNTT', 2, N'Nguyễn Thị Sa', '0231389978', NULL, 1),
('HH', 1, N'Trần Trung Minh', '0244929477', NULL, NULL),
('HH', 2, N'Thái Hà', '0901234321', NULL, 2),
('SH', 1, N'Hà Minh', 'NULL', NULL, 1)

insert into CONGVIEC (IDDuAn, STTTo, IDKhoa, IDGV, MoTa) values 
('CV1', 1, 'CNTT', 2, N'Dự án Smart Home'),
('CV1', 2, 'HH', 2, N'Dự án nghiên cứu vật liệu nhẹ bền phục vụ xây dựng'),
('CV2', 1, 'CNTT', 1, N'Dự án con mắt công nghệ hỗ trợ người khiếm thị'),
('CV2', 2, 'SH', 1, N'Dự án trồng cây trên vùng đất ngập mặn')

update KHOA set TruongKhoa = 1 where IDKhoa in ('CNTT', 'SH')
update KHOA set TruongKhoa = 2 where IDKhoa in ('HH')

update GIAOVIEN set IDCVChinh = 'CV1' where IDKhoa in ('CNTT', 'SH') and IDGiaoVien = 1
update GIAOVIEN set IDCVChinh = 'CV1' where IDKhoa in ('HH') and IDGiaoVien = 2
update GIAOVIEN set IDCVChinh = 'CV2' where IDKhoa in ('CNTT') and IDGiaoVien = 2

--Cho biết giáo viên và tên công việc chính của giáo viên thuộc khoa công nghệ

select gv.IDGiaoVien, gv.Hoten, cv.MoTa
from GIAOVIEN gv
join KHOA k on gv.IDKhoa = k.IDKhoa
join CONGVIEC cv on cv.IDDuAn = gv.IDCVChinh and gv.Stt = cv.STTTo
where k.TenKhoa like N'%Công nghệ%'

--Cho biết tên khoa, số giáo viên và tổng số công việc giáo viên tham gia
select k.TenKhoa, COUNT (gv.IDGIaoVien) as SoGiaoVien, COUNT (gv.IDCVChinh) as TongCongViec
from KHOA k
left join GIAOVIEN gv on k.IDKhoa = gv.IDKhoa 
left join CONGVIEC cv on cv.IDKhoa = k.IDKhoa and cv.IDGV = gv.IDGiaoVien
group by k.TenKhoa

select * from KHOA
select * from GIAOVIEN
select * from CONGVIEC

--Cho biết giáo viên và tên công việc chính của giáo viên thuộc khoa công nghệ
select gv.IDGiaoVien, gv.Hoten, cv.MoTa
from GIAOVIEN gv
join CONGVIEC cv on gv.IDCVChinh = cv.IDDuAn and cv.STTTo = gv.Stt
join KHOA k on k.IDKhoa = gv.IDKhoa
where k.TenKhoa like N'%Công nghệ%'
--Cho biết tên khoa, số giáo viên và tổng số công việc giáo viên tham gia
select k.TenKhoa, COUNT(gv.IDGiaoVien) as TongSoGV, COUNT(cv.STTTo) as SoCongViec
from KHOA k 
join GIAOVIEN gv on k.IDKhoa = gv.IDKhoa
join CONGVIEC cv on cv.IDGV = gv.IDGiaoVien and cv.IDKhoa = gv.IDKhoa
group by k.TenKhoa