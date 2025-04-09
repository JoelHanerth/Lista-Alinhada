/* Lista Aninhada 2 
   26-03-2025
   Tarefa Avaliativa

   Trabalho em Dupla:
   
   (1).....................................................
   (2).....................................................
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef char string[40];

//////////////////////////////////////////////
// Estruturas de Dados
//////////////////////////////////////////////

typedef struct tipoPreRequisito {
    struct tipoDisciplina *disciplina;
    struct tipoPreRequisito *prox;
} TPreRequisito;

typedef struct tipoDisciplina {
    string nome;
    int cargaHoraria;
    struct tipoDisciplina *prox;
    struct tipoDisciplina *ant;
    TPreRequisito *preRequisitos;
} TDisciplina;

typedef struct tipoGrade {
    TDisciplina *disciplina;
    int periodo;
    struct tipoGrade *prox;
} TGrade;

typedef struct tipoCurso {
    string nome;
    struct tipoCurso *ante;
    struct tipoCurso *prox;
    TGrade *gradeCurricular;
} TCurso;

typedef struct tipoLista {
    TCurso *cursos;
    TDisciplina *disciplinas;
} TLista;

TLista lista;

//////////////////////////////////////////////
// Funções Auxiliares
//////////////////////////////////////////////

// Inicializa a lista (cursos e disciplinas)
void inicializa(TLista *L) {
    L->cursos = NULL;
    L->disciplinas = NULL;
}

// Retorna a disciplina no índice indicado (0-base)
TDisciplina *buscarDisciplinaIndex(TLista list, int index) {
    TDisciplina *current = list.disciplinas;
    int i;
    for (i = 0; current != NULL && i < index; i++) {
        current = current->prox;
    }
    return current;
}

// Retorna o curso no índice indicado (0-base)
TCurso *buscarCursoIndex(TLista list, int index) {
    TCurso *curso = list.cursos;
    for (int i = 0; curso != NULL && i < index; i++) {
        curso = curso->prox;
    }
    return curso;
}

// Exibe a lista de disciplinas
void listarDisciplinas(TLista list) {
    TDisciplina *current = list.disciplinas;
    int i = 1;
    printf("\n\t═══════════════════════════════════════════════\n");
    printf("\t| %-4s | %-30s | %-12s |\n", "ID", "Nome da Disciplina", "Carga Horária");
    printf("\t═══════════════════════════════════════════════\n");
    while (current != NULL) {
        printf("\t| %-4d | %-30s | %-12d |\n", i++, current->nome, current->cargaHoraria);
        current = current->prox;
    }
    printf("\t═══════════════════════════════════════════════\n\n");
}

// Exibe a lista de cursos
void listarCursos(TLista list) {
    TCurso *current = list.cursos;
    int i = 1;
    printf("\n\t═══════════════════════════════\n");
    printf("\t| %-4s | %-20s |\n", "ID", "Nome do Curso");
    printf("\t═══════════════════════════════\n");
    while (current != NULL) {
        printf("\t| %-4d | %-20s |\n", i++, current->nome);
        current = current->prox;
    }
    printf("\t═══════════════════════════════\n\n");
}

// Seleciona uma disciplina com base no índice informado pelo usuário
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

// Seleciona um curso com base no índice informado pelo usuário
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

//////////////////////////////////////////////
// Criação e Inserção – Disciplinas e Cursos
//////////////////////////////////////////////

// Cria uma nova disciplina com os parâmetros fornecidos
TDisciplina *criaDisciplina(const char nome[], int cargaHoraria) {
    TDisciplina *novo = (TDisciplina *)malloc(sizeof(TDisciplina));
    if (novo != NULL) {
        strcpy(novo->nome, nome);
        novo->cargaHoraria = cargaHoraria;
        novo->prox = NULL;
        novo->ant = NULL;
        novo->preRequisitos = NULL;
    }
    return novo;
}

// Insere a disciplina no final da lista de disciplinas
void inserirDisciplina(TLista *list, TDisciplina *disciplina) {
    if (list->disciplinas == NULL) {
        list->disciplinas = disciplina;
    } else {
        TDisciplina *atual = list->disciplinas;
        while (atual->prox != NULL)
            atual = atual->prox;
        disciplina->ant = atual;
        atual->prox = disciplina;
    }
}

// Função interativa de cadastro de disciplina (usuário digita os dados)
void cadastroDisciplinas(TLista *list){
    char nome[100];
    int carga;
    printf("\n\n\t\t════════════════════════════\n");
    printf("\t\t    CADASTRO DE DISCIPLINAS\n");
    printf("\t\t════════════════════════════\n\n");
    printf("\t► Nome da Disciplina: ");
    // Se necessário, use fgets para evitar problemas de buffer
    scanf(" %49[^\n]", nome);
    printf("\t► Carga Horária (horas): ");
    scanf("%d", &carga);
    
    TDisciplina *novo = criaDisciplina(nome, carga);
    inserirDisciplina(list, novo);
    
    printf("\n\t═══════════════════════════════════════════\n");
    printf("\t✔ Disciplina cadastrada com sucesso!\n");
    printf("\t═══════════════════════════════════════════\n\n");
    listarDisciplinas(*list);
}

// Cadastro de disciplina por parâmetro (utilizada no main para inserir dados iniciais)
void cadastroDisciplinas2(TLista *list, const char nome[], int carga) {
    TDisciplina *novo = criaDisciplina(nome, carga);
    inserirDisciplina(list, novo);
}

// Cria um novo curso com os parâmetros fornecidos
TCurso *criaCurso(const char nome[]) {
    TCurso *novo = (TCurso *)malloc(sizeof(TCurso));
    if (novo != NULL) {
        strcpy(novo->nome, nome);
        novo->ante = NULL;
        novo->prox = NULL;
        novo->gradeCurricular = NULL;
    }
    return novo;
}

// Insere o curso no final da lista de cursos
void inserirCurso(TLista *list, TCurso *curso) {
    if (list->cursos == NULL) {
        list->cursos = curso;
    } else {
        TCurso *atual = list->cursos;
        while (atual->prox != NULL)
            atual = atual->prox;
        curso->ante = atual;
        atual->prox = curso;
    }
}

// Função interativa de cadastro de curso
void cadastroCursos(TLista *list){
    char nome[100];
    printf("\n\n\t\t════════════════════════\n");
    printf("\t\t     CADASTRO DE CURSOS\n");
    printf("\t\t════════════════════════\n\n");
    printf("\t► Nome do Curso: ");
    scanf(" %49[^\n]", nome);
    TCurso *novo = criaCurso(nome);
    inserirCurso(list, novo);
    
    printf("\n\t═══════════════════════════════════════════\n");
    printf("\t✔ Curso cadastrado com sucesso!\n");
    printf("\t═══════════════════════════════════════════\n\n");
    listarCursos(*list);
}

// Cadastro de curso por parâmetro (para inserção inicial)
void cadastroCursos2(TLista *list, const char nome[]){
    TCurso *novo = criaCurso(nome);
    inserirCurso(list, novo);
}

//////////////////////////////////////////////
// Remoção – Disciplinas, Cursos e Itens da Grade
//////////////////////////////////////////////

// Remove todas as ocorrências de uma disciplina nas grades curriculares de todos os cursos
void excluirDisciplinaGrade(TLista *list, TDisciplina *disciplina) {
    TCurso *curso = list->cursos;
    while (curso != NULL) {
        TGrade *atual = curso->gradeCurricular;
        TGrade *anterior = NULL;
        while (atual != NULL) {
            if (atual->disciplina == disciplina) {
                // Se for o primeiro elemento na grade
                if (anterior == NULL) {
                    curso->gradeCurricular = atual->prox;
                } else {
                    anterior->prox = atual->prox;
                }
                TGrade *temp = atual;
                atual = atual->prox;
                free(temp);
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }
        curso = curso->prox;
    }
}

// Remove a disciplina da lista e também de todas as grades onde ela aparece
void excluirDisciplina(TLista *list) {
    int index, i;
    TDisciplina *atual = list->disciplinas;
    
    listarDisciplinas(*list);
    printf("\n\t► Índice da disciplina a excluir: ");
    scanf("%d", &index);
    index--;  // Ajustando para 0-base
    
    // Caso seja o primeiro nó
    if (index == 0 && list->disciplinas != NULL) {
        list->disciplinas = atual->prox;
        if (list->disciplinas != NULL)
            list->disciplinas->ant = NULL;
    } else {
        for (i = 0; i < index && atual != NULL; i++) {
            atual = atual->prox;
        }
        if (atual == NULL) {
            printf("\n\t═══════════════════════════════════════════\n");
            printf("\t✘ Disciplina não encontrada!\n");
            printf("\t═══════════════════════════════════════════\n\n");
            return;
        }
        // Ajusta os ponteiros para remover o nó da lista
        if (atual->ant != NULL)
            atual->ant->prox = atual->prox;
        if (atual->prox != NULL)
            atual->prox->ant = atual->ant;
    }
    // Remove a disciplina também das grades
    excluirDisciplinaGrade(list, atual);
    free(atual);
    printf("\n\t═══════════════════════════════════════════\n");
    printf("\t✔ Disciplina removida com sucesso!\n");
    printf("\t═══════════════════════════════════════════\n\n");
    listarDisciplinas(*list);
}

// Remove o curso selecionado, liberando também os itens da grade
void excluirCurso(TLista *list) {
    TCurso *curso = selecionarCurso(list);
    if (curso == NULL) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Curso não encontrado!\n");
        printf("\t═══════════════════════════════════════════\n\n");
        return;
    }
    if (curso->ante != NULL)
        curso->ante->prox = curso->prox;
    else
        list->cursos = curso->prox;  // Se for o primeiro nó
    
    if (curso->prox != NULL)
        curso->prox->ante = curso->ante;
    
    // Libera itens da grade
    TGrade *gradeAtual = curso->gradeCurricular;
    while (gradeAtual != NULL) {
        TGrade *proxGrade = gradeAtual->prox;
        free(gradeAtual);
        gradeAtual = proxGrade;
    }
    free(curso);
    
    printf("\n\t═══════════════════════════════════════════\n");
    printf("\t✔ Curso excluído com sucesso!\n");
    printf("\t═══════════════════════════════════════════\n\n");
    listarCursos(*list);
}

// Exclui um item da grade curricular de um curso selecionado
void excluirItemGradeCurricular(TLista *list) {
    int itemIndex, i;
    TCurso *curso = selecionarCurso(list);
    if (curso == NULL)
        return;
    
    // Exibe a grade atual
    TGrade *atual = curso->gradeCurricular;
    printf("\n\t══════════════════════════════════════════════════\n");
    printf("\tGrade Curricular do curso: %s\n", curso->nome);
    while (atual != NULL) {
        printf("\t%d. %s - Período: %d\n", i+1, atual->disciplina->nome, atual->periodo);
        atual = atual->prox;
        i++;
    }
    printf("\t══════════════════════════════════════════════════\n\n");
    
    printf("\n\t► Índice do item da grade a excluir: ");
    scanf("%d", &itemIndex);
    itemIndex--; // Ajuste para 0-base
    
    TGrade *anterior = NULL;
    atual = curso->gradeCurricular;
    for (i = 0; atual != NULL && i < itemIndex; i++) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Item não encontrado!\n");
        printf("\t═══════════════════════════════════════════\n\n");
        return;
    }
    if (anterior == NULL)
        curso->gradeCurricular = atual->prox;
    else
        anterior->prox = atual->prox;
    
    free(atual);
    printf("\n\t═══════════════════════════════════════════\n");
    printf("\t✔ Item da grade curricular removido com sucesso!\n");
    printf("\t═══════════════════════════════════════════\n\n");
}

//////////////////////////////////////////////
// Pré-requisitos e Grade Curricular
//////////////////////////////////////////////

// Registra um pré-requisito para uma disciplina selecionada
void registrarPreRequisitos(TLista *list) {
    int preRequisitoIndex;
    TDisciplina *disciplina = selecionarDisciplina(list);
    if (disciplina == NULL)
        return;
    listarDisciplinas(*list);
    printf("\n\t► Índice do pré-requisito: ");
    scanf("%d", &preRequisitoIndex);
    preRequisitoIndex--;
    TDisciplina *preRequisito = buscarDisciplinaIndex(*list, preRequisitoIndex);
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
    TPreRequisito *novoPreReq = (TPreRequisito *)malloc(sizeof(TPreRequisito));
    novoPreReq->disciplina = preRequisito;
    novoPreReq->prox = NULL;
    if (disciplina->preRequisitos == NULL)
        disciplina->preRequisitos = novoPreReq;
    else {
        TPreRequisito *atual = disciplina->preRequisitos;
        while (atual->prox != NULL)
            atual = atual->prox;
        atual->prox = novoPreReq;
    }
    printf("\n\t══════════════════════════════════════════════════\n");
    printf("\t✔ Pré-requisito '%s' adicionado a '%s'!\n",
           preRequisito->nome, disciplina->nome);
    printf("\t══════════════════════════════════════════════════\n\n");
}

// Exibe os pré-requisitos de uma disciplina
void listarPreRequisitos(TLista list) {
    TDisciplina *disciplina = selecionarDisciplina(&list);
    if (disciplina == NULL)
        return;
    
    printf("\n\t══════════════════════════════════════════════════\n");
    printf("\tPré-requisitos de: %s\n", disciplina->nome);
    printf("\t══════════════════════════════════════════════════\n");
    
    if (disciplina->preRequisitos == NULL)
        printf("\tNenhum pré-requisito cadastrado\n");
    else {
        TPreRequisito *atual = disciplina->preRequisitos;
        int i = 1;
        while (atual != NULL) {
            printf("\t%d. %s\n", i++, atual->disciplina->nome);
            atual = atual->prox;
        }
    }
    printf("\t══════════════════════════════════════════════════\n\n");
}

// Exclui um pré-requisito de uma disciplina selecionada
void excluirPreRequisito(TLista *list) {
    int preReqIndex, i;
    TDisciplina *disciplina = selecionarDisciplina(list);
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
    TPreRequisito *atual = disciplina->preRequisitos;
    for (i = 1; atual != NULL; i++) {
        printf("\t%d. %s\n", i, atual->disciplina->nome);
        atual = atual->prox;
    }
    printf("\t══════════════════════════════════════════════════\n\n");
    printf("\n\t► Índice do pré-requisito a excluir: ");
    scanf("%d", &preReqIndex);
    preReqIndex--; // Ajuste para 0-base
    atual = disciplina->preRequisitos;
    TPreRequisito *prev = NULL;
    for (i = 0; atual != NULL && i < preReqIndex; i++) {
        prev = atual;
        atual = atual->prox;
    }
    if (atual == NULL) {
        printf("\n\t═══════════════════════════════════════════\n");
        printf("\t✘ Erro: Pré-requisito não encontrado!\n");
        printf("\t═══════════════════════════════════════════\n\n");
        return;
    }
    if (prev == NULL)
        disciplina->preRequisitos = atual->prox;
    else
        prev->prox = atual->prox;
    free(atual);
    printf("\n\t═══════════════════════════════════════════\n");
    printf("\t✔ Pré-requisito removido com sucesso!\n");
    printf("\t═══════════════════════════════════════════\n\n");
}

//////////////////////////////////////////////
// Grade Curricular
//////////////////////////////////////////////

// Registra uma disciplina na grade curricular de um curso selecionado
void registrarGradeCurricular(TLista *list) {
    int periodo;
    TCurso *curso = selecionarCurso(list);
    if (curso == NULL)
        return;
    TDisciplina *disciplina = selecionarDisciplina(list);
    if (disciplina == NULL)
        return;
    printf("\n\t► Informe o período para a disciplina '%s': ", disciplina->nome);
    scanf("%d", &periodo);
    
    TGrade *novoGrade = (TGrade *)malloc(sizeof(TGrade));
    novoGrade->disciplina = disciplina;
    novoGrade->periodo = periodo;
    novoGrade->prox = NULL;
    
    if (curso->gradeCurricular == NULL)
        curso->gradeCurricular = novoGrade;
    else {
        TGrade *atual = curso->gradeCurricular;
        while (atual->prox != NULL)
            atual = atual->prox;
        atual->prox = novoGrade;
    }
    printf("\n\t═══════════════════════════════════════════\n");
    printf("\t✔ Disciplina '%s' registrada no curso '%s' no período %d!\n",
           disciplina->nome, curso->nome, periodo);
    printf("\t═══════════════════════════════════════════\n\n");
}

// Exibe a grade curricular de um curso
void exibirGradeCurricular(TCurso *curso) {
    if (curso->gradeCurricular == NULL) {
        printf("\n\tNenhuma grade encontrada para esse curso\n");
        return;
    }
    TGrade *atual = curso->gradeCurricular;
    int i = 1;
    printf("\n\t══════════════════════════════════════════════════\n");
    printf("\tGrade Curricular do curso: %s\n", curso->nome);
    printf("\t══════════════════════════════════════════════════\n");
    while (atual != NULL) {
        printf("\t%d. %s - Período: %d\n", i++, atual->disciplina->nome, atual->periodo);
        atual = atual->prox;
    }
    printf("\t══════════════════════════════════════════════════\n\n");
}

// Seleciona um curso e exibe sua grade curricular
void listarGradeCurricular(TLista list) {
    TCurso *curso = selecionarCurso(&list);
    if (curso == NULL)
        return;
    exibirGradeCurricular(curso);
}

//////////////////////////////////////////////
// Menu e Main
//////////////////////////////////////////////

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

int main(){
    SetConsoleOutputCP(65001);
    int opcao;
    inicializa(&lista);

    // Cadastro inicial: Insere disciplinas e cursos padrão
    cadastroDisciplinas2(&lista, "Introdução à Programação", 60);
    cadastroDisciplinas2(&lista, "Estrutura de Dados", 90);
    cadastroDisciplinas2(&lista, "Banco de Dados", 120);
    cadastroCursos2(&lista, "Sistemas de Informação");
    cadastroCursos2(&lista, "Administração");
    
    do {
        opcao = menu();
        switch(opcao) {
            case 1: cadastroDisciplinas(&lista); break;
            case 2: excluirDisciplina(&lista); break;
            case 3: cadastroCursos(&lista); break;
            case 4: excluirCurso(&lista); break;
            case 5: registrarPreRequisitos(&lista); break;
            case 6: excluirPreRequisito(&lista); break;
            case 7: registrarGradeCurricular(&lista); break;
            case 8: excluirItemGradeCurricular(&lista); break;
            case 9: listarDisciplinas(lista); break;
            case 10: listarCursos(lista); break;
            case 11: listarPreRequisitos(lista); break;
            case 12: listarGradeCurricular(lista); break;
        }
    } while(opcao != 0);
    
    printf("\n\t═══════════════════════════════════════════\n");
    printf("\t\t Programa encerrado!\n");
    printf("\t═══════════════════════════════════════════\n\n");
    return 0;
}
