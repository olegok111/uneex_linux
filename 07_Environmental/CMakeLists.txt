enable_testing()
cmake_minimum_required(VERSION 3.20)
project(rhasher C)

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

add_test(NAME GenerateInfile
    COMMAND dd if=/dev/random of=file.in count=1
)
set_tests_properties(GenerateInfile PROPERTIES
    FIXTURES_SETUP Infile
)

add_test(NAME Generate_md5
    COMMAND bash -c "md5sum file.in | grep -Po '^\\S+' > file.md5"
)
set_tests_properties(Generate_md5 PROPERTIES
    FIXTURES_SETUP md5
    FIXTURES_REQUIRED Infile
)

add_test(NAME Generate_sha1
    COMMAND bash -c "sha1sum file.in | grep -Po '^\\S+' > file.sha1"
)
set_tests_properties(Generate_sha1 PROPERTIES
    FIXTURES_SETUP sha1
    FIXTURES_REQUIRED Infile
)

function(rhasher_test hash_type arg1 arg2)
    set(testname RHasher_${arg1})
    add_test(NAME ${testname}
        COMMAND bash -c "echo ${arg1} ${arg2} | ./rhasher | grep -Po '[^\\s>]+' > ${testname}.out && cmp file.${hash_type} ${testname}.out"
    )
    set_tests_properties(${testname} PROPERTIES
        FAIL_REGULAR_EXPRESSION differ
        FIXTURES_REQUIRED ${hash_type})
endfunction()

rhasher_test(md5 MD5 file.in File)
rhasher_test(sha1 SHA1 file.in File)
