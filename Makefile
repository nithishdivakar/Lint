# Targets
APP = main.out
LIB = lint


# Directory Names
BINARIES  = bin
SOURCES   = src
TESTCASES = test
INCLUDES  = include
BUILD_DIR = build

#flags and opions

CC      = g++
LINKER  = g++
CFLAGS  = -c -Wall -Wc++11-extensions
INCLUDE = -I $(INCLUDES)
LDFLAGS =  







SRC_DIR = $(SOURCES)
OBJ_DIR = $(BUILD_DIR)
DEP_DIR = $(BUILD_DIR)
BIN_DIR = $(BINARIES)
TST_DIR = $(TESTCASES)


SRC_NAMES = $(notdir $(wildcard $(SRC_DIR)/*.cpp))
OBJ_NAMES = $(SRC_NAMES:.cpp=.o)
DEP_NAMES = $(SRC_NAMES:.cpp=.d)
BIN_NAMES = $(APP)
TST_NAMES = $(notdir $(wildcard $(TST_DIR)/*.cpp))


SRC_FILES = $(addprefix $(SRC_DIR)/,$(SRC_NAMES))
OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(OBJ_NAMES))
DEP_FILES = $(addprefix $(DEP_DIR)/,$(DEP_NAMES))
BIN_FILES = $(addprefix $(BIN_DIR)/,$(BIN_NAMES))
TST_FILES = $(addprefix $(TST_DIR)/,$(TST_NAMES))




all: $(BIN_FILES)

print:	
	@echo $(SRC_FILES)
	@echo $(OBJ_FILES)
	@echo $(DEP_FILES)
	@echo $(BIN_FILES)
	@echo $(TST_FILES)
	@echo $(SRC_DIR) 
	@echo $(OBJ_DIR) 
	@echo $(DEP_DIR)


$(BIN_FILES):$(OBJ_FILES)
	$(LINKER) $(LDFLAGS) $(OBJ_FILES) -o $(BIN_DIR)/$@


	#$(AR) rcs $(BIN_DIR)/$(LIB) $(OBJ_FILES)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp 
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(DEP_DIR)/%.d: $(SRC_DIR)/%.cpp
	$(CC) $(INCLUDE) -MM $< | sed 's|^|$@ |' > $@


clean:
	rm -rf $(BIN_DIR)/* $(DEP_DIR)/*


# testing 


TST_OBJ = $(TST_NAMES:.cpp=.o)
TST_OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(TST_OBJ))

#t:
#	@echo $(TST_OBJ_FILES)
#	@echo $(TST_OBJ)
#	@echo $(GTEST_DIR)
#	@echo $(GTEST_SRCS_)

test: $(TST_OBJ_FILES) $(OBJ_FILES) $(DEP_DIR)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $(BIN_DIR)/test.out

$(OBJ_DIR)/%.o:$(TST_DIR)/%.cpp 
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	



GTEST_DIR     = 3rdparty/googletest/googletest
PPFLAGS      += -isystem $(GTEST_DIR)/include
CXXFLAGS     += -g -Wall -Wextra -pthread
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_   = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

$(DEP_DIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR)/include -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc -o $@

$(DEP_DIR)/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR)/include -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc -o $@

$(DEP_DIR)/gtest.a :$(DEP_DIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(DEP_DIR)/gtest_main.a :$(DEP_DIR)/gtest-all.o $(DEP_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^


