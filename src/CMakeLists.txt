add_executable(Kursatch3 Cell.cpp Cell.h Textures.cpp Textures.h Cell.cpp Cell.h Area.cpp Area.h ship.cpp ship.h Player.cpp Player.h ShipMovement.cpp ShipMovement.h ShipShot.cpp ShipShot.h Game.cpp Game.h Game.cpp Game.h)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp *.h)
target_sources(Kursatch3 PRIVATE ${SOURCE_FILES})
target_link_libraries(Kursatch3 sfml-system sfml-window sfml-graphics sfml-audio)