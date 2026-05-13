cmake_minimum_required(VERSION 3.16)
project(Linumes LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# Dependencies
# ---------------------------------------------------------------------------

# SDL 1.x
find_package(SDL REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_image REQUIRED)

# OpenGL + GLU
find_package(OpenGL REQUIRED)

# dl (plugin loading via dlopen/dlsym — Linux/macOS only)
# CMAKE_DL_LIBS is empty on Windows where this path is unused.

# ---------------------------------------------------------------------------
# Bundled third-party sources
# ---------------------------------------------------------------------------

# Frank Vanden Berghen's XML parser (vendored in xmlparser/)
set(XMLPARSER_SOURCES xmlparser/xmlParser.cpp)

# XMMS FFT (vendored in xmms/, GPL v2+)
set(XMMS_SOURCES xmms/fft.c)

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
    ${XMLPARSER_SOURCES}
    ${XMMS_SOURCES}
)

target_include_directories(Linumes PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/xmlparser
    ${CMAKE_SOURCE_DIR}/xmms
    ${SDL_INCLUDE_DIR}
    ${SDLMIXER_INCLUDE_DIR}
    ${SDLTTF_INCLUDE_DIR}
    ${SDLIMAGE_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(Linumes PRIVATE
    ${SDL_LIBRARY}
    ${SDLMIXER_LIBRARY}
    ${SDLTTF_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${CMAKE_DL_LIBS}
)

# ---------------------------------------------------------------------------
# Build configuration
# ---------------------------------------------------------------------------

# Mirror the old Eclipse Debug flag
target_compile_definitions(Linumes PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

# Windows GUI entry point (matches the MING_ENTRY guard in Linumes.cpp)
if(WIN32)
    target_compile_definitions(Linumes PRIVATE MING_ENTRY)
    set_target_properties(Linumes PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Compiler warnings
if(MSVC)
    target_compile_options(Linumes PRIVATE /W3)
else()
    target_compile_options(Linumes PRIVATE -Wall -Wextra)
endif()
