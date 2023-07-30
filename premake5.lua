workspace "BillardAI"
    architecture "x64"    
    
    OutputDir = "%{cfg.architecture}/%{cfg.buildcfg}"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    group "Dependencies"
        include "deps"
    group ""    
    
    include "BillardAI"

