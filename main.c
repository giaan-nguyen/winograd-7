//
//  main.c
//  winograd7
//
//  Created by Giaan Nguyen on 2/16/21.
//  Copyright © 2021 Giaan Nguyen. All rights reserved.
//

#include <stdio.h>
#include "winograd7.h"

int main(int argc, const char * argv[]) {
    int i;
    float x[7];
    struct complex X_dft[7]={0};
    printf("Please input a 7-point real sequence, separated by commas or newlines:\n");
    for(i = 0; i < 7; i++){
        scanf("%f,", &x[i]);
    }
    wino7(x, X_dft);
    return 0;
}
