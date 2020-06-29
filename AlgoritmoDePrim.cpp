# include <iostream>
# include <stdio.h>
# include <stdlib.h>
#include <locale.h>

using namespace std;

struct vertice {
       char nod;
       int marca;
       struct vertice *sig;
       struct arco *arc;
};

struct arco {
       struct vertice *ver;
       int marca;
       int soma;
       int chave;
       struct arco *sig;
};


struct vertice *pri, *nue, *aux, *ult, *aux2;
struct arco *nueArc, *auxArc, *arcMen, *auxArc2, *antArc;
char auxNod, auxNod2, ban2, let;
int ban, enlace, ban3, ban4, numVer;

void atualizarCampos ();
void criarVertice();
void ligacaoVertices();
void ligacao();
void listarAdjacencia();
void obterArcoMenor();
void listarAdjacenciaPrim ();
void somaCaminhos();

void criarVertice () {
     if (pri == NULL){
        pri = new vertice;
        cout << "O Grafo nao possui vertices.\nDigite a letra do Primeiro No: ";
        cin >> pri->nod;
        pri->marca = 0;
        pri->arc = NULL;
        pri->sig = NULL;
        ult = pri;
        cout << "\nNo registrado corretamente.";
     }
     else {
          cout << "Digite a letra do vertice: ";
          cin >> let;
          do {
              aux = pri;
              ban = 0;
              while (aux != NULL){
                    if (aux->nod == let){
                          ban = 1;
                    }
                    aux = aux->sig;
              }
              if (ban == 1) {
                     cout << "\nEssa letra ja foi usada, assim como a seguinte:\n";
                     aux = pri;
                     while (aux != NULL) {
                           cout << aux->nod << " ";
                           aux = aux->sig;
                     }
                     cout << "\nDigite uma letra diferente: ";
                     cin >> let;
              }
          }while (ban == 1);
          nue = new vertice;
          nue->nod = let;
          nue->marca = 0;
          nue->sig = NULL;
          nue->arc = NULL;
          ult->sig = nue;
          ult = nue;
          cout << "\nNo registrado corretamente.";  
     }     
     
     getchar();         
}

void ligarVertices () {
     if (pri != NULL){
        aux = pri;
        while (aux != NULL){
              cout << aux->nod << "\n";
              aux = aux->sig;
        }
        cout << "\nDigite a letra do ao qual deseja ligar: ";
        cin >> auxNod;        
        ban = 0;
        while (ban == 0){
              aux = pri;
              while (aux != NULL && ban == 0){
                   if (aux->nod == auxNod){
                      ban = 1;
                   }
                   aux = aux->sig;
              }
              if (ban == 0){
                 cout << "\nO no nao existe.\nPor favor digite um dos listados anteriormente: ";
                 cin >> auxNod;
              }
        }
        cout << "\nEstes sao os nos disponiveis para criar a respectiva ligacao:\n";
        aux = pri;
        aux2 = pri;
        while (aux2->nod != auxNod){
              aux2 = aux2->sig;
        }
        while (aux != NULL){
              if (aux->nod != auxNod){
                  auxArc = aux2->arc;
                  ban4 = 0;
                  while (auxArc != NULL && ban4 == 0){
                        if (aux->nod == auxArc->ver->nod){
                           ban4 = 1;
                        }
                        auxArc = auxArc->sig;
                  }
                  if (ban4 == 0){
                     cout << aux->nod << "\n";
                  }
              }
              
              aux = aux->sig;
        }
        cout << "\nDigite a letra do ao qual deseja ligar ao no escolhido: ";
        cin >> auxNod2;
        ban = 0;
        while (ban == 0){
              aux = pri; 
              while (auxNod2 == auxNod){
                    cout << "\nNao foi possivel criar a ligacao.\nDigite outro no disponivel: ";
                    cin >> auxNod2;
              }
              while (aux != NULL && ban == 0){
                   if (aux->nod == auxNod2){
                      ban = 1;
                   }
                   aux = aux->sig;
              }
              if (ban == 0){
                 cout << "\nO no nao existe.\nPor favor digite um dos listados anteriormente: ";
                 cin >> auxNod2;
              }
        }        
        aux = pri;
        while (aux->nod != auxNod){
              aux = aux->sig;
        }        
        auxArc = aux->arc;
        ban3 = 0;
        while (auxArc != NULL && ban3 == 0){
              if (auxArc->ver->nod == auxNod2){
                 ban3 = 1;
              }
              auxArc = auxArc->sig;
        }
        if (ban3 == 0){
           ligacao();
           cout << "\nLigacao criada corretamente.";
        }
        else {
             cout << "\nEssa ligacao ja existe. Verifique a ligacao.";
        }
     }
}

void ligacao (){
        aux = pri;
        while (aux->nod != auxNod){
              aux = aux->sig;
        }
        aux2 = pri;
        while (aux2->nod != auxNod2){
              aux2 = aux2->sig;
        }
        if (aux->arc == NULL){
           nueArc = new arco;
           nueArc->ver = aux2;
           cout << "\nDigite o valor da ligacao: ";
           cin >> enlace;
           while (nueArc->chave < 0){
                 cout << "\nO valor deve ser positivo.\nDigite o valor da ligacao: ";
                 cin >> enlace;
           }
           nueArc->chave = enlace;
           nueArc->marca = 0;
           nueArc->soma = 0;
           nueArc->sig = NULL;
           aux->arc = nueArc;
           if (aux2->arc == NULL){
               nueArc = new arco;
               nueArc->ver = aux;           
               nueArc->chave = enlace;
               nueArc->marca = 0;
               nueArc->soma = 0;
               nueArc->sig = NULL;
               aux2->arc = nueArc;
            }
            else {
               nueArc = new arco;
               nueArc->ver = aux;
               nueArc->chave = enlace;
               nueArc->marca = 0;
               nueArc->soma = 0;
               nueArc->sig = NULL;
               auxArc = aux2->arc;
               while (auxArc->sig != NULL){
                     auxArc = auxArc->sig;
               }
               auxArc->sig = nueArc;
            }
        }
        else {
           nueArc = new arco;
           nueArc->ver = aux2;
           cout << "\nDigite o valor da ligacao: ";
           cin >> enlace;
           while (enlace < 0){
                 cout << "\nO valor deve ser positivo.\nDigite o valor da ligacao: ";
                 cin >> enlace;
           }
           nueArc->chave = enlace;  
           nueArc->marca = 0;
           nueArc->soma = 0;         
           nueArc->sig = NULL;
           auxArc = aux->arc;
           while (auxArc->sig != NULL){
                 auxArc = auxArc->sig;
           }
           auxArc->sig = nueArc;
           if (aux2->arc == NULL){
               nueArc = new arco;
               nueArc->ver = aux;           
               nueArc->chave = enlace;
               nueArc->marca = 0;
               nueArc->soma = 0;
               nueArc->sig = NULL;
               aux2->arc = nueArc;
            }
            else {
               nueArc = new arco;
               nueArc->ver = aux;
               nueArc->chave = enlace;
               nueArc->marca = 0;
               nueArc->soma = 0;
               nueArc->sig = NULL;
               auxArc = aux2->arc;
               while (auxArc->sig != NULL){
                     auxArc = auxArc->sig;
               }
               auxArc->sig = nueArc;
            }
        }
}

void obterArcoMenor () {
     aux2 = pri;
     arcMen = NULL;
     while (aux2 != NULL){
           if (aux2->marca == 1){
                      auxArc = aux2->arc;
                      while (auxArc != NULL){
                            if (auxArc->marca == 1){
                                  if (arcMen == NULL){
                                         arcMen = auxArc;
                                  }
                                  else{
                                       if (auxArc->chave < arcMen->chave){
                                              arcMen = auxArc;
                                       }
                                  }
                            }
                            auxArc = auxArc->sig;
                      }
           }
           aux2 = aux2->sig;
     }
     arcMen->marca = 3;
     arcMen->ver->marca = 1;
}

void obterSomaMenor () {
     aux2 = pri;
     arcMen = NULL;
     while (aux2 != NULL){
           if (aux2->marca == 1){
                      auxArc = aux2->arc;
                      while (auxArc != NULL){
                            if (auxArc->marca == 1){
                                  if (arcMen == NULL){
                                         arcMen = auxArc;
                                  }
                                  else{
                                       if (auxArc->soma < arcMen->soma){
                                              arcMen = auxArc;
                                       }
                                  }
                            }
                            auxArc = auxArc->sig;
                      }
           }
           aux2 = aux2->sig;
     }
     arcMen->marca = 3;
     arcMen->ver->marca = 1;
     auxArc = arcMen->ver->arc;
     while (auxArc != NULL){
           auxArc->soma = arcMen->soma + auxArc->chave;
           auxArc = auxArc->sig;
     }
}

void peso2 (){
            obterArcoMenor();
            cout << "\nO arco menor e: "<< arcMen->ver->nod << " vale: " << arcMen->chave;
            getchar();
            aux = arcMen->ver;
            auxArc = aux->arc;
            while (auxArc != NULL){
                  if (auxArc->ver->marca == 0){
                         aux2 = pri;
                         while (aux2 != NULL){
                               if (aux2 != aux && aux2->marca == 1){
                                     auxArc2 = aux2->arc;
                                     while (auxArc2 != NULL){
                                           if (auxArc->ver->nod == auxArc2->ver->nod){
                                                  if (auxArc->chave < auxArc2->chave){
                                                         auxArc2->marca = 2;
                                                         auxArc->marca = 1;
                                                  }
                                                  else {
                                                       auxArc->marca = 2;
                                                       auxArc2->marca = 1;
                                                  }
                                           }
                                           auxArc2 = auxArc2->sig;
                                     }
                               }
                               aux2 = aux2->sig;
                         }
                         if (auxArc->marca == 0){
                                auxArc->marca = 1;
                         }
                  }
                  else {
                       auxArc->marca = 2;
                  }
                  auxArc = auxArc->sig;
            }
}




void algoritmoPrim () {
     if (pri != NULL){
            atualizarCampos();
            cout << "Digite o vertice inicial: ";
            cin >> auxNod;
            ban = 0;
            while (ban == 0){
                  aux = pri;
                  while (aux != NULL){
                        if (aux->nod == auxNod){
                               ban = 1;
                        }
                        aux = aux->sig;
                  }
                  if (ban == 0){
                         cout << "\nNao ha no com essa letra.";
                         aux = pri;
                         cout << "\n---Lista de Nos---\n";
                         while (aux != NULL){
                               cout << aux->nod << " ";
                               aux = aux->sig;
                         }
                         cout << "\nDigite um dos nos acima: ";
                         cin >> auxNod;
                  }
            }
            aux = pri;
            while (aux->nod != auxNod){
                  aux = aux->sig;
            }
            aux->marca = 1;
            auxArc = aux->arc;
            while (auxArc != NULL){
                  auxArc->marca = 1;
                  auxArc = auxArc->sig;
            }
            cout << "\nTodos os arcos foram marcados para o vertice escolhido.";
            ban2 = 1;
            while (ban2 == 1){
                  peso2();
                  ban2 = 0;
                  aux = pri;
                  while (aux != NULL){
                        if (aux->marca == 0){
                               ban2 = 1;
                        }
                        aux = aux->sig;
                  }
            }
            listarAdjacenciaPrim ();
            somaCaminhos();
     }
     getchar();
}

void listarAdjacencia () {
     if (pri != NULL){
        aux = pri;
        cout << "---Lista de Adjacencia---\n";
        while (aux != NULL){
              auxArc = aux->arc;
              cout << "\n|\n" << aux->nod << "->";
              while (auxArc != NULL){
                    cout << auxArc->ver->nod << " ";
                    auxArc = auxArc->sig;
              }
              aux = aux->sig;
        }
        getchar();
     }
}

void somaCaminhos () {
     aux = pri;
     int soma = 0;
     while (aux != NULL){
           auxArc = aux->arc;
           while (auxArc != NULL){
                 if (auxArc->marca == 3){
                        soma = soma + auxArc->chave;
                 }
                 auxArc = auxArc->sig;
           }
           aux = aux->sig;
     }
     cout << "\nA soma dos caminhos e: " << soma;
}

void listarAdjacenciaPrim () {
     if (pri != NULL){
        aux = pri;
        cout << "\n---Lista de Adjacencia---\n";
        while (aux != NULL){
              auxArc = aux->arc;
              cout << "\n|\n" << aux->nod << "->";
              while (auxArc != NULL){
                    if (auxArc->marca == 3)
                    cout << auxArc->ver->nod << " ";
                    auxArc = auxArc->sig;
              }
              aux = aux->sig;
        }
     }
}


void liberarMemoria () {
     if (pri != NULL){
        aux = pri;
        while (aux != NULL){
              auxArc = aux->arc;
              while (auxArc != NULL){
                    aux->arc = aux->arc->sig;
                    delete auxArc;
                    auxArc = aux->arc;
              }
              pri = pri->sig;
              delete aux;
              aux = pri;
        }
     }
     cout << "Memoria Livre";
     getchar();
}



void atualizarCampos () {
     aux = pri;
     while (aux != NULL){
           auxArc = aux->arc;
           while (auxArc != NULL){
                 auxArc->marca = 0;
                 auxArc->soma = 0;
                 auxArc = auxArc->sig;
           }
           aux->marca = 0;
           aux = aux->sig;
     }
}

main (){
    setlocale(LC_ALL, "");
    int op = 0;
    do{
       cout<<"---Fundação Centro de Análise e Pesquisa e Inovação Tecnológica---";
       cout<<"\n---FACULDADE FUCAPI(INSTITUTO DE ENSINO SUPERIOR FUCAPI)---";
       cout<<"\n---ALGORITMO DE PRIM---";
       cout<<"\nRealizado Por:";
       cout<<"\n\nTayná Rodrigues";
       cout<<"\n\n-----MENU-----";
       cout<<"\n1. Criar Vertices.";
       cout<<"\n2. Ligar Vertices.";
       cout<<"\n3. Listar Vertices com sua lista de adjacencia.";
       cout<<"\n4. Algoritmo de Prim.";
       cout<<"\n5. Liberar Memoria.";
       cout<<"\n6. Sair";
       cout<<"\n\nDigite a opcao:==>";
       cin>>op;
       while (op>6)
	   {
             cout << "Essa opcao nao existe. Digite um numero de 1 a 6: ";
             cin >> op;
       }
       switch(op){
                  case 1: criarVertice(); break;
                  case 2: ligarVertices(); getchar(); break;
                  case 3: listarAdjacencia(); break;
                  case 4: algoritmoPrim(); break;
                  case 5: liberarMemoria (); break;
                  case 6: exit (0);
       }
    }while(op<6);
}