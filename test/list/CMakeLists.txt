
include_directories("${PROJECT_SOURCE_DIR}/lib")

add_executable(test_list test)
target_link_libraries(test_list List)

add_executable(test_list_suite test_suite.c insertion.c)
target_link_libraries(test_list_suite List)

macro(do_test testname exec arg result)
	add_test("${testname}" ${exec} ${args})
	set_tests_properties("${testname}"
		PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro(do_test)

macro(expect test result)
	set_tests_properties(${test}
		PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro(expect)

set(list1 "ListAppend_12_15")
add_test(${list1} test_list b 12 15)
expect(${list1} "^12, 15\n?$")

set(list2 "ListAddFront_45_78")
add_test(${list2} test_list f 45 78)
expect(${list2} "^78, 45\n?$")

set(list3 "ListAddSorted_0_5_-1")
add_test(${list3} test_list s 0 5 -1)
expect(${list3} "^-1, 0, 5\n?$")

add_test(ListSuite1 test_list_suite -a)

