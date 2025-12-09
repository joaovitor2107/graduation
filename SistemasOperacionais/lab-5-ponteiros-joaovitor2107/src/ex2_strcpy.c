# include <stdio.h>

// Implemente minha_strcpy
char * minha_strcpy (char *destino , const char * origem ) {

    int i = 0;
    while(origem[i] != '\0'){
        destino[i] = origem[i];
        i++;
    }
    destino[i]='\0';

    return destino ;
}


int main () {
    char str1 [50];
    char str2 [] = " Teste de copia de string ";

    minha_strcpy (str1 , str2);
    printf (" String copiada : %s\n", str1);

    return 0;
}
