project(Grafos C)

cmake_minimum_required(VERSION 2.8)

if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "You may use Release and Debug types: ")
	message(STATUS "   cmake -D CMAKE_BUILD_TYPE=Release ../")
	set(CMAKE_BUILD_TYPE Debug)
endif (NOT CMAKE_BUILD_TYPE)

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

set(a "-g -Wextra -Wall -std=gnu99 -pipe -Wshadow -Winit-self")
set(a "${a} -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline")
set(a "${a} -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum")
set(a "${a} -Wswitch-default -Wtraditional-conversion -Wconversion")
set(a "${a} -Wunsafe-loop-optimizations -Wpointer-arith -Wbad-function-cast")
set(a "${a} -Wlogical-op -Waggregate-return -Wstrict-prototypes")
set(a "${a} -Wmissing-prototypes -Wmissing-format-attribute -Wpacked")
set(a "${a} -Wdisabled-optimization -Werror-implicit-function-declaration -lm")
set(CMAKE_C_FLAGS_DEBUG "${a}")

set(CMAKE_C_FLAGS_RELEASE "-O3 -march=native -DHAVE_INLINE -pipe -lm")

SET(CMAKE_EXE_LINKER_FLAGS "-Wl,-O1 -Wl,--as-needed")
           
add_subdirectory(lib)

enable_testing()
add_subdirectory(test)

