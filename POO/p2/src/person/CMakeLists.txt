add_executable(person-main person-main.cc)
add_library(person person.cc person.h)
target_include_directories(person PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(person-main PUBLIC person)

