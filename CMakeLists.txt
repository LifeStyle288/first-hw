cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{GITHUB_RUN_NUMBER})
    message(STATUS "Find number")
    project(helloworld VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
else ()
    message(STATUS "Don't find number")
    project(helloworld)
endif()

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp ip_filter.cpp)

if (Boost_FOUND)
    add_executable(tests tests.cpp)
    set_target_properties(tests PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )
    target_link_libraries(tests
        ${Boost_LIBRARIES}
        helloworld
    )
    set(TESTS tests)
else ()
    set(TESTS)
endif()

set_target_properties(helloworld_cli helloworld ${TESTS} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(helloworld_cli PRIVATE
    helloworld
)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(helloworld PRIVATE
        /W4
    )
    if (Boost_FOUND)
        target_compile_options(tests PRIVATE
            /W4
        )
    endif ()
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if (Boost_FOUND)
        target_compile_options(tests PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()



install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(tests tests)
