/* Buoi 1- Ho va ten: Phan Nguyen Minh Thao
		   MSSV: B1605247
*/
CREATE DATABASE QLPHONGTN
USE QLPHONGTN

CREATE TABLE Khuvuc(
	IP varchar(10)PRIMARY KEY,
	tenKhuvuc varchar(30) NOT NULL,
	tang varchar(1)
);
CREATE TABLE Phong(
	MP varchar(3) PRIMARY KEY,
	tenphong varchar(10) NOT NULL,
	somay int,
	IP varchar(10) NOT NULL,
	FOREIGN KEY (IP) REFERENCES KHUVUC(IP)
);
CREATE TABLE Loai(
	idloai varchar(10) PRIMARY KEY,
	tenloai varchar(30) NOT NULL
);
CREATE TABLE May(
	idMay varchar(3) PRIMARY KEY,
	tenmay varchar(10) NOT NULL,
	IP varchar(10),
	ad int CHECK (ad<255 AND ad>0),
	idloai varchar(10) NOT NULL,
	FOREIGN KEY (idloai) REFERENCES Loai(idloai),
	MP varchar(3) NOT NULL,
	FOREIGN KEY (MP) REFERENCES Phong(MP)
);
--ALTER TABLE MAY ADD CONSTRAINT FK_MAY_PHONG FOREIGN KEY(MP) 
--REFERENCES PHONG(MP) ON UPDATE CASCADE

CREATE TABLE Phanmem(
	idPM varchar(4) PRIMARY KEY,
	tenPM varchar(30) NOT NULL,
	ngaymua date,
	version float,
	idloai varchar(10) NOT NULL,
	FOREIGN KEY (idloai) REFERENCES Loai(idloai),
	gia float CHECK (gia>=0)
);
CREATE TABLE Caidat(
	id int PRIMARY KEY,
	idMay varchar(3) NOT NULL,
	FOREIGN KEY (idMay) REFERENCES May(idMay),
	idPM varchar(4) NOT NULL,
	FOREIGN KEY (idPM) REFERENCES Phanmem(idPM),
	ngaycai date DEFAULT GETDATE()
);

INSERT Khuvuc (IP,tenkhuvuc) VALUES ('130.120.80','BrinRDC');
INSERT Khuvuc (IP,tenkhuvuc) VALUES ('130.120.81','Brintang1');
INSERT Khuvuc (IP,tenkhuvuc) VALUES ('130.120.82','Brintang2');
INSERT Khuvuc (IP,tenkhuvuc) VALUES ('130.120.83','Brintang3');

INSERT Phong VALUES ('s01','Salle1','3','130.120.80');
INSERT Phong VALUES ('s02','Salle2','2','130.120.80');
INSERT Phong VALUES ('s03','Salle3','2','130.120.80');
INSERT Phong VALUES ('s11','Salle11','2','130.120.81');
INSERT Phong VALUES ('s12','Salle12','1','130.120.81');
INSERT Phong VALUES ('s21','Salle21','2','130.120.82');
INSERT Phong VALUES ('s22','Salle22','0','130.120.83');
INSERT Phong VALUES ('s23','Salle23','0','130.120.83');

INSERT INTO Loai VALUES ('TX','TerminalX-Window');
INSERT INTO Loai VALUES ('UNIX','SYSTEM UNIX');
INSERT INTO Loai VALUES ('PCNT','PC WINDOWS NT');
INSERT INTO Loai VALUES ('PCWS','PC WINDOWS');
INSERT INTO Loai VALUES ('NC','NETWORK COMPUTER');
INSERT INTO Loai VALUES ('BeOS','Microsoft Windows');

INSERT INTO May VALUES ('p1','Poste1','130.120.80','01','TX','s01');
INSERT INTO May VALUES ('p2','Poste2','130.120.80','02','UNIX','s01');
INSERT INTO May VALUES ('p3','Poste3','130.120.80','03','TX','s01');
INSERT INTO May VALUES ('p4','Poste4','130.120.80','04','PCWS','s02');
INSERT INTO May VALUES ('p5','Poste5','130.120.80','05','PCWS','s02');
INSERT INTO May VALUES ('p6','Poste6','130.120.80','06','UNIX','s03');
INSERT INTO May VALUES ('p7','Poste7','130.120.80','07','TX','s03');
INSERT INTO May VALUES ('p8','Poste8','130.120.81','01','UNIX','s11');
INSERT INTO May VALUES ('p9','Poste9','130.120.81','02','TX','s11');
INSERT INTO May VALUES ('p10','Poste10','130.120.81','03','UNIX','s12');
INSERT INTO May VALUES ('p11','Poste11','130.120.82','01','PCNT','s21');
INSERT INTO May VALUES ('p12','Poste12','130.120.82','02','PCWS','s21');

INSERT INTO Phanmem VALUES ('log1','Oracle 6','1995-05-13','6.2','UNIX','3000');
INSERT INTO Phanmem VALUES ('log2','Oracle 8','1999-09-15','81','UNIX','5600');
INSERT INTO Phanmem VALUES ('log3','SQLServer','1998-04-12','7','PCNT','2700');
INSERT INTO Phanmem VALUES ('log4','FrontPage','1997-06-03','5','PCWS','500');
INSERT INTO Phanmem VALUES ('log5','WinDev','1997-05-12','5','PCWS','750');
INSERT INTO Phanmem(idPM, tenPM, version, idloai, gia) VALUES ('log6','SQL*Net','2.0','UNIX','500');
INSERT INTO Phanmem VALUES ('log7','Thao','2000-04-12','2','PCNT','810');
INSERT INTO Phanmem VALUES ('log8','DreamWeaver','2003-09-21','2.0','BeOS','1400');

INSERT INTO Caidat VALUES (1,'p2','log1','5/15/2003');
INSERT INTO Caidat VALUES (2,'p2','log2','9/17/2003');
INSERT INTO Caidat (id,idMay,idPM)VALUES (3,'p4','log5');
INSERT INTO Caidat VALUES (4,'p6','log6','2003-05-20');
INSERT INTO Caidat VALUES (5,'p6','log1','2003-05-20');
INSERT INTO Caidat VALUES (6,'p8','log2','2003-05-19');
INSERT INTO Caidat VALUES (7,'p8','log6','2003-05-20');
INSERT INTO Caidat VALUES (8,'p11','log3','2003-04-20');
INSERT INTO Caidat VALUES (9,'p12','log4','2003-04-20');
INSERT INTO Caidat VALUES (10,'p11','log7','2003-04-20');
INSERT INTO Caidat VALUES (11,'p7','log7','2002-04-01');

--Cau 3: Sửa đổi cột tang của bảng Khuvuc để có số tầng đúng. Nghĩa là 0 cho 130.120.80, 1 cho 130.120.81, 2 cho 130.120.82
UPDATE Khuvuc
SET tang=RIGHT(IP,1)

--Cau 4: Giảm 10% giá của các phần mềm kiểu 'PCNT'
SELECT * FROM PHANMEM
UPDATE PHANMEM
SET gia=90*gia/100
WHERE idloai='PCNT'

--Cau 5: Thêm cột nbLog (số phần mềm mỗi máy) kiểu SMALLINT vào trong bảng May và cột nbInstall
--(số lần cài đặt mỗi phần mềm) kiểu SMALLINT vào trong bảng Phầnmềm. Cập nhật 2 cột này
--những giá trị sau:

idPM nbInstall idM
alter table May add nbLog smallint
alter table Phanmem add nbInstall smallint
--
select * from May
update May
set nbLog=0
where idMay in ('p1','p3','p5','p9','p10')

update May
set nbLog=1
where idMay in ('p4','p7','p12')

update May
set nbLog=2
where idMay in ('p2','p6','p8','p11')

update Phanmem
set nbInstall=1
where idPM in ('log3','log4','log5')
update Phanmem
set nbInstall=2
where idPM in ('log1','log2','log6','log7','log8')

-- cau 6: Tạo bảng PhanmemUNIX(idPM, tenPM, ngaymua, version) có cấu kiểu dữ liệu tương tự như bảng Phanmem đã tạo
create table PhanmemUNIX(
	idPM varchar(4) NOT NULL ,
	tenPM varchar(30) NOT NULL,
	ngaymua date,
	version float,
);
--cau 7: Thêm Khóa chính idPM cho bảng PhanmemUNIX vừa tạo
ALTER TABLE PhanmemUNIX ADD CONSTRAINT PK_PhanmemUNIX PRIMARY KEY(idPM)

--cau 8: Thêm cột giá cho bảng vừa tạo
alter table PhanmemUNIX add gia float

--cau 9: Thay đổi kiểu cho cột version thành VARCHAR (15) cho bảng PhanmemUNIX vừa tạo
alter table PhanmemUNIX alter column version varchar(15)

--cau10: Thêm ràng buộc duy nhất cho cột tên phần mềm cho bảng PhanmemUNIX vừa tạo
alter table PhanmemUNIX add constraint uk_tenPM UNIQUE (tenPM)

--cau 11: Thêm dữ liệu cho bảng PhanmemUNIX bằng cách lấy dữ liệu từ bảng Phanmemselect * from Phanmem
select * from PhanmemUNIX
insert PhanmemUNIX
select idPM,tenPM,ngaymua,version,gia
from Phanmem

--cau 12: Xóa cột version khỏi bảng PhanmemUNIXalter table PhanmemUNIX drop column version

--cau 13: Xóa các phần mềm trong bảng phần mềm có giá lớn hơn 5000 ? Giải thích kết quả
delete from Phanmem
where gia>5000
select * from Phanmem
select * from Caidat
--GT: mau tin can xoa ben bang phan mem duoc cac mau tin bang cai dat tham chieu toi. (muon xoa thi dung delete cascase)

--cau 14:  Xóa các phần mềm trong bảng phanmemUNIX có giá lớn hơn 5000 ? Giải thích kết quả
delete from PhanmemUNIX
where gia>5000
--GT: bang doc lap khng co quan he vs bat ki bang nao

--cau 15: Xóa bảng Phanmem ? Giải thích kết quảdrop table Phanmem
--GT: no duoc tham chieu boi khoa ngoai bang cai dat (idPM)

--cau 16: Xóa bảng PhanmemUNIX ? Giải thích kết quả 
drop table PhanmemUNIX

--cau 17:  Xóa các cột nbLog và nbInstall
alter table May drop column nbLog
alter table Phanmem drop column nbInstall