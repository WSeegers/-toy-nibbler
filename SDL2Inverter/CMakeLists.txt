add_library(SDL2Inverter SHARED
	src/SDL2Inverter.cpp
)

target_include_directories(SDL2Inverter SYSTEM
	PRIVATE ${PROJECT_SOURCE_DIR}/Core/interface
)

target_link_libraries(SDL2Inverter PUBLIC SDL2)
