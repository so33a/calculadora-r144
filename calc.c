#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define MAX 1000
typedef struct no * link;
struct no{
    char item;// char para receber ( ou ) tambem
    link next;
};
struct pilha{
    link t;      /* t é o topo da pilha*/
    //int v[MAX]; /* v é o vetor que armazena os elementos da pilha */
};
/* Define um novo tipo de dado chamado Pilha que é um ponteiro para "struct pilha". */
typedef struct pilha * Pilha;

/* Aloca espaço para armazenar uma nova Pilha */
Pilha novaPilha () {
    Pilha p = malloc(sizeof(*p));
    if (p == NULL)
        {
            printf("Algum erro aconteceu !\n");
            exit(-1);
        }
    p->t = 0; /* devemos inicializar o topo com 0 */
    return p;
}
/* Operação de inserir novo elemento na pilha */
void push (Pilha p, char valor) {
    //p->v[(p->t)++] = valor;
    link aux = malloc(sizeof(*aux));
        if (aux == NULL){
            printf("Algum erro aconteceu !\n");
            exit(-1);
        }
    aux->item = valor;
    aux->next = p->t;
    p->t = aux;
}
/* Operação de remover um elemento da pilha */
char pop (Pilha p) {
    link aux = malloc(sizeof(*aux));
    if (aux == NULL){
        printf("Algum erro aconteceu !\n");
        exit(-1);
    }
    aux = p->t;
    char x = aux->item;
    p->t = aux->next;
    free(aux);
    return x;
}
/* Libera memória de uma dada pilha p */
void destroiPilha (Pilha p)
{
    while(p->t!=NULL)
        pop(p);
    free(p);
}
/* Operação para pegar o elemento do topo da pilha*/
char topo (Pilha p) {
    return p->t->item;
}

/* Transforma a notação infixa para a notação posfixa */
int infixoParaPosfixo (char * entrada, char * saida, int n)
{
    Pilha p = novaPilha();
    int i,k ;
    int j = 0;
    char c;
    push(p, '(');
    for (i = 0; entrada[i] != '\0' &&  i < n; i++)
        {
            if((j-1 > 0) && (saida[j-1] != ' '))
                saida[j++]  = ' ';
            if(entrada[i] == '(') {
                push(p, entrada[i]);
            } else if(entrada[i] == ')'){
                while (1) {
                    c = pop(p);
                    if(c == '(') break;
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
            } else if((entrada[i] == '+') || (entrada[i] == '-')){
                while (1) {
                    c = topo(p);
                    if(c == '(') break;
                    pop(p);
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
                push(p, entrada[i]);
            } else if((entrada[i] == '*') || (entrada[i] == '/')) {
                while (1) {
                    c = topo(p);
                    if(c == '(' || c == '+' || c == '-'  ) break;
                    pop(p);
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
                push(p, entrada[i]);
            } else if (entrada[i] >= '0' && entrada[i] <= '9') {
                while (entrada[i] >= '0' && entrada[i] <= '9') {
                    saida[j++] = entrada[i];
                    i++;
                }
                saida[j++] = ' ';
                i--;
            }

        }
    while (1) {
        c = pop(p);
        if(c == '(') break;
        saida[j++] = c;
        saida[j++] = ' ';
    }
    saida[j] = '\0';
    destroiPilha(p);
    return 0;
}

int bemEncaixado (char* s) {
    Pilha p = novaPilha();
    int i;
    int resultado = 1;
    for(i = 0; s[i] != '\0'; i++) {
        if(s[i] == '(') {
            if(p->t >= MAX) {
                resultado = 0;
                break;
            }
            push(p, 1);
        } else if (s[i] == ')') {
            if(p->t <= 0) {
                resultado = 0;
                break;
            }
            pop(p);
        }
    }
    if(p->t > 0)
        resultado = 0;
    destroiPilha(p);
    return resultado;
}


int calcula ( char * s ) {
    int i = 0;
    int d = 0,k;
    int numero = 0;
    Pilha p = novaPilha();
    int resultado ;
    int a,b;
    while  (s[i] != '\0') {
        if(s[i] >= '0' && s[i] <= '9' ) {
            sscanf(&s[i], "%d", & numero);
            while(s[i] >= '0' && s[i] <= '9')
                i++;
            i--;
            push(p, numero);
        } else if (s[i] == '+') {
            b = pop(p);
            a = pop(p);
            push (p, a + b);
        } else if (s[i] == '-') {
            b = pop(p);
            a = pop(p);
            push (p, a - b);
        } else if (s[i] == '*') {
            b = pop(p);
            a = pop(p);
            push (p, a * b);
        } else if (s[i] == '/') {
            b = pop(p);
            a = pop(p);
            push (p, a/b);
        }
        i++;
    }

    resultado = topo(p);
    destroiPilha(p);
    return resultado;
}



/* Exemplo de utilização */
int main () {
    char infixo[255] ;
    char posfixo[255];
    printf("Sou uma calculadora de inteiros implementado com pilha!\n");
    printf("Digite quit para sair !\n");
    printf ("> ");
    while(fgets(infixo, 255, stdin) != NULL) {
        if(strcmp(infixo, "quit\n") == 0)  {
            printf ("morri !\n");
            return 0;
        }
        if(bemEncaixado(infixo)) {
            infixoParaPosfixo(infixo, posfixo, 255);
            printf("%d\n", calcula(posfixo));
        } else
            printf ("Erro nos parenteses\n");
        printf ("> ");
    }
    return 0;
}
