NAME            = testMysqlApi


###################################################################################
# PROJECT FILES
###################################################################################

FILES=         testMysqlApi


###################################################################################
# PROJECT SETTINGS
###################################################################################
PROJ_DIR	= .
INCLUDE_PATH	= ./inc

OBJECTS		= $(foreach file,$(FILES),$(addsuffix .o,$(file)))

MYSQL_INC := $(shell mysql_config --include)
MYSQL_LIB := $(shell mysql_config --libs)

#LL_OPT	:= `mysql_config –libs` 
LL_OPT  := $(MYSQL_LIB)
CFLAGS  := $(CFLAGS) -std=c99 -pedantic -O2 -g -W -Wall `mysql_config –cflags`
CXX     := g++
CXXFLAGS:= $(CXXFLAGS)  -Wall #-pedantic -Wno-long-long -02
#LIBS    := -L/usr/local/lib -lmysqlpp -lmysqlclient
INCLUDES:= ./inc $(MYSQL_INC)

VPATH = src obj

.PHONY : clean all executable

all: executable


###################################################################################
#  C Compiler - Code generation
###################################################################################
#g++ -I/usr/include/mysql -I/usr/include/mysql++ -o test.o -c test.c
#g++ -L/usr/local/lib -lmysqlpp -lmysqlclient -o test test.o


%.o: %.c
		$(CC) $(CFLAGS) -c -I $(INCLUDE_PATH) -o obj/$@  $<

#%.o: %.cpp
#		$(CXX) $(CXXFLAGS) -c -I$(INCLUDE_PATH) -o obj/$@  $<
%.o : %.cpp
		g++ -g -o obj/$@ -c -I$(INCLUDES) $<

#executable:	$(OBJECTS)
#		$(CXX) -g $(OBJ_LIST) $(LL_OPT) -o c$(NAME)

executable:	$(OBJECTS)
		g++ obj/$^ -o$(NAME) -g $(LL_OPT) 



#g++ -o genDatabase genDatabase.cpp `mysql_config --cflags` `mysql_config --libs`

test:		
		echo "CC: $(CC)"
		echo "CFLAGS: $(CFLAGS)"
###################################################################################
#  clean
###################################################################################
clean:
	rm -f obj/*.o
	rm -f $(NAME)
	rm -f core
