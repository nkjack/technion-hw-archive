/*
 * Company.h
 *
 *  Created on: May 30, 2017
 *      Author: Noam
 */

#ifndef COMPANY_H_
#define COMPANY_H_

#include "mtm_ex3.h"
#include "room.h"
#include "set.h"
#include "list.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct company *Company;

/**
 * This type defines all errors for the company.
 */
typedef enum {
	COMPANY_OUT_OF_MEMORY, // You should exit program after this error
	COMPANY_NULL_PARAMETER,
	COMPANY_INVALID_PARAMETER,
	COMPANY_ROOM_ALREADY_EXIST,
	COMPANY_ROOM_DOES_NOT_EXIST,
	COMPANY_ROOM_NOT_AVAILABLE,
	COMPANY_SUCCESS,
	COMPANY_DEFAULT
} CompanyResult;
/**
 * Company Data Type
 */

/**
 * create company in the system with the email and faculty as input.
 * the identification between companies will be the email.
 *
 * @param email the email which the company will have
 * @param faculty the faculty which the company will be under.
 * @param CompanyResult* result for output
 *
 * @return Company object. NULL if one of the parameters are null, or if there
 * are problems with memory allocating.
 */
Company createCompany(char* email, TechnionFaculty faculty,
		CompanyResult* companyResult);

/**
 * destroy the company, free all its elements memory and free itself.
 *
 * @param company object.
 * @return CompanyResult an Enum result.
 */
void destroyCompany(Company company);

/**
 * free company for implementing Set. Using the Destroy function of Company.
 */
void freeCompanySetFunction(SetElement company);

/**
 * free company for implementing List. Using the Destroy function of Company.
 */
void freeCompanyListFunction(ListElement company);
/**
 * copy company. create a new company with the same values as the company from
 * the input. this function use the createCompany function to create the
 * new Company.
 *
 * @param company the object to copy the values from
 * @return company with the same values as the inputed, or NULL if some memory
 * allocations happened.
 */
Company companyCopy(Company company);

/**
 * copy function for implementing Set.
 */
SetElement companyCopySetFunction(SetElement company);

/**
 * copy function for implementing List.
 */
ListElement companyCopyListFunction(ListElement company);

/**
 * This function use the strcmp from the string library. It uses the function
 * on the emails of the companies. Means, it compares the emails of the first
 * companies to the email of the second one.
 *
 * @param company_1 first escaper
 * @param company_2 second escaper
 *
 * @return int according to the strcmp function.
 */
int companyCompareEmails(SetElement company_1, SetElement company_2);

/**
 * This function compares the faculty of the first
 * companies to the faculty of the second one.
 *
 * @param company_1 first escaper
 * @param company_2 second escaper
 *
 * @return int like standard comparing function, according to the the facutly
 * integer.
 */
int companyCompareFaculties(SetElement company_1, SetElement company_2);

/**
 * add a room to the current company. this function check if the room is not
 * already exist in the company, if yes the function will return the right
 * result, and if not it will add the room into the set of rooms of the company.
 *
 * @param company the company to add the room into
 * @param room the room to add into the company
 *
 * @return MtmErrorCode an Enum result, it will return the correct message
 * depends on the situation.
 */
CompanyResult addRoomToCompany(Company company, Room room);

/**
 * remove a room from the set of the company, first the function search for the
 * room according to the id parameter. If the room exist then the
 * function will remove it from the company.
 *
 * @param company the company that the function removes the room from
 * @param id and id of the room
 *
 * @return MtmErrorCode an Enum result, it will return the correct message
 * depends on the situation.
 */
CompanyResult removeRoomFromCompany(Company company, int id);

/**
 * get the email of a company from the struct.
 *
 * @param company struct
 * @return NULL if parameter is wrong or problem with memory allocations,
 * the copy of the company's email if otherwise.
 */
char* getCompanyEmail(Company company);

/**
 * get The TechnionFaculty Enum of what the company belongs to.
 *
 * @param company the Company that belongs to a certain faculty
 * @return TechnionFaculty Enum, an id of a faculty.
 */
TechnionFaculty getCompanyFaculty(Company company);

/**
 * This function checks if a certain company has a room with a certain id.
 * and return true if yes and false otherwise.
 *
 * @param company the ADT that contain rooms Set
 * @param id the id of a room that the function searches;
 *
 * @return True if the company has a room with the Id, and false otherwise.
 */
bool checkCompanyHasRoomWithId(Company company, int id);

/**
 * This function find a room in the company Set of rooms, and return the price
 * of that room.
 *
 * @param company to search the room inside it
 * @param room_id the room that the function search for
 *
 * @return int price, the price of the room with the inputed id.
 */
int getRoomPriceFromCompany(Company company, int room_id);

/**
 * This function find a room in the company Set of rooms, and return the
 * difficulty of that room.
 *
 * @param company to search the room inside it
 * @param room_id the room that the function search for
 *
 * @return int difficulty, the level of the room with the inputed id.
 */
int getRoomDifficultyFromCompany(Company company, int room_id);

/**
 * create a new list and insert all the rooms the company has into the list.
 * each room is a copy.
 *
 * @param company the company which the function takes the set of rooms from.
 *
 *@return NULL - if one of the parameters is NULL or allocations failed.
 *  		A new List in case of success.
 */
List companyGetListOfRooms(Company company);

/**
 * This function return a copy of all the room of the company that get as
 * input.
 *
 * @param company
 *
 * @return Set of companies. NULL if problem with memory allocations.
 */
Set getCopyOfAllRooms(Company company);

/**
 * This function return the amount of rooms in the a certain company
 *
 * @param Company
 * @return int size of set of rooms in company.
 */
int companyGetSizeOfRooms(Company company);

#endif /* COMPANY_H_ */
