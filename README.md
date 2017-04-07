# Structure Stellaire
@authors: Léo ESNAULT, Erwan Olivier.

Ce projet vise à développer un code de calcul de structure stellaire simple en C++.
La résolution de l'équation de Lane-Emden est effectuée à l'aide d'un schéma excentré à gauche en une seule itération, et une méthode de Newton est utilisée pour trouver des racines aux équations non linéaires.

Le programme principal, nommé prog_Lane-Emden.cpp est placé dans le dossier exe/ avec son Makefile et un autre code, nommé prog_comparaison_methodes.cpp qui permet de tester la méthode de Newton-Raphson ainsi que celle de la dichotomie.
Le dossier resultats/ contient les résultats de quelques simulations, et le dossier affichages/ les affichages correspondants (attention au chemin du fichier .dat si vous cherchez à afficher les résultats d'une de vos simulations).
Le sujet et quelques articles sont placés dans le dossier doc/ et les images du rapport dans le dossier images/ .
