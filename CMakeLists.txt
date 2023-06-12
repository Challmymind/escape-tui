cmake_minimum_required(VERSION 3.19)

# Export compile commands for clangd autocompletion server.
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

# Library project.
project(

	# Project name.
	escape-tui

	# Project version.
	VERSION 0.0.1

	# Languges needed to build project.
	LANGUAGES CXX C

	)

# Add library to project.
add_library(${PROJECT_NAME})

# Get all source files.
file(GLOB_RECURSE ESCAPE_TUI_SOURCE src/*cpp)

# Link source files to library,
# Use PRIVATE so sources are only used to build library itself.
target_sources(${PROJECT_NAME} PRIVATE ${ESCAPE_TUI_SOURCE})

# Include global and use PUBLIC so dependent libraries can use it in autocompletion.
target_include_directories(${PROJECT_NAME} PUBLIC inc)

# Link pthread library to library.
target_link_libraries({PROJECT_NAME} PRIVATE pthread)
