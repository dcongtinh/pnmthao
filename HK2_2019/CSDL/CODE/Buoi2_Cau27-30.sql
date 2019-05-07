-- Tim cac may co cai dat it nhat mot phan mem giong may p6
SELECT distinct C1.idMay
FROM Caidat C1
WHERE EXISTS
  (SELECT * FROM Caidat C2
   WHERE C1.idPM=C2.idPM AND C1.idMay<>C2.idMay AND C2.idMay='P6')
--Tim cac may co cai dat tat ca cac phan mem ma may p6 cai dat
SELECT distinct idMay
FROM Caidat A
where not exists (
    select * from Caidat B 
    where idMay='p6' and not exists (
         select * from Caidat C 
         where B.idPM=C.idPM and A.idMay=c.idMay)
     ) and a.idMay<>'p6'
--Tim cac may co cai dat dung cac phan mem ma may p6 da cai
select M1.idMay, idPM
from
	(SELECT distinct idMay
	 FROM Caidat A
	 where not exists (
		select * from Caidat B 
		where idMay='p6' and not exists (
			 select * from Caidat C 
			 where B.idPM=C.idPM and A.idMay=c.idMay)
		 ) and a.idMay<>'p6') M1,
	Caidat M2
where m1.idMay=m2.idMay
---
select M1.idMay, COUNT(*) 
from
	(SELECT distinct idMay
	 FROM Caidat A
	 where not exists (
		select * from Caidat B 
		where idMay='p6' and not exists (
			 select * from Caidat C 
			 where B.idPM=C.idPM and A.idMay=c.idMay)
		 ) and a.idMay<>'p6') M1,
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
		where idMay='p6' and not exists (
			 select * from Caidat C 
			 where B.idPM=C.idPM and A.idMay=c.idMay)
		 ) and a.idMay<>'p6') M1,
	Caidat M2
where m1.idMay=m2.idMay
group by m1.idMay
having COUNT(*)= (select COUNT(*) from Caidat where idMay='p6')

		 