CC = clang++

FLAGS = -DDEBUG -D_DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Wc++17-compat -Wmissing-declarations -Wcast-align \
		-Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral \
		-Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked \
		-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 \
		-Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros \
		-Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new \
		-fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -fPIE \
		-Werror=vla -fsanitize=address,undefined,float-divide-by-zero,integer-divide-by-zero,vptr

LDFLAGS = -isystem /opt/homebrew/include -L/opt/homebrew/lib -lraylib \
          -framework OpenGL -framework Cocoa -framework IOKit

COMMON_INCLUDES = -I./include -I./src

BASE_FILES     = src/Guids.cpp

ALL_SRCS = src/main.cpp $(BASE_FILES)

WORK_DIR = ./work
BUILD_DIR = ./work/build
RUN_DIR = ./work/run
TARGET = $(RUN_DIR)/vectoria_program

all: vectoria

vectoria: $(ALL_SRCS) $(GRAPHICS_FILES) $(SHAPES_FILES) $(TOOLS_FILES) $(WINDOWS_FILES)
	@mkdir -p $(WORK_DIR)
	@mkdir -p $(BUILD_DIR) $(RUN_DIR)
	@echo "-----------------------------------------------------------------------------------------"
	$(CC) $(COMMON_INCLUDES) -o $(BUILD_DIR)/vectoria_program $(FLAGS) $(ALL_SRCS) $(LDFLAGS)
	@mv $(BUILD_DIR)/vectoria_program $(TARGET)
	@echo "Build successful: $(TARGET)"
	@echo "-----------------------------------------------------------------------------------------"

run-vectoria: vectoria
	$(TARGET)
	
run: run-vectoria

clean:
	rm -rf $(WORK_DIR)

help:
	@echo "Available commands:"
	@echo ""
	@echo "  make vectoria                - compile vectoria"
	@echo "  make run-vectoria            - compile and run vectoria"
	@echo "  make run                     - compile and run vectoria"
	@echo ""
	@echo "  make clean                   - remove compiled programs"

.PHONY: vectoria run-vectoria run clean help
