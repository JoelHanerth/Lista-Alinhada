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
		printf("%d - %s\n", i,current->nome);
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
	TDisciplina *novo;
	printf("\n\n\t\t=======| Cadastro de DISCILINAS|=======\n\n");

	novo = (TDisciplina *)malloc(sizeof(TDisciplina));
	novo->ant = NULL;
	novo->prox = NULL;
	novo->preRequisitos = NULL;

	printf("\tInforme o nome da Disciplina: ");
	scanf(" %49[^\n]s", novo->nome);
	printf("\tInforme a carga horária da disciplina em Horas: ");
	scanf("%d", &novo->cargaHoraria);

}




//================================================================
int menu(){
	int opcao;
	system("CLS");
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
				break;
			case 3:
				break;
			case 4:
				break;
			case 5: 
				break;
		}//switch
		
	}while(opcao != 0);
	//teste
	
	return 0;
}