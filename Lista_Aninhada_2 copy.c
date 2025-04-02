/* Lista Aninhada 2 
   26-03-2025
   Tarefa Avaliativa
   
   Trabalho em Dupla:
   
   (1).....................................................
   (2).....................................................
   
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef char string[40];

typedef struct tipoDisciplina {
	string nome;
	int cargaHoraria;
	struct tipoDisciplina *prox;
	struct tipoDisciplina *ant;
	struct tipoPreRequisito *preRequisitos;	
}TDisciplina;

typedef struct tipoPreRequisito {
	TDisciplina *disciplina;
	struct tipoPreRequisito *prox;
}TPreRequisito;

typedef struct tipoGrade {
	TDisciplina *disciplina;
	int periodo;
	 struct tipoGrade *prox;	
}TGrade;

typedef struct tipoCurso { //nome curso
	string nome;
	struct tipoCurso *ante;
	struct tipoCurso *prox;
	TGrade *gradeCurricular;
}TCurso;

typedef struct tipoLista {
	TCurso *cursos;
	TDisciplina *disciplinas;
}TLista;

TLista lista;

//===| Funções |==================================================
void inicializa(TLista *L){
	L->cursos = NULL;
	L->disciplinas = NULL;	
}

void listarDisciplinas(TLista list) {
    TDisciplina *current = list.disciplinas;
    int i = 1;

    printf("\n\t═══════════════════════════════════════════════\n");
    printf("\t| %-4s | %-30s | %-12s |\n", "ID", "Nome da Disciplina", "Carga Horária");
    printf("\t═══════════════════════════════════════════════\n");

    while(current != NULL) {
        printf("\t| %-4d | %-30s | %-12d |\n", i++, current->nome, current->cargaHoraria);
        current = current->prox;
    }
    printf("\t═══════════════════════════════════════════════\n\n");
}

void listarCursos(TLista list) {
    TCurso *current = list.cursos;
    int i = 1;

    printf("\n\t═══════════════════════════════\n");
    printf("\t| %-4s | %-20s |\n", "ID", "Nome do Curso");
    printf("\t═══════════════════════════════\n");

    while(current != NULL) {
        printf("\t| %-4d | %-20s |\n", i++, current->nome);
        current = current->prox;
    }
    printf("\t═══════════════════════════════\n\n");
}

TDisciplina *buscarDisciplinaIndex(TLista list, int index) {
    TDisciplina *current = list.disciplinas;
    int i;

    for (i = 0; current != NULL && i < index; i++) {
        current = current->prox;
    }

    return current;
}

void cadastroDisciplinas(TLista *list){
	TDisciplina *novo, *atual;
	printf("\n\n\t\t════════════════════════════\n");
	printf("\t\t    CADASTRO DE DISCIPLINAS\n");
	printf("\t\t════════════════════════════\n\n");

	novo = (TDisciplina *)malloc(sizeof(TDisciplina));
	novo->ant = NULL;
	novo->prox = NULL;
	novo->preRequisitos = NULL;

	printf("\t► Nome da Disciplina: ");
	scanf(" %49[^\n]s", novo->nome);
	printf("\t► Carga Horária (horas): ");
	scanf("%d", &novo->cargaHoraria);

	atual = list->disciplinas;			

	if(atual == NULL){
		list->disciplinas = novo;		
	} else {
		while(atual->prox != NULL){
			atual = atual->prox;
		}
		atual->prox = novo;
	}

	printf("\n\t═══════════════════════════════════════════\n");
	printf("\t✔ Disciplina cadastrada com sucesso!\n");
	printf("\t═══════════════════════════════════════════\n\n");
	listarDisciplinas(*list);
}

void cadastroDisciplinas2(TLista *list, char nome[100], int carga){
	TDisciplina *novo, *atual;

	novo = (TDisciplina *)malloc(sizeof(TDisciplina));
	novo->ant = NULL;
	novo->prox = NULL;
	novo->preRequisitos = NULL;

	strcpy(novo->nome, nome);
	novo->cargaHoraria = carga;

	atual = list->disciplinas;			

	if(atual == NULL){
		list->disciplinas = novo;		
	} else {
		while(atual->prox != NULL){
			atual = atual->prox;
		}
		atual->prox = novo;
	}
}

void excluirDisciplina(TLista *list){
	TDisciplina *atual = list->disciplinas;
	int i, index;

	listarDisciplinas(*list);
	printf("\n\t► Índice da disciplina a excluir: ");
	scanf("%d", &index);
	index--;

	if (index == 0 && list->disciplinas!=NULL) {
		list->disciplinas = atual->prox;
		free(atual);

	} else {
		for (i = 0; i < index && atual != NULL; i++) {
			atual = atual->prox;
		}
		if (atual != NULL) {
			atual->ant->prox = atual->prox;
			free(atual);
		}
		else{
			printf("\n\t═══════════════════════════════════════════\n");
			printf("\t✔ Disciplina não encontrada!\n");
			printf("\t═══════════════════════════════════════════\n\n");
			return;
		}
	}

	printf("\n\t═══════════════════════════════════════════\n");
	printf("\t✔ Disciplina removida com sucesso!\n");
	printf("\t═══════════════════════════════════════════\n\n");
	listarDisciplinas(*list);
}

void cadastroCursos(TLista *list){
	TCurso *novo, *atual;
	printf("\n\n\t\t════════════════════════\n");
	printf("\t\t     CADASTRO DE CURSOS\n");
	printf("\t\t════════════════════════\n\n");

	novo = (TCurso *)malloc(sizeof(TCurso));
	novo->ante = NULL;
	novo->prox = NULL;
	novo->gradeCurricular = NULL;

	printf("\t► Nome do Curso: ");
	scanf(" %49[^\n]s", novo->nome);

	atual = list->cursos;			

	if(atual == NULL){
		list->cursos = novo;		
	} else {
		while(atual->prox != NULL){
			atual = atual->prox;
		}
		atual->prox = novo;
	}

	printf("\n\t═══════════════════════════════════════════\n");
	printf("\t✔ Curso cadastrado com sucesso!\n");
	printf("\t═══════════════════════════════════════════\n\n");
	listarCursos(*list);
}

void cadastroCursos2(TLista *list, char nome[100]){
	TCurso *novo, *atual;

	novo = (TCurso *)malloc(sizeof(TCurso));
	novo->ante = NULL;
	novo->prox = NULL;
	novo->gradeCurricular = NULL;

	strcpy(novo->nome, nome);

	atual = list->cursos;			

	if(atual == NULL){
		list->cursos = novo;		
	} else {
		while(atual->prox != NULL){
			atual = atual->prox;
		}
		atual->prox = novo;
	}
}

void excluirCurso(TLista *list){
	TCurso *atual = list->cursos;
	int i, index;

	listarCursos(*list);
	printf("\n\t► Índice do curso a excluir: ");
	scanf("%d", &index);
	index--;

	if (index == 0 && list->cursos != NULL) {
		list->cursos = atual->prox;
		free(atual);
	} else {
		for (i = 0; i < index && atual != NULL; i++) {
			atual = atual->prox;
		}
		if (atual != NULL) {
			atual->ante = atual->prox;
			printf("aqui");
			free(atual);
		}
		else{
			printf("\n\t═══════════════════════════════════════════\n");
			printf("\tX Curso não encontrado\n");
			printf("\t═══════════════════════════════════════════\n\n");
			return;
		}
	}

	printf("\n\t═══════════════════════════════════════════\n");
	printf("\t✔ Curso removido com sucesso!\n");
	printf("\t═══════════════════════════════════════════\n\n");
}

void registrarPreRequisitos(TLista *list) {
    int disciplinaIndex, preRequisitoIndex;
    TDisciplina *disciplina, *preRequisito;
    TPreRequisito *novoPreRequisito, *atualPreReq;

    listarDisciplinas(*list);
	
    printf("\n\t► Índice da disciplina principal: ");
    scanf("%d", &disciplinaIndex);
    disciplinaIndex--;

    disciplina = buscarDisciplinaIndex(*list, disciplinaIndex);

    if (disciplina == NULL) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Disciplina não encontrada!\n");
        printf("\t═══════════════════════════════════════════\n\n");
        return;
    }

    listarDisciplinas(*list);
    printf("\n\t► Índice do pré-requisito: ");
    scanf("%d", &preRequisitoIndex);
    preRequisitoIndex--;

    preRequisito = buscarDisciplinaIndex(*list, preRequisitoIndex);

    if (preRequisito == NULL) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Pré-requisito não encontrado!\n");
        printf("\t═══════════════════════════════════════════\n\n");
        return;
    }

    if (disciplina == preRequisito) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Disciplina não pode ser pré-requisito de si mesma!\n");
        printf("\t═══════════════════════════════════════════\n\n");
        return;
    }

    novoPreRequisito = (TPreRequisito *)malloc(sizeof(TPreRequisito));
    novoPreRequisito->disciplina = preRequisito;
    novoPreRequisito->prox = NULL;

    if (disciplina->preRequisitos == NULL) {
        disciplina->preRequisitos = novoPreRequisito;
    } else {
        atualPreReq = disciplina->preRequisitos;
        while (atualPreReq->prox != NULL) {
            atualPreReq = atualPreReq->prox;
        }
        atualPreReq->prox = novoPreRequisito;
    }

    printf("\n\t══════════════════════════════════════════════════\n");
    printf("\t✔ Pré-requisito '%s' adicionado a '%s'!\n", preRequisito->nome, disciplina->nome);
    printf("\t══════════════════════════════════════════════════\n\n");
}

void listarPreRequisitos(TLista list) {
    int disciplinaIndex;
    TDisciplina *disciplina;
    TPreRequisito *atualPreReq;

    listarDisciplinas(list);
    printf("\n\t► Índice da disciplina: ");
    scanf("%d", &disciplinaIndex);
    disciplinaIndex--;

    disciplina = buscarDisciplinaIndex(list, disciplinaIndex);
    if (disciplina == NULL) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Disciplina não encontrada!\n");
        printf("\t═══════════════════════════════════════════\n\n");
        return;
    }

    printf("\n\t══════════════════════════════════════════════════\n");
    printf("\tPré-requisitos de: %s\n", disciplina->nome);
    printf("\t══════════════════════════════════════════════════\n");

    if (disciplina->preRequisitos == NULL) {
        printf("\tNenhum pré-requisito cadastrado\n");
    } else {
        atualPreReq = disciplina->preRequisitos;
        int i = 1;
        while (atualPreReq != NULL) {
            printf("\t%d. %s\n", i++, atualPreReq->disciplina->nome);
            atualPreReq = atualPreReq->prox;
        }
    }
    printf("\t══════════════════════════════════════════════════\n\n");
}

int menu(){
	int opcao;
	printf("\n\n\t╔═══════════════════════════════════╗");
	printf("\n\t║           MENU PRINCIPAL          ║");
	printf("\n\t╠═══════════════════════════════════╣");
	printf("\n\t║  0 - SAIR                         ║");
	printf("\n\t║  1 - Inserir Disciplinas          ║");
	printf("\n\t║  2 - Excluir Disciplinas          ║");
	printf("\n\t║  3 - Inserir Cursos               ║");
	printf("\n\t║  4 - Excluir Cursos               ║");
	printf("\n\t║  5 - Registrar Pré-requisitos     ║");
	printf("\n\t║  6 - Excluir Pré-requisito        ║");
	printf("\n\t║  7 - Registrar Grade Curricular   ║");
	printf("\n\t║  8 - Excluir Item da Grade        ║");
	printf("\n\t║  9 - Listar Disciplinas           ║");
	printf("\n\t║ 10 - Listar Cursos                ║");
	printf("\n\t║ 11 - Listar Pré-requisitos        ║");
	printf("\n\t║ 12 - Listar Grade Curricular      ║");
	printf("\n\t╚═══════════════════════════════════╝");
	printf("\n\n\t► Escolha uma opção: ");
	scanf("%d", &opcao);
	return opcao;
}

//================================================================
int main(){
	SetConsoleOutputCP(65001);
	int opcao;

	inicializa(&lista);

	cadastroDisciplinas2(&lista,"Introdução à Programação",60);
	cadastroDisciplinas2(&lista,"Estrutura de Dados",90);
	cadastroDisciplinas2(&lista,"Banco de Dados",120);

	cadastroCursos2(&lista, "Sistemas de Informação");
	cadastroCursos2(&lista, "Administração");
	
	do{
		opcao = menu();
		
		switch(opcao){
			case 1: cadastroDisciplinas(&lista); break;
			case 2: excluirDisciplina(&lista); break;
			case 3: cadastroCursos(&lista); break;
			case 4: excluirCurso(&lista); break;
			case 5: registrarPreRequisitos(&lista); break;
			case 6: break;
			case 7: break;
			case 8: break;
			case 9: listarDisciplinas(lista); break;
			case 10: listarCursos(lista); break;
			case 11: listarPreRequisitos(lista); break;
			case 12: break;

		}
	}while(opcao != 0);
	
	printf("\n\t═══════════════════════════════════════════\n");
	printf("\t\t Programa encerrado!\n");
	printf("\t═══════════════════════════════════════════\n\n");
	return 0;
}