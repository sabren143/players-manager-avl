#ifndef PLAYERS_MANAGER_H
#define PLAYERS_MANAGER_H

#include "AVLTree.h"
#include "GroupNode.h"
#include "PlayerNode.h"
#include <iostream>

/**
 * Status types used by the PlayersManager interface.
 */
typedef enum {
    PM_SUCCESS = 0,
    PM_FAILURE = -1,
    PM_ALLOCATION_ERROR = -2,
    PM_INVALID_INPUT = -3
} PM_StatusType;

/**
 * Manages players, groups, and levels using AVL tree data structures.
 */
class PlayersManager {
public:
    AVLTree<int>* empty_groups_tree;
    AVLTree<GroupNode>* non_empty_groups_tree;
    AVLTree<LevelNode>* levels_tree;
    AVLTree<PlayerNode>* players_tree;
    int total_players;
    int* max_player_info; // [0] = max level, [1] = player ID

    /**
     * Constructs a new PlayersManager.
     */
    explicit PlayersManager() {
        empty_groups_tree = new AVLTree<int>();
        non_empty_groups_tree = new AVLTree<GroupNode>();
        levels_tree = new AVLTree<LevelNode>();
        players_tree = new AVLTree<PlayerNode>();
        total_players = 0;
        max_player_info = new int[2]{0, 1};
    }

    /**
     * Destroys the PlayersManager and deallocates all trees.
     */
    ~PlayersManager() {
        delete empty_groups_tree;
        delete non_empty_groups_tree;
        delete players_tree;
        delete levels_tree;
        delete[] max_player_info;
    }

    /**
     * Adds a new group to the system.
     * @param group_id The group ID to add.
     * @return PM_SUCCESS on success, PM_FAILURE on duplicate.
     */
    PM_StatusType addGroup(int group_id);

    /**
     * Adds a player to the system.
     * @param player_id ID of the player.
     * @param group_id Group to add the player to.
     * @param level Player's level.
     * @return PM_SUCCESS or PM_FAILURE.
     */
    PM_StatusType addPlayer(int player_id, int group_id, int level);

    /**
     * Removes a player by ID.
     * @param player_id Player ID to remove.
     * @return PM_SUCCESS or PM_FAILURE.
     */
    PM_StatusType removePlayer(int player_id);

    /**
     * Replaces a group with another group, merging players.
     * @param group_id ID of group to remove.
     * @param replacement_id ID of group to merge into.
     * @return PM_SUCCESS or PM_FAILURE.
     */
    PM_StatusType replaceGroup(int group_id, int replacement_id);

    /**
     * Increases the level of a given player.
     * @param player_id Player to upgrade.
     * @param level_increase Amount to increase.
     * @return PM_SUCCESS or PM_FAILURE.
     */
    PM_StatusType increaseLevel(int player_id, int level_increase);

    /**
     * Gets the highest level player ID either globally or in a group.
     * @param group_id Group ID or -1 for all.
     * @param player_id Output pointer for result.
     * @return PM_SUCCESS or PM_FAILURE.
     */
    PM_StatusType getHighestLevel(int group_id, int* player_id);

    /**
     * Gets all player IDs in order of descending level.
     * @param group_id Group ID or -1 for all.
     * @param players Output pointer to array.
     * @param num_of_players Output pointer to array size.
     * @return PM_SUCCESS or PM_FAILURE.
     */
    PM_StatusType getAllPlayersByLevel(int group_id, int** players, int* num_of_players);

    /**
     * Gets the highest-level player in each of the lowest N groups.
     * @param num_of_groups Number of groups to include.
     * @param players Output pointer to array.
     * @return PM_SUCCESS or PM_FAILURE.
     */
    PM_StatusType getGroupsHighestLevel(int num_of_groups, int** players);

private:
    Node<PlayerNodeOfGroup>* buildPlayersBST(PlayerNodeOfGroup** array, int left, int right);
    Node<LevelNode>* buildLevelsBST(LevelNode** array, int left, int right);

    void updatePlayersParents(Node<PlayerNodeOfGroup>* root);
    void updateLevelsParents(Node<LevelNode>* root);

    void oppositeInorderAux(Node<LevelNode>* root, int* arr, int* index);
    int* oppositeInorder(Node<LevelNode>* root, int* size);

    static void inorderGroups(Node<GroupNode>* min_group, int* num_of_groups, int* output);
};

#endif // PLAYERS_MANAGER_H
