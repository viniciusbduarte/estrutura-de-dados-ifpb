/*==============================================================================
 * Nome do Programa: Lista de Funcionários em uma empresa
 
 * Descrição       : Desafio: Crie uma Lista Duplamente Encadeada que armazena 
 * em cada nó o nome de um funcionário, sua ocupação na empresa e o seu salário. 
 * Considere o tamanho da string nome de, no máximo, 30 caracteres. Considere 
 * também que a ocupação seja: Gerente ou Supervisor ou Peão. 
 * A Lista deve inserir os funcionários já Ordenados considerando primeiro a 
 * ocupação (primeiro os Gerentes, depois os Supervisores e, por último, os Peões)	, 
 * e depois os salários (primeiro os Gerentes com maiores salários … por último os
 * Peões com menores salários).
 * 
 * Autor           : Vinicius Batista Duarte
 * Data de Criação : 18/12/24
 * Última Modificação: 18/12/24
 * Versão          : 1.0
 *==============================================================================
 */ 

//========================= BIBLIOTECAS ========================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//========================= CONSTANTES GLOBAIS =================================
#define TAM 30

//========================= ESTRUTURAS =========================================
struct sNODE {
    char nome[TAM], cargo[TAM];
    int salario;  
    struct sNODE *ant;
    struct sNODE *prox;
};

struct sLISTA {
    struct sNODE *ini, *fim;
};

typedef struct sLISTA LISTA;

//========================= PROTÓTIPOS DE FUNÇÕES ==============================
void inicializar_cargos(LISTA *gerentes, LISTA *supervisores, LISTA *peoes);
void inserir_ord(LISTA *lst, const char *nome, const char *cargo, int salario_funcionario);
void imprimir(LISTA *lst);
LISTA *cargo_lista(const char *cargo, LISTA *gerentes, LISTA *supervisores, LISTA *peoes);

//========================= FUNÇÃO PRINCIPAL ===================================
int main() {
    LISTA gerentes1, supervisores1, peoes1;

    inicializar_cargos(&gerentes1, &supervisores1, &peoes1);

    inserir_ord(cargo_lista("gerente", &gerentes1, &supervisores1, &peoes1), "fulano", "gerente", 1000);

    inserir_ord(cargo_lista("gerente", &gerentes1, &supervisores1, &peoes1), "fulano", "gerente", 1000);

    inserir_ord(cargo_lista("gerente", &gerentes1, &supervisores1, &peoes1), "fulano", "gerente", 1000);
    inserir_ord(cargo_lista("supervisor", &gerentes1, &supervisores1, &peoes1), "ciclano", "supervisor", 800);
    inserir_ord(cargo_lista("peao", &gerentes1, &supervisores1, &peoes1), "beltrano", "peao", 500);

    printf("Gerentes: ");
    imprimir(&gerentes1);
    printf("Supervisores: ");
    imprimir(&supervisores1);
    printf("Peoes: ");
    imprimir(&peoes1);

    return 0;
}

//========================= IMPLEMENTAÇÃO DAS FUNÇÕES ==========================
void inicializar_cargos(LISTA *gerentes, LISTA *supervisores, LISTA *peoes) {
    gerentes->ini = gerentes->fim = NULL;
    supervisores->ini = supervisores->fim = NULL;
    peoes->ini = peoes->fim = NULL;
}

LISTA *cargo_lista(const char *cargo, LISTA *gerentes, LISTA *supervisores, LISTA *peoes) {
    if (strcmp(cargo, "gerente") == 0) return gerentes;
    if (strcmp(cargo, "supervisor") == 0) return supervisores;
    if (strcmp(cargo, "peao") == 0) return peoes;
    return NULL;
}

void inserir_ord(LISTA *lst, const char *nome, const char *cargo, int salario_funcionario) {
    if (!lst) {
        printf("Erro: Lista inválida.\n");
        return;
    }

    struct sNODE *novo = (struct sNODE*) malloc(sizeof(struct sNODE));
    if (!novo) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    strcpy(novo->nome, nome);
    strcpy(novo->cargo, cargo);
    novo->salario = salario_funcionario;
    novo->ant = NULL;
    novo->prox = NULL;

    if (!lst->ini) {
        lst->ini = lst->fim = novo;
    } else {
        lst->fim->prox = novo;
        novo->ant = lst->fim;
        lst->fim = novo;
    }
}

void imprimir(LISTA *lst) {
    struct sNODE *aux = lst->ini;
    printf("[");
    while (aux) {
        printf(" %s,%s,%d ", aux->nome, aux->cargo, aux->salario);
        aux = aux->prox;
    }
    printf(" ]\n");
}
