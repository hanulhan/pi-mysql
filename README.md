# pi-mysql

sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libmysqlclient-dev

from: http://www.raspberry-projects.com/pi/programming-in-c/databases-programming-in-c/mysql/setup-mysql-c-access



MYSQL_TYPE_TINY
	C Variable: signed char
	SQL Type: TINYINT (-128 to 127)

MYSQL_TYPE_SHORT
	C Variable: short int (int16_t)
	SQL Type: SMALLINT (-32768 to 32767)

MYSQL_TYPE_LONG
	C Variable: int (int32_t)
	SQL Type: INT (-2147483648 to 2147483647)

MYSQL_TYPE_LONGLONG
	C Variable: long long int (int64_t)
	SQL Type: BIGINT (-9223372036854775808 to 9223372036854775807)

MYSQL_TYPE_FLOAT
	C Variable: float
	SQL Type: FLOAT

MYSQL_TYPE_DOUBLE
	C Variable: double
	SQL Type: DOUBLE

MYSQL_TYPE_TIME
	C Variable: MYSQL_TIME
	SQL Type: TIME

MYSQL_TYPE_DATE
	C Variable: MYSQL_TIME
	SQL Type: DATE

MYSQL_TYPE_DATETIME
	C Variable: MYSQL_TIME
	SQL Type: DATETIME

MYSQL_TYPE_TIMESTAMP
	C Variable: MYSQL_TIME
	SQL Type: TIMESTAMP

MYSQL_TYPE_STRING
	C Variable: char[]
	SQL Type: TEXT, CHAR, VARCHAR

MYSQL_TYPE_BLOB
	C Variable: char[]
	SQL Type: BLOB, BINARY, VARBINARY

MYSQL_TYPE_NULL
	C Variable: 
	SQL Type: NULL


good makefile stuff:
https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile


Try this
https://tangentsoft.com/mysqlpp/home