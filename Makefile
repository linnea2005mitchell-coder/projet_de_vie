CXX = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = fichier1.cc fichier2.cc #lister tous les fichiers source: nom_fichier.cc
OFILES = $(CXXFILES:.cc=.o)

all: jeu #modifier avec nom de l'exécutable

jeu   :  $(OFILES)
	$(CXX) $(OFILES) -o jeu


fichier1.o   :  fichier1.cc fichier1.h #modèle: ne pas modifier pour pouvoir copier/coller
	$(CXX) $(CXXFLAGS) -c fichier1.cc -o fichier1.o #modèle: ne pas modifier

fichier2.o  :  fichier2.cc fichier2.h fichier2.h
	$(CXX) $(CXXFLAGS) -c fichier2.cc -o fichier2.o

depend :
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile


clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ jeu

#taper "make depend" ou "make clean" dans le terminal pour que ça s'exécute