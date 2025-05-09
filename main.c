#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct carta{
  int numero;
  int naipe;
}carta;

typedef struct elemento{
  carta* carta;
  struct elemento *proximo;
  struct elemento *anterior;
}elemento;

typedef struct pilha{
  elemento* topo;
  int numItens;
}pilha;

typedef struct lista{
  elemento* inicio;
}lista;

typedef struct jogador{
  elemento* topo;
  carta* mao;
  char nome[11];
  int num;
}jogador;

//criação e liberação pilha e lista
lista* criaLista(){
    lista* l = (lista*)malloc(sizeof(lista));
    if (l != NULL) {
        l->inicio = NULL;
        return l;
    } else {
        return NULL;
    }
}
pilha* criaPilha(){
    pilha* p = (pilha*)malloc(sizeof(pilha));
    if (p != NULL) {
        p->topo = NULL;
        p->numItens = 0;
        return p;
    } else {
        return NULL;
    }
}
void limpaLista(lista* l) {
  elemento *aux = l->inicio;
  while (aux != NULL) {
    elemento *proximo = aux->proximo;
    free(aux->carta);  
    aux = proximo;
  }
  l->inicio = NULL;
}
void liberaPilha(pilha *p){
  if (p == NULL) {
    return;  // Evite acessar uma pilha nula
  }
  while (p->topo != NULL) {
    elemento *aux = p->topo;
    p->topo = aux->anterior;
    free(aux);
  }

  free(p);
}
//Funções auxiliares
elemento* criaNovo() {
    elemento* novo = (elemento*)malloc(sizeof(elemento));
    if (novo != NULL) {
        novo->carta = (carta*)malloc(sizeof(carta)); // Aloca memória para carta
        if (novo->carta != NULL) {
            return novo;
        } else {
            free(novo);
            return NULL;
        }
    } else {
        return NULL;
    }
}
int estaVaziaLista(lista*l){ //verifica se a lista está vazia
    if(l->inicio==NULL){
        return 1;
    }else{
        return 0;
    }
}
int estaVaziaPilha(pilha* p){ // verifica se a pilha está vazia
  if(p->topo==NULL){
    return 1;
  }else {
    return 0;
  }
}
int estaVaziaJogador(jogador* p){ // verifica se a pilha está vazia
  if(p->topo==NULL){
    return 1;
  }else {
    return 0;
  }
}
elemento* criaNovoPilha() {
    elemento* novo = (elemento*)malloc(sizeof(elemento));
    if (novo != NULL) {
        novo->carta = (carta*)malloc(sizeof(carta)); // Aloca memória para carta
        if (novo->carta != NULL) {
            return novo;
        } else {
            free(novo);
            return NULL;
        }
    } else {
        return NULL;
    }
}
void imprimePilha(pilha* p){ //imprime pilha
  elemento* aux = p->topo;
  int c = 0;
  do{
    c++;
    if(aux->carta->naipe==0){
        printf("%d de PAUS.\n", aux->carta->numero);
      }else if(aux->carta->naipe==1){
          printf("%d de ESPADA.\n", aux->carta->numero);
      }else if(aux->carta->naipe==2){
          printf("%d de OURO.\n", aux->carta->numero);
      }else{
          printf("%d de COPAS.\n", aux->carta->numero);
      }
      aux=aux->anterior;
    }while(aux!=NULL);
}
void imprimirJogador(jogador*p,int vez){ //imprime lista
  elemento* aux=p->topo;
  int c=0;
  do{
    c++;
    if(p[vez].mao->naipe==0){
      printf("%d de PAUS.\n", p[vez].mao->numero);
    }else if(p[vez].mao->naipe==1){
        printf("%d de ESPADA.\n", p[vez].mao->numero);
    }else if(p[vez].mao->naipe==2){
        printf("%d de OURO.\n", p[vez].mao->numero);
    }else{
        printf("%d de COPAS.\n", p[vez].mao->numero);
    }
    aux=aux->anterior;
  }while(aux!=NULL);

}
void imprimeMao(jogador *p, int vez) {//imprime a mão do jogador
    if(p[vez].mao->naipe==0){
      printf("%d de PAUS.\n", p[vez].mao->numero);
    }else if(p[vez].mao->naipe==1){
        printf("%d de ESPADA.\n", p[vez].mao->numero);
    }else if(p[vez].mao->naipe==2){
        printf("%d de OURO.\n", p[vez].mao->numero);
    }else{
        printf("%d de COPAS.\n", p[vez].mao->numero);
    }
}
void imprimeMonte(lista *p) {//imprime a mão do jogador
    elemento* auxLi=p->inicio;
    int c=0;
    do{
      c++;
      if(auxLi->carta->naipe==0){
        printf("%d°: %d de PAUS\n",c,auxLi->carta->numero);
      }else if(auxLi->carta->naipe==1){
          printf("%d°: %d de ESPADA\n",c,auxLi->carta->numero);
      }else if(auxLi->carta->naipe==2){
          printf("%d°: %d de OURO\n",c,auxLi->carta->numero);
      }else{
          printf("%d°: %d de COPAS\n",c,auxLi->carta->numero);
      }
      auxLi=auxLi->proximo;
    }while(auxLi!=NULL);
}
void imprimeTopo(jogador* jogador, int vez){
  if(jogador[vez].mao->naipe==0){
    printf("%d de PAUS.\n", jogador[vez].mao->numero);
  }else if(jogador[vez].mao->naipe==1){
      printf("%d de ESPADA.\n", jogador[vez].mao->numero);
  }else if(jogador[vez].mao->naipe==2){
      printf("%d de OURO.\n", jogador[vez].mao->numero);
  }else{
      printf("%d de COPAS.\n", jogador[vez].mao->numero);
  }
}
int inserirUltimaPosicao(lista* l,carta* aux){ // insere membro na lista
    if(estaVaziaLista(l)){
        elemento* novo= criaNovo();
        novo->carta->numero=aux->numero;
        novo->carta->naipe=aux->naipe;
        novo->proximo=NULL;
        l->inicio=novo;
        return 1;
    }else{
        elemento *aux1=l->inicio;
      while(aux1->proximo != NULL){
          aux1 = aux1->proximo;
      }
        elemento*novo= criaNovo();
        novo->carta->numero=aux->numero;
        novo->carta->naipe=aux->naipe;
        novo->proximo=NULL;
        aux1->proximo=novo;
        return 1;
    }
    return 0;
}
int inserirOrdenado(lista* l,carta* aux){ 
    elemento* novo= criaNovo();
    elemento* auxLi;
    elemento* ant;
  if(estaVaziaLista(l)==1){
    novo->carta->naipe=aux->naipe;
    novo->carta ->numero=aux->numero;
    novo->proximo=NULL;
    l->inicio=novo;
    return 1;
  }else{
    auxLi=l->inicio;
    ant=NULL;
    while(aux->numero > auxLi->carta->numero && auxLi!=NULL){
      ant=auxLi;
      auxLi=auxLi->proximo;
    }
    if(ant==NULL){
      novo->carta->naipe=aux->naipe;
      novo->carta ->numero=aux->numero;
      novo->proximo=l->inicio;
      l->inicio=novo;
      return 1;
    }else{
      novo->carta->naipe=aux->naipe;
      novo->carta ->numero=aux->numero;
      novo->proximo=auxLi;
      ant->proximo=novo;
      return 1;
    }
  }
  return 0;
}
int removePosicao(lista* l, int posicao, carta* aux) {// retira membro da lista
if (l->inicio == NULL || posicao <= 0) {
        printf("Posicao invalida\n");
        return 0;
    }
    if (posicao == 1) {
        // Remover o primeiro elemento
        elemento *auxL = l->inicio;
        aux->numero = auxL->carta->numero;
        aux->naipe= auxL->carta->naipe;
        l->inicio = auxL->proximo;
        return 1;
    } else {
        // Encontrar o elemento anterior ao que será removido
        elemento *anterior = NULL;
        elemento *atual = l->inicio;
        int contador = 1;
        while (atual != NULL && contador < posicao) {
            anterior = atual;
            atual = atual->proximo;
            contador++;
        }
        if (atual == NULL) {
            printf("Posicao invalida\n");
            return 0;
        }
        // Remover o elemento na posição especificada
        aux->numero = atual->carta->numero;
        aux->naipe = atual->carta->naipe;
        anterior->proximo = atual->proximo;
        free(atual);
        return 1;
    }
  return 0;
}
int removeInicio(lista* l, carta* aux) {
    if(estaVaziaLista(l)==1){
        return 0;
      }else{
        elemento* auxLi= l->inicio;
        l->inicio= auxLi->proximo;
        auxLi->proximo=NULL;
        aux->numero=auxLi->carta->numero;
        aux->naipe=auxLi->carta->naipe;
        free(auxLi);
        return 1;
      }
}  
int removeFim(lista* l, carta* aux) {
    if (estaVaziaLista(l)) {
        return 0;
    } else {
        elemento* atual = l->inicio;
        elemento* ant = NULL;
        if (atual->proximo == NULL) {
            aux->numero = atual->carta->numero;
            aux->naipe = atual->carta->naipe;
            free(atual);
            l->inicio = NULL;  // A lista está vazia agora
            return 1;
        }
        while (atual->proximo != NULL) {
            ant = atual;
            atual = atual->proximo;
        }
        ant->proximo = NULL;
        aux->numero = atual->carta->numero;
        aux->naipe = atual->carta->naipe;
        free(atual);
        return 1;
    }
}
int recuperarPorChave(lista* l, int chave){ //retorna valor da posição em relação a chave
  if (l == NULL) {
    // Adicione uma verificação para lista nula
    return -1;
  }
  int c=1;
  elemento* aux=l->inicio;
  while(chave!=aux->carta->numero && aux->proximo!=NULL){
  aux=aux->proximo;
  ++c;
  }
  if (aux == NULL) {
    // A chave não foi encontrada na lista
    return -1;
  }
  return c;
}
int recuperarPorPosicao(lista* l, int posicao){
  elemento* aux=l->inicio;
  int c=1;
  if(posicao==1){
    return aux->carta->numero;
  }else{
    while(c!=posicao){
      aux=aux->proximo;
      c++;
    }
    return aux->carta->numero;
  }
  return 0;
}
//Funções Pilha
int empilha(pilha*p,carta* aux){ //insere mebro na pilha
      elemento *novo= criaNovo();
      novo->carta->numero=aux->numero;
      p->numItens++;
      novo->carta->naipe=aux->naipe;
      novo->anterior= p->topo;
      p->topo=novo;
      return 1;
}
int desempilha(pilha*p,carta*aux){ //retira membro da pilha
  if (estaVaziaPilha(p) == 0) {
      elemento *auxPilha = p->topo;
      aux->numero = p->topo->carta->numero;
      aux->naipe =p->topo->carta->naipe;
      p->topo = auxPilha->anterior;
      p->numItens--;
      free(auxPilha->carta);
      free(auxPilha);
      return 1;
  }
  return 0;
}
int empilhaJogador(jogador*p,carta* aux){ //insere mebro na pilha
    elemento *novo= criaNovoPilha();
    novo->carta->numero=aux->numero;
    p->num++;
    novo->carta->naipe=aux->naipe;
    novo->anterior= p->topo;
    p->topo=novo;
    return 1;
}
int desempilhajogador(jogador*p,carta*aux){ //retira membro da pilha
  if (estaVaziaJogador(p) == 0) {
      elemento *auxPilha = p->topo;
      aux->numero = p->topo->carta->numero;
      aux->naipe=p->topo->carta->naipe;
      p->topo = auxPilha->anterior;
      p->num--;
      // Libere a memória da carta desempilhada
      free(auxPilha->carta);
      free(auxPilha);
      return 1;
  } 
  return 0;
}
// Baralho
void embaralha(pilha* p,int numBaralho){ // cria uma lista em com todas as cartas de forma ordenada e depois passa para uma pilha embaralhando
    lista* monte= criaLista();
    int numCartas=0;
    int posicao;
    carta aux;
    int naipe;

    for(int i = 0; i < numBaralho; i++) {
      for(int j = 0; j < 4; j++) {
        for(int k = 1; k <= 13; k++) {
          aux.numero = k;
          aux.naipe = j;
          inserirUltimaPosicao(monte, &aux);
          numCartas++;
        }
      }
    }
    while(numCartas>0){
      srand((unsigned)time(NULL));
      posicao=(rand()%numCartas)+1;
      //printf("%d ",posicao);
      removePosicao(monte,posicao,&aux);
      //printf("%d ",aux.numero);
      //printf("%d\n",aux.naipe);
      empilha(p,&aux);
      numCartas--;
    }
    limpaLista(monte);
}
void descartar(jogador* jogadores,int vez, lista* descarte){ // joga a carta no descarte
    carta aux;
    aux.numero=jogadores[vez].mao->numero;
    aux.naipe=jogadores[vez].mao->naipe;
  
    inserirUltimaPosicao(descarte, &aux);
}
// Jogador
jogador *criaJogador(int numJogadores) {
    jogador* novoJogador = (jogador*)malloc(numJogadores * sizeof(jogador));

    if (novoJogador == NULL) {
        printf("Erro: Falha na alocação de memória para jogadores\n");
        exit(1);
    } else {
        for (int i = 0; i < numJogadores; i++) {
            novoJogador[i].topo = NULL;
            novoJogador[i].mao = (carta*)malloc(sizeof(carta));
            if (novoJogador[i].mao == NULL) {
                printf("Erro: Falha na alocação de memória para a mão do jogador %d\n", i);
                return NULL;;
            }
            novoJogador[i].num = 0;
        }
        return novoJogador;
    }
}
void ordenaJogadores(jogador* jogadores, int numJogadores) {
    int trocou;
    do {
        trocou = 0;
        for (int i = 0; i < numJogadores; i++) {
            if (!estaVaziaJogador(&jogadores[i]) && !estaVaziaJogador(&jogadores[i + 1]) &&
                jogadores[i].topo->carta->numero < jogadores[i + 1].topo->carta->numero) {
                // Troca as cartas nas pilhas
                carta temp = *(jogadores[i].topo->carta);
                desempilhajogador(&jogadores[i], jogadores[i].topo->carta);
                empilhaJogador(&jogadores[i + 1], &temp);
                trocou = 1;
            }
        }
    } while (trocou);
}
void ranking(jogador* jogadores, int numJogadores) {
    int i, j;
    jogador chave;
    for (i = 1; i < numJogadores; i++) {
        chave = jogadores[i];
        j = i - 1;
        // Move os elementos do array jogadores[0..i-1] que são maiores que a chave
        // para uma posição à frente de sua posição atual
        while (j >= 0 && (jogadores[j].num < chave.num || (jogadores[j].num == chave.num && jogadores[j].topo->carta->numero < chave.topo->carta->numero))) {
            jogadores[j + 1] = jogadores[j];
            j = j - 1;
        }
        jogadores[j + 1] = chave;
    }

    // Imprime o ranking
    printf("Ranking:\n");
    for (int i = 0; i < numJogadores; i++) {
        printf("%dº lugar: %s - %d cartas na pilha\n", i + 1, jogadores[i].nome, jogadores[i].num);
        imprimirJogador(jogadores, i);
    }
}
//cria uma "pilha" dos jogadores
int loop(int numJogadores, int vez){ // mantém o jogo em loop
  if(vez+1==numJogadores){
    vez=0;
  }else{
    vez++;
  }
  return vez;
}
void compraCarta(jogador* jogador, pilha* p, int vez) {
    if (jogador == NULL || jogador[vez].mao == NULL) {
        printf("Erro: jogador ou jogador[%d].mao é nulo\n", vez);
        exit(1);
    }
    carta aux;
    if (!desempilha(p, &aux)) {
        printf("Erro: não foi possível desempilhar uma carta\n");
        return;
    }else{
      jogador[vez].mao->numero = aux.numero;
      jogador[vez].mao->naipe = aux.naipe;
    }
}
void pegaDescarte(jogador* jogador,int vez, lista* descarte){
  int posicao;
  carta aux;
  posicao=recuperarPorChave(descarte, jogador[vez].mao->numero);
  removePosicao(descarte,posicao, &aux);
  empilhaJogador(&jogador[vez], &aux);
  aux.numero=jogador[vez].mao->numero;
  aux.naipe=jogador[vez].mao->naipe;
  empilhaJogador(&jogador[vez], &aux);
}
void roubaMonte(jogador* jogador, int vez,int igualJogador){
  pilha* pilhaAux= criaPilha();
  carta aux;
  while(jogador[igualJogador].num!=0){
    desempilhajogador(&jogador[igualJogador], &aux);
    empilha(pilhaAux, &aux);
  }
  while(pilhaAux->numItens!=0){
    desempilha(pilhaAux, &aux);
    empilhaJogador(&jogador[vez], &aux);
  }
  liberaPilha(pilhaAux);
  aux.numero=jogador[vez].mao->numero;
  aux.naipe=jogador[vez].mao->naipe;
  empilhaJogador(jogador, &aux);
}

int main() {
  int numJog, numBaralho;
  pilha* baralho=criaPilha();

  lista* descarte= criaLista();
  jogador* jogadores;
  do{
    printf("Qual o número de jogadores?");
    scanf("%d",&numJog);
    if(numJog<=1){
    printf("\n\nNúmero de jogadores insuficientes.\n\n");
    }
      jogadores=criaJogador(numJog);
    for(int i=0;i<numJog;i++){
      printf("Qual o nome do jogador %d?",i+1);
      setbuf(stdin, NULL);
      fgets(jogadores[i].nome, 11, stdin);
      size_t length = strlen(jogadores[i].nome);
      if (jogadores[i].nome[length - 1] == '\n') {
          jogadores[i].nome[length - 1] = '\0';  // Substitui a quebra de linha por um caractere nulo
      }
    }
  }while(numJog<=1);
  do{
    printf("Quantos baralhos serão utilizados?");
    scanf("%d",&numBaralho);
    if(numBaralho<1){
    printf("\n\nNúmero de baralhos insuficientes.\n\n");
    }
    embaralha(baralho,numBaralho);
  }while(numBaralho<1);
// Inicio do jogo
  int vez=0;
  int opcao=0;
  int fim=1;
  int contador=0;
  int posicaoIgual=0;
  int igualJogador;
  
do{
    do{
      if(baralho->numItens==0){
      fim=0;
        break;
      }
      opcao=0;
      igualJogador=0;
      printf("Vez do jogador %s.\n",jogadores[vez].nome);
      compraCarta(jogadores, baralho, vez);
      printf("Jogador %s, sua carta é:\n", jogadores[vez].nome);
      imprimeMao(jogadores,vez);
      printf("Você tem %d cartas na pilha.\n",jogadores[vez].num);
        for(int i=0;i<numJog;i++){
          if(i!=vez && jogadores[i].num>0){
            if(jogadores[vez].mao->numero==jogadores[i].topo->carta->numero){
              printf("Sua carta é igual a do jogador %s. Ele tem %d na pilha\n" ,jogadores[i].nome, jogadores[i].num);
              printf("Precione %d para pegar a pilha do jogador\n",2);
              scanf("%d",&opcao);
              contador++;
              igualJogador=i;
            }
          }
        }
      if(jogadores[vez].num>1 && jogadores[vez].mao->numero==jogadores[vez].topo->carta->numero){
        printf("Sua carta é igual a do topo da pilha. Você tem %d cartas na pilha.\n",jogadores[vez].num);
        printf("Precione %d para colocar a carta na sua pilha\n",3);
        scanf("%d",&opcao);
      }
      if(descarte->inicio==NULL){
        opcao=0;
      }else{
        posicaoIgual=recuperarPorChave(descarte,jogadores[vez].mao->numero);
        if(jogadores[vez].mao->numero==recuperarPorPosicao(descarte, posicaoIgual)){
          printf("Sua carta é igual a do descarte, precione %d para pegar a carta do descarte\n",1);
          scanf("%d",&opcao);
        }
      }
      switch(opcao){
        case 0:
          printf("\n\nSua carta não é igual a nenhuma outra. Ela irá para a zona de descarte.");
          descartar(jogadores, vez, descarte);
          printf("Pressione ENTER tecla para continuar.\n\n");
          setbuf(stdin, NULL);
          getchar();
          opcao=-1;
          break;
        case 1:
            printf("\n\nVocê pegou a carte %d da área de descarte. Agora ela está na sua pilha.\n",jogadores[vez].mao->numero);
          pegaDescarte(jogadores, vez, descarte);
          printf("Seu topo é:\n");
          imprimeTopo(jogadores,vez);
          printf("Você tem %d cartas na pilha.\n",jogadores[vez].num);
          printf("\n\n");
          break;
      case 2:
            printf("Você pegou a pilha do jogador %s.\n\n",jogadores[igualJogador].nome);
            roubaMonte(jogadores, vez, igualJogador);
            printf("Seu topo é:\n");
            imprimeTopo(jogadores,vez);
            printf("Você tem %d cartas na pilha.\n",jogadores[vez].num);
            printf("\n\n");
            break;
        case 3:
            printf("\n\nVocê colocou a carta %d na sua pilha.\n",jogadores[vez].mao->numero);
            carta aux;
            aux.naipe=jogadores[vez].mao->naipe;
            aux.numero=jogadores[vez].mao->numero;
            empilhaJogador(&jogadores[vez],&aux);
            printf("Seu topo é:\n");
            imprimeTopo(jogadores,vez);
            printf("Você tem %d cartas na pilha.\n",jogadores[vez].num);
            printf("\n\n");
            break;
          }
      }while(opcao!=-1);
      vez=loop(numJog, vez);
  }while(fim!=0);
  printf("\nFIM!!!!\n\n");
  ordenaJogadores(jogadores, numJog);
  ranking(jogadores,numJog);
  liberaPilha(baralho);
  return 0;
}