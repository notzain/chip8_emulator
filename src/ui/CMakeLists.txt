set(UI_FILES
        GameWindow.h
        GameWindow.cpp
        KeypadWindow.h
        KeypadWindow.cpp)

add_library(ui ${UI_FILES})
target_link_libraries(ui PUBLIC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} )