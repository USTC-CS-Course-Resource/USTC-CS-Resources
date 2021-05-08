/*==============================================================*/
/* DBMS name:      Sybase SQL Anywhere 12                       */
/* Created on:     2021/5/7 16:13:00                            */
/*==============================================================*/


if exists(select 1 from sys.sysforeignkey where role='FK_CHECKING_CHECKING_ACCOUNT') then
    alter table checking_account
       delete foreign key FK_CHECKING_CHECKING_ACCOUNT
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_CONTACTS_CONTACTS__CUSTOMER') then
    alter table contacts
       delete foreign key FK_CONTACTS_CONTACTS__CUSTOMER
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_DEPARTME_DEPARTMEN_BRANCH') then
    alter table department
       delete foreign key FK_DEPARTME_DEPARTMEN_BRANCH
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_DEPARTME_DEPARTMEN_DEPARTME') then
    alter table department_manager
       delete foreign key FK_DEPARTME_DEPARTMEN_DEPARTME
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_DEPARTME_MANAGER_STAFF') then
    alter table department_manager
       delete foreign key FK_DEPARTME_MANAGER_STAFF
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_HAVE_ACC_HAVE_ACCO_CUSTOMER') then
    alter table have_account
       delete foreign key FK_HAVE_ACC_HAVE_ACCO_CUSTOMER
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_HAVE_ACC_HAVE_ACCO_BRANCH') then
    alter table have_account
       delete foreign key FK_HAVE_ACC_HAVE_ACCO_BRANCH
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_HAVE_ACC_HAVE_ACCO_ACCOUNT') then
    alter table have_account
       delete foreign key FK_HAVE_ACC_HAVE_ACCO_ACCOUNT
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_LOAN_RELEASE_L_BRANCH') then
    alter table loan
       delete foreign key FK_LOAN_RELEASE_L_BRANCH
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_LOAN_REL_LOAN_RELA_CUSTOMER') then
    alter table loan_relation
       delete foreign key FK_LOAN_REL_LOAN_RELA_CUSTOMER
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_LOAN_REL_LOAN_RELA_LOAN') then
    alter table loan_relation
       delete foreign key FK_LOAN_REL_LOAN_RELA_LOAN
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_PAY_LOAN_PAY_LOAN__LOAN') then
    alter table pay_loan
       delete foreign key FK_PAY_LOAN_PAY_LOAN__LOAN
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

if exists(select 1 from sys.sysforeignkey where role='FK_STAFF_WORK_IN_DEPARTME') then
    alter table staff
       delete foreign key FK_STAFF_WORK_IN_DEPARTME
end if;

drop index if exists account.account_PK;

drop table if exists account;

drop index if exists branch.branch_PK;

drop table if exists branch;

drop index if exists checking_account.checking_account_PK;

drop table if exists checking_account;

drop index if exists contacts.contacts_relationship_FK;

drop index if exists contacts.contacts_PK;

drop table if exists contacts;

drop index if exists customer.customer_PK;

drop table if exists customer;

drop index if exists department.department_branch_FK;

drop index if exists department.department_PK;

drop table if exists department;

drop index if exists department_manager.manager_FK;

drop index if exists department_manager.department_manager_relation_FK;

drop index if exists department_manager.department_manager_PK;

drop table if exists department_manager;

drop index if exists have_account.have_account3_FK;

drop index if exists have_account.have_account2_FK;

drop index if exists have_account.have_account_FK;

drop index if exists have_account.have_account_PK;

drop table if exists have_account;

drop index if exists loan.release_loan_FK;

drop index if exists loan.loan_PK;

drop table if exists loan;

drop index if exists loan_relation.loan_relation2_FK;

drop index if exists loan_relation.loan_relation_FK;

drop index if exists loan_relation.loan_relation_PK;

drop table if exists loan_relation;

drop index if exists pay_loan.pay_loan_relation_FK;

drop index if exists pay_loan.pay_loan_PK;

drop table if exists pay_loan;

drop index if exists responsibility.responsibility2_FK;

drop index if exists responsibility.responsibility_FK;

drop index if exists responsibility.responsibility_PK;

drop table if exists responsibility;

drop index if exists saving_account.saving_account_PK;

drop table if exists saving_account;

drop index if exists staff.work_in_FK;

drop index if exists staff.hire_FK;

drop index if exists staff.staff_PK;

drop table if exists staff;

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
/* Table: contacts                                              */
/*==============================================================*/
create table contacts 
(
   cus_id               char(18)                       not null,
   name                 varchar(16)                    not null,
   phone                varchar(16)                    not null,
   email                varchar(32)                    not null,
   relation             varchar(16)                    not null,
   constraint PK_CONTACTS primary key (cus_id, name)
);

/*==============================================================*/
/* Index: contacts_PK                                           */
/*==============================================================*/
create unique index contacts_PK on contacts (
cus_id ASC,
name ASC
);

/*==============================================================*/
/* Index: contacts_relationship_FK                              */
/*==============================================================*/
create index contacts_relationship_FK on contacts (
cus_id ASC
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
   bra_name             varchar(16)                    not null,
   id                   varchar(16)                    not null,
   name                 varchar(16)                    not null,
   type                 varchar(16)                    not null,
   constraint PK_DEPARTMENT primary key (bra_name, id)
);

/*==============================================================*/
/* Index: department_PK                                         */
/*==============================================================*/
create unique index department_PK on department (
bra_name ASC,
id ASC
);

/*==============================================================*/
/* Index: department_branch_FK                                  */
/*==============================================================*/
create index department_branch_FK on department (
bra_name ASC
);

/*==============================================================*/
/* Table: department_manager                                    */
/*==============================================================*/
create table department_manager 
(
   dep_bra_name         varchar(16)                    not null,
   dep_id               varchar(16)                    not null,
   sta_id               char(18)                       not null,
   constraint PK_DEPARTMENT_MANAGER primary key clustered (dep_bra_name, dep_id, sta_id)
);

/*==============================================================*/
/* Index: department_manager_PK                                 */
/*==============================================================*/
create unique clustered index department_manager_PK on department_manager (
dep_bra_name ASC,
dep_id ASC,
sta_id ASC
);

/*==============================================================*/
/* Index: department_manager_relation_FK                        */
/*==============================================================*/
create index department_manager_relation_FK on department_manager (
dep_bra_name ASC,
dep_id ASC
);

/*==============================================================*/
/* Index: manager_FK                                            */
/*==============================================================*/
create index manager_FK on department_manager (
sta_id ASC
);

/*==============================================================*/
/* Table: have_account                                          */
/*==============================================================*/
create table have_account 
(
   cus_id               char(18)                       not null,
   bra_name             varchar(16)                    not null,
   acc_id               char(18)                       not null,
   latest_visit_date    date                           not null,
   type                 smallint                       not null,
   constraint PK_HAVE_ACCOUNT primary key clustered (cus_id, bra_name, acc_id)
);

comment on table have_account is 
'应当对 (用户id, 支行名, 账户类型) 有一个 unique 约束';

/*==============================================================*/
/* Index: have_account_PK                                       */
/*==============================================================*/
create unique clustered index have_account_PK on have_account (
cus_id ASC,
bra_name ASC,
acc_id ASC
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
bra_name ASC
);

/*==============================================================*/
/* Index: have_account3_FK                                      */
/*==============================================================*/
create index have_account3_FK on have_account (
acc_id ASC
);

/*==============================================================*/
/* Table: loan                                                  */
/*==============================================================*/
create table loan 
(
   bra_name             varchar(16)                    not null,
   id                   char(32)                       not null,
   amount               double                         not null,
   constraint PK_LOAN primary key (bra_name, id)
);

comment on table loan is 
'这里可能可以加入一个待付贷款额，但不小心可能造成数据不一致';

/*==============================================================*/
/* Index: loan_PK                                               */
/*==============================================================*/
create unique index loan_PK on loan (
bra_name ASC,
id ASC
);

/*==============================================================*/
/* Index: release_loan_FK                                       */
/*==============================================================*/
create index release_loan_FK on loan (
bra_name ASC
);

/*==============================================================*/
/* Table: loan_relation                                         */
/*==============================================================*/
create table loan_relation 
(
   cus_id               char(18)                       not null,
   loa_bra_name         varchar(16)                    not null,
   loa_id               char(32)                       not null,
   constraint PK_LOAN_RELATION primary key clustered (loa_bra_name, cus_id, loa_id)
);

/*==============================================================*/
/* Index: loan_relation_PK                                      */
/*==============================================================*/
create unique clustered index loan_relation_PK on loan_relation (
loa_bra_name ASC,
cus_id ASC,
loa_id ASC
);

/*==============================================================*/
/* Index: loan_relation_FK                                      */
/*==============================================================*/
create index loan_relation_FK on loan_relation (
cus_id ASC
);

/*==============================================================*/
/* Index: loan_relation2_FK                                     */
/*==============================================================*/
create index loan_relation2_FK on loan_relation (
loa_bra_name ASC,
loa_id ASC
);

/*==============================================================*/
/* Table: pay_loan                                              */
/*==============================================================*/
create table pay_loan 
(
   loa_bra_name         varchar(16)                    not null,
   loa_id               char(32)                       not null,
   id                   integer                        not null,
   amount               double                         not null,
   pay_date             timestamp                      not null,
   constraint PK_PAY_LOAN primary key (loa_bra_name, loa_id, id)
);

/*==============================================================*/
/* Index: pay_loan_PK                                           */
/*==============================================================*/
create unique index pay_loan_PK on pay_loan (
loa_bra_name ASC,
loa_id ASC,
id ASC
);

/*==============================================================*/
/* Index: pay_loan_relation_FK                                  */
/*==============================================================*/
create index pay_loan_relation_FK on pay_loan (
loa_bra_name ASC,
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
   dep_bra_name         varchar(16)                    not null,
   dep_id               varchar(16)                    not null,
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
/* Index: work_in_FK                                            */
/*==============================================================*/
create index work_in_FK on staff (
dep_bra_name ASC,
dep_id ASC
);

alter table checking_account
   add constraint FK_CHECKING_CHECKING_ACCOUNT foreign key (acc_id)
      references account (id)
      on update restrict
      on delete restrict;

alter table contacts
   add constraint FK_CONTACTS_CONTACTS__CUSTOMER foreign key (cus_id)
      references customer (id)
      on update restrict
      on delete restrict;

alter table department
   add constraint FK_DEPARTME_DEPARTMEN_BRANCH foreign key (bra_name)
      references branch (name)
      on update restrict
      on delete restrict;

alter table department_manager
   add constraint FK_DEPARTME_DEPARTMEN_DEPARTME foreign key (dep_bra_name, dep_id)
      references department (bra_name, id)
      on update restrict
      on delete restrict;

alter table department_manager
   add constraint FK_DEPARTME_MANAGER_STAFF foreign key (sta_id)
      references staff (id)
      on update restrict
      on delete restrict;

alter table have_account
   add constraint FK_HAVE_ACC_HAVE_ACCO_CUSTOMER foreign key (cus_id)
      references customer (id)
      on update restrict
      on delete restrict;

alter table have_account
   add constraint FK_HAVE_ACC_HAVE_ACCO_BRANCH foreign key (bra_name)
      references branch (name)
      on update restrict
      on delete restrict;

alter table have_account
   add constraint FK_HAVE_ACC_HAVE_ACCO_ACCOUNT foreign key (acc_id)
      references account (id)
      on update restrict
      on delete restrict;

alter table loan
   add constraint FK_LOAN_RELEASE_L_BRANCH foreign key (bra_name)
      references branch (name)
      on update restrict
      on delete restrict;

alter table loan_relation
   add constraint FK_LOAN_REL_LOAN_RELA_CUSTOMER foreign key (cus_id)
      references customer (id)
      on update restrict
      on delete restrict;

alter table loan_relation
   add constraint FK_LOAN_REL_LOAN_RELA_LOAN foreign key (loa_bra_name, loa_id)
      references loan (bra_name, id)
      on update restrict
      on delete restrict;

alter table pay_loan
   add constraint FK_PAY_LOAN_PAY_LOAN__LOAN foreign key (loa_bra_name, loa_id)
      references loan (bra_name, id)
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

alter table staff
   add constraint FK_STAFF_WORK_IN_DEPARTME foreign key (dep_bra_name, dep_id)
      references department (bra_name, id)
      on update restrict
      on delete restrict;

