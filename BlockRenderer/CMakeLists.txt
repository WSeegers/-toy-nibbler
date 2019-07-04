add_library(BlockRenderer SHARED
	src/BlockRenderer.cpp
)

find_package(SDL2 REQUIRED)

target_include_directories(BlockRenderer SYSTEM
	PRIVATE ${PROJECT_SOURCE_DIR}/Core/interface
)

target_link_libraries(BlockRenderer PUBLIC SDL2)
