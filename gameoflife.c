#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int** criamatriz(int linhas, int colunas, FILE * fp){ //cria matriz direto do arquivo alocando memoria com duas linhas e duas colunas a mais
    int i,j;
    int **gi = (int**)malloc((linhas+2) * sizeof(int*));
    for(i = 0; i<linhas+2; i++)
        gi[i] = (int*)malloc((colunas+2) * sizeof(int));
    for(i = 0; i<linhas+2; i++){
        for(j = 0; j<colunas+2; j++){
            gi[i][j] = 0;
            }
        }
    for(i = 1; i<=linhas; i++){
        for(j = 1; j<=colunas; j++){
            fscanf(fp, "%d ", &gi[i][j]);
        }
    }
    return gi;
}
int contavizinhos(int i, int j, int** gi){ //acha o numero de vizinhos
    int vizinhos = 0;
    if(gi[i-1][j-1] == 1)
        vizinhos++;
    if(gi[i-1][j] == 1)
        vizinhos++;
    if(gi[i-1][j+1] == 1)
        vizinhos++;
    if(gi[i][j-1] == 1)
        vizinhos++;
    if(gi[i][j+1] == 1)
        vizinhos++;
    if(gi[i+1][j-1] == 1)
        vizinhos++;
    if(gi[i+1][j] == 1)
        vizinhos++;
    if(gi[i+1][j+1] == 1)
        vizinhos++;
    return vizinhos;
}
int** proximageracao(int** gi, int linhas, int colunas){
    int i, j;
    int **gf = (int**)malloc((linhas+2) * sizeof(int*));
    for(i = 0; i<linhas+2; i++)
        gf[i] = (int*)malloc((colunas+2) * sizeof(int));
    for(i = 0; i<linhas+2; i++){
        for(j = 0; j<colunas+2; j++){
            gf[i][j] = 0;
            }
        }
    for(i = 1; i <= linhas; i++){
        for(j = 1; j <= colunas; j++){
            gf[i][j] = contavizinhos(i, j, gi); //gf fica sendo uma matriz onde cada célula é o número de vizinhos em gi
        }
    }
    for(i = 1; i <= linhas; i++){ //a célula da matriz gf recebe 1 ou 0 seguindo as regras do exercicio
        for(j = 1; j <= colunas; j++){
            if(gi[i][j] == 1){
                if(gf[i][j] < 2 || gf[i][j] > 3)
                    gf[i][j] = 0;
                else if(gf[i][j] == 3 || gf[i][j] == 2)
                    gf[i][j] = 1;
            }
            if(gi[i][j] == 0)
                if(gf[i][j] == 3)
                    gf[i][j] = 1;
                else gf[i][j] = gi[i][j];
        }
    }
    return gf;
}
int main(void){
    char c, str[100];
    int n, **gi, i, j, linhas = 0, colunas = 0;
    FILE *fp, *gff;
    printf("\n%c%c%c%c%c%c  JOGO DA VIDA  %c%c%c%c%c%c\n\nDIGITE o nome do arquivo (incluindo .txt).\n",178,178,177,177,176,176,176,176,177,177,178,178);
    gets(str);
    fp = fopen(str, "r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo. Digite ENTER para encerrar.\n");
        getchar();
        return;
    }
    printf("DIGITE 'S' PARA COMECAR");
    fscanf(fp, "%d %d", &linhas, &colunas);
    //cria a matriz e preenche
    gi = criamatriz(linhas, colunas, fp);
    fclose(fp);
    while(1){
        scanf("%c", &c);
       switch(c){
        case('n'):{
                gff = fopen("geracaofinal.txt", "w");
                for(i = 1; i<=linhas; i++){
                    for(j = 1; j<=colunas; j++){
                        fprintf(gff, "%d ", gi[i][j]);
                    }
                    fprintf(gff, "\n");
                }
                fclose(gff);
            for(i = 0; i< linhas; i++)
                free(*gi);
            free(gi);
            return 0;
        }
        case('s'):{
            printf("%c", 201);
            for(j = 1; j<=colunas; j++)
                printf("%c", 205);
            printf("%c\n", 187);
            for(i = 1; i<=linhas; i++){
                printf("%c", 186);
                for(j = 1; j<=colunas; j++){
                        if(gi[i][j] == 0)
                            printf(" ");
                        if(gi[i][j] == 1)
                            printf("*");
                }
                printf("%c\n", 186);
            }
            printf("%c", 200);
            for(j = 1; j<=colunas; j++)
                printf("%c", 205);
            printf("%c\n", 188);
            gi = proximageracao(gi, linhas, colunas);
            printf("DESEJA GERAR A PROXIMA GERACAO?\nSE SIM, DIGITE 'S'\nSE NAO, DIGITE 'N'\nDIGITE 'L' PARA UM LOOP INFINITO.");
            break;
        }
        case('l'):{
            while(1){
                for(i = 1; i<=linhas; i++){
                    printf("%c", 186);
                for(j = 1; j<=colunas; j++){
                        if(gi[i][j] == 0)
                            printf(" ");
                        if(gi[i][j] == 1)
                            printf("*");
                }
                printf("%c\n", 186);
            }
            usleep(41000);
            system("cls");
            gi = proximageracao(gi, linhas, colunas);
            }
        }
    }
    }
}
