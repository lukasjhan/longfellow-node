cmake_minimum_required(VERSION 3.18)
project(longfellow_node LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# cmake-js가 넘겨주는 Node 관련 include/src
include_directories(${CMAKE_JS_INC})

# node-addon-api 헤더 경로를 Node로부터 얻어 include
execute_process(
  COMMAND node -p "require('node-addon-api').include"
  OUTPUT_VARIABLE NAPI_INC
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REPLACE "\"" "" NAPI_INC ${NAPI_INC})
include_directories(${NAPI_INC})
add_definitions(-DNAPI_VERSION=8)

# Longfellow 설치 경로
set(LF_INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/third_party/longfellow-zk/install")
if(NOT DEFINED LF_INSTALL)
  message(FATAL_ERROR "Set -DLF_INSTALL=${CMAKE_CURRENT_SOURCE_DIR}/third_party/longfellow-zk/install")
endif()

include_directories(${LF_INSTALL}/include)

# 설치된 lib 이름을 찾습니다. install/lib 안 내용을 보고 이름을 맞추세요.
# 아래 NAMES 리스트는 예시입니다. 실제 파일명(.a/.so/.dylib/.lib)을 확인해 넣으세요.
find_library(LFZK_LIB
  NAMES libmdoc_static.a
  PATHS ${LF_INSTALL}/lib
  NO_DEFAULT_PATH
  REQUIRED
)

add_library(${PROJECT_NAME} SHARED src/addon.cpp ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# 런타임에서 .node 옆의 라이브러리를 찾도록 rpath 설정
if(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    BUILD_RPATH "@loader_path"
    INSTALL_RPATH "@loader_path"
  )
elseif(UNIX)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    BUILD_RPATH "\$ORIGIN"
    INSTALL_RPATH "\$ORIGIN"
  )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_JS_LIB} ${LFZK_LIB})

# 필요 시 OpenSSL/Zstd 등도 찾고 링크(동적 링크 환경에 따라)
find_package(OpenSSL QUIET)
if(OPENSSL_FOUND)
  target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

find_library(ZSTD_LIB zstd)
if(ZSTD_LIB)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${ZSTD_LIB})
endif()
