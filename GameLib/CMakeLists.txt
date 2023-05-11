project(GameLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h GameView.cpp GameView.h ScoreBoard.cpp ScoreBoard.h RedundancyFly.cpp RedundancyFly.h NullBug.cpp NullBug.h GarbageBug.cpp GarbageBug.h Feature.cpp Feature.h Game.cpp Game.h Bug.cpp Bug.h ids.h Program.cpp Program.h Item.cpp Item.h Level.cpp Level.h ItemVisitor.cpp ItemVisitor.h BugVisitor.cpp BugVisitor.h BossBug.cpp BossBug.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
