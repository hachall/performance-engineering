# CMake generated Testfile for 
# Source directory: /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2/projects
# Build directory: /homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(RunTests "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest")
set_tests_properties(RunTests PROPERTIES  FAIL_REGULAR_EXPRESSION "Filters:")
add_test(ListTests "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest" "--list-tests" "--verbosity" "high")
set_tests_properties(ListTests PROPERTIES  FAIL_REGULAR_EXPRESSION "Hidden Test" PASS_REGULAR_EXPRESSION "[0-9]+ test cases")
add_test(ListTags "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest" "--list-tags")
set_tests_properties(ListTags PROPERTIES  FAIL_REGULAR_EXPRESSION "\\[\\.\\]" PASS_REGULAR_EXPRESSION "[0-9]+ tags")
add_test(ListReporters "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest" "--list-reporters")
set_tests_properties(ListReporters PROPERTIES  PASS_REGULAR_EXPRESSION "Available reporters:")
add_test(ListTestNamesOnly "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest" "--list-test-names-only")
set_tests_properties(ListTestNamesOnly PROPERTIES  FAIL_REGULAR_EXPRESSION "Hidden Test" PASS_REGULAR_EXPRESSION "Regex string matcher")
add_test(NoAssertions "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest" "-w" "NoAssertions")
set_tests_properties(NoAssertions PROPERTIES  PASS_REGULAR_EXPRESSION "No assertions in test case")
add_test(NoTest "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest" "Tracker," "___nonexistent_test___")
set_tests_properties(NoTest PROPERTIES  FAIL_REGULAR_EXPRESSION "No tests ran" PASS_REGULAR_EXPRESSION "No test cases matched '___nonexistent_test___'")
add_test(WarnAboutNoTests "/usr/bin/cmake" "-P" "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2/projects/SelfTest/WarnAboutNoTests.cmake" "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest")
add_test(UnmatchedOutputFilter "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest" "[this-tag-does-not-exist]" "-w" "NoTests")
set_tests_properties(UnmatchedOutputFilter PROPERTIES  PASS_REGULAR_EXPRESSION "No test cases matched '\\[this-tag-does-not-exist\\]'")
add_test(FilteredSection-1 "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest" "#1394" "-c" "RunSection")
set_tests_properties(FilteredSection-1 PROPERTIES  FAIL_REGULAR_EXPRESSION "No tests ran")
add_test(FilteredSection-2 "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest" "#1394 nested" "-c" "NestedRunSection" "-c" "s1")
set_tests_properties(FilteredSection-2 PROPERTIES  FAIL_REGULAR_EXPRESSION "No tests ran")
add_test(ApprovalTests "/usr/bin/python" "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2/scripts/approvalTests.py" "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest")
set_tests_properties(ApprovalTests PROPERTIES  FAIL_REGULAR_EXPRESSION "Results differed")
add_test(RegressionCheck-1670 "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest" "#1670 regression check" "-c" "A" "-r" "compact")
set_tests_properties(RegressionCheck-1670 PROPERTIES  PASS_REGULAR_EXPRESSION "Passed 1 test case with 2 assertions.")
add_test(VersionCheck "/homes/hh1919/Documents/code/performance-eng/performanceengineeringcw1_hh1919/cpp-benchmark/Release/catch2-prefix/src/catch2-build/projects/SelfTest" "-h")
set_tests_properties(VersionCheck PROPERTIES  PASS_REGULAR_EXPRESSION "Catch v2.9.2")
