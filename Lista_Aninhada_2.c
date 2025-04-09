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
	int i;

	for ( i = 0; current != NULL; i++){
		printf("%d - %s - (%d horas)\n", i+1,current->nome, current->cargaHoraria);
        current = current->prox;
	}
	printf("\n");
}

void listarCursos(TLista list) {
	TCurso *current = list.cursos;
	int i;

	for ( i = 0; current != NULL; i++){
		printf("%d - %s\n", i+1,current->nome);
		current = current->prox;
	}
	printf("\n");
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
	printf("\n\n\t\t=======| Cadastro de DISCILINAS|=======\n\n");

	novo = (TDisciplina *)malloc(sizeof(TDisciplina));
	novo->ant = NULL;
	novo->prox = NULL;
	novo->preRequisitos = NULL;

	printf("\tInforme o nome da Disciplina: ");
	scanf(" %49[^\n]s", novo->nome);
	printf("\tInforme a carga horária da disciplina em Horas: ");
	scanf("%d", &novo->cargaHoraria);

	atual = list->disciplinas;			

	if(atual == NULL){
		//Lista vazia.
		list->disciplinas = novo;		
	} else {
		//Lista com pelo menos uma disciplina.
		while(atual->prox != NULL){
			atual = atual->prox;
		}//while
		atual->prox = novo;
	}

	listarDisciplinas(*list);
	printf("\n\n\tDisciplina cadastrada com sucesso!\n\n");

}

void cadastroDisciplinaParamentro(TLista *list, char nome[100], int carga){
	TDisciplina *novo, *atual;
	printf("\n\n\t\t=======| Cadastro de DISCILINAS|=======\n\n");

	novo = (TDisciplina *)malloc(sizeof(TDisciplina));
	novo->ant = NULL;
	novo->prox = NULL;
	novo->preRequisitos = NULL;

	strcpy(novo->nome, nome);
	novo->cargaHoraria = carga;

	atual = list->disciplinas;			

	if(atual == NULL){
		//Lista vazia.
		list->disciplinas = novo;		
	} else {
		//Lista com pelo menos uma disciplina.
		while(atual->prox != NULL){
			atual = atual->prox;
		}//while
		atual->prox = novo;
	}

	listarDisciplinas(*list);
	printf("\n\n\tDisciplina cadastrada com sucesso!\n\n");

}

void excluirDisciplina(TLista *list){
	TDisciplina *atual = list->disciplinas;
	TDisciplina *anterior = NULL;
	int i, index;

	listarDisciplinas(*list);
	printf("\n\n\tInforme o indice da disciplina a ser excluida: ");
	scanf("%d", &index);
	index--;

	if (index == 0) {
		list->disciplinas = atual->prox;
		free(atual);
	} else {
		for (i = 0; i < index && atual != NULL; i++) {
			anterior = atual;
			atual = atual->prox;
		}
		if (atual != NULL) {
			anterior->prox = atual->prox;
			free(atual);
		}
	}
	printf("\n\n\tDisciplina excluida com sucesso!\n\n");
	listarDisciplinas(*list);
}

void cadastroCursos(TLista *list){
	TCurso *novo, *atual;
	printf("\n\n\t\t=======| Cadastro de CURSOS |=======\n\n");

	novo = (TCurso *)malloc(sizeof(TCurso));
	novo->ante = NULL;
	novo->prox = NULL;
	novo->gradeCurricular = NULL;

	printf("\tInforme o nome do Curso: ");
	scanf(" %49[^\n]s", novo->nome);

	atual = list->cursos;			

	if(atual == NULL){
		//Lista vazia.
		list->cursos = novo;		
	} else {
		//Lista com pelo menos um curso.
		while(atual->prox != NULL){
			atual = atual->prox;
		}//while
		atual->prox = novo;
	}

	listarCursos(*list);
	printf("\n\n\tCurso cadastrado com sucesso!\n\n");
}

void cadastroCursoParamentro(TLista *list, char nome[100]){
	TCurso *novo, *atual;
	printf("\n\n\t\t=======| Cadastro de CURSOS |=======\n\n");

	novo = (TCurso *)malloc(sizeof(TCurso));
	novo->ante = NULL;
	novo->prox = NULL;
	novo->gradeCurricular = NULL;

	strcpy(novo->nome, nome);

	atual = list->cursos;			

	if(atual == NULL){
		//Lista vazia.
		list->cursos = novo;		
	} else {
		//Lista com pelo menos um curso.
		while(atual->prox != NULL){
			atual = atual->prox;
		}//while
		atual->prox = novo;
	}

	listarCursos(*list);
	printf("\n\n\tCurso cadastrado com sucesso!\n\n");
}

void excluirCurso(TLista *list){
	TCurso *atual = list->cursos;
	TCurso *anterior = NULL;
	int i, index;

	listarCursos(*list);
	printf("\n\n\tInforme o indice do curso a ser excluido: ");
	scanf("%d", &index);

	index--;

	if (index == 0) {
		list->cursos = atual->prox;
		free(atual);
	} else {
		for (i = 0; i < index && atual != NULL; i++) {
			anterior = atual;
			atual = atual->prox;
		}
		if (atual != NULL) {
			anterior->prox = atual->prox;
			free(atual);
		}
	}

	printf("\n\n\tCurso excluido com sucesso!\n\n");
}

void registrarPreRequisitos(TLista *list) {
    int disciplinaIndex, preRequisitoIndex;
    TDisciplina *disciplina, *preRequisito;
    TPreRequisito *novoPreRequisito, *atualPreReq;

    listarDisciplinas(*list);
	
    printf("\n\n\tInforme o índice da disciplina que deseja inserir o pré-requisito: ");
    scanf("%d", &disciplinaIndex);
    disciplinaIndex--;

    disciplina = buscarDisciplinaIndex(*list, disciplinaIndex);

    if (disciplina == NULL) {
        printf("\n\n\tERRO: Disciplina não encontrada!\n\n");
        return;
    }

    printf("\n\n\tDisciplina selecionada: %s\n", disciplina->nome);

    listarDisciplinas(*list);
    printf("\n\n\tInforme o índice do pré-requisito: ");
    scanf("%d", &preRequisitoIndex);
    preRequisitoIndex--;

    preRequisito = buscarDisciplinaIndex(*list, preRequisitoIndex);

    if (preRequisito == NULL) {
        printf("\n\n\tERRO: Pré-requisito não encontrado!\n\n");
        return;
    }

    printf("\n\n\tPré-requisito selecionado: %s\n", preRequisito->nome);

    if (disciplina == preRequisito) {
        printf("\n\n\tERRO: Uma disciplina não pode ser pré-requisito dela mesma!\n\n");
        return;
    }

    // Criar novo nó de pré-requisito
	printf("\n\n\tAdicionando pré-requisito...\n");
    novoPreRequisito = (TPreRequisito *)malloc(sizeof(TPreRequisito));

	printf("\n\n\tmalloc criado\n\n");

    if (novoPreRequisito == NULL) {
        printf("\n\n\tERRO: Falha na alocação de memória!\n\n");
        return;
    }
    
	printf("\n\n\tpre requisito == null\n\n");

    novoPreRequisito->disciplina = preRequisito;
    novoPreRequisito->prox = NULL;

	printf("\n\n\tpre requisito->prox == null\n\n");

    if (disciplina->preRequisitos == NULL) {
        disciplina->preRequisitos = novoPreRequisito;
		printf("\n\n\tIF I\n\n");
    } else {
        atualPreReq = disciplina->preRequisitos;
		printf("\n\n\tELSE I\n\n");// está parando aqui !!!!
        while (atualPreReq->prox != NULL) {
            atualPreReq = atualPreReq->prox;
        }
		printf("\n\n\tWHILE\n\n");
        atualPreReq->prox = novoPreRequisito;
    }

    printf("\n\n\tPré-requisito adicionado com sucesso!\n\n");
}


void listarPreRequisitos(TLista list) { // ainda não testado
    int disciplinaIndex;
    TDisciplina *disciplina;
    TPreRequisito *atualPreReq;

    listarDisciplinas(list);
    printf("\n\n\tInforme o índice da disciplina para visualizar os pré-requisitos: ");
    scanf("%d", &disciplinaIndex);
    disciplinaIndex--;

    disciplina = buscarDisciplinaIndex(list, disciplinaIndex);
    if (disciplina == NULL) {
        printf("\n\n\tERRO: Disciplina não encontrada!\n\n");
        return;
    }

    printf("\n\nPré-requisitos da disciplina '%s':\n", disciplina->nome);
    if (disciplina->preRequisitos == NULL) {
        printf("\tNenhum pré-requisito cadastrado.\n");
        return;
    }

    atualPreReq = disciplina->preRequisitos;
    int i = 1;
    while (atualPreReq != NULL) {
        printf("\t%d - %s\n", i++, atualPreReq->disciplina->nome);
        atualPreReq = atualPreReq->prox;
    }
    printf("\n");
}




//================================================================
int menu(){
	int opcao;
	//system("CLS");
	printf("\n\n\n\t\t=======| MENU |=======\n\n");
	printf("\t0 - SAIR (Encerrar Aplicacao).\n\n");
	printf("\t1 - Inserir DISCIPLINAS.\n");
	printf("\t2 - Excluir DISCIPLINAS.\n\n");
	printf("\t3 - Inserir CURSOS.\n");
	printf("\t4 - Excluir CURSOS.\n");
	printf("\t5 - Registrar PRE-REQUISITOS para DISCIPLINA.\n");
	printf("\t6 - Excluir PRE-REQUISITO de DISCIPLINA.\n\n");
	printf("\t7 - Registrar GRADE CURRICULAR para CURSO.\n");
	printf("\t8 - Excluir item da GRADE CURRICULAR de CURSO.\n\n");
	printf("\t9 - Listar DISCIPLINAS.\n");
	printf("\t10- Listar CURSOS.\n");
	printf("\t11- Listar PRE_REQUISITOS de DISCIPLINA especifica.\n");
	printf("\t12- Listar GRADE CURRICULAR de CURSO especifico.\n\n");
	
	printf("\t\tInforme a OPCAO desejada: ");
	scanf("%d", &opcao);
	
	if((opcao < 0) || (opcao > 12)){
		printf("\n\n\n\tERRO: OPCAO invalida!\n\tTente Novamente\n\n");
		system("PAUSE");
	}//if
	return opcao;
}
//================================================================

int main(){
	int opcao;

	inicializa(&lista);

	cadastroDisciplinaParamentro(&lista,"a",60);
	cadastroDisciplinaParamentro(&lista,"b",90);
	cadastroDisciplinaParamentro(&lista,"c",120);

	listarDisciplinas(lista);

	cadastroCursoParamentro(&lista, "SI");
	cadastroCursoParamentro(&lista, "ADM");
	listarCursos(lista);


	
	do{
		opcao = menu();
		
		switch(opcao){
			case 1:
				cadastroDisciplinas(&lista);
				break;
			case 2:
				excluirDisciplina(&lista);
				break;
			case 3:
				cadastroCursos(&lista);
				break;
			case 4:
				excluirCurso(&lista);
				break;
			case 5: 
				registrarPreRequisitos(&lista);
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				listarDisciplinas(lista);
				break;
			case 10:
				listarCursos(lista);
				break;
			case 11:
				listarPreRequisitos(lista);
				break;
			case 12:
				break;

		}//switch
		
	}while(opcao != 0);
	//teste
	
	return 0;
}