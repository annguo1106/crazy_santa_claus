# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build"

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include extern/glfw/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include extern/glfw/CMakeFiles/uninstall.dir/progress.make

extern/glfw/CMakeFiles/uninstall:
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/extern/glfw" && "C:/Program Files/CMake/bin/cmake.exe" -P "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/extern/glfw/cmake_uninstall.cmake"

uninstall: extern/glfw/CMakeFiles/uninstall
uninstall: extern/glfw/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
extern/glfw/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : extern/glfw/CMakeFiles/uninstall.dir/build

extern/glfw/CMakeFiles/uninstall.dir/clean:
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/extern/glfw" && $(CMAKE_COMMAND) -P CMakeFiles/uninstall.dir/cmake_clean.cmake
.PHONY : extern/glfw/CMakeFiles/uninstall.dir/clean

extern/glfw/CMakeFiles/uninstall.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus" "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/extern/glfw" "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build" "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/extern/glfw" "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/extern/glfw/CMakeFiles/uninstall.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : extern/glfw/CMakeFiles/uninstall.dir/depend
