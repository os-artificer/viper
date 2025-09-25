# use the local yaml-cpp lib
find_package(yaml-cpp QUIET)

if(NOT yaml-cpp_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG yaml-cpp-0.8.0
  )
  FetchContent_MakeAvailable(yaml-cpp)
endif()

# link libs
# target_link_libraries(YOUR_LIBRARY PUBLIC yaml-cpp::yaml-cpp)
