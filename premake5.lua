project "c_json"
	location "."
	kind "StaticLib"
	language "C"
	
	files { "**.c" }
	includedirs { "../_vendor", ".", ".." }

	links { "m", "c_log" }