CXX = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = balls.cc bricks.cc game.cc message.cc paddle.cc project.cc tools.cc  #lister tous les fichiers source: nom_fichier.cc
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

#taper "make clean", "make depend, "make" dans le terminal

balls.o: balls.cc balls.h tools.h constants.h message.h
bricks.o: bricks.cc bricks.h tools.h constants.h message.h
game.o: game.cc game.h balls.h tools.h constants.h message.h bricks.h \
 paddle.h
message.o: message.cc message.h
paddle.o: paddle.cc paddle.h tools.h constants.h message.h
project.o: project.cc game.h balls.h tools.h constants.h message.h \
 bricks.h paddle.h
tools.o: tools.cc tools.h constants.h message.h
balls.o: balls.cc balls.h tools.h constants.h message.h
bricks.o: bricks.cc bricks.h tools.h constants.h message.h
game.o: game.cc game.h balls.h tools.h constants.h message.h bricks.h \
  paddle.h
message.o: message.cc message.h
paddle.o: paddle.cc paddle.h tools.h constants.h message.h
project.o: project.cc game.h balls.h tools.h constants.h message.h \
  bricks.h paddle.h
tools.o: tools.cc tools.h constants.h message.h
