include(GoogleTest)

file(GLOB_RECURSE TINYRPC_TEST_SOURCES "*test.cc")

foreach(tinyrpc_test_source ${TINYRPC_TEST_SOURCES})
  # Create a human readable name.
  get_filename_component(tinyrpc_test_filename ${tinyrpc_test_source} NAME)
  string(REPLACE ".cc" "" tinyrpc_test_name ${tinyrpc_test_filename})

  add_executable(${tinyrpc_test_name} ${tinyrpc_test_source})

  gtest_discover_tests(${tinyrpc_test_name})

  target_link_libraries(${tinyrpc_test_name} tinyrpc gtest gmock_main)
endforeach()
