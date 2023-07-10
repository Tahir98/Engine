workspace "Engine" 
    configurations { "Debug", "Release" , "Dist"}
    platforms "Win64"

project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"

    targetdir "bin/output/%{prj.name}/%{cfg.buildcfg}"
    objdir "bin/int/%{prj.name}/%{cfg.buildcfg}"

    includedirs {
        "Dependencies/GLFW/include",
        "Dependencies/GLAD/include",
        "Dependencies/spdlog/include",
        "Dependencies/GLM",
        "Dependencies/STB",
        "Engine/vendor/ImGui",
        "Engine/src"
    }

    libdirs { 
        "Dependencies/GLFW/lib-vc2022"
    }

    links {
        "glfw3.lib"
    }

    files { "%{prj.name}/**.h", "%{prj.name}/**.c", "%{prj.name}/**.hpp", "%{prj.name}/**.cpp" }

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"RELEASE"}
        optimize "On"

    filter "configurations:Dist"
        defines {"DIST"}
        optimize "On"

    filter { "platforms:Win64" }
        system "Windows"
        cppdialect "C++17"
        systemversion "latest"
        architecture "x86_64"    
        
    --defines { "GRAPHICS_API_OPENGL" }
    defines { "GRAPHICS_API_DIRECTX" }   
        
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    
    targetdir "bin/output/%{prj.name}/%{cfg.buildcfg}"
    objdir "bin/int/%{prj.name}/%{cfg.buildcfg}"
    
    includedirs {
        "Dependencies/GLFW/include",
        "Dependencies/GLAD/include",
        "Dependencies/spdlog/include",
        "Dependencies/STB",
        "Dependencies/GLM",
        "Engine",
        "Engine/src",
        "Engine/vendor/ImGui"
    }

    libdirs { 
        "Dependencies/GLFW/lib-vc2022"
    }
    
    links {
        "Engine", "glfw3.lib"
    }

    files { "%{prj.name}/**.h", "%{prj.name}/**.c", "%{prj.name}/**.hpp", "%{prj.name}/**.cpp"}
    
    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
    
    filter "configurations:Release"
        defines {"RELEASE"}
        optimize "On"
    
    filter "configurations:Dist"
        defines {"DIST"}
        optimize "On"
    
    filter { "platforms:Win64" }
        system "Windows"
        cppdialect "C++17"
        systemversion "latest"
        architecture "x86_64"

    --defines { "GRAPHICS_API_OPENGL" }
    defines { "GRAPHICS_API_DIRECTX" }                    

project "DxProject"
    location "DxProject"
    kind "ConsoleApp"
    language "C++"
    
    targetdir "bin/output/%{prj.name}/%{cfg.buildcfg}"
    objdir "bin/int/%{prj.name}/%{cfg.buildcfg}"
    
    includedirs {
        "Dependencies/GLFW/include",
        "Dependencies/GLAD/include",
        "Dependencies/spdlog/include",
        "Dependencies/STB",
        "Dependencies/GLM",
        "Engine",
        "Engine/src",
        "Engine/vendor/ImGui"
    }

    libdirs { 
        "Dependencies/GLFW/lib-vc2022"
    }
    
    links {
        "Engine", "glfw3.lib"
    }

    files { "%{prj.name}/**.h", "%{prj.name}/**.c", "%{prj.name}/**.hpp", "%{prj.name}/**.cpp"}
    
    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
    
    filter "configurations:Release"
        defines {"RELEASE"}
        optimize "On"
    
    filter "configurations:Dist"
        defines {"DIST"}
        optimize "On"
    
    filter { "platforms:Win64" }
        system "Windows"
        cppdialect "C++17"
        systemversion "latest"
        architecture "x86_64"

     --defines { "GRAPHICS_API_OPENGL" }
    defines { "GRAPHICS_API_DIRECTX" }                             

