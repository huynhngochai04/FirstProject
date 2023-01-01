#include <iostream>
#include <mysql.h>
#include <string.h>
#include <cstring>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <sstream>
#include <mysqld_error.h>
//--------------------------------------------------------
void addObject();
void menuConsole();
void exitProgram();
void deleteObject();
void editObject();
void deleteConsole();

using namespace std;

int qstate;

char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "123456789";

void addObject()
{
    MYSQL* conn;

    int price_in = 0, price_out = 0, remaining = 0;
    string object_id;
    string object_name;

    bool ProgramIsOpened = true;
    int answer = 0;

    char* consult;
    char* sentence;
    string sentence_aux = ""; // Syntax to add data to the table

    //------------------------------------------------------------------------------------
    //          Connection

    if (!(conn = mysql_init(0)))
    {
        std::cout << "ERROR: MySQL Object could not be created.\n";
    }
    else
    {
        if (!mysql_real_connect(conn, HOST, USER, PASS, "salesmanagement", 4306, NULL, 0))
        {
            std::cout << "ERROR: Some database info is wrong or do not exits.\n";
            std::cout << mysql_error(conn) << endl;
        }
        else
        {
            std::cout << "Logged in." << endl << endl;
            while (ProgramIsOpened)
            {
                std::cout << "Nhap ma SP: ";
                cin >> object_id;

                cin.ignore();
                std::cout << "Nhap ten SP: ";
                getline(cin, object_name);

                std::cout << "Gia nhap vao: ";
                cin >> price_in;

                std::cout << "Gia ban ra: ";
                cin >> price_out;

                std::cout << "So luong: ";
                cin >> remaining;

                string insert_query1 = "INSERT INTO object(object_id,object_name,price_in,price_out,remaining) VALUES('" + object_id + "','" + object_name + "',";
                ostringstream convert;
                convert << price_in;
                string test = convert.str();
                insert_query1 = insert_query1 + "'" + test + "',";
                ostringstream convert1;
                convert1 << price_out;
                string test1 = convert1.str();
                insert_query1 = insert_query1 + "'" + test1 + "',";
                ostringstream convert2;
                convert2 << remaining;
                string test2 = convert2.str();
                insert_query1 = insert_query1 + "'" + test2 + "')";

                const char* q = insert_query1.c_str();

                qstate = mysql_query(conn, q);

                //make our attempt

                if (mysql_ping(conn))
                {
                    std::cout << "ERROR: Impossible to connect." << endl;
                    std::cout << mysql_error(conn) << endl;
                }

                if (!qstate)
                {
                    std::cout << "Info added correctly." << endl;
                }
                else
                {
                    std::cout << "ERROR: " << mysql_error(conn) << endl;
                    rewind(stdin);
                    cin.ignore();
                }
                mysql_store_result(conn);

                std::cout << endl << "Another?" << endl;
                std::cout << "[1]: YES" << endl;
                std::cout << "[0]: NO" << endl;
                std::cout << "Answer: ";
                cin >> answer;
                cin.ignore(100, '\n');
                if (answer == 0)
                {
                    ProgramIsOpened = false;
                }
                std::cout << endl;

            }
        }
    }
}

void exitProgram()
{
    std::cout << "** Bye (Coding by: HaiCodeDao) **\n";
}

void changeProgram()
{
    printf("** Ban muon thay doi du lieu nao **\n");
    printf("**     1: object_id              **\n");
    printf("**     2: object_name            **\n");
    printf("**     3: price_in               **\n");
    printf("**     4: price_out              **\n");
    printf("**     5: remaining              **\n");
    printf("**     6: nothing                **\n");
}

void editObject()
{
    MYSQL* conn;

    int price_in = 0, price_out = 0, remaining = 0;
    string object_id;
    string object_name;

    bool ProgramIsOpened = true;
    int answer = 0;

    char* consult;
    char* sentence;
    string sentence_aux = ""; // Syntax to add data to the table

    //------------------------------------------------------------------------------------
    //          Connection

    if (!(conn = mysql_init(0)))
    {
        std::cout << "ERROR: MySQL Object could not be created.\n";
    }
    else
    {
        if (!mysql_real_connect(conn, HOST, USER, PASS, "salesmanagement", 4306, NULL, 0))
        {
            std::cout << "ERROR: Some database info is wrong or do not exits.\n";
            std::cout << mysql_error(conn) << endl;
        }
        else
        {
            std::cout << "Logged in database, you can edit object.\n";
            int answer = 0;
            int qstate;
            while (1)
            {
                changeProgram();
                std::cout << "Your answer: ";
                cin >> answer;
                if (answer == 6)
                {
                    std::cout << "Noti: Ban da thoat chuong trinh sua san pham\n";
                    system("cls");
                    menuConsole();
                    break;
                }
                string find_id = "";
                std::cout << "Moi ban nhap vao ma san pham can thay doi: ";
                cin >> find_id;
                string update_query = "";
                if (answer == 5)
                {
                    std::cout << "Moi ban nhap so luong moi: ";
                    cin >> remaining;
                    ostringstream convert;
                    convert << remaining;
                    string ss = convert.str();
                    update_query = "UPDATE objcet SET remaining='"+ss+"' WHERE object_id='"+find_id+"'";
                }
                if (answer == 4)
                {
                    std::cout << "Moi ban nhap gia ban ra moi: ";
                    cin >> price_out;
                    ostringstream convert;
                    convert << price_out;
                    string ss = convert.str();
                    update_query = "UPDATE object SET price_out='" + ss +"' WHERE object_id='" + find_id + "'";
                }
                if (answer == 3)
                {
                    std::cout << "Moi ban nhap gia nhap vao moi: ";
                    cin >> price_in;
                    ostringstream convert;
                    convert << price_in;
                    string ss = convert.str();
                    update_query = "UPDATE object SET price_in='" + ss + "' WHERE object_id='" + find_id + "'";
                }
                if (answer == 2)
                {
                    std::cout << "Moi ban nhap vao ten san pham moi: ";
                    cin.ignore();
                    getline(cin, object_name);
                    update_query = "UPDATE object SET object_name='" + object_name + "' WHERE object_id='" + find_id + "'";
                }
                if (answer == 1)
                {
                    std::cout << "Moi ban nhap vao ma san pham moi: ";
                    cin >> object_id;
                    update_query = "UPDATE object SET object_id='" + object_id + "' WHERE object_id='" + find_id + "'";
                }
                const char* q = update_query.c_str();

                qstate = mysql_query(conn, q);

                if (!qstate)
                {
                    std::cout << "Your data has been changed in table.\n";
                }
                else
                {
                    std::cout << "Your data not founded.\n";
                }
            }
        }
    }
}

void deleteConsole()
{
    printf("** Ban muon xoa id khong **\n");
    printf("**    1: Co              **\n");
    printf("**    2: Khong           **\n");
}

void deleteObject()
{

    MYSQL* conn;

    int price_in = 0, price_out = 0, remaining = 0;
    string object_id;
    string object_name;

    bool ProgramIsOpened = true;
    int answer = 0;

    char* consult;
    char* sentence;
    string sentence_aux = ""; // Syntax to add data to the table

    //------------------------------------------------------------------------------------
    //          Connection

    if (!(conn = mysql_init(0)))
    {
        std::cout << "ERROR: MySQL Object could not be created.\n";
    }
    else
    {
        if (!mysql_real_connect(conn, HOST, USER, PASS, "salesmanagement", 4306, NULL, 0))
        {
            std::cout << "ERROR: Some database info is wrong or do not exits.\n";
            std::cout << mysql_error(conn) << endl;
        }
        else
        {
            std::cout << "Logged in database, you can delete object.\n";
            int answer = 0;
            int qstate;
            while (1)
            {
                deleteConsole();
                std::cout << "Your answer: ";
                cin >> answer;
                if (answer!=1)
                { 
                    break;
                }
                else
                {
                    std::cout << "Nhap vao ma id san pham ban muon xoa: ";
                    string find_id = "";
                    cin >> find_id;
                    string delete_query = "DELETE FROM object WHERE object_id='" + find_id + "'";
                    const char* q = delete_query.c_str();
                    qstate = mysql_query(conn, q);

                    if (!qstate)
                    {
                        std::cout << "Your choice has beeen done.\n";
                    }
                    else
                    {
                        std::cout << "Have something wrong, you can do it again.\n";
                    }
                }
            }
        } 
    }
}

void menuConsole()
{
    printf("*************************************\n");
    printf("**     QUAN LY BAN HANG            **\n");
    printf("**       1: Them san pham          **\n");
    printf("**       2: Sua san pham           **\n");
    printf("**       3: Xoa san pham           **\n");
    printf("**       4: Thoat                  **\n");
    printf("*************************************\n");
}
int main()
{
    int result = 0;
    while (1)
    {
        menuConsole();
        std::cout << "Your answer: ";
        cin >> result;
        if (result == 4)
        {
            exitProgram();
            return 0;
        }
        if (result == 1)
        {
            addObject();
        }
        if (result == 2)
        {
            editObject();
        }
        if (result == 3)
        {
            deleteObject();
        }
        system("cls");
    }
    std::cout << "Coding By: Hai Code Dao" << endl;
    return 0;
}