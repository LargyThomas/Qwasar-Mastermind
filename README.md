# Welcome to My Mastermind
***

## Task
What is the problem? And where is the challenge?
L’objectif de ce projet est de coder une version du jeu Mastermind.
## Description
How have you solved the problem?
Le programme génère ou reçoit en argument un code secret de 4 chiffres différents entre 0 et 8.
## Installation
How to install your project? npm install? make? make re?
J'ai utilisé le terminal pour créer mes fichiers et moon Makefile pour compiler.
## Usage
How does it work?
J'ai créer plusieurs fonctions qqui vont me permettre de réaliser différentes tâchhes (generation8_code(), str_len(), validation_format(), compare_code(), lecture_code(), gestion_arguments())

Dans la fonction main je fais en sorte que :
Le joueur doit essayer de deviner le code en un nombre limité de tentatives (10 par défaut ou modifiable avec `-t`).  
Après chaque essai, le programme affiche :
- Le nombre de chiffres bien placés(bonne valeur + bonne position)
- Le nombre de chiffres mal placés(bonne valeur mais position différente)

Si le joueur trouve le code exact, le programme affiche un message de victoire.


### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
