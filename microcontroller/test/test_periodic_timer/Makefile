### For detailled explanations about all the avalaible options,
### please refer to https://github.com/sudar/Arduino-Makefile/blob/master/arduino-mk-vars.md

### don't touch this
CURRENT_DIR       = $(shell basename $(CURDIR))
MAKEFILE_DIR     := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

#ARDUINO_LIBS = Ethernet SPI

### PROJECT_DIR
### This is the path to where you have created/cloned your project
PROJECT_DIR       = $(MAKEFILE_DIR)/../../

#LOCAL_C_SRCS    = $(wildcard src/*.c)
#LOCAL_CPP_SRCS  = $(wildcard src/*.cpp)
#LOCAL_CC_SRCS   = $(wildcard src/*.cc)
#LOCAL_PDE_SRCS  = $(wildcard src/*.pde)
#LOCAL_INO_SRCS  = $(wildcard src/*.ino)
#LOCAL_AS_SRCS   = $(wildcard src/*.S)

### AVR_GCC_VERSION
### Check if the version is equal or higher than 4.9
AVR_GCC_VERSION  := $(shell expr `avr-gcc -dumpversion | cut -f1` \>= 4.9)

### ARDMK_DIR
### Path to the Arduino-Makefile directory.
ARDMK_DIR         = $(PROJECT_DIR)/arduino-mk

### ARDUINO_DIR
### Path to the Arduino application and ressources directory.
ARDUINO_DIR       = $(PROJECT_DIR)/arduino-ide/arduino-1.8.0

### USER_LIB_PATH
### Path to where the your project's libraries are stored.
USER_LIB_PATH     :=  $(realpath $(PROJECT_DIR)/lib)

### BOARD_TAG & BOARD_SUB
### For Arduino IDE 1.0.x
### Only BOARD_TAG is needed. It must be set to the board you are currently using. (i.e uno, mega2560, etc.)
# BOARD_TAG         = mega2560
### For Arduino IDE 1.6.x
### Both BOARD_TAG and BOARD_SUB are needed. They must be set to the board you are currently using. (i.e BOARD_TAG = uno, mega, etc. & BOARD_SUB = atmega2560, etc.)
### Note: for the Arduino Uno, only BOARD_TAG is mandatory and BOARD_SUB can be equal to anything
#BOARD_TAG         = uno
#BOARD_SUB         = atmega328p
BOARD_TAG         = mega
BOARD_SUB         = atmega2560

### AVR_TOOLS_DIR
### Path to the AVR tools directory such as avr-gcc, avr-g++, etc.
AVR_TOOLS_DIR     = /usr

### AVRDDUDE
### Path to avrdude directory.
AVRDDUDE          = /usr/bin/avrdude
AVRDUDE_CONF      = /etc/avrdude.conf

### CFLAGS_STD
CFLAGS_STD        = -std=gnu11

### CXXFLAGS_STD
CXXFLAGS_STD      = -std=gnu++11

### CPPFLAGS
### Flags you might want to set for debugging purpose. Comment to stop.
CXXFLAGS         = -Wall -Wextra

### If avr-gcc -v is higher than 4.9, activate coloring of the output
ifeq "$(AVR_GCC_VERSION)" "1"
    CXXFLAGS += -fdiagnostics-color
endif

### MONITOR_BAUDRATE
### It must be set to Serial baudrate value you are using.
MONITOR_BAUDRATE  = 9600

### MONITOR
### The port your board is connected to. Using an '*' tries all the ports and finds the right one.
MONITOR_PORT      = /dev/ttyACM*

### OBJDIR
### This is were you put the binaries you just compile using 'make'
OBJDIR            = $(PROJECT_DIR)/bin/$(CURRENT_DIR)/$(BOARD_TAG)

### path to Arduino.mk, inside the ARDMK_DIR, don't touch.
include $(ARDMK_DIR)/Arduino.mk

