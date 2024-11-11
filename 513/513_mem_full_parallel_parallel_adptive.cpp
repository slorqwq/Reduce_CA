#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>


using namespace std;
int const n = 60; /* n-qubit state */
static uint64_t s[4];
static uint64_t x = 0xbf3749f5b97cd3b9; /* The state can be seeded with any value. */
double r; // random number



uint64_t next64() {  // random number
    uint64_t z = (x += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}

void rnd256_init() { // random number
    s[0] = next64();  s[1] = next64();  s[2] = next64();  s[3] = next64();
}


int correct(int (*Error_vector)[n], int a, int B);

int SQerror(int (*Record_error)[n], int a, double probability); // Single qubit error
int TQerror(int (*Record_error)[n], int a, int b, double probability); // Two qubit error
int CNOT(int (*Error_vector)[n], int a, int b);
int SWAP(int (*Error_vector)[n], int a, int b);
int Hadamard(int (*Error_vector)[n], int a);

int circuit(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha);


int unflagged_s(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha); // g1,2,3,4
int unflagged_v(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha); // g1,5,3,4
int unflagged_m1(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha);  // g1
int unflagged_m2(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha);  // g2
int unflagged_m3(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha);  // g3
int unflagged_m4(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha);  // g4

int unflagged_m14(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha );
int unflagged_3m4(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha );
int unflagged_m34(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha );
int unflagged_2m34(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha );
int unflagged_m234(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha );
int unflagged_1m23(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha );
int unflagged_m123(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha );
int unflagged_4m1(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha );

int perfect(int (*Error_vector)[n] );

int const table_length = 56; // 192


int syndrome_table[15][4]= { 0 };
int syndrome_table_p[15][4]= { 0 };
int syndrome_table_flag[table_length][12]= { 0 };
int adptive_index[table_length][4]= { 0 };
int symdorme_result[4] = { 0 };
int symdorme_result2[8] = { 0 };
int symdorme_result3[12] = { 0 };
int recovery_x[15][5]= { 0 };
int recovery_z[15][5]= { 0 };
int recovery_x_flag[table_length][5]= { 0 };
int recovery_z_flag[table_length][5]= { 0 };
int stabilizer_x[4][5]= { 0 }; // 4個stabilizer, wight 5
int stabilizer_z[4][5]= { 0 }; // 4個stabilizer, wight 5
int test1[4] = { 0 };
int test2[8] = { 0 };
int test3[12] = { 0 };
int compare_result;
int compare_result2;
int table_index;


int main(){
    
    
    
//============================================================================================================================
    
//讀取table
    
    
    ifstream fin1("table_full\\513table_s.txt");
    if(!fin1) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<=14;i++)
        for(int k=0;k<=3;k++)
            fin1 >> syndrome_table[i][k];
    fin1.close();
    
    ifstream fin2("table_full\\recovery_x.txt");
    if(!fin2) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<=14;i++)
        for(int k=0;k<=4;k++)
            fin2 >> recovery_x[i][k];
    fin2.close();
    
    
    ifstream fin3("table_full\\recovery_z.txt");
    if(!fin3) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<=14;i++)
        for(int k=0;k<=4;k++)
            fin3 >> recovery_z[i][k];
    fin3.close();
    
    
    
    ifstream fin4("table_full\\adptive_index.txt");
    if(!fin4) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<=table_length;i++)
        for(int k=0;k<=3;k++)
            fin4 >> adptive_index[i][k];
    fin4.close();
    
    ifstream fin5("table_full\\513table_flag.txt");
    if(!fin5) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<=table_length;i++)
        for(int k=0;k<=11;k++)
            fin5 >> syndrome_table_flag[i][k];
    fin5.close();
    
    
    ifstream fin6("table_full\\recovery_x_flag.txt");
    if(!fin6) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<=table_length;i++)
        for(int k=0;k<=4;k++)
            fin6 >> recovery_x_flag[i][k];
    fin6.close();
    
    ifstream fin7("table_full\\recovery_z_flag.txt");
    if(!fin7) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<=table_length;i++)
        for(int k=0;k<=4;k++)
            fin7 >> recovery_z_flag[i][k];
    fin7.close();
    /*
cout<< "adptive_index 1 " << adptive_index[0][0]<<adptive_index[0][1] <<adptive_index[0][2] <<adptive_index[0][3]  << endl ;
cout<< "adptive_index 2 " << adptive_index[1][0]<<adptive_index[1][1] <<adptive_index[1][2] <<adptive_index[1][3]  << endl ;
cout<< "adptive_index 3 " << adptive_index[10][0]<<adptive_index[10][1] <<adptive_index[10][2] <<adptive_index[10][3]  << endl ;
   
   
cout<< "syndrome_table 1 " << syndrome_table[0][0]<<syndrome_table[0][1] <<syndrome_table[0][2] <<syndrome_table[0][3]  << endl ;
cout<< "syndrome_table 2 " << syndrome_table[1][0]<<syndrome_table[1][1] <<syndrome_table[1][2] <<syndrome_table[1][3]  << endl ;
cout<< "syndrome_table 3 " << syndrome_table[2][0]<<syndrome_table[2][1] <<syndrome_table[2][2] <<syndrome_table[2][3]  << endl ;
   
cout<< "syndrome_table_p 1 " <<  syndrome_table_p[0][0]<< syndrome_table_p[0][1] << syndrome_table_p[0][2] << syndrome_table_p[0][3]  << endl ;
cout<< "syndrome_table_p 2 " <<  syndrome_table_p[1][0]<< syndrome_table_p[1][1] << syndrome_table_p[1][2] << syndrome_table_p[1][3]  << endl ;
cout<< "syndrome_table_p 3 " <<  syndrome_table_p[2][0]<< syndrome_table_p[2][1] << syndrome_table_p[2][2] << syndrome_table_p[2][3]  << endl ;
   
cout<< "513table_flag 1 " <<  syndrome_table_flag[0][0]<< syndrome_table_flag[0][1] << syndrome_table_flag[0][2] << syndrome_table_flag[0][3] << syndrome_table_flag[0][4] << syndrome_table_flag[0][5] << syndrome_table_flag[0][6] << syndrome_table_flag[0][7] << syndrome_table_flag[0][8]<< syndrome_table_flag[0][9] << endl ;
cout<< "513table_flag 2 " <<  syndrome_table_flag[1][0]<< syndrome_table_flag[1][1] << syndrome_table_flag[1][2] << syndrome_table_flag[1][3] << syndrome_table_flag[1][4] << syndrome_table_flag[1][5] << syndrome_table_flag[1][6] << syndrome_table_flag[1][7] << syndrome_table_flag[1][8]<< syndrome_table_flag[1][9] << endl ;
cout<< "513table_flag 3 " <<  syndrome_table_flag[2][0]<< syndrome_table_flag[2][1] << syndrome_table_flag[2][2] << syndrome_table_flag[2][3] << syndrome_table_flag[2][4] << syndrome_table_flag[2][5] << syndrome_table_flag[2][6] << syndrome_table_flag[2][7] << syndrome_table_flag[2][8]<< syndrome_table_flag[2][9] << endl ;
cout<< "513table_flag 4 " <<  syndrome_table_flag[3][0]<< syndrome_table_flag[3][1] << syndrome_table_flag[3][2] << syndrome_table_flag[3][3] << syndrome_table_flag[3][4] << syndrome_table_flag[3][5] << syndrome_table_flag[3][6] << syndrome_table_flag[3][7] << syndrome_table_flag[3][8]<< syndrome_table_flag[3][9] << endl ;
   
   
cout<< "recovery_x_flag 1 " << recovery_x_flag[0][0]<<recovery_x_flag[0][1] <<recovery_x_flag[0][2] <<recovery_x_flag[0][3]  << recovery_x_flag[0][4]  << endl ;
cout<< "recovery_x_flag 2 " << recovery_x_flag[1][0]<<recovery_x_flag[1][1] <<recovery_x_flag[1][2] <<recovery_x_flag[1][3]  << recovery_x_flag[0][4]  << endl ;
cout<< "recovery_x_flag 3 " << recovery_x_flag[2][0]<<recovery_x_flag[2][1] <<recovery_x_flag[2][2] <<recovery_x_flag[2][3]  << recovery_x_flag[0][4]  << endl ;
   
cout<< "recovery_z_flag 1 " << recovery_z_flag[0][0]<<recovery_z_flag[0][1] <<recovery_z_flag[0][2] <<recovery_z_flag[0][3]  << recovery_z_flag[0][4]  << endl ;
cout<< "recovery_z_flag 2 " << recovery_z_flag[1][0]<<recovery_z_flag[1][1] <<recovery_z_flag[1][2] <<recovery_z_flag[1][3]  << recovery_z_flag[0][4]  << endl ;
cout<< "recovery_z_flag 3 " << recovery_z_flag[2][0]<<recovery_z_flag[2][1] <<recovery_z_flag[2][2] <<recovery_z_flag[2][3]  << recovery_z_flag[0][4]  << endl ;
     */
    
//============================================================================================================================
    
    
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
    
    double Total_number, Error_number, probability;
    int s1, s2, s3, s4, s5, s6, s7, s8, m1, m2, m3, m4,m5,m6,m7,m8, q1, q2, f1, f2, f3, f4;
    int s9,s10,s11,s12,s13,s14,s15,s16;
    int Error_vector[2][n]={0};
    int Error_vector2[2][n]={0};
    int xe[1]={2}   ; // sigle error by user , X, Z, Y = 2, 3, 4
    int ze[1]={3}   ; // sigle error by user , X, Z, Y = 2, 3, 4
    
    int N = 15; // 切 N 個格子
    double Gamma = 1; // gamma = error memory rate of idle qubits / gate error rate
    double alpha = 10; // measurement error & preparation ancilla
    double beta = 1;  // CNOT error
    double Display_p[N], Display_e[N], Display_d[N];
    
    cout << "%[[5,1,3]] full parallel with with the last round is parallel adpative, memeory threshold" << " ,loop=" << N-1 << " ,gamma, alpha, beta=" << Gamma << alpha << beta << endl << endl << endl;
    
    int index_loop;
    index_loop = 0;
    for(int i=1; i<N; i++){
        
        //probability = 0.00001+0.01*(i-1); // gamma=1 ; N=4
        probability = 0.00001+0.00001*(i-1)*(i*i/2); // gamma=1 ; N=4
        Total_number = 0; // 總共執行電路的次數
        Error_number = 0; // 測到是電路的 output 是 malignant pair的次數
        while(Total_number<100000000){ // Error_number = malignant pair 數量
            //while(Total_number<10000||Error_number<1600){ // Error_number = malignant pair 數量
            index_loop = i+index_loop;
            s1 = 0;
            s2 = 0;
            s3 = 0;
            s4 = 0;
            s5 = 0;
            s6 = 0;
            s7 = 0;
            s8 = 0;
            s9 = 0;
            s10= 0;
            s11= 0;
            s12= 0;
            s13= 0;
            s14= 0;
            s15= 0;
            s16= 0;
            m1 = 0;
            m2 = 0;
            m3 = 0;
            m4 = 0;
            m5 = 0;
            m6 = 0;
            m7 = 0;
            m8 = 0;
            q1 = 0;
            q2 = 0;
            f1 = 0;
            f2 = 0;
            f3 = 0;
            f4 = 0;
            
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
             */
            //  correct(Error_vector, 5, 2);
            
            circuit(Error_vector, probability, Gamma, beta, alpha );
            
            
            
            
            m1 = Error_vector[0][5]; // g1
            m2 = Error_vector[0][6]; // g2
            m3 = Error_vector[0][7]; // g3
            m4 = Error_vector[0][8]; // g4
            
            f1 = Error_vector[1][9];  // f1
            f2 = Error_vector[1][10]; // f2
            f3 = Error_vector[1][11]; // f1
            f4 = Error_vector[1][12]; // f2
            
            //---------------------------------------------------------------------------------------------------------------------------------------------
            /*
    if ( m1+m2+m3+m4+f1+f2+f3+f4 > 0){
    cout<< "After circuit: No."  << index_loop << endl ;
    cout<< "Error_vector X " << Error_vector[0][0]<<Error_vector[0][1] <<Error_vector[0][2] <<Error_vector[0][3] <<Error_vector[0][4]  << endl ;
    cout<< "Error_vector Z " << Error_vector[1][0]<<Error_vector[1][1] <<Error_vector[1][2] <<Error_vector[1][3] <<Error_vector[1][4]  << endl ;
 
    cout<< "m1234f1234 " << Error_vector[0][5]<<Error_vector[0][6] <<Error_vector[0][7] <<Error_vector[0][8] <<Error_vector[1][9] <<Error_vector[1][10] <<Error_vector[1][11] <<Error_vector[1][12] << endl ;
    }
             */
            //---------------------------------------------------------------------------------------------------------------------------------------------
            
            
            
            if ( m1 ==0 && m2 ==0 && m3 ==0 && m4 ==0 && f1 ==0 && f2 ==0 && f3 ==0 && f4 ==0  ){
                goto ckp1;
            }
            
            
            
            if ( f1==1 || f2==1 || f3==1 || f4==1){
                
                //  unflagged_s(Error_vector, probability, Gamma, beta, alpha ); //g1,2,3,4
                //  unflagged_s(Error_vector, probability, 0, 0,0 ); //g1,2,3,4
                // used flag rise table to do recovery
                //loading syndorme result to array
                
                
                symdorme_result2[0] = Error_vector[0][5];   // g1
                symdorme_result2[1] = Error_vector[0][6];   // g2
                symdorme_result2[2] = Error_vector[0][7];   // g3
                symdorme_result2[3] = Error_vector[0][8];   // g4
                
                symdorme_result2[4] = Error_vector[1][9];   // f1
                symdorme_result2[5] = Error_vector[1][10];  // f2
                symdorme_result2[6] = Error_vector[1][11];  // f3
                symdorme_result2[7] = Error_vector[1][12];  // f4
                
                symdorme_result3[0] = Error_vector[0][5];   // g1
                symdorme_result3[1] = Error_vector[0][6];   // g2
                symdorme_result3[2] = Error_vector[0][7];   // g3
                symdorme_result3[3] = Error_vector[0][8];   // g4
                
                symdorme_result3[4] = Error_vector[1][9];   // f1
                symdorme_result3[5] = Error_vector[1][10];  // f2
                symdorme_result3[6] = Error_vector[1][11];  // f3
                symdorme_result3[7] = Error_vector[1][12];  // f4
                
                
                //	symdorme_result2[8] = Error_vector[0][15];  // g'1
                //	symdorme_result2[9] = Error_vector[0][16];  // g'2
                //	symdorme_result2[10] = Error_vector[0][17];  // g'3
                //	symdorme_result2[11] = Error_vector[0][18];  // g'4
                /*
                 * cout <<"Loop No. " << index_loop ;
                 * cout<< " flag rise: " << endl;
                 * cout<< "Error_vector X " << Error_vector[0][0]<<Error_vector[0][1] <<Error_vector[0][2] <<Error_vector[0][3] <<Error_vector[0][4]  << endl ;
                 * cout<< "Error_vector Z " << Error_vector[1][0]<<Error_vector[1][1] <<Error_vector[1][2] <<Error_vector[1][3] <<Error_vector[1][4]  << endl ;
                 * cout<< "m1234f1234m'1234  " << Error_vector[0][5]<<Error_vector[0][6] <<Error_vector[0][7] <<Error_vector[0][8] <<Error_vector[1][9] <<Error_vector[1][10] <<Error_vector[1][11] <<Error_vector[1][12]  << Error_vector[0][15]<<Error_vector[0][16] <<Error_vector[0][17] <<Error_vector[0][18] << endl ;
                 * cout<< "symdorme_result   " << symdorme_result2[0]<<symdorme_result2[1] <<symdorme_result2[2] <<symdorme_result2[3] << symdorme_result2[4]<<symdorme_result2[5] <<symdorme_result2[6] <<symdorme_result2[7] <<symdorme_result2[8] <<symdorme_result2[9] <<symdorme_result2[10] <<symdorme_result2[11] << endl  << endl ;
                 */
                
                //compare test2 and symdorme_result array and get index j
                for (int j=0; j<table_length; j++){
                    
                    for (int i=0; i<8; i++){
                        test2[i]=syndrome_table_flag[j][i];
                    }
                    
                    
                    //---------------------------------------------
                    /*
                     * cout <<"test2 = "<< endl;
                     * for (int q=0; q<12;q++  ){
                     * cout << test2[q] ;
                     * }
                     * cout << endl;
                     */
                    //--------------------------------------------
                    
                    /*
                // 排除syndrome = 0000的情快
                if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  ){
                    break;
                }
                     */
                    compare_result = memcmp(test2, symdorme_result2,sizeof(test2));
                    
                    if (compare_result == 0) {
                        
                        //   table_index = j;
                        // cout <<  "compare result = "<< compare_result << endl;
                        // cout <<  "j= "  << j << endl;
                        
                        
          
					if ( adptive_index[j][0] == 2 && adptive_index[j][1] == 0 && adptive_index[j][2] == 0 && adptive_index[j][3] == 2  ){
                        unflagged_m14(Error_vector, probability, Gamma, beta, alpha );
                        }
                    if ( adptive_index[j][0] == 0 && adptive_index[j][1] == 0 && adptive_index[j][2] == 1 && adptive_index[j][3] == 2  ){
                        unflagged_3m4(Error_vector, probability, Gamma, beta, alpha );
                    }
                    if ( adptive_index[j][0] == 0 && adptive_index[j][1] == 1 && adptive_index[j][2] == 0 && adptive_index[j][3] == 1  ){
                        Error_vector[0][15] = 0;  // g'1
						Error_vector[0][16] = 1;  // g'5
						Error_vector[0][17] = 0;  // g'3
						Error_vector[0][18] = 1;  // g'4  
                    }
                    if ( adptive_index[j][0] == 0 && adptive_index[j][1] == 1 && adptive_index[j][2] == 1 && adptive_index[j][3] == 0  ){
                        Error_vector[0][15] = 0;  // g'1
						Error_vector[0][16] = 1;  // g'5
						Error_vector[0][17] = 1;  // g'3
						Error_vector[0][18] = 0;  // g'4
                    }
                    if ( adptive_index[j][0] == 0 && adptive_index[j][1] == 0 && adptive_index[j][2] == 2 && adptive_index[j][3] == 2  ){
                        unflagged_m34(Error_vector, probability, Gamma, beta, alpha );
                    }
                    if ( adptive_index[j][0] == 0 && adptive_index[j][1] == 1 && adptive_index[j][2] == 2 && adptive_index[j][3] == 2  ){
                        unflagged_2m34(Error_vector, probability, Gamma, beta, alpha );
                    }
                    if ( adptive_index[j][0] == 1 && adptive_index[j][1] == 0 && adptive_index[j][2] == 1 && adptive_index[j][3] == 0  ){
                        Error_vector[0][15] = 1;  // g'1
						Error_vector[0][16] = 0;  // g'5
						Error_vector[0][17] = 1;  // g'3
						Error_vector[0][18] = 0;  // g'4
                    }
                    if ( adptive_index[j][0] == 1 && adptive_index[j][1] == 1 && adptive_index[j][2] == 0 && adptive_index[j][3] == 0  ){
                        Error_vector[0][15] = 1;  // g'1
						Error_vector[0][16] = 1;  // g'5
						Error_vector[0][17] = 0;  // g'3
						Error_vector[0][18] = 0;  // g'4
                    }
                    if ( adptive_index[j][0] == 0 && adptive_index[j][1] == 2 && adptive_index[j][2] == 2 && adptive_index[j][3] == 2  ){
                        unflagged_m234(Error_vector, probability, Gamma, beta, alpha );
                    }
                    if ( adptive_index[j][0] == 1 && adptive_index[j][1] == 2 && adptive_index[j][2] == 2 && adptive_index[j][3] == 0  ){
                        unflagged_1m23(Error_vector, probability, Gamma, beta, alpha );
                    }
                    if ( adptive_index[j][0] == 2 && adptive_index[j][1] == 2 && adptive_index[j][2] == 2 && adptive_index[j][3] == 0  ){
                        unflagged_m123(Error_vector, probability, Gamma, beta, alpha );
                    }
                    if ( adptive_index[j][0] == 2 && adptive_index[j][1] == 0 && adptive_index[j][2] == 0 && adptive_index[j][3] == 1  ){
                        unflagged_4m1(Error_vector, probability, Gamma, beta, alpha );
                    }                       
		
                        
                        
                        /*
                        if ( adptive_index[j][0] == 2 && adptive_index[j][1] == 0 && adptive_index[j][2] == 0 && adptive_index[j][3] == 2  ){
                            unflagged_m14(Error_vector, probability, Gamma, beta, alpha );
                        }
                        if ( adptive_index[j][0] == 0 && adptive_index[j][1] == 0 && adptive_index[j][2] == 2 && adptive_index[j][3] == 2  ){
                            unflagged_m34(Error_vector, probability, Gamma, beta, alpha );
                        }
                        if ( adptive_index[j][0] == 0 && adptive_index[j][1] == 1 && adptive_index[j][2] == 0 && adptive_index[j][3] == 1  ){
                            unflagged_m24(Error_vector, probability, Gamma, beta, alpha );
                        }
                        if ( adptive_index[j][0] == 0 && adptive_index[j][1] == 1 && adptive_index[j][2] == 1 && adptive_index[j][3] == 0  ){
                            unflagged_m23(Error_vector, probability, Gamma, beta, alpha );
                        }
                        if ( adptive_index[j][0] == 0 && adptive_index[j][1] == 2 && adptive_index[j][2] == 2 && adptive_index[j][3] == 2  ){
                            unflagged_m234(Error_vector, probability, Gamma, beta, alpha );
                        }
                        if ( adptive_index[j][0] == 1 && adptive_index[j][1] == 0 && adptive_index[j][2] == 1 && adptive_index[j][3] == 0  ){
                            unflagged_m13(Error_vector, probability, Gamma, beta, alpha );
                        }
                        if ( adptive_index[j][0] == 1 && adptive_index[j][1] == 1 && adptive_index[j][2] == 0 && adptive_index[j][3] == 0  ){
                            unflagged_m12(Error_vector, probability, Gamma, beta, alpha );
                        }
                        if ( adptive_index[j][0] == 2 && adptive_index[j][1] == 2 && adptive_index[j][2] == 2 && adptive_index[j][3] == 0  ){
                            unflagged_m123(Error_vector, probability, Gamma, beta, alpha );
                        }
                        */
                        /*
                switch (adptive_index[j][0]) {
                case 2:
                    unflagged_m1(Error_vector, probability, Gamma, beta, alpha);
                    break;
                case 1:
                    Error_vector[0][15] = 1;
                    break;
                default:
                    Error_vector[0][15] = 0;
                    break;
                }
           
                switch (adptive_index[j][1]) {
                case 2:
                    unflagged_m2(Error_vector, probability, Gamma, beta, alpha);
                    break;
                case 1:
                    Error_vector[0][16] = 1;
                    break;
                default:
                    Error_vector[0][16] = 0;
                    break;
                }
           
                switch (adptive_index[j][2]) {
                case 2:
                    unflagged_m3(Error_vector, probability, Gamma, beta, alpha);
                    break;
                case 1:
                    Error_vector[0][17] = 1;
                    break;
                default:
                    Error_vector[0][17] = 0;
                    break;
                }
           
                switch (adptive_index[j][3]) {
                case 2:
                    unflagged_m4(Error_vector, probability, Gamma, beta, alpha);
                    break;
                case 1:
                    Error_vector[0][18] = 1;
                    break;
                default:
                    Error_vector[0][18] = 0;
                    break;
                }
                         */
                        
                        symdorme_result3[8] = Error_vector[0][15];  // g'1
                        symdorme_result3[9] = Error_vector[0][16];  // g'2
                        symdorme_result3[10] = Error_vector[0][17];  // g'3
                        symdorme_result3[11] = Error_vector[0][18];  // g'4
                        
                        
                        
                        //compare test2 and symdorme_result array and get index j
                        for (int jj=0; jj<table_length; jj++){
                            
                            for (int i=0; i<12; i++){
                                test3[i]=syndrome_table_flag[jj][i];
                            }
                            
                            
                            //---------------------------------------------
                            /*
                             * cout <<"test2 = "<< endl;
                             * for (int q=0; q<12;q++  ){
                             * cout << test2[q] ;
                             * }
                             * cout << endl;
                             */
                            //--------------------------------------------
                            
                            /*
                             * // 排除syndrome = 0000的情快
                             * if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  ){
                             * break;
                             * }
                             */
                            compare_result2 = memcmp(test3, symdorme_result3,sizeof(test3));
                            
                            if (compare_result2 == 0) {
                                
                                //   table_index = j;
                                // cout <<  "compare result = "<< compare_result << endl;
                                // cout <<  "j= "  << j << endl;
                                
                                //使用recovery table進行 revcovery (error correction)
                                
                                for (int k=0; k<5; k++){
                                    Error_vector[0][k]= (Error_vector[0][k]+recovery_x_flag[jj][k])%2;
                                    Error_vector[1][k]= (Error_vector[1][k]+recovery_z_flag[jj][k])%2;
                                }
                                /*
                                 * cout<< "After recover" << endl;
                                 * cout<< "Error_vector X " << Error_vector[0][0]<<Error_vector[0][1] <<Error_vector[0][2] <<Error_vector[0][3] <<Error_vector[0][4]  << endl ;
                                 * cout<< "Error_vector Z " << Error_vector[1][0]<<Error_vector[1][1] <<Error_vector[1][2] <<Error_vector[1][3] <<Error_vector[1][4]  << endl ;
                                 */
                                break;
                                
                            }
                            
                        }
                        
                        
                        
                        
                        
                        
                        
                        /*
                         * cout<< "After recover" << endl;
                         * cout<< "Error_vector X " << Error_vector[0][0]<<Error_vector[0][1] <<Error_vector[0][2] <<Error_vector[0][3] <<Error_vector[0][4]  << endl ;
                         * cout<< "Error_vector Z " << Error_vector[1][0]<<Error_vector[1][1] <<Error_vector[1][2] <<Error_vector[1][3] <<Error_vector[1][4]  << endl ;
                         */
                        break;
                        
                    }
                    
                }
                goto ckp1;
                
            } // End of if ( f1==1 || f2==1 )
            
            /*
    cout << "After recovery " << endl;
    cout << "X " <<Error_vector[0][0] <<Error_vector[0][1] <<Error_vector[0][2]<<Error_vector[0][3]<<Error_vector[0][4]<< " " <<Error_vector[0][5]<<Error_vector[0][6]<<Error_vector[0][7]<< endl;
    cout << "Z " <<Error_vector[1][0] <<Error_vector[1][1] <<Error_vector[1][2]<<Error_vector[1][3]<<Error_vector[1][4]<< " " <<Error_vector[1][8]<<Error_vector[1][9]<<Error_vector[1][10]<< endl<< endl<< endl;
             */
            
            
            
            if ( m1==1 || m2==1 || m3==1 || m4==1  ){
                
                for(int i=0; i<2; i++){
                    for(int j=5; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                }
                
                
                unflagged_s(Error_vector, probability, Gamma, beta, alpha ); //g1,2,3,4
                // unflagged_s(Error_vector, probability, 0, 0,0 ); //g1,2,3,4
                // used standard table to do recovery
                //loading syndorme result to array
                
                symdorme_result[0] = Error_vector[0][15];
                symdorme_result[1] = Error_vector[0][16];
                symdorme_result[2] = Error_vector[0][17];
                symdorme_result[3] = Error_vector[0][18];
                /*
    cout<< "measurement" << endl;
    cout<< "Error_vector X " << Error_vector[0][0]<<Error_vector[0][1] <<Error_vector[0][2] <<Error_vector[0][3] <<Error_vector[0][4]  << endl ;
    cout<< "Error_vector Z " << Error_vector[1][0]<<Error_vector[1][1] <<Error_vector[1][2] <<Error_vector[1][3] <<Error_vector[1][4]  << endl ;
    cout<< "m'1534          "  << Error_vector[0][15]<<Error_vector[0][16] <<Error_vector[0][17] <<Error_vector[0][18] << endl ;
    cout<< "symdorme_result " << symdorme_result[0]<<symdorme_result[1] <<symdorme_result[2] <<symdorme_result[3]  << endl  << endl ;
                 */
                
                //compare test1 and symdorme_result array and get index j
                for (int j=0; j<15; j++){
                    
                    for (int i=0; i<4; i++){
                        test1[i]=syndrome_table[j][i];
                    }
                    
                    // 排除syndrome = 0000的情快
                    
                    if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  ){
                        break;
                    }
                    
                    compare_result = memcmp(test1, symdorme_result,sizeof(test1));
                    
                    if (compare_result == 0) {
                        
                        //   table_index = j;
                        
                        //cout <<  "j= "  << j << endl;
                        //使用recovery table進行 revcovery (error correction)
                        
                        
                        //---------------------------------------------
                        /*
                         * cout <<"test1 = "<< endl;
                         * for (int q=0; q<4;q++  ){
                         * cout << test1[q] ;
                         * }
                         * cout << endl;
                         *
                         * cout <<"Recovery X = "<< endl;
                         * for (int q=0; q<4;q++  ){
                         * cout << recovery_x[j][q] ;
                         * }
                         * cout << endl;
                         *
                         * cout <<"Recovery Y = "<< endl;
                         * for (int q=0; q<4;q++  ){
                         * cout << recovery_z[j][q] ;
                         * }
                         * cout << endl;
                         */
                        //--------------------------------------------
                        
                        
                        
                        for (int k=0; k<5; k++){
                            Error_vector[0][k]= (Error_vector[0][k]+recovery_x[j][k])%2;
                            Error_vector[1][k]= (Error_vector[1][k]+recovery_z[j][k])%2;
                        }
                        /*
                cout<< "After recover" << endl;
                cout<< "Error_vector X " << Error_vector[0][0]<<Error_vector[0][1] <<Error_vector[0][2] <<Error_vector[0][3] <<Error_vector[0][4]  << endl ;
                cout<< "Error_vector Z " << Error_vector[1][0]<<Error_vector[1][1] <<Error_vector[1][2] <<Error_vector[1][3] <<Error_vector[1][4]  << endl ;
                         */
                        break;
                        
                    }
                    
                }
                
                goto ckp1;
            }  // End of if ( m1==1 || m2==1 || m3==1 || m4==1  )
            
            
            
            
//----------------------------------------------------------------------------------------------------------------------------------
            
            ckp1:
                
                
//---Perfect circuit----------------------------------------------------------------------------------------------------
                
                
                for(int i=0; i<2; i++){
                    for(int j=5; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                }
                
                
                
                perfect(Error_vector);
                
                /*
       cout <<"After perfect No." << index_loop << endl;
       cout << "X " <<Error_vector[0][0] <<Error_vector[0][1] <<Error_vector[0][2]<<Error_vector[0][3]<<Error_vector[0][4]<< " " <<Error_vector[0][5]<<Error_vector[0][6]<<Error_vector[0][7]<< endl;
       cout << "Z " <<Error_vector[1][0] <<Error_vector[1][1] <<Error_vector[1][2]<<Error_vector[1][3]<<Error_vector[1][4]<< " " <<Error_vector[1][8]<<Error_vector[1][9]<<Error_vector[1][10]<< endl<< endl<< endl;
     
       cout <<  "syndrome " <<Error_vector[0][5] <<Error_vector[0][8] <<Error_vector[0][6]<<Error_vector[0][9] <<  endl;
       cout <<  "flag     " <<Error_vector[1][7] <<Error_vector[1][10]<<endl<< endl<< endl ;
                 */
                
                
                //loading syndorme result to array
                
                symdorme_result[0] = Error_vector[0][5];
                symdorme_result[1] = Error_vector[0][8];
                symdorme_result[2] = Error_vector[0][6];
                symdorme_result[3] = Error_vector[0][9];
                
                
                //compare test1 and symdorme_result array and get index j
                for (int j=0; j<15; j++){
                    
                    for (int i=0; i<4; i++){
                        test1[i]=syndrome_table[j][i];
                    }
                    // 排除syndrome = 0000的情快
                    if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  ){
                        break;
                    }
                    
                    compare_result = memcmp(test1, symdorme_result,sizeof(symdorme_result));
                    
                    if (compare_result == 0) {
                        
                        //   table_index = j;
                        
                        // cout <<  "j= "  << j << endl;
                        //使用recovery進行 x error
                        
                        for (int k=0; k<5; k++){
                            Error_vector[0][k]= (Error_vector[0][k]+recovery_x[j][k])%2;
                            Error_vector[1][k]= (Error_vector[1][k]+recovery_z[j][k])%2;
                        }
                        break;
                        
                    }
                    
                }
                
                
                
                /*
    cout << "After recovery " << endl;
    cout << "X " <<Error_vector[0][0] <<Error_vector[0][1] <<Error_vector[0][2]<<Error_vector[0][3]<<Error_vector[0][4]<< " " <<Error_vector[0][5]<<Error_vector[0][6]<<Error_vector[0][7]<< endl;
    cout << "Z " <<Error_vector[1][0] <<Error_vector[1][1] <<Error_vector[1][2]<<Error_vector[1][3]<<Error_vector[1][4]<< " " <<Error_vector[1][8]<<Error_vector[1][9]<<Error_vector[1][10]<< endl<< endl<< endl;
                 */
                
                
                //排除logci X, logic Z
                
                for (int i=0; i<5;i++){
                    s9=(s9+Error_vector[0][i])%2;
                }
                for (int i=0; i<5;i++){
                    s10=(s10+Error_vector[1][i])%2;
                }
                
                if (s9 == 0  && s10 ==0){
                    goto ckp3;
                }
                /*
cout <<"Final No. " << index_loop << endl;
cout << "X " <<Error_vector[0][0] <<Error_vector[0][1] <<Error_vector[0][2]<<Error_vector[0][3]<<Error_vector[0][4]<< " " <<Error_vector[0][5]<<Error_vector[0][6]<<Error_vector[0][7]<< endl;
cout << "Z " <<Error_vector[1][0] <<Error_vector[1][1] <<Error_vector[1][2]<<Error_vector[1][3]<<Error_vector[1][4]<< " " <<Error_vector[1][8]<<Error_vector[1][9]<<Error_vector[1][10]<< endl<< endl<< endl;
                 */
                
                Error_number = Error_number + 1 ;
                
                ckp3:
                    
                    
                    Total_number = Total_number + 1;
                    //cout << Error_number << ", " << Total_number << endl;
                    
        } // while
        
        
        Display_p[i-1] = probability;
        Display_e[i-1] = Error_number/Total_number;
        cout  <<  "%No." << i << " Physical error rate : " << probability << "; Error number = " << Error_number << ", total_number = " << Total_number << ", logical error rate : " <<  Error_number/(Total_number) << "    |" << c_time_string ;//<< endl;
        
        
        
        
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
    
    cout << "Parallel_" << "Gamma = " << Gamma << endl;
    
    
    
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


int SWAP(int (*Error_vector)[n], int a, int b){
    CNOT(Error_vector, a, b);
    CNOT(Error_vector, b, a);
    CNOT(Error_vector, a, b);
}

int Hadamard(int (*Error_vector)[n], int a){
    
    a = a - 1;
    
    
    if(Error_vector[0][a] == 1 || Error_vector[1][a] == 1 ){
        
        if(Error_vector[0][a]==1 && Error_vector[1][a]==1 ){  // 如果是Y error 先補一次X, Z error
            Error_vector[0][a] = (Error_vector[0][a] + 1)%2;
            Error_vector[1][a] = (Error_vector[1][a] + 1)%2;
        }
        
        
        Error_vector[0][a] = (Error_vector[0][a] + 1)%2;
        Error_vector[1][a] = (Error_vector[1][a] + 1)%2;
        
        
    }
    
}


int perfect(int (*Error_vector)[n]){
    
    //part A
    // g1 & g3
    //Number A--------------------------
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 6);
    Hadamard(Error_vector,1);
    
    //Number B--------------------------
    
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 7);
    Hadamard(Error_vector,1);
    
    //----------------------------------
    CNOT(Error_vector, 8, 6);
    CNOT(Error_vector, 8, 7);
    
    //Number C--------------------------
    
    CNOT(Error_vector, 2, 6);
    
    
    //Number D--------------------------
    Hadamard(Error_vector,3);
    CNOT(Error_vector, 3, 7);
    Hadamard(Error_vector,3);
    
    
    //Number E--------------------------
    
    CNOT(Error_vector, 3, 6);
    
    
    //Number F--------------------------
    
    CNOT(Error_vector, 4, 7);
    
    //----------------------------------
    CNOT(Error_vector, 8, 6);
    CNOT(Error_vector, 8, 7);
    
    
    //Number G--------------------------
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 6);
    Hadamard(Error_vector,4);
    
    
    //Number H--------------------------
    
    CNOT(Error_vector, 5, 7);
    
    
    //----------------------------------
    
    //part B
    // g2 & g4
    //Number I--------------------------
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 9);
    Hadamard(Error_vector,2);
    
    
    //Number J--------------------------
    
    CNOT(Error_vector, 1, 10);
    
    //----------------------------------
    CNOT(Error_vector, 11, 9);
    CNOT(Error_vector, 11, 10);
    
    
    //Number K--------------------------
    
    CNOT(Error_vector, 3, 9);
    
    //Number L--------------------------
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 10);
    Hadamard(Error_vector,2);
    
    //Number M--------------------------
    
    CNOT(Error_vector, 4, 9);
    
    //Number N--------------------------
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 10);
    Hadamard(Error_vector,4);
    
    //----------------------------------
    CNOT(Error_vector, 11, 9);
    CNOT(Error_vector, 11, 10);
    
    
    //Number O--------------------------
    Hadamard(Error_vector,5);
    CNOT(Error_vector, 5, 9);
    Hadamard(Error_vector,5);
    
    //Number P--------------------------
    
    CNOT(Error_vector, 5, 10);
    
    
    //----------------------------------
    
    
    
}


int unflagged_m14(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha ){
	
	

    SQerror(Error_vector, 16, probability*alpha);

    SQerror(Error_vector, 19, probability*alpha);	  
    
    

		
			//===================================================
			//g1 Number 1--------------------------
			Hadamard(Error_vector,1);
            CNOT(Error_vector, 1, 16);
 			Hadamard(Error_vector,1);    		
            TQerror(Error_vector, 1, 16, probability*beta);
		
        	//g4 Number 3--------------------------
			Hadamard(Error_vector,4);
            CNOT(Error_vector, 4, 19);
 			Hadamard(Error_vector,4);    		
            TQerror(Error_vector, 4, 19, probability*beta);
 
 			SQerror(Error_vector, 2, probability*Gamma);
 			SQerror(Error_vector, 3, probability*Gamma);
 			SQerror(Error_vector, 5, probability*Gamma);
 			//===================================================
            
        	//g1 Number 4--------------------------
      		Hadamard(Error_vector,4);
            CNOT(Error_vector, 4, 16);
      		Hadamard(Error_vector,4);
            TQerror(Error_vector, 4, 16, probability*beta);  
        
        	//g4 Number 4--------------------------
            CNOT(Error_vector, 5, 19);
            TQerror(Error_vector, 5, 19, probability*beta);	
            
            
 			SQerror(Error_vector, 1, probability*Gamma);
 			SQerror(Error_vector, 3, probability*Gamma);
			SQerror(Error_vector, 2, probability*Gamma);
 			//===================================================    
	
    	


        	//g1 Number 3--------------------------		
            CNOT(Error_vector, 3, 16);
            TQerror(Error_vector, 3, 16, probability*beta);
        
        	//g4 Number 2--------------------------
      		Hadamard(Error_vector,2);
            CNOT(Error_vector, 2, 19);
      		Hadamard(Error_vector,2);
            TQerror(Error_vector, 2, 19, probability*beta); 
          
			SQerror(Error_vector, 1, probability*Gamma);
 			SQerror(Error_vector, 4, probability*Gamma);
 			SQerror(Error_vector, 5, probability*Gamma);
 			//===================================================
      
        	//g1 Number 2--------------------------
            CNOT(Error_vector, 2, 16);
            TQerror(Error_vector, 2, 16, probability*beta);
        	
			//g4 Number 1--------------------------
			CNOT(Error_vector, 1, 19);
            TQerror(Error_vector, 1, 19, probability*beta);           
    
			SQerror(Error_vector, 3, probability*Gamma);
 			SQerror(Error_vector, 4, probability*Gamma);
 			SQerror(Error_vector, 5, probability*Gamma);
 			//===================================================


    SQerror(Error_vector, 16, probability*alpha);

    SQerror(Error_vector, 19, probability*alpha);	 
    
						Error_vector[0][16] = 0;  // g'5
						Error_vector[0][17] = 0;  // g'3
	
}
int unflagged_3m4(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha ){
    SQerror(Error_vector, 9, probability*alpha);	  
		// g4

			//Number 1--------------------------
			CNOT(Error_vector, 1, 19);
            TQerror(Error_vector, 1, 19, probability*beta);

        //  	SQerror(Error_vector, 1, probability*Gamma);
        	SQerror(Error_vector, 2, probability*Gamma);
        	SQerror(Error_vector, 3, probability*Gamma);
        	SQerror(Error_vector, 4, probability*Gamma);
        	SQerror(Error_vector, 5, probability*Gamma); 
			           
            
        	//Number 2--------------------------
		
      		Hadamard(Error_vector,2);
            CNOT(Error_vector, 2, 19);
      		Hadamard(Error_vector,2);
            TQerror(Error_vector, 2, 19, probability*beta);  	
	

         	SQerror(Error_vector, 1, probability*Gamma);
        //	SQerror(Error_vector, 2, probability*Gamma);
        	SQerror(Error_vector, 3, probability*Gamma);
        	SQerror(Error_vector, 4, probability*Gamma);
        	SQerror(Error_vector, 5, probability*Gamma); 
        	
        	
        	//Number 3--------------------------
			
			Hadamard(Error_vector,4);
            CNOT(Error_vector, 4, 19);
 			Hadamard(Error_vector,4);    		
            TQerror(Error_vector, 4, 19, probability*beta);

         	SQerror(Error_vector, 1, probability*Gamma);
        	SQerror(Error_vector, 2, probability*Gamma);
        	SQerror(Error_vector, 3, probability*Gamma);
        //	SQerror(Error_vector, 4, probability*Gamma);
        	SQerror(Error_vector, 5, probability*Gamma); 
        	
        	
        	//Number 4--------------------------


            CNOT(Error_vector, 5, 19);
            TQerror(Error_vector, 5, 19, probability*beta);	
	
         	SQerror(Error_vector, 1, probability*Gamma);
        	SQerror(Error_vector, 2, probability*Gamma);
        	SQerror(Error_vector, 3, probability*Gamma);
        	SQerror(Error_vector, 4, probability*Gamma);
        //	SQerror(Error_vector, 5, probability*Gamma); 
 
                        Error_vector[0][15] = 0;  // g'1
						Error_vector[0][16] = 0;  // g'5
						Error_vector[0][17] = 1;  // g'3
					//	Error_vector[0][18] = 0;  // g'4
 
}
int unflagged_m34(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha ){



    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);	  
    

			//===================================================
		
        	//g3 Number 2--------------------------
      		Hadamard(Error_vector,3);
            CNOT(Error_vector, 3, 18);
      		Hadamard(Error_vector,3);
            TQerror(Error_vector, 3, 18, probability*beta);  
        	//g4 Number 3--------------------------
			Hadamard(Error_vector,4);
            CNOT(Error_vector, 4, 19);
 			Hadamard(Error_vector,4);    		
            TQerror(Error_vector, 4, 19, probability*beta);
 
 			SQerror(Error_vector, 5, probability*Gamma);
 			SQerror(Error_vector, 2, probability*Gamma);
 			SQerror(Error_vector, 1, probability*Gamma);	
 			//===================================================
            
        
			//g3 Number 1--------------------------
			Hadamard(Error_vector,1);
            CNOT(Error_vector, 1, 18);
 			Hadamard(Error_vector,1);    		
            TQerror(Error_vector, 1, 18, probability*beta);
        	//g4 Number 4--------------------------
            CNOT(Error_vector, 5, 19);
            TQerror(Error_vector, 5, 19, probability*beta);	
	
			SQerror(Error_vector, 2, probability*Gamma);
 			SQerror(Error_vector, 4, probability*Gamma);
 			SQerror(Error_vector, 3, probability*Gamma);
 			//===================================================    
	
    	


        
        	//g3 Number 3--------------------------
            CNOT(Error_vector, 4, 18);
            TQerror(Error_vector, 4, 18, probability*beta);
        	//g4 Number 2--------------------------
      		Hadamard(Error_vector,2);
            CNOT(Error_vector, 2, 19);
      		Hadamard(Error_vector,2);
            TQerror(Error_vector, 2, 19, probability*beta); 
          
			SQerror(Error_vector, 1, probability*Gamma);
 			SQerror(Error_vector, 5, probability*Gamma);
 			SQerror(Error_vector, 3, probability*Gamma);
 			//===================================================
      
             		
        	//g3 Number 4--------------------------
            CNOT(Error_vector, 5, 18);
            TQerror(Error_vector, 5, 18, probability*beta);
			//g4 Number 1--------------------------
			CNOT(Error_vector, 1, 19);
            TQerror(Error_vector, 1, 19, probability*beta);           
    
			SQerror(Error_vector, 3, probability*Gamma);
 			SQerror(Error_vector, 2, probability*Gamma);
 			SQerror(Error_vector, 4, probability*Gamma);		
 			//===================================================
    

    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);
	
                        Error_vector[0][15] = 0;  // g'1
						Error_vector[0][16] = 0;  // g'5	   
        	
}
int unflagged_2m34(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha ){
	
    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);	  
    
    //=========================================================

			//===================================================
		
        	//g3 Number 2--------------------------
      		Hadamard(Error_vector,3);
            CNOT(Error_vector, 3, 18);
      		Hadamard(Error_vector,3);
            TQerror(Error_vector, 3, 18, probability*beta);  
        	//g4 Number 3--------------------------
			Hadamard(Error_vector,4);
            CNOT(Error_vector, 4, 19);
 			Hadamard(Error_vector,4);    		
            TQerror(Error_vector, 4, 19, probability*beta);
 
 			SQerror(Error_vector, 5, probability*Gamma);
 			SQerror(Error_vector, 1, probability*Gamma);
 			SQerror(Error_vector, 2, probability*Gamma);
 			//===================================================
            
        
			//g3 Number 1--------------------------
			Hadamard(Error_vector,1);
            CNOT(Error_vector, 1, 18);
 			Hadamard(Error_vector,1);    		
            TQerror(Error_vector, 1, 18, probability*beta);
        	//g4 Number 4--------------------------
            CNOT(Error_vector, 5, 19);
            TQerror(Error_vector, 5, 19, probability*beta);	
	
			SQerror(Error_vector, 2, probability*Gamma);
 			SQerror(Error_vector, 4, probability*Gamma);
 			SQerror(Error_vector, 3, probability*Gamma);
 			//===================================================    
	
    	


        
        	//g3 Number 3--------------------------
            CNOT(Error_vector, 4, 18);
            TQerror(Error_vector, 4, 18, probability*beta);
        	//g4 Number 2--------------------------
      		Hadamard(Error_vector,2);
            CNOT(Error_vector, 2, 19);
      		Hadamard(Error_vector,2);
            TQerror(Error_vector, 2, 19, probability*beta); 
          
			SQerror(Error_vector, 1, probability*Gamma);
 			SQerror(Error_vector, 5, probability*Gamma);
 			SQerror(Error_vector, 3, probability*Gamma);	
 			//===================================================
      
             		
        	//g3 Number 4--------------------------
            CNOT(Error_vector, 5, 18);
            TQerror(Error_vector, 5, 18, probability*beta);
			//g4 Number 1--------------------------
			CNOT(Error_vector, 1, 19);
            TQerror(Error_vector, 1, 19, probability*beta);           
    
			SQerror(Error_vector, 3, probability*Gamma);
 			SQerror(Error_vector, 2, probability*Gamma);
 			SQerror(Error_vector, 4, probability*Gamma);			
 			//===================================================
    




    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);
	
                        Error_vector[0][15] = 0;  // g'1
						Error_vector[0][16] = 1;  // g'5
	
}
int unflagged_m234(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha ){
	


   
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);	  
    
			//===================================================
			
			//g2 Number 1--------------------------
			Hadamard(Error_vector,2);
            CNOT(Error_vector, 2, 17);
 			Hadamard(Error_vector,2);    		
            TQerror(Error_vector, 2, 17, probability*beta);
        	//g3 Number 2--------------------------
      		Hadamard(Error_vector,3);
            CNOT(Error_vector, 3, 18);
      		Hadamard(Error_vector,3);
            TQerror(Error_vector, 3, 18, probability*beta);  
        	//g4 Number 3--------------------------
			Hadamard(Error_vector,4);
            CNOT(Error_vector, 4, 19);
 			Hadamard(Error_vector,4);    		
            TQerror(Error_vector, 4, 19, probability*beta);
 
 			SQerror(Error_vector, 1, probability*Gamma);
 			SQerror(Error_vector, 5, probability*Gamma);
 			//===================================================
            
        	//g2 Number 2--------------------------
            CNOT(Error_vector, 3, 17);
            TQerror(Error_vector, 3, 17, probability*beta);
			//g3 Number 1--------------------------
			Hadamard(Error_vector,1);
            CNOT(Error_vector, 1, 18);
 			Hadamard(Error_vector,1);    		
            TQerror(Error_vector, 1, 18, probability*beta);
        	//g4 Number 4--------------------------
            CNOT(Error_vector, 5, 19);
            TQerror(Error_vector, 5, 19, probability*beta);	
	
			SQerror(Error_vector, 4, probability*Gamma);
			SQerror(Error_vector, 2, probability*Gamma);
 			//===================================================    
	
    	


        	//g2 Number 4--------------------------
      		Hadamard(Error_vector,5);
            CNOT(Error_vector, 5, 17);
      		Hadamard(Error_vector,5);
            TQerror(Error_vector, 5, 17, probability*beta);  
        	//g3 Number 3--------------------------
            CNOT(Error_vector, 4, 18);
            TQerror(Error_vector, 4, 18, probability*beta);
        	//g4 Number 2--------------------------
      		Hadamard(Error_vector,2);
            CNOT(Error_vector, 2, 19);
      		Hadamard(Error_vector,2);
            TQerror(Error_vector, 2, 19, probability*beta); 
          
          	SQerror(Error_vector, 3, probability*Gamma);
			SQerror(Error_vector, 1, probability*Gamma);
 			//===================================================
      
        
        	//g2 Number 3--------------------------
            CNOT(Error_vector, 4, 17);
            TQerror(Error_vector, 4, 17, probability*beta);  		         		
        	//g3 Number 4--------------------------
            CNOT(Error_vector, 5, 18);
            TQerror(Error_vector, 5, 18, probability*beta);
			//g4 Number 1--------------------------
			CNOT(Error_vector, 1, 19);
            TQerror(Error_vector, 1, 19, probability*beta);   
			
			SQerror(Error_vector, 3, probability*Gamma);        
			SQerror(Error_vector, 2, probability*Gamma);
 			//===================================================


    
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);	   
        	
     Error_vector[0][15] = 0;  // g'1   	
}
int unflagged_1m23(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha ){
	
    
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
  
 
		
			//g2 Number 1--------------------------
			Hadamard(Error_vector,2);
            CNOT(Error_vector, 2, 17);
 			Hadamard(Error_vector,2);    		
            TQerror(Error_vector, 2, 17, probability*beta);
        	//g3 Number 2--------------------------
      		Hadamard(Error_vector,3);
            CNOT(Error_vector, 3, 18);
      		Hadamard(Error_vector,3);
            TQerror(Error_vector, 3, 18, probability*beta);  
        
			SQerror(Error_vector, 1, probability*Gamma);
			SQerror(Error_vector, 4, probability*Gamma);
 			SQerror(Error_vector, 5, probability*Gamma);
 			//===================================================
            
        
        	//g2 Number 2--------------------------
            CNOT(Error_vector, 3, 17);
            TQerror(Error_vector, 3, 17, probability*beta);
			//g3 Number 1--------------------------
			Hadamard(Error_vector,1);
            CNOT(Error_vector, 1, 18);
 			Hadamard(Error_vector,1);    		
            TQerror(Error_vector, 1, 18, probability*beta);
        
			SQerror(Error_vector, 5, probability*Gamma);
			SQerror(Error_vector, 4, probability*Gamma);
			SQerror(Error_vector, 2, probability*Gamma);
 			//===================================================    
	
    	


        
        	//g2 Number 4--------------------------
      		Hadamard(Error_vector,5);
            CNOT(Error_vector, 5, 17);
      		Hadamard(Error_vector,5);
            TQerror(Error_vector, 5, 17, probability*beta);  
        	//g3 Number 3--------------------------
            CNOT(Error_vector, 4, 18);
            TQerror(Error_vector, 4, 18, probability*beta);
        
			SQerror(Error_vector, 1, probability*Gamma);
			SQerror(Error_vector, 2, probability*Gamma);
			SQerror(Error_vector, 3, probability*Gamma);
 			//===================================================
      
        
        	//g2 Number 3--------------------------
            CNOT(Error_vector, 4, 17);
            TQerror(Error_vector, 4, 17, probability*beta);  		         		
        	//g3 Number 4--------------------------
            CNOT(Error_vector, 5, 18);
            TQerror(Error_vector, 5, 18, probability*beta);
		   
			SQerror(Error_vector, 1, probability*Gamma);
			SQerror(Error_vector, 2, probability*Gamma);
			SQerror(Error_vector, 3, probability*Gamma);
 			//===================================================


  
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
                        Error_vector[0][15] = 1;  // g'1
					
						Error_vector[0][18] = 0;  // g'4
     		
}
int unflagged_m123(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha ){


    SQerror(Error_vector, 16, probability*alpha);
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
    
    
			//===================================================
			//g1 Number 1--------------------------
			Hadamard(Error_vector,1);
            CNOT(Error_vector, 1, 16);
 			Hadamard(Error_vector,1);    		
            TQerror(Error_vector, 1, 16, probability*beta);
			//g2 Number 1--------------------------
			Hadamard(Error_vector,2);
            CNOT(Error_vector, 2, 17);
 			Hadamard(Error_vector,2);    		
            TQerror(Error_vector, 2, 17, probability*beta);
        	//g3 Number 2--------------------------
      		Hadamard(Error_vector,3);
            CNOT(Error_vector, 3, 18);
      		Hadamard(Error_vector,3);
            TQerror(Error_vector, 3, 18, probability*beta);  
        
 			SQerror(Error_vector, 4, probability*Gamma);
 			SQerror(Error_vector, 5, probability*Gamma);
 			//===================================================
            
        	//g1 Number 4--------------------------
      		Hadamard(Error_vector,4);
            CNOT(Error_vector, 4, 16);
      		Hadamard(Error_vector,4);
            TQerror(Error_vector, 4, 16, probability*beta);  
        	//g2 Number 2--------------------------
            CNOT(Error_vector, 3, 17);
            TQerror(Error_vector, 3, 17, probability*beta);
			//g3 Number 1--------------------------
			Hadamard(Error_vector,1);
            CNOT(Error_vector, 1, 18);
 			Hadamard(Error_vector,1);    		
            TQerror(Error_vector, 1, 18, probability*beta);
        	
 			SQerror(Error_vector, 5, probability*Gamma);
			SQerror(Error_vector, 2, probability*Gamma);
 			//===================================================    
	
    	


        	//g1 Number 3--------------------------		
            CNOT(Error_vector, 3, 16);
            TQerror(Error_vector, 3, 16, probability*beta);
        	//g2 Number 4--------------------------
      		Hadamard(Error_vector,5);
            CNOT(Error_vector, 5, 17);
      		Hadamard(Error_vector,5);
            TQerror(Error_vector, 5, 17, probability*beta);  
        	//g3 Number 3--------------------------
            CNOT(Error_vector, 4, 18);
            TQerror(Error_vector, 4, 18, probability*beta);
        
 			SQerror(Error_vector, 2, probability*Gamma);
			SQerror(Error_vector, 1, probability*Gamma);
 			//===================================================
      
        	//g1 Number 2--------------------------
            CNOT(Error_vector, 2, 16);
            TQerror(Error_vector, 2, 16, probability*beta);
        	//g2 Number 3--------------------------
            CNOT(Error_vector, 4, 17);
            TQerror(Error_vector, 4, 17, probability*beta);  		         		
        	//g3 Number 4--------------------------
            CNOT(Error_vector, 5, 18);
            TQerror(Error_vector, 5, 18, probability*beta);
			        
 			SQerror(Error_vector, 1, probability*Gamma);
			SQerror(Error_vector, 3, probability*Gamma);
 			//===================================================

	//=========================================================		


    SQerror(Error_vector, 16, probability*alpha);
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
  	 
	Error_vector[0][18] = 0;  // g'4
}
 
int unflagged_4m1(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha ){
	
	
SQerror(Error_vector, 16, probability*alpha);


			// g1

			//Number 1--------------------------
			Hadamard(Error_vector,1);
            CNOT(Error_vector, 1, 16);
 			Hadamard(Error_vector,1);    		
            TQerror(Error_vector, 1, 16, probability*beta);

        // 	SQerror(Error_vector, 1, probability*Gamma);
        	SQerror(Error_vector, 2, probability*Gamma);
        	SQerror(Error_vector, 3, probability*Gamma);
        	SQerror(Error_vector, 4, probability*Gamma);
        	SQerror(Error_vector, 5, probability*Gamma);   
            
        	//Number 2--------------------------
		

            CNOT(Error_vector, 2, 16);
            TQerror(Error_vector, 2, 16, probability*beta);

         	SQerror(Error_vector, 1, probability*Gamma);
        //	SQerror(Error_vector, 2, probability*Gamma);
        	SQerror(Error_vector, 3, probability*Gamma);
        	SQerror(Error_vector, 4, probability*Gamma);
        	SQerror(Error_vector, 5, probability*Gamma); 
        	
        	//Number 3--------------------------
			
            CNOT(Error_vector, 3, 16);
            TQerror(Error_vector, 3, 16, probability*beta);

         	SQerror(Error_vector, 1, probability*Gamma);
        	SQerror(Error_vector, 2, probability*Gamma);
        //	SQerror(Error_vector, 3, probability*Gamma);
        	SQerror(Error_vector, 4, probability*Gamma);
        	SQerror(Error_vector, 5, probability*Gamma); 
        	
        	//Number 4--------------------------
      		Hadamard(Error_vector,4);
            CNOT(Error_vector, 4, 16);
      		Hadamard(Error_vector,4);
            TQerror(Error_vector, 4, 16, probability*beta);     		         		

         	SQerror(Error_vector, 1, probability*Gamma);
        	SQerror(Error_vector, 2, probability*Gamma);
        	SQerror(Error_vector, 3, probability*Gamma);
        //	SQerror(Error_vector, 4, probability*Gamma);
        	SQerror(Error_vector, 5, probability*Gamma); 
        	
SQerror(Error_vector, 16, probability*alpha);

                      //  Error_vector[0][15] = 1;  // g'1
						Error_vector[0][16] = 0;  // g'5
						Error_vector[0][17] = 0;  // g'3
						Error_vector[0][18] = 1;  // g'4	
} 





/* 
int unflagged_m14(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){
    
    
    SQerror(Error_vector, 16, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);
    
    
    
    //===================================================
    //g1 Number 1--------------------------
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 16);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 16, probability*beta);
    
    //g4 Number 3--------------------------
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 19);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 19, probability*beta);
    
    
    //SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    //g1 Number 4--------------------------
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 16);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 16, probability*beta);
    
    //g4 Number 4--------------------------
    CNOT(Error_vector, 5, 19);
    TQerror(Error_vector, 5, 19, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //SQerror(Error_vector, 4, probability*Gamma);
    //SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    
    
    
    //g1 Number 3--------------------------
    CNOT(Error_vector, 3, 16);
    TQerror(Error_vector, 3, 16, probability*beta);
    
    //g4 Number 2--------------------------
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 19);
    Hadamard(Error_vector,2);
    TQerror(Error_vector, 2, 19, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    //SQerror(Error_vector, 2, probability*Gamma);
    //SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    //g1 Number 2--------------------------
    CNOT(Error_vector, 2, 16);
    TQerror(Error_vector, 2, 16, probability*beta);
    
    //g4 Number 1--------------------------
    CNOT(Error_vector, 1, 19);
    TQerror(Error_vector, 1, 19, probability*beta);
    
    //SQerror(Error_vector, 1, probability*Gamma);
    //SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    // Measurement error
    SQerror(Error_vector, 16, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);
    
    
    Error_vector[0][16] = 0;
    Error_vector[0][17] = 0;
    
    
}

int unflagged_m34(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){
    
    
    
    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);
    
    
    //===================================================
    
    //g3 Number 2--------------------------
    Hadamard(Error_vector,3);
    CNOT(Error_vector, 3, 18);
    Hadamard(Error_vector,3);
    TQerror(Error_vector, 3, 18, probability*beta);
    //g4 Number 3--------------------------
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 19);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 19, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //SQerror(Error_vector, 3, probability*Gamma);
    //SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    
    //g3 Number 1--------------------------
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 18);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 18, probability*beta);
    //g4 Number 4--------------------------
    CNOT(Error_vector, 5, 19);
    TQerror(Error_vector, 5, 19, probability*beta);
    
    SQerror(Error_vector, 2, probability*Gamma);
    //===================================================
    
    
    //g3 Number 3--------------------------
    CNOT(Error_vector, 4, 18);
    TQerror(Error_vector, 4, 18, probability*beta);
    //g4 Number 2--------------------------
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 19);
    Hadamard(Error_vector,2);
    TQerror(Error_vector, 2, 19, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    //SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    //g3 Number 4--------------------------
    CNOT(Error_vector, 5, 18);
    TQerror(Error_vector, 5, 18, probability*beta);
    //g4 Number 1--------------------------
    CNOT(Error_vector, 1, 19);
    TQerror(Error_vector, 1, 19, probability*beta);
    
    //SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    //SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    // Measurement error
    
    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);
    
    Error_vector[0][15] = 0;
    Error_vector[0][16] = 0;
    
}

int unflagged_m24(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){
    
    Error_vector[0][15] = 0;
    Error_vector[0][16] = 1;  // g'2
    Error_vector[0][17] = 0;
    Error_vector[0][18] = 1;  // g'4
    
    
}

int unflagged_m23(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){
    Error_vector[0][15] = 0;
    Error_vector[0][16] = 1;  // g'2
    Error_vector[0][17] = 1;  // g'3
    Error_vector[0][18] = 0;
    
}

int unflagged_m234(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){
    
    
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);
    
    
    //===================================================
    
    //g2 Number 1--------------------------
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 17);
    Hadamard(Error_vector,2);
    TQerror(Error_vector, 2, 17, probability*beta);
    //g3 Number 2--------------------------
    Hadamard(Error_vector,3);
    CNOT(Error_vector, 3, 18);
    Hadamard(Error_vector,3);
    TQerror(Error_vector, 3, 18, probability*beta);
    //g4 Number 3--------------------------
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 19);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 19, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    //SQerror(Error_vector, 2, probability*Gamma);
    //SQerror(Error_vector, 3, probability*Gamma);
    //SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    
    //g2 Number 2--------------------------
    CNOT(Error_vector, 3, 17);
    TQerror(Error_vector, 3, 17, probability*beta);
    //g3 Number 1--------------------------
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 18);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 18, probability*beta);
    //g4 Number 4--------------------------
    CNOT(Error_vector, 5, 19);
    TQerror(Error_vector, 5, 19, probability*beta);
    
    //SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    //SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    
    
    //g2 Number 4--------------------------
    Hadamard(Error_vector,5);
    CNOT(Error_vector, 5, 17);
    Hadamard(Error_vector,5);
    TQerror(Error_vector, 5, 17, probability*beta);
    //g3 Number 3--------------------------
    CNOT(Error_vector, 4, 18);
    TQerror(Error_vector, 4, 18, probability*beta);
    //g4 Number 2--------------------------
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 19);
    Hadamard(Error_vector,2);
    TQerror(Error_vector, 2, 19, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    //SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //SQerror(Error_vector, 4, probability*Gamma);
    //SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    
    //g2 Number 3--------------------------
    CNOT(Error_vector, 4, 17);
    TQerror(Error_vector, 4, 17, probability*beta);
    //g3 Number 4--------------------------
    CNOT(Error_vector, 5, 18);
    TQerror(Error_vector, 5, 18, probability*beta);
    //g4 Number 1--------------------------
    CNOT(Error_vector, 1, 19);
    TQerror(Error_vector, 1, 19, probability*beta);
    
    //SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //SQerror(Error_vector, 4, probability*Gamma);
    //SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    // Measurement error
    
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);
    
    Error_vector[0][15] = 0 ;
    
    
}

int unflagged_m13(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){
    
    Error_vector[0][15] = 1;  // g'1
    Error_vector[0][16] = 0;
    Error_vector[0][17] = 1;  // g'3
    Error_vector[0][18] = 0;
    
    
}

int unflagged_m12(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){
    
    Error_vector[0][15] = 1;  // g'1
    Error_vector[0][16] = 1;  // g'2
    Error_vector[0][17] = 0;
    Error_vector[0][18] = 0;
    
}

int unflagged_m123(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){
    
    
    
    SQerror(Error_vector, 16, probability*alpha);
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
    
    
    
    //===================================================
    //g1 Number 1--------------------------
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 16);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 16, probability*beta);
    //g2 Number 1--------------------------
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 17);
    Hadamard(Error_vector,2);
    TQerror(Error_vector, 2, 17, probability*beta);
    //g3 Number 2--------------------------
    Hadamard(Error_vector,3);
    CNOT(Error_vector, 3, 18);
    Hadamard(Error_vector,3);
    TQerror(Error_vector, 3, 18, probability*beta);
    
    
    //SQerror(Error_vector, 1, probability*Gamma);
    //SQerror(Error_vector, 2, probability*Gamma);
    //SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    //g1 Number 4--------------------------
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 16);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 16, probability*beta);
    //g2 Number 2--------------------------
    CNOT(Error_vector, 3, 17);
    TQerror(Error_vector, 3, 17, probability*beta);
    //g3 Number 1--------------------------
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 18);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 18, probability*beta);
    
    
    //SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //SQerror(Error_vector, 3, probability*Gamma);
    //SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    
    //g1 Number 3--------------------------
    CNOT(Error_vector, 3, 16);
    TQerror(Error_vector, 3, 16, probability*beta);
    //g2 Number 4--------------------------
    Hadamard(Error_vector,5);
    CNOT(Error_vector, 5, 17);
    Hadamard(Error_vector,5);
    TQerror(Error_vector, 5, 17, probability*beta);
    //g3 Number 3--------------------------
    CNOT(Error_vector, 4, 18);
    TQerror(Error_vector, 4, 18, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //SQerror(Error_vector, 3, probability*Gamma);
    //SQerror(Error_vector, 4, probability*Gamma);
    //SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    //g1 Number 2--------------------------
    CNOT(Error_vector, 2, 16);
    TQerror(Error_vector, 2, 16, probability*beta);
    //g2 Number 3--------------------------
    CNOT(Error_vector, 4, 17);
    TQerror(Error_vector, 4, 17, probability*beta);
    //g3 Number 4--------------------------
    CNOT(Error_vector, 5, 18);
    TQerror(Error_vector, 5, 18, probability*beta);
    
    
    SQerror(Error_vector, 1, probability*Gamma);
    //SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //SQerror(Error_vector, 4, probability*Gamma);
    //SQerror(Error_vector, 5, probability*Gamma);
    //===================================================
    
    // Measurement error
    SQerror(Error_vector, 16, probability*alpha);
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
    
    
    Error_vector[0][18] = 0;
}

int unflagged_m1(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){  // g1
    
    
    SQerror(Error_vector, 16, probability*alpha);
    // g1
    
    //Number 1--------------------------
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 16);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 16, probability*beta);
    
    // 	SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 2--------------------------
    
    
    CNOT(Error_vector, 2, 16);
    TQerror(Error_vector, 2, 16, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    //	SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 3--------------------------
    
    CNOT(Error_vector, 3, 16);
    TQerror(Error_vector, 3, 16, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //	SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 4--------------------------
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 16);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 16, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //	SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    SQerror(Error_vector, 16, probability*alpha);
}


int unflagged_m2(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){  // g2
    
    
    
    SQerror(Error_vector, 17, probability*alpha);
    
    // g2
    
    //Number 1--------------------------
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 17);
    Hadamard(Error_vector,2);
    TQerror(Error_vector, 2, 17, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    //	SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 2--------------------------
    
    
    CNOT(Error_vector, 3, 17);
    TQerror(Error_vector, 3, 17, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //	SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 3--------------------------
    
    CNOT(Error_vector, 4, 17);
    TQerror(Error_vector, 4, 17, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //	SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 4--------------------------
    Hadamard(Error_vector,5);
    CNOT(Error_vector, 5, 17);
    Hadamard(Error_vector,5);
    TQerror(Error_vector, 5, 17, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    //	SQerror(Error_vector, 5, probability*Gamma);
    
    SQerror(Error_vector, 17, probability*alpha);
}


int unflagged_m3(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){  // g3
    
    
    
    SQerror(Error_vector, 18, probability*alpha);
    
// g3
    
    //Number 1--------------------------
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 18);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 18, probability*beta);
    
    // 	SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 2--------------------------
    
    Hadamard(Error_vector,3);
    CNOT(Error_vector, 3, 18);
    Hadamard(Error_vector,3);
    TQerror(Error_vector, 3, 18, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //	SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 3--------------------------
    
    CNOT(Error_vector, 4, 18);
    TQerror(Error_vector, 4, 18, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //	SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 4--------------------------
    
    
    CNOT(Error_vector, 5, 18);
    TQerror(Error_vector, 5, 18, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    //	SQerror(Error_vector, 5, probability*Gamma);
    
    SQerror(Error_vector, 18, probability*alpha);
}


int unflagged_m4(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){  // g4
    
    
    
    
    SQerror(Error_vector, 19, probability*alpha);
    
    
    
    
    // g4
    
    //Number 1--------------------------
    CNOT(Error_vector, 1, 19);
    TQerror(Error_vector, 1, 19, probability*beta);
    
    //  	SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 2--------------------------
    
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 19);
    Hadamard(Error_vector,2);
    TQerror(Error_vector, 2, 19, probability*beta);
    
    
    SQerror(Error_vector, 1, probability*Gamma);
    //	SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 3--------------------------
    
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 19);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 19, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //	SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 4--------------------------
    
    
    CNOT(Error_vector, 5, 19);
    TQerror(Error_vector, 5, 19, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    //	SQerror(Error_vector, 5, probability*Gamma);
    
    SQerror(Error_vector, 19, probability*alpha);
}
*/

//----------------------------------------------------------------------------
int unflagged_s(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){  // g1,2,3,4
    
    for(int i=0; i<2; i++){
        for(int j=5; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
    }
    
    SQerror(Error_vector, 16, probability*alpha);
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);
    
    
    
    // g1
    
    //Number 1--------------------------
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 16);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 16, probability*beta);
    
    // 	SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 2--------------------------
    
    
    CNOT(Error_vector, 2, 16);
    TQerror(Error_vector, 2, 16, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    //	SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 3--------------------------
    
    CNOT(Error_vector, 3, 16);
    TQerror(Error_vector, 3, 16, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //	SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 4--------------------------
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 16);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 16, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //	SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    // g2
    
    //Number 1--------------------------
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 17);
    Hadamard(Error_vector,2);
    TQerror(Error_vector, 2, 17, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    //	SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 2--------------------------
    
    
    CNOT(Error_vector, 3, 17);
    TQerror(Error_vector, 3, 17, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //	SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 3--------------------------
    
    CNOT(Error_vector, 4, 17);
    TQerror(Error_vector, 4, 17, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //	SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 4--------------------------
    Hadamard(Error_vector,5);
    CNOT(Error_vector, 5, 17);
    Hadamard(Error_vector,5);
    TQerror(Error_vector, 5, 17, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    //	SQerror(Error_vector, 5, probability*Gamma);
    
    
    // g3
    
    //Number 1--------------------------
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 18);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 18, probability*beta);
    
    // 	SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 2--------------------------
    
    Hadamard(Error_vector,3);
    CNOT(Error_vector, 3, 18);
    Hadamard(Error_vector,3);
    TQerror(Error_vector, 3, 18, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //	SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 3--------------------------
    
    CNOT(Error_vector, 4, 18);
    TQerror(Error_vector, 4, 18, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //	SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 4--------------------------
    
    
    CNOT(Error_vector, 5, 18);
    TQerror(Error_vector, 5, 18, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    //	SQerror(Error_vector, 5, probability*Gamma);
    
    
    // g4
    
    //Number 1--------------------------
    CNOT(Error_vector, 1, 19);
    TQerror(Error_vector, 1, 19, probability*beta);
    
    //  	SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 2--------------------------
    
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 19);
    Hadamard(Error_vector,2);
    TQerror(Error_vector, 2, 19, probability*beta);
    
    
    SQerror(Error_vector, 1, probability*Gamma);
    //	SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 3--------------------------
    
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 19);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 19, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //	SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 4--------------------------
    
    
    CNOT(Error_vector, 5, 19);
    TQerror(Error_vector, 5, 19, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    //	SQerror(Error_vector, 5, probability*Gamma);
    
    // Measurement error
    SQerror(Error_vector, 16, probability*alpha);
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);
    
}

int unflagged_v(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){  // g1,5,3,4
    
    
    SQerror(Error_vector, 16, probability*alpha);
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);
    
    
    // g1
    
    //Number 1--------------------------
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 16);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 16, probability*beta);
    
    // 	SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 2--------------------------
    
    
    CNOT(Error_vector, 2, 16);
    TQerror(Error_vector, 2, 16, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    //	SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 3--------------------------
    
    CNOT(Error_vector, 3, 16);
    TQerror(Error_vector, 3, 16, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //	SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 4--------------------------
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 16);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 16, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //	SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    // g5
    
    //Number 1--------------------------
    
    CNOT(Error_vector, 1, 17);
    TQerror(Error_vector, 1, 17, probability*beta);
    
    // 	SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 2--------------------------
    
    
    CNOT(Error_vector, 2, 17);
    TQerror(Error_vector, 2, 17, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    //	SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 3--------------------------
    Hadamard(Error_vector,3);
    CNOT(Error_vector, 3, 17);
    Hadamard(Error_vector,3);
    TQerror(Error_vector, 3, 17, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //	SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 4--------------------------
    Hadamard(Error_vector,5);
    CNOT(Error_vector, 5, 17);
    Hadamard(Error_vector,5);
    TQerror(Error_vector, 5, 17, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    //	SQerror(Error_vector, 5, probability*Gamma);
    
    
    // g3
    
    //Number 1--------------------------
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 18);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 18, probability*beta);
    
    // 	SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    
    //Number 2--------------------------
    
    Hadamard(Error_vector,3);
    CNOT(Error_vector, 3, 18);
    Hadamard(Error_vector,3);
    TQerror(Error_vector, 3, 18, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    //	SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 3--------------------------
    
    CNOT(Error_vector, 4, 18);
    TQerror(Error_vector, 4, 18, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //	SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 4--------------------------
    
    
    CNOT(Error_vector, 5, 18);
    TQerror(Error_vector, 5, 18, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    //	SQerror(Error_vector, 5, probability*Gamma);
    
    
    // g4
    
    //Number 1--------------------------
    CNOT(Error_vector, 1, 19);
    TQerror(Error_vector, 1, 19, probability*beta);
    
    // 	SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    
    //Number 2--------------------------
    
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 19);
    Hadamard(Error_vector,2);
    TQerror(Error_vector, 2, 19, probability*beta);
    
    
    SQerror(Error_vector, 1, probability*Gamma);
    //	SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //Number 3--------------------------
    
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 19);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 19, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    //	SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    //Number 4--------------------------
    
    
    CNOT(Error_vector, 5, 19);
    TQerror(Error_vector, 5, 19, probability*beta);
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    //	SQerror(Error_vector, 5, probability*Gamma);
    
    
    
    // Measurement error
    SQerror(Error_vector, 16, probability*alpha);
    SQerror(Error_vector, 17, probability*alpha);
    SQerror(Error_vector, 18, probability*alpha);
    SQerror(Error_vector, 19, probability*alpha);
    
    
    
}

//----------------------------------------------------------------------------
int circuit(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){
    
    
    SQerror(Error_vector, 6, probability*alpha);
    SQerror(Error_vector, 7, probability*alpha);
    SQerror(Error_vector, 8, probability*alpha);
    SQerror(Error_vector, 9, probability*alpha);
    SQerror(Error_vector, 10, probability*alpha);
    SQerror(Error_vector, 11, probability*alpha);
    SQerror(Error_vector, 12, probability*alpha);
    SQerror(Error_vector, 13, probability*alpha);
    
    
    
    
//電路版本:513_code_parallel_v4.1
    
    
    //step 1----------------------------------------------
    
    //Number A--------------------------
    
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 6);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 6, probability*beta);
    
    
    
    //Number B--------------------------
    
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 7);
    Hadamard(Error_vector,2);
    TQerror(Error_vector, 2, 7, probability*beta);
    
    
    //Number C--------------------------
    
    
    Hadamard(Error_vector,3);
    CNOT(Error_vector, 3, 8);
    Hadamard(Error_vector,3);
    TQerror(Error_vector, 3, 8, probability*beta);
    
    
    
    
    //Number D--------------------------
    
    
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 9);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 9, probability*beta);
    
    
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    //step 2----------------------------------------------
    
    //---a--------------------------------
    CNOT(Error_vector, 10, 6);
    TQerror(Error_vector, 10, 6, probability*beta);
    
    
    
    //---b-------------------------------
    CNOT(Error_vector, 11, 7);
    TQerror(Error_vector, 11, 7, probability*beta);
    
    //---c-------------------------------
    
    CNOT(Error_vector, 12, 8);
    TQerror(Error_vector, 12, 8, probability*beta);
    
    
    //---d-------------------------------
    
    CNOT(Error_vector, 13, 9);
    TQerror(Error_vector, 13, 9, probability*beta);
    
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    
    //step 3----------------------------------------------
    
    //Number E--------------------------
    
    CNOT(Error_vector, 2, 6);
    TQerror(Error_vector, 2, 6, probability*beta);
    
    //Number F--------------------------
    
    
    CNOT(Error_vector, 3, 7);
    TQerror(Error_vector, 3, 7, probability*beta);
    
    
    
    
    //Number G--------------------------
    CNOT(Error_vector, 4, 8);
    TQerror(Error_vector, 4, 8, probability*beta);
    
    
    //Number H--------------------------
    CNOT(Error_vector, 5, 9);
    TQerror(Error_vector, 5, 9, probability*beta);
    
    
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 10, probability*Gamma);
    SQerror(Error_vector, 11, probability*Gamma);
    SQerror(Error_vector, 12, probability*Gamma);
    SQerror(Error_vector, 13, probability*Gamma);
    
    
    //step 4----------------------------------------------
    
    //Number I--------------------------
    
    
    CNOT(Error_vector, 3, 6);
    TQerror(Error_vector, 3, 6, probability*beta);
    
    
    //Number J--------------------------
    
    
    
    CNOT(Error_vector, 4, 7);
    TQerror(Error_vector, 4, 7, probability*beta);
    
    
    
    //Number K--------------------------
    
    
    CNOT(Error_vector, 5, 8);
    TQerror(Error_vector, 5, 8, probability*beta);
    
    
    
    //Number L--------------------------
    
    
    CNOT(Error_vector, 1, 9);
    TQerror(Error_vector, 1, 9, probability*beta);
    
    
    
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 10, probability*Gamma);
    SQerror(Error_vector, 11, probability*Gamma);
    SQerror(Error_vector, 12, probability*Gamma);
    SQerror(Error_vector, 13, probability*Gamma);
    
    
    //step 5----------------------------------------------
    
    //---e--------------------------------
    CNOT(Error_vector, 10, 6);
    TQerror(Error_vector, 10, 6, probability*beta);
    
    
    //---f-------------------------------
    CNOT(Error_vector, 11, 7);
    TQerror(Error_vector, 11, 7, probability*beta);
    
    //---g-------------------------------
    
    CNOT(Error_vector, 12, 8);
    TQerror(Error_vector, 12, 8, probability*beta);
    
    
    //---h-------------------------------
    
    CNOT(Error_vector, 13, 9);
    TQerror(Error_vector, 13, 9, probability*beta);
    
    
    SQerror(Error_vector, 1, probability*Gamma);
    SQerror(Error_vector, 2, probability*Gamma);
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 4, probability*Gamma);
    SQerror(Error_vector, 5, probability*Gamma);
    
    
    
    
    //step 6----------------------------------------------
    
    //Number M--------------------------
    
    
    Hadamard(Error_vector,4);
    CNOT(Error_vector, 4, 6);
    Hadamard(Error_vector,4);
    TQerror(Error_vector, 4, 6, probability*beta);
    
    
    //Number N--------------------------
    
    
    
    Hadamard(Error_vector,5);
    CNOT(Error_vector, 5, 7);
    Hadamard(Error_vector,5);
    TQerror(Error_vector, 5, 7, probability*beta);
    
    
    //Number O--------------------------
    
    Hadamard(Error_vector,1);
    CNOT(Error_vector, 1, 8);
    Hadamard(Error_vector,1);
    TQerror(Error_vector, 1, 8, probability*beta);
    
    
    
    //Number P--------------------------
    
    
    Hadamard(Error_vector,2);
    CNOT(Error_vector, 2, 9);
    Hadamard(Error_vector,2);
    TQerror(Error_vector, 2, 9, probability*beta);
    
    
    
    
    SQerror(Error_vector, 3, probability*Gamma);
    SQerror(Error_vector, 10, probability*Gamma);
    SQerror(Error_vector, 11, probability*Gamma);
    SQerror(Error_vector, 12, probability*Gamma);
    SQerror(Error_vector, 13, probability*Gamma);
    
    
    
    
    
    //---------------------------------------------------
    
    // Measurement error
    
    SQerror(Error_vector, 6, probability*alpha);
    SQerror(Error_vector, 7, probability*alpha);
    SQerror(Error_vector, 8, probability*alpha);
    SQerror(Error_vector, 9, probability*alpha);
    SQerror(Error_vector, 10, probability*alpha);
    SQerror(Error_vector, 11, probability*alpha);
    SQerror(Error_vector, 12, probability*alpha);
    SQerror(Error_vector, 13, probability*alpha);
    
    
    
}





