cmake_minimum_required(VERSION 3.20)
project(rhasher)

find_library(RHASH_LIBRARY
             NAMES rhash
             PATHS /usr/local/lib /usr/lib
            )

find_path(RHASH_INCLUDES rhash.h
           /usr/local/include
           /usr/include
          )

add_executable(rhasher rhasher.c)
target_link_libraries(rhasher ${RHASH_LIBRARY})
target_include_directories(rhasher PUBLIC ${RHASH_INCLUDES})

if(readline)
    message(STATUS "readline ENABLED")

    find_library(READLINE_LIBRARY
             NAMES readline
             PATHS /usr/local/lib /usr/lib
            )

    find_path(READLINE_INCLUDES rhash.h
            /usr/local/include
            /usr/include
            )

    target_link_libraries(rhasher ${READLINE_LIBRARY})
    target_include_directories(rhasher PUBLIC ${READLINE_INCLUDES})
    set(CMAKE_C_FLAGS "-Wall -g -DUNEEX_READLINE")
else()
    message(STATUS "readline DISABLED")
    set(CMAKE_C_FLAGS "-Wall -g")
endif()
