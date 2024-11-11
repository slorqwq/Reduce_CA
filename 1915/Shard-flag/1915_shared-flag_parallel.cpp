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

int SQerror2(int (*Record_error2)[n], int a, double probability); // Single qubit error
int TQerror2(int (*Record_error2)[n], int a, int b, double probability); // Two qubit error
int CNOT2(int (*Error_vector2)[n], int a, int b);

int TQerror3(int (*Record_error)[n], int (*Record_error2)[n], int a, int b, double probability); // Two qubit error
int CNOT3(int (*Error_vector)[n], int (*Error_vector2)[n], int a, int b);

int x_circuit(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta);
int z_circuit(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta);



int main_circuit_1(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta);
int main_circuit_2(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta);

int parallel_flag(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta);
int unflagged(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta);



uint64_t next64() {  // random number
    uint64_t z = (x += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}

void rnd256_init() { // random number
    s[0] = next64();  s[1] = next64();  s[2] = next64();  s[3] = next64();
}



int const table_length_ptz_f1 = 70456; 
int const table_width_ptz_f1 = 72;

int syndrome_ptz_f1[table_length_ptz_f1][table_width_ptz_f1]= { 0 };
int syndrome_result_ptz_f1[table_width_ptz_f1] = { 0 };
int test1_ptz_f1[table_width_ptz_f1] = { 0 };  //
int recovery_ptz_f1[table_length_ptz_f1][38]= { 0 };

int const table_length_ptz_f2 = 70456; 
int const table_width_ptz_f2 = 72;

int syndrome_ptz_f2[table_length_ptz_f2][table_width_ptz_f2]= { 0 };
int syndrome_result_ptz_f2[table_width_ptz_f2] = { 0 };
int test1_ptz_f2[table_width_ptz_f2] = { 0 };  //
int recovery_ptz_f2[table_length_ptz_f2][38]= { 0 };

int const table_length_ptz_f3 = 51132; 
int const table_width_ptz_f3 = 54;

int syndrome_ptz_f3[table_length_ptz_f3][table_width_ptz_f3]= { 0 };
int syndrome_result_ptz_f3[table_width_ptz_f3] = { 0 };
int test1_ptz_f3[table_width_ptz_f3] = { 0 };  //
int recovery_ptz_f3[table_length_ptz_f3][38]= { 0 };

int const table_length_ptz_f4 = 122322; 
int const table_width_ptz_f4 = 72;

int syndrome_ptz_f4[table_length_ptz_f4][table_width_ptz_f4]= { 0 };
int syndrome_result_ptz_f4[table_width_ptz_f4] = { 0 };
int test1_ptz_f4[table_width_ptz_f4] = { 0 };  //
int recovery_ptz_f4[table_length_ptz_f4][38]= { 0 };


int const table_length_ptz_m1 = 78490; 
int const table_width_ptz_m1 = 72;

int syndrome_ptz_m1[table_length_ptz_m1][table_width_ptz_m1]= { 0 };
int syndrome_result_ptz_m1[table_width_ptz_m1] = { 0 };
int test1_ptz_m1[table_width_ptz_m1] = { 0 };  //
int recovery_ptz_m1[table_length_ptz_m1][38]= { 0 };

int const table_length_ptz_m2 = 78490; 
int const table_width_ptz_m2 = 72;

int syndrome_ptz_m2[table_length_ptz_m2][table_width_ptz_m2]= { 0 };
int syndrome_result_ptz_m2[table_width_ptz_m2] = { 0 };
int test1_ptz_m2[table_width_ptz_m2] = { 0 };  //
int recovery_ptz_m2[table_length_ptz_m2][38]= { 0 };


int const table_length_ptz_m3 = 15566; 
int const table_width_ptz_m3 = 54;

int syndrome_ptz_m3[table_length_ptz_m3][table_width_ptz_m3]= { 0 };
int syndrome_result_ptz_m3[table_width_ptz_m3] = { 0 };
int test1_ptz_m3[table_width_ptz_m3] = { 0 };  //
int recovery_ptz_m3[table_length_ptz_m3][38]= { 0 };


int const table_length_ptz_m4 = 129010; 
int const table_width_ptz_m4 = 72;

int syndrome_ptz_m4[table_length_ptz_m4][table_width_ptz_m4]= { 0 };
int syndrome_result_ptz_m4[table_width_ptz_m4] = { 0 };
int test1_ptz_m4[table_width_ptz_m4] = { 0 };  //
int recovery_ptz_m4[table_length_ptz_m4][38]= { 0 };

int const table_length_ptx_f1 = 71264; 
int const table_width_ptx_f1 = 72;

int syndrome_ptx_f1[table_length_ptx_f1][table_width_ptx_f1]= { 0 };
int syndrome_result_ptx_f1[table_width_ptx_f1] = { 0 };
int test1_ptx_f1[table_width_ptx_f1] = { 0 };  //
int recovery_ptx_f1[table_length_ptx_f1][38]= { 0 };

int const table_length_ptx_f2 = 71264; 
int const table_width_ptx_f2 = 72;

int syndrome_ptx_f2[table_length_ptx_f2][table_width_ptx_f2]= { 0 };
int syndrome_result_ptx_f2[table_width_ptx_f2] = { 0 };
int test1_ptx_f2[table_width_ptx_f2] = { 0 };  //
int recovery_ptx_f2[table_length_ptx_f2][38]= { 0 };

int const table_length_ptx_f3 = 51132; 
int const table_width_ptx_f3 = 54;

int syndrome_ptx_f3[table_length_ptx_f3][table_width_ptx_f3]= { 0 };
int syndrome_result_ptx_f3[table_width_ptx_f3] = { 0 };
int test1_ptx_f3[table_width_ptx_f3] = { 0 };  //
int recovery_ptx_f3[table_length_ptx_f3][38]= { 0 };

int const table_length_ptx_f4 = 123490; 
int const table_width_ptx_f4 = 72;

int syndrome_ptx_f4[table_length_ptx_f4][table_width_ptx_f4]= { 0 };
int syndrome_result_ptx_f4[table_width_ptx_f4] = { 0 };
int test1_ptx_f4[table_width_ptx_f4] = { 0 };  //
int recovery_ptx_f4[table_length_ptx_f4][38]= { 0 };


int const table_length_ptx_m1 = 79370; 
int const table_width_ptx_m1 = 72;

int syndrome_ptx_m1[table_length_ptx_m1][table_width_ptx_m1]= { 0 };
int syndrome_result_ptx_m1[table_width_ptx_m1] = { 0 };
int test1_ptx_m1[table_width_ptx_m1] = { 0 };  //
int recovery_ptx_m1[table_length_ptx_m1][38]= { 0 };

int const table_length_ptx_m2 = 79370; 
int const table_width_ptx_m2 = 72;

int syndrome_ptx_m2[table_length_ptx_m2][table_width_ptx_m2]= { 0 };
int syndrome_result_ptx_m2[table_width_ptx_m2] = { 0 };
int test1_ptx_m2[table_width_ptx_m2] = { 0 };  //
int recovery_ptx_m2[table_length_ptx_m2][38]= { 0 };


int const table_length_ptx_m3 = 15566; 
int const table_width_ptx_m3 = 54;

int syndrome_ptx_m3[table_length_ptx_m3][table_width_ptx_m3]= { 0 };
int syndrome_result_ptx_m3[table_width_ptx_m3] = { 0 };
int test1_ptx_m3[table_width_ptx_m3] = { 0 };  //
int recovery_ptx_m3[table_length_ptx_m3][38]= { 0 };


int const table_length_ptx_m4 = 129641; 
int const table_width_ptx_m4 = 72;

int syndrome_ptx_m4[table_length_ptx_m4][table_width_ptx_m4]= { 0 };
int syndrome_result_ptx_m4[table_width_ptx_m4] = { 0 };
int test1_ptx_m4[table_width_ptx_m4] = { 0 };  //
int recovery_ptx_m4[table_length_ptx_m4][38]= { 0 };




int syndrome[190][9]= { 0 };
int recovery[190][19]= { 0 };
int symdorme_result_x[9];
int symdorme_result_z[9];
int test1[9]; // syndrome talbe for function used



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
    
    
    
    ifstream fin_z_1a("table\\syndore_ptz_f1.txt");
    if(!fin_z_1a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_f1;i++)
        for(int k=0;k<table_width_ptz_f1;k++)
            fin_z_1a >> syndrome_ptz_f1[i][k];
    fin_z_1a.close();
    
    
    
    ifstream fin_z_1b("table\\recovery_ptz_f1.txt");
    if(!fin_z_1b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_f1;i++)
        for(int k=0;k<38;k++)
            fin_z_1b >> recovery_ptz_f1[i][k];
    fin_z_1b.close();
    
    
    ifstream fin_z_2a("table\\syndore_ptz_f1.txt");
    if(!fin_z_2a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_f2;i++)
        for(int k=0;k<table_width_ptz_f2;k++)
            fin_z_2a >> syndrome_ptz_f2[i][k];
    fin_z_2a.close();
    
    
    
    ifstream fin_z_2b("table\\recovery_ptz_f1.txt");
    if(!fin_z_2b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_f2;i++)
        for(int k=0;k<38;k++)
            fin_z_2b >> recovery_ptz_f2[i][k];
    fin_z_2b.close();
    
    
    ifstream fin_z_3a("table\\syndore_ptz_f3.txt");
    if(!fin_z_3a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_f3;i++)
        for(int k=0;k<table_width_ptz_f3;k++)
            fin_z_3a >> syndrome_ptz_f3[i][k];
    fin_z_3a.close();
    
    
    
    ifstream fin_z_3b("table\\recovery_ptz_f3.txt");
    if(!fin_z_3b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_f3;i++)
        for(int k=0;k<38;k++)
            fin_z_3b >> recovery_ptz_f3[i][k];
    fin_z_3b.close();
    
    
    
    
    ifstream fin_z_4a("table\\syndore_ptz_f4.txt");
    if(!fin_z_4a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_f4;i++)
        for(int k=0;k<table_width_ptz_f4;k++)
            fin_z_4a >> syndrome_ptz_f4[i][k];
    fin_z_4a.close();
    
    
    
    ifstream fin_z_4b("table\\recovery_ptz_f4.txt");
    if(!fin_z_4b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_f4;i++)
        for(int k=0;k<38;k++)
            fin_z_4b >> recovery_ptz_f4[i][k];
    fin_z_4b.close();
    
    
    ifstream fin_z_5a("table\\syndore_ptz_m1.txt");
    if(!fin_z_5a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_m1;i++)
        for(int k=0;k<table_width_ptz_m1;k++)
            fin_z_5a >> syndrome_ptz_m1[i][k];
    fin_z_5a.close();
    
    
    
    ifstream fin_z_5b("table\\recovery_ptz_m1.txt");
    if(!fin_z_5b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_m1;i++)
        for(int k=0;k<38;k++)
            fin_z_5b >> recovery_ptz_m1[i][k];
    fin_z_5b.close();
    
    
    
    ifstream fin_z_6a("table\\syndore_ptz_m1.txt");
    if(!fin_z_6a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_m2;i++)
        for(int k=0;k<table_width_ptz_m2;k++)
            fin_z_6a >> syndrome_ptz_m2[i][k];
    fin_z_6a.close();
    
    
    
    ifstream fin_z_6b("table\\recovery_ptz_m1.txt");
    if(!fin_z_6b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_m2;i++)
        for(int k=0;k<38;k++)
            fin_z_6b >> recovery_ptz_m2[i][k];
    fin_z_6b.close();
    
    
    ifstream fin_z_7a("table\\syndore_ptz_m3.txt");
    if(!fin_z_7a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_m3;i++)
        for(int k=0;k<table_width_ptz_m3;k++)
            fin_z_7a >> syndrome_ptz_m3[i][k];
    fin_z_7a.close();
    
    
    
    ifstream fin_z_7b("table\\recovery_ptz_m3.txt");
    if(!fin_z_7b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_m3;i++)
        for(int k=0;k<38;k++)
            fin_z_7b >> recovery_ptz_m3[i][k];
    fin_z_7b.close();
    
    
    ifstream fin_z_8a("table\\syndore_ptz_m4.txt");
    if(!fin_z_8a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_m4;i++)
        for(int k=0;k<table_width_ptz_m4;k++)
            fin_z_8a >> syndrome_ptz_m4[i][k];
    fin_z_8a.close();
    
    
    
    ifstream fin_z_8b("table\\recovery_ptz_m4.txt");
    if(!fin_z_8b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptz_m4;i++)
        for(int k=0;k<38;k++)
            fin_z_8b >> recovery_ptz_m4[i][k];
    fin_z_8b.close();
    
    
    
    
    ifstream fin_x_1a("table\\syndore_ptx_f1.txt");
    if(!fin_x_1a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_f1;i++)
        for(int k=0;k<table_width_ptx_f1;k++)
            fin_x_1a >> syndrome_ptx_f1[i][k];
    fin_x_1a.close();
    
    
    
    ifstream fin_x_1b("table\\recovery_ptx_f1.txt");
    if(!fin_x_1b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_f1;i++)
        for(int k=0;k<38;k++)
            fin_x_1b >> recovery_ptx_f1[i][k];
    fin_x_1b.close();
    
    
    ifstream fin_x_2a("table\\syndore_ptx_f1.txt");
    if(!fin_x_2a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_f2;i++)
        for(int k=0;k<table_width_ptx_f2;k++)
            fin_x_2a >> syndrome_ptx_f2[i][k];
    fin_x_2a.close();
    
    
    
    ifstream fin_x_2b("table\\recovery_ptx_f1.txt");
    if(!fin_x_2b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_f2;i++)
        for(int k=0;k<38;k++)
            fin_x_2b >> recovery_ptx_f2[i][k];
    fin_x_2b.close();
    
    
    ifstream fin_x_3a("table\\syndore_ptx_f3.txt");
    if(!fin_x_3a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_f3;i++)
        for(int k=0;k<table_width_ptx_f3;k++)
            fin_x_3a >> syndrome_ptx_f3[i][k];
    fin_x_3a.close();
    
    
    
    ifstream fin_x_3b("table\\recovery_ptx_f3.txt");
    if(!fin_x_3b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_f3;i++)
        for(int k=0;k<38;k++)
            fin_x_3b >> recovery_ptx_f3[i][k];
    fin_x_3b.close();
    
    
    
    
    ifstream fin_x_4a("table\\syndore_ptx_f4.txt");
    if(!fin_x_4a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_f4;i++)
        for(int k=0;k<table_width_ptx_f4;k++)
            fin_x_4a >> syndrome_ptx_f4[i][k];
    fin_x_4a.close();
    
    
    
    ifstream fin_x_4b("table\\recovery_ptx_f4.txt");
    if(!fin_x_4b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_f4;i++)
        for(int k=0;k<38;k++)
            fin_x_4b >> recovery_ptx_f4[i][k];
    fin_x_4b.close();
    
    
    ifstream fin_x_5a("table\\syndore_ptx_m1.txt");
    if(!fin_x_5a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_m1;i++)
        for(int k=0;k<table_width_ptx_m1;k++)
            fin_x_5a >> syndrome_ptx_m1[i][k];
    fin_x_5a.close();
    
    
    
    ifstream fin_x_5b("table\\recovery_ptx_m1.txt");
    if(!fin_x_5b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_m1;i++)
        for(int k=0;k<38;k++)
            fin_x_5b >> recovery_ptx_m1[i][k];
    fin_x_5b.close();
    
    
    
    ifstream fin_x_6a("table\\syndore_ptx_m1.txt");
    if(!fin_x_6a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_m2;i++)
        for(int k=0;k<table_width_ptx_m2;k++)
            fin_x_6a >> syndrome_ptx_m2[i][k];
    fin_x_6a.close();
    
    
    
    ifstream fin_x_6b("table\\recovery_ptx_m1.txt");
    if(!fin_x_6b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_m2;i++)
        for(int k=0;k<38;k++)
            fin_x_6b >> recovery_ptx_m2[i][k];
    fin_x_6b.close();
    
    
    ifstream fin_x_7a("table\\syndore_ptx_m3.txt");
    if(!fin_x_7a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_m3;i++)
        for(int k=0;k<table_width_ptx_m3;k++)
            fin_x_7a >> syndrome_ptx_m3[i][k];
    fin_x_7a.close();
    
    
    
    ifstream fin_x_7b("table\\recovery_ptx_m3.txt");
    if(!fin_x_7b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_m3;i++)
        for(int k=0;k<38;k++)
            fin_x_7b >> recovery_ptx_m3[i][k];
    fin_x_7b.close();
    
    
    ifstream fin_x_8a("table\\syndore_ptx_m4.txt");
    if(!fin_x_8a) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_m4;i++)
        for(int k=0;k<table_width_ptx_m4;k++)
            fin_x_8a >> syndrome_ptx_m4[i][k];
    fin_x_8a.close();
    
    
    
    ifstream fin_x_8b("table\\recovery_ptx_m4.txt");
    if(!fin_x_8b) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<table_length_ptx_m4;i++)
        for(int k=0;k<38;k++)
            fin_x_8b >> recovery_ptx_m4[i][k];
    fin_x_8b.close();
    
    
    
    
    ifstream fin_1("table\\syndrome.txt");
    if(!fin_1) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<190;i++)
        for(int k=0;k<9;k++)
            fin_1 >> syndrome[i][k];
    fin_1.close();
    
    ifstream fin_2("table\\recovery.txt");
    if(!fin_2) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<190;i++)
        for(int k=0;k<19;k++)
            fin_2 >> recovery[i][k];
    fin_2.close();
    
    
    
    
    
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
    double gamma = 0.01; // memory error
    double alpha = 10; // measurement error
    double beta = 1;  // CNOT error
    
    

    cout << "[[19,1,5]] shared-flag the last round is parallel" << " ,loop=" << N-1 << " ,gamma = " << gamma <<  ", alpha = " << alpha << ", beta = "  << beta << endl << endl << endl;
    
    for(int i=1; i<N; i++){
        
       
        probability = 0.0001+0.0001*(i-1)*(i*i/2); // gamma=1 ; N=4
        Total_number = 0; 
        Error_number = 0; 
        while(Total_number<1000000||Error_number<800){ 
        //  while(  Total_number<100000){ 
            
            
            
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
            
            /*
              SQerror(Error_vector, 1, probability);
              SQerror(Error_vector, 2, probability);
              SQerror(Error_vector, 3, probability);
              SQerror(Error_vector, 4, probability);
              SQerror(Error_vector, 5, probability);
              SQerror(Error_vector, 6, probability);
              SQerror(Error_vector, 7, probability);
              SQerror(Error_vector, 8, probability);
              SQerror(Error_vector, 9, probability);
              SQerror(Error_vector, 10, probability);
              SQerror(Error_vector, 11, probability);
              SQerror(Error_vector, 12, probability);
              SQerror(Error_vector, 13, probability);
              SQerror(Error_vector, 14, probability);
              SQerror(Error_vector, 15, probability);
              SQerror(Error_vector, 16, probability);
              SQerror(Error_vector, 17, probability);
              SQerror(Error_vector, 18, probability);
              SQerror(Error_vector, 19, probability);
             */
//------------------------------------------------------------------------------------------------------------------------------
            
            
            main_circuit_1(Error_vector, probability, gamma, alpha, beta );
            
            
            //協助判斷==========================================================================================
            // 判斷Z-type flag and X-type flag
            
            int measure_result = 0;
            int flag_result = 0;
            
            for (int i=0; i<9; i++){
                flag_result = flag_result + Error_vector[1][40+i]  ;
            }
            
            
            for (int i=0; i<9; i++){
                measure_result = measure_result + Error_vector[0][20+i] ;
            }
            //==========================================================================================
            
            if ( measure_result ==0 && flag_result==0 ){
                
                goto ckp1;
                
            }
            
            
            
            
            
            for (int i=18; i<27; i++){
                syndrome_result_ptz_f1[i] = Error_vector[0][i+2];
            }
            for (int i=27; i<36; i++){
                syndrome_result_ptz_f1[i] = Error_vector[1][i+13];
            }
            
            for (int i=18; i<27; i++){
                syndrome_result_ptz_f2[i] = Error_vector[0][i+2];
            }
            for (int i=27; i<36; i++){
                syndrome_result_ptz_f2[i] = Error_vector[1][i+13];
            }
            
            
            syndrome_result_ptz_f3[0] = Error_vector[0][20];  //m1
            syndrome_result_ptz_f3[1] = Error_vector[0][21];  //m2
            syndrome_result_ptz_f3[2] = Error_vector[0][22];  //m3
            syndrome_result_ptz_f3[3] = Error_vector[0][23];  //m4
            syndrome_result_ptz_f3[4] = Error_vector[0][24];  //m5
            syndrome_result_ptz_f3[5] = Error_vector[0][25];  //m6
            syndrome_result_ptz_f3[6] = Error_vector[0][26];  //m7
            syndrome_result_ptz_f3[7] = Error_vector[0][27];  //m8
            syndrome_result_ptz_f3[8] = Error_vector[0][28];  //m9
            syndrome_result_ptz_f3[9] = Error_vector[1][40];  //f1
            syndrome_result_ptz_f3[10] = Error_vector[1][41];  //f2
            syndrome_result_ptz_f3[11] = Error_vector[1][42];  //f3
            syndrome_result_ptz_f3[12] = Error_vector[1][43];  //f4
            syndrome_result_ptz_f3[13] = Error_vector[1][44];  //f5
            syndrome_result_ptz_f3[14] = Error_vector[1][45];  //f6
            syndrome_result_ptz_f3[15] = Error_vector[1][46];  //f7
            syndrome_result_ptz_f3[16] = Error_vector[1][47];  //f8
            syndrome_result_ptz_f3[17] = Error_vector[1][48];  //f9
            
            syndrome_result_ptz_f4[18] = Error_vector[0][20];  //m1
            syndrome_result_ptz_f4[19] = Error_vector[0][21];  //m2
            syndrome_result_ptz_f4[20] = Error_vector[0][22];  //m3
            syndrome_result_ptz_f4[21] = Error_vector[0][23];  //m4
            syndrome_result_ptz_f4[22] = Error_vector[0][24];  //m5
            syndrome_result_ptz_f4[23] = Error_vector[0][25];  //m6
            syndrome_result_ptz_f4[24] = Error_vector[0][26];  //m7
            syndrome_result_ptz_f4[25] = Error_vector[0][27];  //m8
            syndrome_result_ptz_f4[26] = Error_vector[0][28];  //m9
            syndrome_result_ptz_f4[27] = Error_vector[1][40];  //f1
            syndrome_result_ptz_f4[28] = Error_vector[1][41];  //f2
            syndrome_result_ptz_f4[29] = Error_vector[1][42];  //f3
            syndrome_result_ptz_f4[30] = Error_vector[1][43];  //f4
            syndrome_result_ptz_f4[31] = Error_vector[1][44];  //f5
            syndrome_result_ptz_f4[32] = Error_vector[1][45];  //f6
            syndrome_result_ptz_f4[33] = Error_vector[1][46];  //f7
            syndrome_result_ptz_f4[34] = Error_vector[1][47];  //f8
            syndrome_result_ptz_f4[35] = Error_vector[1][48];  //f9
            
            
            
            for (int i=18; i<27; i++){
                syndrome_result_ptz_m1[i] = Error_vector[0][i+2];
            }
            for (int i=27; i<36; i++){
                syndrome_result_ptz_m1[i] = Error_vector[1][i+13];
            }
            
            for (int i=18; i<27; i++){
                syndrome_result_ptz_m2[i] = Error_vector[0][i+2];
            }
            for (int i=27; i<36; i++){
                syndrome_result_ptz_m2[i] = Error_vector[1][i+13];
            }
            
            
            
            syndrome_result_ptz_m3[0] = Error_vector[0][20];  //m1
            syndrome_result_ptz_m3[1] = Error_vector[0][21];  //m2
            syndrome_result_ptz_m3[2] = Error_vector[0][22];  //m3
            syndrome_result_ptz_m3[3] = Error_vector[0][23];  //m4
            syndrome_result_ptz_m3[4] = Error_vector[0][24];  //m5
            syndrome_result_ptz_m3[5] = Error_vector[0][25];  //m6
            syndrome_result_ptz_m3[6] = Error_vector[0][26];  //m7
            syndrome_result_ptz_m3[7] = Error_vector[0][27];  //m8
            syndrome_result_ptz_m3[8] = Error_vector[0][28];  //m9
            syndrome_result_ptz_m3[9] = Error_vector[1][40];  //f1
            syndrome_result_ptz_m3[10] = Error_vector[1][41];  //f2
            syndrome_result_ptz_m3[11] = Error_vector[1][42];  //m3
            syndrome_result_ptz_m3[12] = Error_vector[1][43];  //f4
            syndrome_result_ptz_m3[13] = Error_vector[1][44];  //f5
            syndrome_result_ptz_m3[14] = Error_vector[1][45];  //f6
            syndrome_result_ptz_m3[15] = Error_vector[1][46];  //f7
            syndrome_result_ptz_m3[16] = Error_vector[1][47];  //f8
            syndrome_result_ptz_m3[17] = Error_vector[1][48];  //f9
            
            
            syndrome_result_ptz_m4[18] = Error_vector[0][20];  //m1
            syndrome_result_ptz_m4[19] = Error_vector[0][21];  //m2
            syndrome_result_ptz_m4[20] = Error_vector[0][22];  //m3
            syndrome_result_ptz_m4[21] = Error_vector[0][23];  //m4
            syndrome_result_ptz_m4[22] = Error_vector[0][24];  //m5
            syndrome_result_ptz_m4[23] = Error_vector[0][25];  //m6
            syndrome_result_ptz_m4[24] = Error_vector[0][26];  //m7
            syndrome_result_ptz_m4[25] = Error_vector[0][27];  //m8
            syndrome_result_ptz_m4[26] = Error_vector[0][28];  //m9
            syndrome_result_ptz_m4[27] = Error_vector[1][40];  //f1
            syndrome_result_ptz_m4[28] = Error_vector[1][41];  //f2
            syndrome_result_ptz_m4[29] = Error_vector[1][42];  //f3
            syndrome_result_ptz_m4[30] = Error_vector[1][43];  //m4
            syndrome_result_ptz_m4[31] = Error_vector[1][44];  //f5
            syndrome_result_ptz_m4[32] = Error_vector[1][45];  //f6
            syndrome_result_ptz_m4[33] = Error_vector[1][46];  //f7
            syndrome_result_ptz_m4[34] = Error_vector[1][47];  //f8
            syndrome_result_ptz_m4[35] = Error_vector[1][48];  //f9
            
            for (int i=18; i<27; i++){
                syndrome_result_ptz_m1[i] = Error_vector[0][i+2];
            }
            for (int i=27; i<36; i++){
                syndrome_result_ptz_m1[i] = Error_vector[1][i+13];
            }
            
            for (int i=18; i<27; i++){
                syndrome_result_ptz_m2[i] = Error_vector[0][i+2];
            }
            for (int i=27; i<36; i++){
                syndrome_result_ptz_m2[i] = Error_vector[1][i+13];
            }
            
            
            
            if (   ( Error_vector[1][40] !=0  || Error_vector[1][41] !=0 || Error_vector[1][42] !=0 || Error_vector[1][43] !=0  || Error_vector[1][44] !=0  || Error_vector[1][45] !=0 || Error_vector[1][46] !=0 || Error_vector[1][47] !=0 || Error_vector[1][48] !=0 )   ){
                
                
                
                
                for(int i=0; i<2; i++){
                    for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                }
                
                
                parallel_flag(Error_vector, probability, gamma, alpha, beta );
                
                
                
                //第二次Flag circuit的量測記錄
                
                // Z-type measurement result
                syndrome_result_ptz_f1[36] = Error_vector[0][20];  //m1
                syndrome_result_ptz_f1[37] = Error_vector[0][21];  //m2
                syndrome_result_ptz_f1[38] = Error_vector[0][22];  //m3
                syndrome_result_ptz_f1[39] = Error_vector[0][23];  //m4
                syndrome_result_ptz_f1[40] = Error_vector[0][24];  //m5
                syndrome_result_ptz_f1[41] = Error_vector[0][25];  //m6
                syndrome_result_ptz_f1[42] = Error_vector[0][26];  //m7
                syndrome_result_ptz_f1[43] = Error_vector[0][27];  //m8
                syndrome_result_ptz_f1[44] = Error_vector[0][28];  //m9
                // X-type measurement result
                syndrome_result_ptz_f1[45] = Error_vector[1][30];  //m1
                syndrome_result_ptz_f1[46] = Error_vector[1][31];  //m2
                syndrome_result_ptz_f1[47] = Error_vector[1][32];  //m3
                syndrome_result_ptz_f1[48] = Error_vector[1][33];  //m4
                syndrome_result_ptz_f1[49] = Error_vector[1][34];  //m5
                syndrome_result_ptz_f1[50] = Error_vector[1][35];  //m6
                syndrome_result_ptz_f1[51] = Error_vector[1][36];  //m7
                syndrome_result_ptz_f1[52] = Error_vector[1][37];  //m8
                syndrome_result_ptz_f1[53] = Error_vector[1][38];  //m9
                // Z-type flag result
                syndrome_result_ptz_f1[54] = Error_vector[1][40];  //f1
                syndrome_result_ptz_f1[55] = Error_vector[1][41];  //f2
                syndrome_result_ptz_f1[56] = Error_vector[1][42];  //f3
                syndrome_result_ptz_f1[57] = Error_vector[1][43];  //f4
                syndrome_result_ptz_f1[58] = Error_vector[1][44];  //f5
                syndrome_result_ptz_f1[59] = Error_vector[1][45];  //f6
                syndrome_result_ptz_f1[60] = Error_vector[1][46];  //f7
                syndrome_result_ptz_f1[61] = Error_vector[1][47];  //f8
                syndrome_result_ptz_f1[62] = Error_vector[1][48];  //f9
                // X-type flag result
                syndrome_result_ptz_f1[63] = Error_vector[0][50];  //f1
                syndrome_result_ptz_f1[64] = Error_vector[0][51];  //f2
                syndrome_result_ptz_f1[65] = Error_vector[0][52];  //f3
                syndrome_result_ptz_f1[66] = Error_vector[0][53];  //f4
                syndrome_result_ptz_f1[67] = Error_vector[0][54];  //f5
                syndrome_result_ptz_f1[68] = Error_vector[0][55];  //f6
                syndrome_result_ptz_f1[69] = Error_vector[0][56];  //f7
                syndrome_result_ptz_f1[70] = Error_vector[0][57];  //f8
                syndrome_result_ptz_f1[71] = Error_vector[0][58];  //f9
                
                
                // Z-type measurement result
                syndrome_result_ptz_f4[36] = Error_vector[0][20];  //m1
                syndrome_result_ptz_f4[37] = Error_vector[0][21];  //m2
                syndrome_result_ptz_f4[38] = Error_vector[0][22];  //m3
                syndrome_result_ptz_f4[39] = Error_vector[0][23];  //m4
                syndrome_result_ptz_f4[40] = Error_vector[0][24];  //m5
                syndrome_result_ptz_f4[41] = Error_vector[0][25];  //m6
                syndrome_result_ptz_f4[42] = Error_vector[0][26];  //m7
                syndrome_result_ptz_f4[43] = Error_vector[0][27];  //m8
                syndrome_result_ptz_f4[44] = Error_vector[0][28];  //m9
                // X-type measurement result
                syndrome_result_ptz_f4[45] = Error_vector[1][30];  //m1
                syndrome_result_ptz_f4[46] = Error_vector[1][31];  //m2
                syndrome_result_ptz_f4[47] = Error_vector[1][32];  //m3
                syndrome_result_ptz_f4[48] = Error_vector[1][33];  //m4
                syndrome_result_ptz_f4[49] = Error_vector[1][34];  //m5
                syndrome_result_ptz_f4[50] = Error_vector[1][35];  //m6
                syndrome_result_ptz_f4[51] = Error_vector[1][36];  //m7
                syndrome_result_ptz_f4[52] = Error_vector[1][37];  //m8
                syndrome_result_ptz_f4[53] = Error_vector[1][38];  //m9
                
                
                int flag_result = 0;
                
                for (int i=0; i<10; i++){
                    flag_result = flag_result + Error_vector[1][40+i] +  Error_vector[0][50+i]  ;
                }
                
                
                if ( flag_result != 0){
                    
                    
                    
                    for(int i=0; i<2; i++){
                        for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    
                    unflagged(Error_vector, probability, gamma, alpha, beta );
                    
                    
                    
                    for (int i=0; i<9; i++){
                        syndrome_result_ptz_f1[i] = Error_vector[0][i+20];
                    }
                    for (int i=0; i<9; i++){
                        syndrome_result_ptz_f1[i+9] = Error_vector[1][i+30];
                    }
                    
                    
                    //compare test1 and symdorme_result array and get index j
                    for (int j=0; j<table_length_ptz_f1; j++){
                        
                        for (int i=0; i<table_width_ptz_f1; i++){
                            test1_ptz_f1[i]=syndrome_ptz_f1[j][i];
                        }
                        // 排除syndrome = 0000的情快
                        //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                        //	break;
                        //}
                        
                        compare_result = memcmp(test1_ptz_f1, syndrome_result_ptz_f1,sizeof(syndrome_result_ptz_f1));
                        
                        if (compare_result == 0) {
                            
                            table_index = j;
                            
                            //        cout <<  "j= "  << j << endl;
                            //使用recovery進行 x error
                            
                            for (int k=0; k<19; k++){
                                Error_vector[0][k]= (Error_vector[0][k]+recovery_ptz_f1[j][k])%2;
                                Error_vector[1][k]= (Error_vector[1][k]+recovery_ptz_f1[j][k+19])%2;
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
                        for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    
                    parallel_flag(Error_vector, probability, gamma, alpha, beta );
                    
                    syndrome_result_ptz_f2[36] = Error_vector[0][20];  //m1
                    syndrome_result_ptz_f2[37] = Error_vector[0][21];  //m2
                    syndrome_result_ptz_f2[38] = Error_vector[0][22];  //m3
                    syndrome_result_ptz_f2[39] = Error_vector[0][23];  //m4
                    syndrome_result_ptz_f2[40] = Error_vector[0][24];  //m5
                    syndrome_result_ptz_f2[41] = Error_vector[0][25];  //m6
                    syndrome_result_ptz_f2[42] = Error_vector[0][26];  //m7
                    syndrome_result_ptz_f2[43] = Error_vector[0][27];  //m8
                    syndrome_result_ptz_f2[44] = Error_vector[0][28];  //m9
                    // X-type measurement result
                    syndrome_result_ptz_f2[45] = Error_vector[1][30];  //m1
                    syndrome_result_ptz_f2[46] = Error_vector[1][31];  //m2
                    syndrome_result_ptz_f2[47] = Error_vector[1][32];  //m3
                    syndrome_result_ptz_f2[48] = Error_vector[1][33];  //m4
                    syndrome_result_ptz_f2[49] = Error_vector[1][34];  //m5
                    syndrome_result_ptz_f2[50] = Error_vector[1][35];  //m6
                    syndrome_result_ptz_f2[51] = Error_vector[1][36];  //m7
                    syndrome_result_ptz_f2[52] = Error_vector[1][37];  //m8
                    syndrome_result_ptz_f2[53] = Error_vector[1][38];  //m9
                    // Z-type flag result
                    syndrome_result_ptz_f2[54] = Error_vector[1][40];  //f1
                    syndrome_result_ptz_f2[55] = Error_vector[1][41];  //f2
                    syndrome_result_ptz_f2[56] = Error_vector[1][42];  //f3
                    syndrome_result_ptz_f2[57] = Error_vector[1][43];  //f4
                    syndrome_result_ptz_f2[58] = Error_vector[1][44];  //f5
                    syndrome_result_ptz_f2[59] = Error_vector[1][45];  //f6
                    syndrome_result_ptz_f2[60] = Error_vector[1][46];  //f7
                    syndrome_result_ptz_f2[61] = Error_vector[1][47];  //f8
                    syndrome_result_ptz_f2[62] = Error_vector[1][48];  //f9
                    // X-type flag result
                    syndrome_result_ptz_f2[63] = Error_vector[0][50];  //f1
                    syndrome_result_ptz_f2[64] = Error_vector[0][51];  //f2
                    syndrome_result_ptz_f2[65] = Error_vector[0][52];  //f3
                    syndrome_result_ptz_f2[66] = Error_vector[0][53];  //f4
                    syndrome_result_ptz_f2[67] = Error_vector[0][54];  //f5
                    syndrome_result_ptz_f2[68] = Error_vector[0][55];  //f6
                    syndrome_result_ptz_f2[69] = Error_vector[0][56];  //f7
                    syndrome_result_ptz_f2[70] = Error_vector[0][57];  //f8
                    syndrome_result_ptz_f2[71] = Error_vector[0][58];  //f9
                    
                    
                    // Z-type measurement result
                    syndrome_result_ptz_f3[18] = Error_vector[0][20];  //m1
                    syndrome_result_ptz_f3[19] = Error_vector[0][21];  //m2
                    syndrome_result_ptz_f3[20] = Error_vector[0][22];  //m3
                    syndrome_result_ptz_f3[21] = Error_vector[0][23];  //m4
                    syndrome_result_ptz_f3[22] = Error_vector[0][24];  //m5
                    syndrome_result_ptz_f3[23] = Error_vector[0][25];  //m6
                    syndrome_result_ptz_f3[24] = Error_vector[0][26];  //m7
                    syndrome_result_ptz_f3[25] = Error_vector[0][27];  //m8
                    syndrome_result_ptz_f3[26] = Error_vector[0][28];  //m9
                    // X-type measurement result
                    syndrome_result_ptz_f3[27] = Error_vector[1][30];  //m1
                    syndrome_result_ptz_f3[28] = Error_vector[1][31];  //m2
                    syndrome_result_ptz_f3[29] = Error_vector[1][32];  //m3
                    syndrome_result_ptz_f3[30] = Error_vector[1][33];  //m4
                    syndrome_result_ptz_f3[31] = Error_vector[1][34];  //m5
                    syndrome_result_ptz_f3[32] = Error_vector[1][35];  //m6
                    syndrome_result_ptz_f3[33] = Error_vector[1][36];  //m7
                    syndrome_result_ptz_f3[34] = Error_vector[1][37];  //m8
                    syndrome_result_ptz_f3[35] = Error_vector[1][38];  //m9
                    // Z-type flag result
                    syndrome_result_ptz_f3[36] = Error_vector[1][40];  //f1
                    syndrome_result_ptz_f3[37] = Error_vector[1][41];  //f2
                    syndrome_result_ptz_f3[38] = Error_vector[1][42];  //f3
                    syndrome_result_ptz_f3[39] = Error_vector[1][43];  //f4
                    syndrome_result_ptz_f3[40] = Error_vector[1][44];  //f5
                    syndrome_result_ptz_f3[41] = Error_vector[1][45];  //f6
                    syndrome_result_ptz_f3[42] = Error_vector[1][46];  //f7
                    syndrome_result_ptz_f3[43] = Error_vector[1][47];  //f8
                    syndrome_result_ptz_f3[44] = Error_vector[1][48];  //f9
                    // X-type flag result
                    syndrome_result_ptz_f3[45] = Error_vector[0][50];  //f1
                    syndrome_result_ptz_f3[46] = Error_vector[0][51];  //f2
                    syndrome_result_ptz_f3[47] = Error_vector[0][52];  //f3
                    syndrome_result_ptz_f3[48] = Error_vector[0][53];  //f4
                    syndrome_result_ptz_f3[49] = Error_vector[0][54];  //f5
                    syndrome_result_ptz_f3[50] = Error_vector[0][55];  //f6
                    syndrome_result_ptz_f3[51] = Error_vector[0][56];  //f7
                    syndrome_result_ptz_f3[52] = Error_vector[0][57];  //f8
                    syndrome_result_ptz_f3[53] = Error_vector[0][58];  //f9
                    
                    // Z-type measurement result
                    syndrome_result_ptz_f4[54] = Error_vector[0][20];  //m1
                    syndrome_result_ptz_f4[55] = Error_vector[0][21];  //m2
                    syndrome_result_ptz_f4[56] = Error_vector[0][22];  //m3
                    syndrome_result_ptz_f4[57] = Error_vector[0][23];  //m4
                    syndrome_result_ptz_f4[58] = Error_vector[0][24];  //m5
                    syndrome_result_ptz_f4[59] = Error_vector[0][25];  //m6
                    syndrome_result_ptz_f4[60] = Error_vector[0][26];  //m7
                    syndrome_result_ptz_f4[61] = Error_vector[0][27];  //m8
                    syndrome_result_ptz_f4[62] = Error_vector[0][28];  //m9
                    // X-type measurement result
                    syndrome_result_ptz_f4[63] = Error_vector[1][30];  //m1
                    syndrome_result_ptz_f4[64] = Error_vector[1][31];  //m2
                    syndrome_result_ptz_f4[65] = Error_vector[1][32];  //m3
                    syndrome_result_ptz_f4[66] = Error_vector[1][33];  //m4
                    syndrome_result_ptz_f4[67] = Error_vector[1][34];  //m5
                    syndrome_result_ptz_f4[68] = Error_vector[1][35];  //m6
                    syndrome_result_ptz_f4[69] = Error_vector[1][36];  //m7
                    syndrome_result_ptz_f4[70] = Error_vector[1][37];  //m8
                    syndrome_result_ptz_f4[71] = Error_vector[1][38];  //m9
                    
                    flag_result = 0;
                    
                    for (int i=0; i<10; i++){
                        flag_result = flag_result + Error_vector[1][40+i] + Error_vector[0][50+i] ;
                    }
                    
                    
                    if ( flag_result != 0){   	// 第三次量測 flag rised
                        
                        
                        for(int i=0; i<2; i++){
                            for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                        }
                        
                        
                        unflagged(Error_vector, probability, gamma, alpha, beta );
                        
                        
                        
                        
                        //--use unflagged syndrome do error correction---------------------------------------
                        //-----------------------------------------
                        //loading syndorme result to array
                        
                        for (int i=0; i<9; i++){
                            syndrome_result_ptz_f2[i] = Error_vector[0][i+20];
                        }
                        for (int i=0; i<9; i++){
                            syndrome_result_ptz_f2[i+9] = Error_vector[1][i+30];
                        }
                        
                        
                        //compare test1 and symdorme_result array and get index j
                        for (int j=0; j<table_length_ptz_f2; j++){
                            
                            for (int i=0; i<table_width_ptz_f2; i++){
                                test1_ptz_f2[i]=syndrome_ptz_f2[j][i];
                            }
                            // 排除syndrome = 0000的情快
                            //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                            //	break;
                            //}
                            
                            compare_result = memcmp(test1_ptz_f2, syndrome_result_ptz_f2,sizeof(syndrome_result_ptz_f2));
                            
                            if (compare_result == 0) {
                                
                                table_index = j;
                                
                                //        cout <<  "j= "  << j << endl;
                                //使用recovery進行 x error
                                
                                for (int k=0; k<19; k++){
                                    Error_vector[0][k]= (Error_vector[0][k]+recovery_ptz_f2[j][k])%2;
                                    Error_vector[1][k]= (Error_vector[1][k]+recovery_ptz_f2[j][k+19])%2;
                                }
                                break;
                                
                            }
                            
                        }
                        
                        
                    }  	// 第三次量測 flag rised
                    else {    	// 第三次量測 flag do not rised
                        
                        
                        int s2_result[18] = {0};
                        int s3_result[18] = {0};
                        
                        for (int i=0; i<18; i++){
                            s2_result[i] = syndrome_result_ptz_f1[i+36];
                        }
                        for (int i=0; i<18; i++){
                            s3_result[i] = syndrome_result_ptz_f2[i+36];
                        }
                        
                        compare_result = memcmp(s2_result, s3_result,sizeof(s2_result));
                        
                        if (compare_result == 0){  // s2=s3
                            
                            
                            for (int j=0; j<table_length_ptz_f3; j++){
                                for (int i=0; i<table_width_ptz_f3; i++){
                                    test1_ptz_f3[i]=syndrome_ptz_f3[j][i];
                                }
                                // 排除syndrome = 0000的情快
                                //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                //	break;
                                //}
                                
                                compare_result = memcmp(test1_ptz_f3, syndrome_result_ptz_f3,sizeof(syndrome_result_ptz_f3));
                                
                                if (compare_result == 0) {
                                    
                                    table_index = j;
                                    
                                    //        cout <<  "j= "  << j << endl;
                                    //使用recovery進行 x error
                                    
                                    for (int k=0; k<19; k++){
                                        Error_vector[0][k]= (Error_vector[0][k]+recovery_ptz_f3[j][k])%2;
                                        Error_vector[1][k]= (Error_vector[1][k]+recovery_ptz_f3[j][k+19])%2;
                                    }
                                    break;
                                    
                                }
                                
                            }
                            
                            
                        }  // s2 = s3
                        
                        else {  //s2 unequal s3
                            
                            
                            for(int i=0; i<2; i++){
                                for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                            }
                            
                            
                            
                            unflagged(Error_vector, probability, gamma, alpha, beta );
                            
                            
                            //--use unflagged syndrome do error correction---------------------------------------
                            //-----------------------------------------
                            //loading syndorme result to array
                            
                            for (int i=0; i<9; i++){
                                syndrome_result_ptz_f4[i] = Error_vector[0][i+20];
                            }
                            for (int i=0; i<9; i++){
                                syndrome_result_ptz_f4[i+9] = Error_vector[1][i+30];
                            }
                            
                            
                            //compare test1 and symdorme_result array and get index j
                            for (int j=0; j<table_length_ptz_f4; j++){
                                
                                for (int i=0; i<table_width_ptz_f4; i++){
                                    test1_ptz_f4[i]=syndrome_ptz_f4[j][i];
                                }
                                // 排除syndrome = 0000的情快
                                //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                //	break;
                                //}
                                
                                compare_result = memcmp(test1_ptz_f4, syndrome_result_ptz_f4,sizeof(syndrome_result_ptz_f4));
                                
                                if (compare_result == 0) {
                                    
                                    table_index = j;
                                    
                                    //        cout <<  "j= "  << j << endl;
                                    //使用recovery進行 x error
                                    
                                    for (int k=0; k<19; k++){
                                        Error_vector[0][k]= (Error_vector[0][k]+recovery_ptz_f4[j][k])%2;
                                        Error_vector[1][k]= (Error_vector[1][k]+recovery_ptz_f4[j][k+19])%2;
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
            
            else if ( Error_vector[0][20] !=0 || Error_vector[0][21] !=0  ||  Error_vector[0][22] !=0 || Error_vector[0][23] !=0  ||  Error_vector[0][24] !=0 || Error_vector[0][25] !=0  ||  Error_vector[0][26] !=0 || Error_vector[0][27] !=0 || Error_vector[0][28] !=0   ) {
                
                
                
                
                
                for(int i=0; i<2; i++){
                    for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                }
                
                
                parallel_flag(Error_vector, probability, gamma, alpha, beta );
                
                
                
                // Z-type measurement result
                syndrome_result_ptz_m1[36] = Error_vector[0][20];  //m1
                syndrome_result_ptz_m1[37] = Error_vector[0][21];  //m2
                syndrome_result_ptz_m1[38] = Error_vector[0][22];  //m3
                syndrome_result_ptz_m1[39] = Error_vector[0][23];  //m4
                syndrome_result_ptz_m1[40] = Error_vector[0][24];  //m5
                syndrome_result_ptz_m1[41] = Error_vector[0][25];  //m6
                syndrome_result_ptz_m1[42] = Error_vector[0][26];  //m7
                syndrome_result_ptz_m1[43] = Error_vector[0][27];  //m8
                syndrome_result_ptz_m1[44] = Error_vector[0][28];  //m9
                // X-type measurement result
                syndrome_result_ptz_m1[45] = Error_vector[1][30];  //m1
                syndrome_result_ptz_m1[46] = Error_vector[1][31];  //m2
                syndrome_result_ptz_m1[47] = Error_vector[1][32];  //m3
                syndrome_result_ptz_m1[48] = Error_vector[1][33];  //m4
                syndrome_result_ptz_m1[49] = Error_vector[1][34];  //m5
                syndrome_result_ptz_m1[50] = Error_vector[1][35];  //m6
                syndrome_result_ptz_m1[51] = Error_vector[1][36];  //m7
                syndrome_result_ptz_m1[52] = Error_vector[1][37];  //m8
                syndrome_result_ptz_m1[53] = Error_vector[1][38];  //m9
                // Z-type flag result
                syndrome_result_ptz_m1[54] = Error_vector[1][40];  //f1
                syndrome_result_ptz_m1[55] = Error_vector[1][41];  //f2
                syndrome_result_ptz_m1[56] = Error_vector[1][42];  //f3
                syndrome_result_ptz_m1[57] = Error_vector[1][43];  //f4
                syndrome_result_ptz_m1[58] = Error_vector[1][44];  //f5
                syndrome_result_ptz_m1[59] = Error_vector[1][45];  //f6
                syndrome_result_ptz_m1[60] = Error_vector[1][46];  //f7
                syndrome_result_ptz_m1[61] = Error_vector[1][47];  //f8
                syndrome_result_ptz_m1[62] = Error_vector[1][48];  //f9
                // X-type flag result
                syndrome_result_ptz_m1[63] = Error_vector[0][50];  //f1
                syndrome_result_ptz_m1[64] = Error_vector[0][51];  //f2
                syndrome_result_ptz_m1[65] = Error_vector[0][52];  //f3
                syndrome_result_ptz_m1[66] = Error_vector[0][53];  //f4
                syndrome_result_ptz_m1[67] = Error_vector[0][54];  //f5
                syndrome_result_ptz_m1[68] = Error_vector[0][55];  //f6
                syndrome_result_ptz_m1[69] = Error_vector[0][56];  //f7
                syndrome_result_ptz_m1[70] = Error_vector[0][57];  //f8
                syndrome_result_ptz_m1[71] = Error_vector[0][58];  //f9
                
                // Z-type measurement result
                syndrome_result_ptz_m3[18] = Error_vector[0][20];  //m1
                syndrome_result_ptz_m3[19] = Error_vector[0][21];  //m2
                syndrome_result_ptz_m3[20] = Error_vector[0][22];  //m3
                syndrome_result_ptz_m3[21] = Error_vector[0][23];  //m4
                syndrome_result_ptz_m3[22] = Error_vector[0][24];  //m5
                syndrome_result_ptz_m3[23] = Error_vector[0][25];  //m6
                syndrome_result_ptz_m3[24] = Error_vector[0][26];  //m7
                syndrome_result_ptz_m3[25] = Error_vector[0][27];  //m8
                syndrome_result_ptz_m3[26] = Error_vector[0][28];  //m9
                // X-type measurement result
                syndrome_result_ptz_m3[27] = Error_vector[1][30];  //m1
                syndrome_result_ptz_m3[28] = Error_vector[1][31];  //m2
                syndrome_result_ptz_m3[29] = Error_vector[1][32];  //m3
                syndrome_result_ptz_m3[30] = Error_vector[1][33];  //m4
                syndrome_result_ptz_m3[31] = Error_vector[1][34];  //m5
                syndrome_result_ptz_m3[32] = Error_vector[1][35];  //m6
                syndrome_result_ptz_m3[33] = Error_vector[1][36];  //m7
                syndrome_result_ptz_m3[34] = Error_vector[1][37];  //m8
                syndrome_result_ptz_m3[35] = Error_vector[1][38];  //m9
                // Z-type flag result
                syndrome_result_ptz_m3[36] = Error_vector[1][40];  //f1
                syndrome_result_ptz_m3[37] = Error_vector[1][41];  //f2
                syndrome_result_ptz_m3[38] = Error_vector[1][42];  //m3
                syndrome_result_ptz_m3[39] = Error_vector[1][43];  //f4
                syndrome_result_ptz_m3[40] = Error_vector[1][44];  //f5
                syndrome_result_ptz_m3[41] = Error_vector[1][45];  //f6
                syndrome_result_ptz_m3[42] = Error_vector[1][46];  //f7
                syndrome_result_ptz_m3[43] = Error_vector[1][47];  //f8
                syndrome_result_ptz_m3[44] = Error_vector[1][48];  //f9
                // X-type flag result
                syndrome_result_ptz_m3[45] = Error_vector[0][50];  //f1
                syndrome_result_ptz_m3[46] = Error_vector[0][51];  //f2
                syndrome_result_ptz_m3[47] = Error_vector[0][52];  //m3
                syndrome_result_ptz_m3[48] = Error_vector[0][53];  //f4
                syndrome_result_ptz_m3[49] = Error_vector[0][54];  //f5
                syndrome_result_ptz_m3[50] = Error_vector[0][55];  //f6
                syndrome_result_ptz_m3[51] = Error_vector[0][56];  //f7
                syndrome_result_ptz_m3[52] = Error_vector[0][57];  //f8
                syndrome_result_ptz_m3[53] = Error_vector[0][58];  //f9
                
                // Z-type measurement result
                syndrome_result_ptz_m4[36] = Error_vector[0][20];  //m1
                syndrome_result_ptz_m4[37] = Error_vector[0][21];  //m2
                syndrome_result_ptz_m4[38] = Error_vector[0][22];  //m3
                syndrome_result_ptz_m4[39] = Error_vector[0][23];  //m4
                syndrome_result_ptz_m4[40] = Error_vector[0][24];  //m5
                syndrome_result_ptz_m4[41] = Error_vector[0][25];  //m6
                syndrome_result_ptz_m4[42] = Error_vector[0][26];  //m7
                syndrome_result_ptz_m4[43] = Error_vector[0][27];  //m8
                syndrome_result_ptz_m4[44] = Error_vector[0][28];  //m9
                // X-type measurement result
                syndrome_result_ptz_m4[45] = Error_vector[1][30];  //m1
                syndrome_result_ptz_m4[46] = Error_vector[1][31];  //m2
                syndrome_result_ptz_m4[47] = Error_vector[1][32];  //m3
                syndrome_result_ptz_m4[48] = Error_vector[1][33];  //m4
                syndrome_result_ptz_m4[49] = Error_vector[1][34];  //m5
                syndrome_result_ptz_m4[50] = Error_vector[1][35];  //m6
                syndrome_result_ptz_m4[51] = Error_vector[1][36];  //m7
                syndrome_result_ptz_m4[52] = Error_vector[1][37];  //m8
                syndrome_result_ptz_m4[53] = Error_vector[1][38];  //m9
                
                int flag_result = 0;
                
                for (int i=0; i<10; i++){
                    flag_result = flag_result + Error_vector[1][40+i] +  Error_vector[0][50+i]  ;
                }
                
                
                if ( flag_result != 0){
                    
                    
                    
                    for(int i=0; i<2; i++){
                        for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    
                    unflagged(Error_vector, probability, gamma, alpha, beta );
                    
                    
                    
                    
                    //--use unflagged syndrome do error correction---------------------------------------
                    //-----------------------------------------
                    //loading syndorme result to array
                    
                    for (int i=0; i<9; i++){
                        syndrome_result_ptz_m1[i] = Error_vector[0][i+20];
                    }
                    for (int i=0; i<9; i++){
                        syndrome_result_ptz_m1[i+9] = Error_vector[1][i+30];
                    }
                    
                    
                    //compare test1 and symdorme_result array and get index j
                    for (int j=0; j<table_length_ptz_m1; j++){
                        
                        for (int i=0; i<table_width_ptz_m1; i++){
                            test1_ptz_m1[i]=syndrome_ptz_m1[j][i];
                        }
                        // 排除syndrome = 0000的情快
                        //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                        //	break;
                        //}
                        
                        compare_result = memcmp(test1_ptz_m1, syndrome_result_ptz_m1,sizeof(syndrome_result_ptz_m1));
                        
                        if (compare_result == 0) {
                            
                            table_index = j;
                            
                            //        cout <<  "j= "  << j << endl;
                            //使用recovery進行 x error
                            
                            for (int k=0; k<19; k++){
                                Error_vector[0][k]= (Error_vector[0][k]+recovery_ptz_m1[j][k])%2;
                                Error_vector[1][k]= (Error_vector[1][k]+recovery_ptz_m1[j][k+19])%2;
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
                        for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    
                    parallel_flag(Error_vector, probability, gamma, alpha, beta );
                    
                    // Z-type measurement result
                    syndrome_result_ptz_m2[36] = Error_vector[0][20];  //m2
                    syndrome_result_ptz_m2[37] = Error_vector[0][21];  //m2
                    syndrome_result_ptz_m2[38] = Error_vector[0][22];  //m3
                    syndrome_result_ptz_m2[39] = Error_vector[0][23];  //m4
                    syndrome_result_ptz_m2[40] = Error_vector[0][24];  //m5
                    syndrome_result_ptz_m2[41] = Error_vector[0][25];  //m6
                    syndrome_result_ptz_m2[42] = Error_vector[0][26];  //m7
                    syndrome_result_ptz_m2[43] = Error_vector[0][27];  //m8
                    syndrome_result_ptz_m2[44] = Error_vector[0][28];  //m9
                    // X-type measurement result
                    syndrome_result_ptz_m2[45] = Error_vector[1][30];  //m2
                    syndrome_result_ptz_m2[46] = Error_vector[1][31];  //m2
                    syndrome_result_ptz_m2[47] = Error_vector[1][32];  //m3
                    syndrome_result_ptz_m2[48] = Error_vector[1][33];  //m4
                    syndrome_result_ptz_m2[49] = Error_vector[1][34];  //m5
                    syndrome_result_ptz_m2[50] = Error_vector[1][35];  //m6
                    syndrome_result_ptz_m2[51] = Error_vector[1][36];  //m7
                    syndrome_result_ptz_m2[52] = Error_vector[1][37];  //m8
                    syndrome_result_ptz_m2[53] = Error_vector[1][38];  //m9
                    // Z-type flag result
                    syndrome_result_ptz_m2[54] = Error_vector[1][40];  //f1
                    syndrome_result_ptz_m2[55] = Error_vector[1][41];  //f2
                    syndrome_result_ptz_m2[56] = Error_vector[1][42];  //f3
                    syndrome_result_ptz_m2[57] = Error_vector[1][43];  //f4
                    syndrome_result_ptz_m2[58] = Error_vector[1][44];  //f5
                    syndrome_result_ptz_m2[59] = Error_vector[1][45];  //f6
                    syndrome_result_ptz_m2[60] = Error_vector[1][46];  //f7
                    syndrome_result_ptz_m2[61] = Error_vector[1][47];  //f8
                    syndrome_result_ptz_m2[62] = Error_vector[1][48];  //f9
                    // X-type flag result
                    syndrome_result_ptz_m2[63] = Error_vector[0][50];  //f1
                    syndrome_result_ptz_m2[64] = Error_vector[0][51];  //f2
                    syndrome_result_ptz_m2[65] = Error_vector[0][52];  //f3
                    syndrome_result_ptz_m2[66] = Error_vector[0][53];  //f4
                    syndrome_result_ptz_m2[67] = Error_vector[0][54];  //f5
                    syndrome_result_ptz_m2[68] = Error_vector[0][55];  //f6
                    syndrome_result_ptz_m2[69] = Error_vector[0][56];  //f7
                    syndrome_result_ptz_m2[70] = Error_vector[0][57];  //f8
                    syndrome_result_ptz_m2[71] = Error_vector[0][58];  //f9
                    
                    
                    // Z-type measurement result
                    syndrome_result_ptz_m4[54] = Error_vector[0][20];  //m1
                    syndrome_result_ptz_m4[55] = Error_vector[0][21];  //m2
                    syndrome_result_ptz_m4[56] = Error_vector[0][22];  //m3
                    syndrome_result_ptz_m4[57] = Error_vector[0][23];  //m4
                    syndrome_result_ptz_m4[58] = Error_vector[0][24];  //m5
                    syndrome_result_ptz_m4[59] = Error_vector[0][25];  //m6
                    syndrome_result_ptz_m4[60] = Error_vector[0][26];  //m7
                    syndrome_result_ptz_m4[61] = Error_vector[0][27];  //m8
                    syndrome_result_ptz_m4[62] = Error_vector[0][28];  //m9
                    // X-type measurement result
                    syndrome_result_ptz_m4[63] = Error_vector[1][30];  //m1
                    syndrome_result_ptz_m4[64] = Error_vector[1][31];  //m2
                    syndrome_result_ptz_m4[65] = Error_vector[1][32];  //m3
                    syndrome_result_ptz_m4[66] = Error_vector[1][33];  //m4
                    syndrome_result_ptz_m4[67] = Error_vector[1][34];  //m5
                    syndrome_result_ptz_m4[68] = Error_vector[1][35];  //m6
                    syndrome_result_ptz_m4[69] = Error_vector[1][36];  //m7
                    syndrome_result_ptz_m4[70] = Error_vector[1][37];  //m8
                    syndrome_result_ptz_m4[71] = Error_vector[1][38];  //m9
                    
                    flag_result = 0;
                    
                    for (int i=0; i<10; i++){
                        flag_result = flag_result + Error_vector[1][40+i] + Error_vector[0][50+i] ;
                    }
                    
                    
                    if ( flag_result != 0){   	// 第三次量測 flag rised
                        
                        
                        for(int i=0; i<2; i++){
                            for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                        }
                        
                        
                        unflagged(Error_vector, probability, gamma, alpha, beta );
                        
                        
                        
                        //--use unflagged syndrome do error correction---------------------------------------
                        //-----------------------------------------
                        //loading syndorme result to array
                        
                        for (int i=0; i<9; i++){
                            syndrome_result_ptz_m2[i] = Error_vector[0][i+20];
                        }
                        for (int i=0; i<9; i++){
                            syndrome_result_ptz_m2[i+9] = Error_vector[1][i+30];
                        }
                        
                        
                        //compare test1 and symdorme_result array and get index j
                        for (int j=0; j<table_length_ptz_m2; j++){
                            
                            for (int i=0; i<table_width_ptz_m2; i++){
                                test1_ptz_m2[i]=syndrome_ptz_m2[j][i];
                            }
                            // 排除syndrome = 0000的情快
                            //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                            //	break;
                            //}
                            
                            compare_result = memcmp(test1_ptz_m2, syndrome_result_ptz_m2,sizeof(syndrome_result_ptz_m2));
                            
                            if (compare_result == 0) {
                                
                                table_index = j;
                                
                                //        cout <<  "j= "  << j << endl;
                                //使用recovery進行 x error
                                
                                for (int k=0; k<19; k++){
                                    Error_vector[0][k]= (Error_vector[0][k]+recovery_ptz_m2[j][k])%2;
                                    Error_vector[1][k]= (Error_vector[1][k]+recovery_ptz_m2[j][k+19])%2;
                                }
                                break;
                                
                            }
                            
                        }
                        
                    }  	// 第三次量測 flag rised
                    else {    	// 第三次量測 flag do not rised
                        
                        
                        int s2_result[18] = {0};
                        int s3_result[18] = {0};
                        
                        for (int i=0; i<18; i++){
                            s2_result[i] = syndrome_result_ptz_m1[i+36];
                        }
                        for (int i=0; i<18; i++){
                            s3_result[i] = syndrome_result_ptz_m2[i+36];
                        }
                        
                        compare_result = memcmp(s2_result, s3_result,sizeof(s2_result));
                        
                        if (compare_result == 0){  // s2=s3
                            
                            
                            
                            //compare test1 and symdorme_result array and get index j
                            for (int j=0; j<table_length_ptz_m3; j++){
                                for (int i=0; i<table_width_ptz_m3; i++){
                                    test1_ptz_m3[i]=syndrome_ptz_m3[j][i];
                                }
                                // 排除syndrome = 0000的情快
                                //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                //	break;
                                //}
                                
                                compare_result = memcmp(test1_ptz_m3, syndrome_result_ptz_m3,sizeof(syndrome_result_ptz_m3));
                                
                                if (compare_result == 0) {
                                    
                                    table_index = j;
                                    
                                    //        cout <<  "j= "  << j << endl;
                                    //使用recovery進行 x error
                                    
                                    for (int k=0; k<19; k++){
                                        Error_vector[0][k]= (Error_vector[0][k]+recovery_ptz_m3[j][k])%2;
                                        Error_vector[1][k]= (Error_vector[1][k]+recovery_ptz_m3[j][k+19])%2;
                                    }
                                    break;
                                    
                                }
                                
                            }
                            
                            
                        }  // s2 = s3
                        
                        
                        else {  //s2 unequal s3
                            
                            
                            for(int i=0; i<2; i++){
                                for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                            }
                            
                            
                            
                            
                            unflagged(Error_vector, probability, gamma, alpha, beta );
                            
                            
                            //--use unflagged syndrome do error correction---------------------------------------
                            //-----------------------------------------
                            //loading syndorme result to array
                            
                            for (int i=0; i<9; i++){
                                syndrome_result_ptz_m4[i] = Error_vector[0][i+20];
                            }
                            for (int i=0; i<9; i++){
                                syndrome_result_ptz_m4[i+9] = Error_vector[1][i+30];
                            }
                            
                            
                            //compare test1 and symdorme_result array and get index j
                            for (int j=0; j<table_length_ptz_m4; j++){
                                
                                for (int i=0; i<table_width_ptz_m4; i++){
                                    test1_ptz_m4[i]=syndrome_ptz_m4[j][i];
                                }
                                // 排除syndrome = 0000的情快
                                //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                //	break;
                                //}
                                
                                compare_result = memcmp(test1_ptz_m4, syndrome_result_ptz_m4,sizeof(syndrome_result_ptz_m4));
                                
                                if (compare_result == 0) {
                                    
                                    table_index = j;
                                    
                                    //        cout <<  "j= "  << j << endl;
                                    //使用recovery進行 x error
                                    
                                    for (int k=0; k<19; k++){
                                        Error_vector[0][k]= (Error_vector[0][k]+recovery_ptz_m4[j][k])%2;
                                        Error_vector[1][k]= (Error_vector[1][k]+recovery_ptz_m4[j][k+19])%2;
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
                
                
                
                
            } // 第一次量測 if
            
            
            
            ckp1:
                
                
                for(int i=0; i<2; i++){
                    for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                }
                
                
                
//------------------------------------------------------------------------------------------------------------------------------
                
                main_circuit_2(Error_vector, probability, gamma, alpha, beta );
                
                
                //協助判斷==========================================================================================
                // 判斷Z-type flag and X-type flag
                
                measure_result = 0;
                flag_result = 0;
                
                for (int i=0; i<9; i++){
                    flag_result = flag_result + Error_vector[0][50+i]  ;
                }
                
                
                for (int i=0; i<9; i++){
                    measure_result = measure_result + Error_vector[1][30+i] ;
                }
                //==========================================================================================
                
                if ( measure_result ==0 && flag_result==0 ){
                    
                    goto ckp2;
                    
                }
                
                
                syndrome_result_ptx_f1[18] = Error_vector[1][30];  //m1
                syndrome_result_ptx_f1[19] = Error_vector[1][31];  //m2
                syndrome_result_ptx_f1[20] = Error_vector[1][32];  //m3
                syndrome_result_ptx_f1[21] = Error_vector[1][33];  //m4
                syndrome_result_ptx_f1[22] = Error_vector[1][34];  //m5
                syndrome_result_ptx_f1[23] = Error_vector[1][35];  //m6
                syndrome_result_ptx_f1[24] = Error_vector[1][36];  //m7
                syndrome_result_ptx_f1[25] = Error_vector[1][37];  //m8
                syndrome_result_ptx_f1[26] = Error_vector[1][38];  //m9
                syndrome_result_ptx_f1[27] = Error_vector[0][50];  //f1
                syndrome_result_ptx_f1[28] = Error_vector[0][51];  //f2
                syndrome_result_ptx_f1[29] = Error_vector[0][52];  //f3
                syndrome_result_ptx_f1[30] = Error_vector[0][53];  //f4
                syndrome_result_ptx_f1[31] = Error_vector[0][54];  //f5
                syndrome_result_ptx_f1[32] = Error_vector[0][55];  //f6
                syndrome_result_ptx_f1[33] = Error_vector[0][56];  //f7
                syndrome_result_ptx_f1[34] = Error_vector[0][57];  //f8
                syndrome_result_ptx_f1[35] = Error_vector[0][58];  //f9
                
                syndrome_result_ptx_f2[18] = Error_vector[1][30];  //m1
                syndrome_result_ptx_f2[19] = Error_vector[1][31];  //m2
                syndrome_result_ptx_f2[20] = Error_vector[1][32];  //m3
                syndrome_result_ptx_f2[21] = Error_vector[1][33];  //m4
                syndrome_result_ptx_f2[22] = Error_vector[1][34];  //m5
                syndrome_result_ptx_f2[23] = Error_vector[1][35];  //m6
                syndrome_result_ptx_f2[24] = Error_vector[1][36];  //m7
                syndrome_result_ptx_f2[25] = Error_vector[1][37];  //m8
                syndrome_result_ptx_f2[26] = Error_vector[1][38];  //m9
                syndrome_result_ptx_f2[27] = Error_vector[0][50];  //f1
                syndrome_result_ptx_f2[28] = Error_vector[0][51];  //f2
                syndrome_result_ptx_f2[29] = Error_vector[0][52];  //f3
                syndrome_result_ptx_f2[30] = Error_vector[0][53];  //f4
                syndrome_result_ptx_f2[31] = Error_vector[0][54];  //f5
                syndrome_result_ptx_f2[32] = Error_vector[0][55];  //f6
                syndrome_result_ptx_f2[33] = Error_vector[0][56];  //f7
                syndrome_result_ptx_f2[34] = Error_vector[0][57];  //f8
                syndrome_result_ptx_f2[35] = Error_vector[0][58];  //f9
                
                
                syndrome_result_ptx_f3[0] = Error_vector[1][30];  //m1
                syndrome_result_ptx_f3[1] = Error_vector[1][31];  //m2
                syndrome_result_ptx_f3[2] = Error_vector[1][32];  //m3
                syndrome_result_ptx_f3[3] = Error_vector[1][33];  //m4
                syndrome_result_ptx_f3[4] = Error_vector[1][34];  //m5
                syndrome_result_ptx_f3[5] = Error_vector[1][35];  //m6
                syndrome_result_ptx_f3[6] = Error_vector[1][36];  //m7
                syndrome_result_ptx_f3[7] = Error_vector[1][37];  //m8
                syndrome_result_ptx_f3[8] = Error_vector[1][38];  //m9
                syndrome_result_ptx_f3[9] = Error_vector[0][50];  //f1
                syndrome_result_ptx_f3[10] = Error_vector[0][51];  //f2
                syndrome_result_ptx_f3[11] = Error_vector[0][52];  //f3
                syndrome_result_ptx_f3[12] = Error_vector[0][53];  //f4
                syndrome_result_ptx_f3[13] = Error_vector[0][54];  //f5
                syndrome_result_ptx_f3[14] = Error_vector[0][55];  //f6
                syndrome_result_ptx_f3[15] = Error_vector[0][56];  //f7
                syndrome_result_ptx_f3[16] = Error_vector[0][57];  //f8
                syndrome_result_ptx_f3[17] = Error_vector[0][58];  //f9
                
                
                syndrome_result_ptx_f4[18] = Error_vector[1][30];  //m1
                syndrome_result_ptx_f4[19] = Error_vector[1][31];  //m2
                syndrome_result_ptx_f4[20] = Error_vector[1][32];  //m3
                syndrome_result_ptx_f4[21] = Error_vector[1][33];  //m4
                syndrome_result_ptx_f4[22] = Error_vector[1][34];  //m5
                syndrome_result_ptx_f4[23] = Error_vector[1][35];  //m6
                syndrome_result_ptx_f4[24] = Error_vector[1][36];  //m7
                syndrome_result_ptx_f4[25] = Error_vector[1][37];  //m8
                syndrome_result_ptx_f4[26] = Error_vector[1][38];  //m9
                syndrome_result_ptx_f4[27] = Error_vector[0][50];  //f1
                syndrome_result_ptx_f4[28] = Error_vector[0][51];  //f2
                syndrome_result_ptx_f4[29] = Error_vector[0][52];  //f3
                syndrome_result_ptx_f4[30] = Error_vector[0][53];  //f4
                syndrome_result_ptx_f4[31] = Error_vector[0][54];  //f5
                syndrome_result_ptx_f4[32] = Error_vector[0][55];  //f6
                syndrome_result_ptx_f4[33] = Error_vector[0][56];  //f7
                syndrome_result_ptx_f4[34] = Error_vector[0][57];  //f8
                syndrome_result_ptx_f4[35] = Error_vector[0][58];  //f9
                
                
                syndrome_result_ptx_m1[18] = Error_vector[1][30];  //m1
                syndrome_result_ptx_m1[19] = Error_vector[1][31];  //m2
                syndrome_result_ptx_m1[20] = Error_vector[1][32];  //m3
                syndrome_result_ptx_m1[21] = Error_vector[1][33];  //m4
                syndrome_result_ptx_m1[22] = Error_vector[1][34];  //m5
                syndrome_result_ptx_m1[23] = Error_vector[1][35];  //m6
                syndrome_result_ptx_m1[24] = Error_vector[1][36];  //m7
                syndrome_result_ptx_m1[25] = Error_vector[1][37];  //m8
                syndrome_result_ptx_m1[26] = Error_vector[1][38];  //m9
                syndrome_result_ptx_m1[27] = Error_vector[0][50];  //f1
                syndrome_result_ptx_m1[28] = Error_vector[0][51];  //f2
                syndrome_result_ptx_m1[29] = Error_vector[0][52];  //f3
                syndrome_result_ptx_m1[30] = Error_vector[0][53];  //f4
                syndrome_result_ptx_m1[31] = Error_vector[0][54];  //f5
                syndrome_result_ptx_m1[32] = Error_vector[0][55];  //f6
                syndrome_result_ptx_m1[33] = Error_vector[0][56];  //f7
                syndrome_result_ptx_m1[34] = Error_vector[0][57];  //f8
                syndrome_result_ptx_m1[35] = Error_vector[0][58];  //f9
                
                syndrome_result_ptx_m2[18] = Error_vector[1][30];  //m1
                syndrome_result_ptx_m2[19] = Error_vector[1][31];  //m2
                syndrome_result_ptx_m2[20] = Error_vector[1][32];  //m3
                syndrome_result_ptx_m2[21] = Error_vector[1][33];  //m4
                syndrome_result_ptx_m2[22] = Error_vector[1][34];  //m5
                syndrome_result_ptx_m2[23] = Error_vector[1][35];  //m6
                syndrome_result_ptx_m2[24] = Error_vector[1][36];  //m7
                syndrome_result_ptx_m2[25] = Error_vector[1][37];  //m8
                syndrome_result_ptx_m2[26] = Error_vector[1][38];  //m9
                syndrome_result_ptx_m2[27] = Error_vector[0][50];  //f1
                syndrome_result_ptx_m2[28] = Error_vector[0][51];  //f2
                syndrome_result_ptx_m2[29] = Error_vector[0][52];  //f3
                syndrome_result_ptx_m2[30] = Error_vector[0][53];  //f4
                syndrome_result_ptx_m2[31] = Error_vector[0][54];  //f5
                syndrome_result_ptx_m2[32] = Error_vector[0][55];  //f6
                syndrome_result_ptx_m2[33] = Error_vector[0][56];  //f7
                syndrome_result_ptx_m2[34] = Error_vector[0][57];  //f8
                syndrome_result_ptx_m2[35] = Error_vector[0][58];  //f9
                
                syndrome_result_ptx_m3[0] = Error_vector[1][30];  //m1
                syndrome_result_ptx_m3[1] = Error_vector[1][31];  //m2
                syndrome_result_ptx_m3[2] = Error_vector[1][32];  //m3
                syndrome_result_ptx_m3[3] = Error_vector[1][33];  //m4
                syndrome_result_ptx_m3[4] = Error_vector[1][34];  //m5
                syndrome_result_ptx_m3[5] = Error_vector[1][35];  //m6
                syndrome_result_ptx_m3[6] = Error_vector[1][36];  //m7
                syndrome_result_ptx_m3[7] = Error_vector[1][37];  //m8
                syndrome_result_ptx_m3[8] = Error_vector[1][38];  //m9
                syndrome_result_ptx_m3[9] = Error_vector[0][50];  //f1
                syndrome_result_ptx_m3[10] = Error_vector[0][51];  //f2
                syndrome_result_ptx_m3[11] = Error_vector[0][52];  //f3
                syndrome_result_ptx_m3[12] = Error_vector[0][53];  //f4
                syndrome_result_ptx_m3[13] = Error_vector[0][54];  //f5
                syndrome_result_ptx_m3[14] = Error_vector[0][55];  //f6
                syndrome_result_ptx_m3[15] = Error_vector[0][56];  //f7
                syndrome_result_ptx_m3[16] = Error_vector[0][57];  //f8
                syndrome_result_ptx_m3[17] = Error_vector[0][58];  //f9
                
                syndrome_result_ptx_m4[18] = Error_vector[1][30];  //m1
                syndrome_result_ptx_m4[19] = Error_vector[1][31];  //m2
                syndrome_result_ptx_m4[20] = Error_vector[1][32];  //m3
                syndrome_result_ptx_m4[21] = Error_vector[1][33];  //m4
                syndrome_result_ptx_m4[22] = Error_vector[1][34];  //m5
                syndrome_result_ptx_m4[23] = Error_vector[1][35];  //m6
                syndrome_result_ptx_m4[24] = Error_vector[1][36];  //m7
                syndrome_result_ptx_m4[25] = Error_vector[1][37];  //m8
                syndrome_result_ptx_m4[26] = Error_vector[1][38];  //m9
                syndrome_result_ptx_m4[27] = Error_vector[0][50];  //f1
                syndrome_result_ptx_m4[28] = Error_vector[0][51];  //f2
                syndrome_result_ptx_m4[29] = Error_vector[0][52];  //f3
                syndrome_result_ptx_m4[30] = Error_vector[0][53];  //f4
                syndrome_result_ptx_m4[31] = Error_vector[0][54];  //f5
                syndrome_result_ptx_m4[32] = Error_vector[0][55];  //f6
                syndrome_result_ptx_m4[33] = Error_vector[0][56];  //f7
                syndrome_result_ptx_m4[34] = Error_vector[0][57];  //f8
                syndrome_result_ptx_m4[35] = Error_vector[0][58];  //f9
                
                
                
                if (    Error_vector[0][50] !=0 || Error_vector[0][51] !=0 || Error_vector[0][52] !=0 || Error_vector[0][53] !=0  || Error_vector[0][54] !=0 || Error_vector[0][55] !=0  || Error_vector[0][56] !=0  || Error_vector[0][57] !=0 || Error_vector[0][58] !=0     ){
                    
                    
                    
                    
                    for(int i=0; i<2; i++){
                        for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    
                    parallel_flag(Error_vector, probability, gamma, alpha, beta );
                    
                    
                    
                    // Z-type measurement result
                    syndrome_result_ptx_f1[36] = Error_vector[0][20];  //m1
                    syndrome_result_ptx_f1[37] = Error_vector[0][21];  //m2
                    syndrome_result_ptx_f1[38] = Error_vector[0][22];  //m3
                    syndrome_result_ptx_f1[39] = Error_vector[0][23];  //m4
                    syndrome_result_ptx_f1[40] = Error_vector[0][24];  //m5
                    syndrome_result_ptx_f1[41] = Error_vector[0][25];  //m6
                    syndrome_result_ptx_f1[42] = Error_vector[0][26];  //m7
                    syndrome_result_ptx_f1[43] = Error_vector[0][27];  //m8
                    syndrome_result_ptx_f1[44] = Error_vector[0][28];  //m9
                    // X-type measurement result
                    syndrome_result_ptx_f1[45] = Error_vector[1][30];  //m1
                    syndrome_result_ptx_f1[46] = Error_vector[1][31];  //m2
                    syndrome_result_ptx_f1[47] = Error_vector[1][32];  //m3
                    syndrome_result_ptx_f1[48] = Error_vector[1][33];  //m4
                    syndrome_result_ptx_f1[49] = Error_vector[1][34];  //m5
                    syndrome_result_ptx_f1[50] = Error_vector[1][35];  //m6
                    syndrome_result_ptx_f1[51] = Error_vector[1][36];  //m7
                    syndrome_result_ptx_f1[52] = Error_vector[1][37];  //m8
                    syndrome_result_ptx_f1[53] = Error_vector[1][38];  //m9
                    // Z-type flag result
                    syndrome_result_ptx_f1[54] = Error_vector[1][40];  //f1
                    syndrome_result_ptx_f1[55] = Error_vector[1][41];  //f2
                    syndrome_result_ptx_f1[56] = Error_vector[1][42];  //f3
                    syndrome_result_ptx_f1[57] = Error_vector[1][43];  //f4
                    syndrome_result_ptx_f1[58] = Error_vector[1][44];  //f5
                    syndrome_result_ptx_f1[59] = Error_vector[1][45];  //f6
                    syndrome_result_ptx_f1[60] = Error_vector[1][46];  //f7
                    syndrome_result_ptx_f1[61] = Error_vector[1][47];  //f8
                    syndrome_result_ptx_f1[62] = Error_vector[1][48];  //f9
                    // X-type flag result
                    syndrome_result_ptx_f1[63] = Error_vector[0][50];  //f1
                    syndrome_result_ptx_f1[64] = Error_vector[0][51];  //f2
                    syndrome_result_ptx_f1[65] = Error_vector[0][52];  //f3
                    syndrome_result_ptx_f1[66] = Error_vector[0][53];  //f4
                    syndrome_result_ptx_f1[67] = Error_vector[0][54];  //f5
                    syndrome_result_ptx_f1[68] = Error_vector[0][55];  //f6
                    syndrome_result_ptx_f1[69] = Error_vector[0][56];  //f7
                    syndrome_result_ptx_f1[70] = Error_vector[0][57];  //f8
                    syndrome_result_ptx_f1[71] = Error_vector[0][58];  //f9
                    
                    
                    // Z-type measurement result
                    syndrome_result_ptx_f4[36] = Error_vector[0][20];  //m1
                    syndrome_result_ptx_f4[37] = Error_vector[0][21];  //m2
                    syndrome_result_ptx_f4[38] = Error_vector[0][22];  //m3
                    syndrome_result_ptx_f4[39] = Error_vector[0][23];  //m4
                    syndrome_result_ptx_f4[40] = Error_vector[0][24];  //m5
                    syndrome_result_ptx_f4[41] = Error_vector[0][25];  //m6
                    syndrome_result_ptx_f4[42] = Error_vector[0][26];  //m7
                    syndrome_result_ptx_f4[43] = Error_vector[0][27];  //m8
                    syndrome_result_ptx_f4[44] = Error_vector[0][28];  //m9
                    // X-type measurement result
                    syndrome_result_ptx_f4[45] = Error_vector[1][30];  //m1
                    syndrome_result_ptx_f4[46] = Error_vector[1][31];  //m2
                    syndrome_result_ptx_f4[47] = Error_vector[1][32];  //m3
                    syndrome_result_ptx_f4[48] = Error_vector[1][33];  //m4
                    syndrome_result_ptx_f4[49] = Error_vector[1][34];  //m5
                    syndrome_result_ptx_f4[50] = Error_vector[1][35];  //m6
                    syndrome_result_ptx_f4[51] = Error_vector[1][36];  //m7
                    syndrome_result_ptx_f4[52] = Error_vector[1][37];  //m8
                    syndrome_result_ptx_f4[53] = Error_vector[1][38];  //m9
                    
                    
                    int flag_result = 0;
                    
                    for (int i=0; i<10; i++){
                        flag_result = flag_result + Error_vector[1][40+i] +  Error_vector[0][50+i]  ;
                    }
                    
                    
                    if ( flag_result != 0){
                        
                        
                        
                        for(int i=0; i<2; i++){
                            for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                        }
                        
                        
                        unflagged(Error_vector, probability, gamma, alpha, beta );
                        
                        
                        
                        for (int i=0; i<9; i++){
                            syndrome_result_ptx_f1[i] = Error_vector[0][i+20];
                        }
                        for (int i=0; i<9; i++){
                            syndrome_result_ptx_f1[i+9] = Error_vector[1][i+30];
                        }
                        
                        
                        //compare test1 and symdorme_result array and get index j
                        for (int j=0; j<table_length_ptx_f1; j++){
                            
                            for (int i=0; i<table_width_ptx_f1; i++){
                                test1_ptx_f1[i]=syndrome_ptx_f1[j][i];
                            }
                            // 排除syndrome = 0000的情快
                            //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                            //	break;
                            //}
                            
                            compare_result = memcmp(test1_ptx_f1, syndrome_result_ptx_f1,sizeof(syndrome_result_ptx_f1));
                            
                            if (compare_result == 0) {
                                
                                table_index = j;
                                
                                //        cout <<  "j= "  << j << endl;
                                //使用recovery進行 x error
                                
                                for (int k=0; k<19; k++){
                                    Error_vector[0][k]= (Error_vector[0][k]+recovery_ptx_f1[j][k])%2;
                                    Error_vector[1][k]= (Error_vector[1][k]+recovery_ptx_f1[j][k+19])%2;
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
                            for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                        }
                        
                        
                        parallel_flag(Error_vector, probability, gamma, alpha, beta );
                        
                        syndrome_result_ptx_f2[36] = Error_vector[0][20];  //m1
                        syndrome_result_ptx_f2[37] = Error_vector[0][21];  //m2
                        syndrome_result_ptx_f2[38] = Error_vector[0][22];  //m3
                        syndrome_result_ptx_f2[39] = Error_vector[0][23];  //m4
                        syndrome_result_ptx_f2[40] = Error_vector[0][24];  //m5
                        syndrome_result_ptx_f2[41] = Error_vector[0][25];  //m6
                        syndrome_result_ptx_f2[42] = Error_vector[0][26];  //m7
                        syndrome_result_ptx_f2[43] = Error_vector[0][27];  //m8
                        syndrome_result_ptx_f2[44] = Error_vector[0][28];  //m9
                        // X-type measurement result
                        syndrome_result_ptx_f2[45] = Error_vector[1][30];  //m1
                        syndrome_result_ptx_f2[46] = Error_vector[1][31];  //m2
                        syndrome_result_ptx_f2[47] = Error_vector[1][32];  //m3
                        syndrome_result_ptx_f2[48] = Error_vector[1][33];  //m4
                        syndrome_result_ptx_f2[49] = Error_vector[1][34];  //m5
                        syndrome_result_ptx_f2[50] = Error_vector[1][35];  //m6
                        syndrome_result_ptx_f2[51] = Error_vector[1][36];  //m7
                        syndrome_result_ptx_f2[52] = Error_vector[1][37];  //m8
                        syndrome_result_ptx_f2[53] = Error_vector[1][38];  //m9
                        // Z-type flag result
                        syndrome_result_ptx_f2[54] = Error_vector[1][40];  //f1
                        syndrome_result_ptx_f2[55] = Error_vector[1][41];  //f2
                        syndrome_result_ptx_f2[56] = Error_vector[1][42];  //f3
                        syndrome_result_ptx_f2[57] = Error_vector[1][43];  //f4
                        syndrome_result_ptx_f2[58] = Error_vector[1][44];  //f5
                        syndrome_result_ptx_f2[59] = Error_vector[1][45];  //f6
                        syndrome_result_ptx_f2[60] = Error_vector[1][46];  //f7
                        syndrome_result_ptx_f2[61] = Error_vector[1][47];  //f8
                        syndrome_result_ptx_f2[62] = Error_vector[1][48];  //f9
                        // X-type flag result
                        syndrome_result_ptx_f2[63] = Error_vector[0][50];  //f1
                        syndrome_result_ptx_f2[64] = Error_vector[0][51];  //f2
                        syndrome_result_ptx_f2[65] = Error_vector[0][52];  //f3
                        syndrome_result_ptx_f2[66] = Error_vector[0][53];  //f4
                        syndrome_result_ptx_f2[67] = Error_vector[0][54];  //f5
                        syndrome_result_ptx_f2[68] = Error_vector[0][55];  //f6
                        syndrome_result_ptx_f2[69] = Error_vector[0][56];  //f7
                        syndrome_result_ptx_f2[70] = Error_vector[0][57];  //f8
                        syndrome_result_ptx_f2[71] = Error_vector[0][58];  //f9
                        
                        
                        // Z-type measurement result
                        syndrome_result_ptx_f3[18] = Error_vector[0][20];  //m1
                        syndrome_result_ptx_f3[19] = Error_vector[0][21];  //m2
                        syndrome_result_ptx_f3[20] = Error_vector[0][22];  //m3
                        syndrome_result_ptx_f3[21] = Error_vector[0][23];  //m4
                        syndrome_result_ptx_f3[22] = Error_vector[0][24];  //m5
                        syndrome_result_ptx_f3[23] = Error_vector[0][25];  //m6
                        syndrome_result_ptx_f3[24] = Error_vector[0][26];  //m7
                        syndrome_result_ptx_f3[25] = Error_vector[0][27];  //m8
                        syndrome_result_ptx_f3[26] = Error_vector[0][28];  //m9
                        // X-type measurement result
                        syndrome_result_ptx_f3[27] = Error_vector[1][30];  //m1
                        syndrome_result_ptx_f3[28] = Error_vector[1][31];  //m2
                        syndrome_result_ptx_f3[29] = Error_vector[1][32];  //m3
                        syndrome_result_ptx_f3[30] = Error_vector[1][33];  //m4
                        syndrome_result_ptx_f3[31] = Error_vector[1][34];  //m5
                        syndrome_result_ptx_f3[32] = Error_vector[1][35];  //m6
                        syndrome_result_ptx_f3[33] = Error_vector[1][36];  //m7
                        syndrome_result_ptx_f3[34] = Error_vector[1][37];  //m8
                        syndrome_result_ptx_f3[35] = Error_vector[1][38];  //m9
                        // Z-type flag result
                        syndrome_result_ptx_f3[36] = Error_vector[1][40];  //f1
                        syndrome_result_ptx_f3[37] = Error_vector[1][41];  //f2
                        syndrome_result_ptx_f3[38] = Error_vector[1][42];  //f3
                        syndrome_result_ptx_f3[39] = Error_vector[1][43];  //f4
                        syndrome_result_ptx_f3[40] = Error_vector[1][44];  //f5
                        syndrome_result_ptx_f3[41] = Error_vector[1][45];  //f6
                        syndrome_result_ptx_f3[42] = Error_vector[1][46];  //f7
                        syndrome_result_ptx_f3[43] = Error_vector[1][47];  //f8
                        syndrome_result_ptx_f3[44] = Error_vector[1][48];  //f9
                        // X-type flag result
                        syndrome_result_ptx_f3[45] = Error_vector[0][50];  //f1
                        syndrome_result_ptx_f3[46] = Error_vector[0][51];  //f2
                        syndrome_result_ptx_f3[47] = Error_vector[0][52];  //f3
                        syndrome_result_ptx_f3[48] = Error_vector[0][53];  //f4
                        syndrome_result_ptx_f3[49] = Error_vector[0][54];  //f5
                        syndrome_result_ptx_f3[50] = Error_vector[0][55];  //f6
                        syndrome_result_ptx_f3[51] = Error_vector[0][56];  //f7
                        syndrome_result_ptx_f3[52] = Error_vector[0][57];  //f8
                        syndrome_result_ptx_f3[53] = Error_vector[0][58];  //f9
                        
                        // Z-type measurement result
                        syndrome_result_ptx_f4[54] = Error_vector[0][20];  //m1
                        syndrome_result_ptx_f4[55] = Error_vector[0][21];  //m2
                        syndrome_result_ptx_f4[56] = Error_vector[0][22];  //m3
                        syndrome_result_ptx_f4[57] = Error_vector[0][23];  //m4
                        syndrome_result_ptx_f4[58] = Error_vector[0][24];  //m5
                        syndrome_result_ptx_f4[59] = Error_vector[0][25];  //m6
                        syndrome_result_ptx_f4[60] = Error_vector[0][26];  //m7
                        syndrome_result_ptx_f4[61] = Error_vector[0][27];  //m8
                        syndrome_result_ptx_f4[62] = Error_vector[0][28];  //m9
                        // X-type measurement result
                        syndrome_result_ptx_f4[63] = Error_vector[1][30];  //m1
                        syndrome_result_ptx_f4[64] = Error_vector[1][31];  //m2
                        syndrome_result_ptx_f4[65] = Error_vector[1][32];  //m3
                        syndrome_result_ptx_f4[66] = Error_vector[1][33];  //m4
                        syndrome_result_ptx_f4[67] = Error_vector[1][34];  //m5
                        syndrome_result_ptx_f4[68] = Error_vector[1][35];  //m6
                        syndrome_result_ptx_f4[69] = Error_vector[1][36];  //m7
                        syndrome_result_ptx_f4[70] = Error_vector[1][37];  //m8
                        syndrome_result_ptx_f4[71] = Error_vector[1][38];  //m9
                        
                        flag_result = 0;
                        
                        for (int i=0; i<10; i++){
                            flag_result = flag_result + Error_vector[1][40+i] + Error_vector[0][50+i] ;
                        }
                        
                        
                        if ( flag_result != 0){   	// 第三次量測 flag rised
                            
                            
                            for(int i=0; i<2; i++){
                                for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                            }
                            
                            
                            unflagged(Error_vector, probability, gamma, alpha, beta );
                            
                            
                            
                            
                            //--use unflagged syndrome do error correction---------------------------------------
                            //-----------------------------------------
                            //loading syndorme result to array
                            
                            for (int i=0; i<9; i++){
                                syndrome_result_ptx_f2[i] = Error_vector[0][i+20];
                            }
                            for (int i=0; i<9; i++){
                                syndrome_result_ptx_f2[i+9] = Error_vector[1][i+30];
                            }
                            
                            
                            //compare test1 and symdorme_result array and get index j
                            for (int j=0; j<table_length_ptx_f2; j++){
                                
                                for (int i=0; i<table_width_ptx_f2; i++){
                                    test1_ptx_f2[i]=syndrome_ptx_f2[j][i];
                                }
                                // 排除syndrome = 0000的情快
                                //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                //	break;
                                //}
                                
                                compare_result = memcmp(test1_ptx_f2, syndrome_result_ptx_f2,sizeof(syndrome_result_ptx_f2));
                                
                                if (compare_result == 0) {
                                    
                                    table_index = j;
                                    
                                    //        cout <<  "j= "  << j << endl;
                                    //使用recovery進行 x error
                                    
                                    for (int k=0; k<19; k++){
                                        Error_vector[0][k]= (Error_vector[0][k]+recovery_ptx_f2[j][k])%2;
                                        Error_vector[1][k]= (Error_vector[1][k]+recovery_ptx_f2[j][k+19])%2;
                                    }
                                    break;
                                    
                                }
                                
                            }
                            
                            
                        }  	// 第三次量測 flag rised
                        else {    	// 第三次量測 flag do not rised
                            
                            
                            int s2_result[18] = {0};
                            int s3_result[18] = {0};
                            
                            for (int i=0; i<18; i++){
                                s2_result[i] = syndrome_result_ptx_f1[i+36];
                            }
                            for (int i=0; i<18; i++){
                                s3_result[i] = syndrome_result_ptx_f2[i+36];
                            }
                            
                            compare_result = memcmp(s2_result, s3_result,sizeof(s2_result));
                            
                            if (compare_result == 0){  // s2=s3
                                
                                
                                for (int j=0; j<table_length_ptx_f3; j++){
                                    for (int i=0; i<table_width_ptx_f3; i++){
                                        test1_ptx_f3[i]=syndrome_ptx_f3[j][i];
                                    }
                                    // 排除syndrome = 0000的情快
                                    //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                    //	break;
                                    //}
                                    
                                    compare_result = memcmp(test1_ptx_f3, syndrome_result_ptx_f3,sizeof(syndrome_result_ptx_f3));
                                    
                                    if (compare_result == 0) {
                                        
                                        table_index = j;
                                        
                                        //        cout <<  "j= "  << j << endl;
                                        //使用recovery進行 x error
                                        
                                        for (int k=0; k<19; k++){
                                            Error_vector[0][k]= (Error_vector[0][k]+recovery_ptx_f3[j][k])%2;
                                            Error_vector[1][k]= (Error_vector[1][k]+recovery_ptx_f3[j][k+19])%2;
                                        }
                                        break;
                                        
                                    }
                                    
                                }
                                
                                
                            }  // s2 = s3
                            
                            else {  //s2 unequal s3
                                
                                
                                for(int i=0; i<2; i++){
                                    for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                                }
                                
                                
                                
                                unflagged(Error_vector, probability, gamma, alpha, beta );
                                
                                
                                //--use unflagged syndrome do error correction---------------------------------------
                                //-----------------------------------------
                                //loading syndorme result to array
                                
                                for (int i=0; i<9; i++){
                                    syndrome_result_ptx_f4[i] = Error_vector[0][i+20];
                                }
                                for (int i=0; i<9; i++){
                                    syndrome_result_ptx_f4[i+9] = Error_vector[1][i+30];
                                }
                                
                                
                                //compare test1 and symdorme_result array and get index j
                                for (int j=0; j<table_length_ptx_f4; j++){
                                    
                                    for (int i=0; i<table_width_ptx_f4; i++){
                                        test1_ptx_f4[i]=syndrome_ptx_f4[j][i];
                                    }
                                    // 排除syndrome = 0000的情快
                                    //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                    //	break;
                                    //}
                                    
                                    compare_result = memcmp(test1_ptx_f4, syndrome_result_ptx_f4,sizeof(syndrome_result_ptx_f4));
                                    
                                    if (compare_result == 0) {
                                        
                                        table_index = j;
                                        
                                        //        cout <<  "j= "  << j << endl;
                                        //使用recovery進行 x error
                                        
                                        for (int k=0; k<19; k++){
                                            Error_vector[0][k]= (Error_vector[0][k]+recovery_ptx_f4[j][k])%2;
                                            Error_vector[1][k]= (Error_vector[1][k]+recovery_ptx_f4[j][k+19])%2;
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
                
                else if ( Error_vector[0][30] !=0 || Error_vector[0][31] !=0  ||  Error_vector[0][32] !=0 || Error_vector[0][33] !=0  ||  Error_vector[0][34] !=0 || Error_vector[0][35] !=0  ||  Error_vector[0][36] !=0 || Error_vector[0][37] !=0 || Error_vector[0][38] !=0   ) {
                    
                    
                    
                    
                    
                    for(int i=0; i<2; i++){
                        for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    
                    parallel_flag(Error_vector, probability, gamma, alpha, beta );
                    
                    
                    
                    // Z-type measurement result
                    syndrome_result_ptx_m1[36] = Error_vector[0][20];  //m1
                    syndrome_result_ptx_m1[37] = Error_vector[0][21];  //m2
                    syndrome_result_ptx_m1[38] = Error_vector[0][22];  //m3
                    syndrome_result_ptx_m1[39] = Error_vector[0][23];  //m4
                    syndrome_result_ptx_m1[40] = Error_vector[0][24];  //m5
                    syndrome_result_ptx_m1[41] = Error_vector[0][25];  //m6
                    syndrome_result_ptx_m1[42] = Error_vector[0][26];  //m7
                    syndrome_result_ptx_m1[43] = Error_vector[0][27];  //m8
                    syndrome_result_ptx_m1[44] = Error_vector[0][28];  //m9
                    // X-type measurement result
                    syndrome_result_ptx_m1[45] = Error_vector[1][30];  //m1
                    syndrome_result_ptx_m1[46] = Error_vector[1][31];  //m2
                    syndrome_result_ptx_m1[47] = Error_vector[1][32];  //m3
                    syndrome_result_ptx_m1[48] = Error_vector[1][33];  //m4
                    syndrome_result_ptx_m1[49] = Error_vector[1][34];  //m5
                    syndrome_result_ptx_m1[50] = Error_vector[1][35];  //m6
                    syndrome_result_ptx_m1[51] = Error_vector[1][36];  //m7
                    syndrome_result_ptx_m1[52] = Error_vector[1][37];  //m8
                    syndrome_result_ptx_m1[53] = Error_vector[1][38];  //m9
                    // Z-type flag result
                    syndrome_result_ptx_m1[54] = Error_vector[1][40];  //f1
                    syndrome_result_ptx_m1[55] = Error_vector[1][41];  //f2
                    syndrome_result_ptx_m1[56] = Error_vector[1][42];  //f3
                    syndrome_result_ptx_m1[57] = Error_vector[1][43];  //f4
                    syndrome_result_ptx_m1[58] = Error_vector[1][44];  //f5
                    syndrome_result_ptx_m1[59] = Error_vector[1][45];  //f6
                    syndrome_result_ptx_m1[60] = Error_vector[1][46];  //f7
                    syndrome_result_ptx_m1[61] = Error_vector[1][47];  //f8
                    syndrome_result_ptx_m1[62] = Error_vector[1][48];  //f9
                    // X-type flag result
                    syndrome_result_ptx_m1[63] = Error_vector[0][50];  //f1
                    syndrome_result_ptx_m1[64] = Error_vector[0][51];  //f2
                    syndrome_result_ptx_m1[65] = Error_vector[0][52];  //f3
                    syndrome_result_ptx_m1[66] = Error_vector[0][53];  //f4
                    syndrome_result_ptx_m1[67] = Error_vector[0][54];  //f5
                    syndrome_result_ptx_m1[68] = Error_vector[0][55];  //f6
                    syndrome_result_ptx_m1[69] = Error_vector[0][56];  //f7
                    syndrome_result_ptx_m1[70] = Error_vector[0][57];  //f8
                    syndrome_result_ptx_m1[71] = Error_vector[0][58];  //f9
                    
                    // Z-type measurement result
                    syndrome_result_ptx_m3[18] = Error_vector[0][20];  //m1
                    syndrome_result_ptx_m3[19] = Error_vector[0][21];  //m2
                    syndrome_result_ptx_m3[20] = Error_vector[0][22];  //m3
                    syndrome_result_ptx_m3[21] = Error_vector[0][23];  //m4
                    syndrome_result_ptx_m3[22] = Error_vector[0][24];  //m5
                    syndrome_result_ptx_m3[23] = Error_vector[0][25];  //m6
                    syndrome_result_ptx_m3[24] = Error_vector[0][26];  //m7
                    syndrome_result_ptx_m3[25] = Error_vector[0][27];  //m8
                    syndrome_result_ptx_m3[26] = Error_vector[0][28];  //m9
                    // X-type measurement result
                    syndrome_result_ptx_m3[27] = Error_vector[1][30];  //m1
                    syndrome_result_ptx_m3[28] = Error_vector[1][31];  //m2
                    syndrome_result_ptx_m3[29] = Error_vector[1][32];  //m3
                    syndrome_result_ptx_m3[30] = Error_vector[1][33];  //m4
                    syndrome_result_ptx_m3[31] = Error_vector[1][34];  //m5
                    syndrome_result_ptx_m3[32] = Error_vector[1][35];  //m6
                    syndrome_result_ptx_m3[33] = Error_vector[1][36];  //m7
                    syndrome_result_ptx_m3[34] = Error_vector[1][37];  //m8
                    syndrome_result_ptx_m3[35] = Error_vector[1][38];  //m9
                    // Z-type flag result
                    syndrome_result_ptx_m3[36] = Error_vector[1][40];  //f1
                    syndrome_result_ptx_m3[37] = Error_vector[1][41];  //f2
                    syndrome_result_ptx_m3[38] = Error_vector[1][42];  //m3
                    syndrome_result_ptx_m3[39] = Error_vector[1][43];  //f4
                    syndrome_result_ptx_m3[40] = Error_vector[1][44];  //f5
                    syndrome_result_ptx_m3[41] = Error_vector[1][45];  //f6
                    syndrome_result_ptx_m3[42] = Error_vector[1][46];  //f7
                    syndrome_result_ptx_m3[43] = Error_vector[1][47];  //f8
                    syndrome_result_ptx_m3[44] = Error_vector[1][48];  //f9
                    // X-type flag result
                    syndrome_result_ptx_m3[45] = Error_vector[0][50];  //f1
                    syndrome_result_ptx_m3[46] = Error_vector[0][51];  //f2
                    syndrome_result_ptx_m3[47] = Error_vector[0][52];  //m3
                    syndrome_result_ptx_m3[48] = Error_vector[0][53];  //f4
                    syndrome_result_ptx_m3[49] = Error_vector[0][54];  //f5
                    syndrome_result_ptx_m3[50] = Error_vector[0][55];  //f6
                    syndrome_result_ptx_m3[51] = Error_vector[0][56];  //f7
                    syndrome_result_ptx_m3[52] = Error_vector[0][57];  //f8
                    syndrome_result_ptx_m3[53] = Error_vector[0][58];  //f9
                    
                    // Z-type measurement result
                    syndrome_result_ptx_m4[36] = Error_vector[0][20];  //m1
                    syndrome_result_ptx_m4[37] = Error_vector[0][21];  //m2
                    syndrome_result_ptx_m4[38] = Error_vector[0][22];  //m3
                    syndrome_result_ptx_m4[39] = Error_vector[0][23];  //m4
                    syndrome_result_ptx_m4[40] = Error_vector[0][24];  //m5
                    syndrome_result_ptx_m4[41] = Error_vector[0][25];  //m6
                    syndrome_result_ptx_m4[42] = Error_vector[0][26];  //m7
                    syndrome_result_ptx_m4[43] = Error_vector[0][27];  //m8
                    syndrome_result_ptx_m4[44] = Error_vector[0][28];  //m9
                    // X-type measurement result
                    syndrome_result_ptx_m4[45] = Error_vector[1][30];  //m1
                    syndrome_result_ptx_m4[46] = Error_vector[1][31];  //m2
                    syndrome_result_ptx_m4[47] = Error_vector[1][32];  //m3
                    syndrome_result_ptx_m4[48] = Error_vector[1][33];  //m4
                    syndrome_result_ptx_m4[49] = Error_vector[1][34];  //m5
                    syndrome_result_ptx_m4[50] = Error_vector[1][35];  //m6
                    syndrome_result_ptx_m4[51] = Error_vector[1][36];  //m7
                    syndrome_result_ptx_m4[52] = Error_vector[1][37];  //m8
                    syndrome_result_ptx_m4[53] = Error_vector[1][38];  //m9
                    
                    int flag_result = 0;
                    
                    for (int i=0; i<10; i++){
                        flag_result = flag_result + Error_vector[1][40+i] +  Error_vector[0][50+i]  ;
                    }
                    
                    
                    if ( flag_result != 0){
                        
                        
                        
                        for(int i=0; i<2; i++){
                            for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                        }
                        
                        
                        unflagged(Error_vector, probability, gamma, alpha, beta );
                        
                        
                        
                        
                        //--use unflagged syndrome do error correction---------------------------------------
                        //-----------------------------------------
                        //loading syndorme result to array
                        
                        for (int i=0; i<9; i++){
                            syndrome_result_ptx_m1[i] = Error_vector[0][i+20];
                        }
                        for (int i=0; i<9; i++){
                            syndrome_result_ptx_m1[i+9] = Error_vector[1][i+30];
                        }
                        
                        
                        //compare test1 and symdorme_result array and get index j
                        for (int j=0; j<table_length_ptx_m1; j++){
                            
                            for (int i=0; i<table_width_ptx_m1; i++){
                                test1_ptx_m1[i]=syndrome_ptx_m1[j][i];
                            }
                            // 排除syndrome = 0000的情快
                            //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                            //	break;
                            //}
                            
                            compare_result = memcmp(test1_ptx_m1, syndrome_result_ptx_m1,sizeof(syndrome_result_ptx_m1));
                            
                            if (compare_result == 0) {
                                
                                table_index = j;
                                
                                //        cout <<  "j= "  << j << endl;
                                //使用recovery進行 x error
                                
                                for (int k=0; k<19; k++){
                                    Error_vector[0][k]= (Error_vector[0][k]+recovery_ptx_m1[j][k])%2;
                                    Error_vector[1][k]= (Error_vector[1][k]+recovery_ptx_m1[j][k+19])%2;
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
                            for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                        }
                        
                        
                        parallel_flag(Error_vector, probability, gamma, alpha, beta );
                        
                        // Z-type measurement result
                        syndrome_result_ptx_m2[36] = Error_vector[0][20];  //m2
                        syndrome_result_ptx_m2[37] = Error_vector[0][21];  //m2
                        syndrome_result_ptx_m2[38] = Error_vector[0][22];  //m3
                        syndrome_result_ptx_m2[39] = Error_vector[0][23];  //m4
                        syndrome_result_ptx_m2[40] = Error_vector[0][24];  //m5
                        syndrome_result_ptx_m2[41] = Error_vector[0][25];  //m6
                        syndrome_result_ptx_m2[42] = Error_vector[0][26];  //m7
                        syndrome_result_ptx_m2[43] = Error_vector[0][27];  //m8
                        syndrome_result_ptx_m2[44] = Error_vector[0][28];  //m9
                        // X-type measurement result
                        syndrome_result_ptx_m2[45] = Error_vector[1][30];  //m2
                        syndrome_result_ptx_m2[46] = Error_vector[1][31];  //m2
                        syndrome_result_ptx_m2[47] = Error_vector[1][32];  //m3
                        syndrome_result_ptx_m2[48] = Error_vector[1][33];  //m4
                        syndrome_result_ptx_m2[49] = Error_vector[1][34];  //m5
                        syndrome_result_ptx_m2[50] = Error_vector[1][35];  //m6
                        syndrome_result_ptx_m2[51] = Error_vector[1][36];  //m7
                        syndrome_result_ptx_m2[52] = Error_vector[1][37];  //m8
                        syndrome_result_ptx_m2[53] = Error_vector[1][38];  //m9
                        // Z-type flag result
                        syndrome_result_ptx_m2[54] = Error_vector[1][40];  //f1
                        syndrome_result_ptx_m2[55] = Error_vector[1][41];  //f2
                        syndrome_result_ptx_m2[56] = Error_vector[1][42];  //f3
                        syndrome_result_ptx_m2[57] = Error_vector[1][43];  //f4
                        syndrome_result_ptx_m2[58] = Error_vector[1][44];  //f5
                        syndrome_result_ptx_m2[59] = Error_vector[1][45];  //f6
                        syndrome_result_ptx_m2[60] = Error_vector[1][46];  //f7
                        syndrome_result_ptx_m2[61] = Error_vector[1][47];  //f8
                        syndrome_result_ptx_m2[62] = Error_vector[1][48];  //f9
                        // X-type flag result
                        syndrome_result_ptx_m2[63] = Error_vector[0][50];  //f1
                        syndrome_result_ptx_m2[64] = Error_vector[0][51];  //f2
                        syndrome_result_ptx_m2[65] = Error_vector[0][52];  //f3
                        syndrome_result_ptx_m2[66] = Error_vector[0][53];  //f4
                        syndrome_result_ptx_m2[67] = Error_vector[0][54];  //f5
                        syndrome_result_ptx_m2[68] = Error_vector[0][55];  //f6
                        syndrome_result_ptx_m2[69] = Error_vector[0][56];  //f7
                        syndrome_result_ptx_m2[70] = Error_vector[0][57];  //f8
                        syndrome_result_ptx_m2[71] = Error_vector[0][58];  //f9
                        
                        
                        // Z-type measurement result
                        syndrome_result_ptx_m4[54] = Error_vector[0][20];  //m1
                        syndrome_result_ptx_m4[55] = Error_vector[0][21];  //m2
                        syndrome_result_ptx_m4[56] = Error_vector[0][22];  //m3
                        syndrome_result_ptx_m4[57] = Error_vector[0][23];  //m4
                        syndrome_result_ptx_m4[58] = Error_vector[0][24];  //m5
                        syndrome_result_ptx_m4[59] = Error_vector[0][25];  //m6
                        syndrome_result_ptx_m4[60] = Error_vector[0][26];  //m7
                        syndrome_result_ptx_m4[61] = Error_vector[0][27];  //m8
                        syndrome_result_ptx_m4[62] = Error_vector[0][28];  //m9
                        // X-type measurement result
                        syndrome_result_ptx_m4[63] = Error_vector[1][30];  //m1
                        syndrome_result_ptx_m4[64] = Error_vector[1][31];  //m2
                        syndrome_result_ptx_m4[65] = Error_vector[1][32];  //m3
                        syndrome_result_ptx_m4[66] = Error_vector[1][33];  //m4
                        syndrome_result_ptx_m4[67] = Error_vector[1][34];  //m5
                        syndrome_result_ptx_m4[68] = Error_vector[1][35];  //m6
                        syndrome_result_ptx_m4[69] = Error_vector[1][36];  //m7
                        syndrome_result_ptx_m4[70] = Error_vector[1][37];  //m8
                        syndrome_result_ptx_m4[71] = Error_vector[1][38];  //m9
                        
                        flag_result = 0;
                        
                        for (int i=0; i<10; i++){
                            flag_result = flag_result + Error_vector[1][40+i] + Error_vector[0][50+i] ;
                        }
                        
                        
                        if ( flag_result != 0){   	// 第三次量測 flag rised
                            
                            
                            for(int i=0; i<2; i++){
                                for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                            }
                            
                            
                            unflagged(Error_vector, probability, gamma, alpha, beta );
                            
                            
                            
                            //--use unflagged syndrome do error correction---------------------------------------
                            //-----------------------------------------
                            //loading syndorme result to array
                            
                            for (int i=0; i<9; i++){
                                syndrome_result_ptx_m2[i] = Error_vector[0][i+20];
                            }
                            for (int i=0; i<9; i++){
                                syndrome_result_ptx_m2[i+9] = Error_vector[1][i+30];
                            }
                            
                            
                            //compare test1 and symdorme_result array and get index j
                            for (int j=0; j<table_length_ptx_m2; j++){
                                
                                for (int i=0; i<table_width_ptx_m2; i++){
                                    test1_ptx_m2[i]=syndrome_ptx_m2[j][i];
                                }
                                // 排除syndrome = 0000的情快
                                //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                //	break;
                                //}
                                
                                compare_result = memcmp(test1_ptx_m2, syndrome_result_ptx_m2,sizeof(syndrome_result_ptx_m2));
                                
                                if (compare_result == 0) {
                                    
                                    table_index = j;
                                    
                                    //        cout <<  "j= "  << j << endl;
                                    //使用recovery進行 x error
                                    
                                    for (int k=0; k<19; k++){
                                        Error_vector[0][k]= (Error_vector[0][k]+recovery_ptx_m2[j][k])%2;
                                        Error_vector[1][k]= (Error_vector[1][k]+recovery_ptx_m2[j][k+19])%2;
                                    }
                                    break;
                                    
                                }
                                
                            }
                            
                        }  	// 第三次量測 flag rised
                        else {    	// 第三次量測 flag do not rised
                            
                            
                            int s2_result[18] = {0};
                            int s3_result[18] = {0};
                            
                            for (int i=0; i<18; i++){
                                s2_result[i] = syndrome_result_ptx_m1[i+36];
                            }
                            for (int i=0; i<18; i++){
                                s3_result[i] = syndrome_result_ptx_m2[i+36];
                            }
                            
                            compare_result = memcmp(s2_result, s3_result,sizeof(s2_result));
                            
                            if (compare_result == 0){  // s2=s3
                                
                                
                                
                                //compare test1 and symdorme_result array and get index j
                                for (int j=0; j<table_length_ptx_m3; j++){
                                    for (int i=0; i<table_width_ptx_m3; i++){
                                        test1_ptx_m3[i]=syndrome_ptx_m3[j][i];
                                    }
                                    // 排除syndrome = 0000的情快
                                    //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                    //	break;
                                    //}
                                    
                                    compare_result = memcmp(test1_ptx_m3, syndrome_result_ptx_m3,sizeof(syndrome_result_ptx_m3));
                                    
                                    if (compare_result == 0) {
                                        
                                        table_index = j;
                                        
                                        //        cout <<  "j= "  << j << endl;
                                        //使用recovery進行 x error
                                        
                                        for (int k=0; k<19; k++){
                                            Error_vector[0][k]= (Error_vector[0][k]+recovery_ptx_m3[j][k])%2;
                                            Error_vector[1][k]= (Error_vector[1][k]+recovery_ptx_m3[j][k+19])%2;
                                        }
                                        break;
                                        
                                    }
                                    
                                }
                                
                                
                            }  // s2 = s3
                            
                            
                            else {  //s2 unequal s3
                                
                                
                                for(int i=0; i<2; i++){
                                    for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                                }
                                
                                
                                
                                
                                unflagged(Error_vector, probability, gamma, alpha, beta );
                                
                                
                                //--use unflagged syndrome do error correction---------------------------------------
                                //-----------------------------------------
                                //loading syndorme result to array
                                
                                for (int i=0; i<9; i++){
                                    syndrome_result_ptx_m4[i] = Error_vector[0][i+20];
                                }
                                for (int i=0; i<9; i++){
                                    syndrome_result_ptx_m4[i+9] = Error_vector[1][i+30];
                                }
                                
                                
                                //compare test1 and symdorme_result array and get index j
                                for (int j=0; j<table_length_ptx_m4; j++){
                                    
                                    for (int i=0; i<table_width_ptx_m4; i++){
                                        test1_ptx_m4[i]=syndrome_ptx_m4[j][i];
                                    }
                                    // 排除syndrome = 0000的情快
                                    //if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  && symdorme_result[4] == 0 &&  symdorme_result[5] == 0 && symdorme_result[6] == 0 && symdorme_result[7] == 0 && symdorme_result[8] == 0 && symdorme_result[9] == 0 ){
                                    //	break;
                                    //}
                                    
                                    compare_result = memcmp(test1_ptx_m4, syndrome_result_ptx_m4,sizeof(syndrome_result_ptx_m4));
                                    
                                    if (compare_result == 0) {
                                        
                                        table_index = j;
                                        
                                        //        cout <<  "j= "  << j << endl;
                                        //使用recovery進行 x error
                                        
                                        for (int k=0; k<19; k++){
                                            Error_vector[0][k]= (Error_vector[0][k]+recovery_ptx_m4[j][k])%2;
                                            Error_vector[1][k]= (Error_vector[1][k]+recovery_ptx_m4[j][k+19])%2;
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
                    
                    
                    
                    
                } // 第一次量測 if
                
                ckp2:
                    
                    
                    
                    
//------------------------------------------------------------------------------------------------------------------------------
                    
                    
                    
//---Perfect circuit------------------------------------------------------------------------------------------------------------
                    
                    
                    for(int i=0; i<2; i++){
                        for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                    }
                    
                    // X measurement (1-A)
                    x_circuit(Error_vector, probability, gamma, alpha, beta );
                    
                    // Z measurement (1-B)
                    z_circuit(Error_vector, probability, gamma, alpha, beta);
                    
                    
                    //loading syndorme result to array
                    for (int i=0; i<9; i++){
                        symdorme_result_x[i] = Error_vector[0][i+20];
                    }
                    for (int i=0; i<9; i++){
                        symdorme_result_z[i] = Error_vector[1][i+30];
                    }
                    
                    
                    
                    
                    //compare test1 and symdorme_result_z array and get index j
                    for (int j=0; j<190; j++){
                        
                        for (int i=0; i<9; i++){
                            test1[i]=syndrome[j][i];
                        }
                        // 排除syndrome = 0000的情快
                        
                        if (symdorme_result_x[0] == 0 &&  symdorme_result_x[1] == 0 && symdorme_result_x[2] == 0 && symdorme_result_x[3] == 0 && symdorme_result_x[4] == 0 &&  symdorme_result_x[5] == 0 && symdorme_result_x[6] == 0 && symdorme_result_x[7] == 0 && symdorme_result_x[8] == 0  ){
                            break;
                        }
                        
                        compare_result = memcmp(test1, symdorme_result_x,sizeof(symdorme_result_x));
                        
                        if (compare_result == 0) {
                            //   table_index = j;
                            //使用recovery進行 x error
                            
                            for (int k=0; k<19; k++){
                                Error_vector[0][k]= (Error_vector[0][k]+recovery[j][k])%2;
                            }
                            break;
                            
                        }
                    }
                    
                    
                    
                    //compare test1 and symdorme_result_x array and get index j
                    
                    
                    for (int j=0; j<190; j++){
                        
                        for (int i=0; i<9; i++){
                            test1[i]=syndrome[j][i];
                        }
                        
                        
                        if (symdorme_result_z[0] == 0 &&  symdorme_result_z[1] == 0 && symdorme_result_z[2] == 0 && symdorme_result_z[3] == 0 && symdorme_result_z[4] == 0 &&  symdorme_result_z[5] == 0 && symdorme_result_z[6] == 0 && symdorme_result_z[7] == 0 && symdorme_result_z[8] == 0  ){
                            break;
                        }
                        
                        compare_result = memcmp(test1, symdorme_result_z,sizeof(symdorme_result_z));
                        
                        if (compare_result == 0) {
                            table_index = j;
                            
                            //使用table_r進行 Z error
                            for (int k=0; k<19; k++){
                                Error_vector[1][k]= (Error_vector[1][k]+recovery[j][k])%2;
                                
                            }
                            break;
                            
                        }
                    }
                    
                    
                    
                    
//------------------------------------------------------------------------------------------------------------------------------
                    
                    
                    //排除logci X, logic Z
                    s9=0;
                    s10=0;
                    
                    for (int i=0; i<19;i++){
                        s9=(s9+Error_vector[0][i])%2;
                    }
                    for (int i=0; i<19;i++){
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
    
    //cout <<  "gamma = " << gamma << endl;
    
    
    
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
    if(Error_vector[0][a]==1){                                     // X error 發生
        Error_vector[0][b] = (Error_vector[0][b] + 1)%2;
    }
    if(Error_vector[1][b]==1){    								   // Z error 發生
        Error_vector[1][a] = (Error_vector[1][a] + 1)%2;
    }
    
}

int main_circuit_1(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta){
    
    
	SQerror(Error_vector, 21, probability);
    SQerror(Error_vector, 22, probability);
    SQerror(Error_vector, 23, probability);
    SQerror(Error_vector, 24, probability);
    SQerror(Error_vector, 25, probability);
    SQerror(Error_vector, 26, probability);
    SQerror(Error_vector, 27, probability);
    SQerror(Error_vector, 28, probability);
    SQerror(Error_vector, 29, probability);  
    SQerror(Error_vector, 41, probability);
    SQerror(Error_vector, 42, probability);
    SQerror(Error_vector, 43, probability);
    SQerror(Error_vector, 44, probability);
    SQerror(Error_vector, 45, probability);
    SQerror(Error_vector, 46, probability);
    SQerror(Error_vector, 47, probability);
    SQerror(Error_vector, 48, probability);
    SQerror(Error_vector, 49, probability);  
     
    

								
//*********************************************************************************************************************************



								//slot.1==========================================================================================
								// g4 Number A ------------------------------------------------------------------
								CNOT(Error_vector, 1, 24);
								TQerror(Error_vector, 1, 24, probability * beta);
							    // g8 NumberA ------------------------------------------------------------------
								CNOT(Error_vector, 8, 28);
								TQerror(Error_vector, 8, 28, probability * beta);
								// g9 NumberA ------------------------------------------------------------------
								CNOT(Error_vector, 5, 29);
								TQerror(Error_vector, 5, 29, probability * beta);

								//SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								//SQerror(Error_vector, 5, probability*gamma);
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
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								


								
								//slot.2==========================================================================================
								
								
								// g1 Number A ------------------------------------------------------------------
								CNOT(Error_vector, 1, 21);
								TQerror(Error_vector, 1, 21, probability * beta);	
								
								// g4 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 41, 24);
								TQerror(Error_vector, 41, 24, probability * beta);
								
								// g5 Number B->A ------------------------------------------------------------------
								CNOT(Error_vector, 9, 25);
								TQerror(Error_vector, 9, 25, probability * beta);
								
								// g8 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 44, 28);
								TQerror(Error_vector, 44, 28, probability * beta);
								
								// g9 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 45, 29);
								TQerror(Error_vector, 45, 29, probability * beta);


								//SQerror(Error_vector, 1, probability*gamma);
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
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								





								//slot.3==========================================================================================

								// g1 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 41, 21);
								TQerror(Error_vector, 41, 21, probability * beta);
								// g3 Number A ------------------------------------------------------------------
								CNOT(Error_vector, 12, 23);
								TQerror(Error_vector, 12, 23, probability * beta);
								// g4 Number B ------------------------------------------------------------------
								CNOT(Error_vector, 2, 24);
								TQerror(Error_vector, 2, 24, probability * beta);
								// g5 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 47, 25);
								TQerror(Error_vector, 47, 25, probability * beta);
								// g8 NumberB ------------------------------------------------------------------
								CNOT(Error_vector, 9, 28);
								TQerror(Error_vector, 9, 28, probability * beta);
								// g9 NumberB ------------------------------------------------------------------
								CNOT(Error_vector, 7, 29);
								TQerror(Error_vector, 7, 29, probability * beta);


								SQerror(Error_vector, 1, probability*gamma);
								//SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								//SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								//SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								SQerror(Error_vector, 11, probability*gamma);
								//SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

								SQerror(Error_vector, 44, probability*gamma);
								SQerror(Error_vector, 45, probability*gamma);


								
								//slot.4==========================================================================================

								// g1 Number B ------------------------------------------------------------------
								CNOT(Error_vector, 2, 21);
								TQerror(Error_vector, 2, 21, probability * beta);
								
								// g3 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 45, 23);
								TQerror(Error_vector, 45, 23, probability * beta);							
								// g4 flag 2 ------------------------------------------------------------------
								CNOT(Error_vector, 42, 24);
								TQerror(Error_vector, 42, 24, probability * beta);
							    // g5 Number A->B ------------------------------------------------------------------
								CNOT(Error_vector, 6, 25);
								TQerror(Error_vector, 6, 25, probability * beta);
								// g6 Number A ------------------------------------------------------------------
								CNOT(Error_vector, 16, 26);
								TQerror(Error_vector, 16, 26, probability * beta);
								// g7 NumberA ------------------------------------------------------------------
								CNOT(Error_vector, 10, 27);
								TQerror(Error_vector, 10, 27, probability * beta);
								// g8 flag 2 ------------------------------------------------------------------
								CNOT(Error_vector, 48, 28);
								TQerror(Error_vector, 48, 28, probability * beta);
								// g9 flag 2 ------------------------------------------------------------------
								CNOT(Error_vector, 46, 29);
								TQerror(Error_vector, 46, 29, probability * beta);

								
								SQerror(Error_vector, 1, probability*gamma);
								//SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								//SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								//SQerror(Error_vector, 10, probability*gamma);
								SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								//SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

								SQerror(Error_vector, 41, probability*gamma);
								SQerror(Error_vector, 44, probability*gamma);
								SQerror(Error_vector, 47, probability*gamma);

								
								//slot.5==========================================================================================


								// g1 Number C ------------------------------------------------------------------
								CNOT(Error_vector, 3, 21);
								TQerror(Error_vector, 3, 21, probability * beta);
								// g2 Number A ------------------------------------------------------------------
								CNOT(Error_vector, 1, 22);
								TQerror(Error_vector, 1, 22, probability * beta);
								// g3 Number B ------------------------------------------------------------------
								CNOT(Error_vector, 13, 23);
								TQerror(Error_vector, 13, 23, probability * beta);
								// g4 Number C ------------------------------------------------------------------
								CNOT(Error_vector, 5, 24);
								TQerror(Error_vector, 5, 24, probability * beta);
								// g5 Number C ------------------------------------------------------------------
								CNOT(Error_vector, 16, 25);
								TQerror(Error_vector, 16, 25, probability * beta);
								// g6 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 47, 26);
								TQerror(Error_vector, 47, 26, probability * beta);
								// g8 NumberD ------------------------------------------------------------------
								CNOT(Error_vector, 11, 28);
								TQerror(Error_vector, 11, 28, probability * beta);
								// g9 NumberC ------------------------------------------------------------------
								CNOT(Error_vector, 8, 29);
								TQerror(Error_vector, 8, 29, probability * beta);

								//SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								//SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								//SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								//SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								//SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								//SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								//SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								
								SQerror(Error_vector, 27, probability*gamma);
								SQerror(Error_vector, 41, probability*gamma);
								SQerror(Error_vector, 42, probability*gamma);
								//SQerror(Error_vector, 43, probability*gamma);
								SQerror(Error_vector, 44, probability*gamma);
								SQerror(Error_vector, 45, probability*gamma);
								SQerror(Error_vector, 46, probability*gamma);
								//SQerror(Error_vector, 47, probability*gamma);
								SQerror(Error_vector, 48, probability*gamma);
								//SQerror(Error_vector, 49, probability*gamma);
	
								
								//slot.6==========================================================================================

								// g1 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 41, 21);
								TQerror(Error_vector, 41, 21, probability * beta);
								// g2 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 43, 22);
								TQerror(Error_vector, 43, 22, probability * beta);
								// g3 Number C ------------------------------------------------------------------
								CNOT(Error_vector, 14, 23);
								TQerror(Error_vector, 14, 23, probability * beta);
								// g4 Number D ------------------------------------------------------------------
								CNOT(Error_vector, 6, 24);	
								TQerror(Error_vector, 6, 24, probability * beta);
								// g5 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 47, 25);
								TQerror(Error_vector, 47, 25, probability * beta);
								// g6 Number D->C ------------------------------------------------------------------
								CNOT(Error_vector, 19, 26);
								TQerror(Error_vector, 19, 26, probability * beta);
								// g7 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 49, 27);
								TQerror(Error_vector, 49, 27, probability * beta);		
								// g8 NumberC ------------------------------------------------------------------
								CNOT(Error_vector, 10, 28);
								TQerror(Error_vector, 10, 28, probability * beta);
								// g9 NumberD ------------------------------------------------------------------
								CNOT(Error_vector, 11, 29);
								TQerror(Error_vector, 11, 29, probability * beta);
	
	
								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								//SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								//SQerror(Error_vector, 10, probability*gamma);
								//SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								//SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								//SQerror(Error_vector, 19, probability*gamma);
								

								//SQerror(Error_vector, 41, probability*gamma);
								SQerror(Error_vector, 42, probability*gamma);
								//SQerror(Error_vector, 43, probability*gamma);
								SQerror(Error_vector, 44, probability*gamma);
								SQerror(Error_vector, 45, probability*gamma);
								SQerror(Error_vector, 46, probability*gamma);
								//SQerror(Error_vector, 47, probability*gamma);
								SQerror(Error_vector, 48, probability*gamma);
								//SQerror(Error_vector, 49, probability*gamma);

								
								
								//slot.7==========================================================================================

								// g1 Number D ------------------------------------------------------------------
								CNOT(Error_vector, 4, 21);	
								TQerror(Error_vector, 4, 21, probability * beta);
								// g2 Number B ------------------------------------------------------------------
								CNOT(Error_vector, 3, 22);
								TQerror(Error_vector, 3, 22, probability * beta);
								// g3 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 45, 23);
								TQerror(Error_vector, 45, 23, probability * beta);						
								// g4 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 41, 24);
								TQerror(Error_vector, 41, 24, probability * beta);
								// g5 Number D ------------------------------------------------------------------
								CNOT(Error_vector, 19, 25);	
								TQerror(Error_vector, 19, 25, probability * beta);
								// g6 Number B ------------------------------------------------------------------
								CNOT(Error_vector, 17, 26);
								TQerror(Error_vector, 17, 26, probability * beta);	
								// g7 NumberC ------------------------------------------------------------------
								CNOT(Error_vector, 12, 27);
								TQerror(Error_vector, 12, 27, probability * beta);
								// g8 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 44, 28);
								TQerror(Error_vector, 44, 28, probability * beta);	
								// g9 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 45, 29);
								TQerror(Error_vector, 45, 29, probability * beta);


								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								//SQerror(Error_vector, 3, probability*gamma);
								//SQerror(Error_vector, 4, probability*gamma);
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
								//SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								//SQerror(Error_vector, 19, probability*gamma);
								

								//SQerror(Error_vector, 41, probability*gamma);
								SQerror(Error_vector, 42, probability*gamma);
								SQerror(Error_vector, 43, probability*gamma);
								//SQerror(Error_vector, 44, probability*gamma);
								//SQerror(Error_vector, 45, probability*gamma);
								SQerror(Error_vector, 46, probability*gamma);
								SQerror(Error_vector, 47, probability*gamma);
								SQerror(Error_vector, 48, probability*gamma);
								SQerror(Error_vector, 49, probability*gamma);

								
								//slot.8==========================================================================================
	
								// g2 Number C ------------------------------------------------------------------
								CNOT(Error_vector, 5, 22);
								TQerror(Error_vector, 5, 22, probability * beta);
								// g3 Number D ------------------------------------------------------------------
								CNOT(Error_vector, 15, 23);	
								TQerror(Error_vector, 15, 23, probability * beta);
								// g4 Number E ------------------------------------------------------------------
								CNOT(Error_vector, 8, 24);
								TQerror(Error_vector, 8, 24, probability * beta);
								// g6 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 47, 26);
								TQerror(Error_vector, 47, 26, probability * beta);
								// g7 NumberB ------------------------------------------------------------------
								CNOT(Error_vector, 11, 27);
								TQerror(Error_vector, 11, 27, probability * beta);
								// g8 NumberE ------------------------------------------------------------------
							 	CNOT(Error_vector, 16, 28);
							 	TQerror(Error_vector, 16, 28, probability * beta);	
								// g9 NumberE ------------------------------------------------------------------
							 	CNOT(Error_vector, 12, 29);
							 	TQerror(Error_vector, 12, 29 , probability * beta);

								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								//SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								//SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								//SQerror(Error_vector, 11, probability*gamma);
								//SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								//SQerror(Error_vector, 15, probability*gamma);
								//SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

								//SQerror(Error_vector, 41, probability*gamma);
								SQerror(Error_vector, 42, probability*gamma);
								SQerror(Error_vector, 43, probability*gamma);
								//SQerror(Error_vector, 44, probability*gamma);
								//SQerror(Error_vector, 45, probability*gamma);
								SQerror(Error_vector, 46, probability*gamma);
								//SQerror(Error_vector, 47, probability*gamma);
								SQerror(Error_vector, 48, probability*gamma);
								SQerror(Error_vector, 49, probability*gamma);

								
								//slot.9==========================================================================================							
								
								
								// g2 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 43, 22);
								TQerror(Error_vector, 43, 22, probability * beta);
								// g4 flag 2 ------------------------------------------------------------------
								CNOT(Error_vector, 42, 24);
								TQerror(Error_vector, 42, 24, probability * beta);
								// g7 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 49, 27);
								TQerror(Error_vector, 49, 27, probability * beta);	
							 	// g8 flag 2 ------------------------------------------------------------------
							 	CNOT(Error_vector, 48, 28);
							 	TQerror(Error_vector, 48, 28, probability * beta);
							 	// g9 flag 2 ------------------------------------------------------------------
							 	CNOT(Error_vector, 46, 29);
							 	TQerror(Error_vector, 46, 29, probability * beta);

									
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
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

									
								
								//slot.10==========================================================================================									
								
								
								// g2 Number D ------------------------------------------------------------------
								CNOT(Error_vector, 7, 22);	
								TQerror(Error_vector, 7, 22, probability * beta);
								// g4 Number F ------------------------------------------------------------------
								CNOT(Error_vector, 9, 24);	
								TQerror(Error_vector, 9, 24, probability * beta);
								// g6 Number C->D ------------------------------------------------------------------						
								CNOT(Error_vector, 18, 26);
								TQerror(Error_vector, 18, 26, probability * beta);
								// g7 NumberD ------------------------------------------------------------------
								CNOT(Error_vector, 15, 27);
								TQerror(Error_vector, 15, 27, probability * beta);			
							 	// g8 NumberF ------------------------------------------------------------------
								CNOT(Error_vector, 17, 28);
								TQerror(Error_vector, 17, 28, probability * beta);
							 	// g9 NumberF ------------------------------------------------------------------
								CNOT(Error_vector, 13, 29);	
								TQerror(Error_vector, 13, 29, probability * beta);			      

								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								//SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								//SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								//SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								//SQerror(Error_vector, 15, probability*gamma);
								SQerror(Error_vector, 16, probability*gamma);
								//SQerror(Error_vector, 17, probability*gamma);
								//SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);




//*********************************************************************************************************************************						


	SQerror(Error_vector, 21, probability*alpha);
    SQerror(Error_vector, 22, probability*alpha);
    SQerror(Error_vector, 23, probability*alpha);
    SQerror(Error_vector, 24, probability*alpha);
    SQerror(Error_vector, 25, probability*alpha);
    SQerror(Error_vector, 26, probability*alpha);
    SQerror(Error_vector, 27, probability*alpha);
    SQerror(Error_vector, 28, probability*alpha);
    SQerror(Error_vector, 29, probability*alpha);  
    SQerror(Error_vector, 41, probability*alpha);
    SQerror(Error_vector, 42, probability*alpha);
    SQerror(Error_vector, 43, probability*alpha);
    SQerror(Error_vector, 44, probability*alpha);
    SQerror(Error_vector, 45, probability*alpha);
    SQerror(Error_vector, 46, probability*alpha);
    SQerror(Error_vector, 47, probability*alpha);
    SQerror(Error_vector, 48, probability*alpha);
    SQerror(Error_vector, 49, probability*alpha);     
    
    
    
    
}



int main_circuit_2(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta){
    

    SQerror(Error_vector, 31, probability);
    SQerror(Error_vector, 32, probability);
    SQerror(Error_vector, 33, probability);
    SQerror(Error_vector, 34, probability);
    SQerror(Error_vector, 35, probability);
    SQerror(Error_vector, 36, probability);
    SQerror(Error_vector, 37, probability);
    SQerror(Error_vector, 38, probability);
    SQerror(Error_vector, 39, probability);    
    SQerror(Error_vector, 51, probability);
    SQerror(Error_vector, 52, probability);
    SQerror(Error_vector, 53, probability);
    SQerror(Error_vector, 54, probability);
    SQerror(Error_vector, 55, probability);
    SQerror(Error_vector, 56, probability);
    SQerror(Error_vector, 57, probability);
    SQerror(Error_vector, 58, probability);
    SQerror(Error_vector, 59, probability); 
    
//*********************************************************************************************************************************						



								//slot.1==========================================================================================
								// g4 Number A ------------------------------------------------------------------
								CNOT_rev(Error_vector, 1, 34);
								TQerror(Error_vector, 1, 34, probability * beta);
							    // g8 NumberA ------------------------------------------------------------------
								CNOT_rev(Error_vector, 8, 38);
								TQerror(Error_vector, 8, 38, probability * beta);
								// g9 NumberA ------------------------------------------------------------------
								CNOT_rev(Error_vector, 5, 39);
								TQerror(Error_vector, 5, 39, probability * beta);

								//SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								//SQerror(Error_vector, 5, probability*gamma);
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
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								


								
								//slot.2==========================================================================================
								
								
								// g1 Number A ------------------------------------------------------------------
								CNOT_rev(Error_vector, 1, 31);
								TQerror(Error_vector, 1, 31, probability * beta);	
								
								// g4 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 51, 34);
								TQerror(Error_vector, 51, 34, probability * beta);
								
								// g5 Number B->A ------------------------------------------------------------------
								CNOT_rev(Error_vector, 9, 35);
								TQerror(Error_vector, 9, 35, probability * beta);
								
								// g8 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 54, 38);
								TQerror(Error_vector, 54, 38, probability * beta);
								
								// g9 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 55, 39);
								TQerror(Error_vector, 55, 39, probability * beta);


								//SQerror(Error_vector, 1, probability*gamma);
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
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								





								//slot.3==========================================================================================

								// g1 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 51, 31);
								TQerror(Error_vector, 51, 31, probability * beta);
								// g3 Number A ------------------------------------------------------------------
								CNOT_rev(Error_vector, 12, 33);
								TQerror(Error_vector, 12, 33, probability * beta);
								// g4 Number B ------------------------------------------------------------------
								CNOT_rev(Error_vector, 2, 34);
								TQerror(Error_vector, 2, 34, probability * beta);
								// g5 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 57, 35);
								TQerror(Error_vector, 57, 35, probability * beta);
								// g8 NumberB ------------------------------------------------------------------
								CNOT_rev(Error_vector, 9, 38);
								TQerror(Error_vector, 9, 38, probability * beta);
								// g9 NumberB ------------------------------------------------------------------
								CNOT_rev(Error_vector, 7, 39);
								TQerror(Error_vector, 7, 39, probability * beta);


								SQerror(Error_vector, 1, probability*gamma);
								//SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								//SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								//SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								SQerror(Error_vector, 11, probability*gamma);
								//SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

								SQerror(Error_vector, 54, probability*gamma);
								SQerror(Error_vector, 55, probability*gamma);


								
								//slot.4==========================================================================================

								// g1 Number B ------------------------------------------------------------------
								CNOT_rev(Error_vector, 2, 31);
								TQerror(Error_vector, 2, 31, probability * beta);
								
								// g3 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 55, 33);
								TQerror(Error_vector, 55, 33, probability * beta);							
								// g4 flag 2 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 52, 34);
								TQerror(Error_vector, 52, 34, probability * beta);
							    // g5 Number A->B ------------------------------------------------------------------
								CNOT_rev(Error_vector, 6, 35);
								TQerror(Error_vector, 6, 35, probability * beta);
								// g6 Number A ------------------------------------------------------------------
								CNOT_rev(Error_vector, 16, 36);
								TQerror(Error_vector, 16, 36, probability * beta);
								// g7 NumberA ------------------------------------------------------------------
								CNOT_rev(Error_vector, 10, 37);
								TQerror(Error_vector, 10, 37, probability * beta);
								// g8 flag 2 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 58, 38);
								TQerror(Error_vector, 58, 38, probability * beta);
								// g9 flag 2 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 56, 39);
								TQerror(Error_vector, 56, 39, probability * beta);

								
								SQerror(Error_vector, 1, probability*gamma);
								//SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								//SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								//SQerror(Error_vector, 10, probability*gamma);
								SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								//SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

								SQerror(Error_vector, 51, probability*gamma);
								SQerror(Error_vector, 54, probability*gamma);
								SQerror(Error_vector, 57, probability*gamma);

								
								//slot.5==========================================================================================


								// g1 Number C ------------------------------------------------------------------
								CNOT_rev(Error_vector, 3, 31);
								TQerror(Error_vector, 3, 31, probability * beta);
								// g2 Number A ------------------------------------------------------------------
								CNOT_rev(Error_vector, 1, 32);
								TQerror(Error_vector, 1, 32, probability * beta);
								// g3 Number B ------------------------------------------------------------------
								CNOT_rev(Error_vector, 13, 33);
								TQerror(Error_vector, 13, 33, probability * beta);
								// g4 Number C ------------------------------------------------------------------
								CNOT_rev(Error_vector, 5, 34);
								TQerror(Error_vector, 5, 34, probability * beta);
								// g5 Number C ------------------------------------------------------------------
								CNOT_rev(Error_vector, 16, 35);
								TQerror(Error_vector, 16, 35, probability * beta);
								// g6 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 57, 36);
								TQerror(Error_vector, 57, 36, probability * beta);
								// g8 NumberD ------------------------------------------------------------------
								CNOT_rev(Error_vector, 11, 38);
								TQerror(Error_vector, 11, 38, probability * beta);
								// g9 NumberC ------------------------------------------------------------------
								CNOT_rev(Error_vector, 8, 39);
								TQerror(Error_vector, 8, 39, probability * beta);

								//SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								//SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								//SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								//SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								//SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								//SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								//SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								
								SQerror(Error_vector, 37, probability*gamma);
								SQerror(Error_vector, 51, probability*gamma);
								SQerror(Error_vector, 52, probability*gamma);
								//SQerror(Error_vector, 53, probability*gamma);
								SQerror(Error_vector, 54, probability*gamma);
								SQerror(Error_vector, 55, probability*gamma);
								SQerror(Error_vector, 56, probability*gamma);
								//SQerror(Error_vector, 57, probability*gamma);
								SQerror(Error_vector, 58, probability*gamma);
								//SQerror(Error_vector, 59, probability*gamma);
	
								
								//slot.6==========================================================================================

								// g1 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 51, 31);
								TQerror(Error_vector, 51, 31, probability * beta);
								// g2 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 53, 32);
								TQerror(Error_vector, 53, 32, probability * beta);
								// g3 Number C ------------------------------------------------------------------
								CNOT_rev(Error_vector, 14, 33);
								TQerror(Error_vector, 14, 33, probability * beta);
								// g4 Number D ------------------------------------------------------------------
								CNOT_rev(Error_vector, 6, 34);	
								TQerror(Error_vector, 6, 34, probability * beta);
								// g5 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 57, 35);
								TQerror(Error_vector, 57, 35, probability * beta);
								// g6 Number D->C ------------------------------------------------------------------
								CNOT_rev(Error_vector, 19, 36);
								TQerror(Error_vector, 19, 36, probability * beta);
								// g7 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 59, 37);
								TQerror(Error_vector, 59, 37, probability * beta);		
								// g8 NumberC ------------------------------------------------------------------
								CNOT_rev(Error_vector, 10, 38);
								TQerror(Error_vector, 10, 38, probability * beta);
								// g9 NumberD ------------------------------------------------------------------
								CNOT_rev(Error_vector, 11, 39);
								TQerror(Error_vector, 11, 39, probability * beta);
	
	
								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								//SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								//SQerror(Error_vector, 10, probability*gamma);
								//SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								//SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								//SQerror(Error_vector, 19, probability*gamma);
								

								//SQerror(Error_vector, 51, probability*gamma);
								SQerror(Error_vector, 52, probability*gamma);
								//SQerror(Error_vector, 53, probability*gamma);
								SQerror(Error_vector, 54, probability*gamma);
								SQerror(Error_vector, 55, probability*gamma);
								SQerror(Error_vector, 56, probability*gamma);
								//SQerror(Error_vector, 57, probability*gamma);
								SQerror(Error_vector, 58, probability*gamma);
								//SQerror(Error_vector, 59, probability*gamma);

								
								
								//slot.7==========================================================================================

								// g1 Number D ------------------------------------------------------------------
								CNOT_rev(Error_vector, 4, 31);	
								TQerror(Error_vector, 4, 31, probability * beta);
								// g2 Number B ------------------------------------------------------------------
								CNOT_rev(Error_vector, 3, 32);
								TQerror(Error_vector, 3, 32, probability * beta);
								// g3 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 55, 33);
								TQerror(Error_vector, 55, 33, probability * beta);						
								// g4 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 51, 34);
								TQerror(Error_vector, 51, 34, probability * beta);
								// g5 Number D ------------------------------------------------------------------
								CNOT_rev(Error_vector, 19, 35);	
								TQerror(Error_vector, 19, 35, probability * beta);
								// g6 Number B ------------------------------------------------------------------
								CNOT_rev(Error_vector, 17, 36);
								TQerror(Error_vector, 17, 36, probability * beta);	
								// g7 NumberC ------------------------------------------------------------------
								CNOT_rev(Error_vector, 12, 37);
								TQerror(Error_vector, 12, 37, probability * beta);
								// g8 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 54, 38);
								TQerror(Error_vector, 54, 38, probability * beta);	
								// g9 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 55, 39);
								TQerror(Error_vector, 55, 39, probability * beta);


								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								//SQerror(Error_vector, 3, probability*gamma);
								//SQerror(Error_vector, 4, probability*gamma);
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
								//SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								//SQerror(Error_vector, 19, probability*gamma);
								

								//SQerror(Error_vector, 51, probability*gamma);
								SQerror(Error_vector, 52, probability*gamma);
								SQerror(Error_vector, 53, probability*gamma);
								//SQerror(Error_vector, 54, probability*gamma);
								//SQerror(Error_vector, 55, probability*gamma);
								SQerror(Error_vector, 56, probability*gamma);
								SQerror(Error_vector, 57, probability*gamma);
								SQerror(Error_vector, 58, probability*gamma);
								SQerror(Error_vector, 59, probability*gamma);

								
								//slot.8==========================================================================================
	
								// g2 Number C ------------------------------------------------------------------
								CNOT_rev(Error_vector, 5, 32);
								TQerror(Error_vector, 5, 32, probability * beta);
								// g3 Number D ------------------------------------------------------------------
								CNOT_rev(Error_vector, 15, 33);	
								TQerror(Error_vector, 15, 33, probability * beta);
								// g4 Number E ------------------------------------------------------------------
								CNOT_rev(Error_vector, 8, 34);
								TQerror(Error_vector, 8, 34, probability * beta);
								// g6 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 57, 36);
								TQerror(Error_vector, 57, 36, probability * beta);
								// g7 NumberB ------------------------------------------------------------------
								CNOT_rev(Error_vector, 11, 37);
								TQerror(Error_vector, 11, 37, probability * beta);
								// g8 NumberE ------------------------------------------------------------------
							 	CNOT_rev(Error_vector, 16, 38);
							 	TQerror(Error_vector, 16, 38, probability * beta);	
								// g9 NumberE ------------------------------------------------------------------
							 	CNOT_rev(Error_vector, 12, 39);
							 	TQerror(Error_vector, 12, 39 , probability * beta);

								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								//SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								//SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								//SQerror(Error_vector, 11, probability*gamma);
								//SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								//SQerror(Error_vector, 15, probability*gamma);
								//SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

								//SQerror(Error_vector, 51, probability*gamma);
								SQerror(Error_vector, 52, probability*gamma);
								SQerror(Error_vector, 53, probability*gamma);
								//SQerror(Error_vector, 54, probability*gamma);
								//SQerror(Error_vector, 55, probability*gamma);
								SQerror(Error_vector, 56, probability*gamma);
								//SQerror(Error_vector, 57, probability*gamma);
								SQerror(Error_vector, 58, probability*gamma);
								SQerror(Error_vector, 59, probability*gamma);

								
								//slot.9==========================================================================================							
								
								
								// g2 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 53, 32);
								TQerror(Error_vector, 53, 32, probability * beta);
								// g4 flag 2 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 52, 34);
								TQerror(Error_vector, 52, 34, probability * beta);
								// g7 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 59, 37);
								TQerror(Error_vector, 59, 37, probability * beta);	
							 	// g8 flag 2 ------------------------------------------------------------------
							 	CNOT_rev(Error_vector, 58, 38);
							 	TQerror(Error_vector, 58, 38, probability * beta);
							 	// g9 flag 2 ------------------------------------------------------------------
							 	CNOT_rev(Error_vector, 56, 39);
							 	TQerror(Error_vector, 56, 39, probability * beta);

									
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
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

									
								
								//slot.10==========================================================================================									
								
								
								// g2 Number D ------------------------------------------------------------------
								CNOT_rev(Error_vector, 7, 32);	
								TQerror(Error_vector, 7, 32, probability * beta);
								// g4 Number F ------------------------------------------------------------------
								CNOT_rev(Error_vector, 9, 34);	
								TQerror(Error_vector, 9, 34, probability * beta);
								// g6 Number C->D ------------------------------------------------------------------						
								CNOT_rev(Error_vector, 18, 36);
								TQerror(Error_vector, 18, 36, probability * beta);
								// g7 NumberD ------------------------------------------------------------------
								CNOT_rev(Error_vector, 15, 37);
								TQerror(Error_vector, 15, 37, probability * beta);			
							 	// g8 NumberF ------------------------------------------------------------------
								CNOT_rev(Error_vector, 17, 38);
								TQerror(Error_vector, 17, 38, probability * beta);
							 	// g9 NumberF ------------------------------------------------------------------
								CNOT_rev(Error_vector, 13, 39);	
								TQerror(Error_vector, 13, 39, probability * beta);			      

								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								//SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								//SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								//SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								//SQerror(Error_vector, 15, probability*gamma);
								SQerror(Error_vector, 16, probability*gamma);
								//SQerror(Error_vector, 17, probability*gamma);
								//SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);



					   


//*********************************************************************************************************************************						


    SQerror(Error_vector, 31, probability*alpha);
    SQerror(Error_vector, 32, probability*alpha);
    SQerror(Error_vector, 33, probability*alpha);
    SQerror(Error_vector, 34, probability*alpha);
    SQerror(Error_vector, 35, probability*alpha);
    SQerror(Error_vector, 36, probability*alpha);
    SQerror(Error_vector, 37, probability*alpha);
    SQerror(Error_vector, 38, probability*alpha);
    SQerror(Error_vector, 39, probability*alpha);    
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





int parallel_flag(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta){
    
    
    for(int i=0; i<2; i++){
        for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
    }
    



	SQerror(Error_vector, 21, probability);
    SQerror(Error_vector, 22, probability);
    SQerror(Error_vector, 23, probability);
    SQerror(Error_vector, 24, probability);
    SQerror(Error_vector, 25, probability);
    SQerror(Error_vector, 26, probability);
    SQerror(Error_vector, 27, probability);
    SQerror(Error_vector, 28, probability);
    SQerror(Error_vector, 29, probability);  
    SQerror(Error_vector, 41, probability);
    SQerror(Error_vector, 42, probability);
    SQerror(Error_vector, 43, probability);
    SQerror(Error_vector, 44, probability);
    SQerror(Error_vector, 45, probability);
    SQerror(Error_vector, 46, probability);
    SQerror(Error_vector, 47, probability);
    SQerror(Error_vector, 48, probability);
    SQerror(Error_vector, 49, probability);   
    
    SQerror(Error_vector, 31, probability);
    SQerror(Error_vector, 32, probability);
    SQerror(Error_vector, 33, probability);
    SQerror(Error_vector, 34, probability);
    SQerror(Error_vector, 35, probability);
    SQerror(Error_vector, 36, probability);
    SQerror(Error_vector, 37, probability);
    SQerror(Error_vector, 38, probability);
    SQerror(Error_vector, 39, probability);    
    SQerror(Error_vector, 51, probability);
    SQerror(Error_vector, 52, probability);
    SQerror(Error_vector, 53, probability);
    SQerror(Error_vector, 54, probability);
    SQerror(Error_vector, 55, probability);
    SQerror(Error_vector, 56, probability);
    SQerror(Error_vector, 57, probability);
    SQerror(Error_vector, 58, probability);
    SQerror(Error_vector, 59, probability); 
    
	
								
								
//*********************************************************************************************************************************
//*********************************************************************************************************************************						




								//slot.1==========================================================================================
								// g4 Number A ------------------------------------------------------------------
								CNOT(Error_vector, 1, 24);
								TQerror(Error_vector, 1, 24, probability * beta);
							    // g8 NumberA ------------------------------------------------------------------
								CNOT(Error_vector, 8, 28);
								TQerror(Error_vector, 8, 28, probability * beta);
								// g9 NumberA ------------------------------------------------------------------
								CNOT(Error_vector, 5, 29);
								TQerror(Error_vector, 5, 29, probability * beta);

								//SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								//SQerror(Error_vector, 5, probability*gamma);
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
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								


								
								//slot.2==========================================================================================
								
								
								// g1 Number A ------------------------------------------------------------------
								CNOT(Error_vector, 1, 21);
								TQerror(Error_vector, 1, 21, probability * beta);	
								
								// g4 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 41, 24);
								TQerror(Error_vector, 41, 24, probability * beta);
								
								// g5 Number B->A ------------------------------------------------------------------
								CNOT(Error_vector, 9, 25);
								TQerror(Error_vector, 9, 25, probability * beta);
								
								// g8 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 44, 28);
								TQerror(Error_vector, 44, 28, probability * beta);
								
								// g9 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 45, 29);
								TQerror(Error_vector, 45, 29, probability * beta);


								//SQerror(Error_vector, 1, probability*gamma);
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
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								





								//slot.3==========================================================================================

								// g1 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 41, 21);
								TQerror(Error_vector, 41, 21, probability * beta);
								// g3 Number A ------------------------------------------------------------------
								CNOT(Error_vector, 12, 23);
								TQerror(Error_vector, 12, 23, probability * beta);
								// g4 Number B ------------------------------------------------------------------
								CNOT(Error_vector, 2, 24);
								TQerror(Error_vector, 2, 24, probability * beta);
								// g5 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 47, 25);
								TQerror(Error_vector, 47, 25, probability * beta);
								// g8 NumberB ------------------------------------------------------------------
								CNOT(Error_vector, 9, 28);
								TQerror(Error_vector, 9, 28, probability * beta);
								// g9 NumberB ------------------------------------------------------------------
								CNOT(Error_vector, 7, 29);
								TQerror(Error_vector, 7, 29, probability * beta);


								SQerror(Error_vector, 1, probability*gamma);
								//SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								//SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								//SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								SQerror(Error_vector, 11, probability*gamma);
								//SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

								SQerror(Error_vector, 44, probability*gamma);
								SQerror(Error_vector, 45, probability*gamma);


								
								//slot.4==========================================================================================

								// g1 Number B ------------------------------------------------------------------
								CNOT(Error_vector, 2, 21);
								TQerror(Error_vector, 2, 21, probability * beta);
								
								// g3 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 45, 23);
								TQerror(Error_vector, 45, 23, probability * beta);							
								// g4 flag 2 ------------------------------------------------------------------
								CNOT(Error_vector, 42, 24);
								TQerror(Error_vector, 42, 24, probability * beta);
							    // g5 Number A->B ------------------------------------------------------------------
								CNOT(Error_vector, 6, 25);
								TQerror(Error_vector, 6, 25, probability * beta);
								// g6 Number A ------------------------------------------------------------------
								CNOT(Error_vector, 16, 26);
								TQerror(Error_vector, 16, 26, probability * beta);
								// g7 NumberA ------------------------------------------------------------------
								CNOT(Error_vector, 10, 27);
								TQerror(Error_vector, 10, 27, probability * beta);
								// g8 flag 2 ------------------------------------------------------------------
								CNOT(Error_vector, 48, 28);
								TQerror(Error_vector, 48, 28, probability * beta);
								// g9 flag 2 ------------------------------------------------------------------
								CNOT(Error_vector, 46, 29);
								TQerror(Error_vector, 46, 29, probability * beta);

								
								SQerror(Error_vector, 1, probability*gamma);
								//SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								//SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								//SQerror(Error_vector, 10, probability*gamma);
								SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								//SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

								SQerror(Error_vector, 41, probability*gamma);
								SQerror(Error_vector, 44, probability*gamma);
								SQerror(Error_vector, 47, probability*gamma);

								
								//slot.5==========================================================================================


								// g1 Number C ------------------------------------------------------------------
								CNOT(Error_vector, 3, 21);
								TQerror(Error_vector, 3, 21, probability * beta);
								// g2 Number A ------------------------------------------------------------------
								CNOT(Error_vector, 1, 22);
								TQerror(Error_vector, 1, 22, probability * beta);
								// g3 Number B ------------------------------------------------------------------
								CNOT(Error_vector, 13, 23);
								TQerror(Error_vector, 13, 23, probability * beta);
								// g4 Number C ------------------------------------------------------------------
								CNOT(Error_vector, 5, 24);
								TQerror(Error_vector, 5, 24, probability * beta);
								// g5 Number C ------------------------------------------------------------------
								CNOT(Error_vector, 16, 25);
								TQerror(Error_vector, 16, 25, probability * beta);
								// g6 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 47, 26);
								TQerror(Error_vector, 47, 26, probability * beta);
								// g8 NumberD ------------------------------------------------------------------
								CNOT(Error_vector, 11, 28);
								TQerror(Error_vector, 11, 28, probability * beta);
								// g9 NumberC ------------------------------------------------------------------
								CNOT(Error_vector, 8, 29);
								TQerror(Error_vector, 8, 29, probability * beta);

								//SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								//SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								//SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								//SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								//SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								//SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								//SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								
								SQerror(Error_vector, 27, probability*gamma);
								SQerror(Error_vector, 41, probability*gamma);
								SQerror(Error_vector, 42, probability*gamma);
								//SQerror(Error_vector, 43, probability*gamma);
								SQerror(Error_vector, 44, probability*gamma);
								SQerror(Error_vector, 45, probability*gamma);
								SQerror(Error_vector, 46, probability*gamma);
								//SQerror(Error_vector, 47, probability*gamma);
								SQerror(Error_vector, 48, probability*gamma);
								//SQerror(Error_vector, 49, probability*gamma);
	
								
								//slot.6==========================================================================================

								// g1 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 41, 21);
								TQerror(Error_vector, 41, 21, probability * beta);
								// g2 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 43, 22);
								TQerror(Error_vector, 43, 22, probability * beta);
								// g3 Number C ------------------------------------------------------------------
								CNOT(Error_vector, 14, 23);
								TQerror(Error_vector, 14, 23, probability * beta);
								// g4 Number D ------------------------------------------------------------------
								CNOT(Error_vector, 6, 24);	
								TQerror(Error_vector, 6, 24, probability * beta);
								// g5 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 47, 25);
								TQerror(Error_vector, 47, 25, probability * beta);
								// g6 Number D->C ------------------------------------------------------------------
								CNOT(Error_vector, 19, 26);
								TQerror(Error_vector, 19, 26, probability * beta);
								// g7 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 49, 27);
								TQerror(Error_vector, 49, 27, probability * beta);		
								// g8 NumberC ------------------------------------------------------------------
								CNOT(Error_vector, 10, 28);
								TQerror(Error_vector, 10, 28, probability * beta);
								// g9 NumberD ------------------------------------------------------------------
								CNOT(Error_vector, 11, 29);
								TQerror(Error_vector, 11, 29, probability * beta);
	
	
								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								//SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								//SQerror(Error_vector, 10, probability*gamma);
								//SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								//SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								//SQerror(Error_vector, 19, probability*gamma);
								

								//SQerror(Error_vector, 41, probability*gamma);
								SQerror(Error_vector, 42, probability*gamma);
								//SQerror(Error_vector, 43, probability*gamma);
								SQerror(Error_vector, 44, probability*gamma);
								SQerror(Error_vector, 45, probability*gamma);
								SQerror(Error_vector, 46, probability*gamma);
								//SQerror(Error_vector, 47, probability*gamma);
								SQerror(Error_vector, 48, probability*gamma);
								//SQerror(Error_vector, 49, probability*gamma);

								
								
								//slot.7==========================================================================================

								// g1 Number D ------------------------------------------------------------------
								CNOT(Error_vector, 4, 21);	
								TQerror(Error_vector, 4, 21, probability * beta);
								// g2 Number B ------------------------------------------------------------------
								CNOT(Error_vector, 3, 22);
								TQerror(Error_vector, 3, 22, probability * beta);
								// g3 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 45, 23);
								TQerror(Error_vector, 45, 23, probability * beta);						
								// g4 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 41, 24);
								TQerror(Error_vector, 41, 24, probability * beta);
								// g5 Number D ------------------------------------------------------------------
								CNOT(Error_vector, 19, 25);	
								TQerror(Error_vector, 19, 25, probability * beta);
								// g6 Number B ------------------------------------------------------------------
								CNOT(Error_vector, 17, 26);
								TQerror(Error_vector, 17, 26, probability * beta);	
								// g7 NumberC ------------------------------------------------------------------
								CNOT(Error_vector, 12, 27);
								TQerror(Error_vector, 12, 27, probability * beta);
								// g8 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 44, 28);
								TQerror(Error_vector, 44, 28, probability * beta);	
								// g9 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 45, 29);
								TQerror(Error_vector, 45, 29, probability * beta);


								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								//SQerror(Error_vector, 3, probability*gamma);
								//SQerror(Error_vector, 4, probability*gamma);
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
								//SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								//SQerror(Error_vector, 19, probability*gamma);
								

								//SQerror(Error_vector, 41, probability*gamma);
								SQerror(Error_vector, 42, probability*gamma);
								SQerror(Error_vector, 43, probability*gamma);
								//SQerror(Error_vector, 44, probability*gamma);
								//SQerror(Error_vector, 45, probability*gamma);
								SQerror(Error_vector, 46, probability*gamma);
								SQerror(Error_vector, 47, probability*gamma);
								SQerror(Error_vector, 48, probability*gamma);
								SQerror(Error_vector, 49, probability*gamma);

								
								//slot.8==========================================================================================
	
								// g2 Number C ------------------------------------------------------------------
								CNOT(Error_vector, 5, 22);
								TQerror(Error_vector, 5, 22, probability * beta);
								// g3 Number D ------------------------------------------------------------------
								CNOT(Error_vector, 15, 23);	
								TQerror(Error_vector, 15, 23, probability * beta);
								// g4 Number E ------------------------------------------------------------------
								CNOT(Error_vector, 8, 24);
								TQerror(Error_vector, 8, 24, probability * beta);
								// g6 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 47, 26);
								TQerror(Error_vector, 47, 26, probability * beta);
								// g7 NumberB ------------------------------------------------------------------
								CNOT(Error_vector, 11, 27);
								TQerror(Error_vector, 11, 27, probability * beta);
								// g8 NumberE ------------------------------------------------------------------
							 	CNOT(Error_vector, 16, 28);
							 	TQerror(Error_vector, 16, 28, probability * beta);	
								// g9 NumberE ------------------------------------------------------------------
							 	CNOT(Error_vector, 12, 29);
							 	TQerror(Error_vector, 12, 29 , probability * beta);

								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								//SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								//SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								//SQerror(Error_vector, 11, probability*gamma);
								//SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								//SQerror(Error_vector, 15, probability*gamma);
								//SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

								//SQerror(Error_vector, 41, probability*gamma);
								SQerror(Error_vector, 42, probability*gamma);
								SQerror(Error_vector, 43, probability*gamma);
								//SQerror(Error_vector, 44, probability*gamma);
								//SQerror(Error_vector, 45, probability*gamma);
								SQerror(Error_vector, 46, probability*gamma);
								//SQerror(Error_vector, 47, probability*gamma);
								SQerror(Error_vector, 48, probability*gamma);
								SQerror(Error_vector, 49, probability*gamma);

								
								//slot.9==========================================================================================							
								
								
								// g2 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 43, 22);
								TQerror(Error_vector, 43, 22, probability * beta);
								// g4 flag 2 ------------------------------------------------------------------
								CNOT(Error_vector, 42, 24);
								TQerror(Error_vector, 42, 24, probability * beta);
								// g7 flag 1 ------------------------------------------------------------------
								CNOT(Error_vector, 49, 27);
								TQerror(Error_vector, 49, 27, probability * beta);	
							 	// g8 flag 2 ------------------------------------------------------------------
							 	CNOT(Error_vector, 48, 28);
							 	TQerror(Error_vector, 48, 28, probability * beta);
							 	// g9 flag 2 ------------------------------------------------------------------
							 	CNOT(Error_vector, 46, 29);
							 	TQerror(Error_vector, 46, 29, probability * beta);

									
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
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

									
								
								//slot.10==========================================================================================									
								
								
								// g2 Number D ------------------------------------------------------------------
								CNOT(Error_vector, 7, 22);	
								TQerror(Error_vector, 7, 22, probability * beta);
								// g4 Number F ------------------------------------------------------------------
								CNOT(Error_vector, 9, 24);	
								TQerror(Error_vector, 9, 24, probability * beta);
								// g6 Number C->D ------------------------------------------------------------------						
								CNOT(Error_vector, 18, 26);
								TQerror(Error_vector, 18, 26, probability * beta);
								// g7 NumberD ------------------------------------------------------------------
								CNOT(Error_vector, 15, 27);
								TQerror(Error_vector, 15, 27, probability * beta);			
							 	// g8 NumberF ------------------------------------------------------------------
								CNOT(Error_vector, 17, 28);
								TQerror(Error_vector, 17, 28, probability * beta);
							 	// g9 NumberF ------------------------------------------------------------------
								CNOT(Error_vector, 13, 29);	
								TQerror(Error_vector, 13, 29, probability * beta);			      

								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								//SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								//SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								//SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								//SQerror(Error_vector, 15, probability*gamma);
								SQerror(Error_vector, 16, probability*gamma);
								//SQerror(Error_vector, 17, probability*gamma);
								//SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
    
    
    
	//==========================================================================================================================
	//==========================================================================================================================
	//==========================================================================================================================
    


								//slot.1==========================================================================================
								// g4 Number A ------------------------------------------------------------------
								CNOT_rev(Error_vector, 1, 34);
								TQerror(Error_vector, 1, 34, probability * beta);
							    // g8 NumberA ------------------------------------------------------------------
								CNOT_rev(Error_vector, 8, 38);
								TQerror(Error_vector, 8, 38, probability * beta);
								// g9 NumberA ------------------------------------------------------------------
								CNOT_rev(Error_vector, 5, 39);
								TQerror(Error_vector, 5, 39, probability * beta);

								//SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								//SQerror(Error_vector, 5, probability*gamma);
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
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								


								
								//slot.2==========================================================================================
								
								
								// g1 Number A ------------------------------------------------------------------
								CNOT_rev(Error_vector, 1, 31);
								TQerror(Error_vector, 1, 31, probability * beta);	
								
								// g4 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 51, 34);
								TQerror(Error_vector, 51, 34, probability * beta);
								
								// g5 Number B->A ------------------------------------------------------------------
								CNOT_rev(Error_vector, 9, 35);
								TQerror(Error_vector, 9, 35, probability * beta);
								
								// g8 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 54, 38);
								TQerror(Error_vector, 54, 38, probability * beta);
								
								// g9 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 55, 39);
								TQerror(Error_vector, 55, 39, probability * beta);


								//SQerror(Error_vector, 1, probability*gamma);
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
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								





								//slot.3==========================================================================================

								// g1 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 51, 31);
								TQerror(Error_vector, 51, 31, probability * beta);
								// g3 Number A ------------------------------------------------------------------
								CNOT_rev(Error_vector, 12, 33);
								TQerror(Error_vector, 12, 33, probability * beta);
								// g4 Number B ------------------------------------------------------------------
								CNOT_rev(Error_vector, 2, 34);
								TQerror(Error_vector, 2, 34, probability * beta);
								// g5 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 57, 35);
								TQerror(Error_vector, 57, 35, probability * beta);
								// g8 NumberB ------------------------------------------------------------------
								CNOT_rev(Error_vector, 9, 38);
								TQerror(Error_vector, 9, 38, probability * beta);
								// g9 NumberB ------------------------------------------------------------------
								CNOT_rev(Error_vector, 7, 39);
								TQerror(Error_vector, 7, 39, probability * beta);


								SQerror(Error_vector, 1, probability*gamma);
								//SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								//SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								//SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								SQerror(Error_vector, 11, probability*gamma);
								//SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

								SQerror(Error_vector, 54, probability*gamma);
								SQerror(Error_vector, 55, probability*gamma);


								
								//slot.4==========================================================================================

								// g1 Number B ------------------------------------------------------------------
								CNOT_rev(Error_vector, 2, 31);
								TQerror(Error_vector, 2, 31, probability * beta);
								
								// g3 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 55, 33);
								TQerror(Error_vector, 55, 33, probability * beta);							
								// g4 flag 2 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 52, 34);
								TQerror(Error_vector, 52, 34, probability * beta);
							    // g5 Number A->B ------------------------------------------------------------------
								CNOT_rev(Error_vector, 6, 35);
								TQerror(Error_vector, 6, 35, probability * beta);
								// g6 Number A ------------------------------------------------------------------
								CNOT_rev(Error_vector, 16, 36);
								TQerror(Error_vector, 16, 36, probability * beta);
								// g7 NumberA ------------------------------------------------------------------
								CNOT_rev(Error_vector, 10, 37);
								TQerror(Error_vector, 10, 37, probability * beta);
								// g8 flag 2 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 58, 38);
								TQerror(Error_vector, 58, 38, probability * beta);
								// g9 flag 2 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 56, 39);
								TQerror(Error_vector, 56, 39, probability * beta);

								
								SQerror(Error_vector, 1, probability*gamma);
								//SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								//SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								//SQerror(Error_vector, 10, probability*gamma);
								SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								//SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

								SQerror(Error_vector, 51, probability*gamma);
								SQerror(Error_vector, 54, probability*gamma);
								SQerror(Error_vector, 57, probability*gamma);

								
								//slot.5==========================================================================================


								// g1 Number C ------------------------------------------------------------------
								CNOT_rev(Error_vector, 3, 31);
								TQerror(Error_vector, 3, 31, probability * beta);
								// g2 Number A ------------------------------------------------------------------
								CNOT_rev(Error_vector, 1, 32);
								TQerror(Error_vector, 1, 32, probability * beta);
								// g3 Number B ------------------------------------------------------------------
								CNOT_rev(Error_vector, 13, 33);
								TQerror(Error_vector, 13, 33, probability * beta);
								// g4 Number C ------------------------------------------------------------------
								CNOT_rev(Error_vector, 5, 34);
								TQerror(Error_vector, 5, 34, probability * beta);
								// g5 Number C ------------------------------------------------------------------
								CNOT_rev(Error_vector, 16, 35);
								TQerror(Error_vector, 16, 35, probability * beta);
								// g6 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 57, 36);
								TQerror(Error_vector, 57, 36, probability * beta);
								// g8 NumberD ------------------------------------------------------------------
								CNOT_rev(Error_vector, 11, 38);
								TQerror(Error_vector, 11, 38, probability * beta);
								// g9 NumberC ------------------------------------------------------------------
								CNOT_rev(Error_vector, 8, 39);
								TQerror(Error_vector, 8, 39, probability * beta);

								//SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								//SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								//SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								//SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								//SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								//SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								//SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								
								SQerror(Error_vector, 37, probability*gamma);
								SQerror(Error_vector, 51, probability*gamma);
								SQerror(Error_vector, 52, probability*gamma);
								//SQerror(Error_vector, 53, probability*gamma);
								SQerror(Error_vector, 54, probability*gamma);
								SQerror(Error_vector, 55, probability*gamma);
								SQerror(Error_vector, 56, probability*gamma);
								//SQerror(Error_vector, 57, probability*gamma);
								SQerror(Error_vector, 58, probability*gamma);
								//SQerror(Error_vector, 59, probability*gamma);
	
								
								//slot.6==========================================================================================

								// g1 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 51, 31);
								TQerror(Error_vector, 51, 31, probability * beta);
								// g2 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 53, 32);
								TQerror(Error_vector, 53, 32, probability * beta);
								// g3 Number C ------------------------------------------------------------------
								CNOT_rev(Error_vector, 14, 33);
								TQerror(Error_vector, 14, 33, probability * beta);
								// g4 Number D ------------------------------------------------------------------
								CNOT_rev(Error_vector, 6, 34);	
								TQerror(Error_vector, 6, 34, probability * beta);
								// g5 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 57, 35);
								TQerror(Error_vector, 57, 35, probability * beta);
								// g6 Number D->C ------------------------------------------------------------------
								CNOT_rev(Error_vector, 19, 36);
								TQerror(Error_vector, 19, 36, probability * beta);
								// g7 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 59, 37);
								TQerror(Error_vector, 59, 37, probability * beta);		
								// g8 NumberC ------------------------------------------------------------------
								CNOT_rev(Error_vector, 10, 38);
								TQerror(Error_vector, 10, 38, probability * beta);
								// g9 NumberD ------------------------------------------------------------------
								CNOT_rev(Error_vector, 11, 39);
								TQerror(Error_vector, 11, 39, probability * beta);
	
	
								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								//SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								//SQerror(Error_vector, 10, probability*gamma);
								//SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								//SQerror(Error_vector, 14, probability*gamma);
								SQerror(Error_vector, 15, probability*gamma);
								SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								//SQerror(Error_vector, 19, probability*gamma);
								

								//SQerror(Error_vector, 51, probability*gamma);
								SQerror(Error_vector, 52, probability*gamma);
								//SQerror(Error_vector, 53, probability*gamma);
								SQerror(Error_vector, 54, probability*gamma);
								SQerror(Error_vector, 55, probability*gamma);
								SQerror(Error_vector, 56, probability*gamma);
								//SQerror(Error_vector, 57, probability*gamma);
								SQerror(Error_vector, 58, probability*gamma);
								//SQerror(Error_vector, 59, probability*gamma);

								
								
								//slot.7==========================================================================================

								// g1 Number D ------------------------------------------------------------------
								CNOT_rev(Error_vector, 4, 31);	
								TQerror(Error_vector, 4, 31, probability * beta);
								// g2 Number B ------------------------------------------------------------------
								CNOT_rev(Error_vector, 3, 32);
								TQerror(Error_vector, 3, 32, probability * beta);
								// g3 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 55, 33);
								TQerror(Error_vector, 55, 33, probability * beta);						
								// g4 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 51, 34);
								TQerror(Error_vector, 51, 34, probability * beta);
								// g5 Number D ------------------------------------------------------------------
								CNOT_rev(Error_vector, 19, 35);	
								TQerror(Error_vector, 19, 35, probability * beta);
								// g6 Number B ------------------------------------------------------------------
								CNOT_rev(Error_vector, 17, 36);
								TQerror(Error_vector, 17, 36, probability * beta);	
								// g7 NumberC ------------------------------------------------------------------
								CNOT_rev(Error_vector, 12, 37);
								TQerror(Error_vector, 12, 37, probability * beta);
								// g8 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 54, 38);
								TQerror(Error_vector, 54, 38, probability * beta);	
								// g9 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 55, 39);
								TQerror(Error_vector, 55, 39, probability * beta);


								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								//SQerror(Error_vector, 3, probability*gamma);
								//SQerror(Error_vector, 4, probability*gamma);
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
								//SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								//SQerror(Error_vector, 19, probability*gamma);
								

								//SQerror(Error_vector, 51, probability*gamma);
								SQerror(Error_vector, 52, probability*gamma);
								SQerror(Error_vector, 53, probability*gamma);
								//SQerror(Error_vector, 54, probability*gamma);
								//SQerror(Error_vector, 55, probability*gamma);
								SQerror(Error_vector, 56, probability*gamma);
								SQerror(Error_vector, 57, probability*gamma);
								SQerror(Error_vector, 58, probability*gamma);
								SQerror(Error_vector, 59, probability*gamma);

								
								//slot.8==========================================================================================
	
								// g2 Number C ------------------------------------------------------------------
								CNOT_rev(Error_vector, 5, 32);
								TQerror(Error_vector, 5, 32, probability * beta);
								// g3 Number D ------------------------------------------------------------------
								CNOT_rev(Error_vector, 15, 33);	
								TQerror(Error_vector, 15, 33, probability * beta);
								// g4 Number E ------------------------------------------------------------------
								CNOT_rev(Error_vector, 8, 34);
								TQerror(Error_vector, 8, 34, probability * beta);
								// g6 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 57, 36);
								TQerror(Error_vector, 57, 36, probability * beta);
								// g7 NumberB ------------------------------------------------------------------
								CNOT_rev(Error_vector, 11, 37);
								TQerror(Error_vector, 11, 37, probability * beta);
								// g8 NumberE ------------------------------------------------------------------
							 	CNOT_rev(Error_vector, 16, 38);
							 	TQerror(Error_vector, 16, 38, probability * beta);	
								// g9 NumberE ------------------------------------------------------------------
							 	CNOT_rev(Error_vector, 12, 39);
							 	TQerror(Error_vector, 12, 39 , probability * beta);

								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								//SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								SQerror(Error_vector, 7, probability*gamma);
								//SQerror(Error_vector, 8, probability*gamma);
								SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								//SQerror(Error_vector, 11, probability*gamma);
								//SQerror(Error_vector, 12, probability*gamma);
								SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								//SQerror(Error_vector, 15, probability*gamma);
								//SQerror(Error_vector, 16, probability*gamma);
								SQerror(Error_vector, 17, probability*gamma);
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

								//SQerror(Error_vector, 51, probability*gamma);
								SQerror(Error_vector, 52, probability*gamma);
								SQerror(Error_vector, 53, probability*gamma);
								//SQerror(Error_vector, 54, probability*gamma);
								//SQerror(Error_vector, 55, probability*gamma);
								SQerror(Error_vector, 56, probability*gamma);
								//SQerror(Error_vector, 57, probability*gamma);
								SQerror(Error_vector, 58, probability*gamma);
								SQerror(Error_vector, 59, probability*gamma);

								
								//slot.9==========================================================================================							
								
								
								// g2 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 53, 32);
								TQerror(Error_vector, 53, 32, probability * beta);
								// g4 flag 2 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 52, 34);
								TQerror(Error_vector, 52, 34, probability * beta);
								// g7 flag 1 ------------------------------------------------------------------
								CNOT_rev(Error_vector, 59, 37);
								TQerror(Error_vector, 59, 37, probability * beta);	
							 	// g8 flag 2 ------------------------------------------------------------------
							 	CNOT_rev(Error_vector, 58, 38);
							 	TQerror(Error_vector, 58, 38, probability * beta);
							 	// g9 flag 2 ------------------------------------------------------------------
							 	CNOT_rev(Error_vector, 56, 39);
							 	TQerror(Error_vector, 56, 39, probability * beta);

									
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
								SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);
								

									
								
								//slot.10==========================================================================================									
								
								
								// g2 Number D ------------------------------------------------------------------
								CNOT_rev(Error_vector, 7, 32);	
								TQerror(Error_vector, 7, 32, probability * beta);
								// g4 Number F ------------------------------------------------------------------
								CNOT_rev(Error_vector, 9, 34);	
								TQerror(Error_vector, 9, 34, probability * beta);
								// g6 Number C->D ------------------------------------------------------------------						
								CNOT_rev(Error_vector, 18, 36);
								TQerror(Error_vector, 18, 36, probability * beta);
								// g7 NumberD ------------------------------------------------------------------
								CNOT_rev(Error_vector, 15, 37);
								TQerror(Error_vector, 15, 37, probability * beta);			
							 	// g8 NumberF ------------------------------------------------------------------
								CNOT_rev(Error_vector, 17, 38);
								TQerror(Error_vector, 17, 38, probability * beta);
							 	// g9 NumberF ------------------------------------------------------------------
								CNOT_rev(Error_vector, 13, 39);	
								TQerror(Error_vector, 13, 39, probability * beta);			      

								SQerror(Error_vector, 1, probability*gamma);
								SQerror(Error_vector, 2, probability*gamma);
								SQerror(Error_vector, 3, probability*gamma);
								SQerror(Error_vector, 4, probability*gamma);
								SQerror(Error_vector, 5, probability*gamma);
								SQerror(Error_vector, 6, probability*gamma);
								//SQerror(Error_vector, 7, probability*gamma);
								SQerror(Error_vector, 8, probability*gamma);
								//SQerror(Error_vector, 9, probability*gamma);
								SQerror(Error_vector, 10, probability*gamma);
								SQerror(Error_vector, 11, probability*gamma);
								SQerror(Error_vector, 12, probability*gamma);
								//SQerror(Error_vector, 13, probability*gamma);
								SQerror(Error_vector, 14, probability*gamma);
								//SQerror(Error_vector, 15, probability*gamma);
								SQerror(Error_vector, 16, probability*gamma);
								//SQerror(Error_vector, 17, probability*gamma);
								//SQerror(Error_vector, 18, probability*gamma);
								SQerror(Error_vector, 19, probability*gamma);


					        	
//*********************************************************************************************************************************
//*********************************************************************************************************************************
    
	SQerror(Error_vector, 21, probability*alpha);
    SQerror(Error_vector, 22, probability*alpha);
    SQerror(Error_vector, 23, probability*alpha);
    SQerror(Error_vector, 24, probability*alpha);
    SQerror(Error_vector, 25, probability*alpha);
    SQerror(Error_vector, 26, probability*alpha);
    SQerror(Error_vector, 27, probability*alpha);
    SQerror(Error_vector, 28, probability*alpha);
    SQerror(Error_vector, 29, probability*alpha);  
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
    SQerror(Error_vector, 39, probability*alpha);    
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



int unflagged(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta ){
    
    
    for(int i=0; i<2; i++){
        for(int j=19; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
    }
    
    SQerror(Error_vector, 21, probability*alpha);
    SQerror(Error_vector, 22, probability*alpha);
    SQerror(Error_vector, 23, probability*alpha);
    SQerror(Error_vector, 24, probability*alpha);
    SQerror(Error_vector, 25, probability*alpha);
    SQerror(Error_vector, 26, probability*alpha);
    SQerror(Error_vector, 27, probability*alpha);
    SQerror(Error_vector, 28, probability*alpha);
    SQerror(Error_vector, 29, probability*alpha);
    SQerror(Error_vector, 31, probability*alpha);
    SQerror(Error_vector, 32, probability*alpha);
    SQerror(Error_vector, 33, probability*alpha);
    SQerror(Error_vector, 34, probability*alpha);
    SQerror(Error_vector, 35, probability*alpha);
    SQerror(Error_vector, 36, probability*alpha);
    SQerror(Error_vector, 37, probability*alpha);
    SQerror(Error_vector, 38, probability*alpha);
    SQerror(Error_vector, 39, probability*alpha);
    

//===================================================================================================
   
    //gz1 2================================================================
    CNOT(Error_vector, 2, 21);
    TQerror(Error_vector, 2, 21, probability * beta);   
    //gz2 4================================================================
    CNOT(Error_vector, 7, 22);
    TQerror(Error_vector, 7, 22, probability * beta);
	//gz3 1================================================================
    CNOT(Error_vector, 12, 23);
    TQerror(Error_vector, 12, 23, probability * beta);
    //gz4 1================================================================
    CNOT(Error_vector, 1, 24);
    TQerror(Error_vector, 1, 24, probability * beta);
	//gz5 1================================================================
    CNOT(Error_vector, 6, 25);
    TQerror(Error_vector, 6, 25, probability * beta);
	//gz6 1================================================================
    CNOT(Error_vector, 16, 26);
    TQerror(Error_vector, 16, 26, probability * beta);
	//gz7 1================================================================
    CNOT(Error_vector, 10, 27);
    TQerror(Error_vector, 10, 27, probability * beta);
	//gz8 1================================================================
    CNOT(Error_vector, 8, 28);
    TQerror(Error_vector, 8, 28, probability * beta);
    //gz9 1================================================================
    CNOT(Error_vector, 5, 29);
    TQerror(Error_vector, 5, 29, probability * beta);
	
    //SQerror(Error_vector, 1, probability*gamma);
    //SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    SQerror(Error_vector, 18, probability*gamma);
    SQerror(Error_vector, 19, probability*gamma);
	
	
//===================================================================================================
    

    
    //gz1 1================================================================
    CNOT(Error_vector, 1, 21);
    TQerror(Error_vector, 1, 21, probability * beta);
    //gz2 2================================================================
    CNOT(Error_vector, 3, 22);
    TQerror(Error_vector, 3, 22, probability * beta);
    //gz3 2================================================================
    CNOT(Error_vector, 13, 23);
    TQerror(Error_vector, 13, 23, probability * beta);
    //gz4 3================================================================
    CNOT(Error_vector, 5, 24);
    TQerror(Error_vector, 5, 24, probability * beta);
    //gz5 3================================================================
    CNOT(Error_vector, 16, 25);
    TQerror(Error_vector, 16, 25, probability * beta);
    //gz6 2================================================================
    CNOT(Error_vector, 17, 26);
    TQerror(Error_vector, 17, 26, probability * beta);
    //gz7 2================================================================
    CNOT(Error_vector, 11, 27);
    TQerror(Error_vector, 11, 27, probability * beta);
    //gz8 2================================================================
    CNOT(Error_vector, 9, 28);
    TQerror(Error_vector, 9, 28, probability * beta);
    //gz9 2================================================================
    CNOT(Error_vector, 7, 29);
    TQerror(Error_vector, 7, 29, probability * beta);
	
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
    //SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    //SQerror(Error_vector, 17, probability*gamma);
    SQerror(Error_vector, 18, probability*gamma);
    SQerror(Error_vector, 19, probability*gamma);
	
//===================================================================================================
     
    //gz1 3================================================================
    CNOT(Error_vector, 3, 21);
    TQerror(Error_vector, 3, 21, probability * beta);
    //gz2 3================================================================
    CNOT(Error_vector, 5, 22);
    TQerror(Error_vector, 5, 22, probability * beta);
    //gz3 4================================================================
    CNOT(Error_vector, 15, 23);
    TQerror(Error_vector, 15, 23, probability * beta);
    //gz4 2================================================================
    CNOT(Error_vector, 2, 24);
    TQerror(Error_vector, 2, 24, probability * beta);
    //gz5 2================================================================
    CNOT(Error_vector, 9, 25);
    TQerror(Error_vector, 9, 25, probability * beta);
    //gz6 4================================================================
    CNOT(Error_vector, 19, 26);
    TQerror(Error_vector, 19, 26, probability * beta);
    //gz7 3================================================================
    CNOT(Error_vector, 12, 27);
    TQerror(Error_vector, 12, 27, probability * beta);
    //gz8 3================================================================
    CNOT(Error_vector, 10, 28);
    TQerror(Error_vector, 10, 28, probability * beta);
    //gz9 3================================================================
    CNOT(Error_vector, 8, 29);
    TQerror(Error_vector, 8, 29, probability * beta);

    SQerror(Error_vector, 1, probability*gamma);
    //SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    SQerror(Error_vector, 18, probability*gamma);
    //SQerror(Error_vector, 19, probability*gamma);
	
//===================================================================================================
 
    //gz1 4================================================================
    CNOT(Error_vector, 4, 21);
    TQerror(Error_vector, 4, 21, probability * beta);
	//gz2 1================================================================
    CNOT(Error_vector, 1, 22);
    TQerror(Error_vector, 1, 22, probability * beta);
    //gz3 3================================================================
    CNOT(Error_vector, 14, 23);
    TQerror(Error_vector, 14, 23, probability * beta);
    //gz4 4================================================================
    CNOT(Error_vector, 6, 24);
    TQerror(Error_vector, 6, 24, probability * beta);
    //gz5 4================================================================
    CNOT(Error_vector, 19, 25);
    TQerror(Error_vector, 19, 25, probability * beta);
    //gz6 3================================================================
    CNOT(Error_vector, 18, 26);
    TQerror(Error_vector, 18, 26, probability * beta);
    //gz7 4================================================================
    CNOT(Error_vector, 15, 27);
    TQerror(Error_vector, 15, 27, probability * beta);
    //gz8 4================================================================
    CNOT(Error_vector, 11, 28);
    TQerror(Error_vector, 11, 28, probability * beta);
    //gz9 5================================================================
    CNOT(Error_vector, 12, 29);
    TQerror(Error_vector, 12, 29, probability * beta);

    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    //SQerror(Error_vector, 18, probability*gamma);
    //SQerror(Error_vector, 19, probability*gamma);
	
//===================================================================================================
 
    //gz4 5================================================================
    CNOT(Error_vector, 8, 24);
    TQerror(Error_vector, 8, 24, probability * beta);
    //gz8 5================================================================
    CNOT(Error_vector, 16, 28);
    TQerror(Error_vector, 16, 28, probability * beta);
    //gz9 4================================================================
    CNOT(Error_vector, 11, 29);
    TQerror(Error_vector, 11, 29, probability * beta);    
    
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
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    SQerror(Error_vector, 18, probability*gamma);
    SQerror(Error_vector, 19, probability*gamma);
	
//===================================================================================================
 
    //gz4 6================================================================
    CNOT(Error_vector, 9, 24);
    TQerror(Error_vector, 9, 24, probability * beta);
    //gz8 6================================================================
    CNOT(Error_vector, 17, 28);
    TQerror(Error_vector, 17, 28, probability * beta);
	    
    //gz9 6================================================================
    CNOT(Error_vector, 13, 29);
    TQerror(Error_vector, 13, 29, probability * beta);
	
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
    //SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    //SQerror(Error_vector, 17, probability*gamma);
    SQerror(Error_vector, 18, probability*gamma);
    SQerror(Error_vector, 19, probability*gamma);
	
//===================================================================================================  
    
	

//===================================================================================================
   
  
    //gx1 2================================================================
    CNOT(Error_vector, 31, 2);
    TQerror(Error_vector, 31, 2, probability * beta);
    //gx2 4================================================================
    CNOT(Error_vector, 32, 7);
    TQerror(Error_vector, 32, 7, probability * beta);
	//gx3 1================================================================
    CNOT(Error_vector, 33, 12);
    TQerror(Error_vector, 33, 12, probability * beta);
	//gx4 1================================================================
    CNOT(Error_vector, 34, 1);
    TQerror(Error_vector, 34, 1, probability * beta);
	//gx5 1================================================================
    CNOT(Error_vector, 35, 6);
    TQerror(Error_vector, 35, 6, probability * beta);
	//gx6 1================================================================
    CNOT(Error_vector, 36, 16);
    TQerror(Error_vector, 36, 16, probability * beta);
	//gx7 1================================================================
    CNOT(Error_vector, 37, 10);
    TQerror(Error_vector, 37, 10, probability * beta);
	//gx8 1================================================================
    CNOT(Error_vector, 38, 8);
    TQerror(Error_vector, 38, 8, probability * beta);
    //gx9 1================================================================
    CNOT(Error_vector, 39, 5);
    TQerror(Error_vector, 39, 5, probability * beta);

    //SQerror(Error_vector, 1, probability*gamma);
    //SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    //SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    SQerror(Error_vector, 18, probability*gamma);
    SQerror(Error_vector, 19, probability*gamma);
//===================================================================================================
    
	//gx1 1================================================================
    CNOT(Error_vector, 31, 1);
    TQerror(Error_vector, 31, 1, probability * beta);
    //gx2 2================================================================
    CNOT(Error_vector, 32, 3);
    TQerror(Error_vector, 32, 3, probability * beta);
    //gx3 2================================================================
    CNOT(Error_vector, 33, 13);
    TQerror(Error_vector, 33, 13, probability * beta);
    //gx4 3================================================================
    CNOT(Error_vector, 34, 5);
    TQerror(Error_vector, 34, 5, probability * beta);
    //gx5 3================================================================
    CNOT(Error_vector, 35, 16);
    TQerror(Error_vector, 35, 16, probability * beta);
    //gx6 2================================================================
    CNOT(Error_vector, 36, 17);
    TQerror(Error_vector, 36, 17, probability * beta);
    //gx7 2================================================================
    CNOT(Error_vector, 37, 11);
    TQerror(Error_vector, 37, 11, probability * beta);
    //gx8 2================================================================
    CNOT(Error_vector, 38, 9);
    TQerror(Error_vector, 38, 9, probability * beta);
    //gx9 2================================================================
    CNOT(Error_vector, 39, 7);
    TQerror(Error_vector, 39, 7, probability * beta);
	
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
    //SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    //SQerror(Error_vector, 17, probability*gamma);
    SQerror(Error_vector, 18, probability*gamma);
    SQerror(Error_vector, 19, probability*gamma);
	
//===================================================================================================
    
	
    //gx1 3================================================================
    CNOT(Error_vector, 31, 3);
    TQerror(Error_vector, 31, 3, probability * beta);
    //gx2 3================================================================
    CNOT(Error_vector, 32, 5);
    TQerror(Error_vector, 32, 5, probability * beta);
    //gx3 4================================================================
    CNOT(Error_vector, 33, 15);
    TQerror(Error_vector, 33, 15, probability * beta);
    //gx4 2================================================================
    CNOT(Error_vector, 34, 2);
    TQerror(Error_vector, 34, 2, probability * beta);
    //gx5 2================================================================
    CNOT(Error_vector, 35, 9);
    TQerror(Error_vector, 35, 9, probability * beta);
	//gx6 4================================================================
    CNOT(Error_vector, 36, 19);
    TQerror(Error_vector, 36, 19, probability * beta);
    //gx7 3================================================================
    CNOT(Error_vector, 37, 12);
    TQerror(Error_vector, 37, 12, probability * beta);
    //gx8 3================================================================
    CNOT(Error_vector, 38, 10);
    TQerror(Error_vector, 38, 10, probability * beta);
    //gx9 3================================================================
    CNOT(Error_vector, 39, 8);
    TQerror(Error_vector, 39, 8, probability * beta);
	
    SQerror(Error_vector, 1, probability*gamma);
    //SQerror(Error_vector, 2, probability*gamma);
    //SQerror(Error_vector, 3, probability*gamma);
    SQerror(Error_vector, 4, probability*gamma);
    //SQerror(Error_vector, 5, probability*gamma);
    SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    //SQerror(Error_vector, 8, probability*gamma);
    //SQerror(Error_vector, 9, probability*gamma);
    //SQerror(Error_vector, 10, probability*gamma);
    SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    SQerror(Error_vector, 18, probability*gamma);
    //SQerror(Error_vector, 19, probability*gamma);
	
//===================================================================================================
    
	
    
    //gx1 4================================================================
    CNOT(Error_vector, 31, 4);
    TQerror(Error_vector, 31, 4, probability * beta);
	//gx2 1================================================================
    CNOT(Error_vector, 32, 1);
    TQerror(Error_vector, 32, 1, probability * beta);
    //gx3 3================================================================
    CNOT(Error_vector, 33, 14);
    TQerror(Error_vector, 33, 14, probability * beta);    
	//gx4 4================================================================
    CNOT(Error_vector, 34, 6);
    TQerror(Error_vector, 34, 6, probability * beta);
    //gx5 4================================================================
    CNOT(Error_vector, 35, 19);
    TQerror(Error_vector, 35, 19, probability * beta);
    //gx6 3================================================================
    CNOT(Error_vector, 36, 18);
    TQerror(Error_vector, 36, 18, probability * beta);
    //gx7 4================================================================
    CNOT(Error_vector, 37, 15);
    TQerror(Error_vector, 37, 15, probability * beta);
    //gx8 4================================================================
    CNOT(Error_vector, 38, 11);
    TQerror(Error_vector, 38, 11, probability * beta);
    //gx9 5================================================================
    CNOT(Error_vector, 39, 12);
    TQerror(Error_vector, 39, 12, probability * beta);
	
    //SQerror(Error_vector, 1, probability*gamma);
    SQerror(Error_vector, 2, probability*gamma);
    SQerror(Error_vector, 3, probability*gamma);
    //SQerror(Error_vector, 4, probability*gamma);
    SQerror(Error_vector, 5, probability*gamma);
    //SQerror(Error_vector, 6, probability*gamma);
    SQerror(Error_vector, 7, probability*gamma);
    SQerror(Error_vector, 8, probability*gamma);
    SQerror(Error_vector, 9, probability*gamma);
    SQerror(Error_vector, 10, probability*gamma);
    //SQerror(Error_vector, 11, probability*gamma);
    //SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    //SQerror(Error_vector, 14, probability*gamma);
    //SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    //SQerror(Error_vector, 18, probability*gamma);
    //SQerror(Error_vector, 19, probability*gamma);
//===================================================================================================
   
 
    //gx4 5================================================================
    CNOT(Error_vector, 34, 8);
    TQerror(Error_vector, 34, 8, probability * beta);
    //gx8 5================================================================
    CNOT(Error_vector, 38, 16);
    TQerror(Error_vector, 38, 16, probability * beta);
    //gx9 4================================================================
    CNOT(Error_vector, 39, 11);
    TQerror(Error_vector, 39, 11, probability * beta);

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
    //SQerror(Error_vector, 11, probability*gamma);
    SQerror(Error_vector, 12, probability*gamma);
    SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    //SQerror(Error_vector, 16, probability*gamma);
    SQerror(Error_vector, 17, probability*gamma);
    SQerror(Error_vector, 18, probability*gamma);
    SQerror(Error_vector, 19, probability*gamma);
	
//===================================================================================================
   
    //gx4 6================================================================
    CNOT(Error_vector, 34, 9);
    TQerror(Error_vector, 34, 9, probability * beta);
    //gx8 6================================================================
    CNOT(Error_vector, 38, 17);
    TQerror(Error_vector, 38, 17, probability * beta);
    //gx9 6================================================================
    CNOT(Error_vector, 39, 13);
    TQerror(Error_vector, 39, 13, probability * beta);
	
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
    //SQerror(Error_vector, 13, probability*gamma);
    SQerror(Error_vector, 14, probability*gamma);
    SQerror(Error_vector, 15, probability*gamma);
    SQerror(Error_vector, 16, probability*gamma);
    //SQerror(Error_vector, 17, probability*gamma);
    SQerror(Error_vector, 18, probability*gamma);
    SQerror(Error_vector, 19, probability*gamma);
	
//===================================================================================================
    
  




   



    
    
    SQerror(Error_vector, 21, probability*alpha);
    SQerror(Error_vector, 22, probability*alpha);
    SQerror(Error_vector, 23, probability*alpha);
    SQerror(Error_vector, 24, probability*alpha);
    SQerror(Error_vector, 25, probability*alpha);
    SQerror(Error_vector, 26, probability*alpha);
    SQerror(Error_vector, 27, probability*alpha);
    SQerror(Error_vector, 28, probability*alpha);
    SQerror(Error_vector, 29, probability*alpha);
    SQerror(Error_vector, 31, probability*alpha);
    SQerror(Error_vector, 32, probability*alpha);
    SQerror(Error_vector, 33, probability*alpha);
    SQerror(Error_vector, 34, probability*alpha);
    SQerror(Error_vector, 35, probability*alpha);
    SQerror(Error_vector, 36, probability*alpha);
    SQerror(Error_vector, 37, probability*alpha);
    SQerror(Error_vector, 38, probability*alpha);
    SQerror(Error_vector, 39, probability*alpha);
}




//------------------------------------------------------------------------------------------------------------------------------

int x_circuit(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta){
    
    /*
     * gz1=[1,2,3,4 ];
     * gz2=[1,3,5,7 ];
     * gz3=[12,13,14,15 ];
     * gz4=[1,2,5,6,8,9 ];
     * gz5=[6,9,16,19 ];
     * gz6=[16,17,18,19 ];
     * gz7=[10,11,12,15 ];
     * gz8=[8,9,10,11,16,17 ];
     * gz9=[5,7,8,11,12,13 ];
     */
    
// gz1=[1,2,3,4 ];
    
    CNOT(Error_vector, 1, 21);
    CNOT(Error_vector, 2, 21);
    CNOT(Error_vector, 3, 21);
    CNOT(Error_vector, 4, 21);
    
// gz2=[1,3,5,7 ];
    
    CNOT(Error_vector, 1, 22);
    CNOT(Error_vector, 3, 22);
    CNOT(Error_vector, 5, 22);
    CNOT(Error_vector, 7, 22);
    
// gz3=[12,13,14,15 ];
    
    CNOT(Error_vector, 12, 23);
    CNOT(Error_vector, 13, 23);
    CNOT(Error_vector, 14, 23);
    CNOT(Error_vector, 15, 23);
    
// gz4=[1,2,5,6,8,9 ];
    
    CNOT(Error_vector, 1, 24);
    CNOT(Error_vector, 2, 24);
    CNOT(Error_vector, 5, 24);
    CNOT(Error_vector, 6, 24);
    CNOT(Error_vector, 8, 24);
    CNOT(Error_vector, 9, 24);
    
//  gz5=[6,9,16,19 ];
    
    CNOT(Error_vector, 6, 25);
    CNOT(Error_vector, 9, 25);
    CNOT(Error_vector, 16, 25);
    CNOT(Error_vector, 19, 25);
    
// gz6=[16,17,18,19 ];
    
    CNOT(Error_vector, 16, 26);
    CNOT(Error_vector, 17, 26);
    CNOT(Error_vector, 18, 26);
    CNOT(Error_vector, 19, 26);
    
// gz7=[10,11,12,15 ];
    
    CNOT(Error_vector, 10, 27);
    CNOT(Error_vector, 11, 27);
    CNOT(Error_vector, 12, 27);
    CNOT(Error_vector, 15, 27);
    
    
// gz8=[8,9,10,11,16,17 ];
    
    CNOT(Error_vector, 8, 28);
    CNOT(Error_vector, 9, 28);
    CNOT(Error_vector, 10, 28);
    CNOT(Error_vector, 11, 28);
    CNOT(Error_vector, 16, 28);
    CNOT(Error_vector, 17, 28);
    
    
//  gz9=[5,7,8,11,12,13 ];
    
    
    CNOT(Error_vector, 5, 29);
    CNOT(Error_vector, 7, 29);
    CNOT(Error_vector, 8, 29);
    CNOT(Error_vector, 11, 29);
    CNOT(Error_vector, 12, 29);
    CNOT(Error_vector, 13, 29);
    
}

int z_circuit(int (*Error_vector)[n], double probability, double gamma, double alpha, double beta){
    
    
    
// gx1=[1,2,3,4 ];
    
    CNOT(Error_vector, 31, 1);
    CNOT(Error_vector, 31, 2);
    CNOT(Error_vector, 31, 3);
    CNOT(Error_vector, 31, 4);
    
// gx2=[1,3,5,7 ];
    
    CNOT(Error_vector, 32, 1);
    CNOT(Error_vector, 32, 3);
    CNOT(Error_vector, 32, 5);
    CNOT(Error_vector, 32, 7);
    
// gx3=[12,13,14,15 ];
    
    CNOT(Error_vector, 33, 12);
    CNOT(Error_vector, 33, 13);
    CNOT(Error_vector, 33, 14);
    CNOT(Error_vector, 33, 15);
    
// gx4=[1,2,5,6,8,9 ];
    
    CNOT(Error_vector, 34, 1);
    CNOT(Error_vector, 34, 2);
    CNOT(Error_vector, 34, 5);
    CNOT(Error_vector, 34, 6);
    CNOT(Error_vector, 34, 8);
    CNOT(Error_vector, 34, 9);
    
// gx5=[6,9,16,19 ];
    
    CNOT(Error_vector, 35, 6);
    CNOT(Error_vector, 35, 9);
    CNOT(Error_vector, 35, 16);
    CNOT(Error_vector, 35, 19);
    
// gx6=[16,17,18,19 ];
    
    CNOT(Error_vector, 36, 16);
    CNOT(Error_vector, 36, 17);
    CNOT(Error_vector, 36, 18);
    CNOT(Error_vector, 36, 19);
    
// gx7=[10,11,12,15 ];
    
    CNOT(Error_vector, 37, 10);
    CNOT(Error_vector, 37, 11);
    CNOT(Error_vector, 37, 12);
    CNOT(Error_vector, 37, 15);
    
// gx8=[8,9,10,11,16,17 ];
    
    CNOT(Error_vector, 38, 8);
    CNOT(Error_vector, 38, 9);
    CNOT(Error_vector, 38, 10);
    CNOT(Error_vector, 38, 11);
    CNOT(Error_vector, 38, 16);
    CNOT(Error_vector, 38, 17);
    
    
// gx9=[5,7,8,11,12,13 ];
    
    
    CNOT(Error_vector, 39, 5);
    CNOT(Error_vector, 39, 7);
    CNOT(Error_vector, 39, 8);
    CNOT(Error_vector, 39, 11);
    CNOT(Error_vector, 39, 12);
    CNOT(Error_vector, 39, 13);
    
}


