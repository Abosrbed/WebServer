# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hez1/MyWeb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hez1/MyWeb/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: ../main.cpp
CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hez1/MyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c /home/hez1/MyWeb/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hez1/MyWeb/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hez1/MyWeb/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/socket_control.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/socket_control.cpp.o: ../socket_control.cpp
CMakeFiles/main.dir/socket_control.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hez1/MyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/socket_control.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/socket_control.cpp.o -MF CMakeFiles/main.dir/socket_control.cpp.o.d -o CMakeFiles/main.dir/socket_control.cpp.o -c /home/hez1/MyWeb/socket_control.cpp

CMakeFiles/main.dir/socket_control.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/socket_control.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hez1/MyWeb/socket_control.cpp > CMakeFiles/main.dir/socket_control.cpp.i

CMakeFiles/main.dir/socket_control.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/socket_control.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hez1/MyWeb/socket_control.cpp -o CMakeFiles/main.dir/socket_control.cpp.s

CMakeFiles/main.dir/http/http_conn.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/http/http_conn.cpp.o: ../http/http_conn.cpp
CMakeFiles/main.dir/http/http_conn.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hez1/MyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/http/http_conn.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/http/http_conn.cpp.o -MF CMakeFiles/main.dir/http/http_conn.cpp.o.d -o CMakeFiles/main.dir/http/http_conn.cpp.o -c /home/hez1/MyWeb/http/http_conn.cpp

CMakeFiles/main.dir/http/http_conn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/http/http_conn.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hez1/MyWeb/http/http_conn.cpp > CMakeFiles/main.dir/http/http_conn.cpp.i

CMakeFiles/main.dir/http/http_conn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/http/http_conn.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hez1/MyWeb/http/http_conn.cpp -o CMakeFiles/main.dir/http/http_conn.cpp.s

CMakeFiles/main.dir/log/log.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/log/log.cpp.o: ../log/log.cpp
CMakeFiles/main.dir/log/log.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hez1/MyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/log/log.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/log/log.cpp.o -MF CMakeFiles/main.dir/log/log.cpp.o.d -o CMakeFiles/main.dir/log/log.cpp.o -c /home/hez1/MyWeb/log/log.cpp

CMakeFiles/main.dir/log/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/log/log.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hez1/MyWeb/log/log.cpp > CMakeFiles/main.dir/log/log.cpp.i

CMakeFiles/main.dir/log/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/log/log.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hez1/MyWeb/log/log.cpp -o CMakeFiles/main.dir/log/log.cpp.s

CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.o: ../CGImysql/sql_connection_pool.cpp
CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hez1/MyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.o -MF CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.o.d -o CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.o -c /home/hez1/MyWeb/CGImysql/sql_connection_pool.cpp

CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hez1/MyWeb/CGImysql/sql_connection_pool.cpp > CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.i

CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hez1/MyWeb/CGImysql/sql_connection_pool.cpp -o CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/socket_control.cpp.o" \
"CMakeFiles/main.dir/http/http_conn.cpp.o" \
"CMakeFiles/main.dir/log/log.cpp.o" \
"CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.cpp.o
main: CMakeFiles/main.dir/socket_control.cpp.o
main: CMakeFiles/main.dir/http/http_conn.cpp.o
main: CMakeFiles/main.dir/log/log.cpp.o
main: CMakeFiles/main.dir/CGImysql/sql_connection_pool.cpp.o
main: CMakeFiles/main.dir/build.make
main: /usr/lib/x86_64-linux-gnu/libmysqlclient.so
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hez1/MyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/hez1/MyWeb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hez1/MyWeb /home/hez1/MyWeb /home/hez1/MyWeb/build /home/hez1/MyWeb/build /home/hez1/MyWeb/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend
