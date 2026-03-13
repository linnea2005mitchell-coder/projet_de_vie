CXX = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = fichier1.cc fichier2.cc #lister tous les fichiers source: nom_fichier.cc
OFILES = $(CXXFILES:.cc=.o)

all: jeu #modifier avec nom de l'exécutable

jeu   :  $(OFILES) 
	$(CXX) $(OFILES) -o jeu

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

#taper "make clean", ensuite "make depend, ensuite "make" dans le terminal pour que ça s'exécute