#include "racionais.h"
#include <stdlib.h>
#include <stdio.h>

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (long int min, long int max){ 
    return min + rand() % (max+1 - min);
}

/* Maximo Divisor Comum entre a e b.         
 * Calcula o mdc pelo metodo de Euclides.*/
long int mdc (long int a, long int b){ 
    int resto;
  
    if (a==0 || b==0)
        return 0;
  
    resto = a%b;
    while (resto != 0){
        a = b;
        b = resto;
        resto = a%b;
    }
  
    return b;
}

/* Minimo Multiplo Comum entre a e b */
long int mmc (long int a, long int b){ 
    return (a * b) / mdc(a, b);
}

/* Recebe um numero racional e o retorna simplificado no parametro *r.
   Quem chama esta funcao deve garantir que *r seja valido e nao NULL. */
void simplifica_r (struct racional *r){ 
    int valorMdc;

    /* Nao realiza a simplificacao caso o num ou den sejam 0 */
    if(!r->num || !r->den)
        return;

    valorMdc = mdc(r->num, r->den);
    
    r->num = r->num/valorMdc;
    r->den = r->den/valorMdc;

    return;
}

struct racional *cria_r (long int numerador, long int denominador){ 
    struct racional *r;
    
    /*Aloca memoria para o numero racional criado*/
    r = malloc(sizeof(struct racional));

    /*Retorna NULL caso haja falha na alocacao*/
    if(!r)
        return NULL;

    r->num = numerador;
    r->den = denominador;
    simplifica_r(r);

    return r;
}

struct racional *sorteia_r (long int max){ 
    long int num, den;
    struct racional *r;

    /* Gera dois numeros aleatorios para criar um racional */
    num = aleat(-max,max);
    den = aleat(-max,max);
    r = cria_r(num, den);

    /* Verifica se o numero gerado eh valido antes de realizar a simplificacao */
    if(valido_r(r))
        simplifica_r(r);

    return r;
}

void destroi_r (struct racional **r){ 
    free(*r);
    *r = NULL;
}

long int numerador_r (struct racional *r){ 
    return r->num;
}

long int denominador_r (struct racional *r){ 
    return r->den;
}

int valido_r (struct racional *r){ 
    if(r->den)
        return 1;
    return 0;
}

//* Quem chama esta funcao deve garantir que *r seja valido e nao NULL.
struct racional *soma_r (struct racional *r1, struct racional *r2){ 
    struct racional *r3;

    r3 = malloc(sizeof(struct racional));

    /* Retorna NULL caso haja falha na alocacao */
    if(!r3)
        return NULL;

    r3->den = mmc(r1->den, r2->den);
    r3->num = (r3->den/r1->den)*r1->num + (r3->den/r2->den)*r2->num;
    simplifica_r(r3);

    return r3; 
}

struct racional *subtrai_r (struct racional *r1, struct racional *r2){ 
    struct racional *r3;

    r3 = malloc(sizeof(struct racional));

    /* Retorna NULL caso haja falha na alocacao */
    if(!r3)
        return NULL;

    r3->den = mmc(r1->den, r2->den);
    r3->num = (r3->den/r1->den)*r1->num - (r3->den/r2->den)*r2->num;
    simplifica_r(r3);

    return r3;
}

struct racional *multiplica_r (struct racional *r1, struct racional *r2){ 
    struct racional *r3;

    r3 = malloc(sizeof(struct racional));

    /* Retorna NULL caso haja falha na alocacao */
    if(!r3)
        return NULL;

    r3->num = r1->num * r2->num;
    r3->den = r1->den * r2->den;
    simplifica_r(r3);

    return r3;
}
 
struct racional *divide_r (struct racional *r1, struct racional *r2){ 
    struct racional *r3;

    r3 = malloc(sizeof(struct racional));

    r3->num = r1->num * r2->den;
    r3->den = r1->den * r2->num;

    /* Retorna NULL caso haja falha na alocacao */
    if(!r3 || !r3->den)
        return NULL;

    simplifica_r(r3);

    return r3;
} 

// Quem chama esta funcao deve garantir que *r1 e *r2 sejam valido e nao NULL.
int compara_r (struct racional *r1, struct racional *r2){ 
    int multiplo, num1, num2;

    multiplo = mmc(r1->den, r2->den);
    num1 = r1->num * (multiplo / r1->den);
    num2 = r2->num * (multiplo / r2->den); 

    if (num1 < num2)
        return -1;
    else if (num1 == num2)
        return 0;
    else
        return 1;
}

void imprime_r (struct racional *r){ 
    if(!valido_r(r)){
        printf("INVALIDO"); 
        return;
    }

    /* Manipula os sinais do numerador e denominador */
    if((r->num<0 && r->den<0) || (r->num>=0 && r->den<0)){
        r->num *= (-1);
        r->den *= (-1);
    }

    if((r->num == 0) || (r->den==1))
        printf("%ld", r->num);

    else if(r->num == r->den)
        printf("%d", 1); 

    else 
        printf("%ld/%ld", r->num, r->den);
}
