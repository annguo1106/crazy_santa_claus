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

# Include any dependencies generated for this target.
include src/CMakeFiles/ICG_2024_HW3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/ICG_2024_HW3.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/ICG_2024_HW3.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/ICG_2024_HW3.dir/flags.make

src/CMakeFiles/ICG_2024_HW3.dir/main.cpp.obj: src/CMakeFiles/ICG_2024_HW3.dir/flags.make
src/CMakeFiles/ICG_2024_HW3.dir/main.cpp.obj: src/CMakeFiles/ICG_2024_HW3.dir/includes_CXX.rsp
src/CMakeFiles/ICG_2024_HW3.dir/main.cpp.obj: C:/D/NYCUCS/third\ grade\ course/first\ semester/ICG/crazy_santa_claus/src/main.cpp
src/CMakeFiles/ICG_2024_HW3.dir/main.cpp.obj: src/CMakeFiles/ICG_2024_HW3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/ICG_2024_HW3.dir/main.cpp.obj"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ICG_2024_HW3.dir/main.cpp.obj -MF CMakeFiles/ICG_2024_HW3.dir/main.cpp.obj.d -o CMakeFiles/ICG_2024_HW3.dir/main.cpp.obj -c "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src/main.cpp"

src/CMakeFiles/ICG_2024_HW3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ICG_2024_HW3.dir/main.cpp.i"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src/main.cpp" > CMakeFiles/ICG_2024_HW3.dir/main.cpp.i

src/CMakeFiles/ICG_2024_HW3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ICG_2024_HW3.dir/main.cpp.s"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src/main.cpp" -o CMakeFiles/ICG_2024_HW3.dir/main.cpp.s

src/CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.obj: src/CMakeFiles/ICG_2024_HW3.dir/flags.make
src/CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.obj: src/CMakeFiles/ICG_2024_HW3.dir/includes_CXX.rsp
src/CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.obj: C:/D/NYCUCS/third\ grade\ course/first\ semester/ICG/crazy_santa_claus/src/stb_image.cpp
src/CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.obj: src/CMakeFiles/ICG_2024_HW3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.obj"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.obj -MF CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.obj.d -o CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.obj -c "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src/stb_image.cpp"

src/CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.i"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src/stb_image.cpp" > CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.i

src/CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.s"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src/stb_image.cpp" -o CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.s

src/CMakeFiles/ICG_2024_HW3.dir/shader.cpp.obj: src/CMakeFiles/ICG_2024_HW3.dir/flags.make
src/CMakeFiles/ICG_2024_HW3.dir/shader.cpp.obj: src/CMakeFiles/ICG_2024_HW3.dir/includes_CXX.rsp
src/CMakeFiles/ICG_2024_HW3.dir/shader.cpp.obj: C:/D/NYCUCS/third\ grade\ course/first\ semester/ICG/crazy_santa_claus/src/shader.cpp
src/CMakeFiles/ICG_2024_HW3.dir/shader.cpp.obj: src/CMakeFiles/ICG_2024_HW3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/ICG_2024_HW3.dir/shader.cpp.obj"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ICG_2024_HW3.dir/shader.cpp.obj -MF CMakeFiles/ICG_2024_HW3.dir/shader.cpp.obj.d -o CMakeFiles/ICG_2024_HW3.dir/shader.cpp.obj -c "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src/shader.cpp"

src/CMakeFiles/ICG_2024_HW3.dir/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ICG_2024_HW3.dir/shader.cpp.i"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src/shader.cpp" > CMakeFiles/ICG_2024_HW3.dir/shader.cpp.i

src/CMakeFiles/ICG_2024_HW3.dir/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ICG_2024_HW3.dir/shader.cpp.s"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src/shader.cpp" -o CMakeFiles/ICG_2024_HW3.dir/shader.cpp.s

src/CMakeFiles/ICG_2024_HW3.dir/object.cpp.obj: src/CMakeFiles/ICG_2024_HW3.dir/flags.make
src/CMakeFiles/ICG_2024_HW3.dir/object.cpp.obj: src/CMakeFiles/ICG_2024_HW3.dir/includes_CXX.rsp
src/CMakeFiles/ICG_2024_HW3.dir/object.cpp.obj: C:/D/NYCUCS/third\ grade\ course/first\ semester/ICG/crazy_santa_claus/src/object.cpp
src/CMakeFiles/ICG_2024_HW3.dir/object.cpp.obj: src/CMakeFiles/ICG_2024_HW3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/ICG_2024_HW3.dir/object.cpp.obj"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ICG_2024_HW3.dir/object.cpp.obj -MF CMakeFiles/ICG_2024_HW3.dir/object.cpp.obj.d -o CMakeFiles/ICG_2024_HW3.dir/object.cpp.obj -c "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src/object.cpp"

src/CMakeFiles/ICG_2024_HW3.dir/object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ICG_2024_HW3.dir/object.cpp.i"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src/object.cpp" > CMakeFiles/ICG_2024_HW3.dir/object.cpp.i

src/CMakeFiles/ICG_2024_HW3.dir/object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ICG_2024_HW3.dir/object.cpp.s"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src/object.cpp" -o CMakeFiles/ICG_2024_HW3.dir/object.cpp.s

# Object files for target ICG_2024_HW3
ICG_2024_HW3_OBJECTS = \
"CMakeFiles/ICG_2024_HW3.dir/main.cpp.obj" \
"CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.obj" \
"CMakeFiles/ICG_2024_HW3.dir/shader.cpp.obj" \
"CMakeFiles/ICG_2024_HW3.dir/object.cpp.obj"

# External object files for target ICG_2024_HW3
ICG_2024_HW3_EXTERNAL_OBJECTS =

src/ICG_2024_HW3.exe: src/CMakeFiles/ICG_2024_HW3.dir/main.cpp.obj
src/ICG_2024_HW3.exe: src/CMakeFiles/ICG_2024_HW3.dir/stb_image.cpp.obj
src/ICG_2024_HW3.exe: src/CMakeFiles/ICG_2024_HW3.dir/shader.cpp.obj
src/ICG_2024_HW3.exe: src/CMakeFiles/ICG_2024_HW3.dir/object.cpp.obj
src/ICG_2024_HW3.exe: src/CMakeFiles/ICG_2024_HW3.dir/build.make
src/ICG_2024_HW3.exe: extern/glfw/src/libglfw3.a
src/ICG_2024_HW3.exe: extern/glm/glm/libglm.a
src/ICG_2024_HW3.exe: extern/glad/libglad.a
src/ICG_2024_HW3.exe: src/CMakeFiles/ICG_2024_HW3.dir/linkLibs.rsp
src/ICG_2024_HW3.exe: src/CMakeFiles/ICG_2024_HW3.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ICG_2024_HW3.exe"
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && "C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/ICG_2024_HW3.dir/objects.a
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/ar.exe qc CMakeFiles/ICG_2024_HW3.dir/objects.a @CMakeFiles/ICG_2024_HW3.dir/objects1.rsp
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && C:/w64devkit/bin/g++.exe -g -Wl,--whole-archive CMakeFiles/ICG_2024_HW3.dir/objects.a -Wl,--no-whole-archive -o ICG_2024_HW3.exe -Wl,--out-implib,libICG_2024_HW3.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/ICG_2024_HW3.dir/linkLibs.rsp

# Rule to build all files generated by this target.
src/CMakeFiles/ICG_2024_HW3.dir/build: src/ICG_2024_HW3.exe
.PHONY : src/CMakeFiles/ICG_2024_HW3.dir/build

src/CMakeFiles/ICG_2024_HW3.dir/clean:
	cd "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" && $(CMAKE_COMMAND) -P CMakeFiles/ICG_2024_HW3.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/ICG_2024_HW3.dir/clean

src/CMakeFiles/ICG_2024_HW3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus" "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/src" "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build" "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src" "C:/D/NYCUCS/third grade course/first semester/ICG/crazy_santa_claus/build/src/CMakeFiles/ICG_2024_HW3.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : src/CMakeFiles/ICG_2024_HW3.dir/depend

