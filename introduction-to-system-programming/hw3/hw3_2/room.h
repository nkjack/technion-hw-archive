/*
 * Room.h
 *
 *  Created on: May 30, 2017
 *      Author: Noam
 */

#ifndef ROOM_H_
#define ROOM_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"
#include "order.h"
#include "escaper.h"

#define TIME_LEN 5

typedef struct room *Room;

/**
 * This type defines all errors for the room.
 */
typedef enum {
	ROOM_OUT_OF_MEMORY, // You should exit program after this error
	ROOM_NULL_PARAMETER,
	ROOM_INVALID_PARAMETER,
	ROOM_NOT_AVAILABLE,
	ROOM_SUCCESS,
	ROOM_DEFAULT
} RoomResult;
/**
 * create Room with the params needed.
 *
 * @param id a positive number to identify the room
 * @param price the price for 1 visitor, the price is multiple of 4
 * @param num_ppl number of people recomend for the room
 * @param work_hr the working hours of the current room
 * @param difficulty a number between 1 to 10
 *
 * @return the Room itself, or NULL if on of the parameters is not according
 * the conventions.
 */
Room createRoom(int id, int price, int num_ppl, char* work_hr, int difficulty,
		TechnionFaculty faculty,char* company_email, RoomResult *result);

/**
 * destroy the room and free the memory.
 *
 * @param room the room to free.
 * @return void.
 */
void destroyRoom(Room room);

/**
 * free room function for implementing Set. using destroyRoom function.
 */
void freeRoomSetFunction(SetElement room);

/**
 * free room function for implementing List. using destroyRoom function.
 */
void freeRoomListFunction(ListElement room);
/**
 * copy room functions for data structures like Set and List.
 *
 * @param room the room that the function copies
 * @return new room with the same values.
 */
Room roomCopy(Room room);

/**
 * copy function for implementing Set. using roomCopy function.
 */
SetElement roomCopySetFunction(SetElement room);

/**
 * copy function for implementing List. using roomCopy function
 */
ListElement roomCopyListFunction(ListElement room);


/**
 * compare between rooms. this function compare between all the criterias of
 * room.
 *
 * @param room_1 first room
 * @param room_2 second room
 *
 * @return True if rooms are identical.
 */
bool compareRooms(Room room1, Room room2) ;
/**
 * compare between rooms. this function is for data structures like Set and
 * List.
 *
 * @param room_1 first room
 * @param room_2 second room
 *
 * @return positive number if room_1->id > room_2-> id
 * 						0  if room_1->id == room_2->id
 * 		   negative number if room_1->id < room_2->id
 */
int roomCompareById(Room room_1, Room room_2);

/**
 * compare rooms function for implemnting Set. This function uses the
 * roomCompare function above.
 */
int roomCompareByIdSetFunction(SetElement room1, SetElement room2);
/**
 * get the Id of the room.
 *
 * @param room struct
 * @return NULL if input is null, id other of the room otherwise
 */
int getRoomId(Room room);

/**
 * This function get Room for parameter and return it's Opening hour
 */
int getRoomHourOpen(Room room);
/**
 * This function get Room for parameter and return it's Closing hour
 */
int getRoomHourClose(Room room);
/**
 * This function get Room for parameter and return it's recommend number of
 * people.
 */
int getRoomNumPpl(Room room);
/**
 * This function get Room for parameter and return it's price
 */
int getRoomPrice(Room room);
/**
 * This function get Room for parameter and return it's difficulty
 */
int getRoomDifficulty(Room room);
/**
 * This function get Room for parameter and return it's faculty
 */
TechnionFaculty getRoomFaculty(Room room);
/**
 * This function get Room for parameter and return it's company email
 */
char* getRoomCompanyEmail(Room room);

#endif /* ROOM_H_ */
