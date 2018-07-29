set(EXE_NAME App_Game_Of_Life)

project(${EXE_NAME})

file(GLOB_RECURSE HEADERS "*.h" "*.hpp")
file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(${EXE_NAME}
               ${SOURCES}
               ${HEADERS})

target_include_directories(${EXE_NAME}
   PRIVATE
      .
)

target_link_libraries(${EXE_NAME}
   PRIVATE
       GameOfLifeEngine
)
