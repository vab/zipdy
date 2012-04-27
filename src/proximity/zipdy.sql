-- --------------------------------------------------------------------------
-- sql.txt
--
-- This file is part of Zipdy.
--
-- Zipdy is public domain software.
-- --------------------------------------------------------------------------
--  This is a query which can pull records out of the address
--  table which are with in 5 miles of the 32605 zip code.
--
-- Example Query:
--
-- select * from addresses where addresses.zip IN (select zips_five.destination
-- from zips_five where zips_five.origin='32601');
--
--  This is a demonstrational address table.  Your address
--  records can take any form that you want.  You just need
--  to have a CHAR(5) zipcode for sub select equation.

-- create table addresses
-- (
--	name		VARCHAR(80) NOT NULL,
--	street		VARCHAR(60) NOT NULL,
--	street_two	VARCHAR(60),
--	city		VARCHAR(50) NOT NULL,
--	state		CHAR(2) NOT NULL,
--	zip		CHAR(5) NOT NULL,
--	zip_four	CHAR(4),
--	PRIMARY KEY(name)
--);


--  These are the zip code tables.  The pre calculated
--  text databases are loaded into these tables.

create table zips_five
(
	origin		CHAR(5) NOT NULL,
        destination	CHAR(5) NOT NULL
);
create index zips_five_idx on zips_five(origin);

create table zips_ten
(
        origin          CHAR(5) NOT NULL,
        destination     CHAR(5) NOT NULL
);
create index zips_ten_idx on zips_ten(origin);

create table zips_fifteen
(
        origin          CHAR(5) NOT NULL,
        destination     CHAR(5) NOT NULL
);
create index zips_fifteen_idx on zips_fifteen(origin);

create table zips_twenty
(
        origin          CHAR(5) NOT NULL,
        destination     CHAR(5) NOT NULL
);
create index zips_twenty_idx on zips_twenty(origin);

create table zips_twenty_five
(
        origin          CHAR(5) NOT NULL,
        destination     CHAR(5) NOT NULL
);
create index zips_twenty_five_idx on zips_twenty_five(origin);

create table zips_fifty
(
        origin          CHAR(5) NOT NULL,
        destination     CHAR(5) NOT NULL
);
create index zips_fifty_idx on zips_fifty(origin);

