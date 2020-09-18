#ifndef CONSTANTS_H_
#define CONSTANTS_H_

typedef enum ELevel {Easy, Medium, Hard, All_Levels} Level;

typedef enum EResult {OK, NULL_PARAMETER, MEMORY_PROBLEM, ILLEGAL_PARAMETER,
                      NOT_IN_ROOM, ALREADY_IN_ROOM, NO_AVAILABLE_CHALLENGES,
                      ILLEGAL_TIME } Result;

#endif // CONSTANTS_H_
