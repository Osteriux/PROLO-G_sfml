# PROLO-G SFML Codebase Instructions

## Architecture Overview

PROLO-G is a dungeon-exploration game using C++17 and SFML 2.6.2 with a **Singleton GameManager** pattern (recently refactored from pointer-passing). The architecture follows clean OOP principles with clear component boundaries.

### Core Components

- **GameManager** (Singleton): Central coordinator accessed via `GameManager::getInstance()`. Initialize with `GameManager::initialize(windowSize, levelPath)` before use, destroy with `GameManager::destroy()` on cleanup.
- **EventManager**: Handles SFML input events, delegates to GameManager singleton (no member reference needed).
- **Logger** (Singleton): Centralized logging system for debugging and error tracking. Must be initialized with `Logger::initialize(level, filePath)` before use.
- **Map**: Grid-based map system with `Case` cells, handles rendering/scaling/visibility.
- **GameObject Hierarchy**: `GameObject` → `DynamicGameObject` (Player, Monster) / `StaticGameObject` → `Pickup` (Mine, Battery, Bomb, Detector) / `Interactible` (Lever).

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
#include "../manager/game_manager.hpp"
```

**Exception**: `static_game_object.h` includes `game_object.h` but forward declares `DynamicGameObject`.

### 2. Factory Pattern for Object Creation

```cpp
// ItemFactory - no GameManager parameter needed
auto pickup = ItemFactory::createPickup(x, y, pickupTypeId);
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

### 5. Event System (Event-Driven Architecture)

The codebase uses a **pub/sub event system** to decouple components. Components communicate via events rather than direct calls.

#### Event System Components

- **GameEventSystem**: Singleton event dispatcher (`GameEventSystem::getInstance()`)
- **IEventListener**: Interface for components that react to events
- **GameEvent**: Base class for all events with `Type` enum and `getType()` method

#### Creating New Events

When adding new game actions or state changes, create events to maintain decoupling:

```cpp
// 1. Add event type to GameEvent::Type enum in game_event.hpp
enum class Type {
    // ... existing types
    MY_NEW_EVENT
};

// 2. Create event class inheriting from GameEvent
class MyNewEvent : public GameEvent {
private:
    int someData;
    std::string moreData;

public:
    MyNewEvent(int data, const std::string& more)
        : someData(data), moreData(more) {}

    Type getType() const override { return Type::MY_NEW_EVENT; }
    int getSomeData() const { return someData; }
    const std::string& getMoreData() const { return moreData; }
};
```

#### Using Events

**Emitting Events:**

```cpp
// After state changes, dispatch event
void Player::performAction() {
    // ... perform action logic ...

    MyNewEvent event(42, "action completed");
    GameManager::getInstance().getEventSystem().dispatch(event);
}
```

**Listening to Events:**

```cpp
// 1. Inherit from IEventListener
class MyComponent : public IEventListener {
public:
    MyComponent() {
        // Subscribe in constructor or init()
        GameEventSystem::getInstance().subscribe(GameEvent::Type::MY_NEW_EVENT, this);
    }

    void onEvent(const GameEvent &event) override {
        if (event.getType() == GameEvent::Type::MY_NEW_EVENT) {
            const auto &myEvent = static_cast<const MyNewEvent &>(event);
            // React to event
        }
    }

    ~MyComponent() {
        // Always unsubscribe!
        GameEventSystem::getInstance().unsubscribeAll(this);
    }
};
```

#### Event Categories

**Player State Events:**

- `PlayerMovedEvent`: Position changed
- `PlayerDamagedEvent`: Health decreased
- `PlayerHealedEvent`: Health increased
- `PlayerInventoryChangedEvent`: Inventory counts changed
- `PlayerContextChangedEvent`: Case changed (new pickups/levers available)

**Item Events:**

- `ItemPickedUpEvent`: Pickup collected
- `ItemUsedEvent`: Item used from inventory

**Interaction Events:**

- `LeverToggledEvent`: Lever activated/deactivated
- `DoorOpenedEvent` / `DoorClosedEvent`: Door state changed

**UI Events:**

- `HUDActionEvent`: User clicked HUD button (movement, item use, etc.)

#### Event Flow Pattern

```
User Action → HUD emits HUDActionEvent
           → GameManager listens, translates to game command
           → Player/GameObject executes, emits state event
           → HUD/Log listen, update display
```

#### Best Practices

- **Emit after state changes**: Only dispatch events after the action completes
- **Immutable events**: Events should be const references, data copied at creation
- **Avoid recursion**: Don't dispatch events during event handling
- **Always unsubscribe**: Call `unsubscribeAll(this)` in destructor
- **Use specific events**: Create new event types rather than generic "StateChanged"
- **Init order**: Components subscribing to events need `init()` method called after GameManager exists

## Build System (CMake + MinGW)

### Configuration

- CMake 3.10+ with MinGW Makefiles generator
- SFML 2.6.2 installed at `C:/Program Files/SFML-2.6.2`
- MinGW 13.1.0 at `C:/ProgramData/mingw64/mingw64/bin`
- Two build presets (see `CMakePresets.json`):
  - `prolo-g_preset`: Debug build with all dev tools
  - `prolo-g_release`: Optimized release build, excludes debug code
- Build outputs: `out/build/prolo-g_preset/` (Debug) or `out/build/prolo-g_release/` (Release)

### Build Commands

**Using the Helper Script (Recommended):**

```bash
# Display help
./prolog.sh help

# Build and run development version
./prolog.sh build    # Build dev version
./prolog.sh run      # Run dev version

# run release version
./prolog.sh release  # Run release build

# Create distribution package
./prolog.sh package  # Builds release and creates zip in releases/

# Clean build files
./prolog.sh clean
```

**Manual CMake Commands:**

do not use refer to the helper script above for simplicity.

### Automatic DLL Handling

CMakeLists.txt automatically copies required DLLs to build directory:

- **SFML DLLs**: Debug builds get `-d-2.dll` versions, Release gets `-2.dll`
  - `sfml-graphics`, `sfml-window`, `sfml-system`
- **MinGW Runtime DLLs**: `libgcc_s_seh-1.dll`, `libstdc++-6.dll`

No manual DLL copying needed - everything works out of the box.

### Debug Code Exclusion Convention

**Folders starting with `_` are debug-only** and excluded from Release builds:

- `src/_devTool/`: Development tools, debug console
- Any future `src/_*/` folder will be automatically excluded

Use `#ifdef _DEV_MODE` in code for conditional debug features. The `_DEV_MODE` preprocessor macro is automatically defined in developpement builds.

### Asset Handling

Assets auto-copy from `assets/` to build directory post-build. Level files are in `assets/level/*.txt` with custom format parsed by `LevelFileHandeler`.

## Code Conventions

### Naming

- **Classes**: PascalCase (`GameManager`, `DynamicGameObject`, `Map`, `Player`)
- **Members**: camelCase (`currCase`, `player`, `map`, `door`)
- **Constants**: UPPER_SNAKE_CASE in class scope
- **Folders**: Debug/dev-only folders start with `_` (e.g., `_devTool`, `_debug`)
- **Language**: All code uses English naming conventions (previously had French names - fully translated as of Dec 2025).

### Header Guards

Use `#pragma once` exclusively (modern compiler support assumed).

### Logging and Error Handling

**Logger Singleton** - Centralized logging system in `src/utils/logger/`:

```cpp
// Initialize once at application startup (in main or GameManager::initialize)
Logger::initialize(Logger::INFO, "log/prolo-g.log");

// Use throughout codebase for structured logging
Logger::log("Player moved to position (5, 3)", Logger::INFO);
Logger::log("Failed to load texture: missing file", Logger::ERROR);
Logger::log("Health low, consider healing", Logger::WARNING);
```

**Log Levels** (in order of severity):
- `Logger::DEBUG` (0): Detailed debug information, verbose output
- `Logger::INFO` (10): General informational messages
- `Logger::WARNING` (20): Warning messages for non-critical issues
- `Logger::ERROR` (30): Error messages for failures

**Configuration:**
- Set minimum level at initialization: `Logger::initialize(Logger::WARNING, ...)`
- Messages below the threshold are ignored (e.g., INFO not logged if level is WARNING)
- Log file path is optional: empty string `""` logs to stdout
- Log directory is created automatically if it doesn't exist
- Log file opens in append mode to preserve history

**Error Handling Guidelines:**
- **Logger::log()**: Use for all logging needs instead of raw `std::cerr` or `std::cout`
- **Exceptions**: Use for exceptional conditions (file loading failures, invalid types)
- **Avoid silent failures**: Always log or throw, don't ignore errors
- **Log file location**: Default is `log/prolo-g.log` (excluded from git via `.gitignore`)

## Common Tasks

### Adding New GameObject Type

1. Inherit from `DynamicGameObject`, `Pickup`, or `Interactible`
2. Constructor signature: `MyObject(int x, int y, ...other params)` - NO GameManager param
3. Call parent with appropriate constructor (e.g., `Pickup(std::move(texture), x, y)`)
4. Access GameManager in methods: `GameManager::getInstance().getMap()`
5. Add factory method if needed (return `std::unique_ptr<YourType>`)

### Adding New Pickup Type

1. Add enum to `Pickup::PickupType` in `pickup.h`
2. Create subclass in `src/game_object/static/pickup/` inheriting from `Pickup`
3. Implement `getDescription()` and `action(DynamicGameObject* user)` overrides
4. Add case to `ItemFactory::createPickup()` switch in `src/factory/item_factory.cpp`
5. Add texture path to `Pickup::texturePath()` static method
6. Add corresponding PNG file to `assets/static/`

### Adding New Interactible Type

1. Add enum to `Interactible::InteractibleType` in `interactible.h`
2. Create subclass in `src/game_object/static/interactible/` inheriting from `Interactible`
3. Implement `getDescription()` and `interact(DynamicGameObject* user)` overrides
4. Add factory method to `ItemFactory` in `src/factory/item_factory.h/cpp` if needed
5. Interactibles are triggered by player interaction, while Pickups are collected automatically

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

1. **GameManager Singleton** (Dec 2025): Converted to singleton pattern. All constructors updated to remove GameManager parameters. Use `getInstance()` instead of passing pointers.

2. **Static GameObject Reorganization** (Dec 2025): Split into two hierarchies:

   - **Pickup**: Collectible items (Mine, Battery, Bomb, Detector) - automatically picked up on contact
   - **Interactible**: Environmental objects (Lever) - require player interaction via `interact()`
   - Both inherit from `StaticGameObject` with `action(DynamicGameObject*)` interface
   - Factory renamed: `ItemFactory` class name → `ItemFactory` (file still named `item_factory.h/cpp`)
   - Directory structure: `src/game_object/static/{pickup/,interactible/}`

3. **French to English Translation** (Dec 2025): Complete codebase translation including classes, methods, variables, enums, and asset files. All naming now follows English conventions.

4. **Event System Implementation** (Dec 2025): Added pub/sub event system for component decoupling:

   - **GameEventSystem**: Singleton event dispatcher with subscribe/dispatch pattern
   - **IEventListener**: Interface for event-reactive components
   - **Component Decoupling**: HUD, Log, GameManager now communicate via events
   - **HUD Refactoring**: Removed direct Player pointer, maintains internal state via events
   - **Event Flow**: HUD emits `HUDActionEvent` → GameManager translates to commands → Player executes and emits state events → Components update
   - **Files**: `src/manager/game_event.hpp`, `game_event_system.hpp/cpp`
   - **Documentation**: See `doc/markdown/event_system.md` for detailed guide
   - **Extensible**: Create new events by adding to `GameEvent::Type` enum and implementing event class

5. **Build System Enhancements** (Dec 2025): Comprehensive build automation and DLL management:
   - **Automatic DLL Copying**: SFML and MinGW runtime DLLs auto-copy to build directory
   - **Debug/Release Configuration**: Separate presets with correct DLL versions (`-d-2.dll` for Debug, `-2.dll` for Release)
   - **Debug Code Exclusion**: Folders starting with `_` (like `src/_devTool/`) automatically excluded from Release builds
   - **`_RELEASE` Macro**: Preprocessor macro defined in Release builds for conditional compilation
   - **Helper Script**: `prolog.sh` provides simple commands: `build`, `run`, `release`, `package`, `clean`
   - **Release Packaging**: `package_release.sh` automates creating distributable zip with all dependencies
   - **CMake Improvements**: Proper source filtering, asset copying, cross-build-type support
