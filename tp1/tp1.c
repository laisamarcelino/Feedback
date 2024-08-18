#include <stdio.h>
#include "racionais.h"
#include <stdlib.h>

int main()
{
    //inicia a semente randomica
    srand(0);
    int n, max; 
    struct racional r1, r2, rSoma, rSubtrai, rMultiplica, rDivisao;

    scanf("%d %d", &n, &max);

    //verifica se o 0<n<100 e 0<max<30
    if(n<=0 || n>=100 || max<=0 || max>=30)
        return 1;

    for(int i=1; i<=n; i++){
    	printf("%d: ", i);
    	r1 = sorteia_r(max);
    	r2 = sorteia_r(max);

    	if(!valido_r(r1) || !valido_r(r2)){
    		printf("NUMERO INVALIDO\n");
    		return 1;
    	}

    	imprime_r (r1);
    	imprime_r (r2);
        rSoma = soma_r(r1, r2);
        rSubtrai = subtrai_r(r1, r2);
        rMultiplica = multiplica_r(r1, r2);
    	rDivisao = divide_r(r1,r2);

    	imprime_r(rSoma);
    	imprime_r(rSubtrai);
    	imprime_r(rMultiplica);

        //imprime a divisao somente se den != 0
    	if(valido_r(rDivisao))
    		imprime_r(rDivisao);
    	else{
    		printf("DIVISAO INVALIDA\n");
    		return 1;
    	}
    	printf("\n");

    }
  
	return 0;
}
