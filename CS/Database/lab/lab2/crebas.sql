/*==============================================================*/
/* DBMS name:      Sybase SQL Anywhere 12                       */
/* Created on:     2021/5/2 14:40:06                            */
/*==============================================================*/


if exists(select 1 from sys.sysforeignkey where role='FK_CHECKING_CHECKING_ACCOUNT') then
    alter table checking_account
       delete foreign key FK_CHECKING_CHECKING_ACCOUNT
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_DEPARTME_DEPARTMEN_BRANCH') then
    alter table department
       delete foreign key FK_DEPARTME_DEPARTMEN_BRANCH
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_HAVE_ACC_HAVE_ACCO_CUSTOMER') then
    alter table have_account
       delete foreign key FK_HAVE_ACC_HAVE_ACCO_CUSTOMER
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_HAVE_ACC_HAVE_ACCO_SAVING_A') then
    alter table have_account
       delete foreign key FK_HAVE_ACC_HAVE_ACCO_SAVING_A
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_HAVE_ACC_HAVE_ACCO_BRANCH') then
    alter table have_account
       delete foreign key FK_HAVE_ACC_HAVE_ACCO_BRANCH
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_HAVE_ACC_HAVE_ACCO_CHECKING') then
    alter table have_account
       delete foreign key FK_HAVE_ACC_HAVE_ACCO_CHECKING
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_LOAN_BORROW_CUSTOMER') then
    alter table loan
       delete foreign key FK_LOAN_BORROW_CUSTOMER
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_PAY_LOAN_PAY_LOAN_BRANCH') then
    alter table pay_loan
       delete foreign key FK_PAY_LOAN_PAY_LOAN_BRANCH
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_PAY_LOAN_PAY_LOAN2_LOAN') then
    alter table pay_loan
       delete foreign key FK_PAY_LOAN_PAY_LOAN2_LOAN
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_RESPONSI_RESPONSIB_CUSTOMER') then
    alter table responsibility
       delete foreign key FK_RESPONSI_RESPONSIB_CUSTOMER
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_RESPONSI_RESPONSIB_STAFF') then
    alter table responsibility
       delete foreign key FK_RESPONSI_RESPONSIB_STAFF
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_SAVING_A_SAVING_ACCOUNT') then
    alter table saving_account
       delete foreign key FK_SAVING_A_SAVING_ACCOUNT
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_STAFF_HIRE_BRANCH') then
    alter table staff
       delete foreign key FK_STAFF_HIRE_BRANCH
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_WORK_IN_WORK_IN_STAFF') then
    alter table work_in
       delete foreign key FK_WORK_IN_WORK_IN_STAFF
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_WORK_IN_WORK_IN2_DEPARTME') then
    alter table work_in
       delete foreign key FK_WORK_IN_WORK_IN2_DEPARTME
end if;

drop index if exists account.account_PK;

drop table if exists account;

drop index if exists branch.branch_PK;

drop table if exists branch;

drop index if exists checking_account.checking_account_PK;

drop table if exists checking_account;

drop index if exists customer.customer_PK;

drop table if exists customer;

drop index if exists department.department_branch_FK;

drop index if exists department.department_PK;

drop table if exists department;

drop index if exists have_account.have_account4_FK;

drop index if exists have_account.have_account3_FK;

drop index if exists have_account.have_account2_FK;

drop index if exists have_account.have_account_FK;

drop index if exists have_account.have_account_PK;

drop table if exists have_account;

drop index if exists loan.borrow_FK;

drop index if exists loan.loan_PK;

drop table if exists loan;

drop index if exists pay_loan.pay_loan2_FK;

drop index if exists pay_loan.pay_loan_FK;

drop index if exists pay_loan.pay_loan_PK;

drop table if exists pay_loan;

drop index if exists responsibility.responsibility2_FK;

drop index if exists responsibility.responsibility_FK;

drop index if exists responsibility.responsibility_PK;

drop table if exists responsibility;

drop index if exists saving_account.saving_account_PK;

drop table if exists saving_account;

drop index if exists staff.hire_FK;

drop index if exists staff.staff_PK;

drop table if exists staff;

drop index if exists work_in.work_in2_FK;

drop index if exists work_in.work_in_FK;

drop index if exists work_in.work_in_PK;

drop table if exists work_in;

/*==============================================================*/
/* Table: account                                               */
/*==============================================================*/
create table account 
(
   id                   char(18)                       not null,
   balance              double                         not null,
   type                 smallint                       not null,
   open_account_date    date                           not null,
   constraint PK_ACCOUNT primary key (id)
);

comment on table account is 
'账户类型type: 0 表示储蓄账户, 1 表示支票账户';

/*==============================================================*/
/* Index: account_PK                                            */
/*==============================================================*/
create unique index account_PK on account (
id ASC
);

/*==============================================================*/
/* Table: branch                                                */
/*==============================================================*/
create table branch 
(
   name                 varchar(16)                    not null,
   city                 varchar(16)                    not null,
   constraint PK_BRANCH primary key (name)
);

/*==============================================================*/
/* Index: branch_PK                                             */
/*==============================================================*/
create unique index branch_PK on branch (
name ASC
);

/*==============================================================*/
/* Table: checking_account                                      */
/*==============================================================*/
create table checking_account 
(
   acc_id               char(18)                       not null,
   overdraft            double                         not null,
   constraint PK_CHECKING_ACCOUNT primary key clustered (acc_id)
);

/*==============================================================*/
/* Index: checking_account_PK                                   */
/*==============================================================*/
create unique clustered index checking_account_PK on checking_account (
acc_id ASC
);

/*==============================================================*/
/* Table: customer                                              */
/*==============================================================*/
create table customer 
(
   id                   char(18)                       not null,
   name                 varchar(16)                    not null,
   phone                varchar(16)                    not null,
   address              varchar(32)                    not null,
   contacts_name        varchar(16)                    not null,
   contacts_phone       varchar(16)                    not null,
   contacts_email       varchar(32)                    not null,
   contacts_relation    varchar(16)                    not null,
   constraint PK_CUSTOMER primary key (id)
);

/*==============================================================*/
/* Index: customer_PK                                           */
/*==============================================================*/
create unique index customer_PK on customer (
id ASC
);

/*==============================================================*/
/* Table: department                                            */
/*==============================================================*/
create table department 
(
   id                   varchar(16)                    not null,
   bra_name             varchar(16)                    not null,
   name                 varchar(16)                    not null,
   type                 varchar(16)                    not null,
   constraint PK_DEPARTMENT primary key (id)
);

/*==============================================================*/
/* Index: department_PK                                         */
/*==============================================================*/
create unique index department_PK on department (
id ASC
);

/*==============================================================*/
/* Index: department_branch_FK                                  */
/*==============================================================*/
create index department_branch_FK on department (
bra_name ASC
);

/*==============================================================*/
/* Table: have_account                                          */
/*==============================================================*/
create table have_account 
(
   cus_id               char(18)                       not null,
   sav_acc_id           char(18)                       not null,
   bra_name             varchar(16)                    not null,
   che_acc_id           char(18)                       not null,
   latest_visit_date    date                           not null,
   constraint PK_HAVE_ACCOUNT primary key clustered (cus_id, bra_name)
);

/*==============================================================*/
/* Index: have_account_PK                                       */
/*==============================================================*/
create unique clustered index have_account_PK on have_account (
cus_id ASC,
bra_name ASC
);

/*==============================================================*/
/* Index: have_account_FK                                       */
/*==============================================================*/
create index have_account_FK on have_account (
cus_id ASC
);

/*==============================================================*/
/* Index: have_account2_FK                                      */
/*==============================================================*/
create index have_account2_FK on have_account (
sav_acc_id ASC
);

/*==============================================================*/
/* Index: have_account3_FK                                      */
/*==============================================================*/
create index have_account3_FK on have_account (
bra_name ASC
);

/*==============================================================*/
/* Index: have_account4_FK                                      */
/*==============================================================*/
create index have_account4_FK on have_account (
che_acc_id ASC
);

/*==============================================================*/
/* Table: loan                                                  */
/*==============================================================*/
create table loan 
(
   id                   char(32)                       not null,
   cus_id               char(18)                       not null,
   amount               double                         not null,
   constraint PK_LOAN primary key (id)
);

comment on table loan is 
'这里可能可以加入一个待付贷款额，但不小心可能造成数据不一致';

/*==============================================================*/
/* Index: loan_PK                                               */
/*==============================================================*/
create unique index loan_PK on loan (
id ASC
);

/*==============================================================*/
/* Index: borrow_FK                                             */
/*==============================================================*/
create index borrow_FK on loan (
cus_id ASC
);

/*==============================================================*/
/* Table: pay_loan                                              */
/*==============================================================*/
create table pay_loan 
(
   bra_name             varchar(16)                    not null,
   loa_id               char(32)                       not null,
   amount               double                         not null,
   pay_date             date                           not null,
   constraint PK_PAY_LOAN primary key clustered (bra_name, loa_id)
);

/*==============================================================*/
/* Index: pay_loan_PK                                           */
/*==============================================================*/
create unique clustered index pay_loan_PK on pay_loan (
bra_name ASC,
loa_id ASC
);

/*==============================================================*/
/* Index: pay_loan_FK                                           */
/*==============================================================*/
create index pay_loan_FK on pay_loan (
bra_name ASC
);

/*==============================================================*/
/* Index: pay_loan2_FK                                          */
/*==============================================================*/
create index pay_loan2_FK on pay_loan (
loa_id ASC
);

/*==============================================================*/
/* Table: responsibility                                        */
/*==============================================================*/
create table responsibility 
(
   cus_id               char(18)                       not null,
   sta_id               char(18)                       not null,
   type                 integer                        not null,
   constraint PK_RESPONSIBILITY primary key clustered (cus_id, sta_id)
);

/*==============================================================*/
/* Index: responsibility_PK                                     */
/*==============================================================*/
create unique clustered index responsibility_PK on responsibility (
cus_id ASC,
sta_id ASC
);

/*==============================================================*/
/* Index: responsibility_FK                                     */
/*==============================================================*/
create index responsibility_FK on responsibility (
cus_id ASC
);

/*==============================================================*/
/* Index: responsibility2_FK                                    */
/*==============================================================*/
create index responsibility2_FK on responsibility (
sta_id ASC
);

/*==============================================================*/
/* Table: saving_account                                        */
/*==============================================================*/
create table saving_account 
(
   acc_id               char(18)                       not null,
   interest_rate        double                         not null,
   currency_type        varchar(16)                    not null,
   constraint PK_SAVING_ACCOUNT primary key clustered (acc_id)
);

/*==============================================================*/
/* Index: saving_account_PK                                     */
/*==============================================================*/
create unique clustered index saving_account_PK on saving_account (
acc_id ASC
);

/*==============================================================*/
/* Table: staff                                                 */
/*==============================================================*/
create table staff 
(
   id                   char(18)                       not null,
   bra_name             varchar(16)                    not null,
   name                 varchar(16)                    not null,
   phone                varchar(16)                    not null,
   address              varchar(32)                    not null,
   start_work_date      date                           not null,
   constraint PK_STAFF primary key (id)
);

/*==============================================================*/
/* Index: staff_PK                                              */
/*==============================================================*/
create unique index staff_PK on staff (
id ASC
);

/*==============================================================*/
/* Index: hire_FK                                               */
/*==============================================================*/
create index hire_FK on staff (
bra_name ASC
);

/*==============================================================*/
/* Table: work_in                                               */
/*==============================================================*/
create table work_in 
(
   sta_id               char(18)                       not null,
   dep_id               varchar(16)                    not null,
   is_manager           smallint                       not null,
   constraint PK_WORK_IN primary key clustered (sta_id, dep_id)
);

/*==============================================================*/
/* Index: work_in_PK                                            */
/*==============================================================*/
create unique clustered index work_in_PK on work_in (
sta_id ASC,
dep_id ASC
);

/*==============================================================*/
/* Index: work_in_FK                                            */
/*==============================================================*/
create index work_in_FK on work_in (
sta_id ASC
);

/*==============================================================*/
/* Index: work_in2_FK                                           */
/*==============================================================*/
create index work_in2_FK on work_in (
dep_id ASC
);

alter table checking_account
   add constraint FK_CHECKING_CHECKING_ACCOUNT foreign key (acc_id)
      references account (id)
      on update restrict
      on delete restrict;

alter table department
   add constraint FK_DEPARTME_DEPARTMEN_BRANCH foreign key (bra_name)
      references branch (name)
      on update restrict
      on delete restrict;

alter table have_account
   add constraint FK_HAVE_ACC_HAVE_ACCO_CUSTOMER foreign key (cus_id)
      references customer (id)
      on update restrict
      on delete restrict;

alter table have_account
   add constraint FK_HAVE_ACC_HAVE_ACCO_SAVING_A foreign key (sav_acc_id)
      references saving_account (acc_id)
      on update restrict
      on delete restrict;

alter table have_account
   add constraint FK_HAVE_ACC_HAVE_ACCO_BRANCH foreign key (bra_name)
      references branch (name)
      on update restrict
      on delete restrict;

alter table have_account
   add constraint FK_HAVE_ACC_HAVE_ACCO_CHECKING foreign key (che_acc_id)
      references checking_account (acc_id)
      on update restrict
      on delete restrict;

alter table loan
   add constraint FK_LOAN_BORROW_CUSTOMER foreign key (cus_id)
      references customer (id)
      on update restrict
      on delete restrict;

alter table pay_loan
   add constraint FK_PAY_LOAN_PAY_LOAN_BRANCH foreign key (bra_name)
      references branch (name)
      on update restrict
      on delete restrict;

alter table pay_loan
   add constraint FK_PAY_LOAN_PAY_LOAN2_LOAN foreign key (loa_id)
      references loan (id)
      on update restrict
      on delete restrict;

alter table responsibility
   add constraint FK_RESPONSI_RESPONSIB_CUSTOMER foreign key (cus_id)
      references customer (id)
      on update restrict
      on delete restrict;

alter table responsibility
   add constraint FK_RESPONSI_RESPONSIB_STAFF foreign key (sta_id)
      references staff (id)
      on update restrict
      on delete restrict;

alter table saving_account
   add constraint FK_SAVING_A_SAVING_ACCOUNT foreign key (acc_id)
      references account (id)
      on update restrict
      on delete restrict;

alter table staff
   add constraint FK_STAFF_HIRE_BRANCH foreign key (bra_name)
      references branch (name)
      on update restrict
      on delete restrict;

alter table work_in
   add constraint FK_WORK_IN_WORK_IN_STAFF foreign key (sta_id)
      references staff (id)
      on update restrict
      on delete restrict;

alter table work_in
   add constraint FK_WORK_IN_WORK_IN2_DEPARTME foreign key (dep_id)
      references department (id)
      on update restrict
      on delete restrict;

