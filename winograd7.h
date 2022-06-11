//
//  winograd7.h
//  winograd7

struct complex{
    float real;
    float imag;
};

void wino7(float x_seq[7], struct complex *X_fft)
{
    // Define diagonal entries of matrix D
    int i,j,k;
    struct complex d[9] = {0};
    d[0].real = 1;
    d[1].real = -1.1667;
    d[2].real = 0.3392;
    d[3].real = -0.3951;
    d[4].real = 0.8460;
    d[5].imag = -0.4410;
    d[6].imag = 0.1705;
    d[7].imag = -0.7044;
    d[8].imag = 0.1931;
    struct complex D[9][9] = {0};
    for(i = 0; i < 9; i++){
        D[i][i].real = d[i].real;
        D[i][i].imag = d[i].imag;
    }
    
    // Define matrix A
    int A[9][7] = {0}; // initialize and also set zeros for column 0
    for(j = 0; j < 7; j++){
        A[0][j] = 1; // set ones for row 0
    }
    for(j = 1; j < 7; j++){
        A[1][j] = 1; // set ones for row 1
    }
    for(i = 0; i < 9; i++){
        A[i][1] = 1; // set ones for column 1
    }
    for(i = 0; i < 5; i++){
        A[i][6] = 1; // set ones for first part of column 6
    }
    for(i = 5; i < 9; i++){
        A[i][6] = -1; // set -1 for second part of column 6
    }
    A[2][3] = -1;
    A[2][4] = -1;
    A[3][2] = -2;
    A[3][3] = 1;
    A[3][4] = 1;
    A[3][5] = -2;
    A[4][2] = -1;
    A[4][5] = -1;
    A[5][2] = 1;
    A[5][3] = -1;
    A[5][4] = 1;
    A[5][5] = -1;
    A[6][2] = -2;
    A[6][3] = -1;
    A[6][4] = 1;
    A[6][5] = 2;
    A[7][3] = 1;
    A[7][4] = -1;
    A[8][2] = -1;
    A[8][5] = 1;
    
    // Multiply D*A, (9x9)*(9x7) => (9x7)
    struct complex DA[9][7] = {0};
    for(i = 0; i < 9; i++){
        for(j = 0; j < 7; j++){
            DA[i][j].real = d[i].real * A[i][j];
            DA[i][j].imag = d[i].imag * A[i][j];
        }
    }
    
    // Multiply A^T*D*A = W, (9x7)^T * (9x7) => (7x7)
    struct complex W[7][7] = {0};
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            for(k = 0; k < 9; k++){
                W[i][j].real += A[k][i] * DA[k][j].real;
                W[i][j].imag += A[k][i] * DA[k][j].imag;
            }
        }
    }
    
    // Multiply W by x
    for(i = 0; i < 7; i++){
        X_fft[i].real = 0; // in case X_fft is not init to 0 when function called
        X_fft[i].imag = 0;
        for(j = 0; j < 7; j++){
            X_fft[i].real += W[i][j].real * x_seq[j];
            X_fft[i].imag += W[i][j].imag * x_seq[j];
        }
    }
    
    // Print results
    printf("The 7-point DFT is:\n");
    for(i = 0; i < 7; i++){
        printf("%.4f + %.4f j\n", X_fft[i].real, X_fft[i].imag);
    }
    return;
}
