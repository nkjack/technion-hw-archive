#ifndef CHALLENGE_H_
#define CHALLENGE_H_

#include "constants.h"

typedef struct SChallenge
{
   int id;
   char *name;
   Level level;
   int best_time;
   int num_visits;
} Challenge;

Result init_challenge(Challenge *challenge, int id, char *name, Level level);

Result reset_challenge(Challenge *challenge);

Result change_name(Challenge *challenge, char *name);

Result set_best_time_of_challenge(Challenge *challenge, int time);

Result best_time_of_challenge(Challenge *challenge, int *time);

Result inc_num_visits(Challenge *challenge);

Result num_visits(Challenge *challenge, int *visits);

#endif // CHALLENGE_H_

