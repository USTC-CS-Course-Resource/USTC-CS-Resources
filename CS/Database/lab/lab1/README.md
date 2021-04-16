# Lab 01 -- SQL

## 表结构

设某图书馆数据库包含下面的基本表:

```sql
-- 图书
---- ID 为主键, 书名不能为空. status 为 1 表示借出, 为 0 表示在馆, 默认为 0
Book(ID char(8), name varchar(10), author varchar(10), price float, status int)

-- 读者
---- 读者号 ID 为主键
Reader(ID char(8), name varchar(10), age int, address varchar(20))

-- 借阅
---- Return_Date 为 NULL 表示未还, 
---- 主键为 (book_ID, Reader_ID), 
---- book_ID 为外键, 引用 Book 表的 ID
---- Reader_ID 为外键, 引用 Reader 的 ID
Borrow(book_ID char(8), Reader_ID char(8), Borrow_Date date, Return_Date date)
```

以下使用令人舒适的命名规则:

```sql
-- 图书
---- ID 为主键, 书名不能为空. status 为 1 表示借出, 为 0 表示在馆, 默认为 0
book(id char(8), name varchar(10), author varchar(10), price float, status int)

-- 读者
---- 读者号 ID 为主键
Reader(id char(8), name varchar(10), age int, address varchar(20))

-- 借阅
---- Return_Date 为 NULL 表示未还, 
---- 主键为 (book_ID, Reader_ID), 
---- book_ID 为外键, 引用 Book 表的 ID
---- Reader_ID 为外键, 引用 Reader 的 ID
Borrow(book_id char(8), reader_id char(8), borrow_date date, return_date date)
```

## 实验步骤

### 1.
**创建上述表, 并插入部分测试数据**

首先创建数据库
```sql
Create Database library;
Use library;
```

然后添加表

```sql
-- 创建 book 表
Create Table book(
    id char(8) , 
    name varchar(10) NOT NULL, 
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
```

插入部分数据
```sql
Insert Into book (id, name, author, price, status)
Values
('00000000', 'Dragon', 'Shirley', 999, 0),
('00000000', 'Olaf The Snowman', 'Hank', 666, 0)
```

### 2.
**设计例子，验证实体完整性、参照完整性、用户自定义完整性**

#### 验证实体完整性

应当满足组成主码的所有属性均不可取空值, 对于三个表, 主码分别如下:
|表名|主码|
|:-|:-|
|book|id|
|reader|id|
|borrow|(book_id,reader_id)|

故如要验证主码完整性, 只需:
```sql
select id from book where id is null;
select id from reader where id is null;
select book_id, reader_id from borrow 
where book_id is null or reader_id is null;
```
若返回均为空集, 则满足实体完整性

#### 验证参照完整性

应当满足参照关系 R 的任一外码值必须等于被参照关系 S 中所参照的候选码的某个值或者为空.

题目给出的数据库中有外键约束的只有 `borrow` 表中的 `book_id` 和 `reader_id`.
只需要验证:
```sql
-- check `book_id`
select book_id from borrow
where book_id not in (select id from book) 
    or book_id is null;
-- check `reader_id`
select reader_id from borrow
where reader_id not in (select id from reader) 
    or reader_id is null;
```
如果返回均是空集, 则说明满足参照完整性

#### 验证用户自定义完整性

包括:
- `book` 表中
  1. 书名 name 不能为空
  2. 状态 status 只能为 0 或 1

验证如下:
```sql
-- 书名 name 不能为空
select * from book where name is not null;
-- 状态 status 只能为 0 或 1
select * from book where status != 0 and status != 1;
```

如果返回均为空集, 则说明满足用户自定义完整性

### 3.
**用SQL语言完成下面小题, 并测试运行结果:**

#### (1)
**检索读者Rose的读者号和地址**;

```sql
select id, address from reader where name = 'Rose';
```
#### (2)
**检索读者Rose所借阅读书(包括已还和未还图书的图书名和借期)**;

```sql
select book.name, borrow.borrow_date from book, reader, borrow
where borrow.book_id = book.id and borrow.reader_id = reader.id
    and reader.name = 'Rose';
```

#### (3)
**检索未借阅图书的读者姓名**;

认为是: 当前没有正在借阅图书的读者(而非从未借过书的读者)
```sql
select reader.name from reader
where reader.id not in (
    select distinct reader_id from borrow
        where borrow.return_date is not null
);
```

#### (4)
**检索Ullman所写的书的书名和单价**;

```sql
select name, price from book where author = 'Ullman';
```

#### (5)
**检索读者“李林”借阅未还的图书的图书号和书名**;

```sql
select book.name, book.id from book, reader, borrow
where book.id = borrow.book_id and reader.id = borrow.reader_id
    and reader.name = '李林' and borrow.return_date is null;
```

#### (6)
**检索借阅图书数目超过3本的读者姓名**;

```sql
select reader.name from reader
where reader.id in (
    select reader.id from reader, borrow
        where reader.id = borrow.reader_id
            and borrow.return_date is null
        group by borrow.reader_id
        having count(*) > 3
);
```

#### (7)
**检索没有借阅读者“李林”所借的任何一本书的读者姓名和读者号**;

```sql
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
```

#### (8)
**检索书名中包含“Oracle”的图书书名及图书号**;
```sql
select book.name, book.id from book
where book.name like '%Oracle%';
```

#### (9)
**创建一个读者借书信息的视图，该视图包含读者号、姓名、所借图书号、图书名和借期; 并使用该视图查询最近一年所有读者的读者号以及所借阅的不同图书数**;

创建视图:
```sql
-- create the view
drop table reader_borrow_view;
create view reader_borrow_view as (
    select reader.id as rid, reader.name as rname, 
        book.id as bid, book.name as bname, 
        borrow.borrow_date as borrow_date
    from book, reader, borrow
    where reader.id = borrow.reader_id and book.id = borrow.book_id
);
```

查询
```sql
-- query
select rid, count(distinct bid) as borrow_count
from reader_borrow_view
where timestampdiff(day, borrow_date, now()) <= 366
group by rid;
```

### 4.
**设计一个存储过程, 实现对 Book 表的 ID 的修改(本题要求不得使用外键定义时的on update cascade选项, 因为该选项不是所有 DBMS 都支持)**

一种方法是先添加新的 `book` 条目, 修改好 `borrow` 的 `book_id` 后, 删除旧 `book` 条目:
```sql
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
```

### 5.
**设计一个存储过程, 检查每本图书status是否正确, 并返回status不正确的图书数**

```sql
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
```

为做测试, 可如下:
```sql
update book set status = 1 where id = 'b10' or id = 'b9';
update book set status = 0 where id = 'b7';
call check_status(@out); select @out;
update book set status = 0 where id = 'b10' or id = 'b9';
update book set status = 1 where id = 'b7';
call check_status(@out); select @out;
```

### 6.
**设计触发器, 实现: 当一本书被借出时, 自动将Book表中相应图书的status修改为1; 当某本书被归还时, 自动将status改为0.**

```sql
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
```

测试方法:
```sql
select * from book where id = 'b10';
insert into borrow (book_id, reader_id, borrow_date)
values ('b10', 'r1', now());
select * from book where id = 'b10';
update borrow set return_date = now() where book_id = 'b10' and reader_id = 'r1';
select * from book where id = 'b10';
```