# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark

# Include any dependencies generated for this target.
include CMakeFiles/Benchmark.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Benchmark.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Benchmark.dir/flags.make

CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o: CMakeFiles/Benchmark.dir/flags.make
CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o: Benchmark/Benchmarks.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o -c /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Benchmark/Benchmarks.cpp

CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Benchmark/Benchmarks.cpp > CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.i

CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Benchmark/Benchmarks.cpp -o CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.s

CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o.requires:

.PHONY : CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o.requires

CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o.provides: CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o.requires
	$(MAKE) -f CMakeFiles/Benchmark.dir/build.make CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o.provides.build
.PHONY : CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o.provides

CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o.provides.build: CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o


CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o: CMakeFiles/Benchmark.dir/flags.make
CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o: Source/Implementation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o -c /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Source/Implementation.cpp

CMakeFiles/Benchmark.dir/Source/Implementation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Benchmark.dir/Source/Implementation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Source/Implementation.cpp > CMakeFiles/Benchmark.dir/Source/Implementation.cpp.i

CMakeFiles/Benchmark.dir/Source/Implementation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Benchmark.dir/Source/Implementation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Source/Implementation.cpp -o CMakeFiles/Benchmark.dir/Source/Implementation.cpp.s

CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o.requires:

.PHONY : CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o.requires

CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o.provides: CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o.requires
	$(MAKE) -f CMakeFiles/Benchmark.dir/build.make CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o.provides.build
.PHONY : CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o.provides

CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o.provides.build: CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o


# Object files for target Benchmark
Benchmark_OBJECTS = \
"CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o" \
"CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o"

# External object files for target Benchmark
Benchmark_EXTERNAL_OBJECTS =

Benchmark: CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o
Benchmark: CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o
Benchmark: CMakeFiles/Benchmark.dir/build.make
Benchmark: deps/lib/libbenchmark.a
Benchmark: deps/lib/libbenchmark_main.a
Benchmark: CMakeFiles/Benchmark.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Benchmark"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Benchmark.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Benchmark.dir/build: Benchmark

.PHONY : CMakeFiles/Benchmark.dir/build

CMakeFiles/Benchmark.dir/requires: CMakeFiles/Benchmark.dir/Benchmark/Benchmarks.cpp.o.requires
CMakeFiles/Benchmark.dir/requires: CMakeFiles/Benchmark.dir/Source/Implementation.cpp.o.requires

.PHONY : CMakeFiles/Benchmark.dir/requires

CMakeFiles/Benchmark.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Benchmark.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Benchmark.dir/clean

CMakeFiles/Benchmark.dir/depend:
	cd /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/CMakeFiles/Benchmark.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Benchmark.dir/depend

