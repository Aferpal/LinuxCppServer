TARGET = app

CXX = g++

CXXFLAGS = -Wall -g

SOURCE_FOLDER = ./src

OUTPUT_FOLDER = ./output

OBJS_FOLDER = ./obj


SRCS = main.cpp $(wildcard $(SOURCE_FOLDER)/*.cpp)  $(wildcard $(SOURCE_FOLDER)/Exceptions/*.cpp) $(wildcard $(SOURCE_FOLDER)/String/*.cpp)

OBJS = $(SRCS:$(SOURCE_FOLDER)/%.cpp=$(OBJS_FOLDER)/%.o)



$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(OUTPUT_FOLDER)/$(TARGET)

$(OBJS_FOLDER)/%.o: $(SOURCE_FOLDER)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) -c $< -o $@

clean:
	rm $(OBJS_FOLDER)/*.o

run: 
	$(OUTPUT_FOLDER)/$(TARGET)