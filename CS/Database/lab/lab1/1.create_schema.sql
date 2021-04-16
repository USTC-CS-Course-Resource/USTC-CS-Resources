-- create and use library
drop database library;
create database library;
use library;

-- 创建 book 表
CREATE TABLE book (
    id CHAR(8),
    name VARCHAR(20) NOT NULL,
    author VARCHAR(10),
    price FLOAT,
    status INT DEFAULT 0,
    CONSTRAINT PK_Book PRIMARY KEY (id),
    CONSTRAINT CK_status CHECK (status = 1 OR status = 0)
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
