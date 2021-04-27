Create Database library;
Use library;

-- 创建 book 表
Create Table book(
    id char(8) , 
    name varchar(20) NOT NULL, 
    author varchar(10), 
    price float, 
    status int DEFAULT 0,

    Constraint PK_Book Primary Key (id),
    Constraint CK_status Check (status = 1 or status = 0)
);

-- 创建 reader 表
Create Table reader(
    id char(8), 
    name varchar(10), 
    age int,
    address varchar(20),

    Constraint PK_Reader Primary Key (id)
);

-- 创建 borrow 表
Create Table borrow(
    book_id char(8),
    reader_id char(8), 
    borrow_date date, 
    return_date date,

    Constraint FK_Borrow_book_id Foreign Key (book_id) References Book(id),
    Constraint PK_Book Primary Key (book_id, reader_id),
    Constraint FK_Borrow_reader_id Foreign Key (reader_id) References Reader(id)
);


-- 验证实体完整性
insert into borrow value('b100','r1', now(), null);

-- 验证参照完整性
insert into borrow value('b100','r1', now(), null);

-- 验证自定义完整性
---- 状态 status 只能为 0 或 1
select * from book where status != 0 and status != 1;

-- 检索读者Rose的读者号和地址
select id, address from reader where name = 'Rose';

-- 检索读者Rose所借阅读书(包括已还和未还图书的图书名和借期)
select book.name, borrow.borrow_date from book, reader, borrow
where borrow.book_id = book.id and borrow.reader_id = reader.id
    and reader.name = 'Rose';

-- 检索未借阅图书的读者姓名
select reader.name from reader
where reader.id not in (
    select distinct reader_id from borrow
);

-- 检索Ullman所写的书的书名和单价
select name, price from book where author = 'Ullman';

-- 检索读者“李林”借阅未还的图书的图书号和书名
select book.name, book.id from book, reader, borrow
where book.id = borrow.book_id and reader.id = borrow.reader_id
    and reader.name = '李林' and borrow.return_date is null;

-- 检索借阅图书数目超过3本的读者姓名
select reader.name from reader
where reader.id in (
    select reader.id from reader, borrow
        where reader.id = borrow.reader_id
            /* and borrow.return_date is null */
        group by borrow.reader_id
        having count(*) > 3
);

-- 检索没有借阅读者“李林”所借的任何一本书的读者姓名和读者号
select distinct reader.name, reader.id from reader, borrow
where not exists (
    select borrow.book_id from book, borrow
    where reader.id = borrow.reader_id
        and borrow.book_id in (
        select book_id from reader, borrow
        where reader.id = borrow.reader_id 
            and reader.name = '李林'
    )
);

-- 检索书名中包含“Oracle”的图书书名及图书号
select book.name, book.id from book
where book.name like '%Oracle%';

-- 创建一个读者借书信息的视图，该视图包含读者号、姓名、所借图书号、图书名和借期; 并使用该视图查询最近一年所有读者的读者号以及所借阅的不同图书数

-- create the view
drop table reader_borrow_view;
create view reader_borrow_view as (
    select reader.id as rid, reader.name as rname, 
        book.id as bid, book.name as bname, 
        borrow.borrow_date as borrow_date
    from book, reader, borrow
    where reader.id = borrow.reader_id and book.id = borrow.book_id
);

-- query
select rid, count(distinct bid) as borrow_count
from reader_borrow_view
where timestampdiff(year, borrow_date, now()) <= 1
group by rid;

-- 设计一个存储过程, 实现对 Book 表的 ID 的修改(本题要求不得使用外键定义时的on update cascade选项, 因为该选项不是所有 DBMS 都支持)

drop procedure update_book_id;
delimiter //
create procedure update_book_id(in old_id char(8), in new_id char(8))
begin
    declare s int default 0;
    declare continue handler for sqlexception set s = -1;
    declare continue handler for 1062 set s = 1;

    start transaction;

    insert into book (id, name, author, price, status)
        select new_id as id, name, author, price, status
        from book where id = old_id;
    update borrow set book_id = new_id where book_id = old_id;
    -- update book set id = new_id where id = old_id;
    delete from book where id = old_id;
    if s = 0 then
        select s as 'error_code', 'ok' as 'error_code';
        commit;
    elseif s = 1 then
        select s as 'error_code', '重复' as 'error_msg';
        rollback;
    else
        select s as 'error_code', 'unknown error' as 'error_code';
        rollback;
    end if;
end //
delimiter ;

-- 设计一个存储过程, 检查每本图书status是否正确, 并返回status不正确的图书数
drop procedure check_status;
delimiter //
create procedure check_status(out wrong_count int)
begin
    select count(*) into wrong_count from book
    where book.status = 0 and book.id in (
        select distinct book_id from borrow
        where return_date is null
    ) or book.status = 1 and book.id not in (
        select distinct book_id from borrow
        where return_date is null
    );

end //
delimiter ;

-- 测试样例
update book set status = 1 where id = 'b10' or id = 'b9';
update book set status = 0 where id = 'b7';
call check_status(@out); select @out;
update book set status = 0 where id = 'b10' or id = 'b9';
update book set status = 1 where id = 'b7';
call check_status(@out); select @out;

-- 设计触发器, 实现: 当一本书被借出时, 自动将Book表中相应图书的status修改为1; 当某本书被归还时, 自动将status改为0.
drop trigger update_status_when_borrow;
drop trigger update_status_when_return;
delimiter //
create trigger update_status_when_borrow after insert on borrow
for each row
begin
    update book set status = 1 where id = new.book_id;
end //

create trigger update_status_when_return after update on borrow
for each row
begin
    if new.return_date is not null then
        update book set status = 0 where id = new.book_id;
    else
        update book set status = 1 where id = new.book_id;
    end if;
end //
delimiter ;

-- 测试样例
select * from book where id = 'b10';
insert into borrow (book_id, reader_id, borrow_date)
values ('b10', 'r1', now());
select * from book where id = 'b10';
update borrow set return_date = now() where book_id = 'b10' and reader_id = 'r1';
select * from book where id = 'b10';
