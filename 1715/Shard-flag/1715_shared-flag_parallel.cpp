#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// Compare Memory Blocks
#include <string.h>


using namespace std;
int const n = 90; /* n-qubit state */
static uint64_t s[4];
static uint64_t x = 0xbf3749f5b97cd3b9; /* The state can be seeded with any value. */
double r; // random number

int correct(int (*Error_vector)[n], int a, int B);

int SQerror(int (*Record_error)[n], int a, double probability); // Single qubit error
int TQerror(int (*Record_error)[n], int a, int b, double probability); // Two qubit error
int CNOT(int (*Error_vector)[n], int a, int b);
int CNOT_rev(int (*Error_vector)[n], int b, int a);


int SQerror2(int (*Record_error2)[n], int a, double probability); // Single qubit error
int TQerror2(int (*Record_error2)[n], int a, int b, double probability); // Two qubit error
int CNOT2(int (*Error_vector2)[n], int a, int b);

int TQerror3(int (*Record_error)[n], int (*Record_error2)[n], int a, int b, double probability); // Two qubit error
int CNOT3(int (*Error_vector)[n], int (*Error_vector2)[n], int a, int b);

int x_circuit(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta);
int z_circuit(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta);

int perfect(int (*Error_vector)[n]);

int pt1_circuit(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta);
int pt2_circuit(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta);
int parallel_flag(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta);

int unflagged(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta );

int serial_flag(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta );


uint64_t next64() {  // random number
    uint64_t z = (x += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}

void rnd256_init() { // random number
    s[0] = next64();  s[1] = next64();  s[2] = next64();  s[3] = next64();
}


int const table_length_pt1_f1 = 46565;
int const table_width_pt1_f1 = 61;

int syndrome_pt1_f1[table_length_pt1_f1][table_width_pt1_f1]= { 0 };
int syndrome_result_pt1_f1[table_width_pt1_f1] = { 0 };
int test1_pt1_f1[table_width_pt1_f1] = { 0 };  //
int recovery_pt1_f1[table_length_pt1_f1][34]= { 0 };


int const table_length_pt1_f2 = 46565;
int const table_width_pt1_f2 = 61;

int syndrome_pt1_f2[table_length_pt1_f2][table_width_pt1_f2]= { 0 };
int syndrome_result_pt1_f2[table_width_pt1_f2] = { 0 };
int test1_pt1_f2[table_width_pt1_f2] = { 0 };  //
int recovery_pt1_f2[table_length_pt1_f2][34]= { 0 };


int const table_length_pt1_f3 = 33694;
int const table_width_pt1_f3 = 45;

int syndrome_pt1_f3[table_length_pt1_f3][table_width_pt1_f3]= { 0 };
int syndrome_result_pt1_f3[table_width_pt1_f3] = { 0 };
int test1_pt1_f3[table_width_pt1_f3] = { 0 };  //
int recovery_pt1_f3[table_length_pt1_f3][34]= { 0 };


int const table_length_pt1_f4 = 85539;
int const table_width_pt1_f4 = 63;

int syndrome_pt1_f4[table_length_pt1_f4][table_width_pt1_f4]= { 0 };
int syndrome_result_pt1_f4[table_width_pt1_f4] = { 0 };
int test1_pt1_f4[table_width_pt1_f4] = { 0 };  //
int recovery_pt1_f4[table_length_pt1_f4][34]= { 0 };

int const table_length_pt1_m1 = 54484;
int const table_width_pt1_m1 = 61;

int syndrome_pt1_m1[table_length_pt1_m1][table_width_pt1_m1]= { 0 };
int syndrome_result_pt1_m1[table_width_pt1_m1] = { 0 };
int test1_pt1_m1[table_width_pt1_m1] = { 0 };  //
int recovery_pt1_m1[table_length_pt1_m1][34]= { 0 };

int const table_length_pt1_m2 = 54484;
int const table_width_pt1_m2 = 61;

int syndrome_pt1_m2[table_length_pt1_m2][table_width_pt1_m2]= { 0 };
int syndrome_result_pt1_m2[table_width_pt1_m2] = { 0 };
int test1_pt1_m2[table_width_pt1_m2] = { 0 };  //
int recovery_pt1_m2[table_length_pt1_m2][34]= { 0 };


int const table_length_pt1_m3 = 12054;
int const table_width_pt1_m3 = 45;

int syndrome_pt1_m3[table_length_pt1_m3][table_width_pt1_m3]= { 0 };
int syndrome_result_pt1_m3[table_width_pt1_m3] = { 0 };
int test1_pt1_m3[table_width_pt1_m3] = { 0 };  //
int recovery_pt1_m3[table_length_pt1_m3][34]= { 0 };


int const table_length_pt1_m4 = 94555;
int const table_width_pt1_m4 = 63;

int syndrome_pt1_m4[table_length_pt1_m4][table_width_pt1_m4]= { 0 };
int syndrome_result_pt1_m4[table_width_pt1_m4] = { 0 };
int test1_pt1_m4[table_width_pt1_m4] = { 0 };  //
int recovery_pt1_m4[table_length_pt1_m4][34]= { 0 };


int const table_length_pt2_f1 = 47326;
int const table_width_pt2_f1 = 61;

int syndrome_pt2_f1[table_length_pt2_f1][table_width_pt2_f1]= { 0 };
int syndrome_result_pt2_f1[table_width_pt2_f1] = { 0 };
int test1_pt2_f1[table_width_pt2_f1] = { 0 };  //
int recovery_pt2_f1[table_length_pt2_f1][34]= { 0 };


int const table_length_pt2_f2 = 47326;
int const table_width_pt2_f2 = 61;

int syndrome_pt2_f2[table_length_pt2_f2][table_width_pt2_f2]= { 0 };
int syndrome_result_pt2_f2[table_width_pt2_f2] = { 0 };
int test1_pt2_f2[table_width_pt2_f2] = { 0 };  //
int recovery_pt2_f2[table_length_pt2_f2][34]= { 0 };


int const table_length_pt2_f3 = 33694;
int const table_width_pt2_f3 = 45;

int syndrome_pt2_f3[table_length_pt2_f3][table_width_pt2_f3]= { 0 };
int syndrome_result_pt2_f3[table_width_pt2_f3] = { 0 };
int test1_pt2_f3[table_width_pt2_f3] = { 0 };  //
int recovery_pt2_f3[table_length_pt2_f3][34]= { 0 };


int const table_length_pt2_f4 = 86465;
int const table_width_pt2_f4 = 63;

int syndrome_pt2_f4[table_length_pt2_f4][table_width_pt2_f4]= { 0 };
int syndrome_result_pt2_f4[table_width_pt2_f4] = { 0 };
int test1_pt2_f4[table_width_pt2_f4] = { 0 };  //
int recovery_pt2_f4[table_length_pt2_f4][34]= { 0 };

int const table_length_pt2_m1 = 55159;
int const table_width_pt2_m1 = 61;

int syndrome_pt2_m1[table_length_pt2_m1][table_width_pt2_m1]= { 0 };
int syndrome_result_pt2_m1[table_width_pt2_m1] = { 0 };
int test1_pt2_m1[table_width_pt2_m1] = { 0 };  //
int recovery_pt2_m1[table_length_pt2_m1][34]= { 0 };

int const table_length_pt2_m2 = 55159;
int const table_width_pt2_m2 = 61;

int syndrome_pt2_m2[table_length_pt2_m2][table_width_pt2_m2]= { 0 };
int syndrome_result_pt2_m2[table_width_pt2_m2] = { 0 };
int test1_pt2_m2[table_width_pt2_m2] = { 0 };  //
int recovery_pt2_m2[table_length_pt2_m2][34]= { 0 };


int const table_length_pt2_m3 = 12054;
int const table_width_pt2_m3 = 45;

int syndrome_pt2_m3[table_length_pt2_m3][table_width_pt2_m3]= { 0 };
int syndrome_result_pt2_m3[table_width_pt2_m3] = { 0 };
int test1_pt2_m3[table_width_pt2_m3] = { 0 };  //
int recovery_pt2_m3[table_length_pt2_m3][34]= { 0 };


int const table_length_pt2_m4 = 94993;
int const table_width_pt2_m4 = 63;

int syndrome_pt2_m4[table_length_pt2_m4][table_width_pt2_m4]= { 0 };
int syndrome_result_pt2_m4[table_width_pt2_m4] = { 0 };
int test1_pt2_m4[table_width_pt2_m4] = { 0 };  //
int recovery_pt2_m4[table_length_pt2_m4][34]= { 0 };



int syndrome[153][8]= { 0 };
int recovery[153][17]= { 0 };
int symdorme_result_x[8];
int symdorme_result_z[8];
int test1[8]; // syndrome talbe for function used


int compare_result;
int table_index;



int main(){
    // 數秒counter
    int input;
    clock_t start, end;
    start = clock();
    // print time
    time_t current_time;
    char* c_time_string;
    current_time = time(NULL);
    c_time_string = ctime(&current_time);
    printf("Current time is %s", c_time_string);
    
    
    //讀取table
//============================================================================================================================
    
    
    ifstream fin_z_1a("table\\syndore_pt1_f1.txt");
    if(!fin_z_1a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_f1;i++)
        for(int k=0;k<table_width_pt1_f1;k++)
            fin_z_1a >> syndrome_pt1_f1[i][k];
    fin_z_1a.close();
    
    
    
    ifstream fin_z_1b("table\\recovery_pt1_f1.txt");
    if(!fin_z_1b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_f1;i++)
        for(int k=0;k<34;k++)
            fin_z_1b >> recovery_pt1_f1[i][k];
    fin_z_1b.close();
    
    
    
    ifstream fin_z_2a("table\\syndore_pt1_f1.txt");
    if(!fin_z_2a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_f2;i++)
        for(int k=0;k<table_width_pt1_f2;k++)
            fin_z_2a >> syndrome_pt1_f2[i][k];
    fin_z_2a.close();
    
    
    
    ifstream fin_z_2b("table\\recovery_pt1_f1.txt");
    if(!fin_z_2b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_f2;i++)
        for(int k=0;k<34;k++)
            fin_z_2b >> recovery_pt1_f2[i][k];
    fin_z_2b.close();
    
    
    
    
    ifstream fin_z_3a("table\\syndore_pt1_f3.txt");
    if(!fin_z_3a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_f3;i++)
        for(int k=0;k<table_width_pt1_f3;k++)
            fin_z_3a >> syndrome_pt1_f3[i][k];
    fin_z_3a.close();
    
    
    
    ifstream fin_z_3b("table\\recovery_pt1_f3.txt");
    if(!fin_z_3b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_f3;i++)
        for(int k=0;k<34;k++)
            fin_z_3b >> recovery_pt1_f3[i][k];
    fin_z_3b.close();
    
    
    
    ifstream fin_z_4a("table\\syndore_pt1_f4.txt");
    if(!fin_z_4a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_f4;i++)
        for(int k=0;k<table_width_pt1_f4;k++)
            fin_z_4a >> syndrome_pt1_f4[i][k];
    fin_z_4a.close();
    
    
    
    ifstream fin_z_4b("table\\recovery_pt1_f4.txt");
    if(!fin_z_4b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_f4;i++)
        for(int k=0;k<34;k++)
            fin_z_4b >> recovery_pt1_f4[i][k];
    fin_z_4b.close();
    
    
    
    ifstream fin_z_5a("table\\syndore_pt1_m1.txt");
    if(!fin_z_5a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_m1;i++)
        for(int k=0;k<table_width_pt1_m1;k++)
            fin_z_5a >> syndrome_pt1_m1[i][k];
    fin_z_5a.close();
    
    
    
    ifstream fin_z_5b("table\\recovery_pt1_m1.txt");
    if(!fin_z_5b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_m1;i++)
        for(int k=0;k<34;k++)
            fin_z_5b >> recovery_pt1_m1[i][k];
    fin_z_5b.close();
    
    
    ifstream fin_z_6a("table\\syndore_pt1_m1.txt");
    if(!fin_z_6a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_m2;i++)
        for(int k=0;k<table_width_pt1_m2;k++)
            fin_z_6a >> syndrome_pt1_m2[i][k];
    fin_z_6a.close();
    
    
    
    ifstream fin_z_6b("table\\recovery_pt1_m1.txt");
    if(!fin_z_6b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_m2;i++)
        for(int k=0;k<34;k++)
            fin_z_6b >> recovery_pt1_m2[i][k];
    fin_z_6b.close();
    
    
    
    ifstream fin_z_7a("table\\syndore_pt1_m3.txt");
    if(!fin_z_7a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_m3;i++)
        for(int k=0;k<table_width_pt1_m3;k++)
            fin_z_7a >> syndrome_pt1_m3[i][k];
    fin_z_7a.close();
    
    
    
    ifstream fin_z_7b("table\\recovery_pt1_m3.txt");
    if(!fin_z_7b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_m3;i++)
        for(int k=0;k<34;k++)
            fin_z_7b >> recovery_pt1_m3[i][k];
    fin_z_7b.close();
    
    
    
    
    ifstream fin_z_8a("table\\syndore_pt1_m4.txt");
    if(!fin_z_8a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_m4;i++)
        for(int k=0;k<table_width_pt1_m4;k++)
            fin_z_8a >> syndrome_pt1_m4[i][k];
    fin_z_8a.close();
    
    
    
    ifstream fin_z_8b("table\\recovery_pt1_m4.txt");
    if(!fin_z_8b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt1_m4;i++)
        for(int k=0;k<34;k++)
            fin_z_8b >> recovery_pt1_m4[i][k];
    fin_z_8b.close();
    
    
    
    ifstream fin_x_1a("table\\syndore_pt2_f1.txt");
    if(!fin_x_1a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_f1;i++)
        for(int k=0;k<table_width_pt2_f1;k++)
            fin_x_1a >> syndrome_pt2_f1[i][k];
    fin_x_1a.close();
    
    
    
    ifstream fin_x_1b("table\\recovery_pt2_f1.txt");
    if(!fin_x_1b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_f1;i++)
        for(int k=0;k<34;k++)
            fin_x_1b >> recovery_pt2_f1[i][k];
    fin_x_1b.close();
    
    
    
    ifstream fin_x_2a("table\\syndore_pt2_f1.txt");
    if(!fin_x_2a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_f2;i++)
        for(int k=0;k<table_width_pt2_f2;k++)
            fin_x_2a >> syndrome_pt2_f2[i][k];
    fin_x_2a.close();
    
    
    
    ifstream fin_x_2b("table\\recovery_pt2_f1.txt");
    if(!fin_x_2b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_f2;i++)
        for(int k=0;k<34;k++)
            fin_x_2b >> recovery_pt2_f2[i][k];
    fin_x_2b.close();
    
    
    
    
    ifstream fin_x_3a("table\\syndore_pt2_f3.txt");
    if(!fin_x_3a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_f3;i++)
        for(int k=0;k<table_width_pt2_f3;k++)
            fin_x_3a >> syndrome_pt2_f3[i][k];
    fin_x_3a.close();
    
    
    
    ifstream fin_x_3b("table\\recovery_pt2_f3.txt");
    if(!fin_x_3b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_f3;i++)
        for(int k=0;k<34;k++)
            fin_x_3b >> recovery_pt2_f3[i][k];
    fin_x_3b.close();
    
    
    
    ifstream fin_x_4a("table\\syndore_pt2_f4.txt");
    if(!fin_x_4a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_f4;i++)
        for(int k=0;k<table_width_pt2_f4;k++)
            fin_x_4a >> syndrome_pt2_f4[i][k];
    fin_x_4a.close();
    
    
    
    ifstream fin_x_4b("table\\recovery_pt2_f4.txt");
    if(!fin_x_4b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_f4;i++)
        for(int k=0;k<34;k++)
            fin_x_4b >> recovery_pt2_f4[i][k];
    fin_x_4b.close();
    
    
    
    ifstream fin_x_5a("table\\syndore_pt2_m1.txt");
    if(!fin_x_5a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_m1;i++)
        for(int k=0;k<table_width_pt2_m1;k++)
            fin_x_5a >> syndrome_pt2_m1[i][k];
    fin_x_5a.close();
    
    
    
    ifstream fin_x_5b("table\\recovery_pt2_m1.txt");
    if(!fin_x_5b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_m1;i++)
        for(int k=0;k<34;k++)
            fin_x_5b >> recovery_pt2_m1[i][k];
    fin_x_5b.close();
    
    
    ifstream fin_x_6a("table\\syndore_pt2_m1.txt");
    if(!fin_x_6a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_m2;i++)
        for(int k=0;k<table_width_pt2_m2;k++)
            fin_x_6a >> syndrome_pt2_m2[i][k];
    fin_x_6a.close();
    
    
    
    ifstream fin_x_6b("table\\recovery_pt2_m1.txt");
    if(!fin_x_6b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_m2;i++)
        for(int k=0;k<34;k++)
            fin_x_6b >> recovery_pt2_m2[i][k];
    fin_x_6b.close();
    
    
    
    ifstream fin_x_7a("table\\syndore_pt2_m3.txt");
    if(!fin_x_7a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_m3;i++)
        for(int k=0;k<table_width_pt2_m3;k++)
            fin_x_7a >> syndrome_pt2_m3[i][k];
    fin_x_7a.close();
    
    
    
    ifstream fin_x_7b("table\\recovery_pt2_m3.txt");
    if(!fin_x_7b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_m3;i++)
        for(int k=0;k<34;k++)
            fin_x_7b >> recovery_pt2_m3[i][k];
    fin_x_7b.close();
    
    
    
    
    ifstream fin_x_8a("table\\syndore_pt2_m4.txt");
    if(!fin_x_8a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_m4;i++)
        for(int k=0;k<table_width_pt2_m4;k++)
            fin_x_8a >> syndrome_pt2_m4[i][k];
    fin_x_8a.close();
    
    
    
    ifstream fin_x_8b("table\\recovery_pt2_m4.txt");
    if(!fin_x_8b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_pt2_m4;i++)
        for(int k=0;k<34;k++)
            fin_x_8b >> recovery_pt2_m4[i][k];
    fin_x_8b.close();
    
    
    
    ifstream fin1("table\\syndrome.txt");
    if(!fin1) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<153;i++)
        for(int k=0;k<8;k++)
            fin1 >> syndrome[i][k];
    fin1.close();
    
    ifstream fin2("table\\recovery.txt");
    if(!fin2) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<153;i++)
        for(int k=0;k<17;k++)
            fin2 >> recovery[i][k];
    fin2.close();
    
    
//============================================================================================================================
    
    
    
    double Total_number, Error_number, detected_number, probability;
    int s1, s2, s3, s4, s5, s6, s7, s8, m1, m2, m3, m4,m5 ,m6 ,q1 ,q2 ,q3 ,ga1, ga2;
    int s9,s10,s11,s12,s13,s14,s15,s16, counter;
    int N = 17; // 切 N 個格子
    int Error_vector[2][n]={0};
    int Error_vector2[2][n]={0};
    int xe[1]={2}   ; // sigle error by user , X, Z, Y = 2, 3, 4
    int ze[1]={3}   ; // sigle error by user , X, Z, Y = 2, 3, 4
    
    
    double Display_p[N], Display_e[N], Display_d[N];
    
    double gamma = 1; // memory error
    double alpha = 10; // measurement error
    double beta = 1;  // CNOT error
    
    
    cout << "[[17,1,5]] shared-flag with the last round is parallel" << " ,loop=" << N-1 << " ,gamma = " << gamma <<  ", alpha = " << alpha << ", beta = "  << beta << endl << endl << endl;

    for(int i=1; i<N; i++){
        
        probability = 0.00001+0.00001*(i-1)*(i*i/2); 
        Total_number = 0; 
        Error_number = 0; 
        while(Total_number<1000000||Error_number<800){ 
            
    
            s1 = 0;            s2 = 0;            s3 = 0;            s4 = 0;
            s5 = 0;            s6 = 0;            s7 = 0;            s8 = 0;
            s9 = 0;            s10= 0;            s11= 0;            s12= 0;
            s13= 0;            s14= 0;            s15= 0;            s16= 0;
            m1 = 0;            m2 = 0;            m3 = 0;            m4 = 0;
            m5 = 0;            m6 = 0;            q1 = 0;            q2 = 0;
            q3 = 0;            ga1= 0;            ga2= 0;
            
            //**get time***************************
            time_t current_time;
            char* c_time_string;
            current_time = time(NULL);
            c_time_string = ctime(&current_time);
            //*************************************
            
            
            for(int i=0; i<2; i++){
                for(int j=0; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
            }
            
            
            
//------------------------------------------------------------------------------------------------------------------------------
            
            pt1_circuit(Error_vector, probability, gamma, alpha, beta );
            
            if  (  Error_vector[1][40] ==0   && Error_vector[1][41] ==0 && Error_vector[1][42] ==0 && Error_vector[1][43] ==0  && Error_vector[1][44] ==0  && Error_vector[1][45] ==0  && Error_vector[1][46] ==0 && Error_vector[0][20] ==0 && Error_vector[0][21] ==0 && Error_vector[0][22] ==0 && Error_vector[0][23] ==0 && Error_vector[0][24] ==0 && Error_vector[0][25] ==0 && Error_vector[0][26] ==0 && Error_vector[0][27] ==0    ){
                goto outpoint1;
            }
            
            
            syndrome_result_pt1_f1[16] = Error_vector[0][20];  //m1
            syndrome_result_pt1_f1[17] = Error_vector[0][21];  //m2
            syndrome_result_pt1_f1[18] = Error_vector[0][22];  //m3
            syndrome_result_pt1_f1[19] = Error_vector[0][23];  //m4
            syndrome_result_pt1_f1[20] = Error_vector[0][24];  //m5
            syndrome_result_pt1_f1[21] = Error_vector[0][25];  //m6
            syndrome_result_pt1_f1[22] = Error_vector[0][26];  //m7
            syndrome_result_pt1_f1[23] = Error_vector[0][27];  //m8
            syndrome_result_pt1_f1[24] = Error_vector[1][40];  //f1
            syndrome_result_pt1_f1[25] = Error_vector[1][41];  //f2
            syndrome_result_pt1_f1[26] = Error_vector[1][42];  //f3
            syndrome_result_pt1_f1[27] = Error_vector[1][43];  //f4
            syndrome_result_pt1_f1[28] = Error_vector[1][44];  //f5
            syndrome_result_pt1_f1[29] = Error_vector[1][45];  //f6
            syndrome_result_pt1_f1[30] = Error_vector[1][46];  //f7
            
            syndrome_result_pt1_f2[16] = Error_vector[0][20];  //m1
            syndrome_result_pt1_f2[17] = Error_vector[0][21];  //m2
            syndrome_result_pt1_f2[18] = Error_vector[0][22];  //m3
            syndrome_result_pt1_f2[19] = Error_vector[0][23];  //m4
            syndrome_result_pt1_f2[20] = Error_vector[0][24];  //m5
            syndrome_result_pt1_f2[21] = Error_vector[0][25];  //m6
            syndrome_result_pt1_f2[22] = Error_vector[0][26];  //m7
            syndrome_result_pt1_f2[23] = Error_vector[0][27];  //m8
            syndrome_result_pt1_f2[24] = Error_vector[1][40];  //f1
            syndrome_result_pt1_f2[25] = Error_vector[1][41];  //f2
            syndrome_result_pt1_f2[26] = Error_vector[1][42];  //f3
            syndrome_result_pt1_f2[27] = Error_vector[1][43];  //f4
            syndrome_result_pt1_f2[28] = Error_vector[1][44];  //f5
            syndrome_result_pt1_f2[29] = Error_vector[1][45];  //f6
            syndrome_result_pt1_f2[30] = Error_vector[1][46];  //f7
            
            syndrome_result_pt1_f3[0] = Error_vector[0][20];  //m1
            syndrome_result_pt1_f3[1] = Error_vector[0][21];  //m2
            syndrome_result_pt1_f3[2] = Error_vector[0][22];  //m3
            syndrome_result_pt1_f3[3] = Error_vector[0][23];  //m4
            syndrome_result_pt1_f3[4] = Error_vector[0][24];  //m5
            syndrome_result_pt1_f3[5] = Error_vector[0][25];  //m6
            syndrome_result_pt1_f3[6] = Error_vector[0][26];  //m7
            syndrome_result_pt1_f3[7] = Error_vector[0][27];  //m8
            syndrome_result_pt1_f3[8] = Error_vector[1][40];  //f1
            syndrome_result_pt1_f3[9] = Error_vector[1][41];  //f2
            syndrome_result_pt1_f3[10] = Error_vector[1][42];  //f3
            syndrome_result_pt1_f3[11] = Error_vector[1][43];  //f4
            syndrome_result_pt1_f3[12] = Error_vector[1][44];  //f5
            syndrome_result_pt1_f3[13] = Error_vector[1][45];  //f6
            syndrome_result_pt1_f3[14] = Error_vector[1][46];  //f7
            
            syndrome_result_pt1_f4[16] = Error_vector[0][20];  //m1
            syndrome_result_pt1_f4[17] = Error_vector[0][21];  //m2
            syndrome_result_pt1_f4[18] = Error_vector[0][22];  //m3
            syndrome_result_pt1_f4[19] = Error_vector[0][23];  //m4
            syndrome_result_pt1_f4[20] = Error_vector[0][24];  //m5
            syndrome_result_pt1_f4[21] = Error_vector[0][25];  //m6
            syndrome_result_pt1_f4[22] = Error_vector[0][26];  //m7
            syndrome_result_pt1_f4[23] = Error_vector[0][27];  //m8
            syndrome_result_pt1_f4[24] = Error_vector[1][40];  //f1
            syndrome_result_pt1_f4[25] = Error_vector[1][41];  //f2
            syndrome_result_pt1_f4[26] = Error_vector[1][42];  //f3
            syndrome_result_pt1_f4[27] = Error_vector[1][43];  //f4
            syndrome_result_pt1_f4[28] = Error_vector[1][44];  //f5
            syndrome_result_pt1_f4[29] = Error_vector[1][45];  //f6
            syndrome_result_pt1_f4[30] = Error_vector[1][46];  //f7
            
            
            syndrome_result_pt1_m1[16] = Error_vector[0][20];  //m1
            syndrome_result_pt1_m1[17] = Error_vector[0][21];  //m2
            syndrome_result_pt1_m1[18] = Error_vector[0][22];  //m3
            syndrome_result_pt1_m1[19] = Error_vector[0][23];  //m4
            syndrome_result_pt1_m1[20] = Error_vector[0][24];  //m5
            syndrome_result_pt1_m1[21] = Error_vector[0][25];  //m6
            syndrome_result_pt1_m1[22] = Error_vector[0][26];  //m7
            syndrome_result_pt1_m1[23] = Error_vector[0][27];  //m8
            syndrome_result_pt1_m1[24] = Error_vector[1][40];  //f1
            syndrome_result_pt1_m1[25] = Error_vector[1][41];  //f2
            syndrome_result_pt1_m1[26] = Error_vector[1][42];  //f3
            syndrome_result_pt1_m1[27] = Error_vector[1][43];  //f4
            syndrome_result_pt1_m1[28] = Error_vector[1][44];  //f5
            syndrome_result_pt1_m1[29] = Error_vector[1][45];  //f6
            syndrome_result_pt1_m1[30] = Error_vector[1][46];  //f7
            
            syndrome_result_pt1_m2[16] = Error_vector[0][20];  //m1
            syndrome_result_pt1_m2[17] = Error_vector[0][21];  //m2
            syndrome_result_pt1_m2[18] = Error_vector[0][22];  //m3
            syndrome_result_pt1_m2[19] = Error_vector[0][23];  //m4
            syndrome_result_pt1_m2[20] = Error_vector[0][24];  //m5
            syndrome_result_pt1_m2[21] = Error_vector[0][25];  //m6
            syndrome_result_pt1_m2[22] = Error_vector[0][26];  //m7
            syndrome_result_pt1_m2[23] = Error_vector[0][27];  //m8
            syndrome_result_pt1_m2[24] = Error_vector[1][40];  //f1
            syndrome_result_pt1_m2[25] = Error_vector[1][41];  //f2
            syndrome_result_pt1_m2[26] = Error_vector[1][42];  //f3
            syndrome_result_pt1_m2[27] = Error_vector[1][43];  //f4
            syndrome_result_pt1_m2[28] = Error_vector[1][44];  //f5
            syndrome_result_pt1_m2[29] = Error_vector[1][45];  //f6
            syndrome_result_pt1_m2[30] = Error_vector[1][46];  //f7
            
            
            syndrome_result_pt1_m3[0] = Error_vector[0][20];  //m1
            syndrome_result_pt1_m3[1] = Error_vector[0][21];  //m2
            syndrome_result_pt1_m3[2] = Error_vector[0][22];  //m3
            syndrome_result_pt1_m3[3] = Error_vector[0][23];  //m4
            syndrome_result_pt1_m3[4] = Error_vector[0][24];  //m5
            syndrome_result_pt1_m3[5] = Error_vector[0][25];  //m6
            syndrome_result_pt1_m3[6] = Error_vector[0][26];  //m7
            syndrome_result_pt1_m3[7] = Error_vector[0][27];  //m8
            syndrome_result_pt1_m3[8] = Error_vector[1][40];  //f1
            syndrome_result_pt1_m3[9] = Error_vector[1][41];  //f2
            syndrome_result_pt1_m3[10] = Error_vector[1][42];  //f3
            syndrome_result_pt1_m3[11] = Error_vector[1][43];  //f4
            syndrome_result_pt1_m3[12] = Error_vector[1][44];  //f5
            syndrome_result_pt1_m3[13] = Error_vector[1][45];  //f6
            syndrome_result_pt1_m3[14] = Error_vector[1][46];  //f7
            
            
            syndrome_result_pt1_m4[16] = Error_vector[0][20];  //m1
            syndrome_result_pt1_m4[17] = Error_vector[0][21];  //m2
            syndrome_result_pt1_m4[18] = Error_vector[0][22];  //m3
            syndrome_result_pt1_m4[19] = Error_vector[0][23];  //m4
            syndrome_result_pt1_m4[20] = Error_vector[0][24];  //m5
            syndrome_result_pt1_m4[21] = Error_vector[0][25];  //m6
            syndrome_result_pt1_m4[22] = Error_vector[0][26];  //m7
            syndrome_result_pt1_m4[23] = Error_vector[0][27];  //m8
            syndrome_result_pt1_m4[24] = Error_vector[1][40];  //f1
            syndrome_result_pt1_m4[25] = Error_vector[1][41];  //f2
            syndrome_result_pt1_m4[26] = Error_vector[1][42];  //f3
            syndrome_result_pt1_m4[27] = Error_vector[1][43];  //f4
            syndrome_result_pt1_m4[28] = Error_vector[1][44];  //f5
            syndrome_result_pt1_m4[29] = Error_vector[1][45];  //f6
            syndrome_result_pt1_m4[30] = Error_vector[1][46];  //f7
            
            
            
            
            if (   ( Error_vector[1][40] !=0  || Error_vector[1][41] !=0 || Error_vector[1][42] !=0 || Error_vector[1][43] !=0  || Error_vector[1][44] !=0  || Error_vector[1][45] !=0 || Error_vector[1][46] !=0 )   ){
                
                
                
                
                for(int i=0; i<2; i++){
                    for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                }
                
                
                parallel_flag(Error_vector, probability, gamma, alpha, beta );
                
                
                syndrome_result_pt1_f1[31] = Error_vector[0][20];  //m1
                syndrome_result_pt1_f1[32] = Error_vector[0][21];  //m2
                syndrome_result_pt1_f1[33] = Error_vector[0][22];  //m3
                syndrome_result_pt1_f1[34] = Error_vector[0][23];  //m4
                syndrome_result_pt1_f1[35] = Error_vector[0][24];  //m5
                syndrome_result_pt1_f1[36] = Error_vector[0][25];  //m6
                syndrome_result_pt1_f1[37] = Error_vector[0][26];  //m7
                syndrome_result_pt1_f1[38] = Error_vector[0][27];  //m8
                
                //X-type stabilizer
                syndrome_result_pt1_f1[39] = Error_vector[1][30];  //m9
                syndrome_result_pt1_f1[40] = Error_vector[1][31];  //m10
                syndrome_result_pt1_f1[41] = Error_vector[1][32];  //m11
                syndrome_result_pt1_f1[42] = Error_vector[1][33];  //m12
                syndrome_result_pt1_f1[43] = Error_vector[1][34];  //m13
                syndrome_result_pt1_f1[44] = Error_vector[1][35];  //m14
                syndrome_result_pt1_f1[45] = Error_vector[1][36];  //m15
                syndrome_result_pt1_f1[46] = Error_vector[1][37];  //m16
                
                //Z-type flag
                
                syndrome_result_pt1_f1[47] = Error_vector[1][40];  //f1
                syndrome_result_pt1_f1[48] = Error_vector[1][41];  //f2
                syndrome_result_pt1_f1[49] = Error_vector[1][42];  //f3
                syndrome_result_pt1_f1[50] = Error_vector[1][43];  //f4
                syndrome_result_pt1_f1[51] = Error_vector[1][44];  //f5
                syndrome_result_pt1_f1[52] = Error_vector[1][45];  //f6
                syndrome_result_pt1_f1[53] = Error_vector[1][46];  //f7
                
                //X-type  flag
                syndrome_result_pt1_f1[54] = Error_vector[0][50];  //f1
                syndrome_result_pt1_f1[55] = Error_vector[0][51];  //f2
                syndrome_result_pt1_f1[56] = Error_vector[0][52];  //f3
                syndrome_result_pt1_f1[57] = Error_vector[0][53];  //f4
                syndrome_result_pt1_f1[58] = Error_vector[0][54];  //f5
                syndrome_result_pt1_f1[59] = Error_vector[0][55];  //f6
                syndrome_result_pt1_f1[60] = Error_vector[0][56];  //f7
                
                //Z-type stabilizer
                syndrome_result_pt1_f4[31] = Error_vector[0][20];  //m1
                syndrome_result_pt1_f4[32] = Error_vector[0][21];  //m2
                syndrome_result_pt1_f4[33] = Error_vector[0][22];  //m3
                syndrome_result_pt1_f4[34] = Error_vector[0][23];  //m4
                syndrome_result_pt1_f4[35] = Error_vector[0][24];  //m5
                syndrome_result_pt1_f4[36] = Error_vector[0][25];  //m6
                syndrome_result_pt1_f4[37] = Error_vector[0][26];  //m7
                syndrome_result_pt1_f4[38] = Error_vector[0][27];  //m8
                
                //X-type stabilizer
                syndrome_result_pt1_f4[39] = Error_vector[1][30];  //m9
                syndrome_result_pt1_f4[40] = Error_vector[1][31];  //m10
                syndrome_result_pt1_f4[41] = Error_vector[1][32];  //m11
                syndrome_result_pt1_f4[42] = Error_vector[1][33];  //m12
                syndrome_result_pt1_f4[43] = Error_vector[1][34];  //m13
                syndrome_result_pt1_f4[44] = Error_vector[1][35];  //m14
                syndrome_result_pt1_f4[45] = Error_vector[1][36];  //m15
                syndrome_result_pt1_f4[46] = Error_vector[1][37];  //m16
                
                
                
                int flag_result = 0;
                
                for (int i=0; i<7; i++){
                    flag_result = flag_result + Error_vector[1][40+i] +  Error_vector[0][50+i]  ;
                }
                
                
                if ( flag_result != 0){
                    
                    
                    
                    for(int i=0; i<2; i++){
                        for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    
                    unflagged(Error_vector, probability, gamma, alpha, beta );
                    
                    
                    
                    
                    //--use unflagged syndrome do error correction---------------------------------------
                    //-----------------------------------------
                    //loading syndorme result to array
                    
                    for (int i=0; i<8; i++){
                        syndrome_result_pt1_f1[i] = Error_vector[0][i+20];
                    }
                    for (int i=0; i<8; i++){
                        syndrome_result_pt1_f1[i+8] = Error_vector[1][i+30];
                    }
                    
                    
                    //compare test1 and symdorme_result array and get index j
                    for (int j=0; j<table_length_pt1_f1; j++){
                        
                        for (int i=0; i<table_width_pt1_f1; i++){
                            test1_pt1_f1[i]=syndrome_pt1_f1[j][i];
                        }
                        // 排除syndrome = 0000的情快
                        //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                        //	break;
                        //}
                        
                        compare_result = memcmp(test1_pt1_f1, syndrome_result_pt1_f1,sizeof(syndrome_result_pt1_f1));
                        
                        if (compare_result == 0) {
                            
                            // table_index = j;
                            
                            //        cout <<  "j= "  << j << endl;
                            //使用recovery進行 x error
                            
                            for (int k=0; k<17; k++){
                                Error_vector[0][k]= (Error_vector[0][k]+recovery_pt1_f1[j][k])%2;
                                Error_vector[1][k]= (Error_vector[1][k]+recovery_pt1_f1[j][k+17])%2;
                            }
                            break;
                            
                        }
                        
                    }
                    
                }   //  第二次量測 flag rised
                
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                
                else {
                    
                    
                    for(int i=0; i<2; i++){
                        for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    
                    parallel_flag(Error_vector, probability, gamma, alpha, beta );
                    
                    //Z-type stabilizer
                    syndrome_result_pt1_f2[31] = Error_vector[0][20];  //m1
                    syndrome_result_pt1_f2[32] = Error_vector[0][21];  //m2
                    syndrome_result_pt1_f2[33] = Error_vector[0][22];  //m3
                    syndrome_result_pt1_f2[34] = Error_vector[0][23];  //m4
                    syndrome_result_pt1_f2[35] = Error_vector[0][24];  //m5
                    syndrome_result_pt1_f2[36] = Error_vector[0][25];  //m6
                    syndrome_result_pt1_f2[37] = Error_vector[0][26];  //m7
                    syndrome_result_pt1_f2[38] = Error_vector[0][27];  //m8
                    
                    //X-type stabilizer
                    syndrome_result_pt1_f2[39] = Error_vector[1][30];  //m9
                    syndrome_result_pt1_f2[40] = Error_vector[1][31];  //m10
                    syndrome_result_pt1_f2[41] = Error_vector[1][32];  //m11
                    syndrome_result_pt1_f2[42] = Error_vector[1][33];  //m12
                    syndrome_result_pt1_f2[43] = Error_vector[1][34];  //m13
                    syndrome_result_pt1_f2[44] = Error_vector[1][35];  //m14
                    syndrome_result_pt1_f2[45] = Error_vector[1][36];  //m15
                    syndrome_result_pt1_f2[46] = Error_vector[1][37];  //m16
                    
                    //Z-type flag
                    
                    syndrome_result_pt1_f2[47] = Error_vector[1][40];  //f1
                    syndrome_result_pt1_f2[48] = Error_vector[1][41];  //f2
                    syndrome_result_pt1_f2[49] = Error_vector[1][42];  //f3
                    syndrome_result_pt1_f2[50] = Error_vector[1][43];  //f4
                    syndrome_result_pt1_f2[51] = Error_vector[1][44];  //f5
                    syndrome_result_pt1_f2[52] = Error_vector[1][45];  //f6
                    syndrome_result_pt1_f2[53] = Error_vector[1][46];  //f7
                    
                    //X-type  flag
                    syndrome_result_pt1_f2[54] = Error_vector[0][50];  //f1
                    syndrome_result_pt1_f2[55] = Error_vector[0][51];  //f2
                    syndrome_result_pt1_f2[56] = Error_vector[0][52];  //f3
                    syndrome_result_pt1_f2[57] = Error_vector[0][53];  //f4
                    syndrome_result_pt1_f2[58] = Error_vector[0][54];  //f5
                    syndrome_result_pt1_f2[59] = Error_vector[0][55];  //f6
                    syndrome_result_pt1_f2[60] = Error_vector[0][56];  //f7
                    
                    //Z-type stabilizer
                    syndrome_result_pt1_f3[15] = Error_vector[0][20];  //m1
                    syndrome_result_pt1_f3[16] = Error_vector[0][21];  //m2
                    syndrome_result_pt1_f3[17] = Error_vector[0][22];  //m3
                    syndrome_result_pt1_f3[18] = Error_vector[0][23];  //m4
                    syndrome_result_pt1_f3[19] = Error_vector[0][24];  //m5
                    syndrome_result_pt1_f3[20] = Error_vector[0][25];  //m6
                    syndrome_result_pt1_f3[21] = Error_vector[0][26];  //m7
                    syndrome_result_pt1_f3[22] = Error_vector[0][27];  //m8
                    
                    //X-type stabilizer
                    syndrome_result_pt1_f3[23] = Error_vector[1][30];  //m9
                    syndrome_result_pt1_f3[24] = Error_vector[1][31];  //m10
                    syndrome_result_pt1_f3[25] = Error_vector[1][32];  //m11
                    syndrome_result_pt1_f3[26] = Error_vector[1][33];  //m12
                    syndrome_result_pt1_f3[27] = Error_vector[1][34];  //m13
                    syndrome_result_pt1_f3[28] = Error_vector[1][35];  //m14
                    syndrome_result_pt1_f3[29] = Error_vector[1][36];  //m15
                    syndrome_result_pt1_f3[30] = Error_vector[1][37];  //m16
                    
                    //Z-type flag
                    
                    syndrome_result_pt1_f3[31] = Error_vector[1][40];  //f1
                    syndrome_result_pt1_f3[32] = Error_vector[1][41];  //f2
                    syndrome_result_pt1_f3[33] = Error_vector[1][42];  //f3
                    syndrome_result_pt1_f3[34] = Error_vector[1][43];  //f4
                    syndrome_result_pt1_f3[35] = Error_vector[1][44];  //f5
                    syndrome_result_pt1_f3[36] = Error_vector[1][45];  //f6
                    syndrome_result_pt1_f3[37] = Error_vector[1][46];  //f7
                    
                    //X-type  flag
                    syndrome_result_pt1_f3[38] = Error_vector[0][50];  //f1
                    syndrome_result_pt1_f3[39] = Error_vector[0][51];  //f2
                    syndrome_result_pt1_f3[40] = Error_vector[0][52];  //f3
                    syndrome_result_pt1_f3[41] = Error_vector[0][53];  //f4
                    syndrome_result_pt1_f3[42] = Error_vector[0][54];  //f5
                    syndrome_result_pt1_f3[43] = Error_vector[0][55];  //f6
                    syndrome_result_pt1_f3[44] = Error_vector[0][56];  //f7
                    
                    
                    //Z-type stabilizer
                    syndrome_result_pt1_f4[47] = Error_vector[0][20];  //m1
                    syndrome_result_pt1_f4[48] = Error_vector[0][21];  //m2
                    syndrome_result_pt1_f4[49] = Error_vector[0][22];  //m3
                    syndrome_result_pt1_f4[50] = Error_vector[0][23];  //m4
                    syndrome_result_pt1_f4[51] = Error_vector[0][24];  //m5
                    syndrome_result_pt1_f4[52] = Error_vector[0][25];  //m6
                    syndrome_result_pt1_f4[53] = Error_vector[0][26];  //m7
                    syndrome_result_pt1_f4[54] = Error_vector[0][27];  //m8
                    
                    //X-type stabilizer
                    syndrome_result_pt1_f4[55] = Error_vector[1][30];  //m9
                    syndrome_result_pt1_f4[56] = Error_vector[1][31];  //m10
                    syndrome_result_pt1_f4[57] = Error_vector[1][32];  //m11
                    syndrome_result_pt1_f4[58] = Error_vector[1][33];  //m12
                    syndrome_result_pt1_f4[59] = Error_vector[1][34];  //m13
                    syndrome_result_pt1_f4[60] = Error_vector[1][35];  //m14
                    syndrome_result_pt1_f4[61] = Error_vector[1][36];  //m15
                    syndrome_result_pt1_f4[62] = Error_vector[1][37];  //m16
                    
                    
                    
                    
                    flag_result = 0;
                    
                    for (int i=0; i<7; i++){
                        flag_result = flag_result + Error_vector[1][40+i] + Error_vector[0][50+i] ;
                    }
                    
                    
                    if ( flag_result != 0){   	// 第三次量測 flag rised
                        
                        
                        for(int i=0; i<2; i++){
                            for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                        }
                        
                        
                        unflagged(Error_vector, probability, gamma, alpha, beta );
                        
                        
                        
                        
                        
                        //--use unflagged syndrome do error correction---------------------------------------
                        //loading syndorme result to array
                        
                        for (int i=0; i<8; i++){
                            syndrome_result_pt1_f2[i] = Error_vector[0][i+20];
                        }
                        for (int i=0; i<8; i++){
                            syndrome_result_pt1_f2[i+8] = Error_vector[1][i+30];
                        }
                        
                        
                        //compare test1 and symdorme_result array and get index j
                        for (int j=0; j<table_length_pt1_f2; j++){
                            
                            for (int i=0; i<table_width_pt1_f2; i++){
                                test1_pt1_f2[i]=syndrome_pt1_f2[j][i];
                            }
                            // 排除syndrome = 0000的情快
                            //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                            //	break;
                            //}
                            
                            compare_result = memcmp(test1_pt1_f2, syndrome_result_pt1_f2,sizeof(syndrome_result_pt1_f2));
                            
                            if (compare_result == 0) {
                                
                                // table_index = j;
                                
                                //        cout <<  "j= "  << j << endl;
                                //使用recovery進行 x error
                                
                                for (int k=0; k<17; k++){
                                    Error_vector[0][k]= (Error_vector[0][k]+recovery_pt1_f2[j][k])%2;
                                    Error_vector[1][k]= (Error_vector[1][k]+recovery_pt1_f2[j][k+17])%2;
                                }
                                break;
                                
                            }
                            
                        }
                    }  	// 第三次量測 flag rised
                    else {    	// 第三次量測 flag do not rised
                        
                        
                        int s2_result[16] = {0};
                        int s3_result[16] = {0};
                        
                        for (int i=0; i<16; i++){
                            s2_result[i] = syndrome_result_pt1_f1[i+31];
                        }
                        for (int i=0; i<16; i++){
                            s3_result[i] = syndrome_result_pt1_f2[i+31];
                        }
                        
                        compare_result = memcmp(s2_result, s3_result,sizeof(s2_result));
                        
                        if (compare_result == 0){  // s2=s3
                            
                            
                            
                            
                            //compare test1 and symdorme_result array and get index j
                            for (int j=0; j<table_length_pt1_f3; j++){
                                
                                for (int i=0; i<table_width_pt1_f3; i++){
                                    test1_pt1_f3[i]=syndrome_pt1_f3[j][i];
                                }
                                // 排除syndrome = 0000的情快
                                //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                //	break;
                                //}
                                
                                compare_result = memcmp(test1_pt1_f3, syndrome_result_pt1_f3,sizeof(syndrome_result_pt1_f3));
                                
                                if (compare_result == 0) {
                                    
                                    // table_index = j;
                                    
                                    //        cout <<  "j= "  << j << endl;
                                    //使用recovery進行 x error
                                    
                                    for (int k=0; k<17; k++){
                                        Error_vector[0][k]= (Error_vector[0][k]+recovery_pt1_f3[j][k])%2;
                                        Error_vector[1][k]= (Error_vector[1][k]+recovery_pt1_f3[j][k+17])%2;
                                    }
                                    
                                    break;
                                    
                                }
                                
                            }
                            
                            
                        }
                        
                        else {  //s2 unequal s3
                            
                            
                            for(int i=0; i<2; i++){
                                for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                            }
                            
                            
                            unflagged(Error_vector, probability, gamma, alpha, beta );
                            
                            
                            
                            
                            //--use unflagged syndrome do error correction---------------------------------------
                            //-----------------------------------------
                            //loading syndorme result to array
                            
                            for (int i=0; i<8; i++){
                                syndrome_result_pt1_f4[i] = Error_vector[0][i+20];
                            }
                            for (int i=0; i<8; i++){
                                syndrome_result_pt1_f4[i+8] = Error_vector[1][i+30];
                            }
                            
                            
                            //compare test1 and symdorme_result array and get index j
                            for (int j=0; j<table_length_pt1_f4; j++){
                                
                                for (int i=0; i<table_width_pt1_f4; i++){
                                    test1_pt1_f4[i]=syndrome_pt1_f4[j][i];
                                }
                                // 排除syndrome = 0000的情快
                                //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                //	break;
                                //}
                                
                                compare_result = memcmp(test1_pt1_f4, syndrome_result_pt1_f4,sizeof(syndrome_result_pt1_f4));
                                
                                if (compare_result == 0) {
                                    
                                    table_index = j;
                                    
                                    //        cout <<  "j= "  << j << endl;
                                    //使用recovery進行 x error
                                    
                                    for (int k=0; k<17; k++){
                                        Error_vector[0][k]= (Error_vector[0][k]+recovery_pt1_f4[j][k])%2;
                                        Error_vector[1][k]= (Error_vector[1][k]+recovery_pt1_f4[j][k+17])%2;
                                    }
                                    break;
                                    
                                }
                                
                            }
                            
                            
                            
                            
                        } //s2 unequal s3
                        
                        
                        
                        
                    } // 第三次量測 flag do not rised
                    
                    
                    
                }     // 第二次量測 else if
                
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                
                
            } // 第一次flag rised   if ( Error_vector[1][40] !=0    )
            
            //--------------------------------------------------------------------------------------------------
            //--------------------------------------------------------------------------------------------------
            //--------------------------------------------------------------------------------------------------
            
            else if ( Error_vector[0][20] !=0 || Error_vector[0][21] !=0 || Error_vector[0][22] !=0 || Error_vector[0][23] !=0 || Error_vector[0][24] !=0 || Error_vector[0][25] !=0 || Error_vector[0][26] !=0 || Error_vector[0][27] !=0  ) {
                
                
                
                
                for(int i=0; i<2; i++){
                    for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                }
                
                
                parallel_flag(Error_vector, probability, gamma, alpha, beta );
                
                //Z-type stabilizer
                syndrome_result_pt1_m1[31] = Error_vector[0][20];  //m1
                syndrome_result_pt1_m1[32] = Error_vector[0][21];  //m2
                syndrome_result_pt1_m1[33] = Error_vector[0][22];  //m3
                syndrome_result_pt1_m1[34] = Error_vector[0][23];  //m4
                syndrome_result_pt1_m1[35] = Error_vector[0][24];  //m5
                syndrome_result_pt1_m1[36] = Error_vector[0][25];  //m6
                syndrome_result_pt1_m1[37] = Error_vector[0][26];  //m7
                syndrome_result_pt1_m1[38] = Error_vector[0][27];  //m8
                
                //X-type stabilizer
                syndrome_result_pt1_m1[39] = Error_vector[1][30];  //m9
                syndrome_result_pt1_m1[40] = Error_vector[1][31];  //m10
                syndrome_result_pt1_m1[41] = Error_vector[1][32];  //m11
                syndrome_result_pt1_m1[42] = Error_vector[1][33];  //m12
                syndrome_result_pt1_m1[43] = Error_vector[1][34];  //m13
                syndrome_result_pt1_m1[44] = Error_vector[1][35];  //m14
                syndrome_result_pt1_m1[45] = Error_vector[1][36];  //m15
                syndrome_result_pt1_m1[46] = Error_vector[1][37];  //m16
                
                //Z-type flag
                
                syndrome_result_pt1_m1[47] = Error_vector[1][40];  //f1
                syndrome_result_pt1_m1[48] = Error_vector[1][41];  //f2
                syndrome_result_pt1_m1[49] = Error_vector[1][42];  //f3
                syndrome_result_pt1_m1[50] = Error_vector[1][43];  //f4
                syndrome_result_pt1_m1[51] = Error_vector[1][44];  //f5
                syndrome_result_pt1_m1[52] = Error_vector[1][45];  //f6
                syndrome_result_pt1_m1[53] = Error_vector[1][46];  //f7
                
                //X-type  flag
                syndrome_result_pt1_m1[54] = Error_vector[0][50];  //f1
                syndrome_result_pt1_m1[55] = Error_vector[0][51];  //f2
                syndrome_result_pt1_m1[56] = Error_vector[0][52];  //f3
                syndrome_result_pt1_m1[57] = Error_vector[0][53];  //f4
                syndrome_result_pt1_m1[58] = Error_vector[0][54];  //f5
                syndrome_result_pt1_m1[59] = Error_vector[0][55];  //f6
                syndrome_result_pt1_m1[60] = Error_vector[0][56];  //f7
                
                
                //Z-type stabilizer
                syndrome_result_pt1_m4[31] = Error_vector[0][20];  //m1
                syndrome_result_pt1_m4[32] = Error_vector[0][21];  //m2
                syndrome_result_pt1_m4[33] = Error_vector[0][22];  //m3
                syndrome_result_pt1_m4[34] = Error_vector[0][23];  //m4
                syndrome_result_pt1_m4[35] = Error_vector[0][24];  //m5
                syndrome_result_pt1_m4[36] = Error_vector[0][25];  //m6
                syndrome_result_pt1_m4[37] = Error_vector[0][26];  //m7
                syndrome_result_pt1_m4[38] = Error_vector[0][27];  //m8
                
                //X-type stabilizer
                syndrome_result_pt1_m4[39] = Error_vector[1][30];  //m9
                syndrome_result_pt1_m4[40] = Error_vector[1][31];  //m10
                syndrome_result_pt1_m4[41] = Error_vector[1][32];  //m11
                syndrome_result_pt1_m4[42] = Error_vector[1][33];  //m12
                syndrome_result_pt1_m4[43] = Error_vector[1][34];  //m13
                syndrome_result_pt1_m4[44] = Error_vector[1][35];  //m14
                syndrome_result_pt1_m4[45] = Error_vector[1][36];  //m15
                syndrome_result_pt1_m4[46] = Error_vector[1][37];  //m16
                
                
                
                
                int flag_result = 0;
                
                for (int i=0; i<7; i++){
                    flag_result = flag_result + Error_vector[1][40+i] +  Error_vector[0][50+i]  ;
                }
                
                
                if ( flag_result != 0){
                    
                    
                    
                    for(int i=0; i<2; i++){
                        for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    
                    unflagged(Error_vector, probability, gamma, alpha, beta );
                    
                    
                    
                    
                    //--use unflagged syndrome do error correction---------------------------------------
                    //-----------------------------------------
                    //loading syndorme result to array
                    
                    for (int i=0; i<8; i++){
                        syndrome_result_pt1_m1[i] = Error_vector[0][i+20];
                    }
                    for (int i=0; i<8; i++){
                        syndrome_result_pt1_m1[i+8] = Error_vector[1][i+30];
                    }
                    
                    
                    //compare test1 and symdorme_result array and get index j
                    for (int j=0; j<table_length_pt1_m1; j++){
                        
                        for (int i=0; i<table_width_pt1_m1; i++){
                            test1_pt1_m1[i]=syndrome_pt1_m1[j][i];
                        }
                        // 排除syndrome = 0000的情快
                        //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                        //	break;
                        //}
                        
                        compare_result = memcmp(test1_pt1_m1, syndrome_result_pt1_m1,sizeof(syndrome_result_pt1_m1));
                        
                        if (compare_result == 0) {
                            
                            table_index = j;
                            
                            //        cout <<  "j= "  << j << endl;
                            //使用recovery進行 x error
                            
                            for (int k=0; k<17; k++){
                                Error_vector[0][k]= (Error_vector[0][k]+recovery_pt1_m1[j][k])%2;
                                Error_vector[1][k]= (Error_vector[1][k]+recovery_pt1_m1[j][k+17])%2;
                            }
                            break;
                            
                        }
                        
                    }
                    
                }   //  第二次量測 flag rised
                
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                
                else {
                    
                    
                    for(int i=0; i<2; i++){
                        for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    
                    parallel_flag(Error_vector, probability, gamma, alpha, beta );
                    
                    //Z-type stabilizer
                    syndrome_result_pt1_m2[31] = Error_vector[0][20];  //m1
                    syndrome_result_pt1_m2[32] = Error_vector[0][21];  //m2
                    syndrome_result_pt1_m2[33] = Error_vector[0][22];  //m3
                    syndrome_result_pt1_m2[34] = Error_vector[0][23];  //m4
                    syndrome_result_pt1_m2[35] = Error_vector[0][24];  //m5
                    syndrome_result_pt1_m2[36] = Error_vector[0][25];  //m6
                    syndrome_result_pt1_m2[37] = Error_vector[0][26];  //m7
                    syndrome_result_pt1_m2[38] = Error_vector[0][27];  //m8
                    
                    //X-type stabilizer
                    syndrome_result_pt1_m2[39] = Error_vector[1][30];  //m9
                    syndrome_result_pt1_m2[40] = Error_vector[1][31];  //m10
                    syndrome_result_pt1_m2[41] = Error_vector[1][32];  //m11
                    syndrome_result_pt1_m2[42] = Error_vector[1][33];  //m12
                    syndrome_result_pt1_m2[43] = Error_vector[1][34];  //m13
                    syndrome_result_pt1_m2[44] = Error_vector[1][35];  //m14
                    syndrome_result_pt1_m2[45] = Error_vector[1][36];  //m15
                    syndrome_result_pt1_m2[46] = Error_vector[1][37];  //m16
                    
                    //Z-type flag
                    
                    syndrome_result_pt1_m2[47] = Error_vector[1][40];  //f1
                    syndrome_result_pt1_m2[48] = Error_vector[1][41];  //f2
                    syndrome_result_pt1_m2[49] = Error_vector[1][42];  //f3
                    syndrome_result_pt1_m2[50] = Error_vector[1][43];  //f4
                    syndrome_result_pt1_m2[51] = Error_vector[1][44];  //f5
                    syndrome_result_pt1_m2[52] = Error_vector[1][45];  //f6
                    syndrome_result_pt1_m2[53] = Error_vector[1][46];  //f7
                    
                    //X-type  flag
                    syndrome_result_pt1_m2[54] = Error_vector[0][50];  //f1
                    syndrome_result_pt1_m2[55] = Error_vector[0][51];  //f2
                    syndrome_result_pt1_m2[56] = Error_vector[0][52];  //f3
                    syndrome_result_pt1_m2[57] = Error_vector[0][53];  //f4
                    syndrome_result_pt1_m2[58] = Error_vector[0][54];  //f5
                    syndrome_result_pt1_m2[59] = Error_vector[0][55];  //f6
                    syndrome_result_pt1_m2[60] = Error_vector[0][56];  //f7
                    
                    //Z-type stabilizer
                    syndrome_result_pt1_m3[15] = Error_vector[0][20];  //m1
                    syndrome_result_pt1_m3[16] = Error_vector[0][21];  //m2
                    syndrome_result_pt1_m3[17] = Error_vector[0][22];  //m3
                    syndrome_result_pt1_m3[18] = Error_vector[0][23];  //m4
                    syndrome_result_pt1_m3[19] = Error_vector[0][24];  //m5
                    syndrome_result_pt1_m3[20] = Error_vector[0][25];  //m6
                    syndrome_result_pt1_m3[21] = Error_vector[0][26];  //m7
                    syndrome_result_pt1_m3[22] = Error_vector[0][27];  //m8
                    
                    //X-type stabilizer
                    syndrome_result_pt1_m3[23] = Error_vector[1][30];  //m9
                    syndrome_result_pt1_m3[24] = Error_vector[1][31];  //m10
                    syndrome_result_pt1_m3[25] = Error_vector[1][32];  //m11
                    syndrome_result_pt1_m3[26] = Error_vector[1][33];  //m12
                    syndrome_result_pt1_m3[27] = Error_vector[1][34];  //m13
                    syndrome_result_pt1_m3[28] = Error_vector[1][35];  //m14
                    syndrome_result_pt1_m3[29] = Error_vector[1][36];  //m15
                    syndrome_result_pt1_m3[30] = Error_vector[1][37];  //m16
                    
                    //Z-type flag
                    
                    syndrome_result_pt1_m3[31] = Error_vector[1][40];  //f1
                    syndrome_result_pt1_m3[32] = Error_vector[1][41];  //f2
                    syndrome_result_pt1_m3[33] = Error_vector[1][42];  //f3
                    syndrome_result_pt1_m3[34] = Error_vector[1][43];  //f4
                    syndrome_result_pt1_m3[35] = Error_vector[1][44];  //f5
                    syndrome_result_pt1_m3[36] = Error_vector[1][45];  //f6
                    syndrome_result_pt1_m3[37] = Error_vector[1][46];  //f7
                    
                    //X-type  flag
                    syndrome_result_pt1_m3[38] = Error_vector[0][50];  //f1
                    syndrome_result_pt1_m3[39] = Error_vector[0][51];  //f2
                    syndrome_result_pt1_m3[40] = Error_vector[0][52];  //f3
                    syndrome_result_pt1_m3[41] = Error_vector[0][53];  //f4
                    syndrome_result_pt1_m3[42] = Error_vector[0][54];  //f5
                    syndrome_result_pt1_m3[43] = Error_vector[0][55];  //f6
                    syndrome_result_pt1_m3[44] = Error_vector[0][56];  //f7
                    
                    //Z-type stabilizer
                    syndrome_result_pt1_m4[47] = Error_vector[0][20];  //m1
                    syndrome_result_pt1_m4[48] = Error_vector[0][21];  //m2
                    syndrome_result_pt1_m4[49] = Error_vector[0][22];  //m3
                    syndrome_result_pt1_m4[50] = Error_vector[0][23];  //m4
                    syndrome_result_pt1_m4[51] = Error_vector[0][24];  //m5
                    syndrome_result_pt1_m4[52] = Error_vector[0][25];  //m6
                    syndrome_result_pt1_m4[53] = Error_vector[0][26];  //m7
                    syndrome_result_pt1_m4[54] = Error_vector[0][27];  //m8
                    
                    //X-type stabilizer
                    syndrome_result_pt1_m4[55] = Error_vector[1][30];  //m9
                    syndrome_result_pt1_m4[56] = Error_vector[1][31];  //m10
                    syndrome_result_pt1_m4[57] = Error_vector[1][32];  //m11
                    syndrome_result_pt1_m4[58] = Error_vector[1][33];  //m12
                    syndrome_result_pt1_m4[59] = Error_vector[1][34];  //m13
                    syndrome_result_pt1_m4[60] = Error_vector[1][35];  //m14
                    syndrome_result_pt1_m4[61] = Error_vector[1][36];  //m15
                    syndrome_result_pt1_m4[62] = Error_vector[1][37];  //m16
                    
                    
                    
                    flag_result = 0;
                    
                    for (int i=0; i<7; i++){
                        flag_result = flag_result + Error_vector[1][40+i] + Error_vector[0][50+i] ;
                    }
                    
                    
                    if ( flag_result != 0){   	// 第三次量測 flag rised
                        
                        
                        for(int i=0; i<2; i++){
                            for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                        }
                        
                        
                        unflagged(Error_vector, probability, gamma, alpha, beta );
                        
                        
                        
                        
                        
                        
                        //--use unflagged syndrome do error correction---------------------------------------
                        //-----------------------------------------
                        //loading syndorme result to array
                        
                        for (int i=0; i<8; i++){
                            syndrome_result_pt1_m2[i] = Error_vector[0][i+20];
                        }
                        for (int i=0; i<8; i++){
                            syndrome_result_pt1_m2[i+8] = Error_vector[1][i+30];
                        }
                        
                        
                        //compare test1 and symdorme_result array and get index j
                        for (int j=0; j<table_length_pt1_m2; j++){
                            
                            for (int i=0; i<table_width_pt1_m2; i++){
                                test1_pt1_m2[i]=syndrome_pt1_m2[j][i];
                            }
                            // 排除syndrome = 0000的情快
                            //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                            //	break;
                            //}
                            
                            compare_result = memcmp(test1_pt1_m2, syndrome_result_pt1_m2,sizeof(syndrome_result_pt1_m2));
                            
                            if (compare_result == 0) {
                                
                                table_index = j;
                                
                                //        cout <<  "j= "  << j << endl;
                                //使用recovery進行 x error
                                
                                for (int k=0; k<17; k++){
                                    Error_vector[0][k]= (Error_vector[0][k]+recovery_pt1_m2[j][k])%2;
                                    Error_vector[1][k]= (Error_vector[1][k]+recovery_pt1_m2[j][k+17])%2;
                                }
                                break;
                                
                            }
                            
                        }
                    }  	// 第三次量測 flag rised
                    else {    	// 第三次量測 flag do not rised
                        
                        
                        int s2_result[16] = {0};
                        int s3_result[16] = {0};
                        
                        for (int i=0; i<16; i++){
                            s2_result[i] = syndrome_result_pt1_m1[i+31];
                        }
                        for (int i=0; i<16; i++){
                            s3_result[i] = syndrome_result_pt1_m2[i+31];
                        }
                        
                        compare_result = memcmp(s2_result, s3_result,sizeof(s2_result));
                        
                        if (compare_result == 0){  // s2=s3
                            
                            
                            
                            //compare test1 and symdorme_result array and get index j
                            for (int j=0; j<table_length_pt1_m3; j++){
                                
                                for (int i=0; i<table_width_pt1_m3; i++){
                                    test1_pt1_m3[i]=syndrome_pt1_m3[j][i];
                                }
                                // 排除syndrome = 0000的情快
                                //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                //	break;
                                //}
                                
                                compare_result = memcmp(test1_pt1_m3, syndrome_result_pt1_m3,sizeof(syndrome_result_pt1_m3));
                                
                                if (compare_result == 0) {
                                    
                                    table_index = j;
                                    
                                    //        cout <<  "j= "  << j << endl;
                                    //使用recovery進行 x error
                                    
                                    for (int k=0; k<17; k++){
                                        Error_vector[0][k]= (Error_vector[0][k]+recovery_pt1_m3[j][k])%2;
                                        Error_vector[1][k]= (Error_vector[1][k]+recovery_pt1_m3[j][k+17])%2;
                                    }
                                    break;
                                    
                                }
                                
                            }
                            
                            
                        }
                        
                        else {  //s2 unequal s3
                            
                            
                            for(int i=0; i<2; i++){
                                for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                            }
                            
                            
                            unflagged(Error_vector, probability, gamma, alpha, beta );
                            
                            
                            
                            
                            
                            //--use unflagged syndrome do error correction---------------------------------------
                            //-----------------------------------------
                            //loading syndorme result to array
                            
                            for (int i=0; i<8; i++){
                                syndrome_result_pt1_m4[i] = Error_vector[0][i+20];
                            }
                            for (int i=0; i<8; i++){
                                syndrome_result_pt1_m4[i+8] = Error_vector[1][i+30];
                            }
                            
                            
                            //compare test1 and symdorme_result array and get index j
                            for (int j=0; j<table_length_pt1_m4; j++){
                                
                                for (int i=0; i<table_width_pt1_m4; i++){
                                    test1_pt1_m4[i]=syndrome_pt1_m4[j][i];
                                }
                                // 排除syndrome = 0000的情快
                                //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                //	break;
                                //}
                                
                                compare_result = memcmp(test1_pt1_m4, syndrome_result_pt1_m4,sizeof(syndrome_result_pt1_m4));
                                
                                if (compare_result == 0) {
                                    
                                    table_index = j;
                                    
                                    //        cout <<  "j= "  << j << endl;
                                    //使用recovery進行 x error
                                    
                                    for (int k=0; k<17; k++){
                                        Error_vector[0][k]= (Error_vector[0][k]+recovery_pt1_m4[j][k])%2;
                                        Error_vector[1][k]= (Error_vector[1][k]+recovery_pt1_m4[j][k+17])%2;
                                    }
                                    break;
                                    
                                }
                                
                            }
                            
                            
                            
                            
                        } //s2 unequal s3
                        
                        
                        
                        
                    } // 第三次量測 flag do not rised
                    
                    
                    
                }     // 第二次量測 else if
                
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                
                
                
                
            } // 第一次量測 的 else if ( Error_vector[0][20] !=0 || Error_vector[0][21] !=0  )
            
            
            
            outpoint1:
                
                
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
                
                for(int i=0; i<2; i++){
                    for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                }
                
                
                pt2_circuit(Error_vector, probability, gamma, alpha, beta );
                
                if  (  Error_vector[0][40] ==0   && Error_vector[0][41] ==0 && Error_vector[0][42] ==0 && Error_vector[0][43] ==0  && Error_vector[0][44] ==0  && Error_vector[0][45] ==0  && Error_vector[0][46] ==0 && Error_vector[1][20] ==0 && Error_vector[1][21] ==0 && Error_vector[1][22] ==0 && Error_vector[1][23] ==0 && Error_vector[1][24] ==0 && Error_vector[1][25] ==0 && Error_vector[1][26] ==0 && Error_vector[1][27] ==0    ){
                    goto outpoint2;
                }
                
                syndrome_result_pt2_f1[16] = Error_vector[1][20];  //m1
                syndrome_result_pt2_f1[17] = Error_vector[1][21];  //m2
                syndrome_result_pt2_f1[18] = Error_vector[1][22];  //m3
                syndrome_result_pt2_f1[19] = Error_vector[1][23];  //m4
                syndrome_result_pt2_f1[20] = Error_vector[1][24];  //m5
                syndrome_result_pt2_f1[21] = Error_vector[1][25];  //m6
                syndrome_result_pt2_f1[22] = Error_vector[1][26];  //m7
                syndrome_result_pt2_f1[23] = Error_vector[1][27];  //m8
                syndrome_result_pt2_f1[24] = Error_vector[0][40];  //f1
                syndrome_result_pt2_f1[25] = Error_vector[0][41];  //f2
                syndrome_result_pt2_f1[26] = Error_vector[0][42];  //f3
                syndrome_result_pt2_f1[27] = Error_vector[0][43];  //f4
                syndrome_result_pt2_f1[28] = Error_vector[0][44];  //f5
                syndrome_result_pt2_f1[29] = Error_vector[0][45];  //f6
                syndrome_result_pt2_f1[30] = Error_vector[0][46];  //f7
                
                syndrome_result_pt2_f2[16] = Error_vector[1][20];  //m1
                syndrome_result_pt2_f2[17] = Error_vector[1][21];  //m2
                syndrome_result_pt2_f2[18] = Error_vector[1][22];  //m3
                syndrome_result_pt2_f2[19] = Error_vector[1][23];  //m4
                syndrome_result_pt2_f2[20] = Error_vector[1][24];  //m5
                syndrome_result_pt2_f2[21] = Error_vector[1][25];  //m6
                syndrome_result_pt2_f2[22] = Error_vector[1][26];  //m7
                syndrome_result_pt2_f2[23] = Error_vector[1][27];  //m8
                syndrome_result_pt2_f2[24] = Error_vector[0][40];  //f1
                syndrome_result_pt2_f2[25] = Error_vector[0][41];  //f2
                syndrome_result_pt2_f2[26] = Error_vector[0][42];  //f3
                syndrome_result_pt2_f2[27] = Error_vector[0][43];  //f4
                syndrome_result_pt2_f2[28] = Error_vector[0][44];  //f5
                syndrome_result_pt2_f2[29] = Error_vector[0][45];  //f6
                syndrome_result_pt2_f2[30] = Error_vector[0][46];  //f7
                
                syndrome_result_pt2_f3[0] = Error_vector[1][20];  //m1
                syndrome_result_pt2_f3[1] = Error_vector[1][21];  //m2
                syndrome_result_pt2_f3[2] = Error_vector[1][22];  //m3
                syndrome_result_pt2_f3[3] = Error_vector[1][23];  //m4
                syndrome_result_pt2_f3[4] = Error_vector[1][24];  //m5
                syndrome_result_pt2_f3[5] = Error_vector[1][25];  //m6
                syndrome_result_pt2_f3[6] = Error_vector[1][26];  //m7
                syndrome_result_pt2_f3[7] = Error_vector[1][27];  //m8
                syndrome_result_pt2_f3[8] = Error_vector[0][40];  //f1
                syndrome_result_pt2_f3[9] = Error_vector[0][41];  //f2
                syndrome_result_pt2_f3[10] = Error_vector[0][42];  //f3
                syndrome_result_pt2_f3[11] = Error_vector[0][43];  //f4
                syndrome_result_pt2_f3[12] = Error_vector[0][44];  //f5
                syndrome_result_pt2_f3[13] = Error_vector[0][45];  //f6
                syndrome_result_pt2_f3[14] = Error_vector[0][46];  //f7
                
                syndrome_result_pt2_f4[16] = Error_vector[1][20];  //m1
                syndrome_result_pt2_f4[17] = Error_vector[1][21];  //m2
                syndrome_result_pt2_f4[18] = Error_vector[1][22];  //m3
                syndrome_result_pt2_f4[19] = Error_vector[1][23];  //m4
                syndrome_result_pt2_f4[20] = Error_vector[1][24];  //m5
                syndrome_result_pt2_f4[21] = Error_vector[1][25];  //m6
                syndrome_result_pt2_f4[22] = Error_vector[1][26];  //m7
                syndrome_result_pt2_f4[23] = Error_vector[1][27];  //m8
                syndrome_result_pt2_f4[24] = Error_vector[0][40];  //f1
                syndrome_result_pt2_f4[25] = Error_vector[0][41];  //f2
                syndrome_result_pt2_f4[26] = Error_vector[0][42];  //f3
                syndrome_result_pt2_f4[27] = Error_vector[0][43];  //f4
                syndrome_result_pt2_f4[28] = Error_vector[0][44];  //f5
                syndrome_result_pt2_f4[29] = Error_vector[0][45];  //f6
                syndrome_result_pt2_f4[30] = Error_vector[0][46];  //f7
                
                syndrome_result_pt2_m1[16] = Error_vector[1][20];  //m1
                syndrome_result_pt2_m1[17] = Error_vector[1][21];  //m2
                syndrome_result_pt2_m1[18] = Error_vector[1][22];  //m3
                syndrome_result_pt2_m1[19] = Error_vector[1][23];  //m4
                syndrome_result_pt2_m1[20] = Error_vector[1][24];  //m5
                syndrome_result_pt2_m1[21] = Error_vector[1][25];  //m6
                syndrome_result_pt2_m1[22] = Error_vector[1][26];  //m7
                syndrome_result_pt2_m1[23] = Error_vector[1][27];  //m8
                syndrome_result_pt2_m1[24] = Error_vector[0][40];  //f1
                syndrome_result_pt2_m1[25] = Error_vector[0][41];  //f2
                syndrome_result_pt2_m1[26] = Error_vector[0][42];  //f3
                syndrome_result_pt2_m1[27] = Error_vector[0][43];  //f4
                syndrome_result_pt2_m1[28] = Error_vector[0][44];  //f5
                syndrome_result_pt2_m1[29] = Error_vector[0][45];  //f6
                syndrome_result_pt2_m1[30] = Error_vector[0][46];  //f7
                
                syndrome_result_pt2_m2[16] = Error_vector[1][20];  //m1
                syndrome_result_pt2_m2[17] = Error_vector[1][21];  //m2
                syndrome_result_pt2_m2[18] = Error_vector[1][22];  //m3
                syndrome_result_pt2_m2[19] = Error_vector[1][23];  //m4
                syndrome_result_pt2_m2[20] = Error_vector[1][24];  //m5
                syndrome_result_pt2_m2[21] = Error_vector[1][25];  //m6
                syndrome_result_pt2_m2[22] = Error_vector[1][26];  //m7
                syndrome_result_pt2_m2[23] = Error_vector[1][27];  //m8
                syndrome_result_pt2_m2[24] = Error_vector[0][40];  //f1
                syndrome_result_pt2_m2[25] = Error_vector[0][41];  //f2
                syndrome_result_pt2_m2[26] = Error_vector[0][42];  //f3
                syndrome_result_pt2_m2[27] = Error_vector[0][43];  //f4
                syndrome_result_pt2_m2[28] = Error_vector[0][44];  //f5
                syndrome_result_pt2_m2[29] = Error_vector[0][45];  //f6
                syndrome_result_pt2_m2[30] = Error_vector[0][46];  //f7
                
                syndrome_result_pt2_m3[0] = Error_vector[1][20];  //m1
                syndrome_result_pt2_m3[1] = Error_vector[1][21];  //m2
                syndrome_result_pt2_m3[2] = Error_vector[1][22];  //m3
                syndrome_result_pt2_m3[3] = Error_vector[1][23];  //m4
                syndrome_result_pt2_m3[4] = Error_vector[1][24];  //m5
                syndrome_result_pt2_m3[5] = Error_vector[1][25];  //m6
                syndrome_result_pt2_m3[6] = Error_vector[1][26];  //m7
                syndrome_result_pt2_m3[7] = Error_vector[1][27];  //m8
                syndrome_result_pt2_m3[8] = Error_vector[0][40];  //f1
                syndrome_result_pt2_m3[9] = Error_vector[0][41];  //f2
                syndrome_result_pt2_m3[10] = Error_vector[0][42];  //f3
                syndrome_result_pt2_m3[11] = Error_vector[0][43];  //f4
                syndrome_result_pt2_m3[12] = Error_vector[0][44];  //f5
                syndrome_result_pt2_m3[13] = Error_vector[0][45];  //f6
                syndrome_result_pt2_m3[14] = Error_vector[0][46];  //f7
                
                
                syndrome_result_pt2_m4[16] = Error_vector[1][20];  //m1
                syndrome_result_pt2_m4[17] = Error_vector[1][21];  //m2
                syndrome_result_pt2_m4[18] = Error_vector[1][22];  //m3
                syndrome_result_pt2_m4[19] = Error_vector[1][23];  //m4
                syndrome_result_pt2_m4[20] = Error_vector[1][24];  //m5
                syndrome_result_pt2_m4[21] = Error_vector[1][25];  //m6
                syndrome_result_pt2_m4[22] = Error_vector[1][26];  //m7
                syndrome_result_pt2_m4[23] = Error_vector[1][27];  //m8
                syndrome_result_pt2_m4[24] = Error_vector[0][40];  //f1
                syndrome_result_pt2_m4[25] = Error_vector[0][41];  //f2
                syndrome_result_pt2_m4[26] = Error_vector[0][42];  //f3
                syndrome_result_pt2_m4[27] = Error_vector[0][43];  //f4
                syndrome_result_pt2_m4[28] = Error_vector[0][44];  //f5
                syndrome_result_pt2_m4[29] = Error_vector[0][45];  //f6
                syndrome_result_pt2_m4[30] = Error_vector[0][46];  //f7
                
                
                
                if (   ( Error_vector[0][40] !=0  || Error_vector[0][41] !=0 || Error_vector[0][42] !=0 || Error_vector[0][43] !=0  || Error_vector[0][44] !=0  || Error_vector[0][45] !=0 || Error_vector[0][46] !=0 )   ){
                    
                    
                    
                    
                    for(int i=0; i<2; i++){
                        for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    
                    parallel_flag(Error_vector, probability, gamma, alpha, beta );
                    
                    
                    syndrome_result_pt2_f1[31] = Error_vector[0][20];  //m1
                    syndrome_result_pt2_f1[32] = Error_vector[0][21];  //m2
                    syndrome_result_pt2_f1[33] = Error_vector[0][22];  //m3
                    syndrome_result_pt2_f1[34] = Error_vector[0][23];  //m4
                    syndrome_result_pt2_f1[35] = Error_vector[0][24];  //m5
                    syndrome_result_pt2_f1[36] = Error_vector[0][25];  //m6
                    syndrome_result_pt2_f1[37] = Error_vector[0][26];  //m7
                    syndrome_result_pt2_f1[38] = Error_vector[0][27];  //m8
                    
                    //X-type stabilizer
                    syndrome_result_pt2_f1[39] = Error_vector[1][30];  //m9
                    syndrome_result_pt2_f1[40] = Error_vector[1][31];  //m10
                    syndrome_result_pt2_f1[41] = Error_vector[1][32];  //m11
                    syndrome_result_pt2_f1[42] = Error_vector[1][33];  //m12
                    syndrome_result_pt2_f1[43] = Error_vector[1][34];  //m13
                    syndrome_result_pt2_f1[44] = Error_vector[1][35];  //m14
                    syndrome_result_pt2_f1[45] = Error_vector[1][36];  //m15
                    syndrome_result_pt2_f1[46] = Error_vector[1][37];  //m16
                    
                    //Z-type flag
                    
                    syndrome_result_pt2_f1[47] = Error_vector[1][40];  //f1
                    syndrome_result_pt2_f1[48] = Error_vector[1][41];  //f2
                    syndrome_result_pt2_f1[49] = Error_vector[1][42];  //f3
                    syndrome_result_pt2_f1[50] = Error_vector[1][43];  //f4
                    syndrome_result_pt2_f1[51] = Error_vector[1][44];  //f5
                    syndrome_result_pt2_f1[52] = Error_vector[1][45];  //f6
                    syndrome_result_pt2_f1[53] = Error_vector[1][46];  //f7
                    
                    //X-type  flag
                    syndrome_result_pt2_f1[54] = Error_vector[0][50];  //f1
                    syndrome_result_pt2_f1[55] = Error_vector[0][51];  //f2
                    syndrome_result_pt2_f1[56] = Error_vector[0][52];  //f3
                    syndrome_result_pt2_f1[57] = Error_vector[0][53];  //f4
                    syndrome_result_pt2_f1[58] = Error_vector[0][54];  //f5
                    syndrome_result_pt2_f1[59] = Error_vector[0][55];  //f6
                    syndrome_result_pt2_f1[60] = Error_vector[0][56];  //f7
                    
                    //Z-type stabilizer
                    syndrome_result_pt2_f4[31] = Error_vector[0][20];  //m1
                    syndrome_result_pt2_f4[32] = Error_vector[0][21];  //m2
                    syndrome_result_pt2_f4[33] = Error_vector[0][22];  //m3
                    syndrome_result_pt2_f4[34] = Error_vector[0][23];  //m4
                    syndrome_result_pt2_f4[35] = Error_vector[0][24];  //m5
                    syndrome_result_pt2_f4[36] = Error_vector[0][25];  //m6
                    syndrome_result_pt2_f4[37] = Error_vector[0][26];  //m7
                    syndrome_result_pt2_f4[38] = Error_vector[0][27];  //m8
                    
                    //X-type stabilizer
                    syndrome_result_pt2_f4[39] = Error_vector[1][30];  //m9
                    syndrome_result_pt2_f4[40] = Error_vector[1][31];  //m10
                    syndrome_result_pt2_f4[41] = Error_vector[1][32];  //m11
                    syndrome_result_pt2_f4[42] = Error_vector[1][33];  //m12
                    syndrome_result_pt2_f4[43] = Error_vector[1][34];  //m13
                    syndrome_result_pt2_f4[44] = Error_vector[1][35];  //m14
                    syndrome_result_pt2_f4[45] = Error_vector[1][36];  //m15
                    syndrome_result_pt2_f4[46] = Error_vector[1][37];  //m16
                    
                    
                    
                    int flag_result = 0;
                    
                    for (int i=0; i<7; i++){
                        flag_result = flag_result + Error_vector[1][40+i] +  Error_vector[0][50+i]  ;
                    }
                    
                    
                    if ( flag_result != 0){
                        
                        
                        
                        for(int i=0; i<2; i++){
                            for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                        }
                        
                        
                        unflagged(Error_vector, probability, gamma, alpha, beta );
                        
                        
                        
                        
                        //--use unflagged syndrome do error correction---------------------------------------
                        //-----------------------------------------
                        //loading syndorme result to array
                        
                        for (int i=0; i<8; i++){
                            syndrome_result_pt2_f1[i] = Error_vector[0][i+20];
                        }
                        for (int i=0; i<8; i++){
                            syndrome_result_pt2_f1[i+8] = Error_vector[1][i+30];
                        }
                        
                        
                        //compare test1 and symdorme_result array and get index j
                        for (int j=0; j<table_length_pt2_f1; j++){
                            
                            for (int i=0; i<table_width_pt2_f1; i++){
                                test1_pt2_f1[i]=syndrome_pt2_f1[j][i];
                            }
                            // 排除syndrome = 0000的情快
                            //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                            //	break;
                            //}
                            
                            compare_result = memcmp(test1_pt2_f1, syndrome_result_pt2_f1,sizeof(syndrome_result_pt2_f1));
                            
                            if (compare_result == 0) {
                                
                                // table_index = j;
                                
                                //        cout <<  "j= "  << j << endl;
                                //使用recovery進行 x error
                                
                                for (int k=0; k<17; k++){
                                    Error_vector[0][k]= (Error_vector[0][k]+recovery_pt2_f1[j][k])%2;
                                    Error_vector[1][k]= (Error_vector[1][k]+recovery_pt2_f1[j][k+17])%2;
                                }
                                break;
                                
                            }
                            
                        }
                        
                    }   //  第二次量測 flag rised
                    
                    //--------------------------------------------------------------------------------------------------
                    //--------------------------------------------------------------------------------------------------
                    //--------------------------------------------------------------------------------------------------
                    
                    else {
                        
                        
                        for(int i=0; i<2; i++){
                            for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                        }
                        
                        
                        parallel_flag(Error_vector, probability, gamma, alpha, beta );
                        
                        //Z-type stabilizer
                        syndrome_result_pt2_f2[31] = Error_vector[0][20];  //m1
                        syndrome_result_pt2_f2[32] = Error_vector[0][21];  //m2
                        syndrome_result_pt2_f2[33] = Error_vector[0][22];  //m3
                        syndrome_result_pt2_f2[34] = Error_vector[0][23];  //m4
                        syndrome_result_pt2_f2[35] = Error_vector[0][24];  //m5
                        syndrome_result_pt2_f2[36] = Error_vector[0][25];  //m6
                        syndrome_result_pt2_f2[37] = Error_vector[0][26];  //m7
                        syndrome_result_pt2_f2[38] = Error_vector[0][27];  //m8
                        
                        //X-type stabilizer
                        syndrome_result_pt2_f2[39] = Error_vector[1][30];  //m9
                        syndrome_result_pt2_f2[40] = Error_vector[1][31];  //m10
                        syndrome_result_pt2_f2[41] = Error_vector[1][32];  //m11
                        syndrome_result_pt2_f2[42] = Error_vector[1][33];  //m12
                        syndrome_result_pt2_f2[43] = Error_vector[1][34];  //m13
                        syndrome_result_pt2_f2[44] = Error_vector[1][35];  //m14
                        syndrome_result_pt2_f2[45] = Error_vector[1][36];  //m15
                        syndrome_result_pt2_f2[46] = Error_vector[1][37];  //m16
                        
                        //Z-type flag
                        
                        syndrome_result_pt2_f2[47] = Error_vector[1][40];  //f1
                        syndrome_result_pt2_f2[48] = Error_vector[1][41];  //f2
                        syndrome_result_pt2_f2[49] = Error_vector[1][42];  //f3
                        syndrome_result_pt2_f2[50] = Error_vector[1][43];  //f4
                        syndrome_result_pt2_f2[51] = Error_vector[1][44];  //f5
                        syndrome_result_pt2_f2[52] = Error_vector[1][45];  //f6
                        syndrome_result_pt2_f2[53] = Error_vector[1][46];  //f7
                        
                        //X-type  flag
                        syndrome_result_pt2_f2[54] = Error_vector[0][50];  //f1
                        syndrome_result_pt2_f2[55] = Error_vector[0][51];  //f2
                        syndrome_result_pt2_f2[56] = Error_vector[0][52];  //f3
                        syndrome_result_pt2_f2[57] = Error_vector[0][53];  //f4
                        syndrome_result_pt2_f2[58] = Error_vector[0][54];  //f5
                        syndrome_result_pt2_f2[59] = Error_vector[0][55];  //f6
                        syndrome_result_pt2_f2[60] = Error_vector[0][56];  //f7
                        
                        //Z-type stabilizer
                        syndrome_result_pt2_f3[15] = Error_vector[0][20];  //m1
                        syndrome_result_pt2_f3[16] = Error_vector[0][21];  //m2
                        syndrome_result_pt2_f3[17] = Error_vector[0][22];  //m3
                        syndrome_result_pt2_f3[18] = Error_vector[0][23];  //m4
                        syndrome_result_pt2_f3[19] = Error_vector[0][24];  //m5
                        syndrome_result_pt2_f3[20] = Error_vector[0][25];  //m6
                        syndrome_result_pt2_f3[21] = Error_vector[0][26];  //m7
                        syndrome_result_pt2_f3[22] = Error_vector[0][27];  //m8
                        
                        //X-type stabilizer
                        syndrome_result_pt2_f3[23] = Error_vector[1][30];  //m9
                        syndrome_result_pt2_f3[24] = Error_vector[1][31];  //m10
                        syndrome_result_pt2_f3[25] = Error_vector[1][32];  //m11
                        syndrome_result_pt2_f3[26] = Error_vector[1][33];  //m12
                        syndrome_result_pt2_f3[27] = Error_vector[1][34];  //m13
                        syndrome_result_pt2_f3[28] = Error_vector[1][35];  //m14
                        syndrome_result_pt2_f3[29] = Error_vector[1][36];  //m15
                        syndrome_result_pt2_f3[30] = Error_vector[1][37];  //m16
                        
                        //Z-type flag
                        
                        syndrome_result_pt2_f3[31] = Error_vector[1][40];  //f1
                        syndrome_result_pt2_f3[32] = Error_vector[1][41];  //f2
                        syndrome_result_pt2_f3[33] = Error_vector[1][42];  //f3
                        syndrome_result_pt2_f3[34] = Error_vector[1][43];  //f4
                        syndrome_result_pt2_f3[35] = Error_vector[1][44];  //f5
                        syndrome_result_pt2_f3[36] = Error_vector[1][45];  //f6
                        syndrome_result_pt2_f3[37] = Error_vector[1][46];  //f7
                        
                        //X-type  flag
                        syndrome_result_pt2_f3[38] = Error_vector[0][50];  //f1
                        syndrome_result_pt2_f3[39] = Error_vector[0][51];  //f2
                        syndrome_result_pt2_f3[40] = Error_vector[0][52];  //f3
                        syndrome_result_pt2_f3[41] = Error_vector[0][53];  //f4
                        syndrome_result_pt2_f3[42] = Error_vector[0][54];  //f5
                        syndrome_result_pt2_f3[43] = Error_vector[0][55];  //f6
                        syndrome_result_pt2_f3[44] = Error_vector[0][56];  //f7
                        
                        
                        //Z-type stabilizer
                        syndrome_result_pt2_f4[47] = Error_vector[0][20];  //m1
                        syndrome_result_pt2_f4[48] = Error_vector[0][21];  //m2
                        syndrome_result_pt2_f4[49] = Error_vector[0][22];  //m3
                        syndrome_result_pt2_f4[50] = Error_vector[0][23];  //m4
                        syndrome_result_pt2_f4[51] = Error_vector[0][24];  //m5
                        syndrome_result_pt2_f4[52] = Error_vector[0][25];  //m6
                        syndrome_result_pt2_f4[53] = Error_vector[0][26];  //m7
                        syndrome_result_pt2_f4[54] = Error_vector[0][27];  //m8
                        
                        //X-type stabilizer
                        syndrome_result_pt2_f4[55] = Error_vector[1][30];  //m9
                        syndrome_result_pt2_f4[56] = Error_vector[1][31];  //m10
                        syndrome_result_pt2_f4[57] = Error_vector[1][32];  //m11
                        syndrome_result_pt2_f4[58] = Error_vector[1][33];  //m12
                        syndrome_result_pt2_f4[59] = Error_vector[1][34];  //m13
                        syndrome_result_pt2_f4[60] = Error_vector[1][35];  //m14
                        syndrome_result_pt2_f4[61] = Error_vector[1][36];  //m15
                        syndrome_result_pt2_f4[62] = Error_vector[1][37];  //m16
                        
                        
                        
                        
                        flag_result = 0;
                        
                        for (int i=0; i<7; i++){
                            flag_result = flag_result + Error_vector[1][40+i] + Error_vector[0][50+i] ;
                        }
                        
                        
                        if ( flag_result != 0){   	// 第三次量測 flag rised
                            
                            
                            for(int i=0; i<2; i++){
                                for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                            }
                            
                            
                            unflagged(Error_vector, probability, gamma, alpha, beta );
                            
                            
                            
                            
                            
                            //--use unflagged syndrome do error correction---------------------------------------
                            //loading syndorme result to array
                            
                            for (int i=0; i<8; i++){
                                syndrome_result_pt2_f2[i] = Error_vector[0][i+20];
                            }
                            for (int i=0; i<8; i++){
                                syndrome_result_pt2_f2[i+8] = Error_vector[1][i+30];
                            }
                            
                            
                            //compare test1 and symdorme_result array and get index j
                            for (int j=0; j<table_length_pt2_f2; j++){
                                
                                for (int i=0; i<table_width_pt2_f2; i++){
                                    test1_pt2_f2[i]=syndrome_pt2_f2[j][i];
                                }
                                // 排除syndrome = 0000的情快
                                //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                //	break;
                                //}
                                
                                compare_result = memcmp(test1_pt2_f2, syndrome_result_pt2_f2,sizeof(syndrome_result_pt2_f2));
                                
                                if (compare_result == 0) {
                                    
                                    // table_index = j;
                                    
                                    //        cout <<  "j= "  << j << endl;
                                    //使用recovery進行 x error
                                    
                                    for (int k=0; k<17; k++){
                                        Error_vector[0][k]= (Error_vector[0][k]+recovery_pt2_f2[j][k])%2;
                                        Error_vector[1][k]= (Error_vector[1][k]+recovery_pt2_f2[j][k+17])%2;
                                    }
                                    break;
                                    
                                }
                                
                            }
                        }  	// 第三次量測 flag rised
                        else {    	// 第三次量測 flag do not rised
                            
                            
                            int s2_result[16] = {0};
                            int s3_result[16] = {0};
                            
                            for (int i=0; i<16; i++){
                                s2_result[i] = syndrome_result_pt2_f1[i+31];
                            }
                            for (int i=0; i<16; i++){
                                s3_result[i] = syndrome_result_pt2_f2[i+31];
                            }
                            
                            compare_result = memcmp(s2_result, s3_result,sizeof(s2_result));
                            
                            if (compare_result == 0){  // s2=s3
                                
                                
                                
                                
                                //compare test1 and symdorme_result array and get index j
                                for (int j=0; j<table_length_pt2_f3; j++){
                                    
                                    for (int i=0; i<table_width_pt2_f3; i++){
                                        test1_pt2_f3[i]=syndrome_pt2_f3[j][i];
                                    }
                                    // 排除syndrome = 0000的情快
                                    //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                    //	break;
                                    //}
                                    
                                    compare_result = memcmp(test1_pt2_f3, syndrome_result_pt2_f3,sizeof(syndrome_result_pt2_f3));
                                    
                                    if (compare_result == 0) {
                                        
                                        // table_index = j;
                                        
                                        //        cout <<  "j= "  << j << endl;
                                        //使用recovery進行 x error
                                        
                                        for (int k=0; k<17; k++){
                                            Error_vector[0][k]= (Error_vector[0][k]+recovery_pt2_f3[j][k])%2;
                                            Error_vector[1][k]= (Error_vector[1][k]+recovery_pt2_f3[j][k+17])%2;
                                        }
                                        
                                        break;
                                        
                                    }
                                    
                                }
                                
                                
                            }
                            
                            else {  //s2 unequal s3
                                
                                
                                for(int i=0; i<2; i++){
                                    for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                                }
                                
                                
                                unflagged(Error_vector, probability, gamma, alpha, beta );
                                
                                
                                
                                
                                //--use unflagged syndrome do error correction---------------------------------------
                                //-----------------------------------------
                                //loading syndorme result to array
                                
                                for (int i=0; i<8; i++){
                                    syndrome_result_pt2_f4[i] = Error_vector[0][i+20];
                                }
                                for (int i=0; i<8; i++){
                                    syndrome_result_pt2_f4[i+8] = Error_vector[1][i+30];
                                }
                                
                                
                                //compare test1 and symdorme_result array and get index j
                                for (int j=0; j<table_length_pt2_f4; j++){
                                    
                                    for (int i=0; i<table_width_pt2_f4; i++){
                                        test1_pt2_f4[i]=syndrome_pt2_f4[j][i];
                                    }
                                    // 排除syndrome = 0000的情快
                                    //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                    //	break;
                                    //}
                                    
                                    compare_result = memcmp(test1_pt2_f4, syndrome_result_pt2_f4,sizeof(syndrome_result_pt2_f4));
                                    
                                    if (compare_result == 0) {
                                        
                                        table_index = j;
                                        
                                        //        cout <<  "j= "  << j << endl;
                                        //使用recovery進行 x error
                                        
                                        for (int k=0; k<17; k++){
                                            Error_vector[0][k]= (Error_vector[0][k]+recovery_pt2_f4[j][k])%2;
                                            Error_vector[1][k]= (Error_vector[1][k]+recovery_pt2_f4[j][k+17])%2;
                                        }
                                        break;
                                        
                                    }
                                    
                                }
                                
                                
                                
                                
                            } //s2 unequal s3
                            
                            
                            
                            
                        } // 第三次量測 flag do not rised
                        
                        
                        
                    }     // 第二次量測 else if
                    
                    //--------------------------------------------------------------------------------------------------
                    //--------------------------------------------------------------------------------------------------
                    //--------------------------------------------------------------------------------------------------
                    
                    
                } // 第一次flag rised   if ( Error_vector[1][40] !=0    )
                
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                
                else if ( Error_vector[1][20] !=0 || Error_vector[1][21] !=0 || Error_vector[1][22] !=0 || Error_vector[1][23] !=0 || Error_vector[1][24] !=0 || Error_vector[1][25] !=0 || Error_vector[1][26] !=0 || Error_vector[1][27] !=0  ) {
                    
                    
                    
                    
                    for(int i=0; i<2; i++){
                        for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    
                    parallel_flag(Error_vector, probability, gamma, alpha, beta );
                    
                    //Z-type stabilizer
                    syndrome_result_pt2_m1[31] = Error_vector[0][20];  //m1
                    syndrome_result_pt2_m1[32] = Error_vector[0][21];  //m2
                    syndrome_result_pt2_m1[33] = Error_vector[0][22];  //m3
                    syndrome_result_pt2_m1[34] = Error_vector[0][23];  //m4
                    syndrome_result_pt2_m1[35] = Error_vector[0][24];  //m5
                    syndrome_result_pt2_m1[36] = Error_vector[0][25];  //m6
                    syndrome_result_pt2_m1[37] = Error_vector[0][26];  //m7
                    syndrome_result_pt2_m1[38] = Error_vector[0][27];  //m8
                    
                    //X-type stabilizer
                    syndrome_result_pt2_m1[39] = Error_vector[1][30];  //m9
                    syndrome_result_pt2_m1[40] = Error_vector[1][31];  //m10
                    syndrome_result_pt2_m1[41] = Error_vector[1][32];  //m11
                    syndrome_result_pt2_m1[42] = Error_vector[1][33];  //m12
                    syndrome_result_pt2_m1[43] = Error_vector[1][34];  //m13
                    syndrome_result_pt2_m1[44] = Error_vector[1][35];  //m14
                    syndrome_result_pt2_m1[45] = Error_vector[1][36];  //m15
                    syndrome_result_pt2_m1[46] = Error_vector[1][37];  //m16
                    
                    //Z-type flag
                    
                    syndrome_result_pt2_m1[47] = Error_vector[1][40];  //f1
                    syndrome_result_pt2_m1[48] = Error_vector[1][41];  //f2
                    syndrome_result_pt2_m1[49] = Error_vector[1][42];  //f3
                    syndrome_result_pt2_m1[50] = Error_vector[1][43];  //f4
                    syndrome_result_pt2_m1[51] = Error_vector[1][44];  //f5
                    syndrome_result_pt2_m1[52] = Error_vector[1][45];  //f6
                    syndrome_result_pt2_m1[53] = Error_vector[1][46];  //f7
                    
                    //X-type  flag
                    syndrome_result_pt2_m1[54] = Error_vector[0][50];  //f1
                    syndrome_result_pt2_m1[55] = Error_vector[0][51];  //f2
                    syndrome_result_pt2_m1[56] = Error_vector[0][52];  //f3
                    syndrome_result_pt2_m1[57] = Error_vector[0][53];  //f4
                    syndrome_result_pt2_m1[58] = Error_vector[0][54];  //f5
                    syndrome_result_pt2_m1[59] = Error_vector[0][55];  //f6
                    syndrome_result_pt2_m1[60] = Error_vector[0][56];  //f7
                    
                    
                    //Z-type stabilizer
                    syndrome_result_pt2_m4[31] = Error_vector[0][20];  //m1
                    syndrome_result_pt2_m4[32] = Error_vector[0][21];  //m2
                    syndrome_result_pt2_m4[33] = Error_vector[0][22];  //m3
                    syndrome_result_pt2_m4[34] = Error_vector[0][23];  //m4
                    syndrome_result_pt2_m4[35] = Error_vector[0][24];  //m5
                    syndrome_result_pt2_m4[36] = Error_vector[0][25];  //m6
                    syndrome_result_pt2_m4[37] = Error_vector[0][26];  //m7
                    syndrome_result_pt2_m4[38] = Error_vector[0][27];  //m8
                    
                    //X-type stabilizer
                    syndrome_result_pt2_m4[39] = Error_vector[1][30];  //m9
                    syndrome_result_pt2_m4[40] = Error_vector[1][31];  //m10
                    syndrome_result_pt2_m4[41] = Error_vector[1][32];  //m11
                    syndrome_result_pt2_m4[42] = Error_vector[1][33];  //m12
                    syndrome_result_pt2_m4[43] = Error_vector[1][34];  //m13
                    syndrome_result_pt2_m4[44] = Error_vector[1][35];  //m14
                    syndrome_result_pt2_m4[45] = Error_vector[1][36];  //m15
                    syndrome_result_pt2_m4[46] = Error_vector[1][37];  //m16
                    
                    
                    
                    
                    int flag_result = 0;
                    
                    for (int i=0; i<7; i++){
                        flag_result = flag_result + Error_vector[1][40+i] +  Error_vector[0][50+i]  ;
                    }
                    
                    
                    if ( flag_result != 0){
                        
                        
                        
                        for(int i=0; i<2; i++){
                            for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                        }
                        
                        
                        unflagged(Error_vector, probability, gamma, alpha, beta );
                        
                        
                        
                        
                        //--use unflagged syndrome do error correction---------------------------------------
                        //-----------------------------------------
                        //loading syndorme result to array
                        
                        for (int i=0; i<8; i++){
                            syndrome_result_pt2_m1[i] = Error_vector[0][i+20];
                        }
                        for (int i=0; i<8; i++){
                            syndrome_result_pt2_m1[i+8] = Error_vector[1][i+30];
                        }
                        
                        
                        //compare test1 and symdorme_result array and get index j
                        for (int j=0; j<table_length_pt2_m1; j++){
                            
                            for (int i=0; i<table_width_pt2_m1; i++){
                                test1_pt2_m1[i]=syndrome_pt2_m1[j][i];
                            }
                            // 排除syndrome = 0000的情快
                            //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                            //	break;
                            //}
                            
                            compare_result = memcmp(test1_pt2_m1, syndrome_result_pt2_m1,sizeof(syndrome_result_pt2_m1));
                            
                            if (compare_result == 0) {
                                
                                table_index = j;
                                
                                //        cout <<  "j= "  << j << endl;
                                //使用recovery進行 x error
                                
                                for (int k=0; k<17; k++){
                                    Error_vector[0][k]= (Error_vector[0][k]+recovery_pt2_m1[j][k])%2;
                                    Error_vector[1][k]= (Error_vector[1][k]+recovery_pt2_m1[j][k+17])%2;
                                }
                                break;
                                
                            }
                            
                        }
                        
                    }   //  第二次量測 flag rised
                    
                    //--------------------------------------------------------------------------------------------------
                    //--------------------------------------------------------------------------------------------------
                    //--------------------------------------------------------------------------------------------------
                    
                    else {
                        
                        
                        for(int i=0; i<2; i++){
                            for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                        }
                        
                        
                        parallel_flag(Error_vector, probability, gamma, alpha, beta );
                        
                        //Z-type stabilizer
                        syndrome_result_pt2_m2[31] = Error_vector[0][20];  //m1
                        syndrome_result_pt2_m2[32] = Error_vector[0][21];  //m2
                        syndrome_result_pt2_m2[33] = Error_vector[0][22];  //m3
                        syndrome_result_pt2_m2[34] = Error_vector[0][23];  //m4
                        syndrome_result_pt2_m2[35] = Error_vector[0][24];  //m5
                        syndrome_result_pt2_m2[36] = Error_vector[0][25];  //m6
                        syndrome_result_pt2_m2[37] = Error_vector[0][26];  //m7
                        syndrome_result_pt2_m2[38] = Error_vector[0][27];  //m8
                        
                        //X-type stabilizer
                        syndrome_result_pt2_m2[39] = Error_vector[1][30];  //m9
                        syndrome_result_pt2_m2[40] = Error_vector[1][31];  //m10
                        syndrome_result_pt2_m2[41] = Error_vector[1][32];  //m11
                        syndrome_result_pt2_m2[42] = Error_vector[1][33];  //m12
                        syndrome_result_pt2_m2[43] = Error_vector[1][34];  //m13
                        syndrome_result_pt2_m2[44] = Error_vector[1][35];  //m14
                        syndrome_result_pt2_m2[45] = Error_vector[1][36];  //m15
                        syndrome_result_pt2_m2[46] = Error_vector[1][37];  //m16
                        
                        //Z-type flag
                        
                        syndrome_result_pt2_m2[47] = Error_vector[1][40];  //f1
                        syndrome_result_pt2_m2[48] = Error_vector[1][41];  //f2
                        syndrome_result_pt2_m2[49] = Error_vector[1][42];  //f3
                        syndrome_result_pt2_m2[50] = Error_vector[1][43];  //f4
                        syndrome_result_pt2_m2[51] = Error_vector[1][44];  //f5
                        syndrome_result_pt2_m2[52] = Error_vector[1][45];  //f6
                        syndrome_result_pt2_m2[53] = Error_vector[1][46];  //f7
                        
                        //X-type  flag
                        syndrome_result_pt2_m2[54] = Error_vector[0][50];  //f1
                        syndrome_result_pt2_m2[55] = Error_vector[0][51];  //f2
                        syndrome_result_pt2_m2[56] = Error_vector[0][52];  //f3
                        syndrome_result_pt2_m2[57] = Error_vector[0][53];  //f4
                        syndrome_result_pt2_m2[58] = Error_vector[0][54];  //f5
                        syndrome_result_pt2_m2[59] = Error_vector[0][55];  //f6
                        syndrome_result_pt2_m2[60] = Error_vector[0][56];  //f7
                        
                        //Z-type stabilizer
                        syndrome_result_pt2_m3[15] = Error_vector[0][20];  //m1
                        syndrome_result_pt2_m3[16] = Error_vector[0][21];  //m2
                        syndrome_result_pt2_m3[17] = Error_vector[0][22];  //m3
                        syndrome_result_pt2_m3[18] = Error_vector[0][23];  //m4
                        syndrome_result_pt2_m3[19] = Error_vector[0][24];  //m5
                        syndrome_result_pt2_m3[20] = Error_vector[0][25];  //m6
                        syndrome_result_pt2_m3[21] = Error_vector[0][26];  //m7
                        syndrome_result_pt2_m3[22] = Error_vector[0][27];  //m8
                        
                        //X-type stabilizer
                        syndrome_result_pt2_m3[23] = Error_vector[1][30];  //m9
                        syndrome_result_pt2_m3[24] = Error_vector[1][31];  //m10
                        syndrome_result_pt2_m3[25] = Error_vector[1][32];  //m11
                        syndrome_result_pt2_m3[26] = Error_vector[1][33];  //m12
                        syndrome_result_pt2_m3[27] = Error_vector[1][34];  //m13
                        syndrome_result_pt2_m3[28] = Error_vector[1][35];  //m14
                        syndrome_result_pt2_m3[29] = Error_vector[1][36];  //m15
                        syndrome_result_pt2_m3[30] = Error_vector[1][37];  //m16
                        
                        //Z-type flag
                        
                        syndrome_result_pt2_m3[31] = Error_vector[1][40];  //f1
                        syndrome_result_pt2_m3[32] = Error_vector[1][41];  //f2
                        syndrome_result_pt2_m3[33] = Error_vector[1][42];  //f3
                        syndrome_result_pt2_m3[34] = Error_vector[1][43];  //f4
                        syndrome_result_pt2_m3[35] = Error_vector[1][44];  //f5
                        syndrome_result_pt2_m3[36] = Error_vector[1][45];  //f6
                        syndrome_result_pt2_m3[37] = Error_vector[1][46];  //f7
                        
                        //X-type  flag
                        syndrome_result_pt2_m3[38] = Error_vector[0][50];  //f1
                        syndrome_result_pt2_m3[39] = Error_vector[0][51];  //f2
                        syndrome_result_pt2_m3[40] = Error_vector[0][52];  //f3
                        syndrome_result_pt2_m3[41] = Error_vector[0][53];  //f4
                        syndrome_result_pt2_m3[42] = Error_vector[0][54];  //f5
                        syndrome_result_pt2_m3[43] = Error_vector[0][55];  //f6
                        syndrome_result_pt2_m3[44] = Error_vector[0][56];  //f7
                        
                        //Z-type stabilizer
                        syndrome_result_pt2_m4[47] = Error_vector[0][20];  //m1
                        syndrome_result_pt2_m4[48] = Error_vector[0][21];  //m2
                        syndrome_result_pt2_m4[49] = Error_vector[0][22];  //m3
                        syndrome_result_pt2_m4[50] = Error_vector[0][23];  //m4
                        syndrome_result_pt2_m4[51] = Error_vector[0][24];  //m5
                        syndrome_result_pt2_m4[52] = Error_vector[0][25];  //m6
                        syndrome_result_pt2_m4[53] = Error_vector[0][26];  //m7
                        syndrome_result_pt2_m4[54] = Error_vector[0][27];  //m8
                        
                        //X-type stabilizer
                        syndrome_result_pt2_m4[55] = Error_vector[1][30];  //m9
                        syndrome_result_pt2_m4[56] = Error_vector[1][31];  //m10
                        syndrome_result_pt2_m4[57] = Error_vector[1][32];  //m11
                        syndrome_result_pt2_m4[58] = Error_vector[1][33];  //m12
                        syndrome_result_pt2_m4[59] = Error_vector[1][34];  //m13
                        syndrome_result_pt2_m4[60] = Error_vector[1][35];  //m14
                        syndrome_result_pt2_m4[61] = Error_vector[1][36];  //m15
                        syndrome_result_pt2_m4[62] = Error_vector[1][37];  //m16
                        
                        
                        
                        flag_result = 0;
                        
                        for (int i=0; i<7; i++){
                            flag_result = flag_result + Error_vector[1][40+i] + Error_vector[0][50+i] ;
                        }
                        
                        
                        if ( flag_result != 0){   	// 第三次量測 flag rised
                            
                            
                            for(int i=0; i<2; i++){
                                for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                            }
                            
                            
                            unflagged(Error_vector, probability, gamma, alpha, beta );
                            
                            
                            
                            
                            
                            
                            //--use unflagged syndrome do error correction---------------------------------------
                            //-----------------------------------------
                            //loading syndorme result to array
                            
                            for (int i=0; i<8; i++){
                                syndrome_result_pt2_m2[i] = Error_vector[0][i+20];
                            }
                            for (int i=0; i<8; i++){
                                syndrome_result_pt2_m2[i+8] = Error_vector[1][i+30];
                            }
                            
                            
                            //compare test1 and symdorme_result array and get index j
                            for (int j=0; j<table_length_pt2_m2; j++){
                                
                                for (int i=0; i<table_width_pt2_m2; i++){
                                    test1_pt2_m2[i]=syndrome_pt2_m2[j][i];
                                }
                                // 排除syndrome = 0000的情快
                                //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                //	break;
                                //}
                                
                                compare_result = memcmp(test1_pt2_m2, syndrome_result_pt2_m2,sizeof(syndrome_result_pt2_m2));
                                
                                if (compare_result == 0) {
                                    
                                    table_index = j;
                                    
                                    //        cout <<  "j= "  << j << endl;
                                    //使用recovery進行 x error
                                    
                                    for (int k=0; k<17; k++){
                                        Error_vector[0][k]= (Error_vector[0][k]+recovery_pt2_m2[j][k])%2;
                                        Error_vector[1][k]= (Error_vector[1][k]+recovery_pt2_m2[j][k+17])%2;
                                    }
                                    break;
                                    
                                }
                                
                            }
                        }  	// 第三次量測 flag rised
                        else {    	// 第三次量測 flag do not rised
                            
                            
                            int s2_result[16] = {0};
                            int s3_result[16] = {0};
                            
                            for (int i=0; i<16; i++){
                                s2_result[i] = syndrome_result_pt2_m1[i+31];
                            }
                            for (int i=0; i<16; i++){
                                s3_result[i] = syndrome_result_pt2_m2[i+31];
                            }
                            
                            compare_result = memcmp(s2_result, s3_result,sizeof(s2_result));
                            
                            if (compare_result == 0){  // s2=s3
                                
                                
                                
                                //compare test1 and symdorme_result array and get index j
                                for (int j=0; j<table_length_pt2_m3; j++){
                                    
                                    for (int i=0; i<table_width_pt2_m3; i++){
                                        test1_pt2_m3[i]=syndrome_pt2_m3[j][i];
                                    }
                                    // 排除syndrome = 0000的情快
                                    //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                    //	break;
                                    //}
                                    
                                    compare_result = memcmp(test1_pt2_m3, syndrome_result_pt2_m3,sizeof(syndrome_result_pt2_m3));
                                    
                                    if (compare_result == 0) {
                                        
                                        table_index = j;
                                        
                                        //        cout <<  "j= "  << j << endl;
                                        //使用recovery進行 x error
                                        
                                        for (int k=0; k<17; k++){
                                            Error_vector[0][k]= (Error_vector[0][k]+recovery_pt2_m3[j][k])%2;
                                            Error_vector[1][k]= (Error_vector[1][k]+recovery_pt2_m3[j][k+17])%2;
                                        }
                                        break;
                                        
                                    }
                                    
                                }
                                
                                
                            }
                            
                            else {  //s2 unequal s3
                                
                                
                                for(int i=0; i<2; i++){
                                    for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                                }
                                
                                
                                unflagged(Error_vector, probability, gamma, alpha, beta );
                                
                                
                                
                                
                                
                                //--use unflagged syndrome do error correction---------------------------------------
                                //-----------------------------------------
                                //loading syndorme result to array
                                
                                for (int i=0; i<8; i++){
                                    syndrome_result_pt2_m4[i] = Error_vector[0][i+20];
                                }
                                for (int i=0; i<8; i++){
                                    syndrome_result_pt2_m4[i+8] = Error_vector[1][i+30];
                                }
                                
                                
                                //compare test1 and symdorme_result array and get index j
                                for (int j=0; j<table_length_pt2_m4; j++){
                                    
                                    for (int i=0; i<table_width_pt2_m4; i++){
                                        test1_pt2_m4[i]=syndrome_pt2_m4[j][i];
                                    }
                                    // 排除syndrome = 0000的情快
                                    //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                    //	break;
                                    //}
                                    
                                    compare_result = memcmp(test1_pt2_m4, syndrome_result_pt2_m4,sizeof(syndrome_result_pt2_m4));
                                    
                                    if (compare_result == 0) {
                                        
                                        table_index = j;
                                        
                                        //        cout <<  "j= "  << j << endl;
                                        //使用recovery進行 x error
                                        
                                        for (int k=0; k<17; k++){
                                            Error_vector[0][k]= (Error_vector[0][k]+recovery_pt2_m4[j][k])%2;
                                            Error_vector[1][k]= (Error_vector[1][k]+recovery_pt2_m4[j][k+17])%2;
                                        }
                                        break;
                                        
                                    }
                                    
                                }
                                
                                
                                
                                
                            } //s2 unequal s3
                            
                            
                            
                            
                        } // 第三次量測 flag do not rised
                        
                        
                        
                    }     // 第二次量測 else if
                    
                    //--------------------------------------------------------------------------------------------------
                    //--------------------------------------------------------------------------------------------------
                    //--------------------------------------------------------------------------------------------------
                    
                    
                    
                    
                } // 第一次量測 的 else if ( Error_vector[0][20] !=0 || Error_vector[0][21] !=0  )
                
                
                
                outpoint2:
                    
                    
//------------------------------------------------------------------------------------------------------------------------------
                    
                    
                    
//---Perfect circuit------------------------------------------------------------------------------------------------------------
                    
                    
                    
                    for(int i=0; i<2; i++){
                        for(int j=17; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    // X measurement (1-A)
                    x_circuit(Error_vector, probability, gamma, alpha, beta );
                    
                    // Z measurement (1-B)
                    z_circuit(Error_vector, probability, gamma, alpha, beta);
                    
                    
                    //loading syndorme result to array
                    for (int i=0; i<8; i++){
                        symdorme_result_x[i] = Error_vector[0][i+20];
                    }
                    for (int i=0; i<8; i++){
                        symdorme_result_z[i] = Error_vector[1][i+30];
                    }
                    
                    
                    
                    //compare test1 and symdorme_result_z array and get index j
                    for (int j=0; j<153; j++){
                        
                        for (int i=0; i<8; i++){
                            test1[i]=syndrome[j][i];
                        }
                        // 排除syndrome = 0000的情快
                        
                        if (symdorme_result_x[0] == 0 &&  symdorme_result_x[1] == 0 && symdorme_result_x[2] == 0 && symdorme_result_x[3] == 0 && symdorme_result_x[4] == 0 &&  symdorme_result_x[5] == 0 && symdorme_result_x[6] == 0 && symdorme_result_x[7] == 0 ){
                            break;
                        }
                        
                        compare_result = memcmp(test1, symdorme_result_x,sizeof(symdorme_result_x));
                        
                        if (compare_result == 0) {
                            //   table_index = j;
                            //使用recovery進行 x error
                            
                            for (int k=0; k<17; k++){
                                Error_vector[0][k]= (Error_vector[0][k]+recovery[j][k])%2;
                            }
                            break;
                            
                        }
                    }
                    
                    
                    
                    //compare test1 and symdorme_result_x array and get index j
                    
                    
                    for (int j=0; j<153; j++){
                        
                        for (int i=0; i<8; i++){
                            test1[i]=syndrome[j][i];
                        }
                        
                        
                        if (symdorme_result_z[0] == 0 &&  symdorme_result_z[1] == 0 && symdorme_result_z[2] == 0 && symdorme_result_z[3] == 0 && symdorme_result_z[4] == 0 &&  symdorme_result_z[5] == 0 && symdorme_result_z[6] == 0 && symdorme_result_z[7] == 0  ){
                            break;
                        }
                        
                        compare_result = memcmp(test1, symdorme_result_z,sizeof(symdorme_result_z));
                        
                        if (compare_result == 0) {
                            table_index = j;
                            
                            //使用table_r進行 Z error
                            for (int k=0; k<17; k++){
                                Error_vector[1][k]= (Error_vector[1][k]+recovery[j][k])%2;
                                
                            }
                            break;
                            
                        }
                    }
                    
                    
//------------------------------------------------------------------------------------------------------------------------------
                    
                    
                    //排除logci X, logic Z
                    s9=0;
                    s10=0;
                    
                    for (int i=0; i<17;i++){
                        s9=(s9+Error_vector[0][i])%2;
                    }
                    for (int i=0; i<17;i++){
                        s10=(s10+Error_vector[1][i])%2;
                    }
                    
                    
                    if (s9 == 0  && s10 ==0){
                        
                        Total_number = Total_number + 1;
                    }
                    else {
                        
                        //   if ( Total_number == 1227749 ){
                        /*
                cout << Total_number ;
                cout << " & " ;
                for (int i=0; i<17; i++){
                    cout << Error_vector[0][i];
                }
                cout << " & " ;
                for (int i=0; i<17; i++){
                    cout << Error_vector[1][i];
                }
                cout << endl;
                         */
                        //      }
                        
                        Error_number = Error_number + 1 ;
                        Total_number = Total_number + 1;
                        
                        
                        
                    }
                    
                    
                    
                    // goto ckp3;
                    
                    
                    
                    
                    // ckp3:
                    
                    //    Total_number = Total_number + 1;
                    
                    
                    
                    
                    
        } // while
        Display_p[i-1] = probability;
        Display_e[i-1] = Error_number/(Total_number-detected_number);
        Display_d[i-1] = detected_number/Total_number;
        cout  <<  "% No." << i << " Physical error rate : " << probability << "; Error number = " << Error_number << ", total_number = " << Total_number << ", logical error rate : " <<  Error_number/(Total_number) << "    |" << c_time_string ;//<< endl;
        
        
        
        
    } // i loop
    
    cout << "Physical_error_rate = [ ";
    for(int i=0; i<N-1; i++){
        if(i<N-2)	cout <<  Display_p[i] << ", ";
        if(i==N-2) cout << Display_p[i];
    } cout << " ]" << endl;
    
    cout << "Logical_error_rate = [ ";
    for(int i=0; i<N-1; i++){
        if(i<N-2)	cout <<  Display_e[i] << ", ";
        if(i==N-2) cout << Display_e[i];
    } cout << " ]" << endl;
    
    // cout << "gamma = " << gamma << endl;
    
    
    
    end = clock();
    double diff = end - start; // ms
    printf(" %f  sec", diff / CLOCKS_PER_SEC );
    scanf("%d", &input);
    
    return 0;
}

int correct(int (*Error_vector)[n], int a, int B){
    a = a - 1;
    if( B==2 ){
        *(*(Error_vector+0)+a) = (*(*(Error_vector+0)+a) + 1)%2;   // X error時 ,再該qubit補上一個error count
        //	cout << "X error on " << a+1 << endl;
    }
    if( B==3 ){
        *(*(Error_vector+1)+a) = (*(*(Error_vector+1)+a) + 1)%2;    // Z error時,再該qubit補上一個error count
        //	cout << "Z error on " << a+1 << endl;
    }
    if( B==4 ){
        *(*(Error_vector+0)+a) = (*(*(Error_vector+0)+a) + 1)%2;    // Y error時,再該qubit補上一個X & Y error count
        *(*(Error_vector+1)+a) = (*(*(Error_vector+1)+a) + 1)%2;
        //	cout << "Y error on " << a+1 << endl;
    }
    
}

int SQerror(int (*Error_vector)[n], int a, double probability){
    a = a - 1;
    r = next64()/(pow(2,64));
    if( r < (probability/3) ){ // depolarizing channel, r < (1/3)*p 發生 X error
        *(*(Error_vector+0)+a) = (*(*(Error_vector+0)+a) + 1)%2;
    }
    if( r > (probability/3) && r < (2*probability/3) ){ // (1/3)*p < r < (2/3)*p 發生 Z error
        *(*(Error_vector+1)+a) = (*(*(Error_vector+1)+a) + 1)%2;
    }
    if( r > (2*probability/3) && r < (probability) ){ // (2/3)*p < r < p 發生 Y error
        *(*(Error_vector+0)+a) = (*(*(Error_vector+0)+a) + 1)%2;
        *(*(Error_vector+1)+a) = (*(*(Error_vector+1)+a) + 1)%2;
    }
    
}

int TQerror(int (*Error_vector)[n], int a, int b, double probability){
    SQerror(Error_vector, a, probability);
    SQerror(Error_vector, b, probability);
}

int CNOT(int (*Error_vector)[n], int a, int b){
    a = a - 1;
    b = b - 1;
    if(Error_vector[0][a]==1){                                     // X error 發生
        Error_vector[0][b] = (Error_vector[0][b] + 1)%2;
    }
    if(Error_vector[1][b]==1){    								   // Z error 發生
        Error_vector[1][a] = (Error_vector[1][a] + 1)%2;
    }
    
}

int CNOT_rev(int (*Error_vector)[n], int b, int a){
    a = a - 1;
    b = b - 1;
    if(Error_vector[0][a]==1){
        Error_vector[0][b] = (Error_vector[0][b] + 1)%2;
    }
    if(Error_vector[1][b]==1){
        Error_vector[1][a] = (Error_vector[1][a] + 1)%2;
    }
    
}


int pt1_circuit(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta){
    
    
    
    SQerror(Error_vector, 21, probability);
    SQerror(Error_vector, 22, probability);
    SQerror(Error_vector, 23, probability);
    SQerror(Error_vector, 24, probability);
    SQerror(Error_vector, 25, probability);
    SQerror(Error_vector, 26, probability);
    SQerror(Error_vector, 27, probability);
    SQerror(Error_vector, 28, probability);
    
    SQerror(Error_vector, 41, probability);
    SQerror(Error_vector, 42, probability);
    SQerror(Error_vector, 43, probability);
    SQerror(Error_vector, 44, probability);
    SQerror(Error_vector, 45, probability);
    SQerror(Error_vector, 46, probability);
    SQerror(Error_vector, 47, probability);
    
//================================================================
    
    
    
//slot 1*********************************************************
    //g1
    
    CNOT(Error_vector, 3, 21);
    TQerror(Error_vector, 3, 21, probability * beta);
    
    //g2
    CNOT(Error_vector, 1, 22);
    TQerror(Error_vector, 1, 22, probability * beta);
    
    //g3
    
    CNOT(Error_vector, 5, 23);
    TQerror(Error_vector, 5, 23, probability * beta);
    
    
    //g4
    CNOT(Error_vector, 7, 24);
    TQerror(Error_vector, 7, 24, probability * beta);
    
    
    //g5
    CNOT(Error_vector, 9, 25);
    TQerror(Error_vector, 9, 25, probability * beta);
    
    //g6
    
    CNOT(Error_vector, 11, 26);
    TQerror(Error_vector, 11, 26, probability * beta);
    
    
    //g8
    CNOT(Error_vector, 14, 28);
    TQerror(Error_vector, 14, 28, probability * beta);
    
    
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
//slot 2*********************************************************
    
    
    //g1:Flag 1--------------------------
    CNOT(Error_vector, 41, 21);
    TQerror(Error_vector, 41, 21, probability * beta);
    
    //g3:Flag 1--------------------------
    CNOT(Error_vector, 42, 23);
    TQerror(Error_vector, 42, 23, probability * beta);
    
    //g4:Flag 1--------------------------
    CNOT(Error_vector, 43, 24);
    TQerror(Error_vector, 43, 24, probability * beta);
    
    //g8:Flag 1--------------------------
    CNOT(Error_vector, 44, 28);
    TQerror(Error_vector, 44, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //SQerror(Error_vector, 21, probability*gamma);
    SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    SQerror(Error_vector, 25, probability*gamma);
    SQerror(Error_vector, 26, probability*gamma);
    SQerror(Error_vector, 27, probability*gamma);
    SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    //SQerror(Error_vector, 44, probability*gamma);
    //SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
//slot 3*********************************************************
    //================================================================
    
    
    //g2:Flag 1--------------------------
    CNOT(Error_vector, 41, 22);
    TQerror(Error_vector, 41, 22, probability * beta);
    
    //g5:Flag 1--------------------------
    CNOT(Error_vector, 42, 25);
    TQerror(Error_vector, 42, 25, probability * beta);
    
    //g6:Flag 1--------------------------
    CNOT(Error_vector, 43, 26);
    TQerror(Error_vector, 43, 26, probability * beta);
    
    //g8:
    
    CNOT(Error_vector, 10, 28);
    TQerror(Error_vector, 10, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    SQerror(Error_vector, 23, probability*gamma);
    SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    //SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

//slot 4*********************************************************
//================================================================
    
    
    //g1
    CNOT(Error_vector, 1, 21);
    TQerror(Error_vector, 1, 21, probability * beta);
    
    //g2
    CNOT(Error_vector, 3, 22);
    TQerror(Error_vector, 3, 22, probability * beta);
    
    //g3
    CNOT(Error_vector, 6, 23);
    TQerror(Error_vector, 6, 23, probability * beta);
    
    
    //g4
    CNOT(Error_vector, 8, 24);
    TQerror(Error_vector, 8, 24, probability * beta);
    
    //g5
    CNOT(Error_vector, 10, 25);
    TQerror(Error_vector, 10, 25, probability * beta);
    
    
    //g6
    CNOT(Error_vector, 12, 26);
    TQerror(Error_vector, 12, 26, probability * beta);
    
    //g8:Flag 2--------------------------
    CNOT(Error_vector, 45, 28);
    TQerror(Error_vector, 45, 28, probability * beta);
    
    
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	SQerror(Error_vector, 41, probability*gamma);
    SQerror(Error_vector, 42, probability*gamma);
    SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    //SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
//slot 5*********************************************************
    
    
    //g1
    
    CNOT(Error_vector, 4, 21);
    TQerror(Error_vector, 4, 21, probability * beta);
    //g2
    
    CNOT(Error_vector, 5, 22);
    TQerror(Error_vector, 5, 22, probability * beta);
    
    //g3
    
    CNOT(Error_vector, 9, 23);
    TQerror(Error_vector, 9, 23, probability * beta);
    
    
    //g4
    
    CNOT(Error_vector, 12, 24);
    TQerror(Error_vector, 12, 24, probability * beta);
    
    
    //g5
    
    CNOT(Error_vector, 13, 25);
    TQerror(Error_vector, 13, 25, probability * beta);
    
    
    //g6
    
    CNOT(Error_vector, 16, 26);
    TQerror(Error_vector, 15, 26, probability * beta);
    
    
    //g8
    
    CNOT(Error_vector, 15, 28);
    TQerror(Error_vector, 15, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    //SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	SQerror(Error_vector, 41, probability*gamma);
    SQerror(Error_vector, 42, probability*gamma);
    SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
    
    
//slot 6*********************************************************
    
    
    
    //g1:Flag 1--------------------------
    
    CNOT(Error_vector, 41, 21);
    TQerror(Error_vector, 41, 21, probability * beta);
    
    
    
    //g3:Flag 1--------------------------
    
    CNOT(Error_vector, 42, 23);
    TQerror(Error_vector, 42, 23, probability * beta);
    
    
    //g4:Flag 1--------------------------
    
    CNOT(Error_vector, 43, 24);
    TQerror(Error_vector, 43, 24, probability * beta);
    
    
    //g8
    
    CNOT(Error_vector, 6, 28);
    TQerror(Error_vector, 6, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 21, probability*gamma);
    SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    SQerror(Error_vector, 25, probability*gamma);
    SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
//slot 7*********************************************************
    
    
    //g2:Flag 1--------------------------
    
    CNOT(Error_vector, 41, 22);
    TQerror(Error_vector, 41, 22, probability * beta);
    
    //g5:Flag 1--------------------------
    
    CNOT(Error_vector, 42, 25);
    TQerror(Error_vector, 42, 25, probability * beta);
    
    
    //g6:Flag 1--------------------------
    
    CNOT(Error_vector, 43, 26);
    TQerror(Error_vector, 43, 26, probability * beta);
    
    
    //g8:Flag 3--------------------------
    
    CNOT(Error_vector, 46, 28);
    TQerror(Error_vector, 46, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    SQerror(Error_vector, 23, probability*gamma);
    SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
//slot 8*********************************************************
    
    
    //g1
    
    CNOT(Error_vector, 2, 21);
    TQerror(Error_vector, 2, 21, probability * beta);
    
    
    
    //g2
    
    CNOT(Error_vector, 6, 22);
    TQerror(Error_vector, 6, 22, probability * beta);
    
    //g3
    
    CNOT(Error_vector, 10, 23);
    TQerror(Error_vector, 10, 23, probability * beta);
    
    
    
    //g4
    
    CNOT(Error_vector, 11, 24);
    TQerror(Error_vector, 11, 24, probability * beta);
    
    
    //g5
    
    CNOT(Error_vector, 14, 25);
    TQerror(Error_vector, 14, 25, probability * beta);
    
    
    //g6
    
    CNOT(Error_vector, 15, 26);
    TQerror(Error_vector, 15, 26, probability * beta);
    
    //g7
    
    CNOT(Error_vector, 12, 27);
    TQerror(Error_vector, 12, 27, probability * beta);
    
    
    //g8
    CNOT(Error_vector, 3, 28);
    TQerror(Error_vector, 3, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    //SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    //SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
    
//slot 9*********************************************************
    
    //g7:Flag 1--------------------------
    
    CNOT(Error_vector, 47, 27);
    TQerror(Error_vector, 47, 27, probability * beta);
    
    //g8
    
    CNOT(Error_vector, 7, 28);
    TQerror(Error_vector, 7, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
   
    SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
//slot 10*********************************************************
    
    //g7
    CNOT(Error_vector, 8, 27);
    TQerror(Error_vector, 8, 27, probability * beta);
    
    
    //g8:Flag 1--------------------------
    CNOT(Error_vector, 44, 28);
    TQerror(Error_vector, 44, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	

    //SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    SQerror(Error_vector, 46, probability*gamma);
    SQerror(Error_vector, 47, probability*gamma);

    
    
//slot 11*********************************************************
    
    //g7
    
    CNOT(Error_vector, 17, 27);
    TQerror(Error_vector, 17, 27, probability * beta);
    
    //g8
    
    CNOT(Error_vector, 4, 28);
    TQerror(Error_vector, 4, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    //SQerror(Error_vector, 17, probability*gamma);
	
	
    SQerror(Error_vector, 45, probability*gamma);
    SQerror(Error_vector, 46, probability*gamma);
    SQerror(Error_vector, 47, probability*gamma);
    
//slot 12*********************************************************
    
    
    //g7:Flag 1--------------------------
    CNOT(Error_vector, 47, 27);
    TQerror(Error_vector, 47, 27, probability * beta);
    
    
    //g8:Flag 3--------------------------
    
    CNOT(Error_vector, 46, 28);
    TQerror(Error_vector, 46, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	

    SQerror(Error_vector, 45, probability*gamma);
    
    
//slot 13*********************************************************
    
    //g7
    CNOT(Error_vector, 16, 27);
    TQerror(Error_vector, 16, 27, probability * beta);
    
    //g8:Flag 2--------------------------
    CNOT(Error_vector, 45, 28);
    TQerror(Error_vector, 45, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	

    
    
//slot 14*********************************************************
    
    
    //g8:Number F->I--------------------------
    CNOT(Error_vector, 11, 28);
    TQerror(Error_vector, 11, 28, probability * beta);
    

    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	

    
    
//================================================================
    
    SQerror(Error_vector, 21, probability*alpha);
    SQerror(Error_vector, 22, probability*alpha);
    SQerror(Error_vector, 23, probability*alpha);
    SQerror(Error_vector, 24, probability*alpha);
    SQerror(Error_vector, 25, probability*alpha);
    SQerror(Error_vector, 26, probability*alpha);
    SQerror(Error_vector, 27, probability*alpha);
    SQerror(Error_vector, 28, probability*alpha);
    
    SQerror(Error_vector, 41, probability*alpha);
    SQerror(Error_vector, 42, probability*alpha);
    SQerror(Error_vector, 43, probability*alpha);
    SQerror(Error_vector, 44, probability*alpha);
    SQerror(Error_vector, 45, probability*alpha);
    SQerror(Error_vector, 46, probability*alpha);
    SQerror(Error_vector, 47, probability*alpha);
    
}



int pt2_circuit(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta){
    
        
    SQerror(Error_vector, 21, probability);
    SQerror(Error_vector, 22, probability);
    SQerror(Error_vector, 23, probability);
    SQerror(Error_vector, 24, probability);
    SQerror(Error_vector, 25, probability);
    SQerror(Error_vector, 26, probability);
    SQerror(Error_vector, 27, probability);
    SQerror(Error_vector, 28, probability);
    
    SQerror(Error_vector, 41, probability);
    SQerror(Error_vector, 42, probability);
    SQerror(Error_vector, 43, probability);
    SQerror(Error_vector, 44, probability);
    SQerror(Error_vector, 45, probability);
    SQerror(Error_vector, 46, probability);
    SQerror(Error_vector, 47, probability);
    
//================================================================
    
    
    
//slot 1*********************************************************
    //g1
    
    CNOT_rev(Error_vector, 3, 21);
    TQerror(Error_vector, 3, 21, probability * beta);
    
    //g2
    CNOT_rev(Error_vector, 1, 22);
    TQerror(Error_vector, 1, 22, probability * beta);
    
    //g3
    
    CNOT_rev(Error_vector, 5, 23);
    TQerror(Error_vector, 5, 23, probability * beta);
    
    
    //g4
    CNOT_rev(Error_vector, 7, 24);
    TQerror(Error_vector, 7, 24, probability * beta);
    
    
    //g5
    CNOT_rev(Error_vector, 9, 25);
    TQerror(Error_vector, 9, 25, probability * beta);
    
    //g6
    
    CNOT_rev(Error_vector, 11, 26);
    TQerror(Error_vector, 11, 26, probability * beta);
    
    
    //g8
    CNOT_rev(Error_vector, 14, 28);
    TQerror(Error_vector, 14, 28, probability * beta);
    
    
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
//slot 2*********************************************************
    
    
    //g1:Flag 1--------------------------
    CNOT_rev(Error_vector, 41, 21);
    TQerror(Error_vector, 41, 21, probability * beta);
    
    //g3:Flag 1--------------------------
    CNOT_rev(Error_vector, 42, 23);
    TQerror(Error_vector, 42, 23, probability * beta);
    
    //g4:Flag 1--------------------------
    CNOT_rev(Error_vector, 43, 24);
    TQerror(Error_vector, 43, 24, probability * beta);
    
    //g8:Flag 1--------------------------
    CNOT_rev(Error_vector, 44, 28);
    TQerror(Error_vector, 44, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //SQerror(Error_vector, 21, probability*gamma);
    SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    SQerror(Error_vector, 25, probability*gamma);
    SQerror(Error_vector, 26, probability*gamma);
    SQerror(Error_vector, 27, probability*gamma);
    SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    //SQerror(Error_vector, 44, probability*gamma);
    //SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
//slot 3*********************************************************
    //================================================================
    
    
    //g2:Flag 1--------------------------
    CNOT_rev(Error_vector, 41, 22);
    TQerror(Error_vector, 41, 22, probability * beta);
    
    //g5:Flag 1--------------------------
    CNOT_rev(Error_vector, 42, 25);
    TQerror(Error_vector, 42, 25, probability * beta);
    
    //g6:Flag 1--------------------------
    CNOT_rev(Error_vector, 43, 26);
    TQerror(Error_vector, 43, 26, probability * beta);
    
    //g8:
    
    CNOT_rev(Error_vector, 10, 28);
    TQerror(Error_vector, 10, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    SQerror(Error_vector, 23, probability*gamma);
    SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    //SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

//slot 4*********************************************************
//================================================================
    
    
    //g1
    CNOT_rev(Error_vector, 1, 21);
    TQerror(Error_vector, 1, 21, probability * beta);
    
    //g2
    CNOT_rev(Error_vector, 3, 22);
    TQerror(Error_vector, 3, 22, probability * beta);
    
    //g3
    CNOT_rev(Error_vector, 6, 23);
    TQerror(Error_vector, 6, 23, probability * beta);
    
    
    //g4
    CNOT_rev(Error_vector, 8, 24);
    TQerror(Error_vector, 8, 24, probability * beta);
    
    //g5
    CNOT_rev(Error_vector, 10, 25);
    TQerror(Error_vector, 10, 25, probability * beta);
    
    
    //g6
    CNOT_rev(Error_vector, 12, 26);
    TQerror(Error_vector, 12, 26, probability * beta);
    
    //g8:Flag 2--------------------------
    CNOT_rev(Error_vector, 45, 28);
    TQerror(Error_vector, 45, 28, probability * beta);
    
    
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	SQerror(Error_vector, 41, probability*gamma);
    SQerror(Error_vector, 42, probability*gamma);
    SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    //SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
//slot 5*********************************************************
    
    
    //g1
    
    CNOT_rev(Error_vector, 4, 21);
    TQerror(Error_vector, 4, 21, probability * beta);
    //g2
    
    CNOT_rev(Error_vector, 5, 22);
    TQerror(Error_vector, 5, 22, probability * beta);
    
    //g3
    
    CNOT_rev(Error_vector, 9, 23);
    TQerror(Error_vector, 9, 23, probability * beta);
    
    
    //g4
    
    CNOT_rev(Error_vector, 12, 24);
    TQerror(Error_vector, 12, 24, probability * beta);
    
    
    //g5
    
    CNOT_rev(Error_vector, 13, 25);
    TQerror(Error_vector, 13, 25, probability * beta);
    
    
    //g6
    
    CNOT_rev(Error_vector, 16, 26);
    TQerror(Error_vector, 15, 26, probability * beta);
    
    
    //g8
    
    CNOT_rev(Error_vector, 15, 28);
    TQerror(Error_vector, 15, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    //SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	SQerror(Error_vector, 41, probability*gamma);
    SQerror(Error_vector, 42, probability*gamma);
    SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
    
    
//slot 6*********************************************************
    
    
    
    //g1:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 41, 21);
    TQerror(Error_vector, 41, 21, probability * beta);
    
    
    
    //g3:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 42, 23);
    TQerror(Error_vector, 42, 23, probability * beta);
    
    
    //g4:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 43, 24);
    TQerror(Error_vector, 43, 24, probability * beta);
    
    
    //g8
    
    CNOT_rev(Error_vector, 6, 28);
    TQerror(Error_vector, 6, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 21, probability*gamma);
    SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    SQerror(Error_vector, 25, probability*gamma);
    SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
//slot 7*********************************************************
    
    
    //g2:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 41, 22);
    TQerror(Error_vector, 41, 22, probability * beta);
    
    //g5:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 42, 25);
    TQerror(Error_vector, 42, 25, probability * beta);
    
    
    //g6:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 43, 26);
    TQerror(Error_vector, 43, 26, probability * beta);
    
    
    //g8:Flag 3--------------------------
    
    CNOT_rev(Error_vector, 46, 28);
    TQerror(Error_vector, 46, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    SQerror(Error_vector, 23, probability*gamma);
    SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
//slot 8*********************************************************
    
    
    //g1
    
    CNOT_rev(Error_vector, 2, 21);
    TQerror(Error_vector, 2, 21, probability * beta);
    
    
    
    //g2
    
    CNOT_rev(Error_vector, 6, 22);
    TQerror(Error_vector, 6, 22, probability * beta);
    
    //g3
    
    CNOT_rev(Error_vector, 10, 23);
    TQerror(Error_vector, 10, 23, probability * beta);
    
    
    
    //g4
    
    CNOT_rev(Error_vector, 11, 24);
    TQerror(Error_vector, 11, 24, probability * beta);
    
    
    //g5
    
    CNOT_rev(Error_vector, 14, 25);
    TQerror(Error_vector, 14, 25, probability * beta);
    
    
    //g6
    
    CNOT_rev(Error_vector, 15, 26);
    TQerror(Error_vector, 15, 26, probability * beta);
    
    //g7
    
    CNOT_rev(Error_vector, 12, 27);
    TQerror(Error_vector, 12, 27, probability * beta);
    
    
    //g8
    CNOT_rev(Error_vector, 3, 28);
    TQerror(Error_vector, 3, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    //SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    //SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
    
//slot 9*********************************************************
    
    //g7:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 47, 27);
    TQerror(Error_vector, 47, 27, probability * beta);
    
    //g8
    
    CNOT_rev(Error_vector, 7, 28);
    TQerror(Error_vector, 7, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
   
    SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
//slot 10*********************************************************
    
    //g7
    CNOT_rev(Error_vector, 8, 27);
    TQerror(Error_vector, 8, 27, probability * beta);
    
    
    //g8:Flag 1--------------------------
    CNOT_rev(Error_vector, 44, 28);
    TQerror(Error_vector, 44, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	

    //SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    SQerror(Error_vector, 46, probability*gamma);
    SQerror(Error_vector, 47, probability*gamma);

    
    
//slot 11*********************************************************
    
    //g7
    
    CNOT_rev(Error_vector, 17, 27);
    TQerror(Error_vector, 17, 27, probability * beta);
    
    //g8
    
    CNOT_rev(Error_vector, 4, 28);
    TQerror(Error_vector, 4, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    //SQerror(Error_vector, 17, probability*gamma);
	
	
    SQerror(Error_vector, 45, probability*gamma);
    SQerror(Error_vector, 46, probability*gamma);
    SQerror(Error_vector, 47, probability*gamma);
    
//slot 12*********************************************************
    
    
    //g7:Flag 1--------------------------
    CNOT_rev(Error_vector, 47, 27);
    TQerror(Error_vector, 47, 27, probability * beta);
    
    
    //g8:Flag 3--------------------------
    
    CNOT_rev(Error_vector, 46, 28);
    TQerror(Error_vector, 46, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	

    SQerror(Error_vector, 45, probability*gamma);
    
    
//slot 13*********************************************************
    
    //g7
    CNOT_rev(Error_vector, 16, 27);
    TQerror(Error_vector, 16, 27, probability * beta);
    
    //g8:Flag 2--------------------------
    CNOT_rev(Error_vector, 45, 28);
    TQerror(Error_vector, 45, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	

    
    
//slot 14*********************************************************
    
    
    //g8:Number F->I--------------------------
    CNOT_rev(Error_vector, 11, 28);
    TQerror(Error_vector, 11, 28, probability * beta);
    

    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	

    
    
//================================================================
    
    SQerror(Error_vector, 21, probability*alpha);
    SQerror(Error_vector, 22, probability*alpha);
    SQerror(Error_vector, 23, probability*alpha);
    SQerror(Error_vector, 24, probability*alpha);
    SQerror(Error_vector, 25, probability*alpha);
    SQerror(Error_vector, 26, probability*alpha);
    SQerror(Error_vector, 27, probability*alpha);
    SQerror(Error_vector, 28, probability*alpha);
    
    SQerror(Error_vector, 41, probability*alpha);
    SQerror(Error_vector, 42, probability*alpha);
    SQerror(Error_vector, 43, probability*alpha);
    SQerror(Error_vector, 44, probability*alpha);
    SQerror(Error_vector, 45, probability*alpha);
    SQerror(Error_vector, 46, probability*alpha);
    SQerror(Error_vector, 47, probability*alpha);
    
    
}



int parallel_flag(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta){
    
    
    SQerror(Error_vector, 21, probability);
    SQerror(Error_vector, 22, probability);
    SQerror(Error_vector, 23, probability);
    SQerror(Error_vector, 24, probability);
    SQerror(Error_vector, 25, probability);
    SQerror(Error_vector, 26, probability);
    SQerror(Error_vector, 27, probability);
    SQerror(Error_vector, 28, probability);
    
    SQerror(Error_vector, 41, probability);
    SQerror(Error_vector, 42, probability);
    SQerror(Error_vector, 43, probability);
    SQerror(Error_vector, 44, probability);
    SQerror(Error_vector, 45, probability);
    SQerror(Error_vector, 46, probability);
    SQerror(Error_vector, 47, probability);
    
    
    SQerror(Error_vector, 31, probability);
    SQerror(Error_vector, 32, probability);
    SQerror(Error_vector, 33, probability);
    SQerror(Error_vector, 34, probability);
    SQerror(Error_vector, 35, probability);
    SQerror(Error_vector, 36, probability);
    SQerror(Error_vector, 37, probability);
    SQerror(Error_vector, 38, probability);
    
    SQerror(Error_vector, 51, probability);
    SQerror(Error_vector, 52, probability);
    SQerror(Error_vector, 53, probability);
    SQerror(Error_vector, 54, probability);
    SQerror(Error_vector, 55, probability);
    SQerror(Error_vector, 56, probability);
    SQerror(Error_vector, 57, probability);
    
//================================================================
//================================================================
    

//slot 1*********************************************************
    //g1
    
    CNOT(Error_vector, 3, 21);
    TQerror(Error_vector, 3, 21, probability * beta);
    
    //g2
    CNOT(Error_vector, 1, 22);
    TQerror(Error_vector, 1, 22, probability * beta);
    
    //g3
    
    CNOT(Error_vector, 5, 23);
    TQerror(Error_vector, 5, 23, probability * beta);
    
    
    //g4
    CNOT(Error_vector, 7, 24);
    TQerror(Error_vector, 7, 24, probability * beta);
    
    
    //g5
    CNOT(Error_vector, 9, 25);
    TQerror(Error_vector, 9, 25, probability * beta);
    
    //g6
    
    CNOT(Error_vector, 11, 26);
    TQerror(Error_vector, 11, 26, probability * beta);
    
    
    //g8
    CNOT(Error_vector, 14, 28);
    TQerror(Error_vector, 14, 28, probability * beta);
    
    
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
//slot 2*********************************************************
    
    
    //g1:Flag 1--------------------------
    CNOT(Error_vector, 41, 21);
    TQerror(Error_vector, 41, 21, probability * beta);
    
    //g3:Flag 1--------------------------
    CNOT(Error_vector, 42, 23);
    TQerror(Error_vector, 42, 23, probability * beta);
    
    //g4:Flag 1--------------------------
    CNOT(Error_vector, 43, 24);
    TQerror(Error_vector, 43, 24, probability * beta);
    
    //g8:Flag 1--------------------------
    CNOT(Error_vector, 44, 28);
    TQerror(Error_vector, 44, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //SQerror(Error_vector, 21, probability*gamma);
    SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    SQerror(Error_vector, 25, probability*gamma);
    SQerror(Error_vector, 26, probability*gamma);
    SQerror(Error_vector, 27, probability*gamma);
    SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    //SQerror(Error_vector, 44, probability*gamma);
    //SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
//slot 3*********************************************************
    //================================================================
    
    
    //g2:Flag 1--------------------------
    CNOT(Error_vector, 41, 22);
    TQerror(Error_vector, 41, 22, probability * beta);
    
    //g5:Flag 1--------------------------
    CNOT(Error_vector, 42, 25);
    TQerror(Error_vector, 42, 25, probability * beta);
    
    //g6:Flag 1--------------------------
    CNOT(Error_vector, 43, 26);
    TQerror(Error_vector, 43, 26, probability * beta);
    
    //g8:
    
    CNOT(Error_vector, 10, 28);
    TQerror(Error_vector, 10, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    SQerror(Error_vector, 23, probability*gamma);
    SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    //SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

//slot 4*********************************************************
//================================================================
    
    
    //g1
    CNOT(Error_vector, 1, 21);
    TQerror(Error_vector, 1, 21, probability * beta);
    
    //g2
    CNOT(Error_vector, 3, 22);
    TQerror(Error_vector, 3, 22, probability * beta);
    
    //g3
    CNOT(Error_vector, 6, 23);
    TQerror(Error_vector, 6, 23, probability * beta);
    
    
    //g4
    CNOT(Error_vector, 8, 24);
    TQerror(Error_vector, 8, 24, probability * beta);
    
    //g5
    CNOT(Error_vector, 10, 25);
    TQerror(Error_vector, 10, 25, probability * beta);
    
    
    //g6
    CNOT(Error_vector, 12, 26);
    TQerror(Error_vector, 12, 26, probability * beta);
    
    //g8:Flag 2--------------------------
    CNOT(Error_vector, 45, 28);
    TQerror(Error_vector, 45, 28, probability * beta);
    
    
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	SQerror(Error_vector, 41, probability*gamma);
    SQerror(Error_vector, 42, probability*gamma);
    SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    //SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
//slot 5*********************************************************
    
    
    //g1
    
    CNOT(Error_vector, 4, 21);
    TQerror(Error_vector, 4, 21, probability * beta);
    //g2
    
    CNOT(Error_vector, 5, 22);
    TQerror(Error_vector, 5, 22, probability * beta);
    
    //g3
    
    CNOT(Error_vector, 9, 23);
    TQerror(Error_vector, 9, 23, probability * beta);
    
    
    //g4
    
    CNOT(Error_vector, 12, 24);
    TQerror(Error_vector, 12, 24, probability * beta);
    
    
    //g5
    
    CNOT(Error_vector, 13, 25);
    TQerror(Error_vector, 13, 25, probability * beta);
    
    
    //g6
    
    CNOT(Error_vector, 16, 26);
    TQerror(Error_vector, 15, 26, probability * beta);
    
    
    //g8
    
    CNOT(Error_vector, 15, 28);
    TQerror(Error_vector, 15, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    //SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	SQerror(Error_vector, 41, probability*gamma);
    SQerror(Error_vector, 42, probability*gamma);
    SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
    
    
//slot 6*********************************************************
    
    
    
    //g1:Flag 1--------------------------
    
    CNOT(Error_vector, 41, 21);
    TQerror(Error_vector, 41, 21, probability * beta);
    
    
    
    //g3:Flag 1--------------------------
    
    CNOT(Error_vector, 42, 23);
    TQerror(Error_vector, 42, 23, probability * beta);
    
    
    //g4:Flag 1--------------------------
    
    CNOT(Error_vector, 43, 24);
    TQerror(Error_vector, 43, 24, probability * beta);
    
    
    //g8
    
    CNOT(Error_vector, 6, 28);
    TQerror(Error_vector, 6, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 21, probability*gamma);
    SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    SQerror(Error_vector, 25, probability*gamma);
    SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
//slot 7*********************************************************
    
    
    //g2:Flag 1--------------------------
    
    CNOT(Error_vector, 41, 22);
    TQerror(Error_vector, 41, 22, probability * beta);
    
    //g5:Flag 1--------------------------
    
    CNOT(Error_vector, 42, 25);
    TQerror(Error_vector, 42, 25, probability * beta);
    
    
    //g6:Flag 1--------------------------
    
    CNOT(Error_vector, 43, 26);
    TQerror(Error_vector, 43, 26, probability * beta);
    
    
    //g8:Flag 3--------------------------
    
    CNOT(Error_vector, 46, 28);
    TQerror(Error_vector, 46, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    SQerror(Error_vector, 23, probability*gamma);
    SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    //SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
//slot 8*********************************************************
    
    
    //g1
    
    CNOT(Error_vector, 2, 21);
    TQerror(Error_vector, 2, 21, probability * beta);
    
    
    
    //g2
    
    CNOT(Error_vector, 6, 22);
    TQerror(Error_vector, 6, 22, probability * beta);
    
    //g3
    
    CNOT(Error_vector, 10, 23);
    TQerror(Error_vector, 10, 23, probability * beta);
    
    
    
    //g4
    
    CNOT(Error_vector, 11, 24);
    TQerror(Error_vector, 11, 24, probability * beta);
    
    
    //g5
    
    CNOT(Error_vector, 14, 25);
    TQerror(Error_vector, 14, 25, probability * beta);
    
    
    //g6
    
    CNOT(Error_vector, 15, 26);
    TQerror(Error_vector, 15, 26, probability * beta);
    
    //g7
    
    CNOT(Error_vector, 12, 27);
    TQerror(Error_vector, 12, 27, probability * beta);
    
    
    //g8
    CNOT(Error_vector, 3, 28);
    TQerror(Error_vector, 3, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    //SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 21, probability*gamma);
    //SQerror(Error_vector, 22, probability*gamma);
    //SQerror(Error_vector, 23, probability*gamma);
    //SQerror(Error_vector, 24, probability*gamma);
    //SQerror(Error_vector, 25, probability*gamma);
    //SQerror(Error_vector, 26, probability*gamma);
    //SQerror(Error_vector, 27, probability*gamma);
    //SQerror(Error_vector, 28, probability*gamma);
	//SQerror(Error_vector, 41, probability*gamma);
    //SQerror(Error_vector, 42, probability*gamma);
    //SQerror(Error_vector, 43, probability*gamma);
    //SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
    
//slot 9*********************************************************
    
    //g7:Flag 1--------------------------
    
    CNOT(Error_vector, 47, 27);
    TQerror(Error_vector, 47, 27, probability * beta);
    
    //g8
    
    CNOT(Error_vector, 7, 28);
    TQerror(Error_vector, 7, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
   
    SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    SQerror(Error_vector, 46, probability*gamma);
    //SQerror(Error_vector, 47, probability*gamma);

    
    
//slot 10*********************************************************
    
    //g7
    CNOT(Error_vector, 8, 27);
    TQerror(Error_vector, 8, 27, probability * beta);
    
    
    //g8:Flag 1--------------------------
    CNOT(Error_vector, 44, 28);
    TQerror(Error_vector, 44, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	

    //SQerror(Error_vector, 44, probability*gamma);
    SQerror(Error_vector, 45, probability*gamma);
    SQerror(Error_vector, 46, probability*gamma);
    SQerror(Error_vector, 47, probability*gamma);

    
    
//slot 11*********************************************************
    
    //g7
    
    CNOT(Error_vector, 17, 27);
    TQerror(Error_vector, 17, 27, probability * beta);
    
    //g8
    
    CNOT(Error_vector, 4, 28);
    TQerror(Error_vector, 4, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    //SQerror(Error_vector, 17, probability*gamma);
	
	
    SQerror(Error_vector, 45, probability*gamma);
    SQerror(Error_vector, 46, probability*gamma);
    SQerror(Error_vector, 47, probability*gamma);
    
//slot 12*********************************************************
    
    
    //g7:Flag 1--------------------------
    CNOT(Error_vector, 47, 27);
    TQerror(Error_vector, 47, 27, probability * beta);
    
    
    //g8:Flag 3--------------------------
    
    CNOT(Error_vector, 46, 28);
    TQerror(Error_vector, 46, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	

    SQerror(Error_vector, 45, probability*gamma);
    
    
//slot 13*********************************************************
    
    //g7
    CNOT(Error_vector, 16, 27);
    TQerror(Error_vector, 16, 27, probability * beta);
    
    //g8:Flag 2--------------------------
    CNOT(Error_vector, 45, 28);
    TQerror(Error_vector, 45, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	

    
    
//slot 14*********************************************************
    
    
    //g8:Number F->I--------------------------
    CNOT(Error_vector, 11, 28);
    TQerror(Error_vector, 11, 28, probability * beta);
    

    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	

    
    
//================================================================  
//================================================================
//================================================================  
//================================================================
// X-type stabilizer



    
//slot 1*********************************************************
    //g1
    
    CNOT_rev(Error_vector, 3, 31);
    TQerror(Error_vector, 3, 31, probability * beta);
    
    //g2
    CNOT_rev(Error_vector, 1, 32);
    TQerror(Error_vector, 1, 32, probability * beta);
    
    //g3
    
    CNOT_rev(Error_vector, 5, 33);
    TQerror(Error_vector, 5, 33, probability * beta);
    
    
    //g4
    CNOT_rev(Error_vector, 7, 34);
    TQerror(Error_vector, 7, 34, probability * beta);
    
    
    //g5
    CNOT_rev(Error_vector, 9, 35);
    TQerror(Error_vector, 9, 35, probability * beta);
    
    //g6
    
    CNOT_rev(Error_vector, 11, 36);
    TQerror(Error_vector, 11, 36, probability * beta);
    
    
    //g8
    CNOT_rev(Error_vector, 14, 38);
    TQerror(Error_vector, 14, 38, probability * beta);
    
    
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
//slot 2*********************************************************
    
    
    //g1:Flag 1--------------------------
    CNOT_rev(Error_vector, 51, 31);
    TQerror(Error_vector, 51, 31, probability * beta);
    
    //g3:Flag 1--------------------------
    CNOT_rev(Error_vector, 52, 33);
    TQerror(Error_vector, 52, 33, probability * beta);
    
    //g4:Flag 1--------------------------
    CNOT_rev(Error_vector, 53, 34);
    TQerror(Error_vector, 53, 34, probability * beta);
    
    //g8:Flag 1--------------------------
    CNOT_rev(Error_vector, 54, 38);
    TQerror(Error_vector, 54, 38, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //SQerror(Error_vector, 31, probability*gamma);
    SQerror(Error_vector, 32, probability*gamma);
    //SQerror(Error_vector, 33, probability*gamma);
    //SQerror(Error_vector, 34, probability*gamma);
    SQerror(Error_vector, 35, probability*gamma);
    SQerror(Error_vector, 36, probability*gamma);
    SQerror(Error_vector, 37, probability*gamma);
    SQerror(Error_vector, 38, probability*gamma);
	//SQerror(Error_vector, 51, probability*gamma);
    //SQerror(Error_vector, 52, probability*gamma);
    //SQerror(Error_vector, 53, probability*gamma);
    //SQerror(Error_vector, 54, probability*gamma);
    //SQerror(Error_vector, 55, probability*gamma);
    //SQerror(Error_vector, 56, probability*gamma);
    //SQerror(Error_vector, 57, probability*gamma);

    
//slot 3*********************************************************
    //================================================================
    
    
    //g2:Flag 1--------------------------
    CNOT_rev(Error_vector, 51, 32);
    TQerror(Error_vector, 51, 32, probability * beta);
    
    //g5:Flag 1--------------------------
    CNOT_rev(Error_vector, 52, 35);
    TQerror(Error_vector, 52, 35, probability * beta);
    
    //g6:Flag 1--------------------------
    CNOT_rev(Error_vector, 53, 36);
    TQerror(Error_vector, 53, 36, probability * beta);
    
    //g8:
    
    CNOT_rev(Error_vector, 10, 38);
    TQerror(Error_vector, 10, 38, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    SQerror(Error_vector, 31, probability*gamma);
    //SQerror(Error_vector, 32, probability*gamma);
    SQerror(Error_vector, 33, probability*gamma);
    SQerror(Error_vector, 34, probability*gamma);
    //SQerror(Error_vector, 35, probability*gamma);
    //SQerror(Error_vector, 36, probability*gamma);
    //SQerror(Error_vector, 37, probability*gamma);
    //SQerror(Error_vector, 38, probability*gamma);
	//SQerror(Error_vector, 51, probability*gamma);
    //SQerror(Error_vector, 52, probability*gamma);
    //SQerror(Error_vector, 53, probability*gamma);
    SQerror(Error_vector, 54, probability*gamma);
    //SQerror(Error_vector, 55, probability*gamma);
    //SQerror(Error_vector, 56, probability*gamma);
    //SQerror(Error_vector, 57, probability*gamma);

//slot 4*********************************************************
//================================================================
    
    
    //g1
    CNOT_rev(Error_vector, 1, 31);
    TQerror(Error_vector, 1, 31, probability * beta);
    
    //g2
    CNOT_rev(Error_vector, 3, 32);
    TQerror(Error_vector, 3, 32, probability * beta);
    
    //g3
    CNOT_rev(Error_vector, 6, 33);
    TQerror(Error_vector, 6, 33, probability * beta);
    
    
    //g4
    CNOT_rev(Error_vector, 8, 34);
    TQerror(Error_vector, 8, 34, probability * beta);
    
    //g5
    CNOT_rev(Error_vector, 10, 35);
    TQerror(Error_vector, 10, 35, probability * beta);
    
    
    //g6
    CNOT_rev(Error_vector, 12, 36);
    TQerror(Error_vector, 12, 36, probability * beta);
    
    //g8:Flag 2--------------------------
    CNOT_rev(Error_vector, 55, 38);
    TQerror(Error_vector, 55, 38, probability * beta);
    
    
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 31, probability*gamma);
    //SQerror(Error_vector, 32, probability*gamma);
    //SQerror(Error_vector, 33, probability*gamma);
    //SQerror(Error_vector, 34, probability*gamma);
    //SQerror(Error_vector, 35, probability*gamma);
    //SQerror(Error_vector, 36, probability*gamma);
    //SQerror(Error_vector, 37, probability*gamma);
    //SQerror(Error_vector, 38, probability*gamma);
	SQerror(Error_vector, 51, probability*gamma);
    SQerror(Error_vector, 52, probability*gamma);
    SQerror(Error_vector, 53, probability*gamma);
    SQerror(Error_vector, 54, probability*gamma);
    //SQerror(Error_vector, 55, probability*gamma);
    //SQerror(Error_vector, 56, probability*gamma);
    //SQerror(Error_vector, 57, probability*gamma);

    
    
//slot 5*********************************************************
    
    
    //g1
    
    CNOT_rev(Error_vector, 4, 31);
    TQerror(Error_vector, 4, 31, probability * beta);
    //g2
    
    CNOT_rev(Error_vector, 5, 32);
    TQerror(Error_vector, 5, 32, probability * beta);
    
    //g3
    
    CNOT_rev(Error_vector, 9, 33);
    TQerror(Error_vector, 9, 33, probability * beta);
    
    
    //g4
    
    CNOT_rev(Error_vector, 12, 34);
    TQerror(Error_vector, 12, 34, probability * beta);
    
    
    //g5
    
    CNOT_rev(Error_vector, 13, 35);
    TQerror(Error_vector, 13, 35, probability * beta);
    
    
    //g6
    
    CNOT_rev(Error_vector, 16, 36);
    TQerror(Error_vector, 15, 36, probability * beta);
    
    
    //g8
    
    CNOT_rev(Error_vector, 15, 38);
    TQerror(Error_vector, 15, 38, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    //SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 31, probability*gamma);
    //SQerror(Error_vector, 32, probability*gamma);
    //SQerror(Error_vector, 33, probability*gamma);
    //SQerror(Error_vector, 34, probability*gamma);
    //SQerror(Error_vector, 35, probability*gamma);
    //SQerror(Error_vector, 36, probability*gamma);
    //SQerror(Error_vector, 37, probability*gamma);
    //SQerror(Error_vector, 38, probability*gamma);
	SQerror(Error_vector, 51, probability*gamma);
    SQerror(Error_vector, 52, probability*gamma);
    SQerror(Error_vector, 53, probability*gamma);
    SQerror(Error_vector, 54, probability*gamma);
    SQerror(Error_vector, 55, probability*gamma);
    //SQerror(Error_vector, 56, probability*gamma);
    //SQerror(Error_vector, 57, probability*gamma);

    
    
    
    
//slot 6*********************************************************
    
    
    
    //g1:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 51, 31);
    TQerror(Error_vector, 51, 31, probability * beta);
    
    
    
    //g3:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 52, 33);
    TQerror(Error_vector, 52, 33, probability * beta);
    
    
    //g4:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 53, 34);
    TQerror(Error_vector, 53, 34, probability * beta);
    
    
    //g8
    
    CNOT_rev(Error_vector, 6, 38);
    TQerror(Error_vector, 6, 38, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 31, probability*gamma);
    SQerror(Error_vector, 32, probability*gamma);
    //SQerror(Error_vector, 33, probability*gamma);
    //SQerror(Error_vector, 34, probability*gamma);
    SQerror(Error_vector, 35, probability*gamma);
    SQerror(Error_vector, 36, probability*gamma);
    //SQerror(Error_vector, 37, probability*gamma);
    //SQerror(Error_vector, 38, probability*gamma);
	//SQerror(Error_vector, 51, probability*gamma);
    //SQerror(Error_vector, 52, probability*gamma);
    //SQerror(Error_vector, 53, probability*gamma);
    SQerror(Error_vector, 54, probability*gamma);
    SQerror(Error_vector, 55, probability*gamma);
    //SQerror(Error_vector, 56, probability*gamma);
    //SQerror(Error_vector, 57, probability*gamma);

    
//slot 7*********************************************************
    
    
    //g2:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 51, 32);
    TQerror(Error_vector, 51, 32, probability * beta);
    
    //g5:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 52, 35);
    TQerror(Error_vector, 52, 35, probability * beta);
    
    
    //g6:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 53, 36);
    TQerror(Error_vector, 53, 36, probability * beta);
    
    
    //g8:Flag 3--------------------------
    
    CNOT_rev(Error_vector, 56, 38);
    TQerror(Error_vector, 56, 38, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    SQerror(Error_vector, 31, probability*gamma);
    //SQerror(Error_vector, 32, probability*gamma);
    SQerror(Error_vector, 33, probability*gamma);
    SQerror(Error_vector, 34, probability*gamma);
    //SQerror(Error_vector, 35, probability*gamma);
    //SQerror(Error_vector, 36, probability*gamma);
    //SQerror(Error_vector, 37, probability*gamma);
    //SQerror(Error_vector, 38, probability*gamma);
	//SQerror(Error_vector, 51, probability*gamma);
    //SQerror(Error_vector, 52, probability*gamma);
    //SQerror(Error_vector, 53, probability*gamma);
    SQerror(Error_vector, 54, probability*gamma);
    SQerror(Error_vector, 55, probability*gamma);
    //SQerror(Error_vector, 56, probability*gamma);
    //SQerror(Error_vector, 57, probability*gamma);

    
    
//slot 8*********************************************************
    
    
    //g1
    
    CNOT_rev(Error_vector, 2, 31);
    TQerror(Error_vector, 2, 31, probability * beta);
    
    
    
    //g2
    
    CNOT_rev(Error_vector, 6, 32);
    TQerror(Error_vector, 6, 32, probability * beta);
    
    //g3
    
    CNOT_rev(Error_vector, 10, 33);
    TQerror(Error_vector, 10, 33, probability * beta);
    
    
    
    //g4
    
    CNOT_rev(Error_vector, 11, 34);
    TQerror(Error_vector, 11, 34, probability * beta);
    
    
    //g5
    
    CNOT_rev(Error_vector, 14, 35);
    TQerror(Error_vector, 14, 35, probability * beta);
    
    
    //g6
    
    CNOT_rev(Error_vector, 15, 36);
    TQerror(Error_vector, 15, 36, probability * beta);
    
    //g7
    
    CNOT_rev(Error_vector, 12, 37);
    TQerror(Error_vector, 12, 37, probability * beta);
    
    
    //g8
    CNOT_rev(Error_vector, 3, 38);
    TQerror(Error_vector, 3, 38, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    //SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
    //SQerror(Error_vector, 31, probability*gamma);
    //SQerror(Error_vector, 32, probability*gamma);
    //SQerror(Error_vector, 33, probability*gamma);
    //SQerror(Error_vector, 34, probability*gamma);
    //SQerror(Error_vector, 35, probability*gamma);
    //SQerror(Error_vector, 36, probability*gamma);
    //SQerror(Error_vector, 37, probability*gamma);
    //SQerror(Error_vector, 38, probability*gamma);
	//SQerror(Error_vector, 51, probability*gamma);
    //SQerror(Error_vector, 52, probability*gamma);
    //SQerror(Error_vector, 53, probability*gamma);
    //SQerror(Error_vector, 54, probability*gamma);
    SQerror(Error_vector, 55, probability*gamma);
    SQerror(Error_vector, 56, probability*gamma);
    //SQerror(Error_vector, 57, probability*gamma);

    
    
    
//slot 9*********************************************************
    
    //g7:Flag 1--------------------------
    
    CNOT_rev(Error_vector, 57, 37);
    TQerror(Error_vector, 57, 37, probability * beta);
    
    //g8
    
    CNOT_rev(Error_vector, 7, 38);
    TQerror(Error_vector, 7, 38, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	
   
    SQerror(Error_vector, 54, probability*gamma);
    SQerror(Error_vector, 55, probability*gamma);
    SQerror(Error_vector, 56, probability*gamma);
    //SQerror(Error_vector, 57, probability*gamma);

    
    
//slot 10*********************************************************
    
    //g7
    CNOT_rev(Error_vector, 8, 37);
    TQerror(Error_vector, 8, 37, probability * beta);
    
    
    //g8:Flag 1--------------------------
    CNOT_rev(Error_vector, 54, 38);
    TQerror(Error_vector, 54, 38, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	

    //SQerror(Error_vector, 54, probability*gamma);
    SQerror(Error_vector, 55, probability*gamma);
    SQerror(Error_vector, 56, probability*gamma);
    SQerror(Error_vector, 57, probability*gamma);

    
    
//slot 11*********************************************************
    
    //g7
    
    CNOT_rev(Error_vector, 17, 37);
    TQerror(Error_vector, 17, 37, probability * beta);
    
    //g8
    
    CNOT_rev(Error_vector, 4, 38);
    TQerror(Error_vector, 4, 38, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    //SQerror(Error_vector, 17, probability*gamma);
	
	
    SQerror(Error_vector, 55, probability*gamma);
    SQerror(Error_vector, 56, probability*gamma);
    SQerror(Error_vector, 57, probability*gamma);
    
//slot 12*********************************************************
    
    
    //g7:Flag 1--------------------------
    CNOT_rev(Error_vector, 57, 37);
    TQerror(Error_vector, 57, 37, probability * beta);
    
    
    //g8:Flag 3--------------------------
    
    CNOT_rev(Error_vector, 56, 38);
    TQerror(Error_vector, 56, 38, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	

    SQerror(Error_vector, 55, probability*gamma);
    
    
//slot 13*********************************************************
    
    //g7
    CNOT_rev(Error_vector, 16, 37);
    TQerror(Error_vector, 16, 37, probability * beta);
    
    //g8:Flag 2--------------------------
    CNOT_rev(Error_vector, 55, 38);
    TQerror(Error_vector, 55, 38, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
	

    
    
//slot 14*********************************************************
    
    
    //g8:Number F->I--------------------------
    CNOT_rev(Error_vector, 11, 38);
    TQerror(Error_vector, 11, 38, probability * beta);
    

    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);



  
//================================================================  
//================================================================

    SQerror(Error_vector, 21, probability*alpha);
    SQerror(Error_vector, 22, probability*alpha);
    SQerror(Error_vector, 23, probability*alpha);
    SQerror(Error_vector, 24, probability*alpha);
    SQerror(Error_vector, 25, probability*alpha);
    SQerror(Error_vector, 26, probability*alpha);
    SQerror(Error_vector, 27, probability*alpha);
    SQerror(Error_vector, 28, probability*alpha);
    
    SQerror(Error_vector, 41, probability*alpha);
    SQerror(Error_vector, 42, probability*alpha);
    SQerror(Error_vector, 43, probability*alpha);
    SQerror(Error_vector, 44, probability*alpha);
    SQerror(Error_vector, 45, probability*alpha);
    SQerror(Error_vector, 46, probability*alpha);
    SQerror(Error_vector, 47, probability*alpha);



    SQerror(Error_vector, 31, probability*alpha);
    SQerror(Error_vector, 32, probability*alpha);
    SQerror(Error_vector, 33, probability*alpha);
    SQerror(Error_vector, 34, probability*alpha);
    SQerror(Error_vector, 35, probability*alpha);
    SQerror(Error_vector, 36, probability*alpha);
    SQerror(Error_vector, 37, probability*alpha);
    SQerror(Error_vector, 38, probability*alpha);
    
    SQerror(Error_vector, 51, probability*alpha);
    SQerror(Error_vector, 52, probability*alpha);
    SQerror(Error_vector, 53, probability*alpha);
    SQerror(Error_vector, 54, probability*alpha);
    SQerror(Error_vector, 55, probability*alpha);
    SQerror(Error_vector, 56, probability*alpha);
    SQerror(Error_vector, 57, probability*alpha);
    
    
    
}


//------------------------------------------------------------------------------------------------------------------------------

int x_circuit(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta){
    
    /*
     * gz1=[1,2,3,4 ];
     * gz2=[1,3,5,6 ];
     * gz3=[5,6,9,10 ];
     * gz4=[7,8,11,12 ];
     * gz5=[9,10,13,14 ];
     * gz6=[11,12,15,16 ];
     * gz7=[8,12,16,17 ];
     * gz8=[3,4,6,7,10,11,14,15 ];
     */
    
// gz1=[1,2,3,4 ];
    
    CNOT(Error_vector, 1, 21);
    CNOT(Error_vector, 2, 21);
    CNOT(Error_vector, 3, 21);
    CNOT(Error_vector, 4, 21);
    
// gz2=[1,3,5,6 ];
    
    CNOT(Error_vector, 1, 22);
    CNOT(Error_vector, 3, 22);
    CNOT(Error_vector, 5, 22);
    CNOT(Error_vector, 6, 22);
    
// gz3=[5,6,9,10 ];
    
    CNOT(Error_vector, 5, 23);
    CNOT(Error_vector, 6, 23);
    CNOT(Error_vector, 9, 23);
    CNOT(Error_vector, 10, 23);
    
// gz4=[7,8,11,12 ];
    
    CNOT(Error_vector, 7, 24);
    CNOT(Error_vector, 8, 24);
    CNOT(Error_vector, 11, 24);
    CNOT(Error_vector, 12, 24);
    
//  gz5=[9,10,13,14 ];
    
    CNOT(Error_vector, 9, 25);
    CNOT(Error_vector, 10, 25);
    CNOT(Error_vector, 13, 25);
    CNOT(Error_vector, 14, 25);
    
// gz6=[11,12,15,16 ];
    
    CNOT(Error_vector, 11, 26);
    CNOT(Error_vector, 12, 26);
    CNOT(Error_vector, 15, 26);
    CNOT(Error_vector, 16, 26);
    
// gz7=[8,12,16,17 ];
    
    CNOT(Error_vector, 8, 27);
    CNOT(Error_vector, 12, 27);
    CNOT(Error_vector, 16, 27);
    CNOT(Error_vector, 17, 27);
    
    
// gz8=[3,4,6,7,10,11,14,15 ];
    
    CNOT(Error_vector, 3, 28);
    CNOT(Error_vector, 4, 28);
    CNOT(Error_vector, 6, 28);
    CNOT(Error_vector, 7, 28);
    CNOT(Error_vector, 10, 28);
    CNOT(Error_vector, 11, 28);
    CNOT(Error_vector, 14, 28);
    CNOT(Error_vector, 15, 28);
    
    
//add measurement error
    /*
     * SQerror(Error_vector, 61, probability*alpha);
     * SQerror(Error_vector, 62, probability*alpha);
     * SQerror(Error_vector, 63, probability*alpha);
     * SQerror(Error_vector, 64, probability*alpha);
     * SQerror(Error_vector, 65, probability*alpha);
     * SQerror(Error_vector, 66, probability*alpha);
     * SQerror(Error_vector, 67, probability*alpha);
     * SQerror(Error_vector, 68, probability*alpha);
     * SQerror(Error_vector, 69, probability*alpha);
     * SQerror(Error_vector, 70, probability*alpha);
     * SQerror(Error_vector, 71, probability*alpha);
     * SQerror(Error_vector, 72, probability*alpha);
     * SQerror(Error_vector, 73, probability*alpha);
     * SQerror(Error_vector, 74, probability*alpha);
     * SQerror(Error_vector, 75, probability*alpha);
     * SQerror(Error_vector, 76, probability*alpha);
     * SQerror(Error_vector, 77, probability*alpha);
     * SQerror(Error_vector, 78, probability*alpha);
     * SQerror(Error_vector, 79, probability*alpha);
     * SQerror(Error_vector, 80, probability*alpha);
     */
    
}

int z_circuit(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta){
    
// gx1=[1,2,3,4 ];
    
    CNOT(Error_vector, 31, 1);
    CNOT(Error_vector, 31, 2);
    CNOT(Error_vector, 31, 3);
    CNOT(Error_vector, 31, 4);
    
// gx2=[1,3,5,6 ];
    
    CNOT(Error_vector, 32, 1);
    CNOT(Error_vector, 32, 3);
    CNOT(Error_vector, 32, 5);
    CNOT(Error_vector, 32, 6);
    
// gx3=[5,6,9,10 ];
    
    CNOT(Error_vector, 33, 5);
    CNOT(Error_vector, 33, 6);
    CNOT(Error_vector, 33, 9);
    CNOT(Error_vector, 33, 10);
    
// gx4=[7,8,11,12 ];
    
    CNOT(Error_vector, 34, 7);
    CNOT(Error_vector, 34, 8);
    CNOT(Error_vector, 34, 11);
    CNOT(Error_vector, 34, 12);
    
// gx5=[9,10,13,14 ];
    
    CNOT(Error_vector, 35, 9);
    CNOT(Error_vector, 35, 10);
    CNOT(Error_vector, 35, 13);
    CNOT(Error_vector, 35, 14);
    
// gx6=[11,12,15,16 ];
    
    CNOT(Error_vector, 36, 11);
    CNOT(Error_vector, 36, 12);
    CNOT(Error_vector, 36, 15);
    CNOT(Error_vector, 36, 16);
    
// gx7=[8,12,16,17 ];
    
    CNOT(Error_vector, 37, 8);
    CNOT(Error_vector, 37, 12);
    CNOT(Error_vector, 37, 16);
    CNOT(Error_vector, 37, 17);
    
// gx8=[3,4,6,7,10,11,14,15 ];
    
    CNOT(Error_vector, 38, 3);
    CNOT(Error_vector, 38, 4);
    CNOT(Error_vector, 38, 6);
    CNOT(Error_vector, 38, 7);
    CNOT(Error_vector, 38, 10);
    CNOT(Error_vector, 38, 11);
    CNOT(Error_vector, 38, 14);
    CNOT(Error_vector, 38, 15);
    
    /*
     * //add measurement error
     * SQerror(Error_vector, 41, probability*alpha);
     * SQerror(Error_vector, 42, probability*alpha);
     * SQerror(Error_vector, 43, probability*alpha);
     * SQerror(Error_vector, 44, probability*alpha);
     * SQerror(Error_vector, 45, probability*alpha);
     * SQerror(Error_vector, 46, probability*alpha);
     * SQerror(Error_vector, 47, probability*alpha);
     * SQerror(Error_vector, 48, probability*alpha);
     * SQerror(Error_vector, 49, probability*alpha);
     * SQerror(Error_vector, 50, probability*alpha);
     * SQerror(Error_vector, 51, probability*alpha);
     * SQerror(Error_vector, 52, probability*alpha);
     * SQerror(Error_vector, 53, probability*alpha);
     * SQerror(Error_vector, 54, probability*alpha);
     * SQerror(Error_vector, 55, probability*alpha);
     * SQerror(Error_vector, 56, probability*alpha);
     * SQerror(Error_vector, 57, probability*alpha);
     * SQerror(Error_vector, 58, probability*alpha);
     * SQerror(Error_vector, 59, probability*alpha);
     * SQerror(Error_vector, 60, probability*alpha);
     */
}


int unflagged(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta ){
    
    
    SQerror(Error_vector, 21, probability*alpha);
    SQerror(Error_vector, 22, probability*alpha);
    SQerror(Error_vector, 23, probability*alpha);
    SQerror(Error_vector, 24, probability*alpha);
    SQerror(Error_vector, 25, probability*alpha);
    SQerror(Error_vector, 26, probability*alpha);
    SQerror(Error_vector, 27, probability*alpha);
    SQerror(Error_vector, 28, probability*alpha);
    

    

//==============================================================================
//==============================================================================	
  
// gz1=[1,2,3,4 ]======number 2=============================;
    CNOT(Error_vector, 2, 21);
    TQerror(Error_vector, 2, 21, probability * beta);
     
  
// gz2=[1,3,5,6 ]======number 1=============================;
    
    CNOT(Error_vector, 1, 22);
    TQerror(Error_vector, 1, 22, probability * beta);
    
  
// gz3=[5,6,9,10 ]======number 1=============================;
    
    CNOT(Error_vector, 5, 23);
    TQerror(Error_vector, 5, 23, probability * beta);
// gz4=[7,8,11,12 ]======number 1=============================;
    
    CNOT(Error_vector, 7, 24);
    TQerror(Error_vector, 7, 24, probability * beta);  

//  gz5=[9,10,13,14 ]======number 1=============================; 
    
    CNOT(Error_vector, 9, 25);
    TQerror(Error_vector, 9, 25, probability * beta);

// gz6=[11,12,15,16 ]======number 2=============================; 
    CNOT(Error_vector, 12, 26);
    TQerror(Error_vector, 12, 26, probability * beta);
    

// gz7=[8,12,16,17 ]======number 1=============================; 
    CNOT(Error_vector, 8, 27);
    TQerror(Error_vector, 8, 27, probability * beta);
    
// gz8=[3,4,6,7,10,11,14,15 ]======number 1=============================;  
    
    CNOT(Error_vector, 3, 28);
    TQerror(Error_vector, 3, 28, probability * beta);
    
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
  
  
//==============================================================================
//==============================================================================	

 // gz1=[1,2,3,4 ]======number 1=============================;
    
    CNOT(Error_vector, 1, 21);
    TQerror(Error_vector, 1, 21, probability * beta);

    
 
// gz2=[1,3,5,6 ]======number 2=============================;
    CNOT(Error_vector, 3, 22);
    TQerror(Error_vector, 3, 22, probability * beta);
      
    
// gz3=[5,6,9,10 ]======number 2=============================; 
    CNOT(Error_vector, 6, 23);
    TQerror(Error_vector, 6, 23, probability * beta);
// gz4=[7,8,11,12 ]======number 2=============================; 
    CNOT(Error_vector, 8, 24);
    TQerror(Error_vector, 8, 24, probability * beta);
   

//  gz5=[9,10,13,14 ]======number 2=============================;  
    CNOT(Error_vector, 10, 25);
    TQerror(Error_vector, 10, 25, probability * beta);
// gz6=[11,12,15,16 ]======number 1=============================; 
    
    CNOT(Error_vector, 11, 26);
    TQerror(Error_vector, 11, 26, probability * beta);
// gz7=[8,12,16,17 ]======number 2=============================;  
    CNOT(Error_vector, 12, 27);
    TQerror(Error_vector, 12, 27, probability * beta);
    
// gz8=[3,4,6,7,10,11,14,15 ]======number 2=============================; 
    CNOT(Error_vector, 4, 28);
    TQerror(Error_vector, 4, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);



//==============================================================================
//==============================================================================	
  

// gz1=[1,2,3,4 ]======number 3=============================;
    CNOT(Error_vector, 3, 21);
    TQerror(Error_vector, 3, 21, probability * beta);
    
// gz2=[1,3,5,6 ]======number 3=============================;
    CNOT(Error_vector, 5, 22);
    TQerror(Error_vector, 5, 22, probability * beta);
    
// gz3=[5,6,9,10 ]======number 3=============================;
    CNOT(Error_vector, 9, 23);
    TQerror(Error_vector, 9, 23, probability * beta);
// gz4=[7,8,11,12 ]======number 3=============================;
    CNOT(Error_vector, 11, 24);
    TQerror(Error_vector, 11, 24, probability * beta);

//  gz5=[9,10,13,14 ]======number 3=============================;   
    CNOT(Error_vector, 13, 25);
    TQerror(Error_vector, 13, 25, probability * beta);
// gz6=[11,12,15,16 ]======number 3=============================; 
    CNOT(Error_vector, 15, 26);
    TQerror(Error_vector, 15, 26, probability * beta);
// gz7=[8,12,16,17 ]======number 3=============================;   
    CNOT(Error_vector, 16, 27);
    TQerror(Error_vector, 16, 27, probability * beta);

// gz8=[3,4,6,7,10,11,14,15 ]======number 3=============================;  
    CNOT(Error_vector, 6, 28);
    TQerror(Error_vector, 6, 28, probability * beta);
	
	
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    //SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
	
    
//==============================================================================
//==============================================================================	
  
  
  
// gz1=[1,2,3,4 ]======number 4=============================;
    CNOT(Error_vector, 4, 21);
    TQerror(Error_vector, 4, 21, probability * beta);
    
// gz2=[1,3,5,6 ]======number 4=============================;
    CNOT(Error_vector, 6, 22);
    TQerror(Error_vector, 6, 22, probability * beta);
    
  
// gz3=[5,6,9,10 ]======number 4=============================;
    CNOT(Error_vector, 10, 23);
    TQerror(Error_vector, 10, 23, probability * beta);
// gz4=[7,8,11,12 ]======number 4=============================;   
    CNOT(Error_vector, 12, 24);
    TQerror(Error_vector, 12, 24, probability * beta); 
  
  
//  gz5=[9,10,13,14 ]======number 4=============================;  
    CNOT(Error_vector, 14, 25);
    TQerror(Error_vector, 14, 25, probability * beta);
// gz6=[11,12,15,16 ]======number 4=============================;  
    CNOT(Error_vector, 16, 26);
    TQerror(Error_vector, 16, 26, probability * beta);   
// gz7=[8,12,16,17 ]======number 4=============================;  
    CNOT(Error_vector, 17, 27);
    TQerror(Error_vector, 17, 27, probability * beta);
  
// gz8=[3,4,6,7,10,11,14,15 ]======number 4=============================;  
    CNOT(Error_vector, 7, 28);
    TQerror(Error_vector, 7, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    //SQerror(Error_vector, 17, probability*gamma);
    
    
//==============================================================================
//==============================================================================	
  
  
  
  
    
// gz8=[3,4,6,7,10,11,14,15 ]======number 5=============================; 
    CNOT(Error_vector, 10, 28);
    TQerror(Error_vector, 10, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
//==============================================================================
//==============================================================================	
  
  
  
// gz8=[3,4,6,7,10,11,14,15 ]======number 6=============================; 
    CNOT(Error_vector, 11, 28);
    TQerror(Error_vector, 11, 28, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
//==============================================================================
//==============================================================================	
  

  

// gz8=[3,4,6,7,10,11,14,15 ]======number 7=============================; 
    CNOT(Error_vector, 14, 28);
    TQerror(Error_vector, 14, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
//==============================================================================
//==============================================================================	
  
  
  
  
// gz8=[3,4,6,7,10,11,14,15 ]======number 8=============================; 
    CNOT(Error_vector, 15, 28);
    TQerror(Error_vector, 15, 28, probability * beta);
    
   

    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //=========================================================================
    //=========================================================================



    //=========================================================================
    // X-type start
    
    SQerror(Error_vector, 31, probability*alpha);
    SQerror(Error_vector, 32, probability*alpha);
    SQerror(Error_vector, 33, probability*alpha);
    SQerror(Error_vector, 34, probability*alpha);
    SQerror(Error_vector, 35, probability*alpha);
    SQerror(Error_vector, 36, probability*alpha);
    SQerror(Error_vector, 37, probability*alpha);
    SQerror(Error_vector, 38, probability*alpha);
    
// gx1=[1,2,3,4 ]======number 2=============================; 
    CNOT(Error_vector, 31, 2);
    TQerror(Error_vector, 31, 2, probability * beta);

// gx2=[1,3,5,6 ]======number 1=============================; 
    
    CNOT(Error_vector, 32, 1);
    TQerror(Error_vector, 32, 1, probability * beta);
    
// gx3=[5,6,9,10 ]======number 1=============================;
    
    CNOT(Error_vector, 33, 5);
    TQerror(Error_vector, 33, 5, probability * beta);
    
// gx4=[7,8,11,12 ]======number 1=============================;
    
    CNOT(Error_vector, 34, 7);
    TQerror(Error_vector, 34, 7, probability * beta);
    
// gx5=[9,10,13,14 ]======number 1=============================;
    
    CNOT(Error_vector, 35, 9);
    TQerror(Error_vector, 35, 9, probability * beta);
	
// gx6=[11,12,15,16 ]======number 2=============================;
    CNOT(Error_vector, 36, 12);
    TQerror(Error_vector, 36, 12, probability * beta);   

// gx7=[8,12,16,17 ]======number 1=============================;
    
    CNOT(Error_vector, 37, 8);
    TQerror(Error_vector, 37, 8, probability * beta);
 
// gx8=[3,4,6,7,10,11,14,15 ]======number 1=============================;
    
    CNOT(Error_vector, 38, 3);
    TQerror(Error_vector, 38, 3, probability * beta);
    
    //SQerror(Error_vector, 1, probability*gamma);
    //SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);    
    
//==============================================================================
//==============================================================================	
  
// gx1=[1,2,3,4 ]======number 1=============================; 
    
    CNOT(Error_vector, 31, 1);
    TQerror(Error_vector, 31, 1, probability * beta);
    
    
    
// gx2=[1,3,5,6 ]======number 2=============================;
    CNOT(Error_vector, 32, 3);
    TQerror(Error_vector, 32, 3, probability * beta);
    
  
  
// gx3=[5,6,9,10 ]======number 2=============================;
    CNOT(Error_vector, 33, 6);
    TQerror(Error_vector, 33, 6, probability * beta);
    
  
// gx4=[7,8,11,12 ]======number 2=============================; 
    CNOT(Error_vector, 34, 8);
    TQerror(Error_vector, 34, 8, probability * beta);

// gx5=[9,10,13,14 ]======number 2=============================; 
    CNOT(Error_vector, 35, 10);
    TQerror(Error_vector, 35, 10, probability * beta);
 
// gx6=[11,12,15,16 ]======number 1=============================;
    
    CNOT(Error_vector, 36, 11);
    TQerror(Error_vector, 36, 11, probability * beta);

  
  // gx7=[8,12,16,17 ]======number 2=============================;
    CNOT(Error_vector, 37, 12);
    TQerror(Error_vector, 37, 12, probability * beta);
    
    
  
// gx8=[3,4,6,7,10,11,14,15 ]======number 2=============================; 
    CNOT(Error_vector, 38, 4);
    TQerror(Error_vector, 38, 4, probability * beta);
    
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);	
	
//==============================================================================
//==============================================================================	
	
	
  
// gx1=[1,2,3,4 ]======number 3=============================;   
    CNOT(Error_vector, 31, 3);
    TQerror(Error_vector, 31, 3, probability * beta);
    
// gx2=[1,3,5,6 ]======number 3=============================; 
    CNOT(Error_vector, 32, 5);
    TQerror(Error_vector, 32, 5, probability * beta);
    
// gx3=[5,6,9,10 ]======number 3=============================;
    CNOT(Error_vector, 33, 9);
    TQerror(Error_vector, 33, 9, probability * beta);
	
	
  // gx4=[7,8,11,12 ]======number 3=============================; 
    CNOT(Error_vector, 34, 11);
    TQerror(Error_vector, 34, 11, probability * beta); 
 
// gx5=[9,10,13,14 ]======number 3=============================; 
    CNOT(Error_vector, 35, 13);
    TQerror(Error_vector, 35, 13, probability * beta);	

// gx6=[11,12,15,16 ]======number 3=============================; 
    CNOT(Error_vector, 36, 15);
    TQerror(Error_vector, 36, 15, probability * beta);
 	
	
// gx7=[8,12,16,17 ]======number 3=============================;
    CNOT(Error_vector, 37, 16);
    TQerror(Error_vector, 37, 16, probability * beta);
    
   
// gx8=[3,4,6,7,10,11,14,15 ]======number 3=============================; 
    CNOT(Error_vector, 38, 6);
    TQerror(Error_vector, 38, 6, probability * beta);
    
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    //SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
//==============================================================================
//==============================================================================
	
  
// gx1=[1,2,3,4 ]======number 4=============================;   
    CNOT(Error_vector, 31, 4);
    TQerror(Error_vector, 31, 4, probability * beta);
    
// gx2=[1,3,5,6 ]======number 4=============================;  
    CNOT(Error_vector, 32, 6);
    TQerror(Error_vector, 32, 6, probability * beta);
   
// gx3=[5,6,9,10 ]======number 4=============================; 
    CNOT(Error_vector, 33, 10);
    TQerror(Error_vector, 33, 10, probability * beta);
    
// gx4=[7,8,11,12 ]======number 4=============================;  
    CNOT(Error_vector, 34, 12);
    TQerror(Error_vector, 34, 12, probability * beta);
    
    
// gx5=[9,10,13,14 ]======number 4=============================;
    CNOT(Error_vector, 35, 14);
    TQerror(Error_vector, 35, 14, probability * beta);
    	
// gx6=[11,12,15,16 ]======number 4=============================; 
    CNOT(Error_vector, 36, 16);
    TQerror(Error_vector, 36, 16, probability * beta);
    
// gx7=[8,12,16,17 ]======number 4=============================;
    CNOT(Error_vector, 37, 17);
    TQerror(Error_vector, 37, 17, probability * beta);
    
	
// gx8=[3,4,6,7,10,11,14,15 ]======number 4=============================;
    CNOT(Error_vector, 38, 7);
    TQerror(Error_vector, 38, 7, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    //SQerror(Error_vector, 17, probability*gamma);
//==============================================================================
//==============================================================================
	
	
// gx8=[3,4,6,7,10,11,14,15 ]======number 5=============================; 
    CNOT(Error_vector, 38, 10);
    TQerror(Error_vector, 38, 10, probability * beta);
    

    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);

// gx8=[3,4,6,7,10,11,14,15 ]======number 6=============================; 
    CNOT(Error_vector, 38, 11);
    TQerror(Error_vector, 38, 11, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);  
  
  
// gx8=[3,4,6,7,10,11,14,15 ]======number 7=============================;
    CNOT(Error_vector, 38, 14);
    TQerror(Error_vector, 38, 14, probability * beta);
    
	
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
// gx8=[3,4,6,7,10,11,14,15 ]======number 8=============================;
    CNOT(Error_vector, 38, 15);
    TQerror(Error_vector, 38, 15, probability * beta);
    
   
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    SQerror(Error_vector, 31, probability*alpha);
    SQerror(Error_vector, 32, probability*alpha);
    SQerror(Error_vector, 33, probability*alpha);
    SQerror(Error_vector, 34, probability*alpha);
    SQerror(Error_vector, 35, probability*alpha);
    SQerror(Error_vector, 36, probability*alpha);
    SQerror(Error_vector, 37, probability*alpha);
    SQerror(Error_vector, 38, probability*alpha);
    
    
    
    
}





int serial_flag(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta ){
    
    
    
    SQerror(Error_vector, 21, probability*alpha);
    SQerror(Error_vector, 22, probability*alpha);
    SQerror(Error_vector, 23, probability*alpha);
    SQerror(Error_vector, 24, probability*alpha);
    SQerror(Error_vector, 25, probability*alpha);
    SQerror(Error_vector, 26, probability*alpha);
    SQerror(Error_vector, 27, probability*alpha);
    SQerror(Error_vector, 28, probability*alpha);
    
    SQerror(Error_vector, 41, probability*alpha);
    SQerror(Error_vector, 42, probability*alpha);
    SQerror(Error_vector, 43, probability*alpha);
    SQerror(Error_vector, 44, probability*alpha);
    SQerror(Error_vector, 45, probability*alpha);
    SQerror(Error_vector, 46, probability*alpha);
    SQerror(Error_vector, 47, probability*alpha);
    SQerror(Error_vector, 48, probability*alpha);
    SQerror(Error_vector, 49, probability*alpha);
    
    SQerror(Error_vector, 31, probability*alpha);
    SQerror(Error_vector, 32, probability*alpha);
    SQerror(Error_vector, 33, probability*alpha);
    SQerror(Error_vector, 34, probability*alpha);
    SQerror(Error_vector, 35, probability*alpha);
    SQerror(Error_vector, 36, probability*alpha);
    SQerror(Error_vector, 37, probability*alpha);
    SQerror(Error_vector, 38, probability*alpha);
    
    SQerror(Error_vector, 51, probability*alpha);
    SQerror(Error_vector, 52, probability*alpha);
    SQerror(Error_vector, 53, probability*alpha);
    SQerror(Error_vector, 54, probability*alpha);
    SQerror(Error_vector, 55, probability*alpha);
    SQerror(Error_vector, 56, probability*alpha);
    SQerror(Error_vector, 57, probability*alpha);
    SQerror(Error_vector, 58, probability*alpha);
    SQerror(Error_vector, 59, probability*alpha);
    
    //g1:Number C->D->A--------------------------
    
    CNOT(Error_vector, 3, 21);
    TQerror(Error_vector, 3, 21, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g1:Flag 1--------------------------
    
    CNOT(Error_vector, 41, 21);
    TQerror(Error_vector, 41, 21, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g1:Number A->B--------------------------
    CNOT(Error_vector, 1, 21);
    TQerror(Error_vector, 1, 21, probability * beta);
    
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g1:Number D->C--------------------------
    
    CNOT(Error_vector, 4, 21);
    TQerror(Error_vector, 4, 21, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g1:Flag 1--------------------------
    
    CNOT(Error_vector, 41, 21);
    TQerror(Error_vector, 41, 21, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g1:Number B->A->D--------------------------
    
    CNOT(Error_vector, 2, 21);
    TQerror(Error_vector, 2, 21, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    //SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g2:Number A--------------------------
    CNOT(Error_vector, 1, 22);
    TQerror(Error_vector, 1, 22, probability * beta);
    
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g2:Flag 1--------------------------
    
    CNOT(Error_vector, 42, 22);
    TQerror(Error_vector, 42, 22, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g2:Number B--------------------------
    
    CNOT(Error_vector, 3, 22);
    TQerror(Error_vector, 3, 22, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    //g2:Number C--------------------------
    
    CNOT(Error_vector, 5, 22);
    TQerror(Error_vector, 5, 22, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g2:Flag 1--------------------------
    
    CNOT(Error_vector, 42, 22);
    TQerror(Error_vector, 42, 22, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g2:Number D--------------------------
    
    CNOT(Error_vector, 6, 22);
    TQerror(Error_vector, 6, 22, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g3:Number A--------------------------
    
    CNOT(Error_vector, 5, 23);
    TQerror(Error_vector, 5, 23, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g3:Flag 1--------------------------
    
    CNOT(Error_vector, 43, 23);
    TQerror(Error_vector, 43, 23, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g3:Number B--------------------------
    CNOT(Error_vector, 6, 23);
    TQerror(Error_vector, 6, 23, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g3:Number C--------------------------
    
    CNOT(Error_vector, 9, 23);
    TQerror(Error_vector, 9, 23, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g3:Flag 1--------------------------
    
    CNOT(Error_vector, 43, 23);
    TQerror(Error_vector, 43, 23, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g3:Number D--------------------------
    
    CNOT(Error_vector, 10, 23);
    TQerror(Error_vector, 10, 23, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g4:Number A--------------------------
    CNOT(Error_vector, 7, 24);
    TQerror(Error_vector, 7, 24, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g4:Flag 1--------------------------
    
    CNOT(Error_vector, 44, 24);
    TQerror(Error_vector, 44, 24, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g4:Number B--------------------------
    
    CNOT(Error_vector, 8, 24);
    TQerror(Error_vector, 8, 24, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g4:Number C--------------------------
    
    CNOT(Error_vector, 11, 24);
    TQerror(Error_vector, 11, 24, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g4:Flag 1--------------------------
    
    CNOT(Error_vector, 44, 24);
    TQerror(Error_vector, 44, 24, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g4:Number D--------------------------
    
    CNOT(Error_vector, 12, 24);
    TQerror(Error_vector, 12, 24, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g5:Number A--------------------------
    CNOT(Error_vector, 9, 25);
    TQerror(Error_vector, 9, 25, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g5:Flag 1--------------------------
    
    CNOT(Error_vector, 45, 25);
    TQerror(Error_vector, 45, 25, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g5:Number B--------------------------
    
    CNOT(Error_vector, 10, 25);
    TQerror(Error_vector, 10, 25, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g5:Number C--------------------------
    
    CNOT(Error_vector, 13, 25);
    TQerror(Error_vector, 13, 25, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    //SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g5:Flag 1--------------------------
    
    CNOT(Error_vector, 45, 25);
    TQerror(Error_vector, 45, 25, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g5:Number D--------------------------
    
    CNOT(Error_vector, 14, 25);
    TQerror(Error_vector, 14, 25, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g6:Number A--------------------------
    
    CNOT(Error_vector, 11, 26);
    TQerror(Error_vector, 11, 26, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g6:Flag 1--------------------------
    
    CNOT(Error_vector, 46, 26);
    TQerror(Error_vector, 46, 26, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g6:Number B--------------------------
    CNOT(Error_vector, 12, 26);
    TQerror(Error_vector, 12, 26, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    //g6:Number C--------------------------
    
    CNOT(Error_vector, 15, 26);
    TQerror(Error_vector, 15, 26, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g6:Flag 1--------------------------
    
    CNOT(Error_vector, 46, 26);
    TQerror(Error_vector, 46, 26, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g6:Number D--------------------------
    
    CNOT(Error_vector, 16, 26);
    TQerror(Error_vector, 16, 26, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g7:Number B->C->A--------------------------
    
    CNOT(Error_vector, 12, 27);
    TQerror(Error_vector, 12, 27, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g7:Flag 1--------------------------
    
    CNOT(Error_vector, 47, 27);
    TQerror(Error_vector, 47, 27, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g7:Number A->D->B--------------------------
    CNOT(Error_vector, 8, 27);
    TQerror(Error_vector, 8, 27, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g7:Number D->A->C--------------------------
    
    CNOT(Error_vector, 17, 27);
    TQerror(Error_vector, 17, 27, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    //SQerror(Error_vector, 17, probability*gamma);
    
    //g7:Flag 1--------------------------
    
    CNOT(Error_vector, 47, 27);
    TQerror(Error_vector, 47, 27, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g7:Number C->B->D--------------------------
    
    CNOT(Error_vector, 16, 27);
    TQerror(Error_vector, 16, 27, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g8:Number G->A--------------------------
    
    CNOT(Error_vector, 14, 28);
    TQerror(Error_vector, 14, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g8:Flag 1--------------------------
    
    CNOT(Error_vector, 48, 28);
    TQerror(Error_vector, 48, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g8:Number E->B--------------------------
    
    CNOT(Error_vector, 10, 28);
    TQerror(Error_vector, 10, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g8:Flag 2--------------------------
    
    CNOT(Error_vector, 49, 28);
    TQerror(Error_vector, 49, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //================================================================
    
    //g8:Number I->D->C--------------------------
    
    CNOT(Error_vector, 15, 28);
    TQerror(Error_vector, 15, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g8:Number C->D--------------------------
    
    CNOT(Error_vector, 6, 28);
    TQerror(Error_vector, 6, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g8:Flag 3--------------------------
    
    CNOT(Error_vector, 50, 28);
    TQerror(Error_vector, 50, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g8:Number A->G->E--------------------------
    CNOT(Error_vector, 3, 28);
    TQerror(Error_vector, 3, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    //g8:Number D->I->F--------------------------
    
    CNOT(Error_vector, 7, 28);
    TQerror(Error_vector, 7, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g8:Flag 1--------------------------
    
    CNOT(Error_vector, 48, 28);
    TQerror(Error_vector, 48, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g8:Number B->E->G--------------------------
    
    CNOT(Error_vector, 4, 28);
    TQerror(Error_vector, 4, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g8:Flag 3--------------------------
    
    CNOT(Error_vector, 50, 28);
    TQerror(Error_vector, 50, 28, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    //g8:Flag 2--------------------------
    
    CNOT(Error_vector, 49, 28);
    TQerror(Error_vector, 49, 28, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    //g8:Number F->I--------------------------
    
    CNOT(Error_vector, 11, 28);
    TQerror(Error_vector, 11, 28, probability * beta);
    
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
// X-type stabilizer
    
    
    
// gx1=[1,2,3,4 ] -> 3142;
    
    CNOT(Error_vector, 31, 3);
    TQerror(Error_vector, 31, 3, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 31, 51);
    TQerror(Error_vector, 31, 51, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 31, 1);
    TQerror(Error_vector, 31, 1, probability * beta);
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 31, 4);
    TQerror(Error_vector, 31, 4, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 31, 51);
    TQerror(Error_vector, 31, 51, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 31, 2);
    TQerror(Error_vector, 31, 2, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    //SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
// gx2=[1,3,5,6 ] ->1356;
    
    CNOT(Error_vector, 32, 1);
    TQerror(Error_vector, 32, 1, probability * beta);
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 32, 52);
    TQerror(Error_vector, 32, 52, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 32, 3);
    TQerror(Error_vector, 32, 3, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 32, 5);
    TQerror(Error_vector, 32, 5, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 32, 52);
    TQerror(Error_vector, 32, 52, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 32, 6);
    TQerror(Error_vector, 32, 6, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
// gx3=[5,6,9,10 ]- >56910;
    
    CNOT(Error_vector, 33, 5);
    TQerror(Error_vector, 33, 5, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 33, 53);
    TQerror(Error_vector, 33, 53, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 33, 6);
    TQerror(Error_vector, 33, 6, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 33, 9);
    TQerror(Error_vector, 33, 9, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 33, 53);
    TQerror(Error_vector, 33, 53, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 33, 10);
    TQerror(Error_vector, 33, 10, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
// gx4=[7,8,11,12 ] -> 781112;
    
    CNOT(Error_vector, 34, 7);
    TQerror(Error_vector, 34, 7, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 34, 54);
    TQerror(Error_vector, 34, 54, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 34, 8);
    TQerror(Error_vector, 34, 8, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 34, 11);
    TQerror(Error_vector, 34, 11, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 34, 54);
    TQerror(Error_vector, 34, 54, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 34, 12);
    TQerror(Error_vector, 34, 12, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
// gx5=[9,10,13,14 ] ->9101314;
    
    CNOT(Error_vector, 35, 9);
    TQerror(Error_vector, 35, 9, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 35, 55);
    TQerror(Error_vector, 35, 55, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 35, 10);
    TQerror(Error_vector, 35, 10, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 35, 13);
    TQerror(Error_vector, 35, 13, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    //SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 35, 55);
    TQerror(Error_vector, 35, 55, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 35, 14);
    TQerror(Error_vector, 35, 14, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
// gx6=[11,12,15,16 ] ->11121516;
    
    CNOT(Error_vector, 36, 11);
    TQerror(Error_vector, 36, 11, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 36, 56);
    TQerror(Error_vector, 36, 56, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 36, 12);
    TQerror(Error_vector, 36, 12, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 36, 15);
    TQerror(Error_vector, 36, 15, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 36, 56);
    TQerror(Error_vector, 36, 56, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 36, 16);
    TQerror(Error_vector, 36, 16, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
// gx7=[8,12,16,17 ] ->12 8 17 16;
    
    CNOT(Error_vector, 37, 12);
    TQerror(Error_vector, 37, 12, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 37, 57);
    TQerror(Error_vector, 37, 57, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 37, 8);
    TQerror(Error_vector, 37, 8, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 37, 17);
    TQerror(Error_vector, 37, 17, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    //SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 37, 57);
    TQerror(Error_vector, 37, 57, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 37, 16);
    TQerror(Error_vector, 37, 16, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
// gx8=[3,4,6,7,10,11,14,15 ] -> 14,10,15,6,3,7,4,11 ;
    
    CNOT(Error_vector, 38, 14);
    TQerror(Error_vector, 38, 14, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 38, 58);
    TQerror(Error_vector, 38, 58, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 38, 10);
    TQerror(Error_vector, 38, 10, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 38, 59);
    TQerror(Error_vector, 38, 59, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 38, 15);
    TQerror(Error_vector, 38, 15, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 38, 6);
    TQerror(Error_vector, 38, 6, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 38, 60);
    TQerror(Error_vector, 38, 60, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 38, 3);
    TQerror(Error_vector, 38, 3, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 38, 7);
    TQerror(Error_vector, 38, 7, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    CNOT(Error_vector, 38, 58);
    TQerror(Error_vector, 38, 58, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 38, 4);
    TQerror(Error_vector, 38, 4, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 38, 59);
    TQerror(Error_vector, 38, 59, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    CNOT(Error_vector, 38, 11);
    TQerror(Error_vector, 38, 11, probability * beta);
    SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    
    
    SQerror(Error_vector, 21, probability*alpha);
    SQerror(Error_vector, 22, probability*alpha);
    SQerror(Error_vector, 23, probability*alpha);
    SQerror(Error_vector, 24, probability*alpha);
    SQerror(Error_vector, 25, probability*alpha);
    SQerror(Error_vector, 26, probability*alpha);
    SQerror(Error_vector, 27, probability*alpha);
    SQerror(Error_vector, 28, probability*alpha);
    
    SQerror(Error_vector, 41, probability*alpha);
    SQerror(Error_vector, 42, probability*alpha);
    SQerror(Error_vector, 43, probability*alpha);
    SQerror(Error_vector, 44, probability*alpha);
    SQerror(Error_vector, 45, probability*alpha);
    SQerror(Error_vector, 46, probability*alpha);
    SQerror(Error_vector, 47, probability*alpha);
    SQerror(Error_vector, 48, probability*alpha);
    SQerror(Error_vector, 49, probability*alpha);
    
    SQerror(Error_vector, 31, probability*alpha);
    SQerror(Error_vector, 32, probability*alpha);
    SQerror(Error_vector, 33, probability*alpha);
    SQerror(Error_vector, 34, probability*alpha);
    SQerror(Error_vector, 35, probability*alpha);
    SQerror(Error_vector, 36, probability*alpha);
    SQerror(Error_vector, 37, probability*alpha);
    SQerror(Error_vector, 38, probability*alpha);
    
    SQerror(Error_vector, 51, probability*alpha);
    SQerror(Error_vector, 52, probability*alpha);
    SQerror(Error_vector, 53, probability*alpha);
    SQerror(Error_vector, 54, probability*alpha);
    SQerror(Error_vector, 55, probability*alpha);
    SQerror(Error_vector, 56, probability*alpha);
    SQerror(Error_vector, 57, probability*alpha);
    SQerror(Error_vector, 58, probability*alpha);
    SQerror(Error_vector, 59, probability*alpha);
    
    
    
}
