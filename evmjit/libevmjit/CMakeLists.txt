set(TARGET_NAME evmjit)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")
source_group("" FILES ${HEADERS})
source_group("" FILES ${SOURCES})

if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	# Disable rtti for Cache as LLVM has no rtti
	set_source_files_properties(Cache.cpp PROPERTIES COMPILE_FLAGS -fno-rtti)
endif ()

add_library(${TARGET_NAME} ${SOURCES} ${HEADERS})
set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "libs")

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(${TARGET_NAME} ${LLVM_LIBS})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

#install( TARGETS ${EXECUTABLE} ARCHIVE DESTINATION lib LIBRARY DESTINATION lib )
#install( FILES ${HEADERS} DESTINATION include/${EXECUTABLE} )
