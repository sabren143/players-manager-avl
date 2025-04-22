#ifndef LIBRARY_H
#define LIBRARY_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum {
        SUCCESS = 0,
        FAILURE = -1,
        ALLOCATION_ERROR = -2,
        INVALID_INPUT = -3
    } StatusType;

    void* Init();

    StatusType AddGroup(void* DS, int groupID);
    StatusType AddPlayer(void* DS, int playerID, int groupID, int level);
    StatusType RemovePlayer(void* DS, int playerID);
    StatusType ReplaceGroup(void* DS, int groupID, int replacementID);
    StatusType IncreaseLevel(void* DS, int playerID, int levelIncrease);
    StatusType GetHighestLevel(void* DS, int groupID, int* playerID);
    StatusType GetAllPlayersByLevel(void* DS, int groupID, int** players, int* numOfPlayers);
    StatusType GetGroupsHighestLevel(void* DS, int numOfGroups, int** players);
    void Quit(void** DS);

#ifdef __cplusplus
}
#endif

#endif // LIBRARY_H
