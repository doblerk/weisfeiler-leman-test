cmake_minimum_required(VERSION 3.10)

# Project name
project(weisfeiler-leman VERSION 1.0 
        				 DESCRIPTION "Weisfeiler Leman graph isomorphism test"
                		 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CSS_STANDARD_REQUIRED True)

# Find Boost libraries
set(BOOST_ROOT "${PROJECT_SOURCE_DIR}/third_party/boost")
set(BOOST_INCLUDEDIR "${PROJECT_SOURCE_DIR}/third_party/boost")
set(BOOST_LIBRARYDIR "${PROJECT_SOURCE_DIR}/third_party/boost/stage/lib")

find_library(BOOST_LIB
	NAMES boost_graph boost_regex
	HINTS ${BOOST_LIBRARYDIR}
)

if (NOT BOOST_LIB)
    message(FATAL_ERROR "Boost library not found in ${BOOST_LIBRARYDIR}")
endif()

# Add the source files
set(SOURCES
	src/main.cpp
	src/WeisfeilerLeman.cpp
	src/RadixSort.cpp
)

# Add the header files
set(HEADERS
	include/WeisfeilerLeman.h
	include/RadixSort.h
)

# Add directories
include_directories(${PROJECT_SOURCE_DIR}/include ${BOOST_INCLUDEDIR})

# Create the executable
add_executable(weisfeiler-leman ${SOURCES} ${HEADERS})

target_link_libraries(weisfeiler-leman 
	PRIVATE
	${BOOST_LIB}
)

# Create an object library for each source file
add_library(weisfeiler_leman STATIC ${PROJECT_SOURCE_DIR}/src/WeisfeilerLeman.cpp ${PROJECT_SOURCE_DIR}/include/WeisfeilerLeman.h)
target_include_directories(weisfeiler_leman PUBLIC ${BOOST_INCLUDEDIR})
target_link_libraries(weisfeiler_leman PUBLIC ${BOOST_LIB})

add_library(radix_sort STATIC ${PROJECT_SOURCE_DIR}/src/RadixSort.cpp ${PROJECT_SOURCE_DIR}/include/RadixSort.h)
target_include_directories(radix_sort PUBLIC ${BOOST_INCLUDEDIR})
target_link_libraries(radix_sort PUBLIC ${BOOST_LIB})