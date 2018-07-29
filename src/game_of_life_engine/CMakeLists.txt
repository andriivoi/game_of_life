set(LIB_NAME GameOfLifeEngine)

project(${LIB_NAME})

file(GLOB_RECURSE HEADERS "*.h" "*.hpp")
file(GLOB_RECURSE SOURCES "*.cpp")

add_library(${LIB_NAME}
            ${SOURCES}
            ${HEADERS})

target_include_directories(${LIB_NAME}
   PUBLIC
      include/
   PRIVATE
      source/include_impl/
)
