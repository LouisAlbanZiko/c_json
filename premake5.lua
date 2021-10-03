project "c_json"
	location "."
	kind "StaticLib"
	language "C"
	
	files { "**.c", "**.h" }
	includedirs { "../_vendor", ".", ".." }

	links { "c_log", "c_mem" }

	filter "system:linux"
		links { "m" }