project "c_json"
	location "."
	kind "StaticLib"
	language "C"
	
	files { "**.c", "**.h" }
	includedirs { "../_vendor", ".", ".." }

	links { "c_mem" }

	filter "configurations:Debug"
		defines "CM_DEBUG"