add_subdirectory(common)

add_library(tinyrpc STATIC ${ALL_OBJECT_FILES})

set(TINYRPC_LIBS tinyrpc_common)

set(TINYRPC_THIRDPARTY_LIBS tinyxml2)

target_link_libraries(tinyrpc ${TINYRPC_LIBS} ${TINYRPC_THIRDPARTY_LIBS})
