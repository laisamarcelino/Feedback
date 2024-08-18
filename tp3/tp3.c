/* Arquivo MAIN que usa o TAD racionais */

#include "racionais.h"
#include <stdlib.h>
#include <stdio.h>

/* Imprime os racionais de v */
void imprime_racionais(int n, struct racional *v[]){
    for (int i=0; i<n; i++){
        imprime_r(v[i]);
        printf(" ");
    }
}

/* Troca a posição de dois ponteiros */
void troca(int i, int n, struct racional *v[]){
    struct racional *aux;

    aux = v[i];
    v[i] = v[n];
    v[n] = aux;
}

/* Elimina os racionais invalidos */
int elimina_invalidos(int n, struct racional *v[]){
    int i = 0;

    while (i < n){
        if (valido_r(v[i])){
            i++;
        }
        else if (valido_r(v[n-1])){
            troca(i, n-1, v);
            destroi_r(&v[n-1]);
            n--;
        }
        else {
            destroi_r(&v[n-1]);
            n--;
        }
    }
    return n;
}

/* Retorna o índice do maior racional */
int maximo(int n, struct racional *v[]){
	int maior_r = 0;
    
	for(int i=1; i<n; i++){
		if(compara_r(v[i], v[maior_r]) == 1)
			maior_r = i;
	}
	return maior_r;
}

/* Ordena o vetor */
void ordena_r(int n, struct racional *v[]){
	while (n > 1){
        troca(n-1, maximo(n,v), v);
		n--;
	}
}

/* Calcula e imprime a soma dos racionais utilizando um vetor auxiliar*/
void somatorio_r (int n, struct racional *v[]){
    struct racional **v_aux;
    v_aux = malloc((n+1)*sizeof(struct racional*));

    /* Inicializa o primeiro racional como 0, variável acumulativa*/
    v_aux[0] = cria_r(0,1);

    for (int i=1; i<=n; i++){
        v_aux[i] = soma_r(v_aux[i-1], v[i-1]);
    }
    printf("\na soma de todos os elementos eh: ");
    imprime_r(v_aux[n]);

    /* Libera memória alocada p/ vetor auxiliar*/
    for (int i=0; i<=n; i++){
        destroi_r(&v_aux[i]);
    }
    free(v_aux);
}

int main (){

    srand(0);

    /* vetor de ponteiros para racionais */
    struct racional **v;  /* equivalente a struct racional *v[] */
    int n, novo_n;
    long int num, den;
    scanf("%d", &n);

    /* Aloca a memoria para o criar o vetor de ponteiros */
    v = malloc(n*sizeof(struct racional*));
    
    /* Cria um vetor[n] contendo ponteiros para racionais */
    for (int i=0; i<n; i++){
        scanf("%ld %ld", &num, &den);
        v[i] = cria_r(num, den);
    }

    imprime_racionais(n, v);
    printf("\n");

    novo_n = elimina_invalidos(n,v);
    imprime_racionais(novo_n, v);
    printf("\n");
    
    ordena_r(novo_n,v);
    imprime_racionais(novo_n,v);

    somatorio_r(novo_n,v);

    /* Libera a memoria alocada p/ cada racional em v */
    for (int i=0; i<n; i++){
        destroi_r(&v[i]);
    }

    /* Libera a memoria alocada para o vetor de ponteiros */
    free(v);

    printf("\n");
    return 0;
}