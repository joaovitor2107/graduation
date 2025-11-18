#include <stdio.h>
#include <stdlib.h>

void swp(int *a, int  *b){
   *a = *b + *a;
   *b = *a - *b;
   *a = *a - *b;
}

void cria_heap_max(int size, int *vec){
    for(int iterator = size/2; iterator > 0; iterator--){
        int i = iterator;
        while(i){
            if(i*2 > size-1) break;
            if(i*2+1 <= size-1){
                if(vec[i] > vec[i*2] && vec[i] > vec[i*2+1]) break;
                if(vec[i*2] > vec[i*2+1]){
                    swp(&vec[i], &vec[i*2]);
                    i *= 2;
                }
                else{
                    swp(&vec[i], &vec[i*2+1]);
                    i = i*2 + 1;
                }
            }
            else{
                if(vec[i] > vec[i*2]) break;
                else swp(&vec[i], &vec[i*2]);
                i *= 2;
            }
        }

    }
}

int main(){

    int size;
    scanf("%d", &size);
    size++;
    int *vec;
    vec = (int*) malloc(sizeof(int)*size);

    int elem;
    for(int i = 1; i < size; i++){
        scanf("%d", &elem);
        vec[i] = elem;
    }

    cria_heap_max(size, vec);

    printf("[");
    for(int i = 1; i < size; i++){
        if(i == size-1) printf("%d", vec[i]);
        else printf("%d,",vec[i]);

    }
    printf("]\n");


    return 0;
}
