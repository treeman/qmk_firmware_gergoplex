MOUSEKEY_ENABLE = yes
LEADER_ENABLE = yes
MOUSEKEY_ENABLE = yes
UNICODE_ENABLE = yes
WPM_ENABLE = yes

# Combos!
VPATH +=  keyboards/gboards/

# Saves a bunch of memory
EXTRAFLAGS += -flto
CONSOLE_ENABLE = false
EXTRAKEY_ENABLE = false
VERBOSE = no
DEBUG_MATRIX_SCAN_RATE  = no
DEBUG_MATRIX = no

# A bunch of stuff that you shouldn't touch unless you
# know what you're doing.
#
# No touchy, capiche?
SRC += matrix.c i2c_master.c
ifeq ($(strip $(DEBUG_MATRIX)), yes)
    OPT_DEFS += -DDEBUG_MATRIX
endif

