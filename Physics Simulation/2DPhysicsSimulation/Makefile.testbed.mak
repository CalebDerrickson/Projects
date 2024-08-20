# Your existing variables here...
DIR := $(subst /,\,${CURDIR})
BUILD_DIR := bin
OBJ_DIR := obj

DEPENDENCIES_PATH := dependencies

ASSEMBLY := testbed
EXTENSION := .exe
COMPILER_FLAGS := -g -MD -Werror=vla -Wno-missing-braces #-fPIC
INCLUDE_FLAGS := -Itestbed\src -I$(DEPENDENCIES_PATH)\include 
LINKER_FLAGS := -g -L$(OBJ_DIR)\ -L$(BUILD_DIR)\ -L$(DEPENDENCIES_PATH)\lib -lglfw3 -lgdi32 -lopengl32 #-Wl,-rpath,.
DEFINES :=

# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRC_FILES := $(call rwildcard,$(ASSEMBLY)/,*.cpp) # Get all .cpp files
DIRECTORIES := \$(ASSEMBLY)\src $(subst $(DIR),,$(shell dir $(ASSEMBLY)\src /S /AD /B | findstr /i src)) # Get all directories under src.
OBJ_FILES := $(SRC_FILES:%=$(OBJ_DIR)/%.o) # Get all compiled .cpp.o objects for testbed

all: scaffold compile link

.PHONY: scaffold
scaffold: # create build directory
	@echo Scaffolding folder structure...
	-@setlocal enableextensions enabledelayedexpansion && mkdir $(addprefix $(OBJ_DIR), $(DIRECTORIES)) 2>NUL || cd .
	@echo Done.

.PHONY: link
link: scaffold $(OBJ_FILES) # link
	@echo Linking $(ASSEMBLY)...
	@g++ $(OBJ_FILES) -o $(BUILD_DIR)/$(ASSEMBLY)$(EXTENSION) $(LINKER_FLAGS)

.PHONY: compile
compile: #compile .cpp files
	@echo Compiling...

.PHONY: clean
clean: # clean build directory
	if exist $(BUILD_DIR)\$(ASSEMBLY)$(EXTENSION) del $(BUILD_DIR)\$(ASSEMBLY)$(EXTENSION)
	rmdir /s /q $(OBJ_DIR)\$(ASSEMBLY)

.PHONY: list_dependencies
list_dependencies:
	@echo Listing files in $(DEPENDENCIES_PATH)...
	@dir $(DEPENDENCIES_PATH)\lib
	
$(OBJ_DIR)/%.cpp.o: %.cpp # compile .cpp to .cpp.o object
	@echo   $<...
	@g++ $< $(COMPILER_FLAGS) -c -o $@ $(DEFINES) $(INCLUDE_FLAGS)

-include $(OBJ_FILES:.o=.d)
