-- cau 1
select NT,tua
from tacpham
where tacgia='Guy de Maupassant'

-- cau 2
select ten
from DOCGIA
where dchi='32 rue des Alouettes, 75003 Paris'

-- cau 3
select nxb
from TACPHAM t, SACH s
where t.NT=s.NT and t.tua like '%fleur%'

-- cau 4
select tua
from TACPHAM
where tua like 'Le %'

-- cau 5
select ten
from DOCGIA d, MUON m
where d.ND=m.ND and '9/15/2007'<=ngaymuon and ngaymuon<='09/20/2007' 

-- cau 6
select COUNT(*) as sotp_lib
from TACPHAM

-- cau 7
select tacgia, COUNT(*) as sotp
from TACPHAM
group by tacgia

-- cau 8

select COUNT(*) as sotg_2tp
from (select tacgia, COUNT(*) as sotp
	from TACPHAM
	group by tacgia
	having COUNT(*)>=2) A
	
-- cau 9
select tua, COUNT(*) as sosach_moitp
from SACH s, TACPHAM t
where s.NT=t.NT 
group by tua

-- cau 10
select tua, COUNT(*) as sosach_moitp into A
from SACH s, TACPHAM t
where s.NT=t.NT 
group by tua

select tua
from A
where sosach_moitp= (select MAX(sosach_moitp) from A)

----Cach 2
select tua, COUNT(*) as sosach_moitp
from SACH s, TACPHAM t
where s.NT=t.NT 
group by tua
having COUNT(*) >=all (
	select COUNT(*)
	from SACH s, TACPHAM t
	where s.NT=t.NT 
	group by tua)
	
-- cau 11
select nxb, COUNT(*) as sotp_nxb_nhieunhat
from SACH 
group by nxb
having COUNT(*)>=all( 
	select COUNT(*)
	from SACH 
	group by nxb)

-- cau 12
select distinct nxb
from TACPHAM t, SACH s
where t.NT=s.NT and tua='Germinal'

-- cau 13
select tua
from TACPHAM t , SACH s
where t.NT=s.NT
group by tua
having COUNT(*)>=2

-- cau 14
select ten
from DOCGIA d, MUON m, TACPHAM t, SACH s
where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS and tua='Poésie'

-- cau 15
select ten
from DOCGIA d, MUON m, TACPHAM t, SACH s
where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS and tua='Les Fleurs du mal'

-- cau 16
select YEAR(ngaymuon), ND, COUNT(*) as solanmuon 
from MUON
group by YEAR(ngaymuon), ND

-- cau 17
select ten, tua
from DOCGIA d, MUON m, TACPHAM t, SACH s
where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS and ngaytra is null

-- cau 18
select ten, tua
from DOCGIA d, MUON m, TACPHAM t, SACH s
where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS and ngaytra > hantra

-- cau 19
select ten, tua
from DOCGIA d, MUON m, TACPHAM t, SACH s
where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS and ngaytra < hantra

-- cau 20
select tua
from (
	select distinct tua, ten
	from DOCGIA d, MUON m, TACPHAM t, SACH s
	where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS	)a
group by tua
having COUNT(*) >= all (
	select COUNT(*)
	from (
			select distinct tua, ten
			from DOCGIA d, MUON m, TACPHAM t, SACH s
			where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS	)b
	group by tua)
	
-- cau 21
select tua
from (
	select distinct tua, ten
	from DOCGIA d, MUON m, TACPHAM t, SACH s
	where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS	)a
group by tua
having COUNT(*) <= all (
	select COUNT(*)
	from (
			select distinct tua, ten
			from DOCGIA d, MUON m, TACPHAM t, SACH s
			where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS	)b
	group by tua)

-- cau 22
select ten
from (
	select distinct ten, tua
	from DOCGIA d, MUON m, TACPHAM t, SACH s
	where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS	)a
group by ten
having COUNT(*) >= all (
	select COUNT(*)
	from (
			select distinct ten, tua
			from DOCGIA d, MUON m, TACPHAM t, SACH s
			where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS	)b
	group by ten)

--cau 23
select ten
from (
	select distinct ten, tua
	from DOCGIA d, MUON m, TACPHAM t, SACH s
	where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS	)a
group by ten
having COUNT(*) <= all (
	select COUNT(*)
	from (
			select distinct ten, tua
			from DOCGIA d, MUON m, TACPHAM t, SACH s
			where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS	)b
	group by ten)
	
-- cau 24
select ten, tacgia
from DOCGIA d, MUON m, TACPHAM t, SACH s
where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS and tacgia='Victor Hugo'

-- cau 25
select ten, tua
from DOCGIA d, MUON m, TACPHAM t, SACH s
where d.ND=m.ND and t.NT=s.NT and m.NS=s.NS and YEAR(ngaymuon)='2007'

-- cau 26
--Cach 1
select NT, NS into t1
from SACH

select distinct NS into t2
from MUON

select NT,tp.NS as tp_NS, s.NS as s_Ns into t3 
from tp_sach tp left join sach_muon s on (tp.NS=s.NS)

select nt into t4
from t3 where s_Ns is not null

select NT, COUNT(*) as sosach into t5
from t1
group by NT

select NT,COUNT(*) as sosach into t6
from t4
group by NT

select a.NT 
from (
	select t5.nt, t5.sosach ss1, t6.sosach ss2
	from t5 left join t6 on (t5.nt = t6.nt))a
where ss1>ss2 or (ss2 is null)

--Cach 2
select a.NT 
from (
	select t5.nt, t5.sosach ss1, t6.sosach ss2
	from 
	     (select NT, COUNT(*) as sosach
		  from
			   (select NT, NS 
			   from SACH) t1
		  group by NT) t5 left join 
				(select NT,COUNT(*) as sosach 
				 from 
					 (select nt 
					  from 
							(select NT,tp.NS as tp_NS, s.NS as s_Ns 
							 from tp_sach tp left join sach_muon s on (tp.NS=s.NS)) t3 
							 where s_Ns is not null) t4
							 group by NT) t6 on (t5.nt = t6.nt))a
where ss1>ss2 or (ss2 is null)

-- cau 27
select a.NT 
from (
	select t5.nt, t5.sosach ss1, t6.sosach ss2
	from 
	     (select NT, COUNT(*) as sosach
		  from
			   (select NT, NS 
			   from SACH) t1
		  group by NT) t5 left join 
				(select NT,COUNT(*) as sosach 
				 from 
					 (select nt 
					  from 
							(select NT,tp.NS as tp_NS, s.NS as s_Ns 
							 from tp_sach tp left join sach_muon s on (tp.NS=s.NS)) t3 
							 where s_Ns is not null) t4
							 group by NT) t6 on (t5.nt = t6.nt))a
where ss1=ss2 

-- cau 28
select ND,ho+' '+ten [Ho ten]
from DOCGIA
where ND not in (select ND from MUON)

--cau 29
select distinct nxb
from sach 
where NS not in (select NS from MUON )

-- cau 30
select t.NT, tua
from sach s, TACPHAM t
where s.NT=t.NT
group by t.NT, tua
having COUNT(*)>=3

-- cau 31
select ns into T
from sach s, TACPHAM t
where s.NT=t.NT and tua='Madame Bovary'

select distinct m.ND, m.NS into U
from DOCGIA d, MUON m
where d.ND=m.ND

select distinct d.ND, ho+' '+ten [ho ten]
from U u1, DOCGIA d
where u1.ND=d.ND and not exists (
	select *
	from T t
	where not exists(
		select *
		from U u2
		where u1.ND=u2.ND and u2.NS=t.NS))
-- cau 32

select HO+' '+ten [ho ten], dchi, tel
from DOCGIA d, MUON m, (select ho+' '+ten [ho ten], NS 
						from MUON m, DOCGIA d
						where m.ND=d.ND and ho+' '+ten='Raymond Carole') b
where d.ND=m.ND and m.NS=b.NS and HO+' '+ten <> 'Raymond Carole'