#include "racionais.h"
#include <stdlib.h>
#include <stdio.h>

int aleat (int min, int max){ 
	return min + rand() % (max+1 - min);
}

//calculo recursivo do mdc pelo metodo de euclides
int mdc (int a, int b){ 
	int maior = a;
	
	//manipula os sinais para que a=|a| e b=|b|
	if(a<0)
		a *= (-1);
	else if(b<0)
		b *= (-1);

	if(a == b)
		return a;

	if(b>maior){
		maior = b;
		b = a;
	}

	return mdc(b, maior-b);
}

int mmc (int a, int b){ 
	return (a * b) / mdc(a, b);
}

struct racional simplifica_r (struct racional r){
	struct racional r3;

	r3.num = r.num;
	r3.den = r.den;

	//exclui o zero do calculo do mdc
	if(r3.num != 0){
		r3.num = r.num/mdc(r.num, r.den);
		r3.den = r.den/mdc(r.num, r.den);
	}

	//manipula os sinais do numerador e denominador
	if((r3.num<0 && r3.den<0) || (r3.num>=0 && r3.den<0)){
		r3.num *= (-1);
		r3.den *= (-1);
	}

	return r3;
}

struct racional cria_r (int numerador, int denominador){ 
	struct racional r;

	r.num = numerador;
	r.den = denominador;
	r.valido = r.den != 0; 

	return r;
}

struct racional sorteia_r (int n){
	struct racional r;
	int num, den;

	num = aleat(0,n);
	den = aleat(0,n);

	r = cria_r(num, den);
	return r;
}	

void imprime_r (struct racional r){ 

	if(!valido_r(r)){
		printf("INVALIDO "); 
		return;
	}

	r = simplifica_r(r);

	if((r.num == 0) || (r.den==1))
		printf("%d ", r.num);

	else if(r.num == r.den)
		printf("%d ", 1); 

	else
		printf("%d/%d ", r.num, r.den);
}

int valido_r (struct racional r){ 
	if(r.den == 0)
		return 0;
	return 1;
}

struct racional soma_r (struct racional r1, struct racional r2){ 
	struct racional r3;

	r3.den = mmc(r1.den, r2.den);
	r3.num = (r3.den/r1.den)*r1.num + (r3.den/r2.den)*r2.num;
	r3.valido = 1;
	r3 = simplifica_r(r3);

	return r3;
}

struct racional subtrai_r (struct racional r1, struct racional r2){ 
	struct racional r3;

	r3.den = mmc(r1.den, r2.den);
	r3.num = (r3.den/r1.den)*r1.num - (r3.den/r2.den)*r2.num;
	r3.valido = 1;
	r3 = simplifica_r(r3);

	return r3;
}

struct racional multiplica_r (struct racional r1, struct racional r2){
	struct racional r3;

	r3.num = r1.num * r2.num;
	r3.den = r1.den * r2.den;
	r3.valido = 1;
	r3 = simplifica_r(r3);
	
	return r3;	
}

struct racional divide_r (struct racional r1, struct racional r2){
	struct racional r3;

	r3.num = r1.num * r2.den;
	r3.den = r1.den * r2.num;
	r3.valido = r3.den != 0;
	r3 = simplifica_r(r3);

	return r3;
}