

# variables

# where we put all our binaries and other similar files
BUILDDIR:= target

# the files to compile
# ADD NEWLY CREATED FILES HERE:
override SRC :=	\
		src/main.cpp \
		src/Village.cpp \
		src/ResourcesManager.cpp \
		src/GameManager.cpp \
		src/WindowManager.cpp \
		src/AssetsManager.cpp \
		src/Displayable.cpp \
		src/Clickable.cpp \
		\
		src/Buildings/Building.cpp \
		src/Buildings/TownHall.cpp \
		src/Buildings/Tank.cpp \
		src/Buildings/GoldTank.cpp \
		src/Buildings/ManaTank.cpp \
		src/Buildings/ResourceGenerator.cpp \
		src/Buildings/GoldMine.cpp \
		src/Buildings/ManaMill.cpp \
		\
		src/Scenes/Scene.cpp \
		src/Scenes/VillageScene.cpp \
		src/Scenes/ShopScene.cpp \
		\
		src/Buttons/Button.cpp \
		src/Buttons/OpenShopButton.cpp \
		src/Buttons/BuildingButtons/BuildingButton.cpp \
		src/Buttons/BuildingButtons/UpgradeButton.cpp \
		src/Buttons/BuildingButtons/InfoButton.cpp \
		src/Buttons/BuildingButtons/CollectResourceButton.cpp \
		src/Buttons/BuildingButtons/CollectGoldButton.cpp \
		src/Buttons/BuildingButtons/CollectManaButton.cpp \
		\
		src/Buttons/CreateBuildingButtons/CreateBuildingButton.cpp \
		src/Buttons/CreateBuildingButtons/CreateGoldTankButton.cpp \
		src/Buttons/CreateBuildingButtons/CreateGoldMineButton.cpp \
		src/Buttons/CreateBuildingButtons/CreateManaMillButton.cpp \
		src/Buttons/CreateBuildingButtons/CreateManaTankButton.cpp \
		src/Buttons/CreateBuildingButtons/CreateTownHallButton.cpp \

		



# the corresponding binary files
# they are obtained by replacing (syntactically) all instances of .cpp by .o
override OBJ :=	$(SRC:%.cpp=$(BUILDDIR)/%.o)

# name of the project
NAME := main

# compiler
CXX:= g++ # it is g++ by default, but good to know the option
# pre-compilation flags
override CPPFLAGS += -I include
# compile flags
override CXXFLAGS += -Wall -std=c++17

# linker (g++ is fine, just in case we want it to be custom)
LD := $(CXX)
# libraries used in the project
override LDLIBS += -lsfml-graphics -lsfml-window -lsfml-system
# flags for the linkage
override LDFLAGS += 

override RM := rm -rf

# the default rule for the makefile (must be the first one)
all: $(NAME)

# main rule for the project
# the $^ sign means that all dependencies are compiled
# the -o option refers to the linkage step
# $@ means the resulting binary will be named NAME
$(NAME): $(OBJ)
	
	$(LD) $(LDFLAGS) $^ -o $@ $(LDLIBS) 

# cleans up everything nicely
clean:
	$(RM) $(BUILDDIR) $(NAME)

# rules in order to correctly take into account the .hpp files
$(BUILDDIR)/%.o: override CPPFLAGS += -MT $@ -MMD -MP -MF $(@:.o=.d)
$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(COMPILE.cc) $< -o $@


# the targets that do not generate binaries
.PHONY := all clean

-include $(OBJ:.o=.d)

