# TP2 : Jeu Hex

## 1 - Description du problème

Dans ce projet, vous êtes charg ́e de développer un agent capable de jouer au jeu Hex. Voici
les règles du jeu (source : Wikipedia <https://fr.wikipedia.org/wiki/Hex>).
Le jeu commence avec le joueur X. Les joueurs placent à tour de rôle un pion de leur couleur
sur une case vide du plateau. Une fois placé, un pion ne peut plus être déplacé ni retiré
jusqu’à la fin de la partie. Un joueur gagne dès qu’il réussit à former un chemin continu de
pions de sa couleur reliant ses deux côtés opposés du plateau (de gauche à droite pour X
et de haut en bas pour O). Il est important de noter qu’un match nul est impossible dans
Hex ; il n’existe aucune configuration de jeu o`u aucun des joueurs ne peut gagner.

Vous pouvez jouer contre vous-même dans l’environnement de jeu pour mieux assimiler les
règles. Pour jouer un coup, cliquez simplement sur la case choisie. Si le coup est valide,
votre pion sera placé sur le plateau.

## 2 - Instructions

Votre mission consiste à impl ́ementer une intelligence artificielle utilisant l’algorithme Monte
Carlo Tree Search (MCTS). Pour l’ évaluation, chaque joueur dispose de 100 seconds de
temps de réflexion pour l’ensemble de la partie. Le d ́epassement de ce d élai d’une minute entraîne la perte de la partie.

## 3 - Langages de programmation

L’utilisation du langage C++ est TRÈS FORTEMENT RECOMMAND ́EE, un squelette de code vous  ́etant fourni. Vous devrez modifier le fichier src/IA Player.h en redéfinissant
les méthodes suivantes :
— void otherPlayerMove(int row, int col), appel ́ee apr`es chaque coup de l’adver-
saire.
— std::tuple<int, int> getMove(Hex Environment& hex), qui doit déterminer et
retourner le coup à jouer par votre IA.
Dans le code initial, les coups sont choisis de manière aléatoire.
Si vous optez pour un autre langage de programmation, assurez-vous que votre projet soit
compatible avec l’environnement de jeu :

— Votre programme sera lancé avec comme premier argument X si votre agent joue les
rouges, ou O s’il joue les bleus.
— Les échanges avec le programme se feront via l’entŕee et la sortie standard, en utilisant
des coordonnées sous la forme ”ij”, où ”i” représente le num ́ero de la ligne (entre 0
et 9) et ”j” le numéro de la colonne (également entre 0 et 9).
— Votre programme doit pouvoir être compilé et exécuté dans l’environnement de correction (Linux Ubuntu 23.10).

## 4 - Environnement de jeu

Pour compilier l’environement :
$ mkdir build
$ cd build
$ cmake ..
$ make
Pour connaître les différentes options du jeu vous pouvez l’ex ́ecuter avec la commande
“--help” :
$ ./Hex --help
Environnement pour le jeu Hex
Usage: ./Hex [OPTIONS]
Options:
-h,--help Print this help message and exit
-X TEXT Si "-X IA" alors le joueur X (rouge) sera jou ́e par l’IA.
Sinon, il s’agit d’un path vers un programme externe.
-O TEXT Si "-O IA" alors le joueur O (bleu) sera jou ́e par l’IA.
Sinon, il s’agit d’un path vers un programme externe.
--slow Ajoutez un d ́elai entre chaque coup de l’IA
--noGUI D ́esactiver l’affichage graphique
--size UINT Taille du plateau de jeu (default: 10, seulement 10 si appel
`a un programme externe)
--seed UINT Seed pour l’al ́eatoire (par d ́efaut: 0 pour seed al ́eatoire)

## 5 - Évaluation

Votre programme sera  évalué face à un certain nombre d’IA de différents niveaux. Votre
 évaluation dépendra de la performance de votre IA et du respect des directives. Tous les joueurs artificiels seront  ́egalement comparés lors d’un tournoi virtuel. Les 5 meilleures IA
recevront un point bonus supplémentaire.

### 6 - Algorithme MCTS

### 7 - Optimisations

Vous avez terminé d’impl ́ementer MCTS et votre IA n’est toujours pas très forte ? C’est
normal, sur une taille de 10x10, des optimisations sont nécessaire pour rendre votre IA
performante

### 7.1 - Fillin pruning

### 7.2 - RAVE (Rapid Action Value Estimation)

## Directives

— Vous avez la possibilité de modifier ou d’ajouter des fichiers sources à votre projet,
à l’exception de la classe Player Interface et du nom de la classe de votre IA doit
rester IA Player. Votre programme doit  également rester compatible avec le fichier main.cpp. Ce dernier sera automatiquement remplacé pour l’évaluation. Veillez donc
à ne déclarer aucun élément dans ce fichier qui serait nécessaire au fonctionnement
de votre IA.
— Le devoir est à rendre par Moodle avant le 11 mars 23h59 (5% de pénalité par jour
de retard).
— Rendre les fichiers source seulement. Aucun fichier binaire. (supprimer le dossier
build de votre archive)
— Compilable et exécutable sans modifications et via cmake pour C++.
