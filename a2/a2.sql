--Q1
select distinct S.snum, S.sname \
from student S, mark m1, mark m2, department d \
where d.deptname = 'computer science' \
	and S.year = 2 \
	and S.snum = m1.snum \
	and S.snum = m2.snum \
	and m1.deptcode = d.deptcode \
	and m2.deptcode = d.deptcode \
	and m1.grade < 65 \
	and m2.grade < 65 \
	and (m1.term != m2.term or m1.cnum != m2.cnum)
--Q2
select distinct P.pnum, P.pname \
from professor P, class c \
where p.deptcode != 'PM' \
	and c.deptcode = 'CS' \
	and c.cnum = 245 \
	and c.pnum = P.pnum \
	and not exists ( \
		select distinct s.snum \
		from student s, mark m \
		where m.snum = s.snum \
			and m.deptcode = 'CS' \
			and m.cnum = 245 \
			and m.term = c.term \
			and m.section = c.section \
			and m.grade is not null \
	) \
	and not exists ( \
		select * \
		from class cpri \
		where cpri.deptcode = 'CS' \
			and cpri.cnum = 245 \
			and cpri.pnum = P.pnum \
			and cpri.term != c.term \
	)
--Q3
select distinct S.snum, S.sname, S.year \
from student S \
where S.snum in ( \
		select m.snum \
		from mark m \
		where m.deptcode = 'CS' \
			and m.cnum = 240 \
		order by grade desc \
		limit 3 \
	)
--Q4
select distinct S.snum, S.sname \
from student S \
where S.year > 2 \
    and not exists ( \
    	select * \
	    from mark m \
    	where m.snum = S.snum \
        	and m.deptcode = 'CS' \
	        and m.grade < 85 \
	) \
    and not exists  ( \
    	select * \
    	from mark m1, class c, professor p \
	    where p.deptcode != 'CS' \
	        and c.pnum = p.pnum \
    	    and m1.snum = S.snum \
        	and m1.cnum = c.cnum \
	        and m1.term = c.term \
    	    and m1.section = c.section \
    )
--Q5
select distinct D.deptcode \
from department D, professor p, class c \
where p.deptcode = D.deptcode \
	and c.pnum = p.pnum \
	and not exists ( \
		select distinct s.snum \
		from student s, mark m \
		where m.snum = s.snum \
			and m.deptcode = c.deptcode \
			and m.cnum = c.cnum \
			and m.term = c.term \
			and m.section = c.section \
			and m.grade is not null \
	) \
	and not exists ( \
		select * \
		from class cl \
		where cl.pnum = p.pnum \
			and cl.deptcode != p.deptcode \
			and cl.term = c.term \
	) \
order by deptcode
--Q6
select c1.deptcode, c1.cnum, c1.section, c1.term, mi1.grade, ma1.grade, p1.pnum, p1.pname, c2.deptcode, c2.cnum, c2.section, c2.term, mi2.grade, ma2.grade, p2.pnum, p2.pname \
from mark mi1, mark ma1, mark mi2, mark ma2, professor p1, professor p2, class c1, class c2 \
where p1.pnum != p2.pnum \
	and p1.pnum = c1.pnum \
    and p2.pnum = c2.pnum \
    and c1.deptcode = c2.deptcode \
    and c1.cnum = c2.cnum \
    and c1.term = c2.term \
    and mi1.grade in ( \
        select m.grade \
        from mark m \
        where m.deptcode = c1.deptcode \
            and m.cnum = c1.cnum \
            and m.term = c1.term \
            and m.section = c1.section \
        order by grade \
        limit 1 \
    ) \
    and mi2.grade in ( \
        select m.grade \
        from mark m \
        where m.deptcode = c2.deptcode \
            and m.cnum = c2.cnum \
            and m.term = c2.term \
            and m.section = c2.section \
        order by grade \
        limit 1 \
    ) \
    and ma1.grade in ( \
        select m.grade \
        from mark m \
        where m.deptcode = c1.deptcode \
            and m.cnum = c1.cnum \
            and m.term = c1.term \
            and m.section = c1.section \
        order by grade desc \
        limit 1 \
    ) \
    and ma2.grade in ( \
        select m.grade \
        from mark m \
        where m.deptcode = c2.deptcode \
            and m.cnum = c2.cnum \
            and m.term = c2.term \
            and m.section = c2.section \
        order by grade desc \
        limit 1 \
    )
--Q7
select p1.pnum, p1.pname, p2.pnum, p2.pname \
from professor p1, professor p2 \
where p1.pnum != p2.pnum \
		and not exists ( \
			select c1.pnum \
			from class c1 \
			where c1.pnum = p1.pnum \
				and not exists ( \
					select c2.pnum \
					from class c2 \
					where c2.pnum = p2.pnum \
						and c2.deptcode = c1.deptcode \
						and c2.cnum = c1.cnum \
						and c2.term = c1.term \
				) \
		)
--Q8
with \
	countEnroll(cnum, ne) as ( \
		select e.cnum, count(*) as ne \
		from enrollment e \
		group by e.cnum \
	), \
	low3(ne) as ( \
		select distinct ne \
		from countEnroll \
		order by ne \
		limit 3 \
	) \
select ce.cnum, ce.ne \
from countEnroll ce, low3 l3 \
where ce.ne = l3.ne
--Q9
with \
	num_pm_profs(num) as ( \
		select count(p.pnum) as num \
		from professor p \
		where p.deptcode = 'PM' \
	), \
	num_lazy_profs(num) as ( \
		select count(distinct p.pnum) as num \
		from professor p \
		where p.deptcode = 'PM' \
			and not exists ( \
				select * \
				from class c1, class c2 \
				where c1.pnum = p.pnum \
					and c2.pnum = p.pnum \
					and c1.term = c2.term \
			) \
	) \
select 100 * a.num / b.num as percentage \
from num_lazy_profs a, num_pm_profs b \
where b.num != 0	 
