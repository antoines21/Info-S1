# Notes au sujet du jeu
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
---
## Notes sur le fonctionnement du code

+ Le plateau du jeu est représenté par un tableau de 9 cases, comprenant dans chaque case une structure nommé `s_partisan`.
+ La structure `s_partisan` est composé de 2 sous-éléments : 
  - Une valeur qui défini l'orientation de la carte (son allégence). Cette valeur est un `int` qui peut prendre deux valeurs : 1 ou 2.
  - Une valeur qui défini le personnage. Une valeur `int` entre 1 et 7.



### Persoonnages disponibles 

| Numéro | Nom |
| ------ | ----------- |
| 1 | Citoyen |
| 2 | Roi |
| 3 | Reine |
| 4 | Princesse |
| 5 | Ministre |
| 6 | Général |
| 7 | Château |


## Choses à faire
+ Ajouter des `if` autour des `scanf` et vérifier qu'ils ne fonctionnent qu'avec la bonne valeur rentrée