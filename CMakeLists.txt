cmake_minimum_required(VERSION 3.16)
project(DSALabAssignments LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Collect all shared source files from the global src/ directory
file(GLOB_RECURSE SHARED_SOURCES "src/*.cpp")

# 2. Add global include directory so all main.cpp files can find headers in include/
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# ==========================================
# ASSIGNMENT 1 TARGETS
# ==========================================

# Question 1: Coin Toss
add_executable(assign1_q1 
    Assignments/Assignment_1/cpp/q1_coinToss/main.cpp
    ${SHARED_SOURCES}
)

# Question 2: Bubble Sort
add_executable(assign1_avg_q2 
    Assignments/Assignment_1/cpp/q2_bubbleSort/main_copy.cpp 
    ${SHARED_SOURCES}
)

# Question 3: Quick Sort & Hybrid Sort
add_executable(assign1_q3 
    Assignments/Assignment_1/cpp/q3_quickSort/main.cpp 
    ${SHARED_SOURCES}
)

# Question 4: Estimate the value of Pi using monte carlo simulation
add_executable(assign2_q4 
    Assignments/Assignment_2/cpp/q4_computePI/main.cpp 
    ${SHARED_SOURCES}
)
# Question 5: integration estimation using monte carlo simulation
add_executable(assign2_q5 
    Assignments/Assignment_2/cpp/q5_integration_estimation/main.cpp 
    ${SHARED_SOURCES}
)
# Question 6: Primality testing using miller rabin test
add_executable(assign2_q6 
    Assignments/Assignment_2/cpp/q6_primality_testing/main.cpp 
    ${SHARED_SOURCES}
)
# Question 7: Majority element finding using randomized algorithm
add_executable(assign2_q7 
    Assignments/Assignment_2/cpp/q7_majority_element/main.cpp 
    ${SHARED_SOURCES}
)
# Question 8: Randomized quick sort
add_executable(assign2_q8 
    Assignments/Assignment_2/cpp/q8_randomized_quick_sort/main.cpp 
    ${SHARED_SOURCES}
)

# ==========================================
# (Optional) Future Assignments can go here:
# ==========================================
# add_executable(assign2_q1 Assignment2/cpp/q1_someProblem/main.cpp ${SHARED_SOURCES})