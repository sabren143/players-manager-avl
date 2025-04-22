#include "library.h"
#include "PlayersManager.h"

static StatusType switchStatus(PM_StatusType type) {
    if (type == PM_SUCCESS) return SUCCESS;
    else if (type == PM_FAILURE) return FAILURE;
    else if (type == PM_INVALID_INPUT) return INVALID_INPUT;
    else if (type == PM_ALLOCATION_ERROR) return ALLOCATION_ERROR;
    return FAILURE; // Fallback
}

void* Init() {
    try {
        return static_cast<void*>(new PlayersManager());
    } catch (...) {
        return nullptr;
    }
}

StatusType AddGroup(void* DS, int groupID) {
    if (!DS || groupID <= 0) return INVALID_INPUT;
    return switchStatus(static_cast<PlayersManager*>(DS)->addGroup(groupID));
}

StatusType AddPlayer(void* DS, int playerID, int groupID, int level) {
    if (!DS || playerID <= 0 || groupID <= 0 || level < 0) return INVALID_INPUT;
    return switchStatus(static_cast<PlayersManager*>(DS)->addPlayer(playerID, groupID, level));
}

StatusType RemovePlayer(void* DS, int playerID) {
    if (!DS || playerID <= 0) return INVALID_INPUT;
    return switchStatus(static_cast<PlayersManager*>(DS)->removePlayer(playerID));
}

StatusType ReplaceGroup(void* DS, int groupID, int replacementID) {
    if (!DS || groupID <= 0 || replacementID <= 0 || groupID == replacementID) return INVALID_INPUT;
    return switchStatus(static_cast<PlayersManager*>(DS)->replaceGroup(groupID, replacementID));
}

StatusType IncreaseLevel(void* DS, int playerID, int levelIncrease) {
    if (!DS || playerID <= 0 || levelIncrease <= 0) return INVALID_INPUT;
    return switchStatus(static_cast<PlayersManager*>(DS)->increaseLevel(playerID, levelIncrease));
}

StatusType GetHighestLevel(void* DS, int groupID, int* playerID) {
    if (!DS || !playerID || groupID == 0) return INVALID_INPUT;
    return switchStatus(static_cast<PlayersManager*>(DS)->getHighestLevel(groupID, playerID));
}

StatusType GetAllPlayersByLevel(void* DS, int groupID, int** players, int* numOfPlayers) {
    if (!DS || !players || !numOfPlayers || groupID == 0) return INVALID_INPUT;
    return switchStatus(static_cast<PlayersManager*>(DS)->getAllPlayersByLevel(groupID, players, numOfPlayers));
}

StatusType GetGroupsHighestLevel(void* DS, int numOfGroups, int** players) {
    if (!DS || !players || numOfGroups < 1) return INVALID_INPUT;
    return switchStatus(static_cast<PlayersManager*>(DS)->getGroupsHighestLevel(numOfGroups, players));
}

void Quit(void** DS) {
    if (DS && *DS) {
        delete static_cast<PlayersManager*>(*DS);
        *DS = nullptr;
    }
}
