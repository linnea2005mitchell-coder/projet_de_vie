CXX = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = balls.cc bricks.cc message.cc paddle.cc tools.cc #lister tous les fichiers source: nom_fichier.cc
OFILES = $(CXXFILES:.cc=.o)

all: project #modifier avec nom de l'exécutable

project   :  $(OFILES) 
	$(CXX) $(OFILES) -o project

depend :
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile


clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ project

#taper "make clean", ensuite "make depend, ensuite "make" dans le terminal pour que ça s'exécuteballs.o: balls.cc

balls.o: balls.cc
bricks.o: bricks.cc
message.o: message.cc message.h
paddle.o: paddle.cc
tools.o: tools.cc
