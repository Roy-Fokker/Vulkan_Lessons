# Find the fmtlib package installed by vcpkg.
# fmtlib can be installed by running following command in shell
# => vcpkg install fmt cppitertools
find_package(fmt REQUIRED)

# Define the executable we want to build.
add_executable(lesson_1)

# Source files used to build lesson_1.exe
target_sources(lesson_1
    PRIVATE
        main.cpp
        window.cpp
        window.hpp)

# Tell the build system we have to use C++17 Standard
target_compile_features(lesson_1
    PRIVATE
        cxx_std_17)

# Provide some extra compiler options IF the compiler is MSVC
# - /W3 : enable all the warnings
# - /permissive- : tell msvc to work in conformance mode
# - /Zc:__cpluspluc : tell msvc to report C++ version correctly
# - /std:c++17 : tell msvc to use Standard C++ 17. CMake passes flag incorrectly
target_compile_options(lesson_1
    PRIVATE 
        $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /Zc:__cplusplus /std:c++17>)

# Provide some extra linker options IF the compiler is MSVC
# /ENTRY:mainCRTStartup : tell msvc we want to start in main() function.
target_link_options(lesson_1
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/ENTRY:mainCRTStartup>)

# Define "DEBUG" if the Build type is Debug
# Define only for MSVC to silence deprecated header warnings
target_compile_definitions(lesson_1
    PRIVATE
        UNICODE _UNICODE
        $<$<CONFIG:Debug>:DEBUG _DEBUG>
        $<$<CXX_COMPILER_ID:MSVC>:_SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING>)

# Add the fmt library to linker lib path for lesson_1 executable.
target_link_libraries(lesson_1 
    PRIVATE 
        fmt::fmt)
