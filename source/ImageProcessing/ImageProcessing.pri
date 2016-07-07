OPENCV_DIR = $$(OPENCV_DIR)

INCLUDEPATH *= $$PWD/src
INCLUDEPATH += $$PWD/../
INCLUDEPATH += $$OPENCV_DIR/../../include

PROJNAME = $$basename(PWD)   # name of project
BASENAME = $$PROJNAME        # base name of output file

TEMP = $$PWD/src/$$PROJNAME/*.h     # projdir header files
for(a,TEMP) {
   exists($$a) {
      HEADERS *= $$a
   }
}
TEMP = $$PWD/src/$$PROJNAME/*.cpp   # projdir source files
for(a,TEMP) {
   exists($$a) {
      SOURCES *= $$a
   }
}

TEMPDIR = $$PWD/tmp
LIBDIR  = lib

equals(TEMPLATE, "app") | equals(TEMPLATE, "vcapp") {
  build_pass:CONFIG(debug, debug|release) {
    win32:LIBNAME = $$join(BASENAME,,,d.lib)
  } else {
    build_pass:CONFIG(release, debug|release) {
      win32:LIBNAME = $$join(BASENAME,,,.lib)
    }
  }
  LIBS *= -L$$TEMPDIR/$$LIBDIR               # library directory
  LIBS *= $$LIBNAME                          # library name
  DEPENDPATH *= $$PWD/src
  LIBNAME = ""  # just to be safe
}
