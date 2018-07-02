set(UI_FILES
        GameWindow.h
        GameWindow.cpp
        canvas/ICanvas.h
        canvas/GameCanvas.cpp
        canvas/GameCanvas.h
        canvas/KeypadCanvas.cpp
        canvas/KeypadCanvas.h)

add_library(ui ${UI_FILES})

target_link_libraries(ui PRIVATE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} core)