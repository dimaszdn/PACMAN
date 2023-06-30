cmake_minimum_required(VERSION 3.15) # Проверка версии CMake.
									 # Если версия установленой программы
									 # старее указаной, произайдёт аварийный выход.

set(PROJECT_NAME PACMAN)				 # имя проекта		 
project("${PROJECT_NAME}")


set(CMAKE_CXX_STANDARD 17)			 # устанавливаем 17 стандарт языка
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


add_definitions(-DSFML_STATIC)		 # дефайны

include_directories("ext/SFML/include/")	# добавляем директории
include_directories("inc/")
include_directories("src/")
link_directories("ext/SFML/lib/")	

add_executable("${PROJECT_NAME}" main.cpp

		inc/Global.h inc/Pacman.h inc/Map.h inc/Ghost.h src/Pacman.cpp src/Ghost.cpp inc/Collision.h src/Collision.cpp inc/Blinky.h src/Blinky.cpp inc/Clyde.h src/Clyde.cpp inc/Pinky.h src/Pinky.cpp inc/Inky.h src/Inky.cpp inc/Game.h src/Game.cpp inc/GameBar.h src/GameBar.cpp)

target_link_libraries("${PROJECT_NAME}" optimized sfml-graphics-s
		optimized sfml-window-s
		optimized sfml-system-s
		opengl32
		freetype
		winmm
		gdi32
		optimized sfml-audio-s
		openal32
		flac
		vorbisenc
		vorbisfile
		vorbis
		ogg
		debug sfml-graphics-s-d
		debug sfml-window-s-d
		debug sfml-system-s-d
		debug sfml-audio-s-d
		)