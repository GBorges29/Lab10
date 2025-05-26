#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "input.h"
#include "map.h" 
#include "stringWrap.h"

void showMenu() {
    printf("\n--- Sistema de Votação ---\n");
    printf("1. Abrir nova votação\n");
    printf("2. Registar voto\n");
    printf("3. Fechar votação\n");
    printf("4. Listar candidatos (ordem alfabética)\n");
    printf("5. Apresentar vencedor\n");
    printf("6. Resultados por número de votos\n");
    printf("0. Sair\n");
    printf("\nOpção: ");
}

int main() {
    int menuOption;
    bool votingIsOpen = false; /* Votação aberta? */
    PtMap voting = mapCreate(); /* Contém candidatos e votos associados */

    if(voting == NULL) {
        printf("[ERRO] Não foi possível iniciar o programa. Não existe memória disponível.\n");
        return EXIT_FAILURE;
    }

    do {
        showMenu();
        readInteger(&menuOption);

        if (menuOption == 1) {
            if(votingIsOpen) {
                printf("[ERRO] Já existe uma votação em aberto.\n");
                continue;
            }

            if (voting != NULL) {
                mapClear(voting);
            }

            printf("Registo de candidatos ->\n");
            char nome[100];
            do {
                printf("Nome (ENTER para terminar)?: ");
                readString(nome, 100);

                if (strlen(nome) == 0) break;

                StringWrap candidato = stringWrapCreate(nome);
                if (!mapContains(voting, candidato)) {
                    mapPut(voting, candidato, 0);
                }
            } while(strlen(nome) != 0);

            int size;
            mapSize(voting, &size);
            if(size == 0) {
                printf("[ERRO] Não é possível abrir uma votação sem candidatos.\n");
            } else {
                votingIsOpen = true;
                printf("[INFO] Nova votação iniciada com %d candidatos.\n", size);
            }

        } else if (menuOption == 2) {
            if (!votingIsOpen) {
                printf("[ERRO] A votação está encerrada. Não é possível registar mais votos.\n");
                continue;
            } else {
                char nome[100];
                printf("Nome do candidato: ");
                readString(nome, 100);
                StringWrap candidato = stringWrapCreate(nome);

                int votos;
                if (mapGet(voting, candidato, &votos) == MAP_OK) {
                    mapPut(voting, candidato, votos + 1);
                    printf("[VOTO REGISTADO]\n");
                } else {
                    printf("[CANDIDATO INEXISTENTE]\n");
                }
            }

        } else if (menuOption == 3) {
            if (!votingIsOpen) {
                printf("[ERRO] A votação já está encerrada.\n");
            } else {
                votingIsOpen = false;
                printf("[INFO] Votação encerrada.\n");
            }

        } else if (menuOption == 4) {
            if (mapIsEmpty(voting)) {
                printf("[INFO] Nenhum candidato registado.\n");
            } else {
                int size;
                mapSize(voting, &size);
                MapKey* keys = mapKeys(voting);
                // Ordenar alfabeticamente
                for (int i = 0; i < size - 1; i++) {
                    for (int j = i + 1; j < size; j++) {
                        if (mapKeyCompare(keys[i], keys[j]) > 0) {
                            MapKey temp = keys[i];
                            keys[i] = keys[j];
                            keys[j] = temp;
                        }
                    }
                }

                printf("Candidatos:\n");
                for (int i = 0; i < size; i++) {
                    printf("- ");
                    mapKeyPrint(keys[i]);
                    printf("\n");
                }
                free(keys);
            }

        } else if (menuOption == 5) {
            if (mapIsEmpty(voting)) {
                printf("[INFO] Nenhum candidato registado.\n");
            } else {
                int size;
                mapSize(voting, &size);
                MapKey* keys = mapKeys(voting);
                MapKey vencedor = keys[0];
                int maxVotos = -1;

                for (int i = 0; i < size; i++) {
                    int votos;
                    mapGet(voting, keys[i], &votos);
                    if (votos > maxVotos) {
                        maxVotos = votos;
                        vencedor = keys[i];
                    }
                }
                printf("Vencedor: ");
                mapKeyPrint(vencedor);
                printf("\n");
                free(keys);
            }

        } else if (menuOption == 6) {
            if (mapIsEmpty(voting)) {
                printf("[INFO] Nenhum candidato registado.\n");
            } else {
                int size;
                mapSize(voting, &size);
                MapKey* keys = mapKeys(voting);
                MapValue* votos = mapValues(voting);

                // Ordenar por número de votos (descendente)
                for (int i = 0; i < size - 1; i++) {
                    for (int j = i + 1; j < size; j++) {
                        if (votos[i] < votos[j]) {
                            MapValue tmpV = votos[i]; votos[i] = votos[j]; votos[j] = tmpV;
                            MapKey tmpK = keys[i]; keys[i] = keys[j]; keys[j] = tmpK;
                        }
                    }
                }

                printf("Resultados:\n");
                for (int i = 0; i < size; i++) {
                    printf("%dº ", i + 1);
                    mapKeyPrint(keys[i]);
                    printf(" - %d votos\n", votos[i]);
                }
                free(keys);
                free(votos);
            }

        } else if (menuOption == 0) {
            printf("[PROGRAMA TERMINADO]\n");

        } else {
            printf("[ERRO] Opção inválida.\n");
        }

    } while (menuOption != 0);

    mapDestroy(&voting);

    return EXIT_SUCCESS;
}
