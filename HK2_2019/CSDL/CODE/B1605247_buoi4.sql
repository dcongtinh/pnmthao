-- cau 1
select tua, kinhphi
from film
where kinhphi>=1000000

--cau 2
select tenloai
from LOAI l, LOAIPHIM lp, film f
where l.idLoai=lp.idLoai and lp.idFilm=f.idFilm and tua='IMPORTANCE OF BEING ERNEST'

--cau 3
select tua, kinhphi
from LOAI l, LOAIPHIM lp, film f
where l.idLoai=lp.idLoai and lp.idFilm=f.idFilm and tenloai='SCIENCE FICTION' and 800<=kinhphi and kinhphi<=1000000
order by kinhphi

-- cau 4
select ho+' '+ten [ho ten], thulao
from film f, DIENVIEN d, CANHAN c
where f.idFilm=d.idFilm and d.idCN=c.idCN and tua='MARK OF THE DEVIL'
order by thulao desc

-- cau 5
select ho+' '+ten [ho ten]
from film f, DIENVIEN d, CANHAN c
where f.idFilm=d.idFilm and f.nguoithuchien=c.idCN and tua='ONCE A THIEF'

--cau 6
select tua
from film
where tua like'%IMPOSSIBLE%'

-- cau 7
select f.idFilm, f.kinhphi, f.tua, f.nguoithuchien, ho+' '+ten [ho ten]
from film f, CANHAN c
where f.nguoithuchien=c.idCN and idFilm in(
	select d.idFilm
	from DIENVIEN d, CANHAN c
	where d.idCN=c.idCN and c.ho='WILDE' and c.ten='CORNEL')
	
--cau 8
select distinct tua
from film f, DIENVIEN d, CANHAN c
where f.idFilm=d.idFilm and f.nguoithuchien=c.idCN and c.ten='HUGH' and c.ho='WILSON'

--cau 9
select f.idFilm, nguoithuchien, ho+' '+ten [ho ten]
from film f, DIENVIEN d, CANHAN c
where f.idFilm=d.idFilm and d.idCN=c.idCN and f.nguoithuchien=c.idCN
order by nguoithuchien

--cau 10
select nguoithuchien, ho+' '+ten [ho ten], COUNT(*) as sobophim
from film f, DIENVIEN d, CANHAN c
where f.idFilm=d.idFilm and d.idCN=c.idCN and f.nguoithuchien=c.idCN
group by nguoithuchien, ho+' '+ten 
having COUNT(*)>=10

--cau 11
select sum(thulao) as tongthulao
from DIENVIEN d, film f
where d.idFilm=f.idFilm and tua='TALE OF TWO CITIES' 

--cau 12
select lp.idLoai, COUNT(*) as sophim_moitheloai
from LOAIPHIM lp
group by lp.idLoai

--cau 13
select lp.idLoai,tenloai, COUNT(*) as sophim_moitheloai
from LOAIPHIM lp, LOAI l
where lp.idLoai=l.idLoai
group by lp.idLoai, tenloai
having COUNT(*) >= all
	(select COUNT(*) 
	 from LOAIPHIM lp
	 group by lp.idLoai)
	 
--cau 14
select nguoithuchien, AVG(kinhphi) as kinhphi_trungbinh
from film
group by nguoithuchien

--cau 15
select ho+' '+ten as hoten
from film f, CANHAN c
where f.nguoithuchien=c.idCN
group by ho+' '+ten
having COUNT(*)>=50

--cau 16
select ho+' '+ten as hoten, COUNT(*) as nhieu_phim_nhat
from film f, CANHAN c
where f.nguoithuchien=c.idCN
group by ho+' '+ten
having COUNT(*)>= all(
	select COUNT(*)
	from film f, CANHAN c
	where f.nguoithuchien=c.idCN
	group by ho+' '+ten)

--cau 17
select ho+' '+ten as hoten, COUNT(*)
from CANHAN c, DIENVIEN d
where d.idCN=c.idCN
group by ho+' '+ten
having COUNT(*)>=50

--cau 18
select ho+' '+ten as hoten, COUNT(*)
from CANHAN c, DIENVIEN d
where d.idCN=c.idCN
group by ho+' '+ten
having COUNT(*)>= all(
	select COUNT(*)
	from  CANHAN c, DIENVIEN d
	where d.idCN=c.idCN
	group by ho+' '+ten)

--cau 19
select tua, kinhphi
from film
where kinhphi=(
		select MAX(kinhphi)
		from film)
-----
select tua, kinhphi
from film
where kinhphi >= all(
		select kinhphi
		from film)
--cau 20
select tua, kinhphi
from film
where kinhphi=(
		select Min(kinhphi)
		from film)

--cau 21
--Cach hieu 1: tim phim co thu lao cao nhat tra cho mot dien vien nao do
select tua
from film f, DIENVIEN d
where f.idFilm=d.idFilm and thulao=( select MAX(thulao) from DIENVIEN)

--Cach hieu 2: voi moi bo phim cho biet thu lao cao nhat la dien vien nao
select tua, ho+' '+ten as hoten, thulao into thulao1
from film f, DIENVIEN d, CANHAN c
where f.idFilm=d.idFilm and d.idCN=c.idCN

select tua, Max(thulao) as thulao_max into thulao2
from thulao1
group by tua
order by tua

select t1.tua, hoten, t1.thulao
from thulao1 t1, thulao2 t2
where t1.tua=t2.tua and t1.thulao=t2.thulao_max
order by tua

--cau 22
select tua, kinhphi, sum(thulao) as tongthulao
from film f, DIENVIEN d
where f.idFilm=d.idFilm
group by tua, kinhphi

--cau 23
select ho+' '+ten, sum(thulao) as tongthulao, COUNT(*)as solanthamgiacuadienvien
from DIENVIEN d, CANHAN c
where d.idCN=c.idCN
group by ho+' '+ten
having SUM(thulao)>800000

--cau 24
select tenloai, avg(kinhphi) as tb_kinhphi
from film f, LOAI l, LOAIPHIM p
where f.idFilm=p.idFilm and p.idLoai=l.idLoai
group by tenloai
having AVG(kinhphi)>500000000

--cau 25
select ho+' '+ten [ho ten],sum(thulao) as tongthulao
from film f, DIENVIEN d, CANHAN c
where f.idFilm=d.idFilm and d.idCN=c.idCN and tua in(
	select tua
	from film f, DIENVIEN d, CANHAN c
	where f.idFilm=d.idFilm and d.idCN=c.idCN and c.ho='BALIN' and c.ten='MIREILLE')
group by ho+' '+ten

--cau 26
select c1.ho+' '+c1.ten [ho ten dien vien], c2.ho+' '+c2.ten [ho ten nguoi thuc hien]
from film f, DIENVIEN d, CANHAN c1, CANHAN c2
where f.idFilm=d.idFilm and d.idCN=c1.idCN and f.nguoithuchien=c2.idCN and tua='RESULTADO FINAL'

--cau 27
select ho+' '+ten as hoten
from DIENVIEN d, CANHAN c
where d.idCN=c.idCN and thulao= ( select MAX(thulao) from DIENVIEN)

--cau 28
select HO+' '+ten as hoten, sum(thulao) as tongthulao into A
from DIENVIEN d, CANHAN c
where d.idCN=c.idCN
group by HO+' '+ten

select hoten
from A
where tongthulao= (select MIN(tongthulao) from A)

--cau 29
select COUNT(*)
from (select distinct idCN 
	from DIENVIEN) tam
	
--cau 30
select COUNT(*)
from (select nguoithuchien
	from film) tam

--cau 31
select COUNT(*)
from(
	select nguoithuchien
	from film
	intersect
	select idCN
	from film f, DIENVIEN d
	where f.idFilm=d.idFilm) A
	
--cau 32
select COUNT(*)
from(
	select idCN
	from DIENVIEN 
	except
	select nguoithuchien
	from film) A

--cau 33
select COUNT(*)
from(
	select nguoithuchien
	from film
	except
	select idCN
	from DIENVIEN ) A


--cau 34
select COUNT(*)
from(
	select idcn
	from CANHAN
	except (select nguoithuchien
		from film
		union
		select idCN
		from DIENVIEN) ) A

--cau 35
select distinct d.idCN, HO+' '+ten [ho ten]
from DIENVIEN d, CANHAN c
where d.idCN=c.idCN and idFilm in (
	select idFilm
	from DIENVIEN d, CANHAN c
	where d.idCN=c.idCN and c.ho='LANCASTER' and c.ten='BURT')
	
--cau 36
select idFilm into S
from DIENVIEN d, CANHAN c
where d.idCN=c.idCN and c.ho='RIVA' and c.ten='EMMANUELLE'

select idCN, idFilm into R
from DIENVIEN

select distinct c.idCN, ho+' '+ten as hoten
from R r1, CANHAN c
where r1.idCN=c.idCN and c.ho<>'RIVA' and c.ten<>'EMMANUELLE'and not exists (
	select *
	from S
	where not exists (
		select *
		from R r2
		where r1.idCN=r2.idCN and r2.idFilm=s.idFilm)) 

--cau 37
select f.idFilm into T
from film f, CANHAN c
where f.nguoithuchien=c.idCN and c.ho='BIVEL'

select idCN, idFilm into U
from DIENVIEN

select idCN
from U u1
where not exists (
	select *
	from T
	where not exists (
		select *
		from U u2
		where u1.idCN=u2.idCN and u2.idFilm=T.idFilm))

