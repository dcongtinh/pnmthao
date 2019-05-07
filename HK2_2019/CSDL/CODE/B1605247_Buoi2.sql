
--cau 1: Loại của máy 'p8'

select idloai 
from May 
where idMay='p8'

--cau 2: Tên của các phần mềm 'UNIX'

select tenPM 
from Phanmem 
where idloai='UNIX'

--cau 3: Tên phòng, địa chỉ IP phòng, mã phòng của các máy loại 'UNIX' hoặc 'PCWS'

select p.MP,tenphong, p.IP
from Phong p, May m
where p.MP=m.MP and (idloai='UNIX' or idloai='PCWS')

--cau 4: Tên phòng, địa chỉ IP phòng, mã phòng của các máy loại 'UNIX' hoặc 'PCWS' ở khu vực '130.120.80', sắp xếp kết quả tăng dần theo mã phòng

select distinct p.MP,tenphong, p.IP
from Phong p, May m
where p.MP=m.MP and (idloai='UNIX' or idloai='PCWS') and (m.IP='130.120.80')
order by p.MP asc --tang dan (giam desc)

--cau 5: Số các phần mềm được cài đặt trên máy 'p6'

select COUNT (*) as so_pm
from Caidat
where idMay='p6'

--cau 6: Số các máy đã cài phần mềm 'log1'

select COUNT (*) as so_may
from Caidat
where idPM='log1'

--cau 7: Tên và địa chỉ IP (ví dụ: 130.120.80.1) đầy đủ của các máy loại 'TX'
select tenmay,IP+'.'+cast(ad as varchar(3)) as diachi_ip -- ad kieu int nen dung cast de chuyen doi kdl phu hop 
from May
where idloai='TX'

--cau 8: Tính số phần mềm đã cài đặt trên mỗi máy

select idMay, COUNT (*) as so_pm
from Caidat
group by idMay

--cau 9: Tính số máy mỗi phòng

select MP, COUNT (*) as so_may
from May
group by MP

--cau 10: Tính số cài lần cài đặt của mỗi phần mềm trên các máy khác nhau
select idPM, COUNT (*) as so_lancai
from Caidat
group by idPM

--cau 11: Giá trung bình của các phần mềm UNIX 

select AVG (gia) as gia_tb
from Phanmem
where idloai='UNIX'

-- cau 12: Ngày mua phần mềm gần nhất
select MAX (ngaymua) as ngaygannhat
from Phanmem

-- cau 13:  Số máy có ít nhất 2 phần mềm

select idMay into tam
from Caidat
group by idMay  
having COUNT (*)>=2
--
select COUNT(*) so_may
from tam

-- cau 14:  Số máy có ít nhất 2 phần mềm, sử dụng một select con trong mệnh đề FROM

select COUNT(*) so_may 
from(
	select idMay 
	from Caidat
    group by idMay  
    having COUNT (*) >=2) a
      
--CAU 15-17 SD SELECT CON VA OUTER JOIN
--cau 15: Tìm các loại không thuộc loại máy

select *
from Loai l
where l.idloai not in(
	select m.idloai 
	from May m) -- dung phep toan tru
--
select l.idloai,tenloai
from Loai l left join May m on (l.idloai=m.idloai)
where m.idloai is null

--Cau 16. Cac loai thuoc ca hai loai may va loai phan mem

--Cach 1
(select idloai from May)intersect(select idloai from Phanmem)

--Cach 2
select idloai 
from Loai l 
where l.idloai in ((select m.idloai from May m) intersect (select p.idloai from Phanmem p))

--Cach 3
select idloai 
from Loai l
where l.idloai in ((select m.idloai from May m where m.idloai in (select p.idloai from Phanmem p)))
    
--Cac loai thuoc loai may va loai phan mem

--Cach 1
select * from Loai l
where l.idloai in ((select m.idloai from May m) union (select p.idloai from Phanmem p))

--Cach 2
(select idloai from May) union (select idloai from Phanmem)

--Cach 3
select distinct m.idloai loai_may,p.idloai loai_pm
from May m full join Phanmem p on (m.idloai=p.idloai)

--Cau 17: Tìm các loại máy không phải là loại phần mềm

select m.idloai, tenloai from May m, Loai l where m.idloai=l.idloai
except -- phep tru
select p.idloai, tenloai from Phanmem p, Loai l where p.idloai=l.idloai
--
select distinct m.idloai, tenloai
from May m, Loai l
where (m.idloai=l.idloai) and m.idloai not in (select p.idloai from Phanmem p)

--Cau 18-22 SU DUNG SELECT LONG NHAU
--cau 18:  Địa chỉ IP đầy đủ của các máy cài phần mềm 'log6'
select m.IP+'.'+cast(m.ad as varchar(3)) as diachi_ip
from May m, Caidat c
where (m.idMay=c.idMay) and c.idPM='log6'
--
select IP+'.'+cast(ad as varchar(3)) as diachi_ip
from May
where idMay in(
	select idMay 
	from Caidat 
	where idPM='log6')
--
select IP+'.'+cast(ad as varchar(3)) as diachi_ip
from May m inner join Caidat c on ((m.idMay=c.idMay)and c.idPM='log6')

--cau 19: Địa chỉ IP đầy đủ của các máy cài phần mềm tên 'Oracle 8'
--Cach 1
select IP+'.'+cast(ad as varchar(3)) as diachi_ip
from May 
where idMay in(
	select idMay 
	from Caidat 
	where idPM in(
		select idPM 
		from Phanmem 
		where tenPM='Oracle 8'))
---Cach 2
select IP+'.'+cast(ad as varchar(3)) as diachi_ip
from May
where idMay in(
	select idMay from (Caidat c inner join Phanmem p on (c.idPM=p.idPM and tenPM='Oracle 8')))
	
--cau 20: Tên của các khu vực có chính xác 3 máy loại 'TX'

select tenkhuvuc 
from Khuvuc
where IP in(
	select IP from May where idloai='TX'
	group by IP
	having COUNT(*)=3)
	 
--cau 21:  Tên phòng có ít nhất một máy cài phần mềm tên 'Oracle 6'
-- Cach 1
select tenphong 
from Phong 
where MP in(
	select MP 
	from May m, Caidat c, Phanmem p 
	where (m.idMay=c.idMay) and (c.idPM=p.idPM) and tenPM='Oracle 6')
--Cach 2
select tenphong 
from Phong 
where MP in(
	select MP 
	from (May m inner join Caidat c on (m.idMay=c.idMay)) inner join Phanmem p on (c.idPM=p.idPM and tenPM='Oracle 6'))

--cau 22:  Tên phần mềm được mua gần nhất (sử dụng câu 12)
--Cach 1
select tenPM 
from Phanmem 
where ngaymua=(select MAX (ngaymua)from Phanmem)
--Cach 2
select tenPM 
from Phanmem 
where ngaymua >= all
   (select ngaymua from Phanmem where ngaymua is not null)
--Cach 3
select tenPM 
from Phanmem p1, (select max(ngaymua) ngay from Phanmem) p2 
where p1.ngaymua=p2.ngay
---Cach 4
select tenPM 
from Phanmem p1 inner join (select max(ngaymua) ngay from Phanmem) p2 on p1.ngaymua=p2.ngay

--cau 27: Tên của máy có ít nhất một phần mềm chung với máy 'p6' → kq: p2, p8, p1

select distinct tenmay
from may m,Caidat c
where m.idMay=c.idMay and m.idmay <>'p6' and idPM in
	(select idpm
	from Caidat
	where idMay='p6')

--Cau 28: Tên của phần mềm PCNT có giá lớn hơn bất kỳ giá của một phần mềm UNIX nà

select tenPM 
from Phanmem
where idloai='PCNT' and gia>ANY(
	select gia 
	from Phanmem 
	where idloai='UNIX')
	
--Cau 29:  Tên của phần mềm UNIX có giá lớn hơn tất cả các giá của các phần mềm PCNT

select tenPM 
from Phanmem
where idloai='UNIX' and gia>ALL(
	select gia 
	from Phanmem 
	where idloai='PCNT')
	
--Cau 30: Tên của các máy có cùng phần mềm như máy 'p6' (có thể nhiều phần mềm hơn máy 'p6') → kq: p2, p8
select distinct idMay
from Caidat A
where not exists (
    select * from Caidat B 
    where idMay='p6' and not exists (
         select * from Caidat C 
         where B.idPM=C.idPM and A.idMay=C.idMay)
     ) and a.idMay<>'p6' 
     
--Cau 31:  Tên của các máy có chính xác các phần mềm như máy 'p2' → kq: p8
select M1.idMay, idPM
from
	(select distinct idMay
	 from Caidat A
	 where not exists (
		select * from Caidat B 
		where idMay='p2' and not exists (
			 select * from Caidat C 
			 where B.idPM=C.idPM and A.idMay=c.idMay)
		 ) and a.idMay<>'p2') M1,
	Caidat M2
where m1.idMay=m2.idMay

---
select M1.idMay, COUNT(*) 
from
	(SELECT distinct idMay
	 FROM Caidat A
	 where not exists (
		select * from Caidat B 
		where idMay='p2' and not exists (
			 select * from Caidat C 
			 where B.idPM=C.idPM and A.idMay=c.idMay)
		 ) and a.idMay<>'p2') M1,
	Caidat M2
where m1.idMay=m2.idMay
group by m1.idMay

--
select M1.idMay
from
	(SELECT distinct idMay
	 FROM Caidat A
	 where not exists (
		select * from Caidat B 
		where idMay='p2' and not exists (
			 select * from Caidat C 
			 where B.idPM=C.idPM and A.idMay=c.idMay)
		 ) and a.idMay<>'p2') M1,
	Caidat M2
where m1.idMay=m2.idMay
group by m1.idMay
having COUNT(*)= (select COUNT(*) from Caidat where idMay='p2')

		 


