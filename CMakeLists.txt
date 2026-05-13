cmake_minimum_required(VERSION 3.16)
project(Linumes LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# Dependencies  (SDL2 via vcpkg or system install)
# ---------------------------------------------------------------------------

find_package(SDL2         CONFIG REQUIRED)
find_package(SDL2_mixer   CONFIG REQUIRED)
find_package(SDL2_ttf     CONFIG REQUIRED)
find_package(SDL2_image   CONFIG REQUIRED)
find_package(OpenGL       REQUIRED)
find_package(yaml-cpp     CONFIG REQUIRED)

# ---------------------------------------------------------------------------
# Bundled third-party sources
# ---------------------------------------------------------------------------

set(XMMS_SOURCES      xmms/fft.c)

# ---------------------------------------------------------------------------
# Game sources
# ---------------------------------------------------------------------------

set(FRAMEWORK_SOURCES
    src/framework/AudioInfo.cpp
    src/framework/AudioManager.cpp
    src/framework/AudioResource.cpp
    src/framework/BaseTextDisplay.cpp
    src/framework/Configuration.cpp
    src/framework/FileUtils.cpp
    src/framework/Font.cpp
    src/framework/FontInfo.cpp
    src/framework/FontInfoBuilder.cpp
    src/framework/FontResource.cpp
    src/framework/MediaManager.cpp
    src/framework/Mode.cpp
    src/framework/ModeManager.cpp
    src/framework/MusicResource.cpp
    src/framework/OpenGLUtils.cpp
    src/framework/PluginResource.cpp
    src/framework/Positioned.cpp
    src/framework/Resource.cpp
    src/framework/ResourceHelper.cpp
    src/framework/StringResource.cpp
    src/framework/TextureInfo.cpp
    src/framework/TextureQuad.cpp
    src/framework/TextureResource.cpp
    src/framework/Theme.cpp
    src/framework/ThemeManager.cpp
    src/framework/Themed.cpp
    src/framework/TimeLimited.cpp
    src/framework/TimePositioned.cpp
    src/framework/Timed.cpp
    src/framework/Utils.cpp
    src/framework/XMLSongBuilder.cpp
    src/framework/XMLTextDisplayBuilder.cpp
    src/framework/XMLTheme.cpp
    src/framework/XMLUtils.cpp
)

set(GAME_SOURCES
    src/linumes/Block.cpp
    src/linumes/BlockMesh.cpp
    src/linumes/ConfigurationBoard.cpp
    src/linumes/ConfigurationMode.cpp
    src/linumes/FadingForeground.cpp
    src/linumes/GameBoard.cpp
    src/linumes/GameBoardScreenSaver.cpp
    src/linumes/GameMode.cpp
    src/linumes/GamePiece.cpp
    src/linumes/Grid.cpp
    src/linumes/HUD.cpp
    src/linumes/HighScoreManager.cpp
    src/linumes/HighScoreTable.cpp
    src/linumes/Icon.cpp
    src/linumes/Linumes.cpp
    src/linumes/LinumesModeManager.cpp
    src/linumes/LinumesThemeManager.cpp
    src/linumes/MagicBlock.cpp
    src/linumes/PluggableBackground.cpp
    src/linumes/Scanner.cpp
    src/linumes/ScreenSaverMode.cpp
    src/linumes/Selection.cpp
    src/linumes/SelectionBoard.cpp
    src/linumes/SelectionMode.cpp
    src/linumes/SimpleBackground.cpp
    src/linumes/TimeLimitedGameBoard.cpp
    src/linumes/TimeLimitedGameMode.cpp
    src/linumes/Token.cpp
    src/linumes/boss/Boss.cpp
    src/linumes/boss/BossBoard.cpp
    src/linumes/boss/BossIcon.cpp
    src/linumes/boss/BossMode.cpp
    src/linumes/boss/BossPiece.cpp
)

# ---------------------------------------------------------------------------
# Executable
# ---------------------------------------------------------------------------

add_executable(Linumes
    ${FRAMEWORK_SOURCES}
    ${GAME_SOURCES}
    ${XMMS_SOURCES}
)

target_include_directories(Linumes PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/xmms
    ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(Linumes PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
    ${OPENGL_LIBRARIES}
    ${CMAKE_DL_LIBS}
    yaml-cpp::yaml-cpp
)

# ---------------------------------------------------------------------------
# Build configuration
# ---------------------------------------------------------------------------

target_compile_definitions(Linumes PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

# On Windows: use srand() instead of POSIX srandom(), disable dlfcn plugin loader
if(WIN32)
    target_compile_definitions(Linumes PRIVATE MING_RANDOM MING_NO_PLUGIN MING_ENTRY)
    set_target_properties(Linumes PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(MSVC)
    # /Z7 embeds debug info in .obj files (no shared PDB per TU) — avoids C1041
    # contention when MSBuild compiles files in parallel.
    string(REPLACE "/Zi" "/Z7" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "/Zi" "/Z7" CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG}")
    string(REPLACE "/Zi" "/Z7" CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
    string(REPLACE "/Zi" "/Z7" CMAKE_C_FLAGS_RELWITHDEBINFO   "${CMAKE_C_FLAGS_RELWITHDEBINFO}")

    # Force-include OpenGLHeaders.h first in every TU so windows.h always
    # precedes GL/gl.h regardless of individual file include order.
    target_compile_options(Linumes PRIVATE
        /W3 /wd4996
        "/FI${CMAKE_SOURCE_DIR}/src/framework/OpenGLHeaders.h"
        "/FI${CMAKE_SOURCE_DIR}/src/framework/SDL2Compat.h"
    )
else()
    target_compile_options(Linumes PRIVATE -Wall -Wextra)
endif()

# ---------------------------------------------------------------------------
# Copy runtime data assets next to the executable after each build
# ---------------------------------------------------------------------------

set(ASSET_DIRS  Themes base jublo)
set(ASSET_FILES LinumesConfiguration.yaml themelist.yaml jublo.yaml)

foreach(DIR ${ASSET_DIRS})
    if(EXISTS "${CMAKE_SOURCE_DIR}/${DIR}")
        add_custom_command(TARGET Linumes POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_SOURCE_DIR}/${DIR}"
                "$<TARGET_FILE_DIR:Linumes>/${DIR}"
            COMMENT "Copying ${DIR}/ to output"
        )
    endif()
endforeach()

foreach(FILE ${ASSET_FILES})
    if(EXISTS "${CMAKE_SOURCE_DIR}/${FILE}")
        add_custom_command(TARGET Linumes POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_SOURCE_DIR}/${FILE}"
                "$<TARGET_FILE_DIR:Linumes>/${FILE}"
            COMMENT "Copying ${FILE} to output"
        )
    endif()
endforeach()
