/*
 *  A libESMTP Example Application.
 *  Copyright (C) 2001,2002  Brian Stafford <brian@stafford.uklinux.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation; either version 2 of the License,
 *  or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* This program accepts a single file argument followed by a list of
   recipients.  The file is mailed to each of the recipients.

   Error checking is minimal to non-existent, this is just a quick
   and dirty program to give a feel for using libESMTP.
 */


#define UNUSED(x) (void)(x)
#include "pi-mysql.h"


#include <stdio.h>
#include <stdlib.h>


#include <mysql/mysql.h>

//*****************************************
//*****************************************
//********** CONNECT TO DATABASE **********
//*****************************************
//*****************************************

void mysql_connect(void) {
    //initialize MYSQL object for connections
    mysql1 = mysql_init(NULL);

    if (mysql1 == NULL) {
        fprintf(stderr, "%s\n", mysql_error(mysql1));
        return;
    }

    //Connect to the database
    if (mysql_real_connect(mysql1, "localhost", DATABASE_USERNAME, DATABASE_PASSWORD, DATABASE_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(mysql1));
    } else {
        printf("Database connection successful.\n");
    }
}



//**********************************************
//**********************************************
//********** DISCONNECT FROM DATABASE **********
//**********************************************
//**********************************************

void mysql_disconnect(void) {
    mysql_close(mysql1);
    printf("Disconnected from database.\n");
}

void mysql_write(void) {

    MYSQL_STMT *sql_statement1;
    MYSQL_BIND sql_bind_parameters1[3];
    bool sql_error = false;


    //Setup to create query
    sql_statement1 = mysql_stmt_init(mysql1);
    if (!sql_statement1)
        sql_error = 1;


    //----- SET THE QUERY TEXT -----
#define SQL_QUERY_TEXT_1 "INSERT INTO \
								test_table(some_int_column, some_string_column, some_smallint_column) \
								VALUES(?,?,?)"
    if (mysql_stmt_prepare(sql_statement1, SQL_QUERY_TEXT_1, strlen(SQL_QUERY_TEXT_1)))
        sql_error = 1;

    //----- SET THE QUERY PARAMETER VALUES -----
    //If you want to know how many parameters are expected
    //int param_count = mysql_stmt_param_count(sql_statement1);

    //Set the parameter values
    memset(sql_bind_parameters1, 0, sizeof (sql_bind_parameters1)); //Reset the parameters memory to null

    //Integer
    int int_data = 10;
    sql_bind_parameters1[0].buffer_type = MYSQL_TYPE_LONG;
    sql_bind_parameters1[0].buffer = (char*) &int_data; //<Note: this is a pointer!
    sql_bind_parameters1[0].is_null = 0;
    sql_bind_parameters1[0].length = 0;

    //string
    char str_data[50] = "Hello";
    unsigned long str_length = strlen(str_data);
    sql_bind_parameters1[1].buffer_type = MYSQL_TYPE_STRING;
    sql_bind_parameters1[1].buffer = (char*) str_data;
    sql_bind_parameters1[1].buffer_length = sizeof (str_data);
    sql_bind_parameters1[1].is_null = 0;
    sql_bind_parameters1[1].length = &str_length; //<Note: this is a pointer!

    //smallint
    short small_data;
    my_bool is_null = 1; //We'll store this as null in this example
    sql_bind_parameters1[2].buffer_type = MYSQL_TYPE_SHORT;
    sql_bind_parameters1[2].buffer = (char*) &small_data; //<Note: this is a pointer!
    sql_bind_parameters1[2].is_null = &is_null; //<Note: this is a pointer!
    sql_bind_parameters1[2].length = 0;

    //Pointers are used in the bind parameters so that if you are say adding multiple rows you can use the same query setup with new values for each execute of it.

    //Bind the buffers
    if (mysql_stmt_bind_param(sql_statement1, sql_bind_parameters1))
        sql_error = 1;

    //----- EXECUTE THE QUERY ------
    if (!sql_error) {
        if (mysql_stmt_execute(sql_statement1))
            sql_error = 1;
    }

    //If you want to get the number of affected rows
    //my_ulonglong affected_rows = mysql_stmt_affected_rows(sql_statement1);
    //if (affected_rows != 1)
    //{
    //	do something
    //}

    //IF YOU WANT TO GET THE VALUE GENERATED FOR AN AUTO_INCREMENT COLUMN IN THE PREVIOUS INSERT/UPDATE STATEMENT
    //my_ulonglong sql_insert_id = mysql_stmt_insert_id(sql_statement1);

    //If you want to do the query again then change any values you want to change and call mysql_stmt_execute(sql_statement1) again

    //Close the statement
    if (sql_statement1) {
        if (mysql_stmt_close(sql_statement1))
            sql_error = 1;
    }

    Reading From The Database(safe parameters based query)


    MYSQL_STMT *sql_statement1;
    MYSQL_BIND sql_bind_parameters1[3];
    MYSQL_BIND sql_bind_results1[3];
    bool sql_error = false;



    //Setup to create query
    sql_statement1 = mysql_stmt_init(mysql1);
    if (!sql_statement1)
        sql_error = 1;

    //----- SET THE QUERY TEXT -----
#define SQL_QUERY_TEXT_1 "SELECT some_string_column FROM test_table WHERE some_int_column = ?"
    if (mysql_stmt_prepare(sql_statement1, SQL_QUERY_TEXT_1, strlen(SQL_QUERY_TEXT_1)))
        sql_error = 1;

    //----- SET THE QUERY PARAMETER VALUES -----
    //If you want to know how many parameters are expected
    //int param_count = mysql_stmt_param_count(sql_statement1);

    memset(sql_bind_parameters1, 0, sizeof (sql_bind_parameters1)); //Reset the parameters memory to null

    //Integer
    int int_data = 10;
    sql_bind_parameters1[0].buffer_type = MYSQL_TYPE_LONG;
    sql_bind_parameters1[0].buffer = (char*) &int_data; //<Note: this is a pointer!
    sql_bind_parameters1[0].length = 0;

    //Pointers are used in the bind parameters so that if you are say adding multiple rows you can use the same query setup with new values for each execute of it.

    //Bind the buffers
    if (mysql_stmt_bind_param(sql_statement1, sql_bind_parameters1))
        sql_error = 1;

    //----- SETUP THE RESULT BUFERS -----
    //Integer column
    //int int_data;
    //unsigned long int_length;
    //my_bool int_is_null;
    //my_bool int_error;
    //sql_bind_results1[0].buffer_type= MYSQL_TYPE_LONG;
    //sql_bind_results1[0].buffer = (char *)&int_data;
    //sql_bind_results1[0].is_null= &int_is_null;				//<This is filled by mysql_stmt_fetch, not specified by us
    //sql_bind_results1[0].length= &int_length;				//<This is filled by mysql_stmt_fetch, not specified by us
    //sql_bind_results1[0].error= &int_error;					//<This is filled by mysql_stmt_fetch, not specified by us

    //String column
    char str_data[50] = "";
    unsigned long str_length;
    my_bool str_is_null;
    my_bool str_error;
    sql_bind_results1[0].buffer_type = MYSQL_TYPE_STRING;
    sql_bind_results1[0].buffer = (char *) str_data;
    sql_bind_results1[0].buffer_length = sizeof (str_data);
    sql_bind_results1[0].is_null = &str_is_null;
    sql_bind_results1[0].length = &str_length;
    sql_bind_results1[0].error = &str_error;

    //Smallint column
    //short small_data;
    //unsigned long short_length;
    //my_bool short_is_null;
    //my_bool short_error;
    //sql_bind_results1[0].buffer_type= MYSQL_TYPE_SHORT;
    //sql_bind_results1[0].buffer= (char *)&small_data;
    //sql_bind_results1[0].is_null= &short_is_null;
    //sql_bind_results1[0].length= &short_length;
    //sql_bind_results1[0].error= &short_error;

    //Timestamp column
    //MYSQL_TIME ts;
    //unsigned long ts_length;
    //my_bool ts_is_null;
    //my_bool ts_error;
    //sql_bind_results1[0].buffer_type= MYSQL_TYPE_TIMESTAMP;
    //sql_bind_results1[0].buffer= (char *)&ts;
    //sql_bind_results1[0].is_null= &ts_is_null;
    //sql_bind_results1[0].length= &ts_length;
    //sql_bind_results1[0].error= &ts_error;

    if (mysql_stmt_bind_result(sql_statement1, sql_bind_results1))
        sql_error = 1;

    //----- EXECUTE THE QUERY ------
    if (!sql_error) {
        if (mysql_stmt_execute(sql_statement1))
            sql_error = 1;
    }

    if (!sql_error) {
        //OPTIONAL - If you want to fetch all results in 1 operation include this, to get each row from the server one by one comment out/discard:
        //if (mysql_stmt_store_result(sql_statement1))
        //{
        //	sql_error = 1;
        //	std::cout << "Database error: " << mysql_errno(mysql1) << " - " << mysql_error(mysql1) << std::endl;
        //}
        while (!mysql_stmt_fetch(sql_statement1)) {
            //Get next result
            string mystring = str_data;
        }
    }

    //Close the statement
    if (sql_statement1) {
        if (mysql_stmt_close(sql_statement1))
            sql_error = 1;

    }
}

void mysql_read_something(void) {
    MYSQL_STMT *sql_statement1;
    MYSQL_BIND sql_bind_parameters1[3];
    MYSQL_BIND sql_bind_results1[3];
    bool sql_error = false;



    //Setup to create query
    sql_statement1 = mysql_stmt_init(mysql1);
    if (!sql_statement1)
        sql_error = 1;

    //----- SET THE QUERY TEXT -----
#define SQL_QUERY_TEXT_1 "SELECT some_string_column FROM test_table WHERE some_int_column = ?"
    if (mysql_stmt_prepare(sql_statement1, SQL_QUERY_TEXT_1, strlen(SQL_QUERY_TEXT_1)))
        sql_error = 1;

    //----- SET THE QUERY PARAMETER VALUES -----
    //If you want to know how many parameters are expected
    //int param_count = mysql_stmt_param_count(sql_statement1);

    memset(sql_bind_parameters1, 0, sizeof (sql_bind_parameters1)); //Reset the parameters memory to null

    //Integer
    int int_data = 10;
    sql_bind_parameters1[0].buffer_type = MYSQL_TYPE_LONG;
    sql_bind_parameters1[0].buffer = (char*) &int_data; //<Note: this is a pointer!
    sql_bind_parameters1[0].length = 0;

    //Pointers are used in the bind parameters so that if you are say adding multiple rows you can use the same query setup with new values for each execute of it.

    //Bind the buffers
    if (mysql_stmt_bind_param(sql_statement1, sql_bind_parameters1))
        sql_error = 1;

    //----- SETUP THE RESULT BUFERS -----
    //Integer column
    //int int_data;
    //unsigned long int_length;
    //my_bool int_is_null;
    //my_bool int_error;
    //sql_bind_results1[0].buffer_type= MYSQL_TYPE_LONG;
    //sql_bind_results1[0].buffer = (char *)&int_data;
    //sql_bind_results1[0].is_null= &int_is_null;				//<This is filled by mysql_stmt_fetch, not specified by us
    //sql_bind_results1[0].length= &int_length;				//<This is filled by mysql_stmt_fetch, not specified by us
    //sql_bind_results1[0].error= &int_error;					//<This is filled by mysql_stmt_fetch, not specified by us

    //String column
    char str_data[50] = "";
    unsigned long str_length;
    my_bool str_is_null;
    my_bool str_error;
    sql_bind_results1[0].buffer_type = MYSQL_TYPE_STRING;
    sql_bind_results1[0].buffer = (char *) str_data;
    sql_bind_results1[0].buffer_length = sizeof (str_data);
    sql_bind_results1[0].is_null = &str_is_null;
    sql_bind_results1[0].length = &str_length;
    sql_bind_results1[0].error = &str_error;

    //Smallint column
    //short small_data;
    //unsigned long short_length;
    //my_bool short_is_null;
    //my_bool short_error;
    //sql_bind_results1[0].buffer_type= MYSQL_TYPE_SHORT;
    //sql_bind_results1[0].buffer= (char *)&small_data;
    //sql_bind_results1[0].is_null= &short_is_null;
    //sql_bind_results1[0].length= &short_length;
    //sql_bind_results1[0].error= &short_error;

    //Timestamp column
    //MYSQL_TIME ts;
    //unsigned long ts_length;
    //my_bool ts_is_null;
    //my_bool ts_error;
    //sql_bind_results1[0].buffer_type= MYSQL_TYPE_TIMESTAMP;
    //sql_bind_results1[0].buffer= (char *)&ts;
    //sql_bind_results1[0].is_null= &ts_is_null;
    //sql_bind_results1[0].length= &ts_length;
    //sql_bind_results1[0].error= &ts_error;

    if (mysql_stmt_bind_result(sql_statement1, sql_bind_results1))
        sql_error = 1;

    //----- EXECUTE THE QUERY ------
    if (!sql_error) {
        if (mysql_stmt_execute(sql_statement1))
            sql_error = 1;
    }

    if (!sql_error) {
        //OPTIONAL - If you want to fetch all results in 1 operation include this, to get each row from the server one by one comment out/discard:
        //if (mysql_stmt_store_result(sql_statement1))
        //{
        //	sql_error = 1;
        //	std::cout << "Database error: " << mysql_errno(mysql1) << " - " << mysql_error(mysql1) << std::endl;
        //}
        while (!mysql_stmt_fetch(sql_statement1)) {
            //Get next result
            string mystring = str_data;
        }
    }

    //Close the statement
    if (sql_statement1) {
        if (mysql_stmt_close(sql_statement1))
            sql_error = 1;
    }
}
