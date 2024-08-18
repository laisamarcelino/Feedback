#include "lista.h"
#include <stdlib.h>

struct lista *lista_cria (){
	struct lista *lista;

	lista = malloc(sizeof(struct lista));

	if (lista == NULL)
		return 0; /* Caso de erro de alocação */

	lista->ini = NULL;
	lista->tamanho = 0; 

	return lista;
}

void lista_destroi (struct lista **lista){
	struct nodo *aux;

	while ((*lista)->ini != NULL){
		aux = (*lista)->ini;
		(*lista)->ini = (*lista)->ini->prox;
		free(aux);
	}

	free(*lista);
	(*lista) = NULL;
	
}

int lista_insere_inicio (struct lista *lista, int chave){
	struct nodo *novo;

	novo = malloc(sizeof(struct nodo));

	if (novo == NULL)
		return 0;

	novo->chave = chave;
	novo->prox = lista->ini;
	lista->ini = novo;
	(lista->tamanho)++;
	
	return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
	struct nodo *novo, *aux;

	novo = malloc(sizeof(struct nodo));

	if (novo == NULL)
		return 0;

	novo->chave = chave;
	novo->prox = NULL;

	if (lista_vazia(lista))
		lista->ini = novo;
	else{
		aux = lista->ini;
		while (aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}

	(lista->tamanho)++;
	
	return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave){
	struct nodo *novo, *aux;

	novo = malloc(sizeof(struct nodo));

	if (novo == NULL)
		return 0;

	novo->chave = chave;

	/* Caso 1: lista vazia ou é 1° elemento*/
	if (lista_vazia(lista) || novo->chave < lista->ini->chave){
		novo->prox = lista->ini;
		lista->ini = novo;
		(lista->tamanho)++;
		return 1;
	}
	
	/* Caso 2: lista possui apenas 1 elemento */
	if (lista_tamanho(lista) == 1){
		novo->prox = NULL;
		lista->ini->prox = novo;
		(lista->tamanho)++;
		return 1;
	}
	
	/* Caso 3: lista possui 2 ou mais elementos */
	aux = lista->ini;
	while (aux->prox != NULL && chave > aux->prox->chave)
		aux = aux->prox;

	novo->prox = aux->prox;
	aux->prox = novo;
	(lista->tamanho)++;

	return 1;
}

int lista_remove_inicio (struct lista *lista, int *chave){
	struct nodo *aux;

	if (lista_vazia(lista))
		return 0;

	*chave = lista->ini->chave;
	aux = lista->ini;
	lista->ini = lista->ini->prox;
	(lista->tamanho)--;
	free(aux);
	aux = NULL;

	return 1;
}

int lista_remove_fim (struct lista *lista, int *chave){
	struct nodo *aux1, *aux2;
	
	if (lista_vazia(lista))
		return 0;
	
	if (lista_tamanho(lista) == 1){
		*chave = lista->ini->chave;
		(lista->tamanho)--;
		free(lista->ini);
		lista->ini = NULL;
		return 1;
	}
	
	aux1 = lista->ini;
	while (aux1->prox != NULL){
		aux2 = aux1;
		aux1 = aux1->prox;
	}
	*chave = aux1->chave;	
	free(aux1);
	aux2->prox = NULL;

	(lista->tamanho)--;
	return 1;
}

int lista_remove_ordenado (struct lista *lista, int chave){ 
	struct nodo *aux1, *aux2;

	if (lista_vazia(lista))
		return 0;

	if (lista_tamanho(lista) == 1){
		aux1 = lista->ini;
		lista->ini = lista->ini->prox;
		free(aux1);
		(lista->tamanho)--;
		return 1;
	}

	aux1 = lista->ini;
	while (aux1->prox != NULL && chave != aux1->prox->chave)
		aux1 = aux1->prox;
	
	aux2 = aux1; 
	aux1 = aux1->prox;
	
	free(aux2);
	(lista->tamanho)--;
	
	return 1;
}

int lista_vazia (struct lista *lista){
	if (!lista->tamanho)
		return 1;
	return 0;
}

int lista_tamanho (struct lista *lista){ /*ok?*/
	return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave){ /*ok?*/
	struct nodo *aux;
	
	if (lista_vazia(lista))
		return 0;
	
	aux = lista->ini;
	while (aux->prox != NULL){
		if (aux->chave == chave){
			return 1;
		}
		aux = aux->prox;
	}
	
	return 0;
}

void lista_inicia_iterador (struct lista *lista){ /*ok?*/
	lista->ptr = lista->ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave){ /*ok?*/
	*chave = lista->ptr->chave;

	if (lista->ptr->prox == NULL) 
		return 0;
	
	lista->ptr = lista->ptr->prox;
	
	return 1;
}
