CXX 		  := g++
CXXFLAGS 	:= -Wall -g -pedantic -O2

OUTPUT		:= main

LAWN_PATH				:= lawn_mower/
NOCHANGE_PATH 	:= no_change/
MICE_PATH 			:= mice_maze/
GOLDBACH_PATH		:= goldbach_conjecture/
MAYA_PATH 			:= maya_calendar/

all: no_change lawn_mower mice goldbach maya

no_change: $(NOCHANGE_PATH)$(OUTPUT)

lawn_mower: $(LAWN_PATH)$(OUTPUT)

mice: $(MICE_PATH)

goldbach: $(GOLDBACH_PATH)$(OUTPUT)

maya: $(MAYA_PATH)$(OUTPUT)

.PHONY: clean all

clean:
	rm */main
