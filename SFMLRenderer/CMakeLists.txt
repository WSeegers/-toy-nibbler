add_library(SFMLRenderer SHARED
	src/SFMLRenderer.cpp
)

target_include_directories(SFMLRenderer SYSTEM
	PRIVATE ${PROJECT_SOURCE_DIR}/Core/interface
)

target_link_libraries(SFMLRenderer 
	PUBLIC sfml-graphics
	PUBLIC sfml-window
	PUBLIC sfml-system.dylib
)
