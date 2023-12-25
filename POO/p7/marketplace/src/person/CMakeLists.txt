# CMakeLists.txt for the 'person' subdirectory

# Define the list of source files for the 'person' library
set(person_sources
    person.cc
    person.h
)

# Create a library from the source files
add_library(person ${person_sources})

# Include the current directory for header files
target_include_directories(person PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

