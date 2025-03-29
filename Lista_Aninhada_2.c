/* Lista Aninhada 2 
   26-03-2025
   Tarefa Avaliativa
   
   Trabalho em Dupla:
   
   (1).....................................................
   (2).....................................................
   
*/
#include <stdlib.h>
#include <stdio.h>

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

TDisciplina *buscarDisciplinaIndex(TLista list, int index){
	TDisciplina *current = list.disciplinas;
	int i;

	for ( i = 0; (i != index && current != NULL); i++){
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
				break;
			case 12:
				break;

		}//switch
		
	}while(opcao != 0);
	//teste
	
	return 0;
}