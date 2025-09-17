cmake_minimum_required(VERSION 3.31)
project(GSP_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(GSP_Project main.cpp
        Skelet/Network.cpp
        Skelet/Network.h
        Skelet/Line.cpp
        Skelet/Line.h
        Skelet/Direction.cpp
        Skelet/Direction.h
        Skelet/BusStop.cpp
        Skelet/BusStop.h
        Skelet/Location.cpp
        Skelet/Location.h
        Filteri/Filter.h
        Filteri/BuiltInFilters/ZoneFilter.cpp
        Filteri/BuiltInFilters/ZoneFilter.h
        Filteri/BuiltInFilters/NumberFilter.cpp
        Filteri/BuiltInFilters/NumberFilter.h
        Filteri/BuiltInFilters/StopCountFilter.cpp
        Filteri/BuiltInFilters/StopCountFilter.h
        Functionality.cpp
        Functionality.h
        Generator/Generator.h
        Generator/BuiltInGenerators/CGenerator.cpp
        Generator/BuiltInGenerators/CGenerator.h
        Generator/BuiltInGenerators/LGenerator.cpp
        Generator/BuiltInGenerators/LGenerator.h
        Exception/Exception.h
        Exception/BuiltInExceptions/FileCantBeOpenException.h
        Exception/BuiltInExceptions/InvalidInputFormatException.h
        Exception/BuiltInExceptions/WrongDirectionException.h
        Exception/BuiltInExceptions/LineNotExists.h
        Exception/BuiltInExceptions/StationNotExists.h
)
