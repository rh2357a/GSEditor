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

TARGET := $(BUILD_TARGET_DIR)/bin/GSEditor.exe

################################################################################

ifeq ($(DEBUG), 1)
WXCFLAGS   := --cflags --unicode --static --debug
WXCXXFLAGS := --cxxflags --unicode --static --debug
WXLDFLAGS  := --libs --unicode --static
else
WXCFLAGS   := --cflags --unicode --static
WXCXXFLAGS := --cxxflags --unicode --static
WXLDFLAGS  := --libs --unicode --static
endif

NOWARNS := -Wno-unused-parameter \
           -Wno-unused-variable \
           -Wno-unused-function

CFLAGS := -std=c17 \
          -MMD -MP \
          -Wall -Wextra \
          $(NOWARNS) \
          $(shell wx-config $(WXCFLAGS))

CXXFLAGS := -std=c++20 -fpermissive \
            -MMD -MP \
            -Wall -Wextra \
            -Wno-comment \
            $(NOWARNS) \
            $(shell wx-config $(WXCXXFLAGS))

DEFINES := -DUNICODE -D_UNICODE

INCLUDES := -Isrc \
            -I$(RESOURCE_DIR)

LDFLAGS := -static -static-libgcc -static-libstdc++ \
           -mwindows -lmsvcrt -lxdelta3 -llzma -lz \
           -L$(LIB_DIR) $(shell wx-config $(WXLDFLAGS))

ifeq ($(DEBUG), 1)
DEFINES    += -DDEBUG
CFLAGS     += -g -O0
CXXFLAGS   += -g -O0
else
DEFINES    += -DRELEASE
CFLAGS     += -O3 -ffunction-sections -fdata-sections
CXXFLAGS   += -O3 -ffunction-sections -fdata-sections
LDFLAGS    += -s -Wl,--gc-sections
endif

################################################################################

SOURCES := $(shell find $(SOURCE_DIR) -type f \( -name "*.cpp" -o -name "*.c" -o -name "*.rc" \) )
OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_OBJ_DIR)/%.o,$(SOURCES))
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_OBJ_DIR)/%.o,$(OBJECTS))
OBJECTS := $(patsubst $(SOURCE_DIR)/%.rc,$(BUILD_OBJ_DIR)/%.rc.o,$(OBJECTS))

################################################################################

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) $(BUILD_OBJ_DIR)/core/resources.o
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
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_OBJ_DIR)/%.rc.o: $(SOURCE_DIR)/%.rc
	@mkdir -p $(dir $@)
	windres $(DEFINES) $(INCLUDES) $< $@

$(BUILD_OBJ_DIR)/core/resources.o: $(SOURCE_DIR)/core/resources.cpp $(shell find $(RESOURCE_DIR) -type f)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

-include $(OBJECTS:.o=.d)
