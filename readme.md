# Notes au sujet du jeu « Luttes de pouvoir »

## Notes sur le fonctionnement du programme

### Fichiers

Le programme contient plusieurs fichiers : `main.c`, `jeu.c`, `affichage.c` et `header.h`.
+ Le fichier `main.c` est celui qui est exécuté lors du lancement du jeu ;
+ Le fichier `jeu.c` contient les fonctions qui réalisent les différentes étapes du jeu ;
+ Le fichier `affichage.c` contient les fonctions d'affichages des éléments du jeu (affichage de la cour, affichage des cartes restantes) ;
+ Le fichier `header.h` qui contient toutes les déclarations des fonctions dans les fichiers `jeu.c` et `affichage.c` ainsi que la déclaration des structures `s_partisan` et `s_joueur`.

### Structures

Nous avons utilisé des structures dans le jeu. 
+ La structure `s_partisan` représente un partisan, c'est un dire un personnage qui est placé dans la cour est qui soutien l'un des deux clans. Il contient deux éléments :
  - `orientation` : une valeur `int` qui défini l'orientation du partisan (son allégence à l'un des clans). Cette valeur peut être 1 ou 2 ;
  - `personnage` : une valeur `int` qui défini le type du personnage. Il s'agit d'une valeur entre 1 et 7. [Voir la liste des personnages](#personnages-disponibles)
+ La structure `s_joueur` représente chaque joueur. Elle comporte deux éléments :
  -  `orientation` : une valeur `int` qui définit le clan du joueur. Cette valeur peut être 1 ou 2.
  -  

### Plateau de jeu

Le plateau du jeu est représenté par un tableau de 9 cases, comprenant dans chaque case une structure nommé `s_partisan`.

### Couleurs des clans

Les couleurs (rouge et vert) n'ont pas de significations particulières. Nous avons utilisé ces couleurs, car leur code ASCII se suivent. 


## Notes sur le fonctionnement du jeu

### Règles du jeu

Deux **clans** luttent pour avoir la plus grande influence dans la **cour du roi**.

### Personnages disponibles 

| Numéro | Nom       |
| ------ | --------- |
| 1      | Citoyen   |
| 2      | Roi       |
| 3      | Reine     |
| 4      | Princesse |
| 5      | Ministre  |
| 6      | Général   |
| 7      | Château   |


## Glossaire
+ **Cour** : Grille *3x3* qui représente la cour du roi. Les partisans sont placés dans cette cour ;
+ **Partisan** : Personnage qui est placé dans la cour et qui soutient l'un des deux clans ;
+ **Personnage** : Type de partisan (citoyen, roi, reine, etc..)
+ **Orientation** : Appartenance de la carte à l'un des deux clans.

## Compilation et exécution

Pour compiler et exécuter le jeu automatique
+ Se mettre dans le dossier `compil`. Si besoin utiliser la commande :
``` console
cd compil
```
+ Exécuter la commande suivante pour autoriser le script Shell
``` console
chmod +x script.sh
```
+ Enfin, exécuter la commande suivante
``` console
./script.sh
```


## Ce que j'ai appris lors de ce projet
+ `tab*` et `tab[]` font la même choses quand ils sont paramètres de fonctions. Cependant, l'utilisation de `tab*` est recommandée
+ Une fonction ne peux pas renvoyer un tableau. Cependant, une fonction peut renvoyer une structure, qui elle peut contenir un tableau à l'intérieur
+ `scanf("%*[^\n]");` Pour initialiser la valeur de saisie
+ Il est important de nommer les variables et des fonctions avec des noms cohérent et précis dès le début de la programmation
+ Nous ne pouvons pas mettre une déclaration de variable juste après un switch, sinon l'erreur `a label can only be part of a statement and a declaration is not a statement` est renvoyée; pour ce faire, il faut mettre un ` ;` juste après le `case`. [Lien de la source](https://www.delftstack.com/howto/c/a-label-can-only-be-part-of-a-statement-and-a-declaration-is-not-a-statement/#a-label-can-only-be-part-of-a-statement-and-a-declaration-is-not-a-statement-error-when-using-switch-statements-in-c).

## Pistes d'amélioration

+ Nous aurions pu utiliser des structures pour définir de manière harmonisée les personnages et leurs pouvoirs (au lieu d'utiliser un grand nombre d'opérateur logique).
+ Trouver une meilleure manière de proposer les cases possibles pour l'application du pouvoir (notre version ne prends pas en compte les cases vides ou le château)

## Choses à faire
- [ ] Après changement du fonctionnement du switch pour les emplacements, vérifier les emplacements possibles pour les pouvoirs de la princesse (4 et 8)
- [ ] Vérifier cohérence de tous les noms de variables et de fonctions (en fonction de l'énoncé du sujet)
- [ ] Remplacer les chiffres par le nom des cartes dans la fonction d'affichage du tableau et ajouter des effets graphique
- [ ] Les nombres du plateau sont sur fond noir (en fonction de la couleur du terminal)
- [x] Vérifier les espaces dans la fonction restant_demande
- [ ] Peut-être : Utiliser un fichier texte pour enregistrer les stats sur le jeu (gagant, nombre de coup, etc...)
- [x] Revoir l'affichage des différentes popssibilités (choix joueur, emplacement possible) en mettant en colonnes par exemple