# Linumes

A music-reactive block-falling puzzle game built with SDL2 and OpenGL. Themes define every visual and audio element — swap them at runtime with **M**.

---

## Prerequisites

| Tool | Notes |
|------|-------|
| CMake 3.16+ | Build system |
| C++17 compiler | MSVC 2019+, GCC 10+, or Clang 12+ |
| [vcpkg](https://github.com/microsoft/vcpkg) | Recommended for dependencies on Windows |

### Dependencies (resolved via vcpkg or system package manager)

- SDL2
- SDL2\_mixer
- SDL2\_ttf
- SDL2\_image
- yaml-cpp
- OpenGL

**vcpkg install command:**
```
vcpkg install sdl2 sdl2-mixer sdl2-ttf sdl2-image yaml-cpp
```

---

## Building

```bash
# Configure
cmake -B build -DCMAKE_TOOLCHAIN_FILE=<path/to/vcpkg>/scripts/buildsystems/vcpkg.cmake

# Release build
cmake --build build --config Release

# Debug build
cmake --build build --config Debug
```

The executable and all runtime assets (themes, config, audio) are copied into `build/Release/` or `build/Debug/` automatically after each build.

---

## Controls

| Key | Action |
|-----|--------|
| Left Arrow | Move piece left |
| Right Arrow | Move piece right |
| Down Arrow | Drop piece |
| Z | Rotate clockwise |
| X | Rotate counter-clockwise |
| Return | Start / restart |
| Backspace | Return to mode selection |
| M | Advance to next theme |
| V | Pause/resume scanner |
| A | Advance token set (debug) |
| B | Dump current block state (debug) |
| F1 | Toggle fullscreen |
| F11 | Screenshot |

**Joystick (beta):**

| Input | Action |
|-------|--------|
| Directional axis | Move |
| Button 0 | Rotate counter-clockwise |
| Button 1 | Rotate clockwise |
| Button 2 | Return |
| Button 3 | Backspace |

---

## Theme System

Themes are data-driven and require no code changes. All theme files are YAML. The game loads themes listed in `themelist.yaml` at startup.

### File layout

```
resources/
  themelist.yaml              ← master list of themes
  LinumesConfiguration.yaml   ← game configuration
  jublo.yaml                  ← boss configuration
  base/                       ← base resources shared by all themes
    base_hud.yaml             ← HUD layout (score, time, announce)
    modeselections.yaml       ← game mode list
    configurationselections.yaml
    highscores.yaml
  Themes/
    my_theme.yaml             ← theme definition
    my_theme/
      my_hud.yaml             ← optional HUD override
      *.png                   ← textures
      *.ttf                   ← fonts
      *.mp3 / *.ogg           ← music track
  jublo/                      ← boss mode assets
```

### Registering a theme

Add an entry to `themelist.yaml` under `themes:`:

```yaml
themes:
  - name: MyTheme
    file: my_theme.yaml
    dir: Themes
```

### Theme definition (`my_theme.yaml`)

```yaml
dir: my_theme          # subdirectory under Themes/ containing assets

resources:
  # Block textures — color0/color1 are the two standard piece colors
  - type: texture
    name: texture_color0
    file: block_a.png

  - type: texture
    name: texture_color1
    file: block_b.png

  # Special (bonus) block variants
  - type: texture
    name: texture_special0
    file: block_a_special.png

  - type: texture
    name: texture_special1
    file: block_b_special.png

  # Scanned (cleared) block variants
  - type: texture
    name: texture_scanned0
    file: block_a_scanned.png

  - type: texture
    name: texture_scanned1
    file: block_b_scanned.png

  # Board chrome
  - type: texture
    name: texture_grid
    file: grid.png

  - type: texture
    name: texture_grid_mask
    file: grid_mask.png

  - type: texture
    name: texture_bg
    file: background.png

  # Game elements
  - type: texture
    name: texture_scanner
    file: scanner.png

  - type: texture
    name: texture_holder
    file: holder.png

  - type: texture
    name: texture_flag
    file: flag.png

  - type: texture
    name: texture_flag_mask
    file: flag_mask.png

  - type: texture
    name: texture_magicbox
    file: magicbox.png

  - type: texture
    name: texture_magicbox_mask
    file: magicbox_mask.png

  - type: texture
    name: texture_spark
    file: spark.png

  - type: texture
    name: texture_spark_mask
    file: spark_mask.png

  - type: texture
    name: texture_stars
    file: stars.png

  - type: texture
    name: texture_stars_mask
    file: stars_mask.png

  - type: texture
    name: texture_icon
    file: icon.png

  - type: texture
    name: texture_icon_mask
    file: icon_mask.png

  # Block tile textures (alternative block styles)
  - type: texture
    name: texture_block0
    file: tile0.png

  - type: texture
    name: texture_block1
    file: tile1.png

  # HUD font
  - type: font
    name: hud_font
    file: MyFont.ttf
    pointsize: '24'
    red: '1.0'
    green: '0.75'
    blue: '0.50'

  # HUD layout file (text display positions)
  - type: string
    name: hud_file
    file: my_hud.yaml

# Music track and beat timings
song:
  name: audio_song
  type: mp3               # mp3 or ogg
  track: mysong.mp3
  track_name: My Song Title
  artist: Artist Name
  tracklength: '180.00'
  unit: seconds
  beats:
    timings:
      - 1.234
      - 2.468
      # ... one timestamp (in seconds) per beat
    unit: seconds
```

### HUD layout (`my_theme/my_hud.yaml`)

Positions HUD text elements in screen-space pixels (origin top-left):

```yaml
text_displays:
  - name: hiscore_txt
    type: string
    text: High
    x: '890'
    y: '700'
  - name: hiscore_val
    type: int
    text: ' '
    x: '890'
    y: '650'
  - name: score_txt
    type: string
    text: Score
    x: '890'
    y: '600'
  - name: score_val
    type: int
    text: ' '
    x: '890'
    y: '550'
  - name: count_txt
    type: string
    text: Block
    x: '890'
    y: '500'
  - name: count_val
    type: int
    text: ' '
    x: '890'
    y: '450'
  - name: time_txt
    type: string
    text: Time
    x: '890'
    y: '400'
  - name: time_val
    type: int
    text: ' '
    x: '890'
    y: '350'
  - name: announce
    type: string
    text: ' '
    x: '400'
    y: '680'
```

Required names (`hiscore_val`, `score_val`, `count_val`, `time_val`, `announce`) are updated by the engine at runtime; the `*_txt` labels are static.

### Beat timings

Beat timestamps drive music-reactive visuals. To generate them for a new track, use any beat-detection tool (e.g. [BeatRoot](https://code.soundsoftware.ac.uk/projects/beatroot), Sonic Annotator, or a DAW) and export timestamps in seconds. Paste the list under `song.beats.timings`.

---

## Credits

- Audio: [Creative Commons](https://creativecommons.org/). See individual theme directories for track attribution.
- Base sound effects: Wesnoth, KDE, Nexuiz.
- FFT implementation: adapted from XMMS (GPL v2.0+).
