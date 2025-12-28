APP_NAME := GSEditor

ifeq ($(DEBUG), 1)
BUILD_TARGET := debug
else
BUILD_TARGET := release
endif

SOURCE_DIR       := src
RESOURCE_DIR     := res
LIB_DIR          := lib
BUILD_DIR        := build
BUILD_TARGET_DIR := $(BUILD_DIR)/$(BUILD_TARGET)
BUILD_OBJ_DIR    := $(BUILD_TARGET_DIR)/obj
BUILD_TOOLS_DIR  := $(BUILD_TARGET_DIR)/tools

APP_FILENAME := $(APP_NAME).exe
TARGET       := $(BUILD_TARGET_DIR)/bin/$(APP_FILENAME)

################################################################################

ifeq ($(DEBUG), 1)
WXCCFLAGS  := --cflags --unicode --static --debug
WXCXXFLAGS := --cxxflags --unicode --static --debug
WXLDFLAGS  := --libs --unicode --static
else
WXCCFLAGS  := --cflags --unicode --static
WXCXXFLAGS := --cxxflags --unicode --static
WXLDFLAGS  := --libs --unicode --static
endif

CCWARNS := -Wno-comment \
           -Wno-parentheses \
           -Wno-unused-parameter \
           -Wno-unused-variable \
           -Wno-unused-function

CXXWARNS := -Wno-comment \
            -Wno-unused-parameter \
            -Wno-unused-variable \
            -Wno-unused-function

CCFLAGS := -std=c17 \
           -MMD -MP \
           -Wall -Wextra \
           -include $(SOURCE_DIR)/prelude.h \
           $(CCWARNS) \
           $(shell wx-config $(WXCCFLAGS))

CXXFLAGS := -std=c++20 -fpermissive \
            -MMD -MP \
            -Wall -Wextra \
            -include $(SOURCE_DIR)/prelude.h \
            $(CXXWARNS) \
            $(shell wx-config $(WXCXXFLAGS))

DEFINES := -DUNICODE -D_UNICODE -DWIN32_LEAN_AND_MEAN

INCLUDES := -Isrc \
            -I$(RESOURCE_DIR)

LDFLAGS := -static -static-libgcc -static-libstdc++ \
           -mwindows -lmsvcrt -lxdelta3 -llzma -lz -lxxhash \
           -L$(LIB_DIR) $(shell wx-config $(WXLDFLAGS))

ifeq ($(DEBUG), 1)
DEFINES    += -DDEBUG
CCFLAGS    += -g -O0
CXXFLAGS   += -g -O0
else
DEFINES    += -DRELEASE
CCFLAGS    += -O3 -ffunction-sections -fdata-sections
CXXFLAGS   += -O3 -ffunction-sections -fdata-sections
LDFLAGS    += -s -Wl,--gc-sections
endif

################################################################################

SOURCES := $(shell find $(SOURCE_DIR) -type f \( -name "*.cpp" -o -name "*.c" \) )
OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_OBJ_DIR)/%.o,$(SOURCES))
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_OBJ_DIR)/%.o,$(OBJECTS))

RESOURCES := $(shell find $(RESOURCE_DIR) -type f)

################################################################################

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) $(BUILD_OBJ_DIR)/app.rc.o $(BUILD_OBJ_DIR)/embed.o
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(LDFLAGS)
ifneq ($(DEBUG), 1)
	upx $@
endif

$(BUILD_OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_TOOLS_DIR)/%: tools/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $<

$(BUILD_OBJ_DIR)/%.rc.o: $(SOURCE_DIR)/%.rc $(RESOURCES)
	@mkdir -p $(dir $@)
	windres $(DEFINES) $(INCLUDES) $< $@

$(BUILD_OBJ_DIR)/embed.o: $(BUILD_OBJ_DIR)/embed.g.cpp $(SOURCE_DIR)/embed.h $(RESOURCES)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_OBJ_DIR)/embed.g.cpp: $(BUILD_TOOLS_DIR)/embed $(SOURCE_DIR)/embed.h $(RESOURCES)
	@mkdir -p $(dir $@)
	$(BUILD_TOOLS_DIR)/embed $(SOURCE_DIR)/embed.h $@

clean:
	rm -rf $(BUILD_DIR)

-include $(OBJECTS:.o=.d)
