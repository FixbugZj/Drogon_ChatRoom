cmake_minimum_required(VERSION 3.5)
project(chat CXX)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)
if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Do nothing
elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
elseif (HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 17)
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cc)

# cryptopp
# 指定 Crypto++ 的头文件路径
include_directories(/usr/include/cryptopp)

# 指定 Crypto++ 的库文件路径
link_directories(/usr/lib/x86_64-linux-gnu)

# 链接 Crypto++ 库
target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp)

find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)




if (CMAKE_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "c++17 or higher is required")
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else ()
    message(STATUS "use c++20")
endif ()


#aux_source_directory(controllers CTL_SRC)
file(GLOB_RECURSE CTL_SRC "controllers/*.cc")

aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)
aux_source_directory(common COMMON_SRC)
aux_source_directory(service SVC_SRC)
aux_source_directory(utils UTILS_SRC)


drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
                    ${CMAKE_CURRENT_BINARY_DIR})


target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${COMMON_SRC}
               ${CTL_SRC}
               ${SVC_SRC}
               ${UTILS_SRC}
               ${FILTER_SRC}
               ${PLUGIN_SRC}
               ${MODEL_SRC})



add_subdirectory(test)

file(COPY config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})




