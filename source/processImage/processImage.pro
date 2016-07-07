TOP_DIR = ../../
SCRIPT_DIR = $$(TOP_DIR)/scripts

include(processImage.pri)

INSTALL_DIR     = $${TOP_DIR}/install
INSTALL_BIN_DIR = $${INSTALL_DIR}/bin
INSTALL_LIB_DIR = $${INSTALL_DIR}/lib
INSTALL_INC_DIR = $${INSTALL_DIR}/include
INSTALL_DOC_DIR = $${INSTALL_DIR}/doc

TEMPLATE = lib                 # build a library
CONFIG  += staticlib           # build a static library
CONFIG  += debug_and_release   # include both debug and release targets
CONFIG  += build_all           # build both debug and release by default

DESTDIR  = $$TEMPDIR/$$LIBDIR   # LIBDIR is declared in project include file
MOC_DIR  = $$TEMPDIR/moc
UI_DIR   = $$TEMPDIR/uic
RCC_DIR  = $$TEMPDIR/rcc
build_pass:CONFIG(debug, debug|release) {
  OBJECTS_DIR = $$TEMPDIR/obj/debug
} else {
  build_pass:CONFIG(release, debug|release) {
    OBJECTS_DIR = $$TEMPDIR/obj/release
  }
}

INSTALL_DIR     = $${TOP_DIR}/install
INSTALL_BIN_DIR = $${INSTALL_DIR}/bin
INSTALL_LIB_DIR = $${INSTALL_DIR}/lib
INSTALL_INC_DIR = $${INSTALL_DIR}/include
INSTALL_DOC_DIR = $${INSTALL_DIR}/doc

build_pass:CONFIG(debug, debug|release) {
  win32: TARGET = $$join(BASENAME,,,d)
} else {
  build_pass:CONFIG(release, debug|release) {
    win32: TARGET = $$BASENAME
  }
}

win32 {
  allclean.depends  = distclean vsclean
  vsclean.commands  = rm -f *.vcproj*          
  QMAKE_EXTRA_TARGETS += vsclean
}
unix {
  allclean.commands = rm -rf $$TEMPDIR  
}
QMAKE_EXTRA_TARGETS += allclean

target.path   = $$INSTALL_LIB_DIR
headers.files = $$HEADERS
headers.path  = $$INSTALL_INC_DIR/$$PROJNAME
INSTALLS += target
INSTALLS += headers
contains(TEMPLATE,vclib)|contains(TEMPLATE,vcapp){
   QMAKE_POST_LINK += nmake install
}