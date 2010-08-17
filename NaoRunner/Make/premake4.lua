solution "NaoRunner"
  kind "StaticLib"
  language "C++"
  targetdir "../Lib/"
  
  platforms {"Native"}
  configurations {"Release","Debug"}
  
  if os.is("windows") then
	defines {"WIN32", "NOMINMAX"}
  end
  
      -- debug configuration
  configuration { "Debug" }
    defines { "DEBUG" }
    flags { "Symbols" }
	
  -- store the makefiles the Make/ directory
  location "."
  
  dofile "Interface.lua"
  dofile "Webots.lua"
  dofile "SimSpark.lua"