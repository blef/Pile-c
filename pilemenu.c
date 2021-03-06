#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CTAF: Useless. define a function. put macro in UPPER_CASE to distinguish them from function. (macro can sometime be more efficient)
#define pile_donnee(tas)  tas->debut->donnee


typedef struct ElementListe {
  char *donnee;
  struct ElementListe *suivant;
} Element;

typedef struct ListeRepere {
  Element *debut;
  int taille;
} Pile;



void initialisation (Pile * tas) {
  tas->debut = NULL;
  tas->taille = 0;
}

/* empiler (ajouter) un élément dans la pile */
int empiler (Pile * tas, char *donnee) {
  Element *nouveau_element;
  //CTAF: GRAAAAAAAAA =
  if ((nouveau_element = (Element *) malloc (sizeof (Element))) == NULL)
    return -1;
  if ((nouveau_element->donnee = (char *) malloc (50 * sizeof (char)))== NULL)
    return -1;
  strcpy (nouveau_element->donnee, donnee);
  nouveau_element->suivant = tas->debut;
  tas->debut = nouveau_element;
  tas->taille++;
}

/* depiler (supprimer un élément de la pile */
int depiler (Pile * tas){
  Element *supp_element;
  if (tas->taille == 0)
    return -1;
  supp_element = tas->debut;
  tas->debut = tas->debut->suivant;
  free (supp_element->donnee);
  free (supp_element);
  tas->taille--;
  return 0;
}

/* affichage de la pile */
void affiche (Pile * tas){
  Element *courant;
  int i;
  courant = tas->debut;
  for(i=0;i<tas->taille;++i){
    printf("%d\t\t%s\n", i, courant->donnee);
    courant = courant->suivant;
  }
  printf ("\n");
}



/* on regarde si la pile est vide */
int pilevide (Pile * tas){
  int lapilevide=0;
  if(tas->debut == NULL){
    lapilevide=1;
  }
  return lapilevide;
}


//CTAF: return int. or return -1 in your fonction means nothing!
//btw command line program return >0 on error. 1 is common.
int main ()
{
  Pile *tas;
  char *nom;
  int end=0;
  int choix=0;

  //CTAF: NEVER EVER use = in a if. only ==. it's very confusing and error prone
  tas = (Pile *) malloc (sizeof (Pile));
  if (tas == NULL)
    return 1;
  nom = (char *) malloc (50 * sizeof (char));
  if (nom == NULL)
    return 1;
  initialisation (tas);

  printf ("Bienvenue dans le gestionnaire de pile de Felix DEMORE et Quentin GESTES\n");

  while(end!=1){

    printf("Que souhaitez-vous faire?\n");
    printf("Pour afficher la pile tapez 1\n");
    //CTAF: WTF never saw this way of adding accent before!!!
    printf("Pour ajouter un %cl%cment tapez 2\n",130,138);
    printf("Pour supprimer un %cl%cment tapez 3\n",130,138);
    printf("Pour quitter le programme tapez 4\n");
    printf("Pour commander un caf%c tapez 5\n",130);
    //CTAF: check for error here...
    scanf("%d",&choix);
    printf("\n");

    //CTAF: use switch(choix) case 1: ... break. case 2: ... break;
    if (choix==1){

      //CTAF: true is 1, false is 0. so pilevide should return 1 if true.
      if (pilevide(tas)==0){
        printf ("La pile contient %d %cl%cment: \n\n",tas->taille,130,138);
        printf("\n********** Haut de la PILE **********\n\n");
        affiche(tas);
        printf("__________ Bas de la PILE __________\n\n");
      }
      else {
        printf ("La pile est vide\n\n");
      }
    }
    else if (choix==2){
      printf ("Entrez le mot %c rajouter %c la pile : \n",133,133);
      //CTAF: You only take one word from here. make a loop.
      scanf ("%s", nom);
      printf ("\n");
      printf("adding: %s\n", nom);
      empiler (tas, nom);
      printf ("La pile contient %d %cl%cments: \n\n",tas->taille,130,138);
      printf("\n********** Haut de la PILE **********\n\n");
      affiche(tas);
      printf("__________ Bas de la PILE __________\n\n");
    }

    else if (choix==3){

      if (pilevide(tas)==0){
        depiler (tas);
        if (pilevide(tas)==0){
          printf ("La pile contient %d %cl%cment: \n\n",tas->taille,130,138);
          printf("\n********** Haut de la PILE **********\n\n");
          affiche(tas);
          printf("__________ Bas de la PILE __________\n\n");
        }
        else{
          printf ("La pile est d%csormais vide\n\n",130);
        }
      }
      else {
        printf ("La pile est d%cj%c vide\n\n",130,133);
      }

    }

    else if (choix==4){
      end=1;
    }

    else if (choix==5){
      printf ("D%csol%c mais l'option machine %c caf%c n'est qu'en cour de d%cveloppement. Repassez nous voir plus tard.\n\n",130,130,133,130,130);
    }

    else {
      choix=0;
      printf ("D%csol%c mais ceci n'est pas une r%cponse acceptable.\n\n",130,130,130);
    }

    //CTAF: you may want to reset choix to 0 here. to help debugging.
  }
}
