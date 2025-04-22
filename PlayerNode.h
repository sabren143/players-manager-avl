//
// Created by sabre on 22/04/2025.
//

#ifndef PLAYERNODE_H
#define PLAYERNODE_H

class PlayerNode {
public:
    int player_id;
    int level;
    int group_id;

    // Constructor
    explicit PlayerNode(int player_id, int level, int group_id)
        : player_id(player_id), level(level), group_id(group_id) {}

    // Default destructor
    ~PlayerNode() = default;

    // Comparison operators based on player_id
    bool operator==(const PlayerNode& other) const {
        return player_id == other.player_id;
    }

    bool operator>(const PlayerNode& other) const {
        return player_id > other.player_id;
    }

    bool operator<(const PlayerNode& other) const {
        return player_id < other.player_id;
    }

    bool operator<=(const PlayerNode& other) const {
        return player_id <= other.player_id;
    }

    bool operator>=(const PlayerNode& other) const {
        return player_id >= other.player_id;
    }
};


#endif //PLAYERNODE_H
