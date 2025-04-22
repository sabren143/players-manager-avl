# Players Manager System

This project implements a fully dynamic and efficient system for managing players, groups, and levels using AVL Trees. It supports adding/removing players, tracking levels, and retrieving group statistics in logarithmic time.

---

## 📦 Core Components

### Data Structures:
- `PlayersTree`: AVL tree indexed by `player_id` holding all players.
- `LevelsTree`: AVL tree indexed by `LevelNode(level, player_id)` used for global player level ranking.
- `EmptyGroupsTree`: AVL tree holding IDs of groups with zero players.
- `NonEmptyGroupsTree`: AVL tree holding `GroupNode` objects for active groups.

### Node Types:
- `PlayerNode`: Stores `player_id`, `level`, and `group_id`.
- `LevelNode`: Used for sorting by level + tie-breaking by player ID.
- `GroupNode`: Contains group metadata, `PlayersTreeOfGroup`, `LevelsTreeOfGroup`, and max level info.
- `PlayerNodeOfGroup`: Links group-local players to the global `PlayersTree`.

---

## 🧠 Main Operations

### `Init()`
Allocates and initializes a new `PlayersManager` instance.

### `AddGroup(groupID)`
Adds a new group. Groups are initially empty.

### `AddPlayer(playerID, groupID, level)`
Adds a player to a group:
- Updates group and global AVL trees
- Updates max-level trackers

### `RemovePlayer(playerID)`
Removes a player from:
- Global and group-specific trees
- Recalculates max-levels

### `ReplaceGroup(groupID, replacementID)`
Merges one group into another, efficiently rebuilding the subtree.

### `IncreaseLevel(playerID, levelIncrease)`
Increases a player’s level and repositions them in all trees.

### `GetHighestLevel(groupID)`
Returns the highest-level player in the specified group or system-wide.

### `GetAllPlayersByLevel(groupID)`
Returns all players sorted by descending level, optionally by group.

### `GetGroupsHighestLevel(numOfGroups)`
Returns the top players of the smallest `numOfGroups` groups.

### `Quit()`
Deletes the entire data structure and frees all resources.

---

## 🧮 Time Complexities

| Operation                  | Time        |
|---------------------------|-------------|
| Add/Remove Player          | O(log n)    |
| Add/Remove Group           | O(log n)    |
| Increase Level            | O(log n)    |
| Replace Group             | O(n log n)  |
| Get Players by Level      | O(n)        |
| Get Group Top Players     | O(k log n)  |

---

## 💡 Notes

- AVL Trees ensure logarithmic time insertions, deletions, and lookups.

---

## 🛠 Tech Stack

- Language: **C++**
- Memory-safe custom AVL Tree
- Header-only modular design
