add_library(
	Core
	src/Snake.cpp
	src/Vec2i.cpp
	src/AMainLoop.cpp
	src/NibblerEngine.cpp
	src/CellMap.cpp
)

target_link_libraries(Core dl)
