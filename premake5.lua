project "c_json"
	location "."
	kind "StaticLib"
	language "C"
	
	files { "**.c" }
	includedirs { "../_vendor", ".", ".." }

	links { "c_log" }

	filter "system:linux"
		links { "m" }