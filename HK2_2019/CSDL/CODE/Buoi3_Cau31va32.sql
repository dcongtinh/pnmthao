-- cau 32
select distinct m1.ND, d1.ten
from MUON m1, DOCGIA d1
where m1.ND=d1.ND and not exists (
	select * from MUON m2, DOCGIA d2
	where m2.ND=d2.ND and d2.ten='Carole' and not exists (
		select * from MUON m3, DOCGIA d3
		where d3.ND=m3.ND and d2.ND=d3.ND and d3.ten=d1.ten )
	) and d1.ten<>'Carole'
--Cau 31
select s.NS into S
from SACH s, TACPHAM t
where s.NT=t.NT and tua='Madame Bovary'

select distinct ho +' ' + ten as hoten, m.NS into R
from DOCGIA d, MUON m
where d.ND=m.ND

select * from R
Select * from S
