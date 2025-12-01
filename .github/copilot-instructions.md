# PROLO-G SFML Codebase Instructions

## Architecture Overview

PROLO-G is a dungeon-exploration game using C++17 and SFML 2.6.2 with a **Singleton GameManager** pattern (recently refactored from pointer-passing). The architecture follows clean OOP principles with clear component boundaries.

### Core Components

- **GameManager** (Singleton): Central coordinator accessed via `GameManager::getInstance()`. Initialize with `GameManager::initialize(windowSize, levelPath)` before use, destroy with `GameManager::destroy()` on cleanup.
- **EventManager**: Handles SFML input events, delegates to GameManager singleton (no member reference needed).
- **Map**: Grid-based map system with `Case` cells, handles rendering/scaling/visibility.
- **GameObject Hierarchy**: `GameObject` → `DynamicGameObject` (Player, Monster) / `StaticGameObject` (Item, Lever).

### Memory Ownership Model

- GameManager owns major components via `std::unique_ptr` (Map, HUD, Log).
- Player is owned by its `Case`, GameManager keeps a raw pointer for access.
- Factories return `std::unique_ptr`, ownership transfers to caller.
- **Never pass GameManager pointers in constructors** - use `getInstance()` in methods that need it.

## Critical Patterns

### 1. Forward Declarations (Not Includes)

Headers use forward declarations to break circular dependencies:

```cpp
// In headers - CORRECT
class GameManager;
class DynamicGameObject;

// In cpp files - include full headers
#include "../manager/game_manager.h"
```

**Exception**: `static_game_object.h` includes `game_object.h` but forward declares `DynamicGameObject`.

### 2. Factory Pattern for Object Creation

```cpp
// ItemFactory - no GameManager parameter needed
auto item = ItemFactory::createItem(x, y, itemTypeId);
auto lever = ItemFactory::createLever(color, x, y, doorId, nb);

// MonsterFactory - no GameManager parameter
auto monster = MonsterFactory::createMonster(monsterType, x, y);
```

### 3. GameObject Constructor Pattern

All GameObject-derived classes follow this signature (no GameManager param):

```cpp
GameObject(std::unique_ptr<MultiTexture> animation, int x, int y)
DynamicGameObject(int health, int speed, std::unique_ptr<MultiTexture> animation, int x, int y)
StaticGameObject(std::unique_ptr<MultiTexture> animation, int x, int y)
```

### 4. Accessing Game State

```cpp
// In any method needing GameManager
Map* map = GameManager::getInstance().getMap();
Player* player = GameManager::getInstance().getPlayer();
HUD& hud = GameManager::getInstance().getHUD();
```

## Build System (CMake + MinGW)

### Configuration

- CMake 3.10+ with MinGW Makefiles generator
- SFML 2.6.2 installed at `C:/Program Files/SFML-2.6.2`
- Preset: `prolo-g_preset` (see `CMakePresets.json`)
- Build output: `out/build/prolo-g_preset/`

### Build Commands

```bash
# Configure (first time or after CMakeLists.txt changes)
cmake --preset prolo-g_preset

# Build
cmake --build out/build/prolo-g_preset

# Run
./out/build/prolo-g_preset/prolog.exe
```

### Asset Handling

Assets auto-copy from `assets/` to build directory post-build. Level files are in `assets/levels/*.txt` with custom format parsed by `LevelFileHandeler`.

## Code Conventions

### Naming

- **Classes**: PascalCase (`GameManager`, `DynamicGameObject`, `Map`, `Player`)
- **Members**: camelCase (`currCase`, `player`, `map`, `door`)
- **Constants**: UPPER_SNAKE_CASE in class scope
- **Language**: All code uses English naming conventions (previously had French names - fully translated as of Dec 2025).

### Header Guards

Use `#pragma once` exclusively (modern compiler support assumed).

### Error Handling

- **Exceptions**: Use for exceptional conditions (file loading failures, invalid types)
- **std::cerr**: Console warnings for non-critical issues
- **Avoid silent failures**: Log or throw, don't ignore errors

## Common Tasks

### Adding New GameObject Type

1. Inherit from `DynamicGameObject` or `StaticGameObject`
2. Constructor signature: `MyObject(int x, int y, ...other params)` - NO GameManager param
3. Call parent with `GameObject(std::move(texture), x, y)`
2. Access GameManager in methods: `GameManager::getInstance().getMap()`
5. Add factory method if needed (return `std::unique_ptr<YourType>`)

### Adding New Item Type

1. Add enum to `Item::ItemType` in `item.h`
2. Create subclass inheriting from `Item`
3. Implement `getDescription()` and `action(DynamicGameObject* user)` overrides
4. Add case to `ItemFactory::createItem()` switch
5. Add texture path to `Item::texturePath()` static method

### Modifying Game State Access

If adding new centralized state, put it in GameManager and access via singleton. DO NOT pass new manager pointers through constructors.

## Documentation

Comprehensive docs in `doc/markdown/`:

- **architecture.md**: Detailed design rationale and patterns
- **quick_reference.md**: Code quality scores and immediate fixes
- **best_practices.md**: C++ patterns used and recommendations
- **circular_dependencies.md**: Why forward declarations are crucial here

Doxygen HTML docs in `doc/html/` - regenerate with `doxygen Doxyfile`.

## Recently Completed Refactoring

GameManager converted to singleton pattern. All constructors updated to remove GameManager parameters. If you see old code patterns with GameManager pointers being passed, they're outdated - use `getInstance()` instead.
