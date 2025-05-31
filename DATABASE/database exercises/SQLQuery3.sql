GO
use lession2
GO
create table BoMon
(
	MaBM char(4) Primary key,
	TenBM nvarchar(50) NOT NULL,
	TruongBM char(4),
)

CREATE TABLE GiangVien
(
	MaGV CHAR(4),
	HoTen NVARCHAR(50),
	Phai NVARCHAR(3) CHECK (Phai in ('Nam', N'Nữ')),
	CMND CHAR(5) UNIQUE,
	MaBM char(4),
	CONSTRAINT PK_GiangVien PRIMARY KEY (MaGV),
)

DROP TABLE GiangVien
-- BoMon(TruongBM) -> GiangVien(MaGV)
ALTER TABLE BoMon ADD CONSTRAINT FK_BM_GV FOREIGN KEY (TruongBM) REFERENCES GiangVien(MaGV)
-- GiangVien(MaBM) -> BoMon(MaBM)
ALTER TABLE GiangVien ADD CONSTRAINT FK_GV_BM FOREIGN KEY (MaBM) REFERENCES BoMon(MaBM)

-- BoMon
INSERT INTO BoMon VALUES
('CNPM', N'Công nghệ phần mềm', NULL),
('KHMT', N'Khoa học máy tính', NULL)

-- GiangVien
INSERT INTO GiangVien (MaGV,HoTen,MaBM) VALUES
('GV02', N'abc', 'KHMT')

-- Update
UPDATE BoMon set TruongBM = 'GV02' WHERE MaBM = 'CNPM'

-- Alter
ALTER TABLE BoMon add NgayNhanChuc datetime
ALTER TABLE GiangVien alter COLUMN Phai NVARCHAR(8)

-- Show
SELECT * FROM GiangVien
SELECT * FROM BoMon
SELECT MaGV, HoTen FROM GiangVien WHERE MaBM = 'CNPM' ORDER BY MaBM ASC