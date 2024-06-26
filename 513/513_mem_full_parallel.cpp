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

int perfect(int (*Error_vector)[n] );

int syndrome_table[15][4]= { 0 };
int syndrome_table_p[15][4]= { 0 };
int syndrome_table_flag[192][12]= { 0 };
int symdorme_result[4] = { 0 };
int symdorme_result2[12] = { 0 };
int recovery_x[15][5]= { 0 };
int recovery_z[15][5]= { 0 };
int recovery_x_flag[192][5]= { 0 };
int recovery_z_flag[192][5]= { 0 };
int stabilizer_x[4][5]= { 0 }; 
int stabilizer_z[4][5]= { 0 }; 
int test1[4] = { 0 };
int test2[12] = { 0 };
int compare_result;
int table_index;


int main(){

//============================================================================================================================

    
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
   
    ifstream fin5("table_full\\513table_flag.txt");
    if(!fin5) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<=191;i++)
        for(int k=0;k<=11;k++)
            fin5 >> syndrome_table_flag[i][k];
    fin5.close();
    
    
    ifstream fin6("table_full\\recovery_x_flag.txt");
    if(!fin6) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<=191;i++)
        for(int k=0;k<=4;k++)
            fin6 >> recovery_x_flag[i][k];
    fin6.close();
    
    ifstream fin7("table_full\\recovery_z_flag.txt");
    if(!fin7) {
        cout << "無法讀入檔案\n";
        system("pause");
        return 0;
    }
    for(int i=0;i<=191;i++)
        for(int k=0;k<=4;k++)
            fin7 >> recovery_z_flag[i][k];
    fin7.close();
  
    
//============================================================================================================================
    
    
    //counter
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

    
    int N = 16; 
    double Gamma = 1; // gamma = error memory rate of idle qubits 
    double alpha = 10; // measurement error
    double beta = 1;  // CNOT error
    double Display_p[N], Display_e[N], Display_d[N];
    
    cout << "[[5,1,3]] full parallel, memeory threshold" << " ,loop=" << N-1 << " ,gamma, alpha, beta=" << Gamma << alpha << beta << endl << endl << endl;
    
    int index_loop;
    index_loop = 0;
    for(int i=1; i<N; i++){
        

        probability = 0.000001+0.000001*(i-1)*(i*i/2); 
        Total_number = 0; 
        Error_number = 0; 
        while(Total_number<100000000){ 
        //while(Total_number<10000||Error_number<1600){
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
            

            
            circuit(Error_vector, probability, Gamma, beta, alpha );
            
            
            
            
            m1 = Error_vector[0][5]; // g1
            m2 = Error_vector[0][6]; // g2
            m3 = Error_vector[0][7]; // g3
            m4 = Error_vector[0][8]; // g4
            
            f1 = Error_vector[1][9];  // f1
            f2 = Error_vector[1][10]; // f2
            f3 = Error_vector[1][11]; // f1
            f4 = Error_vector[1][12]; // f2
            

            
            
            if ( m1 ==0 && m2 ==0 && m3 ==0 && m4 ==0 && f1 ==0 && f2 ==0 && f3 ==0 && f4 ==0  ){
                goto ckp1;
            }
            
            
            
            
            if ( f1==1 || f2==1 || f3==1 || f4==1){
                
                unflagged_s(Error_vector, probability, Gamma, beta, alpha ); //g1,2,3,4

                
                symdorme_result2[0] = Error_vector[0][5];   // g1
                symdorme_result2[1] = Error_vector[0][6];   // g2
                symdorme_result2[2] = Error_vector[0][7];   // g3
                symdorme_result2[3] = Error_vector[0][8];   // g4
                
                symdorme_result2[4] = Error_vector[1][9];   // f1
                symdorme_result2[5] = Error_vector[1][10];  // f2
                symdorme_result2[6] = Error_vector[1][11];  // f3
                symdorme_result2[7] = Error_vector[1][12];  // f4
                
                symdorme_result2[8] = Error_vector[0][15];  // g'1
                symdorme_result2[9] = Error_vector[0][16];  // g'2
                symdorme_result2[10] = Error_vector[0][17];  // g'3
                symdorme_result2[11] = Error_vector[0][18];  // g'4

                
                //compare test2 and symdorme_result array and get index j
                for (int j=0; j<192; j++){
                    
                    for (int i=0; i<12; i++){
                        test2[i]=syndrome_table_flag[j][i];
                    }
      
                
                    compare_result = memcmp(test2, symdorme_result2,sizeof(test2));
                    
                    if (compare_result == 0) {
                        
                        for (int k=0; k<5; k++){
                            Error_vector[0][k]= (Error_vector[0][k]+recovery_x_flag[j][k])%2;
                            Error_vector[1][k]= (Error_vector[1][k]+recovery_z_flag[j][k])%2;
                        }
            
                        break;
                        
                    }
                    
                }
                goto ckp1;
                
            } // End of if ( f1==1 || f2==1 )
                      
            
            if ( m1==1 || m2==1 || m3==1 || m4==1  ){
                
                for(int i=0; i<2; i++){
                    for(int j=5; j<n; j++)	Error_vector[i][j] = 0; // 在進入新的電路之前, 將error vector歸零 (第一列: 紀錄 X error, 第二列: 紀錄 Z error)
                }
                
                
                unflagged_s(Error_vector, probability, Gamma, beta, alpha ); //g1,2,3,4

                
                symdorme_result[0] = Error_vector[0][15];
                symdorme_result[1] = Error_vector[0][16];
                symdorme_result[2] = Error_vector[0][17];
                symdorme_result[3] = Error_vector[0][18];

                
                //compare test1 and symdorme_result array and get index j
                for (int j=0; j<15; j++){
                    
                    for (int i=0; i<4; i++){
                        test1[i]=syndrome_table[j][i];
                    }
                    
                    if (symdorme_result[0] == 0 &&  symdorme_result[1] == 0 && symdorme_result[2] == 0 && symdorme_result[3] == 0  ){
                        break;
                    }
                    
                    compare_result = memcmp(test1, symdorme_result,sizeof(test1));
                    
                    if (compare_result == 0) {
                     
                        
                        for (int k=0; k<5; k++){
                            Error_vector[0][k]= (Error_vector[0][k]+recovery_x[j][k])%2;
                            Error_vector[1][k]= (Error_vector[1][k]+recovery_z[j][k])%2;
                        }

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

                
                Error_number = Error_number + 1 ;
                
                ckp3:
                    
                    
                    Total_number = Total_number + 1;
                 
                    
        } // while
        
        
        Display_p[i-1] = probability;
        Display_e[i-1] = Error_number/Total_number;
        cout  <<  "No." << i << " Physical error rate : " << probability << "; Error number = " << Error_number << ", total_number = " << Total_number << ", logical error rate : " <<  Error_number/(Total_number) << "    |" << c_time_string ;//<< endl;
        
        
        
        
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
    
    cout << "Gamma = " << Gamma << endl;
    
    
    
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
        
        if(Error_vector[0][a]==1 && Error_vector[1][a]==1 ){  
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






//----------------------------------------------------------------------------
int unflagged_s(int (*Error_vector)[n], double probability, double Gamma, double beta, double alpha){  // g1,2,3,4
    
    
    SQerror(Error_vector, 16, probability);
    SQerror(Error_vector, 17, probability);
    SQerror(Error_vector, 18, probability);
    SQerror(Error_vector, 19, probability);
    
    
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
    
    
    SQerror(Error_vector, 16, probability);
    SQerror(Error_vector, 17, probability);
    SQerror(Error_vector, 18, probability);
    SQerror(Error_vector, 19, probability);
    
    
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
    
    
    SQerror(Error_vector, 6, probability);
    SQerror(Error_vector, 7, probability);
    SQerror(Error_vector, 8, probability);
    SQerror(Error_vector, 9, probability);
    SQerror(Error_vector, 10, probability);
    SQerror(Error_vector, 11, probability);
    SQerror(Error_vector, 12, probability);
    SQerror(Error_vector, 13, probability);
    
    
    
    
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





