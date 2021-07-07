#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct tipojogo
{
	char dificuldade;
	char username[21];
	int ranking;
	int pontuacao;
};
struct tiposuspeito	//struct que guardará as características dos suspeitos, executado na funcao suspeito.
{
	char cabelo[20];
	char sexo[20];
	char acessorio[20];
	char esporte[20];
	char carro[20];
	int guardar;
};

struct tipocaract //struct que guardará todas as caracteríscas dos ladroes contidos no caso.
{
	char nome[20];
	char cabelo[20];
	char sexo[10];
	char acessorio[20];
	char esporte[20];
	char carro[20];
};

struct tipopaiscaso //struct que guardará todos os países, cidades e dicas contidas no caso selecionado.
{
	char paiscaso[20];
	char cidade1caso[20];
	char cidade2caso[20];
	char cidade3caso[20];
	char dica1caso[100];
	char dica2caso[100];
	char dica3caso[100];
};

struct tipopaisforacaso //struct que guardará todos os países e cidades contidas fora do caso selecionado.
{
	char paisforacaso[20];
	char cidade1foracaso[20];
	char cidade2foracaso[20];
	char cidade3foracaso[20];
};

void colocarnoranking(int, int, char[]);
int tempo(int time);
void addcasos();
int suspeito(int *, tipocaract*, char*, tiposuspeito*);
void trocarsenhaadm();
void trocarloginadm();
void alterarnomes();
void rankingporpatente();
void rankingporpontos();
void top5();
int checaradm();
int jogo(tipopaiscaso*, char*, tipopaisforacaso*, tipocaract*, int*, int*, tiposuspeito*, tipojogo*);
void leituracasos(int*, char*);
void leituraladroes(int*, char*, tipocaract*);
void leiturapaiscaso(int*, char*, tipopaiscaso*);
void leiturapaisforacaso(int*, char*, tipopaisforacaso*);

int main()
{

	srand(time(NULL));
	char username[20], sair = 'S', charsaida, c = '0';
	char loginadm[20], senhaadm[20], logincripto[100], senhacripto[100];
	int menuprincipal, menuadm, menurank, paisinicial, resultadojogo, checkadm;
	int tempo = 17, fim = 1;

	int ncasos, i = 0, j = 0, d, ncasosfilt = 0, r, nladroes, npaisc, npaisf, contdificuldade = 0;
	char mcasos[50][50], mcasosfilt[50][50], casoselec[50];

	struct tipojogo sjogo;
	struct tipocaract ladrao[20];
	struct tipopaiscaso pcaso[20];
	struct tipopaisforacaso fcaso[20];
	struct tiposuspeito susp;

	system("cls");
	do
	{
		sjogo.dificuldade = '0';
		contdificuldade = 0;
		fim = 1;
		//menu inicial do jogo.
		printf("Ola jogador, escolha qual das opcoes a seguir voce deseja acessar:\n");
		printf("1 - Iniciar um jogo novo.\n");
		printf("2 - Mostrar o ranking do jogo.\n");
		printf("3 - Entrar no modo do administrador.\n");
		printf("0 - Sair do jogo.\n");
		scanf("%i", &menuprincipal);
		switch (menuprincipal)
		{
		case 1://novo jogo.
		{
			sjogo.pontuacao = 0;
			contdificuldade = 0;
			do
			{
				contdificuldade++;
				switch (contdificuldade)
				{
				case 1: printf("Digite seu nome detetive.\n");
					scanf("%s", &sjogo.username);
					system("cls");
					sjogo.dificuldade = '1';//dificuldade do caso fácil.
					break;

				case 2:
					sjogo.dificuldade = '2'; //dificuldade do caso médio.
					break;

				case 3:
					sjogo.dificuldade = '3';//dificuldade do caso difícil.
					break;
				case 4:
					printf("Parabens, voce conseguiu prender toda a gangue dos Tribais de Bagota.\n");
					printf("Parece que por enquanto nao ha nenhum caso que voce seja necessitado.\n");
					printf("\n\nAperte 1 e enter para voltar ao menu principal.\n");
					fim = 0;
					fflush(stdin);
					do
					{
						scanf("%c", &c);
					} while (c == '\n');
					break;
				}

				leituracasos(&ncasos, &mcasos[0][0]);//chama a função que realizará a leitura de todos os casos existentes.
				ncasosfilt = 0;
				for (i = 0; i<ncasos; i++)
				{
					d = strlen(mcasos[i]);
					if (mcasos[i][d - 1] == sjogo.dificuldade)
					{
						strcpy(&mcasosfilt[ncasosfilt][0], &mcasos[i][0]);
						mcasosfilt[ncasosfilt][d - 1] = '\0';
						ncasosfilt++;
					}
				}
				r = rand() % (ncasosfilt);// escolher um caso aleatório entre os casos filtrados com a dificuldade escolhida.
				strcpy(casoselec, &mcasosfilt[r][0]);//copia o nome do caso selecionado sem o valor da dificuldade, ex(Coreia do Norte1 vira Coreia do Norte).
				leituraladroes(&nladroes, casoselec, ladrao);//função que realizará a leitura de todos os ladrões e sua características contidos no caso selecionado, ex: Coreia do NorteLadrao.
				leiturapaiscaso(&npaisc, casoselec, pcaso);//função que realizará a leitura dos paises, cidades e dicas contidas no caso escolido, ex: Coreia do Norte.
				leiturapaisforacaso(&npaisf, casoselec, fcaso);//função que realizará a leitura dosos paises e cidades que estão fora do caso escolhido, ex: Coreia do NortePaises.
				if (fim == 1)
					fim = jogo(pcaso, casoselec, fcaso, ladrao, &nladroes, &npaisc, &susp, &sjogo);//função que rodará o jogo.
			} while (fim == 1);
			break;
		}
		case 2:
		{
			do
			{
				system("cls");
				printf("Voce selecionou mostrar o ranking do jogo.\n");
				printf("Escolha qual dos rankings voce deseja ver.\n");
				printf("1 - Pontuacao e ranking dos 5 melhores jogares.\n");
				printf("2 - Pontuacao e ranking de todos os jogadores por ordem de pontos.\n");
				printf("3 - Pontuacao e ranking de todos os jogadores por ordem de rank.\n");
				printf("0 - Sair desta selecao.\n");
				scanf("%i", &menurank);
				switch (menurank)
				{
				case 1:
				{
					top5();
					printf("\n\nAperte 1 e enter para voltar ao menu anterior.\n");
					fflush(stdin);
					do
					{
						scanf("%c", &c);
					} while (c == '\n');

					break;
				}
				case 2:
				{
					rankingporpontos();
					printf("\n\nAperte 1 e enter para voltar ao menu anterior.\n");
					fflush(stdin);
					do
					{
						scanf("%c", &c);
					} while (c == '\n');
					break;
				}
				case 3:
				{
					rankingporpatente();
					printf("\n\nAperte 1 e enter para voltar ao menu anterior.\n");
					fflush(stdin);
					do
					{
						scanf("%c", &c);
					} while (c == '\n');
					break;
				}
				case 0:
				{
					printf("Voce selecionou sair do menu dos rankings.\n");
					break;
				}
				default:
				{
					printf("Opcao invalida.\n");
					break;
				}
				}
			} while (menurank != 0);
			break;
		}
		case 3:
		{
			system("cls");
			printf("Voce selecionou entrar no modo do administrador.\n");
			checkadm = checaradm();
			if (checkadm == 1)
			{
				do
				{
					printf("Voce entrou no modo do administrador.\n");
					printf("Escolha a opcao que voce deseja realizar:\n");
					printf("1 - Alterar nome de jogadores.\n");
					printf("2 - Alterar o seu login.\n");
					printf("3 - Alterar a sua senha.\n");
					printf("4 - Adicionar casos.\n");
					printf("0 - Sair do menu.\n");
					scanf("%i", &menuadm);
					switch (menuadm)
					{
					case 1:
					{
						alterarnomes();
						break;
					}
					case 2:
					{
						trocarloginadm();
						break;
					}
					case 3:
					{
						trocarsenhaadm();
						break;
					}
					case 4:
					{
						printf("Voce escolheu adicionar casos.\n");
						addcasos();
						break;
					}
					case 0:
						break;
					default:
					{
						printf("Voce selecionou uma opcao invalida.\n");
						break;
					}
					}
				} while (menuadm != 0);
			}
			else
			{
				printf("Senha ou login invalido(s).\n");
			}
			break;
		}
		case 0:
		{
			printf("Voce saiu do jogo.\n");
			break;
		}
		default:
		{
			printf("Voce selecionou uma opcao invalida.\n");
			break;
		}
		}
	} while (menuprincipal != 0);
	system("pause");


	//return 0;
}

int jogo(tipopaiscaso *pcaso, char *casoselec, tipopaisforacaso *fcaso, tipocaract *ladrao, int *nladrao, int* npaisc, tiposuspeito *susp, tipojogo *sjogo)
{
	FILE *arqroubo;
	char itemroubo[50], c, paisatual[50], character = '\n', nome[21];
	int i = 0, j = 0, op, op1, op2, flag = 1, time = 8, flag2 = 0, flag3 = 0, flag4 = 0, f = 0, k = 0, x = 0, flag5 = 0, count5 = 0;
	strcpy(itemroubo, casoselec);
	strcat(itemroubo, "Roubo.txt");
	//leitura do arquivo que contem o objeto roubado do caso escolhido anteriormente. Ex: Coreia do NorteRoubo.
	arqroubo = fopen(itemroubo, "r");
	k = *npaisc;
	if (arqroubo == NULL)
	{
		printf("Erro! Contate o administrado!\n");
	}
	else
	{
		while (!feof(arqroubo))
		{
			c = getc(arqroubo);
			if (c == '\n')
				break;
			itemroubo[i] = c;
			i++;
		}
		itemroubo[i] = '\0';
		fclose(arqroubo);
	}
	i = 0;
	j = 0;
	printf("Seu trabalho eh rastrear e capturar o ladrao que roubou %s.\n", itemroubo);
	printf("Suspeito na cena do crime era %s.\n", ladrao->sexo);
	printf("Voce tera ateh Domingo as 17:00 para captura-lo.\n");
	strcpy(paisatual, pcaso->paiscaso);
	do
	{
		do
		{
			flag2 = tempo(time);
			if (flag2 == 3)
				time = time + 8;
			if (flag2 == 1)
			{
				flag = 0;
				break;
			}
			j = 0;
			while (flag4>0)
			{
				if (strcmp(paisatual, fcaso[j].paisforacaso) == 0)
				{
					break;
				}
				j++;
			}
			printf("Pais atual: %s\n", paisatual);
			printf("1 - Locais para Investigacao.\n");
			printf("2 - Sistema Interpol.\n");
			printf("3 - Mudar de pais.\n");
			printf("0 - Retornar ao menu principal.\n");
			scanf("%d", &op);
			printf("\n\n");
		} while (op>3 || op<0);

		switch (op)
		{
		case 0:
			printf("Voce escolheu sair do jogo e retornar ao menu principal.\n");
			printf("Caso ja tenha passado de algum caso, sua pontuacao ateh o instante foi salva.\n");
			return 0;
		case 1:
			printf("Cidades:\n");
			if (flag4>0)
			{
				printf("1 - %s\n", fcaso[j].cidade1foracaso);
				printf("2 - %s\n", fcaso[j].cidade2foracaso);
				printf("3 - %s\n", fcaso[j].cidade3foracaso);
				printf("0 - Retornar ao menu anterior.\n");
				do {
					scanf("%d", &op1);
				} while (op1 > 3 || op1 < 0);
				printf("\n\n");
				if (op1 == 0)
				{
					break;
				}
				else
				{//Caso o pais não tenha sido visitado pelo suspeito imprime esta mensagem
					printf("Os habitantes locais nao viram nenhum sinal do suspeito.\n");
					time = time + 3;
				}
			}
			else
			{//Imprime a dica da cidade selecionada
				printf("1 - %s\n", pcaso[i].cidade1caso);
				printf("2 - %s\n", pcaso[i].cidade2caso);
				printf("3 - %s\n", pcaso[i].cidade3caso);
				printf("0 - Retornar ao menu anterior.\n");
				do {
					scanf("%d", &op1);
					printf("\n\n");
					switch (op1)
					{
					case 1:	printf("%s\n", pcaso[i].dica1caso);
						time = time + 3;
						break;

					case 2:	printf("%s\n", pcaso[i].dica2caso);
						time = time + 4;
						break;

					case 3:	printf("%s\n", pcaso[i].dica3caso);
						time = time + 5;
						if (pcaso[k - 1].cidade3caso == pcaso[i].cidade3caso)
						{
							if (flag == 0)
							{
								printf("A justica foi feita. O ladrao pagara pelos seus crimes.\nO item %s foi devolvido a %s.\nContinue sua investigacao atras da gangue dos Tribais de Bagota.\n", itemroubo, pcaso->paiscaso);
								sjogo->pontuacao = sjogo->pontuacao + (161 - time)*(sjogo->dificuldade - 48);
								printf("Digite 1 e enter para iniciar o proximo caso, detetive.\n");
								do
								{
									scanf("%c", &character);
								} while (character == '\n');
								for (count5 = 0; sjogo->username[count5]; count5++)
								{
									nome[count5] = sjogo->username[count5];
								}
								nome[count5] = '\0';
								colocarnoranking(sjogo->pontuacao,sjogo->dificuldade,nome);
								system("cls");
								return 1;
							}
							else
							{
								printf("Voce chegou ao suspeito, mas devido a falta de provas da interpol, ele acabou nao sendo preso.\n");
								printf("Mais uma vez a gange dos Tribais de Bagota escapou da justica.\n");
								printf("Digite 1 e enter para retornar ao menu principal, detetive.\n");
								do
								{
									scanf("%c", &character);
								} while (character == '\n');
								return 0;
							}
						}
						break;
					case 0:
						break;
					default:
						printf("Voce escolheu um caso invalido.\n");
						break;
					}
				} while (op1 > 3 || op1 < 0);
			}
			break;

		case 2: flag = suspeito(nladrao, ladrao, casoselec, susp);
			time = time + 6;
			break;

		case 3:
			time = time + 5;
			if (flag3 == 0 && i == 0)
			{
				f = 0;//Imprime 2 paises
				printf("Selecione o pais que deseja viajar:\n");
				printf("1 - %s\n", pcaso[i + 1].paiscaso);
				printf("2 - %s\n", fcaso[f].paisforacaso);
				printf("0 - Retornar ao menu anterior.\n");
				do
				{
					scanf("%d", &op2);
					printf("\n\n");
					switch (op2)
					{
					case 1://Recebe o nome do pais em que voce está, aumenta o contador de paises do caso e aumenta o
						strcpy(paisatual, pcaso[i + 1].paiscaso);//contador de paises que não influenciam no caso
						i++;
						f++;
						flag3++;
						break;
					case 2://Recebe o nome do pais em que voce está e aumenta flag4 e flag3 para que entre no loop dos
						strcpy(paisatual, fcaso[f].paisforacaso);//paises que não influenciam o caso
						f = 0;
						flag3++;
						flag4++;
						break;
					case 0:
						time = time - 5;
						break;
					default:
						printf("Opcao invalida.\n");
					}
				} while (op2>2 || op2<0);
			}
			else
			{
				if (flag4 == 1)
				{
					printf("Selecione o pais que deseja viajar:\n");
					printf("1 - %s\n", pcaso[i].paiscaso);
					printf("2 - %s\n", fcaso[f - i + 1].paisforacaso);
					printf("0 - Retornar ao menu anterior.\n");
					do
					{
						scanf("%d", &op2);
						printf("\n\n");
						switch (op2)
						{
						case 1:
							strcpy(paisatual, pcaso[i].paiscaso);//Retorna ao país anterior
							flag4--;
							f--;
							break;
						case 2:
							strcpy(paisatual, fcaso[f - i + 1].paisforacaso);//Vai ao próximo país sem relação ao caso
							f++;
							flag4++;
							flag5 = 1;
							break;
						case 0:
							time = time - 5;
							break;
						default:
							printf("Opcao invalida.\n");

						}
					} while (op2>2 || op2<0);
					if (flag4 == 0)
						flag3 = 0;

				}
				else
				{
					if (flag5 == 1)
					{
						printf("O aeroporto desde pais esta em reformas.\n");
						printf("Por conta disto, voce soh pode retorna ao pais anterior.\n");
						printf("1 - %s\n", fcaso[f - i - 1].paisforacaso);
						printf("0 - Retornar ao menu anterior.\n");
						do
						{
							scanf("%d", &op2);
							printf("\n\n");
							switch (op2)
							{
							case 1:
								strcpy(paisatual, fcaso[f - i + 1].paisforacaso);//Retorna ao país anterior
								flag4--;
								flag5--;
								f--;
								break;
							case 0:
								time = time - 5;
								break;
							default:
								printf("Opcao invalida.\n");

							}
						} while (op2>1 || op2<0);
					}
					else
					{
						if (flag4>0)
						{
							printf("Selecione o pais que deseja viajar:\n");
							printf("1 - %s\n", fcaso[f - i].paisforacaso);
							printf("2 - %s\n", fcaso[f - i + 1].paisforacaso);
							printf("0 - Retornar ao menu anterior.\n");
							do
							{
								scanf("%d", &op2);
								printf("\n\n");
								switch (op2)
								{
								case 1:
									strcpy(paisatual, fcaso[f - i].paisforacaso);//Retorna ao país anterior
									flag4--;
									f--;
									break;
								case 2:
									strcpy(paisatual, fcaso[f - i + 1].paisforacaso);//Vai ao próximo país sem relação ao caso
									f++;
									flag4++;
									break;
								case 0:
									time = time - 5;
									break;
								default:
									printf("Opcao invalida.\n");

								}
							} while (op2>2 || op2<0);

							if (flag4 == 0)
								flag3 = 0;
							if (flag4 == 3)//Caso vá para 3 países longe do trajeto do suspeito, o jogador perderá o jogo
							{
								printf("Infelizmente voce se afastou do suspeito e ele escapou.\n");
								printf("Digite 1 e enter para voltar ao menu principal.\n");
								do
								{
									scanf("%c", &c);
								} while (c == '\n');
								return 0;
							}

						}
						else
						{
							if (i + 1 == k)//Caso não tenha continuação nos países da história do jogo
							{
								printf("Selecione o pais que deseja viajar:\n");
								printf("1 - %s\n", pcaso[i - 1].paiscaso);
								printf("2 - %s\n", fcaso[f].paisforacaso);
								printf("0 - Retornar ao menu anterior.\n");

								do
								{
									scanf("%d", &op2);
								} while (op2>2 || op2<0);
								printf("\n\n");
								if (op2 == 1)
								{//Retorna ao último país visitado
									strcpy(paisatual, pcaso[i - 1].paiscaso);
									i--;
									f--;
									if (i == 0)
										flag3 = 0;
								}
								if (op2 == 3)
								{//Avança ao próximo país que não possui importância no caso
									strcpy(paisatual, pcaso[i + 1].paiscaso);
									i++;
									f++;
								}
								if (op2 == 2)
								{//Avança ao próximo país com importância ao caso
									strcpy(paisatual, fcaso[f].paisforacaso);
									f = f + i;
									flag4 = 1;
									flag3 = 1;
								}
								if (op2 == 0)
								{//Retorna ao menu anterior
									time = time - 5;
									break;
								}
							}
							else
							{//Caso tenha ainda continuação na história do jogo
								printf("Selecione o pais que deseja viajar:\n");
								printf("1 - %s\n", pcaso[i - 1].paiscaso);
								printf("2 - %s\n", fcaso[f].paisforacaso);
								printf("3 - %s\n", pcaso[i + 1].paiscaso);
								printf("0 - Retornar ao menu anterior.\n");
								do
								{
									scanf("%d", &op2);
								} while (op2>3 || op2<0);
								printf("\n\n");
								if (op2 == 1)
								{//Retorna ao último país visitado
									strcpy(paisatual, pcaso[i - 1].paiscaso);
									i--;
									f--;
									if (i == 0)
										flag3 = 0;
								}
								if (op2 == 3)
								{//Avança ao próximo país que não possui importância no caso
									strcpy(paisatual, pcaso[i + 1].paiscaso);
									i++;
									f++;
								}
								if (op2 == 2)
								{//Avança ao próximo país com importância ao caso
									strcpy(paisatual, fcaso[f].paisforacaso);
									f = f + i;
									flag4 = 1;
									flag3 = 1;
								}
								if (op2 == 0)
								{//Retorna ao menu anterior
									time = time - 5;
									break;
								}
							}
						}
					}
				}
			}
			break;
		}

	} while (flag == 1 || flag2 != 1);


}

void leituracasos(int *ncasoslidos, char *mcasoslidos)
{
	FILE *casos;
	int j = 0;
	char *i, c;

	//Abertura do arquivo chamado casos, o qual contem uma lista de todos os casos criados, realizando sua leitura.
	casos = fopen("casos.txt", "r");

	i = mcasoslidos;
	if (casos == NULL)
	{
		printf("Erro! Entre em contato com o administrador.");
	}
	else
	{
		while (!feof(casos))
		{
			c = getc(casos);
			*mcasoslidos = c;
			mcasoslidos++;

			if (c == '\n' || c == -1)
			{
				mcasoslidos--;
				*mcasoslidos = '\0';
				i += 50;
				mcasoslidos = i;
				j++;
			}
		}
	}
	*ncasoslidos = j;

	//retorna a leitura para a matriz mcasos contida no menu.
	fclose(casos);
}

void leituraladroes(int *nladroeslidos, char *mcaso, tipocaract *mladrao)
{
	FILE *ladroes;
	int i, j, k;
	char c[50], v[60];

	strcpy(v, mcaso);
	strcat(v, "Ladrao.txt");

	//abrirá o arquivo contendo a lista de ladrões e sua características, realizando a leitura.
	ladroes = fopen(v, "r");
	if (ladroes == NULL)
	{
		printf("\nErro! Entre em contato com o administrador\n.");
	}
	else
	{
		k = 0;
		i = 0;
		j = 0;
		while (!feof(ladroes))
		{
			c[i] = getc(ladroes);
			if (c[i] == '\n' || c[i] == -1)
			{
				c[i] = '\0';
				i = 0;
				//guarda  na struct tipocaract todo o conteúdo do arquivo, separando em diferentes variáveis, de acordo com o conteudo.
				switch (j)
				{
				case 0: strcpy(mladrao->nome, c);
					break;
				case 1: strcpy(mladrao->sexo, c);
					break;
				case 2: strcpy(mladrao->acessorio, c);
					break;
				case 3: strcpy(mladrao->cabelo, c);
					break;
				case 4: strcpy(mladrao->esporte, c);
					break;
				case 5: strcpy(mladrao->carro, c);
					break;
				default: break;
				}
				j++;
				if (j == 6)
				{
					j = 0;
					mladrao++;
					k++;
				}
			}
			else
			{
				i++;
			}
		}
	}
	*nladroeslidos = k;
	fclose(ladroes);
}

void leiturapaiscaso(int *npaisclidos, char *mcaso, tipopaiscaso *mpcaso)
{
	FILE *paiscaso;
	int i, j, k;
	char c[100], v[60];

	strcpy(v, mcaso);
	strcat(v, ".txt");
	//abrirá o arquivo correspondente ao caso selecionado, o qual contém os principais paises, cidades e dicas.
	paiscaso = fopen(v, "r");

	if (paiscaso == NULL)
	{
		printf("\nErro! Entre em contato com o administrador\n.");
	}
	else
	{
		k = 0;
		i = 0;
		j = 0;
		while (!feof(paiscaso))
		{
			c[i] = getc(paiscaso);

			if (c[i] == '\n' || c[i] == -1)
			{
				c[i] = '\0';
				i = 0;
				//guarda o conteúdo do arquivo na struct tipopaiscaso, separando em diferentes variáveis de acordo com o conteúdo e linha.
				switch (j)
				{
				case 0: strcpy(mpcaso->paiscaso, c);
					break;
				case 1: strcpy(mpcaso->cidade1caso, c);
					break;
				case 2: strcpy(mpcaso->cidade2caso, c);
					break;
				case 3: strcpy(mpcaso->cidade3caso, c);
					break;
				case 4: strcpy(mpcaso->dica1caso, c);
					break;
				case 5: strcpy(mpcaso->dica2caso, c);
					break;
				case 6: strcpy(mpcaso->dica3caso, c);
					break;
				default: break;
				}
				j++;
				if (j == 7)
				{
					j = 0;
					mpcaso++;
					k++;
				}
			}
			else
			{
				i++;
			}
		}
	}
	*npaisclidos = k;

	fclose(paiscaso);
}

void leiturapaisforacaso(int *npaisflidos, char *mcaso, tipopaisforacaso *mfcaso)
{
	FILE *paisforacaso;
	int i, j, k;
	char c[50], v[60];

	strcpy(v, mcaso);
	strcat(v, "Paises.txt");

	//abrirá o arquivo de paises fora do caso escolhido, correnspondente aos paises que estariam errados.
	paisforacaso = fopen(v, "r");
	if (paisforacaso == NULL)
	{
		printf("\nErro! Entre em contato com o administrador\n.");
	}
	else
	{
		k = 0;
		i = 0;
		j = 0;
		while (!feof(paisforacaso))
		{
			c[i] = getc(paisforacaso);
			if (c[i] == '\n' || c[i] == -1)
			{
				c[i] = '\0';
				i = 0;
				//guarda o conteúdo na struct tipopaisforacaso, separando o conteúdo em difentes variáveis.
				switch (j)
				{
				case 0: strcpy(mfcaso->paisforacaso, c);
					break;
				case 1: strcpy(mfcaso->cidade1foracaso, c);
					break;
				case 2: strcpy(mfcaso->cidade2foracaso, c);
					break;
				case 3: strcpy(mfcaso->cidade3foracaso, c);
					break;
				default: break;
				}
				j++;
				if (j == 4)
				{
					j = 0;
					mfcaso++;
					k++;
				}
				//	printf("%s\n", c);	      	
			}
			else
			{
				i++;
			}
		}
		*npaisflidos = k;
		fclose(paisforacaso);
	}
}

int tempo(int time)
{
	int tempo = 24, resto, resultado;
	resto = time % 24;
	if (time < 161)
	{

		if (resto > 21 || resto<4)//Se acima de 21horas, o usuario dorme por 8horas
		{
			resultado = time / 24;
			switch (resultado)//Imprimir o dia e as horas em que o jogador está
			{
			case 0:
			{
				printf("Segunda-feira %i horas\n", resto);
				break;
			}
			case 1:
			{
				printf("Terca-feira %i horas\n", resto);
				break;
			}
			case 2:
			{
				printf("Quarta-feira %i horas\n", resto);
				break;
			}
			case 3:
			{
				printf("Quinta-feira %i horas\n", resto);
				break;
			}
			case 4:
			{
				printf("Sexta-feira %i horas\n", resto);
				break;
			}
			case 5:
			{
				printf("Sabado %i horas\n", resto);
				break;
			}
			case 6:
			{
				printf("Domingo %i horas\n", resto);
				break;
			}
			}
			printf("Voce foi dormir.\n");
			time = time + 8;
			resto = time % 24;
			resultado = time / 24;
			switch (resultado)//Imprimir o dia e as horas em que o jogador está
			{
			case 0:
			{
				printf("Segunda-feira %i horas\n", resto);
				break;
			}
			case 1:
			{
				printf("Terca-feira %i horas\n", resto);
				break;
			}
			case 2:
			{
				printf("Quarta-feira %i horas\n", resto);
				break;
			}
			case 3:
			{
				printf("Quinta-feira %i horas\n", resto);
				break;
			}
			case 4:
			{
				printf("Sexta-feira %i horas\n", resto);
				break;
			}
			case 5:
			{
				printf("Sabado %i horas\n", resto);
				break;
			}
			case 6:
			{
				printf("Domingo %i horas\n", resto);
				break;
			}
			}

			return 3;
		}
		else
		{
			resultado = time / 24;
			switch (resultado)//Imprimir o dia e as horas em que o jogador está
			{
			case 0:
			{
				printf("Segunda-feira %i horas\n", resto);
				break;
			}
			case 1:
			{
				printf("Terca-feira %i horas\n", resto);
				break;
			}
			case 2:
			{
				printf("Quarta-feira %i horas\n", resto);
				break;
			}
			case 3:
			{
				printf("Quinta-feira %i horas\n", resto);
				break;
			}
			case 4:
			{
				printf("Sexta-feira %i horas\n", resto);
				break;
			}
			case 5:
			{
				printf("Sabado %i horas\n", resto);
				break;
			}
			case 6:
			{
				printf("Domingo %i horas\n", resto);
				break;
			}
			}
			return 0;
		}
	}
	else
	{//Mensagem caso o jogador passe do tempo máximo do jogo
		printf("Infelizmente o tempo passou e voce nao conseguiu capturar o ladrao.\n");
		return 1;
	}
}

int suspeito(int *nladrao, tipocaract *mladrao, char *casoselec, tiposuspeito *susp)
{

	int il = 0, jl = 0, opcao, count = 0, vet[50], i, vet2[50], j, vet3[50], k, vet4[50], l = 0, kl = 1;
	char v[50];

	k = *nladrao;
	do
	{
		printf("Voce escolheu identificacao dos suspeitos.\n");
		printf("Qual eh o sexo?\n");
		printf("1 - Masculino.\n");
		printf("2 - Feminino.\n");
		printf("0 - Nao modificar/Ainda nao descoberto.\n");
		scanf("%i", &opcao);
		switch (opcao)
		{
		case 1:
		{
			count = 1;
			strcpy(susp->sexo, "masculino");
			break;
		}
		case 2:
		{
			count = 1;
			strcpy(susp->sexo, "feminino");
			break;
		}
		case 0:
		{
			if (susp->guardar == 0)
			{
				strcpy(susp->sexo, " ");
				count = 1;
				break;
			}
			else
			{
				count = 1;
				break;
			}
		}
		default:
		{
			printf("Opcao invalida.\n");
			break;
		}
		}
	} while (count != 1);
	for (il = 0; il<k; il++)
	{
		if (strcmp(susp->sexo, mladrao[il].sexo) == 0 || strcmp(susp->sexo, " ") == 0)
			printf("%s\n", mladrao[il].nome);
	}
	count = 0;
	do
	{
		printf("Qual eh a cor do cabelo do suspeito?\n");
		printf("1 - Cabelo loiro.\n");
		printf("2 - Cabelo ruivo.\n");
		printf("3 - Cabelo preto.\n");
		printf("0 - Nao modificar/Ainda nao descoberto.\n");
		scanf("%i", &opcao);
		switch (opcao)
		{
		case 1:
		{
			count = 1;
			strcpy(susp->cabelo, "cabelo loiro");
			break;
		}
		case 2:
		{
			count = 1;
			strcpy(susp->cabelo, "cabelo ruivo");
			break;
		}
		case 3:
		{
			count = 1;
			strcpy(susp->cabelo, "cabelo preto");
			break;
		}
		case 0:
		{
			if (susp->guardar == 0)
			{
				strcpy(susp->cabelo, " ");
				count = 1;
				break;
			}
			else
			{
				count = 1;
				break;
			}
		}
		default:
		{
			printf("Opcao invalida.\n");
			break;
		}
		}
	} while (count != 1);
	i = 0;
	for (il = 0; il<k; il++)
	{
		if ((strcmp(susp->cabelo, mladrao[il].cabelo) == 0 || (strcmp(susp->cabelo, " ") == 0)) && (strcmp(susp->sexo, mladrao[il].sexo) == 0))
		{
			printf("%s\n", mladrao[il].nome);
			vet[i] = il;
			i++;
		}
	}
	count = 0;
	do
	{
		printf("Qual eh o esporte que o suspeito pratica?\n");
		printf("1 - Curling.\n");
		printf("2 - Boxe.\n");
		printf("3 - Poker.\n");
		printf("0 - Nao modificar/Ainda nao descoberto.\n");
		scanf("%i", &opcao);
		switch (opcao)
		{
		case 1:
		{
			count = 1;
			strcpy(susp->esporte, "curling");
			break;
		}
		case 2:
		{
			count = 1;
			strcpy(susp->esporte, "boxe");
			break;
		}
		case 3:
		{
			count = 1;
			strcpy(susp->esporte, "poker");
			break;
		}
		case 0:
		{
			if (susp->guardar == 0)
			{
				strcpy(susp->esporte, " ");
				count = 1;
				break;
			}
			else
			{
				count = 1;
				break;
			}
		}
		default:
		{
			printf("Opcao invalida.\n");
			break;
		}
		}
	} while (count != 1);
	j = 0;
	count = 0;
	while (count < i)
	{
		if (strcmp(susp->esporte, mladrao[vet[count]].esporte) == 0 || (strcmp(susp->esporte, " ") == 0))
		{
			printf("%s\n", mladrao[vet[count]].nome);
			vet2[j] = vet[count];
			j++;
		}
		count++;
	}
	count = 0;
	do
	{
		printf("Qual eh o carro o suspeito possui?\n");
		printf("1 - Fusca.\n");
		printf("2 - Tuqui tuqui.\n");
		printf("3 - Gol.\n");
		printf("0 - Nao modificar/Ainda nao descoberto.\n");
		scanf("%i", &opcao);
		switch (opcao)
		{
		case 1:
		{
			count = 1;
			strcpy(susp->carro, "fusca");
			break;
		}
		case 2:
		{
			count = 1;
			strcpy(susp->carro, "tuqui tuqui");
			break;
		}
		case 3:
		{
			count = 1;
			strcpy(susp->carro, "gol");
			break;
		}
		case 0:
		{
			if (susp->guardar == 0)
			{
				strcpy(susp->carro, " ");
				count = 1;
				break;
			}
			else
			{
				count = 1;
				break;
			}
		}
		default:
		{
			printf("Opcao invalida.\n");
			break;
		}
		}
	} while (count != 1);
	k = 0;
	count = 0;
	while (count < j)
	{
		if (strcmp(susp->carro, mladrao[vet2[count]].carro) == 0 || (strcmp(susp->carro, " ") == 0))
		{
			printf("%s\n", mladrao[vet2[count]].nome);
			vet3[k] = vet2[count];
			k++;
		}
		count++;
	}

	count = 0;
	do
	{
		printf("Qual eh o acessorio do suspeito?\n");
		printf("1 - Tapaolho.\n");
		printf("2 - Dente de Ouro.\n");
		printf("3 - Spinner.\n");
		printf("0 - Nao modificar/Ainda nao descoberto.\n");
		scanf("%i", &opcao);
		switch (opcao)
		{
		case 1:
		{
			count = 1;
			strcpy(susp->acessorio, "tapaolho");
			break;
		}
		case 2:
		{
			count = 1;
			strcpy(susp->acessorio, "dente de ouro");
			break;
		}
		case 3:
		{
			count = 1;
			strcpy(susp->acessorio, "spinner");
			break;
		}
		case 0:
		{
			if (susp->guardar == 0)
			{
				strcpy(susp->acessorio, " ");
				count = 1;
				break;
			}
			else
			{
				count = 1;
				break;
			}
		}
		default:
		{
			printf("Opcao invalida.\n");
			break;
		}
		}
	} while (count != 1);
	l = 0;
	count = 0;
	while (count < k)
	{
		if (strcmp(susp->acessorio, mladrao[vet3[count]].acessorio) == 0 || (strcmp(susp->acessorio, " ") == 0))
		{
			printf("%s\n", mladrao[vet3[count]].nome);
			vet4[l] = vet3[count];
			l++;
		}
		count++;
	}

	susp->guardar = kl;
	if (l == 1)
	{
		printf("\n\nO suspeito identificado foi:\n%s\n", mladrao[vet4[0]].nome);
		if (strcmp(mladrao[0].nome, mladrao[vet4[0]].nome) == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}
}

void alterarnomes()
{
	FILE*ranking;
	char salvarrank[100][100], c, nome[20], limpar[20] = { "                   " };
	int count = 0, count2 = 0, i, menu = 1, num, j, flag = 0;
	system("cls");
	printf("Voce escolheu alterar nome dos jogadores.\n");
	if (!(ranking = fopen("ranking.txt", "r")))
	{
		printf("Erro! Impossivel abrir o arquivo.\n");
	}
	else
	{
		while (!feof(ranking))
		{
			c = fgetc(ranking);//Recebendo o ranking do arquivo
			if (c == ';')
				break;
			salvarrank[count2][count] = c;
			count++;
			if (c == '\n')
			{
				count = 0;
				count2++;
			}
		}
		salvarrank[count2][count] = ';';
		salvarrank[count2][count + 1] = '\0';
		printf("A lista atual de jogadores eh esta:\n\n\n");
		for (i = 0; i <= count2; i++)//Imprimindo os nomes do ranking
		{
			for (j = 0; j<23; j++)
			{
				if (salvarrank[i][j] == ';')
					break;
				printf("%c", salvarrank[i][j]);
			}
			printf("\n");
		}
		fclose(ranking);
		do
		{
			strcpy(nome, limpar);
			i = 0;
			printf("\nEscolha uma das opcoes abaixo:\n");
			printf("1 - Alterar algum nome.\n");
			printf("2 - Reler a lista de nomes.\n");
			printf("0 - Sair do menu.\n");
			scanf("%i", &menu);
			switch (menu)
			{
			case 1:
			{
				ranking = fopen("ranking.txt", "w+");
				printf("Digite o numero que deseja substituir o nome.\n");
				do
				{
					scanf("%i", &num);
					if (num<0 || num>count2 + 1)
						printf("Numero invalido, digite outro numero.\n");
				} while (num<0 || num>count2 + 1);
				printf("Digite o nome desejado(com menos de 20 caracteres):\n");
				scanf("%s", &nome);
				i = 0;
				num--;
				count = 3;
				while (count<23)//Substituindo a linha do nome desejado pelo nome escrito
				{

					salvarrank[num][count] = nome[i];
					count++;
					i++;
				}
				for (i = 0; i <= count2; i++)//Imprimindo no arquivo o ranking com o nome modificado
				{
					for (j = 0; j<43; j++)
					{
						fputc(salvarrank[i][j], ranking);
					}
				}
				fclose(ranking);
				flag = 1;
				break;
			}
			case 2:
			{
				ranking = fopen("ranking.txt", "r");//Imprimindo os nomes do ranking
				count2 = 0;
				count = 0;
				while (!feof(ranking))
				{
					c = fgetc(ranking);
					if (c == ';')
						break;
					salvarrank[count2][count] = c;
					count++;
					if (c == '\n')
					{
						count = 0;
						count2++;
					}

				}
				salvarrank[count2][count] = ';';
				salvarrank[count2][count + 1] = '\0';
				for (i = 0; i <= count2; i++)
				{
					for (j = 0; j<23; j++)
					{
						if (salvarrank[i][j] == ';')
							break;
						printf("%c", salvarrank[i][j]);
					}
					printf("\n");
				}
				fclose(ranking);
				flag = 1;

			}
			case 0:
			{
				printf("\nVoce selecionou sair deste menu.\n");
				if (flag == 0)
				{
					for (i = 0; i <= count2; i++)
					{
						for (j = 0; j<43; j++)
						{
							fputc(salvarrank[i][j], ranking);
						}
					}
					fclose(ranking);
				}
				break;
			}
			default:
			{
				printf("\nOpcao invalida.\n");
				break;
			}
			}

		} while (menu != 0);
	}
}
void top5()
{
	FILE*ranking;
	char salvarrank[100][100] = { "0" }, c = '0', nome[20] = { "0" }, limpar[20] = { "                  " };
	int count = 0, count2 = 0, i, menu = 1, num = 0, j = 0, flag = 0, linha[100] = { 0 }, keep = 0;
	long long int valor[100] = { 0 }, bubble = 0;
	if (!(ranking = fopen("ranking.txt", "r")))
	{
		printf("Erro! Impossivel abrir o arquivo.\n");
	}
	else
	{
		while (!feof(ranking))
		{
			c = fgetc(ranking);
			if (c == ';')
				break;
			salvarrank[count2][count] = c;
			count++;
			if (c == '\n')
			{
				count = 0;
				count2++;
			}

		}
		salvarrank[count2][count] = ';';
		salvarrank[count2][count + 1] = '\0';
		fclose(ranking);
		for (i = 0; i <= count2; i++)
		{
			for (j = 23; j<33; j++)
			{
				if (salvarrank[i][j] == ' ')
					break;
				valor[i] = valor[i] * 10;
				valor[i] = salvarrank[i][j] - 48 + valor[i];
			}
		}

		for (i = 0; i<100; i++)
			linha[i] = i;
		for (i = 0; i <= count2; i++)
		{
			for (j = 0; j <= count2; j++)
			{
				if (valor[i]<valor[i + 1])
				{
					bubble = valor[i + 1];
					valor[i + 1] = valor[i];
					valor[i] = bubble;
					bubble = linha[i + 1];
					linha[i + 1] = linha[i];
					linha[i] = bubble;
					i = 0;
					j = 0;
				}
			}
		}
		printf("Posicao     Nome do jogador               ranking\n");
		for (i = 0; i <= 4; i++)
		{
			printf("%i -         ", i + 1);
			for (count = 3; count<42; count++)
			{
				keep = linha[i];
				printf("%c", salvarrank[keep][count]);
			}
			printf("\n");
		}
	}
}

void rankingporpontos()
{
	FILE*ranking;
	char salvarrank[100][100] = { "0" }, c = '0', nome[20] = { "0" }, limpar[20] = { "                  " };
	int count = 0, count2 = 0, i, menu = 1, num = 0, j = 0, flag = 0, linha[100] = { 0 }, keep = 0;
	long long int valor[100] = { 0 }, bubble = 0;
	if (!(ranking = fopen("ranking.txt", "r")))
	{
		printf("Erro! Impossivel abrir o arquivo.\n");
	}
	else
	{
		while (!feof(ranking))
		{
			c = fgetc(ranking);
			if (c == ';')
				break;
			salvarrank[count2][count] = c;
			count++;
			if (c == '\n')
			{
				count = 0;
				count2++;
			}

		}
		salvarrank[count2][count] = ';';
		salvarrank[count2][count + 1] = '\0';
		fclose(ranking);
		for (i = 0; i <= count2; i++)
		{
			for (j = 23; j<33; j++)
			{
				if (salvarrank[i][j] == ' ')
					break;
				valor[i] = valor[i] * 10;
				valor[i] = salvarrank[i][j] - 48 + valor[i];
			}
		}

		for (i = 0; i<100; i++)
			linha[i] = i;
		for (i = 0; i <= count2; i++)
		{
			for (j = 0; j <= count2; j++)
			{
				if (valor[i]<valor[i + 1])
				{
					bubble = valor[i + 1];
					valor[i + 1] = valor[i];
					valor[i] = bubble;
					bubble = linha[i + 1];
					linha[i + 1] = linha[i];
					linha[i] = bubble;
					i = 0;
					j = 0;
				}
			}
		}
		printf("Posicao      Nome do jogador               ranking\n");
		for (i = 0; i <= count2; i++)
		{
			if (i<9)
				printf("0");
			printf("%i -         ", i + 1);
			for (count = 3; count<42; count++)
			{
				keep = linha[i];
				printf("%c", salvarrank[keep][count]);
			}
			printf("\n");
		}
	}
}

void rankingporpatente()
{
	FILE*ranking;
	char salvarrank[100][100], c, nome[20], limpar[20] = { "                  " };
	int count = 0, count2 = 0, i, menu = 1, num, j, flag = 0, linha[100], keep;
	long long int valor[100], bubble;
	if (!(ranking = fopen("ranking.txt", "r")))
	{
		printf("Erro! Impossivel abrir o arquivo.\n");
	}
	else
	{
		while (!feof(ranking))//Recebendo os valores no arquivo do ranking
		{
			c = fgetc(ranking);
			if (c == ';')
				break;
			salvarrank[count2][count] = c;
			count++;
			if (c == '\n')
			{
				count = 0;
				count2++;
			}

		}
		salvarrank[count2][count] = ';';
		salvarrank[count2][count + 1] = '\0';
		fclose(ranking);
		for (i = 0; i <= count2; i++)
		{
			for (j = 41; j<42; j++)
			{
				if (salvarrank[i][j] == ' ')
					break;
				valor[i] = salvarrank[i][j] - 48;;
			}
		}

		for (i = 0; i<100; i++)
			linha[i] = i;
		for (i = 0; i <= count2; i++)//Realizando uma troca para o ranking ficar na ordem desejada
		{
			for (j = 0; j <= count2; j++)
			{
				if (valor[i]<valor[i + 1])
				{
					bubble = valor[i + 1];
					valor[i + 1] = valor[i];
					valor[i] = bubble;
					bubble = linha[i + 1];
					linha[i + 1] = linha[i];
					linha[i] = bubble;
					i = 0;
					j = 0;
				}
			}
		}//Imprimindo o ranking
		printf("Posicao      Nome do jogador               ranking\n");
		for (i = 0; i <= count2; i++)
		{
			if (i<9)
				printf("0");
			printf("%i -         ", i + 1);
			for (count = 3; count<42; count++)
			{
				keep = linha[i];
				printf("%c", salvarrank[keep][count]);
			}
			printf("\n");
		}
	}
}





int checaradm()
{
	char letra[20], admincripted[20], admin[20], senhacripted[20], senha[20], administradorreal[21], senhareal[21], c;
	int  i, j = 0, aux1, aux2, k = 0, loc = 19, tamadm = 0, tamsen = 0, count = 0, flag = 0;



	FILE *criptografia;
	criptografia = fopen("adm.txt", "r");
	printf("Digite seu login:\n");
	scanf("%s", admin);
	printf("Digite sua senha:\n");
	scanf("%s", senha);





	//USER------------------------------------------------------


	tamadm = strlen(admin);//Criptografando o login digitado pelo usuário
	aux2 = tamadm - 1;
	for (i = 0; i < tamadm; i++)
	{
		admincripted[aux2] = admin[i];
		aux2--;
	}
	admincripted[tamadm] = '\0';


	//SENHA------------------------------------------------------



	tamsen = strlen(senha);
	aux1 = tamsen - 1;
	for (k = 0; k < tamsen; k++)//Criptografando a senha digitada pelo usuário
	{
		senhacripted[aux1] = senha[k];
		aux1--;
	}
	senhacripted[tamsen] = '\0';

	i = 0;
	count = 0;
	while (!feof(criptografia))//Recebendo os valores escritos no arquivo
	{
		c = fgetc(criptografia);
		if (c == '\n')
		{
			if (count == 0)
			{
				administradorreal[i] = '\0';
			}
			if (count == 1)
				senhareal[i] = '\0';
			i = 0;
			count++;
		}
		if (count == 0 && c != '\n')
		{
			administradorreal[i] = c;
			i++;
		}
		if (count == 1 && c != '\n')
		{
			senhareal[i] = c;
			i++;
		}
	}

	fclose(criptografia);//Comparando se o login e a senha criptografados estão iguais

	if (strcmp(administradorreal, admincripted) == 0 && strcmp(senhareal, senhacripted) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void trocarloginadm()
{
	FILE*adm;
	char c, senha[20], login[20], logincripto[20];
	int count = 0, count2 = 0, tamadm, aux;
	adm = fopen("adm.txt", "r");
	if (adm == NULL)
		printf("Erro! Entre em contato com o administrador.\n");
	else
	{
		while (!feof(adm))//Salvando a senha do administrador
		{
			c = getc(adm);
			if (count == 1)
			{
				senha[count2] = c;
				count2++;
			}
			if (c == '\n')
				count++;
		}
		senha[count2 - 1] = '\0';
		fclose(adm);
		printf("Digite o novo login do administrador.\n");
		scanf("%s", login);
		tamadm = strlen(login);
		aux = tamadm - 1;
		for (count = 0; count < tamadm; count++)//Criptografando o novo login do administrador
		{
			logincripto[aux] = login[count];
			aux--;
		}
		logincripto[tamadm] = '\0';
		adm = fopen("adm.txt", "w");
		for (count = 0; logincripto[count]; count++)//Imprimindo no arquivo o novo login do administrador
		{
			fputc(logincripto[count], adm);
		}
		fputc('\n', adm);
		for (count = 0; senha[count]; count++)
		{
			fputc(senha[count], adm);
		}
		fputc('\n', adm);
		fclose(adm);
	}
}

void trocarsenhaadm()
{
	FILE*adm;
	char c, login[20], senha[20], senhacripto[20];
	int count = 0, count2 = 0, tamadm, aux;
	adm = fopen("adm.txt", "r");
	if (adm == NULL)
		printf("Erro! Entre em contato com o administrador.\n");
	else
	{
		while (!feof(adm))//Salvando o login do adm
		{
			c = getc(adm);
			if (count == 0)
			{
				login[count2] = c;
				count2++;
			}
			if (c == '\n')
				count++;
		}
		login[count2 - 1] = '\0';
		fclose(adm);
		printf("Digite a nova senha do administrador.\n");
		scanf("%s", senha);
		tamadm = strlen(senha);
		aux = tamadm - 1;
		for (count = 0; count < tamadm; count++)//Criptografando a senha do administrador
		{
			senhacripto[aux] = senha[count];
			aux--;
		}
		senhacripto[tamadm] = '\0';
		adm = fopen("adm.txt", "w");
		for (count = 0; login[count]; count++)//Imprimindo no arquivo o login e a nova senha do administrador
		{
			fputc(login[count], adm);
		}
		fputc('\n', adm);
		for (count = 0; senhacripto[count]; count++)
		{
			fputc(senhacripto[count], adm);
		}
		fputc('\n', adm);
		fclose(adm);
	}
}

void addcasos()
{
	char casoadicionar[30], casolvl[2], adicionadoroubo[30], adicionado[30], adicionadocaso[30], adicionadoladrao[30], adicionadopais[30], cidades[200][200], letra = 'a', resp, roubo[100][100];

	int c = 1, j, i, linha = 0, coluna = 0, entry = 0;

	FILE *casos;
	casos = fopen("Casos.txt", "a+");
	if (casos == NULL)
	{
		printf("Erro! Entre em contato com o administrador !");
	}
	else
	{
		printf("Digite o nome do caso que deseja adicionar !\n");
		scanf("%s", casoadicionar);

		printf("Entre com a dificuldade do caso que deseja adicionar !\n");
		scanf("%s", &casolvl);

		fprintf(casos, "\n%s", &casoadicionar);

		fprintf(casos, "%s", &casolvl);
	}
	fclose(casos);


	strcpy(adicionado, casoadicionar);//Adicionando o nome do caso a ser criado
	strcpy(adicionadoroubo, casoadicionar);
	strcpy(adicionadopais, casoadicionar);
	strcpy(adicionadoladrao, casoadicionar);
	strcat(adicionado, ".txt");
	strcat(adicionadoroubo, "Roubo.txt");
	strcat(adicionadopais, "Paises.txt");
	strcat(adicionadoladrao, "Ladrao.txt");


	//------------------------------------------------------CONF

	FILE *adicionaroubo;
	adicionaroubo = fopen(adicionadoroubo, "w");

	printf("Informe o que foi roubado pela terrivel gangue !\n(DIGITE 0 PARA ENCERRAR)\n");
	fflush(stdin);
	do
	{
		scanf("%c", &letra);
	} while (letra == '\n');
	fputc(letra, adicionaroubo);
	do
	{

		scanf("%c", &letra);
		if (letra == '0')
			break;
		fputc(letra, adicionaroubo);

	} while (letra != '0');

	printf("Salvo !\n");

	fclose(adicionaroubo);

	//-------------------------------------------------------

	FILE *casoadicionado;
	casoadicionado = fopen(adicionado, "w");

	casoadicionar[strlen(casoadicionar) + 1] = '\0';
	fprintf(casoadicionado, "%s", &casoadicionar);



	do
	{
		if (c == 1)
		{
			if (entry == 0)
			{
				printf("Acontecimentos do roubo !\n");
				printf("Adicione 1 pais\nAdicione 3 cidades\nAdicione 3 pistas\n(DIGITE 0 PARA ENCERRAR)\n");
				printf("Nao eh necessario reescrever o nome do pais no qual o caso comecou.\n");
				//Escrevendo dentro do caso 1 pais 3 cidades e as pistas referente aos acontecimentod do roubo
				fflush(stdin);
				fputc('\n', casoadicionado);
				do
				{
					scanf("%c", &letra);
				} while (letra == '\n');
				fputc(letra, casoadicionado);
				do
				{
					scanf("%c", &letra);
					if (letra == '0')
						break;
					fputc(letra, casoadicionado);
				} while (letra != '0');
			}

			if (c == 1)
			{
				printf("Deseja adicionar outra cidade para o jogo ? \nS-SIM\nN-NAO\nResposta:");
				//Checar se quer adicionar novas informações ou não
				fflush(stdin);

				do
					scanf("%c", &resp);
				while (resp == '\n');

				if (resp == 'S')
				{
					c = 1;
				}
				else if (resp == 'N')
				{
					c = 0;
					printf("Caso Salvo !\n");

				}
				else
				{
					printf("Opcao Invalida !\n");
					c == 1;
					entry = 1;
				}
			}

		}

	} while (c == 1);

	fclose(casoadicionado);

	//---------------------------------------------------------------------------

	FILE *adicionarpais;
	adicionarpais = fopen(adicionadopais, "w");

	printf("Adicione uma lista contendo primeiro 1 pais e depois 3 cidades(DIGITE 0 PARA ENCERRAR)\n");//Paises para viajar
	printf("Pode ser adicionado quantos paises ou cidades quiser utilizando esta formatacao.\n");
	fflush(stdin);
	do
	{
		scanf("%c", &letra);
	} while (letra == '\n');
	fputc(letra, adicionarpais);
	do
	{

		scanf("%c", &letra);
		if (letra == '0')
			break;
		fputc(letra, adicionarpais);

	} while (letra != '0');
	printf("Salvo !\n");

	fclose(adicionarpais);

	//-----------------------------------------------------------------------------

	FILE *adicionarladrao;
	adicionarladrao = fopen(adicionadoladrao, "w");

	printf("Adicione os ladroes que estao relacioandos com o caso:\n");
	printf("Primeiro o ladrao principal e depois quantos ladroes secundarios quiser(DIGITE 0 PARA ENCERRAR).\n");
	printf("A ordem dos dados sao:\n1 - Nome do criminoso\n");
	printf("2 - sexo\n3 - acessorio\n4 - cor do cabelo\n5 - esporte praticado\n6 - carro\n");
	fflush(stdin);
	do
	{
		scanf("%c", &letra);
	} while (letra == '\n');
	fputc(letra, adicionarladrao);
	do
	{
		scanf("%c", &letra);
		if (letra == '0')
			break;
		fputc(letra, adicionarladrao);

	} while (letra != '0');

	printf("Salvo !");

	fclose(adicionarladrao);

}

void colocarnoranking(int pontos, int rank, char nome[])
{
	FILE*ranking;
	char salvarrank[100][100], c, nomeplayer[20], linha[100], num[20], copy[50];
	int count = 0, count2 = 0, count3, menu = 1, count4, tam, tamanhonum = 0, k = 0, var, i = 0, numcasas = 0;
	int sub;
	rank = rank - 48;
	if (!(ranking = fopen("ranking.txt", "r")))
	{
		printf("Erro! Impossivel abrir o arquivo.\n");
	}
	else
	{
		while (!feof(ranking))
		{
			c = fgetc(ranking);
			if (c == ';')
				break;
			salvarrank[count2][count] = c;
			count++;
			if (c == '\n')
			{
				count = 0;
				count2++;
			}

		}
		salvarrank[count2][count] = '\n';
		salvarrank[count2][count + 1] = '\0';
		fclose(ranking);
		strcpy(nomeplayer, nome);
		tam = strlen(nome);
		for (count3 = tam; count3<20; count3++)
			nomeplayer[count3] = ' ';
		nomeplayer[19] = '\0';
		numcasas = pontos;
		while (numcasas>0)
		{
			numcasas = numcasas / 10;
			tamanhonum++;
		}
		var = tamanhonum;
		for (count3 = 0; count3<tamanhonum; count3++)
		{
			k = pontos / (pow(10, var - count3 - 1));
			sub = k*pow(10, var - count3 - 1);
			pontos = pontos - sub;
			num[count3] = k + 48;;
		}
		num[count3] = '\0';
		tamanhonum = strlen(num);
		num[10] = '\0';
		for (count3 = tamanhonum; count3<10; count3++)
		{
			num[count3] = ' ';
		}
		strcpy(copy, salvarrank[count2]);
		copy[23] = '\0';
		for (i = 0; i<21; i++)
		{
			copy[i] = copy[i + 3];
		}
		copy[20] = '\0';
		ranking = fopen("ranking.txt", "w");
		if (strcmp(copy, nomeplayer) == 0)
		{
			if (count2<9)
				sprintf(linha, "0%i-%s %sranking %i;", count2 + 1, nomeplayer, num, rank);
			else
				sprintf(linha, "%i-%s %sranking %i;", count2 + 1, nomeplayer, num, rank);
			strcpy(salvarrank[count2], "oi");
			strcpy(salvarrank[count2], linha);
			for (count3 = 0; count3<count2 + 1; count3++)
			{
				for (count4 = 0; count4<43; count4++)
				{
					fputc(salvarrank[count3][count4], ranking);
				}
			}
		}
		else
		{
			if (count2<8)
				sprintf(linha, "0%i-%s %sranking %i;", count2 + 2, nomeplayer, num, rank);
			else
				sprintf(linha, "%i-%s %sranking %i;", count2 + 2, nomeplayer, num, rank);
			strcpy(salvarrank[count2 + 1], linha);
			for (count3 = 0; count3<count2 + 2; count3++)
			{
				for (count4 = 0; count4<43; count4++)
				{
					fputc(salvarrank[count3][count4], ranking);
				}
			}
		}
		fclose(ranking);
	}
}
