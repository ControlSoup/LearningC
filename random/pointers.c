#include <stdio.h>

typedef struct{
    int a;
} TestStruct;

void no_update_TestSruct(TestStruct mystruct){
    mystruct.a += 1;
}

void update_TestStruct(TestStruct *ptr_mystruct){
    ptr_mystruct->a += 1;
}

void not_count_int(int i){
    i += 1;
}

void count_int(int *i){
    *i += 1;
}

void count_array(int *array, int length){
    for(int i = 0; i<length; i++){
        array[i] += 1;
    }
}

int main(){
   // This should not work

    int i[6] = {1,2,3,4,5,6};

    for(int l = 0; l < 6; l++){
      printf("befor: %d\n", i[l]);
    }

    count_array(i, 6);

    for(int l = 0; l < 6; l++){
      printf("after: %d\n", i[l]);
    }
}