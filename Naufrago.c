/**
    * Programa: Jogo simples de sobrevivencia a partir de escolhas " Naufrago "
    * Data de criacao: 03/09/2019
    * Autor: Gabriel Barberiz
	* github.com/GBarberiz
    * Ultima modificao em 09/12/2019 por Gabriel Barberiz
**/

/**     NOTAS DE TRABALHO

    * Proximas versoes
        - Colocar a probabilidade de craftar errado, e ir adicionando +2 no bonus de arma por fracasso
            - tipo nivel de experiencia

**/
/* BIBLIOTECAS */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
/*DEFINICAO DE CORES DE TEXTO*/
#define COLOR_RED "\x1b[91m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[96m"
#define COLOR_GREEN "\e[0;92m"
#define COLOR_RESET "\x1b[0m"
#define COLOR_WHITE "\x1b[97m"
/* DEFINICAO DE DIFICULDADE */
#define arqueologo '1' /*facil*/
#define leite_com_pera 1
#define cleite_com_pera '1'

#define fotografo '2' /*medio*/
#define cha 2
#define ccha '2'

#define tradutor '3' /*dificil*/
#define cafe 3
#define ccafe '3'
/* DEFINICAO DE LUGARES */
#define Praia 1
#define Floresta 2
#define Montanha 3
#define Lago 4
#define Mar 5
#define Lugar_alto 6
#define Floresta_2 7
#define Cachoeira 8
#define Nascente_cachoeira 9
#define Encosta_da_montanha 10

typedef struct
{
    int saude;
    int fome;
    int sede;
} Sttatus;
typedef struct
{
    int pedras;
    int graveto;
    int fibra_natural;
    int concha;
    int madeira;
    int carne_crua;
} Itens;
typedef struct
{
    int lanca; /*+ 10 dano*/                      /* Mao sozinha da 5 de dano */
    int machado;                                  /*+7 dano*/
    int faca;                                     /* +5 dano*/
    int recipiente_agua; /* 2 fibras */           /* guarda agua +50 de sede */
    int recipiente_agua_cheio;                    /* x recipiente_agua + local certo*/
    int barco_1; /* 20 madeiras, 20 fibras*/      /* quando tentar sair da ilha ele se quebra */
    int escudo_barco; /* 20 conchas, 10 fibras */ /* protege o barco de quebrar */
    int barco_2; /* barco_1 + escudo_barco */     /* ajuda a fugir da ilha. Final do jogo */
    int carne_assada;                             /* x carnes + 1 fogueira (gasta a fogueira, mas assa todas as carnes*/
    int fogueira;                                 /* 3 gravetos + 1 fibra */
    int capacete;
} Itens2;
typedef struct
{
    int mar;
    int praia;
    int floresta;
    int lago;
    int montanha;
    int lugar_alto;
    int floresta_2;
    int cachoeira;
    int nascente_cachoeira;
    int encosta;
} Biomas;
/* PROTOTIPACAO DE FUNCOES*/
/* MENUS*/
void iniciar_jogo();
void status(int *, int *, int *);
void menu();
void regras();
void regra_letreiro();
void Morreu_bobao();
void creditos();
void inventario(Itens *, Itens2 *, int, int, int, Sttatus *, int);
void inventario_letreiro();
void fcraft_letreiro();
/* PROBABILIDADES  E ACONTECIMENTOS */
int num_aleatorio();
int procura_item(int, char, char, int *, int *, int *, int *, int *, int *, int *);
void custo(int, int *, int *);
void fcraft(Itens *, Itens2 *, int);
int transicao(int, char, Itens *, Itens2 *, char, int, Sttatus *);
void pesca(int, Itens *, Itens2 *, Sttatus *, char);
void queda_cachoeira(int *);
int Subida_Descida_Montanha(int, Sttatus *, Itens2 *, Itens *, char);
void batalha(Itens *, Itens2 *, char, int, int, Sttatus *, int);
void animais(int, int, int);
/* BONUS */
int bonus_busca(char);
int bonus_arma(char);
int bonus_d(char);
/* FINAIS */
void final_1();
void final_2(int *, int *, int *);
void final_3();
void final_4();

int main()
{
    /* CONFIGURA O PROMPT */
    system("MODE con cols=84 lines=25");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitle(" Naufrago ");
    srand(time(NULL));
    /* CHAMA O MENU DO JOGO */
    menu();
    regras();
    iniciar_jogo();

    return 0;
}

/* JOGO */
void iniciar_jogo()
{
    SetConsoleTitle(" Naufrago ");
    system("cls");
    /* Variaveis */
    char profissao;
    char dificuldade;
    int i, aux;
    /* FALAS INICIAIS PARA DEFINICAO DE DIFICULDADE (ESCOLHA DA PROFISSAO) */
    printf("\n Voce esta em um aviao em uma viagem muito importante!\n\n");
    printf(COLOR_BLUE " Esta um tempo muito ruim la fora, tem muitas nuvens e mal consigo ver o chao...\n\n");
    printf(COLOR_WHITE " Apos um tempo perdido em seus pensamentos, voce sente que esta sendo observado.");
    printf("\n                                       ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(500);
    }
    printf("\n Voce se vira rapidamente tirando sua cabeca da janela.\n");
    printf(" A aeromoca esta parada ao seu lado, voce nao entende bem o motivo.\n Ela, que esta com um olhar de impressionada, comenta: \n\n");
    printf(COLOR_YELLOW " Voce esta muito bem vestido! Me parece alguem importante, com o que voce trabalha? \n\n");
    printf(COLOR_WHITE "                                   Qual seu trabalho?\n\n");
    printf("                                     Arqueologo(1)\n                                     Fotografo (2)\n                                     Tradutor  (3)\n\n                                          " COLOR_RED);

    fflush(stdin);
    fgets(&profissao, 2, stdin);

    /* SE NAO ESCOLHER UM NUMERO SETA PROFISSAO NENHUMA*/
    if (profissao < '1' || profissao > '3')
    {
        profissao = '0';
    }

    /* POSSIBILIDADES DE RESPOSTA DA AEROMOCA */
    switch (profissao)
    {
    case (fotografo):
        printf(COLOR_YELLOW "\n Nossa que legal! Sempre gostei de fotografar os passaros no ceu, meu sonho um dia   era poder voar com eles, mas sem estar dentro de um aviao e claro! \n");
        ;
        break;

    case (arqueologo):
        printf(COLOR_YELLOW "\n Interessante... Quantas armas antigas voce ja encontrou?  ^^'\n");
        printf(" Desculpe o encomodo, e que eu gosto muito de antiguidades.\n");
        break;

    case (tradutor):
        printf(COLOR_YELLOW "\n E dificil encontrar alguem que seja tradutor hoje em dia, nao?\n Ultimamente as pessoas so utilizam tradutores online.\n");
        printf(" A tecnologia tem avancado muito rapidamente...\n");
        break;

    default:
        printf(COLOR_YELLOW "\n Se nao quiser me falar tudo bem, a escolha a sua.\n");
    }

    printf(COLOR_WHITE "\n");
    Sleep(250);
    system("pause");
    system("cls");

    /* FALAS INICIAIS2 PARA DEFINICAO DE DIFICULDADE (ESCOLHA DA BEBIDA)*/
    printf(COLOR_YELLOW "\n Hm... \n O senhor parece estar com sede, aceita alguma bebida? Eu tenho essas no carrinho:\n\n");
    printf(COLOR_WHITE "                          Voce deseja tomar qual bebida?\n\n");
    printf("                                 Leite com pera(1)\n                                 Cha           (2)\n                                 Cafe          (3)\n\n                                         " COLOR_RED);

    fflush(stdin);
    fgets(&dificuldade, 2, stdin);

    /* POSSIBILIDADES DE RESPOSTA A ESCOLHA DA BEBIDA */
    if (dificuldade <= '3' && dificuldade >= '1')
    {
        printf(COLOR_WHITE "\n No momento em que a aeromoca se vira parar pegar a sua bebida, voce sente o aviao   tremer.\n\n");
    }
    else
    {
        printf(COLOR_YELLOW "\n Tudo bem que nao queira, acho que devo treinar mais para saber quem esta ou nao     com sede...\n\n");
        printf(COLOR_WHITE " Assim que a aeromoca se vira, voce sente o aviao tremer.\n");
    }
    printf(COLOR_BLUE " O que esta acontecendo?\n");
    printf(COLOR_WHITE "\n Tudo comeca a ficar mais leve, como se voce estivesse flutuando no ar.\n\n");

    printf("\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1000);
    }
    printf("\n\n\n");
    system("pause");
    system("cls");
    printf(COLOR_BLUE "\n Sera que o aviao esta caindo?\n");
    printf(COLOR_WHITE "\n Tudo fica silencioso, logo em seguida um ESTRONDO!!\n");
    printf(" Com o impacto voce apaga completamente...\n\n");
    printf("\n Depois de muito tempo voce acorda em uma praia...\n");
    printf(COLOR_BLUE "\n O que aconteceu?\n Como consegui sobreviver?\n Como cheguei aqui? Espera, onde e aqui?\n\n\n");
    printf(COLOR_WHITE " Voce se levanta com muito esforco e tenta olhar em volta para saber onde esta...\n");
    printf(COLOR_BLUE "\n Estou em uma ilha deserta? Por que isso aconteceu comigo?");
    if (profissao == tradutor)
    {
        printf("\n                                    ");
        for (i = 0; i < 3; i++)
        {
            printf(" .");
            Sleep(1000);
        }
        printf("\n Meu deus, perdi meu oculos!!!\n Como se ja nao fosse dificil sobreviver com visao boa...\n\n\n\n" COLOR_WHITE);
    }
    else
    {
        printf(" Eu realmente sou muito    azarado.\n");
        printf("\n                                      ");
        for (i = 0; i < 3; i++)
        {
            printf(" .");
            Sleep(1000);
        }
        printf(COLOR_WHITE "\n\n\n\n");
    }
    system("pause");
    system("cls");

    /*************************************************** COMECA O JOGOOOO AQUIIII ***********************************************************/

    /*VARIAVEIS*/
    char escolha;
    int local, sos = 0;
    Sttatus estatus;
    Itens item;
    Itens2 craft;
    Biomas passagem;

    /* DEFINE AS VARIAVEIS PADROES */
    estatus.saude = 50;
    estatus.sede = 50;
    estatus.fome = 50;
    item.pedras = 0;
    item.graveto = 0;
    item.fibra_natural = 0;
    item.concha = 0;
    item.madeira = 0;
    item.carne_crua = 0;
    craft.lanca = 0;
    craft.machado = 0;
    craft.faca = 0;
    craft.recipiente_agua = 0;
    craft.barco_1 = 0;
    craft.escudo_barco = 0;
    craft.barco_2 = 0;
    craft.carne_assada = 0;
    craft.fogueira = 0;
    craft.recipiente_agua_cheio = 0;
    craft.capacete = 0;
    passagem.mar = 0;
    passagem.floresta = 0;
    passagem.lago = 0;
    passagem.montanha = 0;
    passagem.praia = 0;
    passagem.lugar_alto = 0;
    passagem.floresta_2 = 0;
    passagem.cachoeira = 0;
    passagem.nascente_cachoeira = 0;
    passagem.encosta = 0;
    /* DEIXA O COMECO MAIS FACIL DEPENDENDO DA ESCOLHA DA DIFICULDADE*/
    if (dificuldade == cleite_com_pera || dificuldade == ccha)
        estatus.sede += 10;
    else if (dificuldade != ccafe)
        estatus.sede -= 10;

    /************************************************************** PRAIA *******************************************************************/
LOCAL_PRAIA:
    SetConsoleTitle(" Naufrago - Praia ");
    system("cls");
    fflush(stdin);
    local = Praia;

    do
    {
        /* SE FOR A PRIMEIRA PASSAGEM PELA PRAIA */
        if (passagem.praia == 0)
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
            printf(COLOR_BLUE "\n Cara, realmente parece que estou sozinho neste lugar.\n Isso me lembra muito aqueles jogos de sobrevivencia que jogava quando mais novo.\n");
            printf(" Bom, talvez eles servirao pra me guiar nessa sobrevivencia.\n");
            printf(" Procurar itens na praia com certeza vai deixar com mais sede que o normal.\n");
        }
        else
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
        }

        printf(COLOR_WHITE "\n                                Voce esta na Praia.\n");
        printf("\n                             O que voce vai fazer agora?\n");
        if (item.graveto >= 1 && sos == 0)
            printf("\n                              Procurar Itens na praia(1)\n                              Entrar na floresta(2)\n                              Ir para o mar(3)\n                              Escrever SOS na areia(4)\n\n                                         " COLOR_RED);
        else
            printf("\n                              Procurar Itens na praia(1)\n                              Entrar na floresta(2)\n                              Ir para o mar(3)\n                              Inventario(4)\n\n                                         " COLOR_RED);

        fflush(stdin);
        fgets(&escolha, 2, stdin);

        /* VERIFICA A ESCOLHA */
        switch (escolha)
        {
        case ('1'):
            procura_item(local, profissao, dificuldade, &item.pedras, &item.fibra_natural, &item.concha, &item.graveto, &estatus.fome, &estatus.sede, &estatus.saude);
            custo(local, &estatus.fome, &estatus.sede);
            break;

        case ('2'):
            passagem.praia = 1;
            custo(local, &estatus.fome, &estatus.sede);
            aux = transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            if (aux == 1)
                goto LOCAL_FLORESTA;
            else
                goto LOCAL_PRAIA;
            break;

        case ('3'):
            passagem.praia = 1;
            custo(local, &estatus.fome, &estatus.sede);
            transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            goto LOCAL_MAR;
            break;

        case ('4'):
            if (item.graveto >= 1 && sos == 0)
            {
                sos = 1;
                custo(local, &estatus.fome, &estatus.sede);
                final_4();
            }
            else
                inventario(&item, &craft, profissao, bonus_arma(profissao), local, &estatus, 0);
            break;

        default:
            passagem.praia == 0 ? printf("\n") : printf("\n\n\n\n\n");
            printf(COLOR_BLUE " Tenho que fazer algo, esse sol esta me derretendo.\n\n");
            /* CUSTO POR FICAR PARADO E BRINCAR COM O CARA QUE FEZ O JOGO */
            estatus.sede -= 3;
            estatus.fome -= 2;
            break;
        }
        passagem.praia = 1;
        printf(COLOR_WHITE);
        system("pause");
        system("cls");
    } while (1);

    /************************************************************ FLORESTA ******************************************************************/
LOCAL_FLORESTA:
    SetConsoleTitle(" Naufrago - Floresta ");
    system("cls");
    fflush(stdin);
    local = Floresta;

    do
    {
        /* SE FOR A PRIMEIRA PASSAGEM PELA FLORESTA */
        if (passagem.floresta == 0)
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
            printf(COLOR_BLUE "\n Ainda bem que sai daquele sol.\n Ele possivelmente ia fazer eu morrer de sede rapidinho.\n");
            printf(" Acho que agora que vai comecar a minha verdadeira sobrevivencia.\n");
            printf(" Esse lugar me parece perigoso, acho que vou tomar cuidado ao fazer as coisas.\n");
        }
        else
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
        }

        printf(COLOR_WHITE "\n                                Voce esta na Floresta.\n");
        printf("\n                             O que voce vai fazer agora?\n");
        if (passagem.lugar_alto == 1)
        {
            printf("\n                              Procurar Itens na floresta(1)\n                              Ir para o lago(2)\n                              Ir para a praia(3)\n                              Inventario(4)\n\n                                         " COLOR_RED);
        }
        else
        {
            printf("\n                              Procurar Itens na floresta(1)\n                              Ir para Lugar alto(2)\n                              Ir para a praia(3)\n                              Inventario(4)\n\n                                         " COLOR_RED);
        }
        fflush(stdin);
        fgets(&escolha, 2, stdin);

        /* VERIFICA A ESCOLHA */
        switch (escolha)
        {
        case ('1'):
            procura_item(local, profissao, dificuldade, &item.pedras, &item.fibra_natural, &item.concha, &item.graveto, &estatus.fome, &estatus.sede, &estatus.saude);
            custo(local, &estatus.fome, &estatus.sede);

            break;

        case ('2'):
            passagem.floresta = 1;
            custo(local, &estatus.fome, &estatus.sede);
            if (passagem.lugar_alto == 1)
            {
                aux = transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
                if (aux == 1)
                    goto LOCAL_LAGO;
                else if (aux == 2)
                    goto LOCAL_FLORESTA_2;
                else if (aux == 0)
                    goto LOCAL_FLORESTA;
            }
            else
            {
                system("cls");
                printf(COLOR_WHITE "\n\n\n                  Voce esta caminhando em direcao ao seu destino.\n");
                printf("\n\n\n                                      ");
                for (i = 0; i < 3; i++)
                {
                    printf(" .");
                    Sleep(1000);
                }
                printf("\n\n\n                     Voce chegou em Lugar Alto sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
                system("pause");
                goto LOCAL_LUGAR_ALTO;
            }
            break;

        case ('3'):
            passagem.floresta = 1;
            custo(local, &estatus.fome, &estatus.sede);
            aux = transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            if (aux == 1)
                goto LOCAL_PRAIA;
            else
                goto LOCAL_FLORESTA;
            break;

        case ('4'):
            inventario(&item, &craft, profissao, bonus_arma(profissao), local, &estatus, 0);
            break;

        default:
            passagem.floresta == 0 ? printf("\n") : printf("\n\n\n\n\n");
            printf(COLOR_BLUE " Meus pes estao pinicando, devem ser essas formigas...\n\n");
            /* CUSTO POR FICAR PARADO E BRINCAR COM O CARA QUE FEZ O JOGO */
            estatus.saude -= 3;
            estatus.fome -= 2;
            break;
        }
        passagem.floresta = 1;
        printf(COLOR_WHITE);
        system("pause");
        system("cls");
    } while (1);

    /***************************************************************** MAR ******************************************************************/
LOCAL_MAR:
    SetConsoleTitle(" Naufrago - Mar ");
    system("cls");
    fflush(stdin);
    local = Mar;
    do
    {
        /* SE FOR A PRIMEIRA PASSAGEM PELA FLORESTA */
        if (passagem.mar == 0)
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
            printf(COLOR_BLUE "\n Essa agua esta tao fresca.\n");
            printf(" Eu poderia ficar aqui o dia todo\n");
            printf(" Seria legal tentar pegar alguns peixes aqui.\n");
        }
        else
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
        }

        printf(COLOR_WHITE "\n                                Voce esta no Mar.\n");
        printf("\n                             O que voce vai fazer agora?\n");
        printf("\n                              Pescar no Mar(1)\n                              Ir para a Praia(2)\n                              Sair da ilha(3)\n                              Inventario(4)\n\n                                         " COLOR_RED);

        fflush(stdin);
        fgets(&escolha, 2, stdin);

        /* VERIFICA A ESCOLHA */
        switch (escolha)
        {
        case ('1'):
            pesca(local, &item, &craft, &estatus, profissao);
            custo(local, &estatus.fome, &estatus.sede);
            break;

        case ('2'):
            passagem.mar = 1;
            custo(local, &estatus.fome, &estatus.sede);
            transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            goto LOCAL_PRAIA;
            break;

        case ('3'):
            if (craft.barco_2 == 1)
                final_3();
            else if (craft.barco_1 == 1)
            {
                passagem.mar = 1;
                final_2(&estatus.saude, &estatus.sede, &estatus.fome);
                craft.barco_1 -= 1;
                goto LOCAL_PRAIA;
            }
            else
                final_1();
            break;

        case ('4'):
            inventario(&item, &craft, profissao, bonus_arma(profissao), local, &estatus, 0);
            break;

        default:
            passagem.mar == 0 ? printf("\n") : printf("\n\n\n\n\n");
            printf(COLOR_BLUE " Eu poderia facilmente fugir daqui com um barco...\n\n\n");
            estatus.sede -= 3;
            estatus.fome -= 2;
            break;
        }
        passagem.mar = 1;
        printf(COLOR_WHITE);
        system("pause");
        system("cls");
    } while (1);

    /************************************************************ LUGAR ALTO ****************************************************************/
LOCAL_LUGAR_ALTO:
    SetConsoleTitle(" Naufrago - Lugar Alto ");
    system("cls");
    fflush(stdin);
    local = Lugar_alto;
    do
    {
        if (passagem.lugar_alto == 0)
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
            printf(COLOR_BLUE "\n Esse Local tem uma boa vista.\n");
            printf(" Eu poderia ficar aqui o dia todo admirando\n\n");
        }
        else
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
        }

        printf(COLOR_WHITE "\n                             Voce esta em um Lugar Alto.\n");
        printf("\n                             O que voce vai fazer agora?\n");
        printf("\n                              Olhar a Paisagem(1)\n                              Ir para a Floresta(2)\n                              Inventario(3)\n\n                                         " COLOR_RED);

        fflush(stdin);
        fgets(&escolha, 2, stdin);

        /* VERIFICA A ESCOLHA */
        switch (escolha)
        {
        case ('1'):
            if (passagem.lugar_alto == 0)
            {
                int sucesso = 50 + bonus_busca(profissao) + bonus_d(dificuldade);
                aux = num_aleatorio();
                system("cls");
                printf(COLOR_WHITE "\n\n\n                      Voce olha para paisagem em busca de algo.\n");
                printf("\n\n\n                                      ");
                for (i = 0; i < 3; i++)
                {
                    printf(" .");
                    Sleep(1000);
                }
                if (aux <= sucesso)
                {
                    printf(COLOR_BLUE "\n\n\n Aquilo ali e um lago?\n Ate que enfim poderei tomar agua!\n\n\n\n\n\n\n\n\n\n\n\n" COLOR_WHITE);
                    passagem.lugar_alto = 1;
                }
                else
                {
                    printf(COLOR_BLUE "\n\n\n Nao encontrei nenhum lugar para tomar agua...\n Preciso continuar procurando!\n\n\n\n\n\n\n\n\n\n\n\n" COLOR_WHITE);
                    sucesso += 7;
                }
                custo(local, &estatus.fome, &estatus.sede);
            }
            else
            {
                printf(COLOR_BLUE "\n\n\n Indo pela floresta eu posso chegar ao lago!\n\n\n\n\n");
            }
            break;

        case ('2'):
            custo(local, &estatus.fome, &estatus.sede);
            transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            goto LOCAL_FLORESTA;
            break;

        case ('3'):
            inventario(&item, &craft, profissao, bonus_arma(profissao), local, &estatus, 0);
            break;

        default:
            passagem.lugar_alto == 0 ? printf("\n") : printf("\n\n\n\n\n");
            printf(COLOR_BLUE " Eu posso achar algum lugar para tomar agua aqui perto...\n\n\n");
            estatus.sede -= 3;
            estatus.fome -= 2;
            break;
        }
        printf(COLOR_WHITE);
        system("pause");
        system("cls");
    } while (1);

    /**************************************************************** LAGO ******************************************************************/

LOCAL_LAGO:
    SetConsoleTitle(" Naufrago - Lago ");
    system("cls");
    fflush(stdin);
    local = Lago;
    do
    {
        /* SE FOR A PRIMEIRA PASSAGEM PELO LAGO */
        if (passagem.lago == 0)
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
            printf(COLOR_BLUE "\n Essa agua parece estar tao fresca.\n");
            printf(" Eu poderia beber ela.\n");
            printf(" Espero nao pegar nenhuma doenca.\n");
        }
        else
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
        }

        printf(COLOR_WHITE "\n                                  Voce esta no Lago.\n");
        printf("\n                             O que voce vai fazer agora?\n");
        printf("\n                              Pescar(1)\n                              Ir para a Floresta(2)\n                              Ir mais Afundo na Floresta(3)\n                              Inventario(4)\n\n                                         " COLOR_RED);

        fflush(stdin);
        fgets(&escolha, 2, stdin);

        /* VERIFICA A ESCOLHA */
        switch (escolha)
        {
        case ('1'):
            pesca(local, &item, &craft, &estatus, profissao);
            custo(local, &estatus.fome, &estatus.sede);
            break;

        case ('2'):
            passagem.lago = 1;
            custo(local, &estatus.fome, &estatus.sede);
            aux = transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            if (aux == 1)
                goto LOCAL_FLORESTA;
            else
                goto LOCAL_LAGO;
            break;

        case ('3'):
            passagem.lago = 1;
            custo(local, &estatus.fome, &estatus.sede);
            aux = transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            if (aux == 1)
                goto LOCAL_FLORESTA_2;
            else
                goto LOCAL_LAGO;
            break;

        case ('4'):
            inventario(&item, &craft, profissao, bonus_arma(profissao), local, &estatus, 0);
            break;

        default:
            passagem.lago == 0 ? printf("\n") : printf("\n\n\n\n\n");
            printf(COLOR_BLUE " Essa agua tem um gosto estranho, mas serve...\n\n\n");
            estatus.sede += 5;
            estatus.fome -= 3;
            estatus.saude -= 2;
            break;
        }
        passagem.lago = 1;
        printf(COLOR_WHITE);
        system("pause");
        system("cls");
    } while (1);

    /************************************************************** FLORESTA 2 **************************************************************/
LOCAL_FLORESTA_2:
    SetConsoleTitle(" Naufrago - Floresta Densa ");
    system("cls");
    fflush(stdin);
    local = Floresta_2;

    do
    {
        if (passagem.floresta_2 == 0)
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
            printf(COLOR_BLUE "\n Nao consigo enxergar muita coisa a minha frente.\n");
            printf(" Essas arvores estao impedindo que a luz chegue aqui.\n");
            printf(" Por sorte, estou acostumado a ficar no escuro do meu quarto sozinho.\n");
        }
        else
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
        }

        printf(COLOR_WHITE "\n                           Voce esta na Floresta Densa.\n");
        printf("\n                            O que voce vai fazer agora?\n");
        printf("\n                             Procurar Itens na Floresta Densa(1)\n                             Ir ao pe da Montanha(2)\n                             Ir para o lago(3)\n                             Inventario(4)\n\n                                        " COLOR_RED);

        fflush(stdin);
        fgets(&escolha, 2, stdin);

        /* VERIFICA A ESCOLHA */
        switch (escolha)
        {
        case ('1'):
            procura_item(local, profissao, dificuldade, &item.pedras, &item.fibra_natural, &item.concha, &item.graveto, &estatus.fome, &estatus.sede, &estatus.saude);
            custo(local, &estatus.fome, &estatus.sede);
            break;

        case ('2'):
            passagem.floresta_2 = 1;
            custo(local, &estatus.fome, &estatus.sede);
            aux = transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            if (aux == 1)
                goto LOCAL_ENCOSTA;
            else
                goto LOCAL_LAGO;
            break;

        case ('3'):
            passagem.floresta_2 = 1;
            custo(local, &estatus.fome, &estatus.sede);
            transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            goto LOCAL_LAGO;
            break;

        case ('4'):
            inventario(&item, &craft, profissao, bonus_arma(profissao), local, &estatus, 0);
            break;

        default:
            passagem.floresta_2 == 0 ? printf("\n") : printf("\n\n\n\n\n");
            printf(COLOR_BLUE " Ficar parado nesse breu nao vai ajudar.\n\n");
            /* CUSTO POR FICAR PARADO E BRINCAR COM O CARA QUE FEZ O JOGO */
            estatus.sede -= 2;
            estatus.fome -= 2;
            break;
        }
        passagem.floresta_2 = 1;
        printf(COLOR_WHITE);
        system("pause");
        system("cls");
    } while (1);

    /************************************************************** ENCOSTA DA MONTANHA *****************************************************/
LOCAL_ENCOSTA:
    SetConsoleTitle(" Naufrago - Encosta da Montanha ");
    system("cls");
    fflush(stdin);
    local = Encosta_da_montanha;
    do
    {
        if (passagem.encosta == 0)
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
            printf(COLOR_BLUE " Essa montanha parece bem alta, talvez la em cima tenha algo interessante.\n");
            printf(" Ela lembra muito o predio em que eu trabalhava...\n\n");
        }
        else
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
        }

        printf(COLOR_WHITE "\n                         Voce esta na Encosta da Montanha.\n");
        printf("\n                            O que voce vai fazer agora?\n");
        printf("\n                             Procurar Itens na Encosta(1)\n                             Dar a volta pela Direita(2)\n                             Dar a volta pela Esquerda(3)\n                             Ir para Floresta Densa(4)\n                             Inventario(5)\n\n                                        " COLOR_RED);
        fflush(stdin);
        fgets(&escolha, 2, stdin);

        /* VERIFICA A ESCOLHA */
        switch (escolha)
        {
        case ('1'):
            procura_item(Montanha, profissao, dificuldade, &item.pedras, &item.fibra_natural, &item.concha, &item.graveto, &estatus.fome, &estatus.sede, &estatus.saude);
            custo(local, &estatus.fome, &estatus.sede);
            break;

        case ('2'):
            passagem.encosta = 1;
            custo(local, &estatus.fome, &estatus.sede);
            transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            goto LOCAL_CACHOEIRA;
            break;

        case ('3'):
            passagem.encosta = 1;
            custo(local, &estatus.fome, &estatus.sede);
            transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            SetConsoleTitle(" Naufrago - Atras da Montanha ");
            do
            {
                system("cls");
                fflush(stdin);
                status(&estatus.saude, &estatus.fome, &estatus.sede);
                printf(COLOR_WHITE "\n                          Voce esta na Atras da Montanha.\n");
                printf("\n                            O que voce vai fazer agora?\n");
                printf("\n                             Subir a Montanha(1)\n                             Continuar Andando(2)\n\n                                        " COLOR_RED);
                fflush(stdin);
                fgets(&escolha, 2, stdin);
                if (escolha == '1')
                {
                    aux = Subida_Descida_Montanha(local, &estatus, &craft, &item, profissao);
                    if (aux == 0)
                        goto LOCAL_ENCOSTA;
                    else
                        goto LOCAL_MONTANHA;
                }
                else if (escolha == '2')
                {
                    custo(local, &estatus.fome, &estatus.sede);
                    transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
                    goto LOCAL_CACHOEIRA;
                }
                else
                {
                    printf(COLOR_BLUE "\n\n\n\n\n\n\n Preciso me decidir...\n\n");
                    estatus.sede -= 3;
                    estatus.fome -= 2;
                }
            } while (1);
            break;

        case ('4'):
            passagem.encosta = 1;
            custo(local, &estatus.fome, &estatus.sede);
            transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            goto LOCAL_FLORESTA_2;
            break;

        case ('5'):
            inventario(&item, &craft, profissao, bonus_arma(profissao), local, &estatus, 0);
            break;

        default:
            passagem.encosta == 0 ? printf("\n") : printf("\n\n\n");
            printf(COLOR_BLUE " Essa montanha parece alta, nao vou conseguir subir por aqui.\n\n\n");
            /* CUSTO POR FICAR PARADO E BRINCAR COM O CARA QUE FEZ O JOGO */
            estatus.sede -= 2;
            estatus.fome -= 2;
            break;
        }
        passagem.encosta = 1;
        printf(COLOR_WHITE);
        system("pause");
        system("cls");
    } while (1);

    /************************************************************** CACHOEIRA ***************************************************************/
LOCAL_CACHOEIRA:
    SetConsoleTitle(" Naufrago - Cachoeira ");
    system("cls");
    fflush(stdin);
    local = Cachoeira;
    do
    {
        if (passagem.cachoeira == 0)
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
            printf(COLOR_BLUE "\n Essa Cachoeira e muito linda.\n");
            printf(" Ela parece ter sua nascente no cume da montanha.\n");
            printf(" A agua dela parece mais pura...\n");
        }
        else
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
        }

        printf(COLOR_WHITE "\n                               Voce esta na Cachoeira.\n");
        printf("\n                             O que voce vai fazer agora?\n");
        printf("\n                              Pescar(1)\n                              Continuar dando a Volta(2)\n                              Ir ao pe da Montanha(3)\n                              Inventario(4)\n\n                                         " COLOR_RED);

        fflush(stdin);
        fgets(&escolha, 2, stdin);

        /* VERIFICA A ESCOLHA */
        switch (escolha)
        {
        case ('1'):
            pesca(local, &item, &craft, &estatus, profissao);
            custo(local, &estatus.fome, &estatus.sede);
            break;

        case ('2'):
            passagem.cachoeira = 1;
            custo(local, &estatus.fome, &estatus.sede);
            transicao(Encosta_da_montanha, '3', &item, &craft, profissao, bonus_arma(profissao), &estatus);

            SetConsoleTitle(" Naufrago - Atras da Montanha ");
            do
            {
                system("cls");
                status(&estatus.saude, &estatus.fome, &estatus.sede);
                fflush(stdin);
                printf(COLOR_WHITE "\n                          Voce esta na Atras da Montanha.\n");
                printf("\n                            O que voce vai fazer agora?\n");
                printf("\n                             Subir a Montanha(1)\n                             Continuar Andando(2)\n\n                                        " COLOR_RED);
                fflush(stdin);
                fgets(&escolha, 2, stdin);
                if (escolha == '1')
                {
                    aux = Subida_Descida_Montanha(local, &estatus, &craft, &item, profissao);
                    if (aux == 0)
                        goto LOCAL_ENCOSTA;
                    else
                        goto LOCAL_MONTANHA;
                }
                else if (escolha == '2')
                {
                    custo(local, &estatus.fome, &estatus.sede);
                    transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
                    goto LOCAL_ENCOSTA;
                }
                else
                {
                    printf(COLOR_BLUE "\n\n\n\n\n\n\n Preciso me decidir...\n\n");
                    estatus.sede -= 3;
                    estatus.fome -= 2;
                }
            } while (1);
            break;

        case ('3'):
            passagem.cachoeira = 1;
            custo(local, &estatus.fome, &estatus.sede);
            transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            goto LOCAL_ENCOSTA;
            break;

        case ('4'):
            inventario(&item, &craft, profissao, bonus_arma(profissao), local, &estatus, 0);
            break;

        default:
            passagem.cachoeira == 0 ? printf("\n") : printf("\n\n\n\n\n");
            printf(COLOR_BLUE " Beber a agua dessa cachoeira foi uma otima ideia...\n\n");
            estatus.sede += 5;
            estatus.fome -= 2;
            break;
        }
        passagem.cachoeira = 1;
        printf(COLOR_WHITE);
        system("pause");
        system("cls");
    } while (1);

    /******************************************************************** MONTANHA **********************************************************/
LOCAL_MONTANHA:
    SetConsoleTitle(" Naufrago - Topo da Montanha ");
    system("cls");
    fflush(stdin);
    local = Montanha;
    do
    {
        if (passagem.montanha == 0)
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
            printf(COLOR_BLUE "\n O que e isso?\n");
            printf(" Parece um capacete feito de ossos.\n");
            printf(" Talvez ele me ajude nas minhas proximas batalhas...\n");
            craft.capacete = 1;
        }
        else
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
        }

        printf(COLOR_WHITE "\n                            Voce esta no Topo Montanha.\n");
        printf("\n                            O que voce vai fazer agora?\n");
        printf("\n                             Procurar Itens na Montanha(1)\n                             Ir para Nascente da Cachoeira(2)\n                             Descer a Montanha(3)\n                             Inventario(4)\n\n                                        " COLOR_RED);

        fflush(stdin);
        fgets(&escolha, 2, stdin);

        /* VERIFICA A ESCOLHA */
        switch (escolha)
        {
        case ('1'):
            procura_item(local, profissao, dificuldade, &item.pedras, &item.fibra_natural, &item.concha, &item.graveto, &estatus.fome, &estatus.sede, &estatus.saude);
            custo(local, &estatus.fome, &estatus.sede);
            break;

        case ('2'):
            passagem.montanha = 1;
            custo(local, &estatus.fome, &estatus.sede);
            transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            goto LOCAL_NASCENTE_CACHOEIRA;
            break;

        case ('3'):
            passagem.cachoeira = 1;
            Subida_Descida_Montanha(local, &estatus, &craft, &item, profissao);
            goto LOCAL_ENCOSTA;
            break;

        case ('4'):
            inventario(&item, &craft, profissao, bonus_arma(profissao), local, &estatus, 0);
            break;

        default:
            passagem.montanha == 0 ? printf("\n") : printf("\n\n\n\n\n");
            printf(COLOR_BLUE " Aqui e fresquinho...\n\n");
            estatus.sede -= 2;
            estatus.fome -= 2;
            break;
        }
        passagem.montanha = 1;
        printf(COLOR_WHITE);
        system("pause");
        system("cls");
    } while (1);

    /************************************************************** NASCENTE DA CACHOEIRA ***************************************************/
LOCAL_NASCENTE_CACHOEIRA:
    SetConsoleTitle(" Naufrago - Nascente da Cachoeira ");
    system("cls");
    fflush(stdin);
    local = Nascente_cachoeira;

    do
    {
        if (passagem.nascente_cachoeira == 0)
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
            printf(COLOR_BLUE "\n Aqui seria um otimo lugar para meditar\n");
            printf(" E bem calmo, so escuto o som do vento e da agua.\n");
            printf(" So tenho que tomar cuidado pra nao cair daqui...\n");
        }
        else
        {
            status(&estatus.saude, &estatus.fome, &estatus.sede);
        }

        printf(COLOR_WHITE "\n                        Voce esta na Nascente da Cachoeira.\n");
        printf("\n                            O que voce vai fazer agora?\n");
        printf("\n                             Procurar Itens na Nascente(1)\n                             Pescar(2)\n                             Ir para Topo da Montanha(3)\n                             Inventario(4)\n\n                                        " COLOR_RED);

        fflush(stdin);
        fgets(&escolha, 2, stdin);

        /* VERIFICA A ESCOLHA */
        switch (escolha)
        {
        case ('1'):
            custo(local, &estatus.fome, &estatus.sede);
            if (procura_item(local, profissao, dificuldade, &item.pedras, &item.fibra_natural, &item.concha, &item.graveto, &estatus.fome, &estatus.sede, &estatus.saude))
            {
                passagem.nascente_cachoeira = 1;
                passagem.cachoeira = 1;
                goto LOCAL_CACHOEIRA;
            }
            break;

        case ('2'):
            pesca(local, &item, &craft, &estatus, profissao);
            custo(local, &estatus.fome, &estatus.sede);
            break;

        case ('3'):
            passagem.nascente_cachoeira = 1;
            custo(local, &estatus.fome, &estatus.sede);
            transicao(local, escolha, &item, &craft, profissao, bonus_arma(profissao), &estatus);
            goto LOCAL_MONTANHA;
            break;

        case ('4'):
            inventario(&item, &craft, profissao, bonus_arma(profissao), local, &estatus, 0);
            break;

        default:
            passagem.nascente_cachoeira == 0 ? printf("\n") : printf("\n\n\n");
            printf(COLOR_BLUE " Eu realmente precisava desse tempinho parado.\n\n");
            /* CUSTO POR FICAR PARADO E BRINCAR COM O CARA QUE FEZ O JOGO */
            estatus.sede -= 2;
            estatus.fome -= 2;
            estatus.saude += 5;
            break;
        }
        passagem.nascente_cachoeira = 1;
        printf(COLOR_WHITE);
        system("pause");
        system("cls");
    } while (1);
}

/* MENUS */
void status(int *s, int *f, int *sd)
{
    /* LIMITA OS STATUS NO MAXIMO 100 E MIN 0, E MANDA PARA MORTE CASO MENOR OU IGUAL A 0*/
    if (*s <= 0 || *f <= 0 || *sd <= 0)
    {
        Morreu_bobao();
    }
    if (*s > 100)
        *s = 100;
    if (*f > 100)
        *f = 100;
    if (*sd > 100)
        *sd = 100;
    /* IMPRIME OS STATUS NA TELA */
    printf(COLOR_WHITE " **********************************************************************************\n");
    printf(" *                                                                                *\n");
    printf(" *         Saude:%4d/100         Fome:%4d/100          Sede:%4d/100            *\n", *s, *f, *sd);
    printf(" *                                                                                *\n");
    printf(" **********************************************************************************\n");
}
void menu()
{
    printf("\n\n");
    printf(COLOR_WHITE "                                        ,...                                       \n");
    printf("   `7MN.   `7MF'     ,'                .d'\"\"\"                                       \n");
    printf("     MMN.    M                         dM`                                         \n");
    printf("     M YMb   M   ,6\"Yb.  `7MM  `7MM   mMMmm `7Mb,od8  ,6\"Yb.   .P\"Ybmmm  ,pW\"Wq.   \n");
    printf("     M  `MN. M  8)   MM    MM    MM    MM     MM' \"' 8)   MM  :MI  I8   6W'   `Wb  \n");
    printf("     M   `MM.M   ,pm9MM    MM    MM    MM     MM      ,pm9MM   WmmmP\"   8M     M8  \n");
    printf("     M     YMM  8M   MM    MM    MM    MM     MM     8M   MM  8M        YA.   ,A9  \n");
    printf("   .JML.    YM  `Moo9^Yo.  `Mbod\"YML..JMML. .JMML.   `Moo9^Yo. YMMMMMb   `Ybmd9'   \n");
    printf("                                                               6'    dP           \n");
    printf("                                                                Ybmmmd'             \n");
    printf("\n\n\n");
    printf("                            **************************\n");
    printf("                            *  Criado Em: 03/09/2019 *\n");
    printf("                            * Autor: Gabriel Barberiz*\n");
    printf("                            *     Versão 19.12.09    *\n");
    printf("                            **************************\n");
    printf("\n\n\n");
    system("pause");
    system("cls");
}
void regras()
{
    SetConsoleTitle(" Naufrago - Regras ");
    char teste;
    regra_letreiro();
    printf("\n                  * Tome cuidado com suas escolhas.\n");
    printf("                  * Nao mude o tamanho do prompt.\n");
    printf("                  * Apenas coloque numeros como resposta.\n");
    printf("                  * Coloque qualquer numero entre 0 e 9.\n");
    printf("                  * Use apenas um numero de cada vez.\n");
    printf("                  * Se o numero for maior que 9 sera lido so o primeiro digito!\n\n\n\n");
    printf("                                    Voce entendeu?\n                                          " COLOR_RED);
    fgets(&teste, 2, stdin);
    printf(COLOR_WHITE);
    if (teste > '9' || teste < '0')
    {
        printf("                         Parece que voce nao entendeu nada.\n");
        printf(COLOR_RED "                             Regra 3 - APENAS NUMEROS!!\n" COLOR_WHITE);
    }
    else
    {
        printf("                                Bom, aparentemente sim... \n\n");
    }
    system("pause");
    system("cls");

    /* SEGUNDA PARTE DAS REGRAS, EXPLICACAO DO JOGO*/
    regra_letreiro();

    printf("\n               * Esse e um jogo extremamente trabalhado com probabilidades.\n");
    printf("               * Qualquer acao que fizer tera uma porcentagem de sucesso.\n");
    printf("               * As porcentagens serao mais faceis ou dificeis dependendo da:\n");
    printf("                  - Dificuldade escolhida.\n");
    printf("                  - Profissao escolhida.\n");
    printf("\n               * Obs: Acoes mais dificeis precisam de ferramentas para serem                         feitas mais facilmente.\n");
    printf("               * Isso nao impede que voce tente a sorte de conseguir faze-las                        sem ferramentas ou equipamentos.\n\n\n");
    system("pause");
    system("cls");
    /* TERCEIRA PARTE DAS REGRAS, EXPLICANDO AS ACOES */
    regra_letreiro();

    printf("\n               * Cada acao no jogo tem um custo, sendo eles: \n");
    printf("                  - Fome. \n");
    printf("                  - Saude. \n");
    printf("                  - Sede. \n\n");
    printf("               * Tome cuidado!! Se algum deles chegar a zero voce perde.\n\n\n\n\n\n\n");
    system("pause");
    system("cls");
}
void regra_letreiro()
{
    printf("\n               `7MM\"\"\"Mq.                                               \n");
    printf("                MM   `MM.                                              \n");
    printf("                MM   ,M9   .gP\"Ya   .P\"Ybmmm `7Mb,od8  ,6\"Yb.  ,pP\"Ybd \n");
    printf("                MMmmdM9   ,M'   Yb :MI  I8     MM' \"' 8)   MM  8I   `\" \n");
    printf("                MM  YM.   8M\"\"\"\"\"\"  WmmmP\"     MM      ,pm9MM  `YMMMa. \n");
    printf("                MM   `Mb. YM.    , 8M          MM     8M   MM  L.   I8 \n");
    printf("              .JMML. .JMM. `Mbmmd'  YMMMMMb  .JMML.   `Moo9^Yo.M9mmmP' \n");
    printf("                                   6'    dP                           \n");
    printf("                                    Ybmmmd'     \n");
}
void inventario(Itens *simples, Itens2 *craft, int profissao, int bonus_arma, int local, Sttatus *status, int batalha)
{
    inventario_letreiro();
    if (simples->pedras == 0 && craft->recipiente_agua_cheio == 0 && simples->fibra_natural == 0 && simples->concha == 0 && simples->graveto == 0 && simples->madeira == 0 && simples->carne_crua == 0 && craft->lanca == 0 && craft->machado == 0 && craft->faca == 0 && craft->recipiente_agua == 0 && craft->barco_1 == 0 && craft->escudo_barco == 0 && craft->barco_2 == 0 && craft->fogueira == 0 && craft->carne_assada == 0)
    {
        printf(COLOR_RED "\n\n\n\n\n\n\n                        Voce nao possui itens, va procula-los.\n\n\n\n\n\n\n");
        if (batalha == 1)
            system("pause");
    }
    else
    {
        char escolha;
        printf("\n                              Esses sao seus itens:\n");
        printf("           Basicos:                                           Craftados:\n\n");
        if (simples->pedras == 0 && craft->faca == 0)
            printf("             ...                                                 ...\n");
        else if (simples->pedras != 0 && craft->faca == 0)
            printf("         %3d Pedra(s)                                            ...\n", simples->pedras);
        else if (simples->pedras == 0 && craft->faca != 0)
            printf("             ...                                            %3d Faca(s)\n", craft->faca);
        else if (simples->pedras != 0 && craft->faca != 0)
            printf("         %3d Pedra(s)                                       %3d Faca(s)\n", simples->pedras, craft->faca);
        if (simples->fibra_natural == 0 && craft->machado == 0)
            printf("             ...                                                 ...\n");
        else if (simples->fibra_natural != 0 && craft->machado == 0)
            printf("         %3d Fibra(s)                                            ...\n", simples->fibra_natural);
        else if (simples->fibra_natural == 0 && craft->machado != 0)
            printf("             ...                                            %3d Machado(s)\n", craft->machado);
        else if (simples->fibra_natural != 0 && craft->machado != 0)
            printf("         %3d Fibra(s)                                       %3d Machado(s)\n", simples->fibra_natural, craft->machado);
        if (simples->concha == 0 && craft->lanca == 0)
            printf("             ...                                                 ...\n");
        else if (simples->concha != 0 && craft->lanca == 0)
            printf("         %3d Concha(s)                                           ...\n", simples->concha);
        else if (simples->concha == 0 && craft->lanca != 0)
            printf("             ...                                            %3d Lanca(s)\n", craft->lanca);
        else if (simples->concha != 0 && craft->lanca != 0)
            printf("         %3d Concha(s)                                      %3d Lanca(s)\n", simples->concha, craft->lanca);
        if (simples->graveto == 0 && craft->fogueira == 0)
            printf("             ...                                                 ...\n");
        else if (simples->graveto != 0 && craft->fogueira == 0)
            printf("         %3d Graveto(s)                                          ...\n", simples->graveto);
        else if (simples->graveto == 0 && craft->fogueira != 0)
            printf("             ...                                            %3d Fogueira(s)\n", craft->fogueira);
        else if (simples->graveto != 0 && craft->fogueira != 0)
            printf("         %3d Graveto(s)                                     %3d Fogueira(s)\n", simples->graveto, craft->fogueira);
        if (simples->carne_crua == 0 && craft->carne_assada == 0)
            printf("             ...                                                 ...\n");
        else if (simples->carne_crua != 0 && craft->carne_assada == 0)
            printf("         %3d Carne(s) Crua(s)                                    ...\n", simples->carne_crua);
        else if (simples->carne_crua == 0 && craft->carne_assada != 0)
            printf("             ...                                            %3d Carne(s) Assada(s)\n", craft->carne_assada);
        else if (simples->carne_crua != 0 && craft->carne_assada != 0)
            printf("         %3d Carne(s) Crua(s)                               %3d Carne(s) Assada(s)\n", simples->carne_crua, craft->carne_assada);
        if (simples->madeira == 0 && craft->recipiente_agua == 0)
            printf("             ...                                                 ...\n");
        else if (simples->madeira != 0 && craft->recipiente_agua == 0)
            printf("         %3d Madeira(s)                                          ...\n", simples->madeira);
        else if (simples->madeira == 0 && craft->recipiente_agua != 0)
            printf("             ...                                            %3d Recipiente Vazio\n", craft->recipiente_agua);
        else if (simples->madeira != 0 && craft->recipiente_agua != 0)
            printf("         %3d Madeira(s)                                     %3d Recipiente Vazio\n", simples->madeira, craft->recipiente_agua);
        if (craft->barco_1 == 0)
            printf("                                                                 ...\n");
        else
            printf("                                                            %3d Barco Simples\n", craft->barco_1);
        if (craft->escudo_barco == 0)
            printf("                                                                 ...\n");
        else
            printf("                                                            %3d Escudo de Conchas\n", craft->escudo_barco);
        if (craft->barco_2 == 0)
            printf("                                                                 ...\n");
        else
            printf("                                                            %3d Barco Reforcado\n", craft->barco_2);
        if (craft->recipiente_agua_cheio == 0)
            printf("                                                                 ...\n\n");
        else
            printf("                                                            %3d Recipiente Cheio\n\n", craft->recipiente_agua_cheio);
        system("pause");
        if (batalha == 0)
        {
            inventario_letreiro();
            printf("\n                             Voce deseja craftar algo?\n\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            printf(COLOR_WHITE);
            if (escolha == '1')
                fcraft(simples, craft, bonus_arma);
            else
            {
                printf(COLOR_WHITE "\n\n\n\n\n\n\n");
                if (craft->recipiente_agua > 0 && (local == Lago || local == Cachoeira || local == Nascente_cachoeira))
                {
                    inventario_letreiro();
                    printf("\n                       Voce deseja encher Recipientes Vazios?\n\n");
                    printf("                                      Sim (1)\n");
                    printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
                    fflush(stdin);
                    fgets(&escolha, 2, stdin);
                    printf(COLOR_WHITE);
                    if (escolha == '1')
                    {
                        printf(COLOR_BLUE "\n Foi bem simples encher tudo isso.\n Agora, todos estao cheios...\n\n\n\n\n" COLOR_WHITE);
                        if (craft->recipiente_agua_cheio > 0 || craft->fogueira > 0 || (craft->machado > 0 && (local == Floresta || local == Praia)) || (craft->carne_assada > 0 || simples->carne_crua > 0))
                            system("pause");
                        craft->recipiente_agua_cheio += craft->recipiente_agua;
                        craft->recipiente_agua = 0;
                    }
                    else
                        printf(COLOR_WHITE "\n\n\n\n\n\n\n");
                }
                if (craft->recipiente_agua_cheio > 0)
                {
                    inventario_letreiro();
                    printf("\n                              Voce deseja beber Agua?\n\n");
                    printf("                                      Sim (1)\n");
                    printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
                    fflush(stdin);
                    fgets(&escolha, 2, stdin);
                    printf(COLOR_WHITE);
                    if (escolha == '1')
                    {
                        printf(COLOR_BLUE "\n Talvez essa agua tenha salvo minha vida.\n Pena que perdi o recipiente...\n\n\n\n\n" COLOR_WHITE);
                        if (craft->fogueira > 0 || (craft->machado > 0 && (local == Floresta || local == Praia)) || (craft->carne_assada > 0 || simples->carne_crua > 0))
                            system("pause");
                        craft->recipiente_agua_cheio -= 1;
                        status->sede += 50;
                    }
                    else
                        printf(COLOR_WHITE "\n\n\n\n\n\n\n");
                }
                if (craft->fogueira > 0)
                {
                    inventario_letreiro();
                    printf("\n                             Voce deseja usar fogueira?\n\n");
                    printf("                                      Sim (1)\n");
                    printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
                    fflush(stdin);
                    fgets(&escolha, 2, stdin);
                    printf(COLOR_WHITE);
                    if (escolha == '1')
                    {
                        custo(local, &status->fome, &status->sede);
                        if (simples->carne_crua > 0)
                            printf(COLOR_BLUE "\n Consegui assar todas as minhas carnes.\n Minha fogueira apagou logo depois disso...\n\n\n\n\n" COLOR_WHITE);
                        else
                            printf(COLOR_BLUE "\n Nao sei porque acendi a fogueira ja que nao tenho Carne Crua.\n Minha fogueira apagou logo depois disso...\n\n\n\n\n" COLOR_WHITE);
                        if ((craft->machado > 0 && (local == Floresta || local == Praia)) || (craft->carne_assada > 0 || simples->carne_crua > 0))
                            system("pause");
                        craft->carne_assada += simples->carne_crua;
                        craft->fogueira -= 1;
                        simples->carne_crua = 0;
                    }
                    else
                        printf(COLOR_WHITE "\n\n\n\n\n\n\n");
                }
                if (craft->carne_assada > 0 || simples->carne_crua > 0)
                {
                    inventario_letreiro();
                    printf("\n                            Voce deseja comer uma Carne?\n\n");
                    printf("                                      Sim (1)\n");
                    printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
                    fflush(stdin);
                    fgets(&escolha, 2, stdin);
                    printf(COLOR_WHITE);
                    if (escolha == '1')
                    {
                        if (craft->carne_assada > 0)
                        {
                            printf(COLOR_BLUE "\n Muito melhor assada.\n So faltou um salzinho...\n\n\n\n\n" COLOR_WHITE);
                            status->fome += 20;
                            status->saude += 20;
                            craft->carne_assada -= 1;
                        }
                        else if (simples->carne_crua > 0)
                        {
                            printf(COLOR_BLUE "\n Eu poderia assar essa carne.\n Talvez assim, eu fique com menos fome...\n\n\n\n\n" COLOR_WHITE);
                            status->fome += 10;
                            status->saude += 10;
                            simples->carne_crua -= 1;
                        }
                        if (craft->machado > 0 && (local == Floresta || local == Praia))
                            system("pause");
                    }
                    else
                        printf(COLOR_WHITE "\n\n\n\n\n\n\n");
                }
                if (craft->machado > 0 && (local == Floresta || local == Praia))
                {
                    inventario_letreiro();
                    printf("\n                            Voce deseja usar o Machado?\n\n");
                    printf("                                      Sim (1)\n");
                    printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
                    fflush(stdin);
                    fgets(&escolha, 2, stdin);
                    printf(COLOR_WHITE);
                    if (escolha == '1')
                    {
                        system("cls");
                        int aux; /* NUMERO ALEATORIO */
                        int i = 0;
                        printf(COLOR_WHITE "\n\n\n                 Voce sai caminhando a procura de algo de madeira.\n");
                        printf("\n\n\n                                      ");
                        for (i = 0; i < 3; i++)
                        {
                            printf(" .");
                            Sleep(1000);
                        }
                        aux = num_aleatorio();
                        printf("\n\n");
                        if (local == Floresta)
                        {
                            if (aux <= 20) /* ITEM COMUM */
                            {
                                printf("\n                         Voce encontrou uma" COLOR_YELLOW " Arvore Pequena" COLOR_WHITE ".\n\n");
                                printf(COLOR_GREEN "                                    1 Madeira.\n");
                                simples->madeira += 1;
                            }
                            else if (aux <= 80) /* ITEM IMCOMUM */
                            {
                                printf("\n                          Voce encontrou uma" COLOR_YELLOW " Arvore Media" COLOR_WHITE ".\n\n");
                                printf(COLOR_GREEN "                                    3 Madeiras.\n");
                                simples->madeira += 3;
                            }
                            else if (aux <= 100) /* ITEM RARO */
                            {
                                printf("\n                         Voce encontrou uma" COLOR_YELLOW " Arvore Grande" COLOR_WHITE ".\n\n");
                                printf(COLOR_GREEN "                                    5 Madeiras.\n");
                                simples->madeira += 5;
                            }
                            printf(COLOR_WHITE "\n\n\n\n\n\n\n\n\n\n");
                        }
                        else if (local == Praia)
                        {
                            if (aux <= 60) /* ITEM COMUM */
                            {
                                printf("\n                         Voce encontrou um" COLOR_YELLOW " Coqueiro Pequeno" COLOR_WHITE ".\n\n");
                                printf(COLOR_GREEN "                                    1 Madeira.\n");
                                simples->madeira += 1;
                            }
                            else if (aux <= 90) /* ITEM IMCOMUM */
                            {
                                printf("\n                         Voce encontrou uma" COLOR_YELLOW " Coqueiro Medio" COLOR_WHITE ".\n\n");
                                printf(COLOR_GREEN "                                    2 Madeiras.\n");
                                simples->madeira += 3;
                            }
                            else if (aux <= 100) /* ITEM RARO */
                            {
                                printf("\n                         Voce encontrou uma" COLOR_YELLOW " Coqueiro Grande" COLOR_WHITE ".\n\n");
                                printf(COLOR_GREEN "                                    4 Madeiras.\n");
                                printf("                                    1 Coco. (+10 de Fome e Sede)");
                                simples->madeira += 5;
                                status->fome += 10;
                                status->sede += 10;
                            }
                            printf(COLOR_WHITE "\n\n\n\n\n\n\n\n\n\n");
                        }
                        custo(local, &status->fome, &status->sede);
                    }
                    else
                        printf(COLOR_WHITE "\n\n\n\n\n\n\n");
                }
            }
        }
        else if (craft->recipiente_agua_cheio > 0)
        {
            inventario_letreiro();
            printf("\n                              Voce deseja beber Agua?\n\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            printf(COLOR_WHITE);
            if (escolha == '1')
            {
                printf(COLOR_BLUE "\n Talvez essa agua tenha salvo minha vida.\n Pena que perdi o recipiente...\n\n\n\n\n" COLOR_WHITE);
                system("pause");
                craft->recipiente_agua_cheio -= 1;
                status->sede += 50;
            }
            else
            {
                printf(COLOR_WHITE "\n\n\n\n\n\n\n");
                system("pause");
            }
            if (craft->carne_assada > 0 || simples->carne_crua > 0)
            {
                inventario_letreiro();
                printf("\n                            Voce deseja comer uma Carne?\n\n");
                printf("                                      Sim (1)\n");
                printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
                fflush(stdin);
                fgets(&escolha, 2, stdin);
                printf(COLOR_WHITE);
                if (escolha == '1')
                {
                    if (craft->carne_assada > 0)
                    {
                        printf(COLOR_BLUE "\n Muito melhor assada.\n So faltou um salzinho...\n\n\n\n\n" COLOR_WHITE);
                        status->fome += 20;
                        status->saude += 20;
                        craft->carne_assada -= 1;
                        system("pause");
                    }
                    else if (simples->carne_crua > 0)
                    {
                        printf(COLOR_BLUE "\n Eu poderia assar essa carne.\n Talvez assim, eu fique com menos fome...\n\n\n\n\n" COLOR_WHITE);
                        status->fome += 10;
                        status->saude += 10;
                        simples->carne_crua -= 1;
                        system("pause");
                    }
                }
                else
                    system("pause");
            }
        }
    }
}
void inventario_letreiro()
{
    system("cls");
    printf(COLOR_WHITE " **********************************************************************************\n");
    printf(" *                  `7MMF'  mm                                                    *\n");
    printf(" *                    MM    MM                                                    *\n");
    printf(" *                    MM  mmMMmm   .gP\"Ya  `7MMpMMMb.   ,pP\"Ybd                   *\n");
    printf(" *                    MM    MM    ,M'   Yb   MM    MM   8I   `\"                   *\n");
    printf(" *                    MM    MM    8M\"\"\"\"\"\"   MM    MM   `YMMMa.                   *\n");
    printf(" *                    MM    MM    YM.    ,   MM    MM   L.   I8                   *\n");
    printf(" *                  .JMML.  `Mbmo  `Mbmmd' .JMML  JMML. M9mmmP'                   *\n");
    printf(" **********************************************************************************\n");
}
void Morreu_bobao()
{
    SetConsoleTitle(" Naufrago - Tente de novo! ");
    char aux;
    do
    {
        system("cls");
        printf(COLOR_WHITE "\n\n\n\n\n\n");
        printf(" **********************************************************************************\n");
        printf(" *                                   VOCE MORREU                                  *\n");
        printf(" **********************************************************************************\n\n\n");
        printf("                          Voce gostaria de tentar de novo?\n\n");
        printf("                         Sim, nao vou me dar por vencido(1)\n");
        printf("                     Desisto, sou muito fraco para esse jogo(2)\n\n                                          " COLOR_RED);
        fflush(stdin);
        gets(&aux);

        if (aux == '1')
        {
            printf(COLOR_WHITE "\n\n\n Muito bem, boa sorte na proxima tentativa.\n\n\n");
            system("pause");
            iniciar_jogo();
        }
        else if (aux == '2')
        {
            printf(COLOR_WHITE);
            exit(0);
        }
    } while (1);
}
void creditos()
{
    SetConsoleTitle(" Naufrago - Agradecimentos ");
    system("cls");
    system("MODE con cols=84 lines=30");
    printf(COLOR_WHITE "\n                                           ,,    ,,\n");
    printf("        .g8\"\"\"bgd                ,'      `7MM    db    mm\n");
    printf("      .dP'     `M                          MM          MM\n");
    printf("      dM'       ` `7Mb,od8  .gP\"Ya    ,M\"\"bMM  `7MM  mmMMmm   ,pW\"Wq.  ,pP\"Ybd\n");
    printf("      MM            MM' \"' ,M'   Yb ,AP    MM    MM    MM    6W'   `Wb 8I   `\"\n");
    printf("      MM.           MM     8M\"\"\"\"\"\" 8MI    MM    MM    MM    8M     M8 `YMMMa.\n");
    printf("      `Mb.     ,'   MM     YM.    , `Mb    MM    MM    MM    YA.   ,A9 L.   I8\n");
    printf("        `\"bmmmd'  .JMML.    `Mbmmd'  `Wbmd\"MML..JMML.  `Mbmo  `Ybmd9'  M9mmmP'\n\n");
    printf("                     Demorou muito tempo para \"terminar\" o jogo.\n");
    printf("                         Espero que tenham gostado de jogar.\n");
    printf("         Realmente deu um certo trabalho fazer isso utilizando linguagem C.\n");
    printf("       Mesmo codando sozinho quero agradecer algumas pessoas que me apoiaram.\n\n");
    printf(COLOR_YELLOW "                                      OS TILTADOS\n\n" COLOR_WHITE);
    printf("                                  Arthur Canivas\n");
    printf("                                  Gordinx\n");
    printf("                                  Portelinha rei Delas\n");
    printf("                                  Tiaguetes\n");
    printf("                                  Andrezada\n");
    printf("                                  Bolota\n\n");
    printf("                            Qualquer bug relatar no Discord\n");
    printf("                                  discord.gg/E5ZxmP7\n\n\n");
    system("pause");
    system("MODE con cols=84 lines=25");
}

/* BONUS: MUDA AS PROBABILIDADES DE SUCESSO DAS ACOES */
int bonus_busca(char profissao)
{
    if (profissao == arqueologo || profissao == fotografo) /* ganha +10% em buscas*/
    {
        return 10;
    }
    if (profissao == tradutor) /* perde 10% em busca por conta do oculos */
    {
        return -10;
    }
    /* se n tiver emprego seta em 0*/
    return 0;
}
int bonus_arma(char profissao)
{
    if (profissao == arqueologo)
    {
        return 10;
    }
    if (profissao == fotografo || profissao == tradutor)
    {
        return -10;
    }
    /* se n tiver emprego seta em 0*/
    return 0;
}
int bonus_d(char dificuldade)
{
    /* adiciona 10% nas chances de sucesso*/
    if (dificuldade == cleite_com_pera) /*facil*/
    {
        return 10;
    }
    if (dificuldade == ccafe) /*dificil*/
    {
        /* subtrai 10% */
        return -10;
    }
    /* se ele colocar qualquer coisa seta em medio */
    return 0;
}

/* NUMERO ALEATORIO DE 1 A 100 */
int num_aleatorio()
{
    Sleep(20);
    return rand() % 100 + 1;
}
/* VERIFICA O SUCESSO A ACAO*/
int procura_item(int local_1, char profissao_1, char dificuldade_1, int *pedra, int *fibra_natural, int *concha, int *graveto, int *fome, int *sede, int *saude)
{
    int sucesso = 70 + bonus_busca(profissao_1) + bonus_d(dificuldade_1); /* PORCENTAGEM DE SUCESSO */
    int aux;                                                              /* NUMERO ALEATORIO */
    int i = 0;
    system("cls");
    printf(COLOR_WHITE "\n\n\n                      Voce sai caminhando a procura de itens.\n");
    printf("\n\n\n                                      ");

    /* IMPRIME 3 PONTOS DEMORADOS PARA DAR SENSACAO DE BUSCA */
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1000);
    }
    aux = num_aleatorio();
    printf("\n\n");
    if (sucesso < aux || local_1 == Floresta_2) /* CASO O NUMERO QUE CAIU ESTEJA FORA DA AREA DE SUCESSO (FRACASSO) */
    {
        printf(COLOR_GREEN "\n\n                              Voce nao encontrou nada!");
        local_1 == Floresta_2 ? printf(COLOR_BLUE "\n\n\n                          Esta muito escuro pra achar algo\n\n\n\n" COLOR_WHITE) : printf(COLOR_WHITE "\n\n\n\n\n\n\n");
    }
    else
    {
        aux = num_aleatorio(); /* NOVO NUMERO ALEATORIO PARA ITENS COLETADDOS */
        printf(COLOR_GREEN "\n                            Voce encontrou esses itens:\n\n");
        switch (local_1)
        {
            /* ITENS POSSIVEIS DE SER ACHADOS E SUAS PROBABILIDADES */

        case (Praia):
            /* ITEM COMUM */
            *concha += 1;
            printf("                               1 Concha.\n");

            if ((sucesso / 2) >= aux) /* ITEM IMCOMUM */
            {
                *fibra_natural += 2;
                printf("                               2 Fibras naturais.");
            }
            printf("\n");
            if ((sucesso / 3) >= aux) /* ITEM RARO */
            {
                printf("                               1 Coco. (+10 de Fome e Sede)");
                *fome += 10;
                *sede += 10;
            }
            printf("\n\n\n\n");
            break;

        case (Floresta):
            /* ITEM COMUM */
            *graveto += 1;
            printf("                               1 Graveto.\n");

            if ((sucesso / 2) >= aux) /* ITEM IMCOMUM */
            {
                *fibra_natural += 2;
                printf("                               2 Fibras naturais.");
            }
            printf("\n");
            if ((sucesso / 3) >= aux) /* ITEM RARO */
            {
                printf("                               10 Frutinhas. (+10 de Fome)");
                *fome += 10;
            }
            printf("\n\n\n\n");
            break;

        case (Lago):
            /* ITEM COMUM */
            *concha += 1;
            printf("                               1 Concha.\n");

            if ((sucesso / 2) >= aux) /* ITEM IMCOMUM */
            {
                *graveto += 1;
                printf("                               1 Graveto.");
            }
            printf("\n");
            if ((sucesso / 3) >= aux) /* ITEM RARO */
            {
                printf("                               1 Caramujo. (+10 de Fome -5 de Saude)");
                *fome += 10;
                *saude -= 5;
            }
            printf("\n\n\n\n");
            break;

        case (Montanha):
            /* ITEM COMUM */
            *pedra += 1;
            printf("                               1 Pedra.\n");

            if ((sucesso / 2) >= aux) /* ITEM IMCOMUM */
            {
                *pedra += 2;
                printf("                               2 Pedras.");
            }
            printf("\n");
            if ((sucesso / 3) >= aux) /* ITEM RARO */
            {
                printf("                               1 Inseto. (+10 de Fome)");
                *fome += 10;
            }
            printf("\n\n\n\n");

            break;

        case (Nascente_cachoeira):
            /* ITEM COMUM */
            *concha += 1;
            printf("                               1 concha.\n");

            if ((sucesso / 2) >= aux) /* ITEM IMCOMUM */
            {
                *graveto += 1;
                printf("                               1 graveto.");
            }
            printf("\n");
            if ((sucesso / 3) >= aux) /* ITEM RARO */
            {
                printf("                               1 Musgo");
                aux = num_aleatorio();
                if (sucesso <= aux)
                {
                    printf(" Venenoso. (+5 fome,-10 Saude)");
                    *fome += 5;
                    *saude -= 10;
                }
                else
                {
                    printf(" Comum. (+10 fome)");
                    *fome += 10;
                }
            }
            printf("\n");
            aux = num_aleatorio();
            if (sucesso <= aux)
            {
                printf(COLOR_WHITE "\n\n Voce acaba escorregando em uma das pedras enquanto procurava itens.\n");
                printf(COLOR_BLUE " A correnteza esta muito forte, nao consigo sair daqui.\n\n\n\n\n" COLOR_WHITE);
                system("pause");
                queda_cachoeira(saude);
                return 1;
            }
            else
                printf("\n\n\n\n\n\n\n\n");
            break;

        default:
            break;
        }
    }
    printf("\n\n\n\n\n");
    return 0;
}
/* CUSTO POR ACAO FEITA (PROCURA OU CRAFT) */
void custo(int local, int *f, int *sd)
{
    switch (local)
    {

    case (Praia):
        *sd -= 4;
        *f -= 2;
        break;
    case (Mar):
        *sd -= 4;
        *f -= 2;
        break;

    case (Montanha):
        *sd -= 2;
        *f -= 4;
        break;

    default:
        *sd -= 2;
        *f -= 2;
        break;
    }
}
int transicao(int local, char escolha, Itens *simples, Itens2 *craft, char profissao, int bonus_arma, Sttatus *estatus)
{
    int aux, i;
    system("cls");
    aux = num_aleatorio();
    printf(COLOR_WHITE "\n\n\n                  Voce esta caminhando em direcao ao seu destino.\n");
    printf("\n\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1000);
    }
    switch (local)
    {
    case (Praia):
    {
        switch (escolha)
        {
        case ('2'): /* Floresta */
            if (aux <= 40)
            {
                printf("\n\n\n                       Voce chegou a Floresta sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
                system("pause");
                return 1;
            }
            else if (aux <= 60)
            {
                printf("\n\n\n Apos um tempo caminhando, voce percebe que esta perdido.\n Voce acaba chegando na Praia de novo.\n\n\n\n\n\n\n\n\n\n\n\n");
                system("pause");
                return 0;
            }
            else if (aux <= 80)
            {
                printf("\n\n\n Voce estava admirando a paisagem natural a sua volta, quando acaba tropecando em    uma pedra.");
                printf("\n Voce se machucou de leve, mas veja pelo lado bom," COLOR_GREEN " ganhou uma pedra nova" COLOR_WHITE ".\n\n\n\n\n\n\n\n\n\n\n");
                system("pause");
                simples->pedras += 1;
                estatus->saude -= 1;
                return 1;
            }
            else if (aux <= 100)
            {
                if (simples->pedras >= 1)
                {
                    printf("\n\n\n Um macaco cai em cima de voce e tenta pegar uma de suas pedras.\n");
                    aux = num_aleatorio();
                    if (aux <= 70)
                    {
                        printf("\n\n\n\n\n\n\n\n\n\n\n\n");
                        system("pause");
                        batalha(simples, craft, profissao, bonus_arma, local, estatus, 2);
                    }
                    else
                    {
                        printf(" Dando uma cambalhota para frente, voce consegue fugir do macaco.\n\n\n\n\n\n\n\n\n\n\n\n");
                    }
                }
                else
                {
                    printf("\n\n\n Voce escuta um barulho muito alto de grito." COLOR_BLUE "\n Aparentemente sao macacos..." COLOR_WHITE "\n Andando um pouco mais depressa, voce chega ate seu destino.\n\n\n\n\n\n\n\n\n\n\n");
                }
                system("pause");
                return 1;
            }
            break;

        case ('3'):
            if (aux <= 60)
            {
                printf("\n\n\n                         Voce chegou ao Mar sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
                system("pause");
            }
            else if (aux <= 100)
            {
                aux = num_aleatorio();
                printf("\n\n\n Apos um tempo caminhando, voce olha para o chao e percebe que ali tem uma concha.");
                if (aux <= 50)
                {
                    printf("\n Voce pega a conha, em baixo dela tinha um pequeno carangueijo.\n");
                    simples->concha += 1;
                    aux = num_aleatorio();
                    if (aux <= 60)
                        printf(" O carangueijo se sente ameacado e sai correndo de medo.\n\n\n\n\n\n\n\n\n\n\n");
                    else
                    {
                        printf(" Aquela era a casa de um carangueijo.\n Ele ficou muito bravo com sua atitude e avanca pra cima de voce.\n\n\n\n\n\n\n\n\n\n");
                        system("pause");
                        batalha(simples, craft, profissao, bonus_arma, local, estatus, 1);
                    }
                }
                else if (aux <= 80)
                {
                    simples->concha += 1;
                    printf("\n Voce pega e nada acontece.\n Claro, como se algo pudesse acontecer so de pegar uma concha no chao.\n\n\n\n\n\n\n\n\n\n\n");
                }
                else if (aux <= 100)
                {
                    printf("\n Voce se abaixa para pegar ela.\n Quando esta prestes a se levantar uma onda grande vem e te pega desprevinido.");
                    printf("\n A onda veio rapidamente e voce acaba se engasgando com a agua, a concha cai da sua  mao e voce a perde.\n\n\n\n\n\n\n\n\n");
                    estatus->saude -= 1;
                }
                system("pause");
                return 1;
            }
            break;
        }
    }
    break;

    case (Floresta):
    {
        switch (escolha)
        {
        case ('2'): /* lago */
            if (aux <= 60)
            {
                printf(COLOR_WHITE "\n\n\n                         Voce chegou ao Lago sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
            }
            else if (aux <= 100)
            {
                aux = num_aleatorio();
                printf(COLOR_WHITE "\n\n\n Apos um tempo caminhando, voce percebe que o solo esta ficando mais humido.\n");
                printf(COLOR_BLUE "\n Esta ficando dificil andar por aqui, fora que pode ter algum bixo nessas folhas.\n" COLOR_WHITE);
                if (aux <= 50)
                {
                    aux = num_aleatorio();
                    if (aux <= 70)
                    {
                        printf("\n Voce continua andando e chega ao Lago sem maiores problemas.\n\n\n\n\n\n\n\n\n");
                        system("pause");
                        return 1;
                    }
                    else
                    {
                        printf("\n Voce continua andando por um tempo, e observando a dificuldade do caminho, voce\n resolve voltar.\n\n\n\n\n\n\n\n");
                        system("pause");
                        return 0;
                    }
                }
                if (aux <= 60)
                {
                    printf("\n Apos um tempo caminhando, voce percebe que esta perdido.\n Voce acaba adentrando ainda mais na Floresta.\n\n\n\n\n\n\n\n");
                    system("pause");
                    return 2;
                }
                else if (aux <= 70)
                {
                    estatus->saude -= 2;
                    printf("\n Alguma coisa mordisca seu pe e sai correndo sem ser notado.\n\n\n\n\n\n\n\n\n");
                }
                else if (aux <= 100)
                {
                    printf("\n Voce se abaixa para retirar algumas folhas do seu caminho.\n Quando se depara com um sapo.\n");
                    Sleep(100);
                    aux = num_aleatorio();
                    if (aux <= 60)
                        printf(COLOR_BLUE "\n Ele parece estar feliz...\n\n\n\n\n\n" COLOR_WHITE);
                    else
                    {
                        printf("\n Ele nao parece estar feliz em te ver e te chama pra briga.\n\n\n\n\n\n");
                        system("pause");
                        batalha(simples, craft, profissao, bonus_arma, local, estatus, 4);
                    }
                }
            }
            system("pause");
            return 1;
            break;

        case ('3'): /* praia */
        {
            if (aux <= 50)
            {
                printf("\n\n\n                         Voce chegou a Praia sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
                system("pause");
                return 1;
            }
            else if (aux <= 70)
            {
                printf("\n\n\n Apos um tempo caminhando, voce percebe que esta perdido.\n Voce acaba chegando na Floresta de novo.\n\n\n\n\n\n\n\n\n\n\n\n");
                system("pause");
                return 0;
            }
            else if (aux <= 90)
            {
                printf("\n\n\n Voce estava admirando a paisagem natural a sua volta, quando acaba tropecando em    uma pedra.");
                printf("\n Voce se machucou de leve, mas veja pelo lado bom," COLOR_GREEN " ganhou uma pedra nova" COLOR_WHITE ".\n\n\n\n\n\n\n\n\n\n\n");
                system("pause");
                simples->pedras += 1;
                estatus->saude -= 1;
                return 1;
            }
            else if (aux <= 100)
            {
                if (simples->pedras >= 1)
                {
                    printf("\n\n\n Um macaco cai em cima de voce e tenta pegar uma de suas pedras.\n");
                    aux = num_aleatorio();
                    if (aux <= 70)
                    {
                        printf("\n\n\n\n\n\n\n\n\n\n\n\n");
                        system("pause");
                        batalha(simples, craft, profissao, bonus_arma, local, estatus, 2);
                    }
                    else
                        printf(" Dando uma cambalhota para frente, voce consegue fugir do macaco.\n\n\n\n\n\n\n\n\n\n\n\n");
                }
                else
                    printf("\n\n\n Voce escuta um barulho muito alto de grito." COLOR_BLUE "\n Aparentemente sao macacos..." COLOR_WHITE "\n Andando um pouco mais depressa, voce chega ate seu destino.\n\n\n\n\n\n\n\n\n\n\n");
            }
        }
        break;
        }
    }
    break;

    case (Mar):
    {
        printf(COLOR_WHITE "\n\n\n                        Voce chegou a Praia sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
        system("pause");
    }
    break;

    case (Lugar_alto):
    {
        printf(COLOR_WHITE "\n\n\n                       Voce chegou a Floresta sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
        system("pause");
    }
    break;

    case (Lago):
    {
        switch (escolha)
        {
        case ('2'): /* floresta_1*/
            if (aux <= 60)
            {
                printf(COLOR_WHITE "\n\n\n                       Voce chegou a Floresta sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
            }
            else if (aux <= 100)
            {
                aux = num_aleatorio();
                printf(COLOR_WHITE "\n\n\n Apos um tempo caminhando, voce percebe que o solo esta ficando com muitas folhas.\n");
                printf(COLOR_BLUE "\n E nojento por aqui, parece que estou pisando em algum bixo.\n" COLOR_WHITE);
                if (aux <= 60)
                {
                    aux = num_aleatorio();
                    if (aux <= 50)
                    {
                        printf("\n Voce continua andando e chega a Floresta sem maiores problemas.\n\n\n\n\n\n\n\n\n");
                        system("pause");
                        return 1;
                    }
                    else
                    {
                        printf("\n Voce continua andando por um tempo, e observando a dificuldade do caminho, voce\n resolve voltar.\n\n\n\n\n\n\n\n");
                        system("pause");
                        return 0;
                    }
                }
                else if (aux <= 90)
                {
                    estatus->saude -= 2;
                    printf("\n Alguma coisa mordisca seu pe e sai correndo sem ser notado.\n\n\n\n\n\n\n\n\n");
                }
                else if (aux <= 100)
                {
                    printf("\n Voce se abaixa para retirar algumas folhas do seu caminho.\n Quando se depara com um sapo.\n");
                    aux = num_aleatorio();
                    if (aux <= 30)
                        printf(COLOR_BLUE "\n Ele parece estar feliz...\n\n\n\n\n\n" COLOR_WHITE);
                    else
                    {
                        printf("\n Ele nao parece estar feliz em te ver e te chama pra briga.\n\n\n\n\n\n");
                        system("pause");
                        batalha(simples, craft, profissao, bonus_arma, local, estatus, 4);
                    }
                }
            }
            system("pause");
            return 1;
            break;

        case ('3'): /* Floresta_2*/
            if (aux <= 60)
            {
                printf(COLOR_WHITE "\n\n\n                   Voce foi mais afundo na Floresta sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
            }
            else if (aux <= 100)
            {
                aux = num_aleatorio();
                printf(COLOR_WHITE "\n\n\n Apos um tempo caminhando, voce percebe que esta ficando cada vez mais escuro.\n");
                printf(COLOR_BLUE "\n Nao consigo enxergar muito bem, devo tomar cuidado pra nao cair.\n" COLOR_WHITE);
                if (aux <= 50)
                {
                    aux = num_aleatorio();
                    if (aux <= 70)
                    {
                        printf("\n Voce continua andando e chega a Floresta Densa sem maiores problemas.\n\n\n\n\n\n\n\n\n");
                        system("pause");
                        return 1;
                    }
                    else
                    {
                        printf("\n Voce continua andando por um tempo, e por conta do medo do escuro, voce\n resolve voltar.\n\n\n\n\n\n\n\n");
                        system("pause");
                        return 0;
                    }
                }
                else if (aux <= 80)
                {
                    estatus->saude -= 2;
                    printf("\n Alguma coisa passa voando sobre sua cabeca, voce leva um susto e acaba caindo.\n Voce se machuca um pouco, mas segue o caminho.\n\n\n\n\n\n\n\n");
                }
                else if (aux <= 100)
                {
                    printf("\n No escuro a sua frente, existem dois pequenos olhos.\n Eles te assustam de inicio, mas voce segue em frente.\n");
                    aux = num_aleatorio();
                    if (aux <= 80)
                    {
                        printf("\n Os olhos misteriosos sao de um morcego, e ele esta incomodado com sua presenca.\n\n\n\n\n\n");
                        system("pause");
                        batalha(simples, craft, profissao, bonus_arma, local, estatus, 3);
                    }
                    else
                        printf("\n Os olhos depois de um tempo ficaram para tras, talvez fosse so um reflexo de luz.\n\n\n\n\n\n");
                }
            }
            system("pause");
            return 1;
            break;
        }
    }
    break;

    case (Floresta_2):
    {
        switch (escolha)
        {
        case ('2'): /* pe da montanha */
            if (aux <= 60)
            {
                printf(COLOR_WHITE "\n\n\n                   Voce chegou ao pe da Montanha sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
            }
            else if (aux <= 100)
            {
                aux = num_aleatorio();
                if (aux <= 30)
                {
                    printf("\n\n\n Voce segue andando, e por falta de iluminacao, voce acaba chegando ao lago.\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    system("pause");
                    return 0;
                }
                else if (aux <= 100)
                    printf("\n\n\n Apos um tempo caminhando, voce percebe que o chao ja esta mais seco.\n E um pouco pedregoso...\n\n\n\n\n\n\n\n\n\n\n\n");
            }
            system("pause");
            return 1;
            break;

        case ('3'): /* lago */
        {
            if (aux <= 60)
            {
                printf(COLOR_WHITE "\n\n\n                         Voce chegou ao Lago sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
            }
            else if (aux <= 100)
            {
                aux = num_aleatorio();
                printf(COLOR_WHITE "\n\n\n Apos um tempo caminhando, voce percebe que esta ficando cada vez mais claro.\n");
                printf(COLOR_BLUE "\n Espero nao ter saido no mesmo lugar que entrei.\n" COLOR_WHITE);
                if (aux <= 50)
                {
                    aux = num_aleatorio();
                    if (aux <= 50)
                    {
                        printf("\n Voce continua andando e chega ao Lago sem maiores problemas.\n\n\n\n\n\n\n\n\n");
                        system("pause");
                        return 1;
                    }
                    else
                    {
                        printf("\n\n\n Voce segue andando, e por falta de iluminacao, voce acaba chegando ao pe da Montanha.\n\n\n\n\n\n\n\n\n\n\n\n\n");
                        system("pause");
                        return 0;
                    }
                }
                else if (aux <= 80)
                {
                    estatus->saude -= 2;
                    printf("\n Alguma coisa passa voando sobre sua cabeca, voce leva um susto e acaba caindo.\n Voce se machuca um pouco, mas segue o caminho.\n\n\n\n\n\n\n\n");
                }
                else if (aux <= 100)
                {
                    printf("\n No escuro a sua frente, existem dois pequenos olhos.\n Eles te assustam de inicio, mas voce segue em frente.\n");
                    aux = num_aleatorio();
                    if (aux <= 70)
                    {
                        printf("\n Os olhos misteriosos sao de um morcego, e ele esta incomodado com sua presenca.\n\n\n\n\n\n");
                        system("pause");
                        batalha(simples, craft, profissao, bonus_arma, local, estatus, 3);
                    }
                    else
                        printf("\n Os olhos depois de um tempo ficaram para tras, talvez fosse so um reflexo de luz.\n\n\n\n\n\n");
                }
            }
        }
            system("pause");
            return 1;
            break;
        }
    }
    break;

    case (Encosta_da_montanha):
    {
        switch (escolha)
        {
        case ('2'): /* cachoeira */
            if (aux <= 40)
                printf(COLOR_WHITE "\n\n\n                    Voce chegou em uma Cachoeira sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
            else if (aux <= 100)
            {
                printf("\n\n\n Voce segue andando por aquele chao cheio de pedras...\n");
                aux = num_aleatorio();
                if (aux <= 60)
                {
                    aux = num_aleatorio();
                    if (aux <= 40)
                    {
                        estatus->saude -= 5;
                        printf("\n\n Apos um tempo caminhando, voce sente uma dor imensa no pe.\n As pedras te machucaram um bocado...\n\n\n\n\n\n\n\n\n");
                    }
                    else
                    {
                        printf("\n\n\n O caminho e longo, voce decide sentar para descancar um pouco...\n Voce se escora em uma pedra e percebe algum movimento nela...\n");
                        aux = num_aleatorio();
                        printf(" Um Besouro estava descancando naquela pedra...\n");
                        if (aux <= 60)
                            printf(" Ele te observa com cuidado, mas nao ve em voce nenhum perigo...\n\n\n\n\n\n\n");
                        else
                        {
                            printf(" Ele acorda em posicao de ataque.\n Talvez voce tenha atrapalhado o sono da beleza dele...\n\n\n\n\n");
                            system("pause");
                            batalha(simples, craft, profissao, bonus_arma, local, estatus, 5);
                        }
                    }
                }
                else
                {
                    printf(" O ar comeca a ficar mais humido, isso te anima um pouco...\n\n\n\n\n\n\n\n\n\n\n\n");
                }
            }
            system("pause");
            return 1;
            break;

        case ('3'): /* parte de traz da montanha (escadaria) */
        {
            if (aux <= 40)
                printf(COLOR_WHITE "\n\n\n                   Voce chegou atras da Montanha sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
            else if (aux <= 100)
            {
                printf("\n\n\n Voce segue andando por aquele chao cheio de pedras...\n");
                aux = num_aleatorio();
                if (aux <= 60)
                {
                    aux = num_aleatorio();
                    if (aux <= 40)
                    {
                        estatus->saude -= 5;
                        printf("\n\n Apos um tempo caminhando, voce sente uma dor imensa no pe.\n As pedras te machucaram um bocado...\n\n\n\n\n\n\n\n\n");
                    }
                    else
                    {
                        printf("\n\n\n O caminho e longo, voce decide sentar para descancar um pouco...\n Voce se escora em uma pedra e percebe algum movimento nela...\n");
                        aux = num_aleatorio();
                        printf(" Um Besouro estava descancando naquela pedra...\n");
                        if (aux <= 40)
                            printf(" Ele te observa com cuidado, mas nao ve em voce nenhum perigo...\n\n\n\n\n\n\n");
                        else
                        {
                            printf(" Ele acorda em posicao de ataque.\n Talvez voce tenha atrapalhado o sono da beleza dele...\n\n\n\n\n");
                            system("pause");
                            batalha(simples, craft, profissao, bonus_arma, local, estatus, 5);
                        }
                    }
                }
                else
                {
                    printf(" Voce olha para cima e ve uma possibilidade de subir...\n\n\n\n\n\n\n\n\n\n\n\n");
                }
            }
        }
            system("pause");
            return 1;
            break;

        case ('4'): /* floresta_2 */
            printf(COLOR_WHITE "\n\n\n                     Voce adentrou na Floresta sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
            system("pause");
            return 1;
            break;
        }
    }
    break;

    case (Cachoeira):
    {
        if (aux <= 40)
            printf(COLOR_WHITE "\n\n\n               Voce chegou na Encosta da Montanha sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
        else if (aux <= 100)
        {
            printf("\n\n\n Voce segue andando por aquele chao cheio de pedras...\n");
            aux = num_aleatorio();
            if (aux <= 40)
            {
                estatus->saude -= 5;
                printf("\n\n Apos um tempo caminhando, voce sente uma dor imensa no pe.\n As pedras te machucaram um bocado...\n\n\n\n\n\n\n\n\n");
            }
            else
            {
                printf("\n\n\n O caminho e longo, voce decide sentar para descancar um pouco...\n Voce se escora em uma pedra e percebe algum movimento nela...\n");
                aux = num_aleatorio();
                printf(" Um Besouro estava descancando naquela pedra...\n");
                if (aux <= 40)
                    printf(" Ele te observa com cuidado, mas nao ve em voce nenhum perigo...\n\n\n\n\n\n\n");
                else
                {
                    printf(" Ele acorda em posicao de ataque.\n Talvez voce tenha atrapalhado o sono da beleza dele...\n\n\n\n\n");
                    system("pause");
                    batalha(simples, craft, profissao, bonus_arma, local, estatus, 5);
                }
            }
        }
        system("pause");
        return 1;
    }
    break;

    case (Montanha):
    {
        if (aux <= 40)
            printf(COLOR_WHITE "\n\n\n             Voce chegou na Nascente da Cachoeira sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
        else if (aux <= 100)
        {
            printf("\n\n\n Voce segue andando por aquele chao cheio de pedras...\n");
            aux = num_aleatorio();
            if (aux <= 50)
                printf("\n\n Chegando perto ao seu destido, voce percebe que as pedras estao escorregadias.\n" COLOR_BLUE " Tenho que tomarar muito cuidado pra nao cair na agua...\n\n\n\n\n\n\n\n\n" COLOR_WHITE);
            else
            {
                printf("\n\n Voce caminha tranquilamente, tomando cuidado com as pedras...\n\n\n");
                aux = num_aleatorio();
                if (aux <= 70)
                    printf(" A passos pequenos voce chega ao seu destino.\n\n\n\n\n\n");
                else if (simples->pedras >= 1)
                {
                    printf(" Uma delas te chama atencao, talvez seja pelo seu brilho?\n Talvez seja porque voce esta ficando louco com o ar rarefeito?\n Nao se sabe ao certo, mas voce a pega e a batiza de" COLOR_GREEN " Alberto I." COLOR_WHITE "\n Voce o guarda no Inventario, mas ele acaba se misturando com as outras pedras...\n\n\n\n");
                    simples->pedras += 1;
                }
                else if (simples->pedras < 1)
                    printf("\n\n\n\n\n\n\n");
            }
        }
        system("pause");
        return 1;
    }
    break;

    case (Nascente_cachoeira):
        if (aux <= 50)
            printf(COLOR_WHITE "\n\n\n                  Voce chegou no Topo da Montanha sem problemas.\n\n\n\n\n\n\n\n\n\n\n\n\n");
        else if (aux <= 100)
        {
            printf("\n\n\n Voce se vira para voltar...\n");
            aux = num_aleatorio();
            if (aux <= 40)
                printf("\n\n E faz um caminho tranquilo, sem maiores problemas.\n\n\n\n\n\n\n\n\n\n");
            else
            {
                aux = num_aleatorio();
                printf(COLOR_BLUE "\n\n Olha aquilo e uma Cobra? Ela e tao bonita...\n\n");
                if (aux <= 45)
                    printf(" Ela te olha, fica com medo do seu capacete, e sai correndo...\n\n\n\n\n\n\n\n\n");
                else
                {
                    printf(" Ela te olha, ve seu capacete, e te considera um oponente digno de uma luta.\n\n\n\n\n\n\n\n");
                    system("pause");
                    batalha(simples, craft, profissao, bonus_arma, local, estatus, 7);
                }
            }
        }
        system("pause");
        break;

    default:
        break;
    }
    return 0;
}
void pesca(int local, Itens *simples, Itens2 *craft, Sttatus *estatus, char profissao)
{
    int aux = num_aleatorio();
    int i = 0;
    int chance_local = 0;
    char escolha = 0;
    if (local == Lago)
        chance_local = 10;
    system("cls");

    if (craft->lanca > 0)
        printf(COLOR_WHITE "\n\n\n                       Voce pega sua lanca e comeca a pesca.");
    else if (craft->faca > 0)
        printf(COLOR_WHITE "\n\n\n                        Voce pega sua faca e comeca a pesca.");
    else
        printf(COLOR_WHITE "\n\n\n                    Voce sai com as maos nuas e comeca a pesca.");
    printf("\n\n\n                                      ");
    /* IMPRIME 3 PONTOS DEMORADOS PARA DAR SENSACAO DE BUSCA */
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1200);
    }
    printf("\n\n\n");
    if (craft->lanca > 0 && local != Cachoeira)
    {
        if (aux <= 50 + chance_local)
        {
            printf("                               Voce pegou um" COLOR_GREEN " peixe" COLOR_WHITE "!\n\n\n");
            printf("                                Deseja comer agora?\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            if (escolha == '1')
            {
                printf(COLOR_WHITE "\n\n Voce coloca aquele peixe cru na boca e comeca a comer.\n");
                printf(" O gosto e horrivel, mas serve para matar a fome.\n\n\n");
                estatus->fome += 10;
                estatus->saude += 10;
            }
            else
            {
                printf(COLOR_WHITE "\n\n Voce guarda o peixe no inventario.\n\n\n\n");
                simples->carne_crua += 1;
            }
        }
        else if (aux <= 90)
            printf("                                Voce nao pegou nada.\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        else if (aux <= 100)
        {
            craft->lanca -= 1;
            printf("                                Voce nao pegou nada.\n\n");
            printf("                                 Sua lanca" COLOR_RED " QUEBROU" COLOR_WHITE ".\n\n\n\n\n\n\n\n\n\n\n\n");
        }
    }
    else if (craft->lanca > 0 && local == Cachoeira)
    {
        if (aux <= 50)
        {
            printf("                               Voce pegou um" COLOR_GREEN " peixe" COLOR_WHITE "!\n\n\n");
            printf("                                Deseja comer agora?\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            if (escolha == '1')
            {
                printf(COLOR_WHITE "\n\n Voce coloca aquele peixe cru na boca e comeca a comer.\n");
                printf(" O gosto e horrivel, mas serve para matar a fome.\n\n\n");
                estatus->fome += 10;
                estatus->saude += 10;
            }
            else
            {
                printf(COLOR_WHITE "\n\n Voce guarda o peixe no inventario.\n\n\n\n");
                simples->carne_crua += 1;
            }
        }
        else if (aux <= 90)
            printf("                                Voce nao pegou nada.\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        else if (aux <= 100)
        {
            printf("                        Voce quase pegou um" COLOR_YELLOW " Peixe Lendario" COLOR_WHITE "!\n\n\n");
            printf("              Ele nao gostou da lanca que voce deixou nas costas dele.\n");
            printf("\n\n                                      ");
            for (i = 0; i < 3; i++)
            {
                printf(" .");
                Sleep(1200);
            }
            printf("\n\n\n                        Ele te puxa para dentro da agua...\n" COLOR_BLUE "            Parece que ele so vai te deixar em paz depois que me matar.\n\n\n\n" COLOR_WHITE);
            system("pause");
            batalha(simples, craft, profissao, bonus_arma(profissao), local, estatus, 8);
        }
    }
    else if (craft->faca > 0)
    {
        if (aux <= 30 + chance_local)
        {
            printf("                               Voce pegou um" COLOR_GREEN " peixe" COLOR_WHITE "!\n\n\n");
            printf("                                Deseja comer agora?\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            if (escolha == '1')
            {
                printf(COLOR_WHITE "\n\n Voce coloca aquele peixe cru na boca e comeca a comer.\n");
                printf(" O gosto e horrivel, mas serve para matar a fome.\n\n\n");
                estatus->fome += 10;
                estatus->saude += 10;
            }
            else
            {
                printf(COLOR_WHITE "\n\n Voce guarda o peixe no inventario.\n\n\n\n");
                simples->carne_crua += 1;
            }
        }
        else
            printf("                                Voce nao pegou nada.\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
    else
    {
        if (aux <= 15 + chance_local)
        {
            printf("                               Voce pegou um" COLOR_GREEN " peixe" COLOR_WHITE "!\n\n\n");
            printf("                                Deseja comer agora?\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            if (escolha == '1')
            {
                printf(COLOR_WHITE "\n\n Voce coloca aquele peixe cru na boca e comeca a comer.\n");
                printf(" O gosto e horrivel, mas serve para matar a fome.\n\n\n");
                estatus->fome += 10;
                estatus->saude += 10;
            }
            else
            {
                printf(COLOR_WHITE "\n\n Voce guarda o peixe no inventario.\n\n\n\n");
                simples->carne_crua += 1;
            }
        }
        else
            printf("                                Voce nao pegou nada.\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
}
void fcraft(Itens *basico, Itens2 *completo, int bonus_arma)
{
    char escolha;

    if (!(completo->barco_1 > 0 && completo->escudo_barco > 0) && !(basico->madeira >= 20 && basico->fibra_natural >= 20) && !(basico->concha >= 20 && basico->fibra_natural >= 10) && !(basico->madeira >= 2 && basico->fibra_natural >= 2 && completo->faca >= 1) && !(basico->graveto >= 2 && basico->fibra_natural >= 2 && basico->pedras >= 3) && !(basico->graveto >= 1 && basico->fibra_natural >= 1 && basico->pedras >= 1) && !(basico->madeira >= 1 && basico->graveto >= 3 && basico->fibra_natural >= 1) && !(basico->fibra_natural >= 2))
    {
        fcraft_letreiro();
        printf(COLOR_RED "\n\n\n\n\n                Voce nao possui itens suficientes para construir algo.\n\n\n\n\n\n\n\n");
    }
    else
    {
        if (completo->barco_1 > 0 && completo->escudo_barco > 0)
        {
            fcraft_letreiro();
            printf("\n                      Voce deseja craftar um Barco Reforcado?\n\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            printf(COLOR_WHITE);
            if (escolha == '1')
            {
                completo->barco_1 -= 1;
                completo->escudo_barco -= 1;
                completo->barco_2 += 1;
            }
            printf(COLOR_WHITE "\n\n\n\n\n\n");
        }
        if (basico->madeira >= 20 && basico->fibra_natural >= 15)
        {
            fcraft_letreiro();
            printf("\n                       Voce deseja craftar um Barco Simples?\n\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            printf(COLOR_WHITE);
            if (escolha == '1')
            {
                basico->fibra_natural -= 15;
                basico->madeira -= 20;
                completo->barco_1 += 1;
            }
            printf(COLOR_WHITE "\n\n\n\n\n\n");
        }
        if (basico->concha >= 20 && basico->fibra_natural >= 10)
        {
            fcraft_letreiro();
            printf("\n                     Voce deseja craftar um Escudo de Conchas?\n\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            printf(COLOR_WHITE);
            if (escolha == '1')
            {
                basico->fibra_natural -= 10;
                basico->concha -= 20;
                completo->escudo_barco += 1;
            }
            printf(COLOR_WHITE "\n\n\n\n\n\n");
        }
        if (basico->madeira >= 2 && basico->fibra_natural >= 2 && completo->faca >= 1)
        {
            fcraft_letreiro();
            printf("\n                           Voce deseja craftar uma Lanca?\n\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            printf(COLOR_WHITE);
            if (escolha == '1')
            {
                basico->madeira -= 2;
                basico->fibra_natural -= 2;
                completo->faca -= 1;
                completo->lanca += 1;
            }
            printf(COLOR_WHITE "\n\n\n\n\n\n");
        }
        if (basico->graveto >= 2 && basico->fibra_natural >= 2 && basico->pedras >= 3)
        {
            fcraft_letreiro();
            printf("\n                          Voce deseja craftar um Machado?\n\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            printf(COLOR_WHITE);
            if (escolha == '1')
            {
                basico->graveto -= 2;
                basico->fibra_natural -= 2;
                basico->pedras -= 3;
                completo->machado += 1;
            }
            printf(COLOR_WHITE "\n\n\n\n\n\n");
        }
        if (basico->graveto >= 1 && basico->fibra_natural >= 1 && basico->pedras >= 1)
        {

            fcraft_letreiro();
            printf("\n                           Voce deseja craftar uma Faca?\n\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            printf(COLOR_WHITE);
            if (escolha == '1')
            {
                basico->graveto -= 1;
                basico->fibra_natural -= 1;
                basico->pedras -= 1;
                completo->faca += 1;
            }
            printf(COLOR_WHITE "\n\n\n\n\n\n");
        }
        if (basico->madeira >= 1 && basico->graveto >= 3 && basico->fibra_natural >= 1)
        {

            fcraft_letreiro();
            printf("\n                         Voce deseja craftar uma Fogueira?\n\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            printf(COLOR_WHITE);
            if (escolha == '1')
            {
                basico->fibra_natural -= 1;
                basico->madeira -= 1;
                basico->graveto -= 3;
                completo->fogueira += 1;
            }
            printf(COLOR_WHITE "\n\n\n\n\n\n");
        }
        if (basico->fibra_natural >= 2)
        {
            fcraft_letreiro();
            printf("\n                    Voce deseja craftar um Recipiente para Agua?\n\n");
            printf("                                      Sim (1)\n");
            printf("                                      Nao (2)\n\n " COLOR_RED "                                       ");
            fflush(stdin);
            fgets(&escolha, 2, stdin);
            printf(COLOR_WHITE);
            if (escolha == '1')
            {
                basico->fibra_natural -= 2;
                completo->recipiente_agua += 1;
            }
            printf(COLOR_WHITE "\n\n\n\n\n\n");
        }
    }
}
void fcraft_letreiro()
{
    system("cls");
    printf(" **********************************************************************************\n");
    printf(" *                                                    ,...                        *\n");
    printf(" *                    .g8\"\"\"bgd                     .d' \"\"  mm                    *\n");
    printf(" *                  .dP'     `M                     dM`     MM                    *\n");
    printf(" *                  dM'       ` `7Mb,od8  ,6\"Yb.   mMMmm  mmMMmm                  *\n");
    printf(" *                  MM            MM' \"' 8)   MM    MM      MM                    *\n");
    printf(" *                  MM.           MM      ,pm9MM    MM      MM                    *\n");
    printf(" *                  `Mb.     ,'   MM     8M   MM    MM      MM                    *\n");
    printf(" *                    `\"bmmmd'  .JMML.   `Moo9^Yo..JMML.    `Mbmo                 *\n");
    printf(" **********************************************************************************\n");
}
void queda_cachoeira(int *saude)
{
    int i;
    int aux;
    system("cls");
    printf(COLOR_WHITE "\n\n\n                      Voce aceita que vai cair da cachoeira.\n");
    printf(COLOR_BLUE "        Acho melhor ao menos eu cair com estilo, para tentar reduzir o dano." COLOR_WHITE "\n\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1000);
    }
    printf("\n\n\n                 Voce se prepara pra dar o melhor salto da sua vida!\n\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1000);
    }
    printf("\n\n\n");
    aux = num_aleatorio();
    if (aux <= 25)
    {
        printf("Apos um salto muito desastrado, voce vai muito fundo e acaba se afogando um pouco.\n\n");
        *saude -= 30;
    }
    else if (aux <= 50)
    {
        printf("Apos um salto um pouco desastrado, voce acaba caindo de barriga.\n\n");
        *saude -= 20;
    }
    else if (aux <= 75)
    {
        printf(" Apos um salto um pouco desastrado, voce acaba caindo de costas.\n\n");
        *saude -= 10;
    }
    else if (aux <= 100)
    {
        printf("Voce pula como se fosse um campeao olimpico em Salto ornamental.\n");
        printf("Apos um salto lindo, os danos sao minimos.\n");
        *saude -= 5;
    }
    aux = num_aleatorio();
    if (aux <= 50)
    {
        printf(COLOR_BLUE "\n Quando eu estava no fundo, eu vi um peixe estranho.\n");
        printf(" Ele brilhava muito, sera que consigo pesca-lo?\n\n\n" COLOR_WHITE);
    }
    else
        printf("\n\n\n\n\n");
    system("pause");
}

int Subida_Descida_Montanha(int local, Sttatus *estatus, Itens2 *craft, Itens *simples, char profissao)
{
    int i;
    int aux;
    system("cls");
    if (local == Cachoeira || local == Encosta_da_montanha)
    {
        printf(COLOR_WHITE "\n\n\n                         Voce comeca a escalar a montanha.\n");
    }
    else
    {
        printf(COLOR_WHITE "\n\n\n                         Voce comeca a descer a montanha.\n");
    }
    printf("\n\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1000);
    }
    printf("\n\n\n");
    aux = num_aleatorio();
    if (aux <= 20)
    {
        printf("   Uma pedra que voce usava para se apoiar acaba se soltando e voce acaba caindo.\n\n\n");
        printf(COLOR_BLUE "        Essa queda nao foi tao grande, aparentemente nao me machuquei tanto. \n\n\n\n\n\n\n\n\n\n" COLOR_WHITE);
        estatus->saude -= 10;
        system("pause");
        return 0;
    }
    else if (aux <= 70)
    {
        printf("                      Voce termina seu caminho com cuidado...\n\n                   Esse cuidado te custou um pouco mais de sede.\n\n\n\n\n\n\n\n\n\n\n");
        estatus->sede -= 5;
    }
    else if (aux <= 100)
    {
        printf("                      Apos um tempo na sua jornada ao destino.\n           Voce sente algo com muitas patas passeando pelas suas costas.\n");
        printf(COLOR_BLUE "            Preciso me apressar o mais rapido possivel para tirar isso.\n\n" COLOR_WHITE);
        printf("\n                                      ");
        for (i = 0; i < 3; i++)
        {
            printf(" .");
            Sleep(1000);
        }
        printf("\n\n Chegando ao destino, voce percebe que o que estava nas suas costas era uma aranha.\n");
        aux = num_aleatorio();
        if (aux <= 60)
        {
            printf(" Voce desesperadamente tenta tirar ela. A aranha nao gostou nada disso...\n\n\n\n\n");
            system("pause");
            batalha(simples, craft, profissao, bonus_arma(profissao), local, estatus, 6);
        }
        else
            printf("                  Voce a tira calmamente e coloca sobre uma pedra.\n                       Ela aparentemente gostou da carona...\n\n\n\n");
    }
    system("pause");
    return 1;
}
void batalha(Itens *simples, Itens2 *craft, char profissao, int bonus_arma, int local, Sttatus *estatus, int animal)
{
    int aux = num_aleatorio(), aux2 = num_aleatorio();
    int i = 0;
    int mvida = 0, mdano = 0;
    char escolha;
    int pdano = 15;
    if (craft->capacete)
        mdano = -1;
    if (craft->lanca)
        pdano += 30;
    else if (craft->machado)
        pdano += 21;
    else if (craft->faca)
        pdano += 15;

    if (animal == 8) /* raid do peixe boss*/
    {
        mvida = 600;
        mdano = 10;
    }
    else if (aux <= 33) /* lutas com animais Fracos */
    {
        switch (animal)
        {
        case (1):
            mvida = 65;
            mdano = 5; /*(3/7)*/
            break;
        case (2):
            mvida = 170;
            mdano = 6; /*(4/9)*/
            break;
        case (3):
            mvida = 135;
            mdano = 5; /*(3/7)*/
            break;
        case (4):
            mvida = 135;
            mdano = 5; /*(3/7)*/
            break;
        case (5):
            mvida = 170;
            mdano = 6; /*(4/9)*/
            break;
        case (6):
            mvida = 205;
            mdano = 6; /*(4/9)*/
            break;
        case (7):
            mvida = 240;
            mdano = 7; /*(5/10)*/
            break;
        default:
            break;
        }
    }
    else if (aux <= 65) /* luta com animal normal*/
    {
        switch (animal)
        {
        case (1):
            mvida = 100;
            mdano = 5; /*(3/7)*/
            break;
        case (2):
            mvida = 205;
            mdano = 6; /*(4/9)*/
            break;
        case (3):
            mvida = 170;
            mdano = 6; /*(4/9)*/
            break;
        case (4):
            mvida = 170;
            mdano = 6; /*(4/9)*/
            break;
        case (5):
            mvida = 205;
            mdano = 6; /*(4/9)*/
            break;
        case (6):
            mvida = 240;
            mdano = 7; /*(5/10)*/
            break;
        case (7):
            mvida = 275;
            mdano = 7; /*(5/10)*/
            break;
        default:
            break;
        }
    }
    else if (aux <= 100) /* luta com animal forte*/
    {
        switch (animal)
        {
        case (1):
            mvida = 135;
            mdano = 5; /*(3/7)*/
            break;
        case (2):
            mvida = 240;
            mdano = 7; /*(5/10)*/
            break;
        case (3):
            mvida = 205;
            mdano = 6; /*(4/9)*/
            break;
        case (4):
            mvida = 205;
            mdano = 6; /*(4/9)*/
            break;
        case (5):
            mvida = 240;
            mdano = 7; /*(5/10)*/
            break;
        case (6):
            mvida = 275;
            mdano = 7; /*(5/10)*/
            break;
        case (7):
            mvida = 300;
            mdano = 8; /*(6/12)*/
            break;
        default:
            break;
        }
    }
    for (; mvida > 0;)
    {
        system("cls");
        if (estatus->saude <= 0 || estatus->fome <= 0 || estatus->sede <= 0)
            Morreu_bobao();
        if (estatus->saude > 100)
            estatus->saude = 100;
        if (estatus->fome > 100)
            estatus->fome = 100;
        if (estatus->sede > 100)
            estatus->sede = 100;
        /* IMPRIME OS STATUS NA TELA */
        printf(COLOR_WHITE " **********************************************************************************\n");
        printf(" *                                                                                *\n");
        printf(" *         Saude:%4d/100         Fome:%4d/100          Sede:%4d/100            *\n", estatus->saude, estatus->fome, estatus->sede);
        printf(" *                                                                                *\n");
        printf(" **********************************************************************************\n");
        animais(mvida, animal, aux);
        printf(COLOR_WHITE "\n                               O que voce vai fazer?\n\n");
        printf("                                    Atacar (1)\n");
        printf("                                  Inventario (2)\n\n " COLOR_RED "                                       ");
        //fflush(stdin);
        fgets(&escolha, 2, stdin);
        if (escolha == '1')
        {
            system("cls");
            if (craft->lanca)
                printf(COLOR_WHITE "\n\n\n               Voce parte para cima para dar um ataque com sua Lanca.\n");
            else if (craft->machado)
                printf(COLOR_WHITE "\n\n\n              Voce parte para cima para dar um ataque com seu Machado.\n");
            else if (craft->faca)
                printf(COLOR_WHITE "\n\n\n               Voce parte para cima para dar um ataque com sua Faca.\n");
            else if (!craft->lanca && !craft->machado && !craft->faca)
                printf(COLOR_WHITE "\n\n\n               Voce parte para cima para dar um ataque com suas Maos.\n");
            printf("\n\n                                      ");
            for (i = 0; i < 3; i++)
            {
                printf(" .");
                Sleep(1000);
            }
            aux2 = num_aleatorio();
            if (aux2 <= 20)
            {
                printf(COLOR_WHITE "\n\n\n                                Voce errou o ataque.\n");
            }
            else if (aux2 <= 40)
            {
                printf(COLOR_WHITE "\n\n\n                           Voce acertou um ataque Fraco.\n");
                mvida -= pdano * 0.75;
            }
            else if (aux2 <= 80)
            {
                printf(COLOR_WHITE "\n\n\n                          Voce acertou um ataque Normal.\n");
                mvida -= pdano;
            }
            else if (aux2 <= 100)
            {
                printf(COLOR_WHITE "\n\n\n                           Voce acertou um ataque Forte.\n");
                mvida -= pdano * 1.5;
            }
            printf("\n\n                                      ");
            for (i = 0; i < 3; i++)
            {
                printf(" .");
                Sleep(1000);
            }
            estatus->sede -= 2;
            estatus->fome -= 2;
            aux2 = num_aleatorio();
            printf("\n\n\n                           Ele parte para cima de voce.\n");
            printf("\n\n                                      ");
            for (i = 0; i < 3; i++)
            {
                printf(" .");
                Sleep(1000);
            }
            if (aux2 <= 30)
            {
                printf("\n\n\n                                Ele errou o ataque.\n\n\n");
            }
            else if (aux2 <= 50)
            {
                printf("\n\n\n                           Ele acertou um ataque Fraco.\n\n\n");
                estatus->saude -= mdano * 0.75;
            }
            else if (aux2 <= 80)
            {
                printf("\n\n\n                           Ele acertou um ataque Normal.\n\n\n");
                estatus->saude -= mdano;
            }
            else if (aux2 <= 100)
            {
                printf("\n\n\n                           Ele acertou um ataque Forte.\n\n\n");
                estatus->saude -= mdano * 1.5;
            }
            system("pause");
        }
        else if (escolha == '2')
            inventario(simples, craft, profissao, bonus_arma, local, estatus, 1);
    }

    if (!craft->lanca && !craft->machado && !craft->faca)
    {
        system("cls");
        printf(COLOR_WHITE "\n\n\n\n\n\n\n\n\n\n\n                Voce conseguiu desmaia-lo, melhor sair correndo...\n\n\n\n\n\n\n\n\n\n\n\n");
    }
    else
    {
        if (aux <= 33) /* lutas com animais Fracos */
        {
            switch (animal)
            {
            case (1):
                simples->carne_crua += 1;
                break;
            case (2):
                simples->carne_crua += 2;
                simples->pedras += 1;
                break;
            case (3):
                simples->carne_crua += 1;
                break;
            case (4):
                simples->carne_crua += 1;
                break;
            case (5):
                simples->carne_crua += 1;
                break;
            case (6):
                simples->carne_crua += 1;
                break;
            case (7):
                simples->carne_crua += 4;
                break;
            default:
                simples->carne_crua += 20;
                estatus->saude = 100;
                estatus->fome = 100;
                estatus->sede = 100;
                break;
            }
        }
        else if (aux <= 65) /* luta com animal normal*/
        {
            switch (animal)
            {
            case (1):
                simples->carne_crua += 1;
                break;
            case (2):
                simples->carne_crua += 3;
                simples->pedras += 1;
                break;
            case (3):
                simples->carne_crua += 2;
                break;
            case (4):
                simples->carne_crua += 2;
                break;
            case (5):
                simples->carne_crua += 1;
                break;
            case (6):
                simples->carne_crua += 1;
                break;
            case (7):
                simples->carne_crua += 5;
                break;
            default:
                simples->carne_crua += 20;
                estatus->saude = 100;
                estatus->fome = 100;
                estatus->sede = 100;
                break;
            }
        }
        else if (aux <= 100) /* luta com animal forte*/
        {
            switch (animal)
            {
            case (1):
                simples->carne_crua += 1;
                break;
            case (2):
                simples->carne_crua += 4;
                simples->pedras += 1;
                break;
            case (3):
                simples->carne_crua += 3;
                break;
            case (4):
                simples->carne_crua += 3;
                break;
            case (5):
                simples->carne_crua += 2;
                break;
            case (6):
                simples->carne_crua += 2;
                break;
            case (7):
                simples->carne_crua += 6;
                break;
            default:
                simples->carne_crua += 20;
                estatus->saude = 100;
                estatus->fome = 100;
                estatus->sede = 100;
                break;
            }
        }
        if (animal == 8)
        {
            system("cls");
            printf(COLOR_WHITE "\n\n\n\n\n\n\n\n                       Voce conseguiu algumas carnes dele...\n\n\n");
            printf(COLOR_BLUE "                      Me sinto muito bem, por algum motivo...\n\n\n\n\n\n\n\n\n\n\n\n" COLOR_WHITE);
        }
        else
        {
            system("cls");
            printf(COLOR_WHITE "\n\n\n\n\n\n\n\n\n\n\n                       Voce conseguiu algumas carnes dele...\n\n\n\n\n\n\n\n\n\n\n\n");
        }
    }
}
void animais(int vida, int animal, int aux)
{
    if (animal == 8)
    {
        printf(COLOR_YELLOW "                                      /`-._\n");
        printf("                                     /_,.._`:-\n");
        printf("                                 ,.-'  ,   ``-:_,-')\n");
        printf("                                > ó ):';       _  {\n");
        printf("                                 `-._ `'__,.-''\\`-.)\n");
        printf("                                    `\\\\/  \\,.-'``\n\n" COLOR_GREEN);
        printf("                                     %3d/600\n", vida);
        printf(COLOR_WHITE);
    }
    else if (aux <= 33) /* lutas com animais Fracos */
    {
        switch (animal)
        {
        case (1):
            printf("\n                                     _~^~^~_\n");
            printf("                                 \\) /  ó ò  \\ (/\n");
            printf("                                   '_   -   _'\n");
            printf("                                   | '-----' |\n\n" COLOR_GREEN);
            printf("                                     %3d/65\n", vida);
            break;
        case (2):
            printf("                                      _---_\n");
            printf("                                     ´ _ _ `\n");
            printf("                                    d| ó ò |b\n");
            printf("                                     (  ¨  )\n");
            printf("                                     | >.< |\n");
            printf("                                   ~~(__|__)\n\n" COLOR_GREEN);
            printf("                                     %3d/170\n", vida);
            break;
        case (3):
            printf("                              /\\                 /\\   \n");
            printf("                             / \\'._   (\\_/)   _.'/ \\   \n");
            printf("                            /_.''._'--(ó.ò)--'_.''._\\  \n");
            printf("                            | \\_ / `;=/ \" \\=;` \\ _/ |     \n");
            printf("                             \\/ `\\__|`\\___/`|__/´ \\/       \n");
            printf("                              `      \\(_|_)/      ´\n");
            printf("                                      \" ` \"  \n" COLOR_GREEN);
            printf("                                     %3d/135\n", vida);
            break;
        case (4):
            printf("                                  _\n");
            printf("                                .'_`--.___   __\n");
            printf("                               ( 'ô`   - .`.'_ )\n");
            printf("                                `-._      `_`./_\n");
            printf("                                 ,_/\\\\    ( .'/ )\n");
            printf("                                 ,__//`---'`-'_/\n\n" COLOR_GREEN);
            printf("                                     %3d/135\n", vida);
            break;
        case (5):
            printf("\n                                  /\n");
            printf("                                 / (_/\\ ____\n");
            printf("                                 )  ô /´  -´\\\n");
            printf("                                 `---´_,_,_,/\n");
            printf("                                     <´<´ `-,`,\n\n" COLOR_GREEN);
            printf("                                     %3d/170\n", vida);
            break;
        case (6):
            printf("\n                                         __\n");
            printf("                                        ( ')\n");
            printf("                                    /`óò|´\\´\\\n");
            printf("                                   ´    '  ` `\n\n" COLOR_GREEN);
            printf("                                     %3d/205\n", vida);
            break;
        case (7):
            printf("                                   .--.\n");
            printf("                                 .'óò  `.\n");
            printf("                              >-´'-.-´: :\n");
            printf("                                     .' ;     ___\n");
            printf("                                    '  '.__.-' __'.\n");
            printf("                                    `.______,'´  `)\n\n" COLOR_GREEN);
            printf("                                     %3d/240\n", vida);
            break;
        default:
            break;
        }
    }
    else if (aux <= 65) /* luta com animal normal*/
    {
        switch (animal)
        {
        case (1):
            printf("\n                                     _~^~^~_\n");
            printf("                                 \\) /  o o  \\ (/\n");
            printf("                                   '_   -   _'\n");
            printf("                                   | '-----' |\n\n" COLOR_GREEN);
            printf("                                     %3d/100\n", vida);
            break;
        case (2):
            printf("                                      _---_\n");
            printf("                                     ´ _ _ `\n");
            printf("                                    d| o o |b\n");
            printf("                                     (  ¨  )\n");
            printf("                                     | >.< |\n");
            printf("                                   ~~(__|__)\n\n" COLOR_GREEN);
            printf("                                     %3d/205\n", vida);
            break;
        case (3):
            printf("                              /\\                 /\\   \n");
            printf("                             / \\'._   (\\_/)   _.'/ \\   \n");
            printf("                            /_.''._'--(o.o)--'_.''._\\  \n");
            printf("                            | \\_ / `;=/ \" \\=;` \\ _/ |     \n");
            printf("                             \\/ `\\__|`\\___/`|__/´ \\/       \n");
            printf("                              `      \\(_|_)/      ´\n");
            printf("                                      \" ` \"  \n" COLOR_GREEN);
            printf("                                     %3d/170\n", vida);
            break;
        case (4):
            printf("                                  _\n");
            printf("                                .'_`--.___   __\n");
            printf("                               ( 'o`   - .`.'_ )\n");
            printf("                                `-._      `_`./_\n");
            printf("                                 ,_/\\\\    ( .'/ )\n");
            printf("                                 ,__//`---'`-'_/\n\n" COLOR_GREEN);
            printf("                                     %3d/170\n", vida);
            break;
        case (5):
            printf("\n                                  /\n");
            printf("                                 / (_/\\ ____\n");
            printf("                                 )  o /´  -´\\\n");
            printf("                                 `---´_,_,_,/\n");
            printf("                                     <´<´ `-,`,\n\n" COLOR_GREEN);
            printf("                                     %3d/205\n", vida);
            break;
        case (6):
            printf("\n                                         __\n");
            printf("                                        ( ')\n");
            printf("                                    /`oo|´\\´\\\n");
            printf("                                   ´    '  ` `\n\n" COLOR_GREEN);
            printf("                                     %3d/240\n", vida);
            break;
        case (7):
            printf("                                   .--.\n");
            printf("                                 .'oo  `.\n");
            printf("                              >-´'-.-´: :\n");
            printf("                                     .' ;     ___\n");
            printf("                                    '  '.__.-' __'.\n");
            printf("                                    `.______,'´  `)\n\n" COLOR_GREEN);
            printf("                                     %3d/275\n", vida);
            break;
        default:
            break;
        }
    }
    else if (aux <= 100) /* luta com animal forte*/
    {
        switch (animal)
        {
        case (1):
            printf("\n                                     _~^~^~_\n");
            printf("                                 \\) /  ò ó  \\ (/\n");
            printf("                                   '_   ¬   _'\n");
            printf("                                   | '-----' |\n\n" COLOR_GREEN);
            printf("                                     %3d/135\n", vida);
            break;
        case (2):
            printf("                                      _---_\n");
            printf("                                     ´ _ _ `\n");
            printf("                                    d| ò ó |b\n");
            printf("                                     (  ¨  )\n");
            printf("                                     | >.< |\n");
            printf("                                   ~~(__|__)\n\n" COLOR_GREEN);
            printf("                                     %3d/240\n", vida);
            break;
        case (3):
            printf("                              /\\                 /\\   \n");
            printf("                             / \\'._   (\\_/)   _.'/ \\   \n");
            printf("                            /_.''._'--(ò.ó)--'_.''._\\  \n");
            printf("                            | \\_ / `;=/ \" \\=;` \\ _/ |     \n");
            printf("                             \\/ `\\__|`\\___/`|__/´ \\/       \n");
            printf("                              `      \\(_|_)/      ´\n");
            printf("                                      \" ` \"  \n" COLOR_GREEN);
            printf("                                     %3d/205\n", vida);
            break;
        case (4):
            printf("                                  _\n");
            printf("                                .'_`--.___   __\n");
            printf("                               ( 'ó`   - .`.'_ )\n");
            printf("                                `-._      `_`./_\n");
            printf("                                 ,_/\\\\    ( .'/ )\n");
            printf("                                 ,__//`---'`-'_/\n\n" COLOR_GREEN);
            printf("                                     %3d/205\n", vida);
            break;
        case (5):
            printf("\n                                  /\n");
            printf("                                 / (_/\\ ____\n");
            printf("                                 )  ó /´  -´\\\n");
            printf("                                 `---´_,_,_,/\n");
            printf("                                     <´<´ `-,`,\n\n" COLOR_GREEN);
            printf("                                     %3d/240\n", vida);
            break;
        case (6):
            printf("\n                                         __\n");
            printf("                                        ( ')\n");
            printf("                                    /`òó|´\\´\\\n");
            printf("                                   ´    '  ` `\n\n" COLOR_GREEN);
            printf("                                     %3d/275\n", vida);
            break;
        case (7):
            printf("                                   .--.\n");
            printf("                                 .'òó  `.\n");
            printf("                              >-´'-.-´: :\n");
            printf("                                     .' ;     ___\n");
            printf("                                    '  '.__.-' __'.\n");
            printf("                                    `.______,'´  `)\n\n" COLOR_GREEN);
            printf("                                     %3d/300\n", vida);
            break;
        default:
            break;
        }
    }
}
/* FINAIS */
void final_1()
{
    int i;
    system("cls");
    printf(COLOR_WHITE "\n\n\n               Voce comeca a caminhar em frente, cada vez mais fundo.\n");
    printf("    Em um momento, voce nao consegue se apoiar mais no chao e comeca a nadar.\n");
    printf("\n\n                                      ");
    /* IMPRIME 3 PONTOS DEMORADOS PARA DAR SENSACAO DE BUSCA */
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1500);
    }
    printf("\n\n                               Voce continua nadando.");
    printf("\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(2000);
    }
    printf("\n\n                    Serio que voce achou que isso daria certo?\n");
    printf("\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1500);
    }
    printf("\n\n\n Voce nadou por apenas alguns metros, ondas fortes cairam sobre voce.\n");
    printf(" Voce comeca a se afogar, e nao tem nada o que possa fazer.\n\n\n\n");
    system("pause");
    Morreu_bobao();
}
void final_2(int *saude, int *sede, int *fome)
{
    int i;
    system("cls");
    printf(COLOR_WHITE "\n\n\n    Voce tira do inventario seu barco, deus sabe como voce estava carregando ele.\n");
    printf("                 Voce comeca a empurra-lo e sobe em cima dele.\n");
    printf("\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1500);
    }
    printf("\n\n Como o Programador do jogo esqueceu de colocar remos ( de proposito ).\n");
    printf(" Voce sai sem rumo, uma onda grande bate em seu barco.\n");
    printf(" O criador esqueceu de avisar que voce tem que proteger seu barco. \n");
    printf(" Com o que? Voce me pergunta.\n");
    printf(" Obviamente que com conchas e fibras!");
    printf("\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(2000);
    }
    printf("\n\n Ah, ja ia me esquecendo de voce e seu pequeno barco fragil. \n");
    printf(" No meio de sua pequena viagem, uma onda muito grande te atinge.\n");
    printf(" Voce tenta lutar para se apoiar no barco, mas nao resta mais nada dele.\n");
    printf(" Depois de um tempo se debatendo, voce desiste e se entrega ao mar.\n\n\n");
    system("pause");
    system("cls");
    printf("\n\n\n          Voce apareceu na Praia de novo, com sede, machucado e com fome.\n");
    printf("\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(2000);
    }

    printf("\n\n\n\n                     O mar aparentemente foi piedoso com voce.\n");
    printf("\n\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(2000);
    }
    printf("\n\n\n\n\n\n\n                          Espero que tenha trazido agua.\n\n\n");
    system("pause");
    *sede -= 30;
    *saude -= 30;
    *fome -= 20;
}
void final_3()
{
    int i;
    system("cls");
    printf(COLOR_WHITE "\n\n\n    Voce tira do inventario seu barco, deus sabe como voce estava carregando ele.\n");
    printf("                 Voce comeca a empurra-lo e sobe em cima dele.\n");
    printf("\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1500);
    }
    printf("\n\n Como o Programador do jogo esqueceu de colocar remos ( de proposito ).\n");
    printf(" Voce sai sem rumo, uma onda grande bate em seu barco.\n");
    printf("\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1500);
    }
    printf("\n\n Seu barco ja nao era tao fragil, as ondas apenas retiraram o escudo de conchas. \n");
    printf(" Sua viagem demorou uma eternidade, mas por algum motivo estava tudo bem.\n");
    printf("\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1500);
    }
    printf("\n\n\n\n");
    system("pause");
    system("cls");
    printf("\n\n\n              Ja era noite, voce acaba adormecendo durante o processo.\n");
    printf("               Voce escuta os pipilos das gaivotas e acaba acordando.\n");
    printf("\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(2000);
    }
    printf(COLOR_BLUE "\n\n                          Onde estou agora? Estou a salvo?\n" COLOR_WHITE);
    printf("\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1500);
    }
    printf("\n\n  Voce e seu barco estavam atracados em alguma praia, ao longe se via uma cidade.\n");
    printf("\n\n                        Enfim, voce tinha" COLOR_GREEN " SOBREVIVIDO" COLOR_WHITE ".\n\n\n\n\n\n");
    system("pause");
    creditos();
    exit(0);
}
void final_4()
{
    int aux = num_aleatorio(); /* NUMERO ALEATORIO */
    int i = 0;
    system("cls");
    printf(COLOR_WHITE "\n\n\n            Voce comeca a escrever SOS na areia da praia com um graveto.\n");
    printf("\n\n\n                                      ");
    /* IMPRIME 3 PONTOS DEMORADOS PARA DAR SENSACAO DE BUSCA */
    for (i = 0; i < 3; i++)
    {
        printf(" .");
        Sleep(1500);
    }
    printf("\n\n");
    if (aux <= 10)
    {
        printf(" Assim que voce termina de escrever,um forte vento e um barulho ensurdecedor !!\n");
        printf(" Voce olha para cima com dificuldade por conta do Sol.\n");
        printf(" Apos alguns segundos voce percebe que e um helicoptero, voce esta a " COLOR_GREEN "SALVO" COLOR_WHITE " !!\n");
        printf("\n                                      ");
        for (i = 0; i < 3; i++)
        {
            printf(" .");
            Sleep(1500);
        }
        printf("\n\n No final, nao foi tao dificil sobreviver, nao e mesmo?\n\n\n\n\n\n\n\n");
        system("pause");
        system("cls");
        printf("\n\n\n\n\n\n\n Esse foi o final \"facil\", voce tinha apenas 10%c de sucesso.\n", 37);
        printf(" Pena que ele nao demonstra suas reais habilidades de sobrevivencia.\n");
        printf("\n                                      ");
        for (i = 0; i < 3; i++)
        {
            printf(" .");
            Sleep(1500);
        }
        printf("\n\n\n\n\n\n\n Voce apenas teve sorte...\n\n\n\n\n\n");
        system("pause");
        creditos();
        system("cls");
        printf("\n\n\n Voce acaba pegando no sono no meio da viagem enquanto lia os creditos.\n");
        printf("\n                                      ");
        for (i = 0; i < 3; i++)
        {
            printf(" .");
            Sleep(1500);
        }
        printf("\n\n Voce estava tao feliz por ter dado a sorte grande que esqueceu de colocar o cinto.\n");
        printf("\n Aquele mal tempo ainda nao havia passado e em uma instabilidade voce acaba caindo. \n");
        printf("\n                                      ");
        for (i = 0; i < 3; i++)
        {
            printf(" .");
            Sleep(1500);
        }
        printf("\n\n\n\n\n\n\n Parece que voce nao tem tanta sorte assim...\n\n\n\n\n");
        system("pause");
        Morreu_bobao();
    }
    else
    {
        printf("\n\n                                   Nada acontece.\n\n\n\n\n\n\n\n\n\n\n\n");
    }
}