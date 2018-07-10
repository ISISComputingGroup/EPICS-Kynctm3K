TOP=..
include $(TOP)/configure/CONFIG
#=======================================

# Install .dbd and .db files
DB += kynctm3k.db
DB += kynctm3k_out_channels.db
DATA += kynctm3k.proto

DBD += keyence.dbd

LIBRARY_IOC += KYNCTM3K

KYNCTM3K_DBD += asyn.dbd
KYNCTM3K_DBD += asubFunctions.dbd

KYNCTM3K_SRCS += keyence.c keyence_impl.cpp

KYNCTM3K_LIBS += $(EPICS_BASE_IOC_LIBS)
KYNCTM3K_LIBS += asyn utilities
KYNCTM3K_LIBS += asubFunctions

#=======================================
include $(TOP)/configure/RULES
