# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\konra\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\182.5107.21\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\konra\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\182.5107.21\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\lab\asd\lista3\zad4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\lab\asd\lista3\zad4\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/zad4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/zad4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/zad4.dir/flags.make

CMakeFiles/zad4.dir/main.cpp.obj: CMakeFiles/zad4.dir/flags.make
CMakeFiles/zad4.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\lab\asd\lista3\zad4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/zad4.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\zad4.dir\main.cpp.obj -c C:\lab\asd\lista3\zad4\main.cpp

CMakeFiles/zad4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zad4.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\lab\asd\lista3\zad4\main.cpp > CMakeFiles\zad4.dir\main.cpp.i

CMakeFiles/zad4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zad4.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\lab\asd\lista3\zad4\main.cpp -o CMakeFiles\zad4.dir\main.cpp.s

# Object files for target zad4
zad4_OBJECTS = \
"CMakeFiles/zad4.dir/main.cpp.obj"

# External object files for target zad4
zad4_EXTERNAL_OBJECTS =

zad4.exe: CMakeFiles/zad4.dir/main.cpp.obj
zad4.exe: CMakeFiles/zad4.dir/build.make
zad4.exe: CMakeFiles/zad4.dir/linklibs.rsp
zad4.exe: CMakeFiles/zad4.dir/objects1.rsp
zad4.exe: CMakeFiles/zad4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\lab\asd\lista3\zad4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable zad4.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\zad4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/zad4.dir/build: zad4.exe

.PHONY : CMakeFiles/zad4.dir/build

CMakeFiles/zad4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\zad4.dir\cmake_clean.cmake
.PHONY : CMakeFiles/zad4.dir/clean

CMakeFiles/zad4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\lab\asd\lista3\zad4 C:\lab\asd\lista3\zad4 C:\lab\asd\lista3\zad4\cmake-build-debug C:\lab\asd\lista3\zad4\cmake-build-debug C:\lab\asd\lista3\zad4\cmake-build-debug\CMakeFiles\zad4.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/zad4.dir/depend

