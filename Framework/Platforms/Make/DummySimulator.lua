-- NaoTH controller for the logfile based "simulator"
project "DummySimulator"
  kind "StaticLib"
  language "C++"
  
  includedirs {
    "../Source/"
  }
  
  files {
    "../Source/DummySimulator/**.cpp",
    "../Source/DummySimulator/**.h"
  }
  
  links {
    "glib-2.0",
    "gio-2.0",
    "gobject-2.0",
    "gmodule-2.0",
    "gthread-2.0",
    "protobuf",
    "fftw3"
  }
  
  targetname "dummysimulator"
