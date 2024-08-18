#include "racionais.h"
#include <stdlib.h>
#include <stdio.h>

// Retorna um numero aleatorio entre min e max, inclusive. 
int aleat (int min, int max){ //ok
	return min + rand() % (max+1 - min);
}

/* 
Maximo Divisor Comum entre a e b      
Calcula o mdc pelo metodo de Euclides 
*/
int mdc (int a, int b){
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

// Minimo Multiplo Comum entre a e b 
int mmc (int a, int b){
	return (a * b) / mdc(a, b);
}

/* Recebe um numero racional e o retorna simplificado.
 * Por exemplo, ao receber 10/8 devera retornar 5/4.
 * Se ambos numerador e denominador forem negativos, devera retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Quem chama esta funcao deve garantir que o racional r eh valido */
void simplifica_r (struct racional *r){
	int valorMdc;

	if(!r->num)
		return;

	valorMdc = mdc(r->num, r->den);
	
	r->num = r->num/valorMdc;
	r->den = r->den/valorMdc;
	
	// Manipula os sinais do numerador e denominador
	if((r->num<0 && r->den<0) || (r->num>=0 && r->den<0)){
		r->num *= (-1);
		r->den *= (-1);
	}

	return;
}

struct racional cria_r (int numerador, int denominador){ 
	struct racional r;

	r.num = numerador;
	r.den = denominador;
	r.valido = r.den != 0; 

	return r;
}

struct racional sorteia_r (int n){ 
	int num, den;
	struct racional r;

	// Gera dois numeros aleatorios para criar um racional
	num = aleat(-n,n);
	den = aleat(-n,n);
	r = cria_r(num, den);

	//verifica se o numero gerado eh valido antes de realizar a simplificacao
	if(valido_r(r))
		simplifica_r(&r);

	return r;
}

// Retorna o numerador do racional r 
int numerador_r (struct racional r){ 
	return r.num;
}

// Retorna o denominador do racional r 
int denominador_r (struct racional r){ 
	return r.den;
}

// Retorna o valor do campo valido da struct
int valido_r (struct racional r){
	if(r.valido)
		return 1;

	return 0;
}

void soma_r (struct racional r1, struct racional r2, struct racional *r3){
	r3->den = mmc(r1.den, r2.den);
	r3->num = (r3->den/r1.den)*r1.num + (r3->den/r2.den)*r2.num;
	r3->valido = 1;
	simplifica_r(r3);

	return;
}

void subtrai_r (struct racional r1, struct racional r2, struct racional *r3){
	r3->den = mmc(r1.den, r2.den);
	r3->num = (r3->den/r1.den)*r1.num - (r3->den/r2.den)*r2.num;
	r3->valido = 1;
	simplifica_r(r3);

	return;
}

void multiplica_r (struct racional r1, struct racional r2, struct racional *r3){
	r3->num = r1.num * r2.num;
	r3->den = r1.den * r2.den;
	r3->valido = 1;
	simplifica_r(r3);

	return;
}

int divide_r (struct racional r1, struct racional r2, struct racional *r3){ 
	
	if (!numerador_r(r2)){
		r3->valido = 0;
		return 0;
	}

	r3->num = r1.num * r2.den;
	r3->den = r1.den * r2.num;
	r3->valido = 1;
	simplifica_r(r3);

	return 1;
	
}

int compara_r (struct racional r1, struct racional r2){ 
	int multiplo = mmc(r1.den, r2.den);

	r1.num *= multiplo / r1.den;
	r2.num *= multiplo / r2.den;

	if (r1.num < r2.num)
		return -1;
	else if (r1.num == r2.num)
		return 0;
	else
		return 1;
}

void imprime_r (struct racional r){ 

	if(!valido_r(r)){
		printf("INVALIDO "); 
		return;
	}

	// Manipula sinais e simplifica o numerador
	simplifica_r(&r);

	if((r.num == 0) || (r.den==1))
		printf("%d ", r.num);

	else if(r.num == r.den)
		printf("%d ", 1); 

	else
		printf("%d/%d ", r.num, r.den);
}