# projet_de_vie
le fun

checker les conventions : 
- methodes dans .cc

Définitions: mettre tous les include iostream et compagnie dans les fichiers.cc,
    dans les fichiers.h ne mettre que ce qui est nécessaire dans ce .h (ex: include string ou vector) 
    (ne pas mettre iostream car très lourd) ==>on ne peut pas utiliser cout dans un fichier.h
    ==>remplacer string, vector, ifstream, etc. par std::string, std::vector, std::ifstream, etc dans les .h

Syntaxe de lancement: dans terminal: ./project t01.txt
    si affiche No such file or directory s'assurer que make a bien été fait (doit afficher: Nothing to be done for 'all'.)