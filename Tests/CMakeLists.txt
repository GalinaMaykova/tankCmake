


#include(FetchContent)
#FetchContent_Declare(
#googletest
#URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#)
#### For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)

include_directories(${tankCmake_SOURCE_DIR}/Core)

add_executable (Tank "main.cpp") # "test_move.cpp" "test_rotate.cpp")


#set(CORE_TEST_SOURCES
#test_move.cpp
#test_rotate.cpp
#main.cpp
#)
