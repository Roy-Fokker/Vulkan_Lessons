## SPDX-License-Identifier: MIT

# Root Cmake file.
# Sets up overall project configuration.

# Require that minimum CMake version is 3.15.0
cmake_minimum_required(VERSION 3.15.0)

# Ensure that VCPKG toolchain is loaded by CMake. 
# Allowing us to use the packages installed by vcpkg.
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

