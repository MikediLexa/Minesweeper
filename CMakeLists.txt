cmake_minimum_required(VERSION 3.23)

# Set some basic project attributes
project (
	Minesweeper
	VERSION 0.1
	DESCRIPTION "Learning to use SDL3 hands on"
	LANGUAGES CXX 
)
	
	
	
# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
	
	
# set the output directory for built objects.
#  This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
#
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")


# This project will output an executable file
add_executable(${PROJECT_NAME} 
	main.cpp
)

if(APPLE)
  set_target_properties(${PROJECT_NAME}  PROPERTIES
    INSTALL_RPATH "@executable_path;@loader_path"
    BUILD_WITH_INSTALL_RPATH TRUE
    MACOSX_RPATH TRUE
  )
elseif(UNIX)
  set_target_properties(${PROJECT_NAME}  PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH TRUE
  )
endif()

# Specify that we want to build SDL_TTF's dependencies
set(SDLTTF_VENDORED ON) 

# Set a variable for our vendor directory
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor") 


# Add the SDL libraries from our submodules
add_subdirectory(${VENDOR_DIR}/SDL) 
#add_subdirectory(${VENDOR_DIR}/SDL_image) 
add_subdirectory(${VENDOR_DIR}/SDL_ttf)


# Create a simple configuration header
configure_file(config.h.in config.h)

# Include the configuration header in the build
target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		"${PROJECT_BINARY_DIR}"
	PRIVATE 
		${CMAKE_SOURCE_DIR}/src
)

# Link to the actual SDL3 library.
target_link_libraries(
  ${PROJECT_NAME} 
  SDL3::SDL3 
#  SDL3_::SDL3_image 
  SDL3_ttf::SDL3_ttf 
)

#Export von Compiler Commands für die IDE
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)