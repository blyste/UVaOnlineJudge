CXX 		  := g++
CXXFLAGS 	:= -Wall -g -pedantic -O2 -std=c++11

OUTPUT		:= main

LAWN_PATH				:= lawn_mower/
NOCHANGE_PATH 	:= no_change/
MICE_PATH 			:= mice_maze/
GOLDBACH_PATH		:= goldbach_conjecture/
MAYA_PATH 			:= maya_calendar/
WATER_PATH			:= water_shortage/
X_NETWORK				:= X_network/
CRIME 					:= crime/
ONES						:= ones/
BUY							:= buy/
BALLOONS				:= balloons/

all: no_change lawn_mower mice goldbach maya water x_network crime ones buy balloons

no_change: $(NOCHANGE_PATH)$(OUTPUT)

lawn_mower: $(LAWN_PATH)$(OUTPUT)

mice: $(MICE_PATH)

goldbach: $(GOLDBACH_PATH)$(OUTPUT)

maya: $(MAYA_PATH)$(OUTPUT)

water: $(WATER_PATH)$(OUTPUT)

x_network: $(X_NETWORK)$(OUTPUT)

crime: $(CRIME)$(OUTPUT)

ones: $(ONES)$(OUTPUT)

buy: $(BUY)$(OUTPUT)

balloons: $(BALLOONS)$(OUTPUT)

.PHONY: clean all

clean:
	rm */main
