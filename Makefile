APP_NAME = GSEditor

ifeq ($(DEBUG),1)
BUILD_TARGET := debug
else
BUILD_TARGET := release
endif

ifeq ($(SOURCE_WATCHER),1)
WORK_DIR := $(shell cygpath -m $(CURDIR))/
else
WORK_DIR :=
endif

SOURCE_DIR   := $(WORK_DIR)src
RESOURCE_DIR := $(WORK_DIR)res
BUILD_DIR    := $(WORK_DIR)build
TOOLS_DIR    := $(WORK_DIR)tools

BUILD_TARGET_DIR := $(BUILD_DIR)/$(BUILD_TARGET)
BUILD_OBJ_DIR    := $(BUILD_TARGET_DIR)/obj
BUILD_TOOLS_DIR  := $(BUILD_TARGET_DIR)/tools

################################################################################

ifeq ($(DEBUG),1)
WXCCFLAGS  := --cflags --unicode --static --debug
WXCXXFLAGS := --cxxflags --unicode --static --debug
WXLDFLAGS  := --libs --unicode --static
else
WXCCFLAGS  := --cflags --unicode --static
WXCXXFLAGS := --cxxflags --unicode --static
WXLDFLAGS  := --libs --unicode --static
endif

WARNS     := -Wno-comment \
             -Wno-parentheses \
             -Wno-unused-parameter \
             -Wno-unused-variable \
             -Wno-unused-function

DEFINES   := -DUNICODE -D_UNICODE -DWIN32_LEAN_AND_MEAN

INCLUDES  := -I$(SOURCE_DIR) -I$(RESOURCE_DIR) -I$(SOURCE_DIR)/third_party

LIBS      := $(SOURCE_DIR)/third_party/xdelta3/mingw-w64-x86_64-libxdelta3.a

CCFLAGS   := -std=c17 -MMD -MP -Wall -Wextra $(WARNS) $(shell wx-config $(WXCCFLAGS))
CXXFLAGS  := -std=c++23 -fpermissive -MMD -MP -Wall -Wextra $(WARNS) $(shell wx-config $(WXCXXFLAGS))
LDFLAGS   := -mwindows $(LIBS) -llzma -lz -lxxhash $(shell wx-config $(WXLDFLAGS))
TOOLFLAGS := -std=c++23 $(LIBS) $(INCLUDES)

ifeq ($(DEBUG),1)
DEFINES  += -DDEBUG
CCFLAGS  += -g -O0
CXXFLAGS += -g -O0
else
DEFINES  += -DRELEASE
CCFLAGS  += -O3 -ffunction-sections -fdata-sections
CXXFLAGS += -O3 -ffunction-sections -fdata-sections
LDFLAGS  += -static -static-libgcc -static-libstdc++ -s -Wl,--gc-sections
endif

################################################################################

.PHONY: all clean source-watcher

################################################################################

# App

all: $(BUILD_TARGET_DIR)/bin/$(APP_NAME).exe $(BUILD_TARGET_DIR)/bin/ThirdPartyNotices.txt

SOURCES := $(shell find $(SOURCE_DIR) -type f \( -name "*.cpp" -o -name "*.c" \))

OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_OBJ_DIR)/%.o,$(SOURCES))
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_OBJ_DIR)/%.o,$(OBJECTS))
OBJECTS += $(BUILD_OBJ_DIR)/resources.rc.o
OBJECTS += $(BUILD_OBJ_DIR)/base/resources_embed.g.o

RESOURCES := $(shell find $(RESOURCE_DIR) -type f)

$(BUILD_TARGET_DIR)/bin/$(APP_NAME).exe: $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(LDFLAGS)
ifneq ($(DEBUG),1)
	upx $@
endif

$(BUILD_TARGET_DIR)/bin/ThirdPartyNotices.txt: $(RESOURCE_DIR)/third_party_notices.txt
ifneq ($(DEBUG),1)
	cp $(RESOURCE_DIR)/third_party_notices.txt $@
endif

$(BUILD_OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_OBJ_DIR)/%.g.o: $(BUILD_OBJ_DIR)/%.g.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_OBJ_DIR)/%.rc.o: $(SOURCE_DIR)/%.rc $(RESOURCES)
	@mkdir -p $(dir $@)
	windres $(DEFINES) $(INCLUDES) -D_IGNORE_EMBED $< $@

$(BUILD_OBJ_DIR)/base/resources_embed.g.cpp: $(BUILD_TOOLS_DIR)/embed_generator $(SOURCE_DIR)/base/resources_embed.h $(RESOURCES)
	@mkdir -p $(dir $@)
	$(BUILD_TOOLS_DIR)/embed_generator $(SOURCE_DIR)/base/resources_embed.h $@

-include $(OBJECTS:.o=.d)

################################################################################

# Tools

$(BUILD_TOOLS_DIR)/%: $(TOOLS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(TOOLFLAGS) -o $@ $<

################################################################################

ifeq ($(DEBUG)$(SOURCE_WATCHER),11)
source-watcher: $(BUILD_TOOLS_DIR)/source_watcher
	@mkdir -p $(BUILD_TARGET_DIR)/bin
	@$(BUILD_TOOLS_DIR)/source_watcher \
		--workspace-dir $(WORK_DIR) \
		--output-dir $(BUILD_DIR) \
		--cxx $(shell cygpath -m $(shell which $(CXX))) \
		--cc $(shell cygpath -m $(shell which $(CC))) \
		--cxx-flags "\"$(CXXFLAGS) $(DEFINES) $(INCLUDES)\"" \
		--cc-flags "\"$(CCFLAGS) $(DEFINES) $(INCLUDES)\""
else
source-watcher:
	@$(MAKE) source-watcher DEBUG=1 SOURCE_WATCHER=1
endif

################################################################################

clean:
	rm -rf .vscode/c_cpp_properties.json .vscode/compile_commands.json
	rm -rf $(BUILD_DIR)
