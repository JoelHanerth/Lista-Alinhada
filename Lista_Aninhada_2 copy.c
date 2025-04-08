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

//===| Funções auxiliares |==================================================
void inicializa(TLista *L){
	L->cursos = NULL;
	L->disciplinas = NULL;	
}

TDisciplina *buscarDisciplinaIndex(TLista list, int index) {
    TDisciplina *current = list.disciplinas;
    int i;

    for (i = 0; current != NULL && i < index; i++) {
        current = current->prox;
    }

    return current;
}

TCurso *buscarCursoIndex(TLista list, int index) {
	TCurso *curso = list.cursos;
    for (int i = 0; curso != NULL && i < index; i++) {
        curso = curso->prox;
    }
	return curso;
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

// Função auxiliar para selecionar uma disciplina a partir da lista
TDisciplina* selecionarDisciplina(TLista *list) {
    int disciplinaIndex;
    TDisciplina *disciplina;

    listarDisciplinas(*list);
    printf("\n\t► Índice da disciplina: ");
    scanf("%d", &disciplinaIndex);
    disciplinaIndex--;

    disciplina = buscarDisciplinaIndex(*list, disciplinaIndex);
    if (disciplina == NULL) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Disciplina não encontrada!\n");
        printf("\t═══════════════════════════════════════════\n\n");
    }
    return disciplina;
}

// Função auxiliar para selecionar um curso a partir da lista
TCurso* selecionarCurso(TLista *list) {
    int cursoIndex;
    TCurso *curso;

    listarCursos(*list);
    printf("\n\t► Índice do curso: ");
    scanf("%d", &cursoIndex);
    cursoIndex--;

    curso = buscarCursoIndex(*list, cursoIndex);
    if (curso == NULL) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Curso não encontrado!\n");
        printf("\t═══════════════════════════════════════════\n\n");
    }
    return curso;
}








//===| Funções Disciplinas |==================================================
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
		novo->ant = atual;
		atual->prox = novo;
	}

	printf("\n\t═══════════════════════════════════════════\n");
	printf("\t✔ Disciplina cadastrada com sucesso!\n");
	printf("\t═══════════════════════════════════════════\n\n");
	listarDisciplinas(*list);
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
		if (atual == NULL){
			printf("\n\t═══════════════════════════════════════════\n");
			printf("\t✔ Disciplina não encontrada!\n");
			printf("\t═══════════════════════════════════════════\n\n");
			return;

		}
		if (atual->prox == NULL){
			atual->ant->prox = NULL;
			free(atual);
		}
		else{
			atual->ant->prox = atual->prox;
			atual->prox->ant = atual->ant;
			free(atual);
		}
	}

	printf("\n\t═══════════════════════════════════════════\n");
	printf("\t✔ Disciplina removida com sucesso!\n");
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
		novo->ant = atual;
		atual->prox = novo;
	}
}






//===| Funções Curso |==================================================
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
		novo->ante = atual;
		atual->prox = novo;
	}

	printf("\n\t═══════════════════════════════════════════\n");
	printf("\t✔ Curso cadastrado com sucesso!\n");
	printf("\t═══════════════════════════════════════════\n\n");
	listarCursos(*list);
}

void excluirCurso(TLista *list) {
    TCurso *curso = selecionarCurso(list);
    if (curso == NULL) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Curso não encontrado!\n");
        printf("\t═══════════════════════════════════════════\n\n");
        return;
    }

    if (curso->ante != NULL) {
        curso->ante->prox = curso->prox;
    } else {
        // Se é o primeiro nó, atualiza a cabeça da lista
        list->cursos = curso->prox;
    }

    if (curso->prox != NULL) {
        curso->prox->ante = curso->ante;
    }

    TGrade *gradeAtual = curso->gradeCurricular;
    while (gradeAtual != NULL) {
        TGrade *proximaGrade = gradeAtual->prox;
        free(gradeAtual);
        gradeAtual = proximaGrade;
    }

    free(curso);

    printf("\n\t═══════════════════════════════════════════\n");
    printf("\t✔ Curso excluído com sucesso!\n");
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
		novo->ante = atual;
		atual->prox = novo;
	}
}





//===| Funções Pré Requisitos |==================================================
void registrarPreRequisitos(TLista *list) {
    int preRequisitoIndex;
    TDisciplina *disciplina, *preRequisito;
    TPreRequisito *novoPreRequisito, *atualPreReq;

    disciplina = selecionarDisciplina(list);
    if (disciplina == NULL)
        return;

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
    TDisciplina *disciplina;
    TPreRequisito *atualPreReq;

    disciplina = selecionarDisciplina(&list);
    if (disciplina == NULL)
        return;

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

void excluirPreRequisito(TLista *list) {
    int preReqIndex;
    TDisciplina *disciplina;
    TPreRequisito *current, *prev, *temp;
    
    disciplina = selecionarDisciplina(list);
    if (disciplina == NULL)
        return;
    
    if (disciplina->preRequisitos == NULL) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Nenhum pré-requisito cadastrado para a disciplina!\n");
        printf("\t═══════════════════════════════════════════\n\n");
        return;
    }
    
    printf("\n\t══════════════════════════════════════════════════\n");
    printf("\tPré-requisitos de: %s\n", disciplina->nome);
    printf("\t══════════════════════════════════════════════════\n");
    current = disciplina->preRequisitos;
    int i = 1;
    while (current != NULL) {
        printf("\t%d. %s\n", i++, current->disciplina->nome);
        current = current->prox;
    }
    printf("\t══════════════════════════════════════════════════\n\n");
    
    printf("\n\t► Índice do pré-requisito a excluir: ");
    scanf("%d", &preReqIndex);
    preReqIndex--;
    
    current = disciplina->preRequisitos;
    prev = NULL;
    i = 0;
    while (current != NULL && i < preReqIndex) {
        prev = current;
        current = current->prox;
        i++;
    }
    if (current == NULL) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Pré-requisito não encontrado!\n");
        printf("\t═══════════════════════════════════════════\n\n");
        return;
    }
    
    if (prev == NULL) {
        disciplina->preRequisitos = current->prox; // Removendo o primeiro elemento
    } else {
        prev->prox = current->prox;
    }
    
    temp = current;
    free(temp);
    
    printf("\n\t═══════════════════════════════════════════\n");
    printf("\t✔ Pré-requisito removido com sucesso!\n");
    printf("\t═══════════════════════════════════════════\n\n");
}






//===| Funções Grade curricular |==================================================


void registrarGradeCurricular(TLista *list) {
    int periodo;
	TGrade *atualGrade, *novoGrade;
	TDisciplina *disciplina;
	TCurso *curso;

    curso = selecionarCurso(list);
    if (curso == NULL)
        return;
    
    disciplina = selecionarDisciplina(list);
    if (disciplina == NULL)
        return;
    
    printf("\n\t► Informe o período para a disciplina '%s': ", disciplina->nome);
    scanf("%d", &periodo);

    novoGrade = (TGrade *)malloc(sizeof(TGrade));
    if (novoGrade == NULL) {
        printf("\n\tErro na alocação de memória!\n");
        return;
    }
    novoGrade->disciplina = disciplina;
    novoGrade->periodo = periodo;
    novoGrade->prox = NULL;

    if (curso->gradeCurricular == NULL) {
        curso->gradeCurricular = novoGrade;
    } else {
        atualGrade = curso->gradeCurricular;
        while (atualGrade->prox != NULL) {
            atualGrade = atualGrade->prox;
        }
        atualGrade->prox = novoGrade;
    }

    printf("\n\t═══════════════════════════════════════════\n");
    printf("\t✔ Disciplina '%s' registrada no curso '%s' no período %d!\n", 
           disciplina->nome, curso->nome, periodo);
    printf("\t═══════════════════════════════════════════\n\n");
}

// Função auxiliar para exibir a grade curricular de um curso
void exibirGradeCurricular(TCurso *curso) {
	TGrade *atualGrade;

    if (curso->gradeCurricular == NULL) {
        printf("\n\tNenhuma grade encontrada para esse curso\n");
        return;
    }

    atualGrade = curso->gradeCurricular;
    int i = 1;
    printf("\n\t══════════════════════════════════════════════════\n");
    printf("\tGrade Curricular do curso: %s\n", curso->nome);
    printf("\t══════════════════════════════════════════════════\n");
    while (atualGrade != NULL) {
        printf("\t%d. %s - Período: %d\n", i, atualGrade->disciplina->nome, atualGrade->periodo);
        atualGrade = atualGrade->prox;
        i++;
    }
    printf("\t══════════════════════════════════════════════════\n\n");
}

void listarGradeCurricular(TLista list) {
    TCurso *curso = selecionarCurso(&list);
    if (curso == NULL)
        return;
    
    exibirGradeCurricular(curso);
}

void excluirItemGradeCurricular(TLista *list) {
    int itemIndex;
    TCurso *curso;
    TGrade *atual, *anterior;
    
    curso = selecionarCurso(list);
    if (curso == NULL)
        return;
    
    exibirGradeCurricular(curso);

    printf("\n\t► Índice do item da grade a excluir: ");
    scanf("%d", &itemIndex);
    itemIndex--; 

    anterior = NULL;
    atual = curso->gradeCurricular;
    int i = 0;
    while (atual != NULL && i < itemIndex) {
        anterior = atual;
        atual = atual->prox;
        i++;
    }

    if (atual == NULL) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Item não encontrado!\n");
        printf("\t═══════════════════════════════════════════\n\n");
        return;
    }

    if (anterior == NULL) { // Se for o primeiro item
        curso->gradeCurricular = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual);

    printf("\n\t═══════════════════════════════════════════\n");
    printf("\t✔ Item da grade curricular removido com sucesso!\n");
    printf("\t═══════════════════════════════════════════\n\n");
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
			case 6: excluirPreRequisito(&lista); break;
			case 7: registrarGradeCurricular(&lista); break;
			case 8: excluirItemGradeCurricular(&lista);
			case 9: listarDisciplinas(lista); break;
			case 10: listarCursos(lista); break;
			case 11: listarPreRequisitos(lista); break;
			case 12: listarGradeCurricular(lista);

		}
	}while(opcao != 0);
	
	printf("\n\t═══════════════════════════════════════════\n");
	printf("\t\t Programa encerrado!\n");
	printf("\t═══════════════════════════════════════════\n\n");
	return 0;
}