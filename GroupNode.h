//
// Created by sabre on 22/04/2025.
//

#ifndef GROUPNODE_H
#define GROUPNODE_H
#include "AVLTree.h"
#include "PlayerNode.h"

/**
 * Represents a player inside a group, linked with the AVL Tree structure.
 */
class PlayerNodeOfGroup {
public:
    int player_id;
    Node<PlayerNode>* tree_node;
    int level;
    int group_id;

    explicit PlayerNodeOfGroup(int player_id, Node<PlayerNode>* tree_node, int level, int group_id)
        : player_id(player_id), tree_node(tree_node), level(level), group_id(group_id) {}

    ~PlayerNodeOfGroup() = default;

    bool operator==(const PlayerNodeOfGroup& other) const {
        return player_id == other.player_id;
    }

    bool operator>(const PlayerNodeOfGroup& other) const {
        return player_id > other.player_id;
    }

    bool operator<(const PlayerNodeOfGroup& other) const {
        return player_id < other.player_id;
    }

    bool operator>=(const PlayerNodeOfGroup& other) const {
        return player_id >= other.player_id;
    }

    bool operator<=(const PlayerNodeOfGroup& other) const {
        return player_id <= other.player_id;
    }
};

/**
 * Node used to store level and ID for advanced ordering logic in AVL trees.
 * Ordered by level (descending), and then by player_id (ascending).
 */
class LevelNode {
public:
    int level;
    int player_id;

    explicit LevelNode(int level, int player_id) : level(level), player_id(player_id) {}

    ~LevelNode() = default;

    bool operator==(const LevelNode& other) const {
        return level == other.level && player_id == other.player_id;
    }

    bool operator>(const LevelNode& other) const {
        return (level > other.level) || (level == other.level && player_id < other.player_id);
    }

    bool operator<(const LevelNode& other) const {
        return (level < other.level) || (level == other.level && player_id > other.player_id);
    }

    bool operator>=(const LevelNode& other) const {
        return *this > other || *this == other;
    }

    bool operator<=(const LevelNode& other) const {
        return *this < other || *this == other;
    }
};

/**
 * GroupNode represents a team of players with tracking of AVL trees and level stats.
 */
class GroupNode {
public:
    int group_id;
    int player_count;
    int* max_level; // [0] = max level, [1] = number of players with max level
    AVLTree<PlayerNodeOfGroup>* players_tree;
    AVLTree<LevelNode>* levels_tree;

    explicit GroupNode(int group_id, int player_count)
        : group_id(group_id), player_count(player_count), max_level(new int[2]) {
        players_tree = new AVLTree<PlayerNodeOfGroup>();
        levels_tree = new AVLTree<LevelNode>();
        max_level[0] = -5;
        max_level[1] = -5;
    }

    ~GroupNode() {
        delete players_tree;
        delete levels_tree;
        delete[] max_level;
    }

    bool operator==(const GroupNode& other) const {
        return group_id == other.group_id;
    }

    bool operator>(const GroupNode& other) const {
        return group_id > other.group_id;
    }

    bool operator<(const GroupNode& other) const {
        return group_id < other.group_id;
    }

    bool operator>=(const GroupNode& other) const {
        return group_id >= other.group_id;
    }

    bool operator<=(const GroupNode& other) const {
        return group_id <= other.group_id;
    }
};




#endif //GROUPNODE_H
