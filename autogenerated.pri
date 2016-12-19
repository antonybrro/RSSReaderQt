TOP_DIR = $$PWD/.. 
TARGET_DIR = $$TOP_DIR/target 
BIN_DIR = $$TARGET_DIR/bin
LIB_DIR = $$TARGET_DIR/lib
INCLUDE_DIR = $$TARGET_DIR/include
DESTDIR = $$BIN_DIR 

CONFIG(release, debug|release){DEFINES += QT_NO_DEBUG_OUTPUT}

CONFIG (release, debug|release) { TARGET = RCP-IT06_02-2.14 }
CONFIG (debug, debug|release)   { TARGET = RCP-IT06_02-2.14-d }

V_MAJ = 2
V_MIN = 14
V_PAT = 8

unix: { 
VER_MAJ = $${V_MAJ}
VER_MIN = $${V_MIN}
VER_PAT = $${V_PAT}
}

DEFINES += 'VER_MAJ=$$V_MAJ'
DEFINES += 'VER_MIN=$$V_MIN'
DEFINES += 'VER_PAT=$$V_PAT'

INCLUDEPATH += \
	$$INCLUDE_DIR

CONFIG (release, debug|release) {
	LIBS += \ 
	-L$$LIB_DIR/TSP-DP-Widgets/ -lTSP-DP-Widgets-8.0

}
CONFIG (debug, debug|release) {
	LIBS += \ 
	-L$$LIB_DIR/TSP-DP-Widgets/ -lTSP-DP-Widgets-8.0-d 
}
