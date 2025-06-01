# --------------------------
# TÊN CHƯƠNG TRÌNH CHÍNH
TARGET := release/SnakeGame.exe

# --------------------------
# TRÌNH BIÊN DỊCH & CỜ BIÊN DỊCH
CXX := g++
CXXFLAGS := -I./SFML/include -I./source -std=c++17
LDFLAGS := -mconsole -L./SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lodbc32

# --------------------------
# NGUỒN CHƯƠNG TRÌNH CHÍNH
SRC := $(wildcard source/*.cpp)
OBJ := $(patsubst source/%.cpp, release/%.o, $(SRC))

# --------------------------
# MẶC ĐỊNH
all: $(TARGET)

# --------------------------
# BIÊN DỊCH CHƯƠNG TRÌNH CHÍNH
$(TARGET): $(OBJ)
	@if not exist release mkdir release
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

release/%.o: source/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# CLEAN
clean:
	@if exist release rmdir /S /Q release

.PHONY: all clean
