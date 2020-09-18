#ifndef VISITOR_ROOM_H_
#define VISITOR_ROOM_H_

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "challenge.h"


struct SChallengeActivity;
typedef struct SVisitor
{
  char *visitor_name;
  int visitor_id;
  char **room_name;
  struct SChallengeActivity *current_challenge;
} Visitor;


typedef struct SChallengeActivity
{
   Challenge *challenge;
   Visitor *visitor;
   int start_time;
} ChallengeActivity;


typedef struct SChallengeRoom
{
   char *name;
   int num_of_challenges;
   ChallengeActivity *challenges;
} ChallengeRoom;


Result init_challenge_activity(ChallengeActivity *activity, Challenge *challenge);

Result reset_challenge_activity(ChallengeActivity *activity);

Result init_visitor(Visitor *visitor, char *name, int id);

Result reset_visitor(Visitor *visitor);

Result init_room(ChallengeRoom *room, char *name, int num_challenges);

Result reset_room(ChallengeRoom *room);

Result num_of_free_places_for_level(ChallengeRoom *room, Level level, int *places);

Result change_room_name(ChallengeRoom *room, char *new_name);

Result room_of_visitor(Visitor *visitor, char **room_name);

Result visitor_enter_room(ChallengeRoom *room, Visitor *visitor, Level level, int start_time);
/* the challenge to be chosen is the lexicographically named smaller one that has
   the required level. assume all names are different. */

Result visitor_quit_room(Visitor *visitor, int quit_time);


#endif // VISITOR_ROOM_H_

