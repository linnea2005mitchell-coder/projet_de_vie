OUT      := project
CXX      := g++
CXXFLAGS := -Wall -std=c++17
PKGS     := gtkmm-4.0
LINKING  := $(shell pkg-config --cflags $(PKGS))
LDLIBS   := $(shell pkg-config --libs $(PKGS))

BUILD_DIR := build

CXXFILES := graphic.cc project.cc gui.cc balls.cc bricks.cc game.cc message.cc \
			paddle.cc tools.cc
OFILES   := $(addprefix $(BUILD_DIR)/, $(CXXFILES:.cc=.o))

.PHONY: all clean tests

all: $(OUT)

$(BUILD_DIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

$(OUT): $(OFILES)
	@$(CXX) $(CXXFLAGS) $(LINKING) $^ -o $@ $(LDLIBS)

clean:
	@echo "Cleaning project..."
	@rm -rf $(BUILD_DIR) $(OUT)

tests: $(OUT)
	@for test in $$(ls tests); do \
		echo "Running $$test..."; \
		./$(OUT) tests/$$test; \
	done

#ajouté après:
depend :
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

graphic.o: graphic.cc graphic.h graphic_gui.h
project.o: project.cc game.h balls.h tools.h constants.h message.h \
 graphic.h bricks.h paddle.h gui.h
gui.o: gui.cc constants.h tools.h message.h graphic.h graphic_gui.h gui.h
balls.o: balls.cc balls.h tools.h constants.h message.h graphic.h
bricks.o: bricks.cc bricks.h tools.h constants.h message.h graphic.h
game.o: game.cc game.h balls.h tools.h constants.h message.h graphic.h \
 bricks.h paddle.h
message.o: message.cc message.h
paddle.o: paddle.cc paddle.h tools.h constants.h message.h graphic.h
tools.o: tools.cc tools.h constants.h message.h graphic.h
