include(GoogleTest)

file(GLOB_RECURSE TINYRPC_TEST_SOURCES "*test.cc")

foreach(tinyrpc_test_source ${TINYRPC_TEST_SOURCES})
  # 文件名
  get_filename_component(tinyrpc_test_filename ${tinyrpc_test_source} NAME)
  # 无扩展名
  string(REPLACE ".cc" "" tinyrpc_test_name ${tinyrpc_test_filename})
  
  add_executable(${tinyrpc_test_name} ${tinyrpc_test_source})
  
  target_link_libraries(${tinyrpc_test_name} tinyrpc)
  
  # 如果是gtest，就添加相应的依赖
  STRING(REGEX MATCH "gtest$" IS_GTEST_FILE ${tinyrpc_test_name})
  if(IS_GTEST_FILE)
    gtest_discover_tests(${tinyrpc_test_name})
    target_link_libraries(${tinyrpc_test_name} tinyrpc gtest gmock_main)
  endif()
endforeach()
