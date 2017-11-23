-- An example project generator; see _example.lua for action description

-- 
-- The project generation function, attached to the action in _example.lua.
-- By now, premake.generate() has created the project file using the name
-- provided in _example.lua, and redirected input to this new file.
--
	local qc = premake.qtcreator27
	
  
  function qc.files(prj)
  
    for _, file in ipairs(prj.files) do
      _p(file)
    end
  end
  
  function qc.includes(prj)
  
    -- add system includes
    for _, inc in ipairs(prj.sysincludedirs) do
      _p(inc)
    end
  
    -- add project includes
    for _, inc in ipairs(prj.includedirs) do
      _p(inc)
    end
  end
  
  function qc.defines(prj)
    _p("// ADD PREDEFINED MACROS HERE!")
    _p("")
    _p("// the following defines are autogenerated by \"premake4 qtcreator\"")
    for _, def in ipairs(prj.defines) do
      _p(def)
    end
  end

