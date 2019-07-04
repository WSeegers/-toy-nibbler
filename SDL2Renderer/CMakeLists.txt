add_library(SDL2Renderer SHARED
	src/SDL2Renderer.cpp
)

target_include_directories(SDL2Renderer SYSTEM
	PRIVATE ${PROJECT_SOURCE_DIR}/Core/interface
)

target_link_libraries(SDL2Renderer PUBLIC SDL2)
