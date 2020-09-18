#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "challenge_system.h"

#define ASSERT(test_number, test_condition)  \
   if (!(test_condition)) {printf("\nTEST %s FAILED", test_number); } \
   else printf("\nTEST %s OK", test_number);


int maiaa(int argc, char **argv)
{

   ChallengeRoomSystem *sys=NULL;
   Result r=OK;

   r=create_system("test_1.txt", &sys);

   r=visitor_arrive(sys, "room_2", "visitor_1", 201, Medium, 5);

   r=visitor_arrive(sys, "room_1", "visitor_2", 202, Easy, 8);

   r=visitor_quit(sys, 203, 10);
   ASSERT("1.1" , r==NOT_IN_ROOM)

   r=visitor_quit(sys, 201, 9);
   ASSERT("1.2" , r==OK)

   int time;
   r=best_time_of_system_challenge(sys, "challenge_2", &time);
   ASSERT("1.3" , time==4)

   r=change_system_room_name(sys, "room_1", "room_111");

   r=visitor_arrive(sys, "room_1", "visitor_3", 203, Easy, 8);
   ASSERT("1.4" , r==ILLEGAL_TIME)

   r=visitor_arrive(sys, "room_111", "visitor_3", 203, Easy, 8);
   ASSERT("1.5" , r==ILLEGAL_TIME)

   r=visitor_arrive(sys, "room_111", "visitor_3", 203, Easy, 15);
   ASSERT("1.6" , r==OK)

   r=visitor_arrive(sys, "room_111", "visitor_4", 204, Easy, 16);
   ASSERT("1.7" , r==NO_AVAILABLE_CHALLENGES)

   r=change_challenge_name(sys, 11, "challenge_1111");

   r=best_time_of_system_challenge(sys, "challenge_1111", &time);

   ASSERT("1.8" , time==0)

   char *namep=NULL;
   r=most_popular_challenge(sys, &namep);
   ASSERT("1.9" , namep!=NULL && strcmp(namep, "challenge_1111")==0)
   free(namep);

   char *room=NULL;
   r=system_room_of_visitor(sys, "visitor_4", &room);
   ASSERT("1.10" , r==NOT_IN_ROOM)
   free(room);

   r=system_room_of_visitor(sys, "visitor_3", &room);
   ASSERT("1.11" , r==OK && room!=NULL && strcmp(room, "room_111")==0)
   free(room);

   r=all_visitors_quit(sys, 17);

   r=best_time_of_system_challenge(sys, "challenge_1111", &time);
   ASSERT("1.12" , time==9)

   r=best_time_of_system_challenge(sys, "challenge_4", &time);
   ASSERT("1.13" , time==2)

   char *most_popular_challenge=NULL, *challenge_best_time=NULL;
   r=destroy_system(sys, 18, &most_popular_challenge, &challenge_best_time);
   ASSERT("1.14" , most_popular_challenge!=NULL && strcmp(most_popular_challenge, "challenge_1111")==0)
   ASSERT("1.15" , challenge_best_time!=NULL && strcmp(challenge_best_time, "challenge_4")==0)

   free(most_popular_challenge);

   free(challenge_best_time);

   return 0;
}

