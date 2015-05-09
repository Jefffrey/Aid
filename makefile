CC				:= clang++
RM				:= rm
CP 				:= cp

LD_FLAGS		:=
CC_FLAGS		:= -std=c++1y -O2 -ferror-limit=3
CP_FLAGS 		:= -fR

SUITE_EXE 		:= suite
SUITE_CPP_FILES	:= $(wildcard test/main.cpp)\
				   $(wildcard test/aid/*.cpp)\
				   $(wildcard test/aid/ecs/*.cpp)
SUITE_OBJ_FILES	:= $(SUITE_CPP_FILES:.cpp=.o)

INSTALL_PATH	:= /usr/local/include

suite: $(SUITE_OBJ_FILES)
	$(CC) $(LD_FLAGS) -o $@ $^

install:
	$(RM) -rf $(INSTALL_PATH)/aid
	$(CP) $(CP_FLAGS) include/ $(INSTALL_PATH)

test: suite
	./$(SUITE_EXE)

clean:
	$(RM) -f $(SUITE_EXE)
	find . -name "*.o" -type f -delete

%.o: %.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<
