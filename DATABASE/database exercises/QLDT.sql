--Họ tên: Nguyễn Thanh Phong
--MSSV: 23120154
--Lớp: 23CTT2
--Đề: Quản lý đề tài

create database QLDT

GO 
USE QLDT
GO

-- Bảng KHOA
CREATE TABLE KHOA (
    MAKHOA VARCHAR(4) PRIMARY KEY,
    TENKHOA NVARCHAR(19),
    NAMTL SMALLINT,
    PHONG VARCHAR(3),
    DIENTHOAI VARCHAR(10),
    TRUONGKHOA CHAR(3),
    NGAYNHANCHUC DATE
);

-- Bảng GIAOVIEN
CREATE TABLE GIAOVIEN (
    MAGV CHAR(3) PRIMARY KEY,
    HOTEN NVARCHAR(15),
    LUONG DECIMAL(5, 1),
    PHAI NVARCHAR(3),
    NGSINH DATE,
    DIACHI NVARCHAR(36),
    GVQLCM CHAR(3),
    MABM NVARCHAR(4)
);

-- Bảng CHUDE
CREATE TABLE CHUDE (
    MACD CHAR(4) PRIMARY KEY,
    TENCD NVARCHAR(21)
);

-- Bảng DETAI
CREATE TABLE DETAI (
    MADT CHAR(3) PRIMARY KEY,
    TENDT NVARCHAR(40),
    CAPQL NVARCHAR(8),
    KINHPHI DECIMAL(5, 1),
    NGAYBD DATE,
    NGAYKT DATE,
    MACD CHAR(4),
    GVCNDT CHAR(3), 
);

-- Bảng BOMON
CREATE TABLE BOMON (
    MABM NVARCHAR(4) PRIMARY KEY,
    TENBM NVARCHAR(18),
    PHONG CHAR(3),
    DIENTHOAI VARCHAR(10),
    TRUONGBM CHAR(3),
    MAKHOA VARCHAR(4),
    NGAYNHANCHUC DATE,
);

-- Bảng GV_DT
CREATE TABLE GV_DT (
    MAGV CHAR(3),
    DIENTHOAI CHAR(10),
    PRIMARY KEY (MAGV, DIENTHOAI),
);

-- Bảng CONGVIEC
CREATE TABLE CONGVIEC (
    MADT CHAR(3),
    SOTT SMALLINT,
    TENCV NVARCHAR(24),
    NGAYBD DATE,
    NGAYKT DATE,
    PRIMARY KEY (MADT, SOTT),
);

-- Bảng THAMGIADT
CREATE TABLE THAMGIADT (
    MAGV CHAR(3),
    MADT CHAR(3),
    STT SMALLINT,
    PHUCAP DECIMAL(2, 1),
    KETQUA NVARCHAR(3),
    PRIMARY KEY (MAGV, MADT, STT),
);

-- Bảng NGUOITHAN
CREATE TABLE NGUOITHAN (
    MAGV CHAR(3),
    TEN NVARCHAR(6),
    NGSINH DATE,
    PHAI NVARCHAR(3),
    PRIMARY KEY (MAGV, TEN),
);

-- KHOA (TRUONGKHOA) -> GIAOVIEN (MAGV)
ALTER TABLE KHOA ADD CONSTRAINT FK_KHOA_GIAOVIEN FOREIGN KEY (TRUONGKHOA) REFERENCES GIAOVIEN (MAGV);

-- BOMON (MAKHOA) -> KHOA (MAKHOA)
ALTER TABLE BOMON ADD CONSTRAINT FK_BOMON_KHOA FOREIGN KEY (MAKHOA) REFERENCES KHOA(MAKHOA);

-- BOMON(TRUONGBM) -> GIAOVIEN(MAGV)
ALTER TABLE BOMON ADD CONSTRAINT FK_BOMON_GIAOVIEN FOREIGN KEY (TRUONGBM) REFERENCES GIAOVIEN(MAGV);

-- GIAOVIEN (MABM) -> BOMON (MABM)
ALTER TABLE GIAOVIEN ADD CONSTRAINT FK_GIAOVIEN_BOMON FOREIGN KEY (MABM) REFERENCES BOMON(MABM);

-- GIAOVIEN (GVQLCM) -> GIAOVIEN (MAGV)
ALTER TABLE GIAOVIEN ADD CONSTRAINT FK_GIAOVIEN_GIAOVIEN FOREIGN KEY (GVQLCM) REFERENCES GIAOVIEN(MAGV);

-- DETAI (MACD) -> CHUDE (MACD)
ALTER TABLE DETAI ADD CONSTRAINT FK_DETAI_CHUDE FOREIGN KEY (MACD) REFERENCES CHUDE(MACD);

-- DETAI (GVCNDT) -> GIAOVIEN (MAGV)
ALTER TABLE DETAI ADD CONSTRAINT FK_DETAI_GIAOVIEN FOREIGN KEY (GVCNDT) REFERENCES GIAOVIEN(MAGV);

-- GV_DT (MAGV) -> GIAOVIEN (MAGV)
ALTER TABLE GV_DT ADD CONSTRAINT FK_GV_DT_GIAOVIEN FOREIGN KEY (MAGV) REFERENCES GIAOVIEN(MAGV);

-- CONGVIEC (MADT) -> DETAI (MADT)
ALTER TABLE CONGVIEC ADD CONSTRAINT FK_CONGVIEC_DETAI FOREIGN KEY (MADT) REFERENCES DETAI(MADT);

-- THAMGIADT (MAGV) -> GIAOVIEN (MAGV)
ALTER TABLE THAMGIADT ADD CONSTRAINT FK_THAMGIADT_GIAOVIEN FOREIGN KEY (MAGV) REFERENCES GIAOVIEN(MAGV);

-- THAMGIADT (MADT) -> DETAI (MADT)  
ALTER TABLE THAMGIADT ADD CONSTRAINT FK_THAMGIADT_DETAI FOREIGN KEY (MADT) REFERENCES DETAI(MADT);

-- NGUOITHAN (MAGV) -> GIAOVIEN (MAGV)  
ALTER TABLE NGUOITHAN ADD CONSTRAINT FK_NGUOITHAN_GIAOVIEN FOREIGN KEY (MAGV) REFERENCES GIAOVIEN(MAGV);

-- Nhập liệu bảng KHOA 
INSERT INTO KHOA (MAKHOA, TENKHOA, NAMTL, PHONG, DIENTHOAI, TRUONGKHOA, NGAYNHANCHUC) VALUES
('CNTT', N'Công nghệ thông tin', 1995, 'B11', '0838123456', NULL, '2005-02-20'),
('HH', N'Hóa học', 1980, 'B41', '0838456456', NULL, '2001-10-15'),
('SH', N'Sinh học', 1980, 'B31', '0838454545', NULL, '2000-10-11'),
('VL', N'Vật lý', 1976, 'B21', '0838223223', NULL, '2003-09-18');

-- Nhập liệu bảng GIAOVIEN 
INSERT INTO GIAOVIEN (MAGV, HOTEN, LUONG, PHAI, NGSINH, DIACHI, GVQLCM, MABM) VALUES
('001', N'Nguyễn Hoài An', 2000.0, N'Nam', '1973-02-15', N'25/3 Lạc Long Quân, Q.10, TP HCM', NULL, NULL),
('002', N'Trần Trà Hương', 2500.0, N'Nữ', '1960-06-20', N'125 Trần Hưng Đạo, Q.1, TP HCM', NULL, NULL),
('003', N'Nguyễn Ngọc Ánh', 2200.0, N'Nữ', '1975-05-11', N'12/21 Võ Văn Ngân Thủ Đức, TP HCM', '002', NULL),
('004', N'Trương Nam Sơn', 2300.0, N'Nam', '1959-06-20', N'215 Lý Thường Kiệt, TP Biên Hòa', NULL, NULL),
('005', N'Lý Hoàng Hà', 2500.0, N'Nam', '1954-10-23', N'22/5 Nguyễn Xí, Q.Bình Thạnh, TP HCM', NULL, NULL),
('006', N'Trần Bạch Tuyết', 1500.0, N'Nữ', '1980-05-20', N'127 Hùng Vương, TP Mỹ Tho', '004', NULL),
('007', N'Nguyễn An Trung', 2100.0, N'Nam', '1976-06-05', N'234 3/2, TP Biên Hòa', NULL, NULL),
('008', N'Trần Trung Hiếu', 1800.0, N'Nam', '1977-08-06', N'22/11 Lý Thường Kiệt, TP Mỹ Tho', '007', NULL),
('009', N'Trần Hoàng Nam', 2000.0, N'Nam', '1975-11-22', N'234 Trần Não, An Phú, TP HCM', '001', NULL),
('010', N'Phạm Nam Thanh', 1500.0, N'Nam', '1980-12-12', N'221 Hùng Vương, Q.5, TP HCM', '007', NULL);

-- Nhập liệu bảng CHUDE 
INSERT INTO CHUDE (MACD, TENCD) VALUES
('NCPT', N'Nghiên cứu phát triển'),
('QLGD', N'Quản lý giáo dục'),
('UDCN', N'Ứng dụng công nghệ');

-- Nhập liệu bảng DETAI 
INSERT INTO DETAI (MADT, TENDT, CAPQL, KINHPHI, NGAYBD, NGAYKT, MACD, GVCNDT) VALUES
('001', N'HTTT quản lý các trường ĐH', N'ĐHQG', 20.0, '2007-10-20', '2008-10-20', 'QLGD', NULL),
('002', N'HTTT quản lý giáo vụ cho một Khoa', N'Trường', 20.0, '2000-10-12', '2001-10-12', 'QLGD', NULL),
('003', N'Nghiên cứu chế tạo tạo Nano Platin', N'ĐHQG', 300.0, '2008-05-15', '2010-05-15', 'NCPT', NULL),
('004', N'Tạo vật liệu sinh học bằng màng ối người', N'Nhà nước', 100.0, '2007-01-01', '2009-12-31', 'NCPT', NULL),
('005', N'Ứng dụng hóa học xanh', N'Trường', 200.00, '2003-10-10', '2004-12-10', 'UDCN', NULL),
('006', N'Nghiên cứu tế bào gốc', N'Nhà nước', 4000.0, '2006-10-20', '2009-10-20', 'NCPT', NULL),
('007', N'HTTT quản lý thư viện ở các trường ĐH', N'Trường', 20.0, '2009-05-10', '2010-05-10', 'QLGD', NULL);

-- Nhập liệu bảng BOMON 
INSERT INTO BOMON (MABM, TENBM, PHONG, DIENTHOAI, TRUONGBM, MAKHOA, NGAYNHANCHUC) VALUES
('CNTT', N'Công nghệ tri thức', 'B15', '0838126126', NULL, 'CNTT', NULL),
('HHC', N'Hóa hữu cơ', 'B44', '0382222222', NULL, 'HH', NULL),
('HL', N'Hóa lý', 'B42', '0838878787', NULL, 'HH', NULL),
('HPT', N'Hóa phân tích', 'B43', '0838777777', '007', 'HH', '2007-10-15'),
('HTTT', N'Hệ thống thông tin', 'B13', '0838125125', '002', 'CNTT', '2004-09-20'),
('MMT', N'Mạng máy tính', 'B16', '0838676767', '001', 'CNTT', '2005-05-15'),
('SH', N'Sinh hóa', 'B33', '0838898989', NULL, 'SH', NULL),
('VLĐT', N'Vật lý điện tử', 'B23', '0838234234', NULL, 'VL', NULL),
('VLƯD', N'Vật lý ứng dụng', 'B24', '0838454545', '005', 'VL', '2006-02-18'),
('VS', N'Vi sinh', 'B32', '0838909090', '004', 'SH', '2007-01-01');

-- Nhập liệu bảng GV_DT 
INSERT INTO GV_DT (MAGV, DIENTHOAI) VALUES
('001', '0838912112'),
('001', '0903123123'),
('002', '0913454545'),
('003', '0838121212'),
('003', '0903656565'),
('003', '0937125125'),
('006', '0937888888'),
('008', '0653717171'),
('008', '0913232323');

-- Nhập liệu bảng CONGVIEC
INSERT INTO CONGVIEC (MADT, SOTT, TENCV, NGAYBD, NGAYKT) VALUES
('001', 1, N'Khởi tạo và lập kế hoạch', '2007-10-20', '2008-12-20'),
('001', 2, N'Xác định yêu cầu', '2008-12-21', '2008-03-21'),
('001', 3, N'Phân tích hệ thống', '2008-03-22', '2008-05-22'),
('001', 4, N'Thiết kế hệ thống', '2008-05-23', '2008-06-23'),
('001', 5, N'Cài đặt thử nghiệm', '2008-06-24', '2008-10-20'),
('002', 1, N'Khởi tạo và lập kế hoạch', '2009-05-10', '2009-07-10'),
('002', 2, N'Xác định yêu cầu', '2009-07-11', '2009-10-11'),
('002', 3, N'Phân tích hệ thống', '2009-10-12', '2009-12-20'),
('002', 4, N'Thiết kế hệ thống', '2009-12-21', '2010-03-22'),
('002', 5, N'Cài đặt thử nghiệm', '2010-03-23', '2010-05-10'),
('006', 1, N'Lấy mẫu', '2006-10-20', '2007-02-20'),
('006', 2, N'Nuôi cấy', '2007-02-21', '2008-08-21');

-- Nhập liệu bảng THAMGIADT
INSERT INTO THAMGIADT (MAGV, MADT, STT, PHUCAP, KETQUA) VALUES
('001', '002', 1, 0.0, NULL),
('001', '002', 2, 2.0, NULL),
('002', '001', 4, 2.0, N'Đạt'),
('003', '001', 1, 1.0, N'Đạt'),
('003', '001', 2, 0.0, N'Đạt'),
('003', '001', 4, 1.0, N'Đạt'),
('003', '002', 2, 0.0, NULL),
('004', '006', 1, 0.0, N'Đạt'),
('004', '006', 2, 1.0, N'Đạt'),
('006', '006', 2, 1.5, N'Đạt'),
('009', '002', 3, 0.5, NULL),
('009', '002', 4, 1.5, NULL);

-- Nhập liệu bảng NGUOITHAN
INSERT INTO NGUOITHAN (MAGV, TEN, NGSINH, PHAI) VALUES
('001', N'Hùng', '1990-01-14', N'Nam'),
('001', N'Thủy', '1994-12-08', N'Nữ'),
('003', N'Hà', '1998-09-03', N'Nữ'),
('003', N'Thu', '1998-09-03', N'Nữ'),
('007', N'Mai', '2003-03-26', N'Nữ'),
('007', N'Vy', '2000-02-14', N'Nữ'),
('008', N'Nam', '1991-05-06', N'Nam'),
('009', N'An', '1996-08-19', N'Nam'),
('010', N'Nguyệt', '2006-01-14', N'Nữ');

-- Cập nhật dữ liệu bảng KHOA
UPDATE KHOA SET TRUONGKHOA = '002' WHERE MAKHOA = 'CNTT';
UPDATE KHOA SET TRUONGKHOA = '007' WHERE MAKHOA = 'HH';
UPDATE KHOA SET TRUONGKHOA = '004' WHERE MAKHOA = 'SH';
UPDATE KHOA SET TRUONGKHOA = '005' WHERE MAKHOA = 'VL';

-- Cập nhật dữ liệu bảng GIAOVIEN
UPDATE GIAOVIEN SET MABM = 'MMT' WHERE MAGV IN ('001', '009');
UPDATE GIAOVIEN SET MABM = 'HTTT' WHERE MAGV IN ('002', '003');
UPDATE GIAOVIEN SET MABM = 'VS' WHERE MAGV IN ('004', '006');
UPDATE GIAOVIEN SET MABM = 'VLĐT' WHERE MAGV = '005';
UPDATE GIAOVIEN SET MABM = 'HPT' WHERE MAGV IN ('007', '008', '010');

-- Cập nhật dữ liệu bảng DETAI
UPDATE DETAI SET GVCNDT = '002' WHERE MADT = '001';
UPDATE DETAI SET GVCNDT = '002' WHERE MADT = '002';
UPDATE DETAI SET GVCNDT = '005' WHERE MADT = '003';
UPDATE DETAI SET GVCNDT = '004' WHERE MADT = '004';
UPDATE DETAI SET GVCNDT = '007' WHERE MADT = '005';
UPDATE DETAI SET GVCNDT = '004' WHERE MADT = '006';
UPDATE DETAI SET GVCNDT = '001' WHERE MADT = '007';

SELECT * FROM KHOA
SELECT * FROM GIAOVIEN
SELECT * FROM CHUDE
SELECT * FROM DETAI
SELECT * FROM BOMON
SELECT * FROM GV_DT
SELECT * FROM CONGVIEC
SELECT * FROM THAMGIADT
SELECT * FROM NGUOITHAN

---- Xóa ràng buộc khóa ngoại
--ALTER TABLE KHOA DROP CONSTRAINT FK_KHOA_GIAOVIEN;
--ALTER TABLE BOMON DROP CONSTRAINT FK_BOMON_KHOA;
--ALTER TABLE BOMON DROP CONSTRAINT FK_BOMON_GIAOVIEN;
--ALTER TABLE GIAOVIEN DROP CONSTRAINT FK_GIAOVIEN_BOMON;
--ALTER TABLE GIAOVIEN DROP CONSTRAINT FK_GIAOVIEN_GIAOVIEN;
--ALTER TABLE DETAI DROP CONSTRAINT FK_DETAI_CHUDE;
--ALTER TABLE DETAI DROP CONSTRAINT FK_DETAI_GIAOVIEN;
--ALTER TABLE GV_DT DROP CONSTRAINT FK_GV_DT_GIAOVIEN;
--ALTER TABLE CONGVIEC DROP CONSTRAINT FK_CONGVIEC_DETAI;
--ALTER TABLE THAMGIADT DROP CONSTRAINT FK_THAMGIADT_GIAOVIEN;
--ALTER TABLE THAMGIADT DROP CONSTRAINT FK_THAMGIADT_DETAI;
--ALTER TABLE NGUOITHAN DROP CONSTRAINT FK_NGUOITHAN_GIAOVIEN;

---- Xóa bảng theo thứ tự tránh lỗi ràng buộc
--DROP TABLE GV_DT;
--DROP TABLE THAMGIADT;
--DROP TABLE CONGVIEC;
--DROP TABLE NGUOITHAN;
--DROP TABLE DETAI;
--DROP TABLE CHUDE;
--DROP TABLE GIAOVIEN;
--DROP TABLE BOMON;
--DROP TABLE KHOA;

--Yêu cầu 1
---Đếm số đề tài chủ nhiệm của mỗi bộ môn. Xuất mã, tên, số dtai của mỗi bm. 
select bm.MABM, bm.TENBM, count (dtai.MADT) as SoDeTaiCN
from BOMON bm 
join GIAOVIEN gv on gv.MABM = bm.MABM
join DETAI dtai on dtai.GVCNDT = gv.MAGV
group by bm.MABM, bm.TENBM

---Sắp xếp số đề tài giảm dần
select bm.MABM, bm.TENBM, count (dtai.MADT) as SoDeTaiCN
from BOMON bm 
join GIAOVIEN gv on gv.MABM = bm.MABM
join DETAI dtai on dtai.GVCNDT = gv.MAGV
group by bm.MABM, bm.TENBM
order by count (dtai.MADT) desc;

--Yêu cầu 2
---Đếm số đề tài chủ nhiệm của mỗi giảng viên
select gv.HOTEN, gv.MAGV, count(dtai.MADT) as SoLuongDeTai
from GIAOVIEN gv join DETAI dtai on gv.MAGV = dtai.GVCNDT
group by gv.HOTEN, gv.MAGV;

--Yêu cầu 3
---CHo biết magv, hoten giảng viên chủ nhiệm nhiều đề tài nhất
select gv.HOTEN, gv.MAGV, count(dtai.MADT) as SoLuongDeTai
from GIAOVIEN gv join DETAI dtai on gv.MAGV = dtai.GVCNDT
group by gv.HOTEN, gv.MAGV
having count(dtai.MADT) = (
  select top 1 count(dtai.MADT) as SoLuongDeTai
  from GIAOVIEN gv join DETAI dtai on gv.MAGV = dtai.GVCNDT
  group by gv.HOTEN, gv.MAGV
  order by SoLuongDeTai desc
)
--Yêu cầu 4
---Cho biết giảng viên nào chủ nhiệm hơn 3 đề tài cấp DHQG
select gv.*, count (dtai.CAPQL) as SoLuongDeTai from GIAOVIEN gv
join DETAI dtai on dtai.GVCNDT = gv.MAGV
where dtai.CAPQL = N'ĐHQG' 
group by gv.MAGV, gv.HOTEN, gv.LUONG, gv.PHAI, gv.NGSINH, gv.DIACHI, gv.GVQLCM, gv.MABM
having count (dtai.CAPQL) > 3

--Yêu cầu 5
---CHo biết giảng viên nữ nào của bm hệ thống ttin chưa chủ nhiệm đề tài
select gv.* from GIAOVIEN gv 
join BOMON bm on gv.MABM = bm.MABM 
where gv.PHAI = N'Nữ' and bm.TENBM = N'Hệ thống thông tin' 
except
select gv.* from GIAOVIEN gv 
join BOMON bm on gv.MABM = bm.MABM 
join DETAI dtai on gv.MAGV = dtai.GVCNDT
where gv.PHAI = N'Nữ' and bm.TENBM = N'Hệ thống thông tin'

--Yêu cầu 6
---Cho biết các đề tài được tất cả giảng viên BM hệ thống thông tin tham gia
select dtai.MADT, dtai.TENDT from DETAI dtai
where not exists (select gv.HOTEN from GIAOVIEN gv
                  join BOMON bm on gv.MABM = bm.MABM
                  where bm.TENBM = N'Hệ thống thông tin' 
      and 
      not exists (select tg.MAGV from THAMGIADT tg where 
	              tg.MADT = dtai.MADT and gv.MAGV = tg.MAGV	))

--Yêu cầu 7

---Cho biết các giảng viên bộ môn HTTT tham gia đề tài thuộc tất cả chủ đề
SELECT gv.MAGV, gv.HOTEN
FROM GIAOVIEN gv
JOIN THAMGIADT tgdt ON gv.MAGV = tgdt.MAGV
JOIN DeTai dt ON tgdt.MADT = dt.MADT
WHERE gv.MABM = 'HTTT'
GROUP BY gv.MaGV, gv.HoTen
HAVING COUNT(DISTINCT dt.MACD) = (SELECT COUNT(DISTINCT MACD) FROM DETAI);
