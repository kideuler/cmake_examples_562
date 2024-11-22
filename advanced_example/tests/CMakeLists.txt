
enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(BasicTest BasicTest.cpp)
target_link_libraries(BasicTest PRIVATE matrix GTest::GTest GTest::Main)
gtest_discover_tests(BasicTest)

add_executable(LUFactorizationTest LUFactorizationTest.cpp)
target_link_libraries(LUFactorizationTest PRIVATE matrix GTest::GTest GTest::Main)
gtest_discover_tests(LUFactorizationTest)

add_executable(LUPFactorizationTest LUPFactorizationTest.cpp)
target_link_libraries(LUPFactorizationTest PRIVATE matrix GTest::GTest GTest::Main)
gtest_discover_tests(LUPFactorizationTest)

add_executable(QRFactorizationTest QRFactorizationTest.cpp)
target_link_libraries(QRFactorizationTest PRIVATE matrix GTest::GTest GTest::Main)
gtest_discover_tests(QRFactorizationTest)

add_executable(QRCPFactorizationTest QRCPFactorizationTest.cpp)
target_link_libraries(QRCPFactorizationTest PRIVATE matrix GTest::GTest GTest::Main)
gtest_discover_tests(QRCPFactorizationTest)

add_executable(LUPFactorizationParallelTest LUPFactorizationParallelTest.cpp)
target_link_libraries(LUPFactorizationParallelTest PRIVATE matrix GTest::GTest GTest::Main)
gtest_discover_tests(LUPFactorizationParallelTest)

add_executable(QRCPFactorizationParallelTest QRCPFactorizationParallelTest.cpp)
target_link_libraries(QRCPFactorizationParallelTest PRIVATE matrix GTest::GTest GTest::Main)
gtest_discover_tests(QRCPFactorizationParallelTest)