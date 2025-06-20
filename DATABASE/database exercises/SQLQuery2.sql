﻿GO 
use lession1
GO

CREATE TABLE BOMON
(
  MaBM CHAR(4),
  TenBM NVARCHAR(50) NOT NULL,
  TruongBM CHAR(4),
  CONSTRAINT PK_MaBM PRIMARY KEY(MaBM),
)

CREATE TABLE GIANGVIEN
(
  MaGV CHAR(4),
  HoTen NVARCHAR(50),
  GioiTinh NVARCHAR (3) CHECK (GioiTinh in ('NAM', N'NỮ')),
  CMND CHAR (12) UNIQUE,
  MaBM CHAR(4),
  CONSTRAINT PK_MaGV PRIMARY KEY (MaGV),
)

DROP TABLE BOMON
DROP TABLE GIANGVIEN

--BOMON(TruongBM) -> GIANGVIEN(MaGV)
ALTER TABLE BOMON ADD CONSTRAINT FK_BM_GV FOREIGN KEY (TruongBM) REFERENCES GIANGVIEN(MaGV)
ALTER TABLE BOMON DROP CONSTRAINT PK_MaBM
ALTER TABLE BOMON DROP CONSTRAINT FK_BM_GV 

--GIANGVIEN(MaBM) -> BOMON(MaBM)

ALTER TABLE GIANGVIEN ADD CONSTRAINT FK_GV_BM FOREIGN KEY (MaBM) REFERENCES BOMON(MaBM)
ALTER TABLE GIANGVIEN DROP CONSTRAINT PK_MaGV
ALTER TABLE GIANGVIEN DROP CONSTRAINT FK_GV_BM 


INSERT INTO BOMON VALUES
('CNPM', N'Công nghệ phần mềm', NULL),
('KHMT', N'kHOA HỌC MÁY TÍNH', NULL)

SELECT * FROM BOMON

INSERT INTO GIANGVIEN (MaGV, HoTen, MaBM) VALUES
('GV02', N'NGUYỄN VĂN A','KHMT')

SELECT * FROM GIANGVIEN

ALTER TABLE BOMON ADD NGAYNHANCHUC DATETIME
ALTER TABLE GIANGVIEN ALTER COLUMN GioiTinh NVARCHAR(8)

SELECT * FROM GIANGVIEN WHERE MaBM = 'CNPM' ORDER BY MaBM ASC
