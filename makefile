#set up the compiler and the flags to pass to it
#these are constants
CC = g++
CFLAGS = ""
WORKING_DIR = $(HOME)/dev/c++/analysis
HEADER_DIR = $(WORKING_DIR)/src/headers
_DEPENDENCIES = client.h server.h stdFunctions.h
DEPENDENCIES = $(patsubst %, $(HEADER_DIR)/%, $(_DEPENDENCIES))
O_DIR = $(WORKING_DIR)/obj
_COMMON_OBJ = stdFunctions.o
# used to place object files in separate directory
COMMON_OBJ = $(patsubst %, $(O_DIR)/%, $(_COMMON_OBJ))
_CLIENT_OBJECTS = client.o
CLIENT_OBJECTS = $(COMMON_OBJ) $(patsubst %, $(O_DIR)/%, $(_CLIENT_OBJECTS))
_SERVER_OBJECTS = server.o
SERVER_OBJECTS = $(COMMON_OBJ) $(patsubst %, $(O_DIR)/%, $(_SERVER_OBJECTS))
DOC_DIR = $(WORKING_DIR)/doc
DOC_SRC = $(WORKING_DIR)/src/doc
_DOCS = README.md
DOCS = $(patsubst %, $(DOC_SRC)/%, $(_DOCS))

#define a rule for the .o files
#says they depend on .c and the list of dependecnies
# $@ is left side of dependencies line
# $^ is right side of dependencies line
# $(O_DIR)/%.o places the files in the directory specified by $(O_DIR) by using the left side of the Dependencies line
$(O_DIR)/%.o: %.c $(DEPENDENCIES)
	#says to use the compiler, create the .o file,
	#set the output file to the name of the file on the left of the deps line,
	#and $< is the first item on the DEPS variable
	$(CC) -c -o $@ $< $(CFLAGS)

build: standardMake clientMake serverMake docMake

standardMake: $(COMMON_OBJ)
	$(CC) -c -o $@ $< $(CFLAGS)

clientMake: $(CLIENT_OBJECTS)	#list of dependencies for this rule
	#says to output to client and compile all objects on the right
	#side of the dependencies line
	$(CC) -o client $^ $(CFLAGS)

serverMake: $(SERVER_OBJECTS)
	$(CC) -o server $^ $(CFLAGS)

docMake: $(DOCS)
	pandoc -s --toc -o $(DOC_DIR)/README.html -f markdown+grid_tables -t html $^

#says not to do anything special if there is a file called clearn
.PHONY: clean

#runs with "make clean"
clean:
	#the "-" says to ignore the return status of this command
	-rm $(O_DIR)/*.o
