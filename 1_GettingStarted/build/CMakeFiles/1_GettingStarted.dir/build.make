# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/johan/Documents/Projects/OpenGL/1_GettingStarted

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/build

# Include any dependencies generated for this target.
include CMakeFiles/1_GettingStarted.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/1_GettingStarted.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/1_GettingStarted.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1_GettingStarted.dir/flags.make

CMakeFiles/1_GettingStarted.dir/codegen:
.PHONY : CMakeFiles/1_GettingStarted.dir/codegen

CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.o: CMakeFiles/1_GettingStarted.dir/flags.make
CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.o: /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/EBO.cpp
CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.o: CMakeFiles/1_GettingStarted.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/johan/Documents/Projects/OpenGL/1_GettingStarted/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.o -MF CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.o.d -o CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.o -c /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/EBO.cpp

CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/EBO.cpp > CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.i

CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/EBO.cpp -o CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.s

CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.o: CMakeFiles/1_GettingStarted.dir/flags.make
CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.o: /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/Shader.cpp
CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.o: CMakeFiles/1_GettingStarted.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/johan/Documents/Projects/OpenGL/1_GettingStarted/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.o -MF CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.o.d -o CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.o -c /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/Shader.cpp

CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/Shader.cpp > CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.i

CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/Shader.cpp -o CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.s

CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.o: CMakeFiles/1_GettingStarted.dir/flags.make
CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.o: /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/VAO.cpp
CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.o: CMakeFiles/1_GettingStarted.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/johan/Documents/Projects/OpenGL/1_GettingStarted/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.o -MF CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.o.d -o CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.o -c /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/VAO.cpp

CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/VAO.cpp > CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.i

CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/VAO.cpp -o CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.s

CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.o: CMakeFiles/1_GettingStarted.dir/flags.make
CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.o: /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/VBO.cpp
CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.o: CMakeFiles/1_GettingStarted.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/johan/Documents/Projects/OpenGL/1_GettingStarted/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.o -MF CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.o.d -o CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.o -c /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/VBO.cpp

CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/VBO.cpp > CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.i

CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/VBO.cpp -o CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.s

CMakeFiles/1_GettingStarted.dir/src/main.cpp.o: CMakeFiles/1_GettingStarted.dir/flags.make
CMakeFiles/1_GettingStarted.dir/src/main.cpp.o: /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/main.cpp
CMakeFiles/1_GettingStarted.dir/src/main.cpp.o: CMakeFiles/1_GettingStarted.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/johan/Documents/Projects/OpenGL/1_GettingStarted/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/1_GettingStarted.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1_GettingStarted.dir/src/main.cpp.o -MF CMakeFiles/1_GettingStarted.dir/src/main.cpp.o.d -o CMakeFiles/1_GettingStarted.dir/src/main.cpp.o -c /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/main.cpp

CMakeFiles/1_GettingStarted.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/1_GettingStarted.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/main.cpp > CMakeFiles/1_GettingStarted.dir/src/main.cpp.i

CMakeFiles/1_GettingStarted.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/1_GettingStarted.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/src/main.cpp -o CMakeFiles/1_GettingStarted.dir/src/main.cpp.s

# Object files for target 1_GettingStarted
1_GettingStarted_OBJECTS = \
"CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.o" \
"CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.o" \
"CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.o" \
"CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.o" \
"CMakeFiles/1_GettingStarted.dir/src/main.cpp.o"

# External object files for target 1_GettingStarted
1_GettingStarted_EXTERNAL_OBJECTS =

1_GettingStarted: CMakeFiles/1_GettingStarted.dir/src/EBO.cpp.o
1_GettingStarted: CMakeFiles/1_GettingStarted.dir/src/Shader.cpp.o
1_GettingStarted: CMakeFiles/1_GettingStarted.dir/src/VAO.cpp.o
1_GettingStarted: CMakeFiles/1_GettingStarted.dir/src/VBO.cpp.o
1_GettingStarted: CMakeFiles/1_GettingStarted.dir/src/main.cpp.o
1_GettingStarted: CMakeFiles/1_GettingStarted.dir/build.make
1_GettingStarted: CMakeFiles/1_GettingStarted.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/johan/Documents/Projects/OpenGL/1_GettingStarted/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable 1_GettingStarted"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1_GettingStarted.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1_GettingStarted.dir/build: 1_GettingStarted
.PHONY : CMakeFiles/1_GettingStarted.dir/build

CMakeFiles/1_GettingStarted.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1_GettingStarted.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1_GettingStarted.dir/clean

CMakeFiles/1_GettingStarted.dir/depend:
	cd /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/johan/Documents/Projects/OpenGL/1_GettingStarted /Users/johan/Documents/Projects/OpenGL/1_GettingStarted /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/build /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/build /Users/johan/Documents/Projects/OpenGL/1_GettingStarted/build/CMakeFiles/1_GettingStarted.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/1_GettingStarted.dir/depend

