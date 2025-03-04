-- Visual Studio file generator setup --

workspace "dotenv"
    architecture "x64"
    configurations { "Release" }
    startproject "Dotenv_oop"

project "Dotenv_oop"
    kind          "ConsoleApp"
    language      "C++"
    cppdialect    "C++17"
    staticruntime "off"

    outputdir = "%{cfg.buildcfg}"

    targetdir ("%{wks.location}/x64/%{cfg.buildcfg}")
    objdir    ("%{wks.location}/x64/%{cfg.buildcfg}")

    includedirs{ "$(SolutionDir)include" }
    files { 
        "dotenv/dotenv.h",                   
        "test/test.h",                    
        "test/test_oop.cpp"                
    }

    filter { "system:windows", "toolset:msc" }
        systemversion "latest"

    filter "configurations:Release"
        runtime  "Release"
        optimize "on"

project "Dotenv_alt"
    kind          "ConsoleApp"
    language      "C++"
    cppdialect    "C++17"
    staticruntime "off"

    outputdir = "%{cfg.buildcfg}"

    targetdir ("%{wks.location}/x64/%{cfg.buildcfg}")
    objdir    ("%{wks.location}/x64/%{cfg.buildcfg}")

    includedirs{ "$(SolutionDir)include" }
    files { 
        "dotenv/dotenv-alt.h",               
        "test/test.h",                    
        "test/test_alt.cpp"                
    }

    filter { "system:windows", "toolset:msc" }
        systemversion "latest"

    filter "configurations:Release"
        runtime  "Release"
        optimize "on"

newaction {
    trigger     = "copyenv",
    description = "Copy .env file to the output directories",
    execute     = function ()
        os.copyfile(".env", "x64/Release/.env")
        print("Copied .env to x64/Release/")
    end
}
