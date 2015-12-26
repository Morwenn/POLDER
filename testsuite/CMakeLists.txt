# Include Catch for the tests
include_directories(${CATCH_INCLUDE_DIR})

# Make one executable for the whole testsuite
add_executable(
    polder-testsuite

    main.cpp
    algorithm.cpp
    evaluation.cpp
    gray.cpp
    iterator.cpp
    matrix.cpp
    rational.cpp
    type_traits.cpp
    utility.cpp
    geometry/direction.cpp
    geometry/distance.cpp
    geometry/hypersphere.cpp
    geometry/intersects.cpp
    geometry/line.cpp
    geometry/point.cpp
    geometry/vector.cpp
    ini/dialect.cpp
    ini/element.cpp
    math/cmath.cpp
    math/formula.cpp
    polymorphic/vector.cpp
    semisymbolic/constant.cpp
    semisymbolic/number.cpp
)

add_test(testsuite polder-testsuite)

# Enable unit-testing
enable_testing(true)
