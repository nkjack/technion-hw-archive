/*
 * EscapeTechnion.h
 *
 *  Created on: May 30, 2017
 *      Author: Noam
 */

#ifndef ESCAPE_TECHNION_H_
#define ESCAPE_TECHNION_H_

#include "mtm_ex3.h"
#include "list.h"
#include "set.h"
#include "company.h"
#include "escaper.h"
#include "order.h"

typedef struct escape_technion *EscapeTechnion;

/**
 * Escape Technion Functions
 */

/**
 * this function create the escape technion ADT.
 */
EscapeTechnion createEscapeTechnion();

/**
 *	this function destroy the given escape technion ADT.
 */
void destroyEscapeTechnion(EscapeTechnion escapeTechnion);

/**
 *  this function get escapeTechnion object, email, and faculty. with the given
 *  params this function create a company and add it to the set of companies
 *  that the escape technion has.
 *
 *  @param EscapeTechnion the entire system.
 *  @param char* email of company
 *  @param faculty that the company belongs to
 *
 *  @return MTM_INVALID_PARAMETER  if param is invalid,
 *  		MTM_EMAIL_ALREADY_EXISTS if the email in escapeTechnion already
 *  									exist.
 * 			MTM_SUCCESS
 */
MtmErrorCode companyAdd(EscapeTechnion escapeTechnion, char* email, TechnionFaculty faculty);

/**
 *  this function get escapeTechnion object, email. with the given
 *  params this function remove the company that has the same email in the set
 *  of companies the the escapeTechnion contains
 *
 *  @param EscapeTechnion the entire system.
 *  @param char* email of company
 *
 *  @return MTM_INVALID_PARAMETER  if param is invalid,
 *  		MTM_COMPANY_EMAIL_DOES_NOT_EXIST if the email in escapeTechnion
 *  									doesn't exist.
 * 			MTM_RESERVATION_EXISTS - there are reservations to that particular
 * 									company.
 * 			MTM_SUCCESS
 */
MtmErrorCode companyRemove(EscapeTechnion escapeTechnion, char* email);

/**
 *  this function get escapeTechnion and other params. with the given
 *  params this function add a room to the set of rooms the the escapeTechnion
 *  contains
 *
 *  @param EscapeTechnion the entire system.
 *  @param char* email of company
 *  @param id of room = positive
 *  @param price = positive and divide by 4
 *  @param num_ppl number of people that recommended
 *  @param working_hrs hours the rooms is active
 *  @param difficulty - of the room
 *
 *  @return MTM_INVALID_PARAMETER  if param is invalid,
 *  		MTM_COMPANY_EMAIL_DOES_NOT_EXIST if the email in escapeTechnion
 *  									doesn't exist.
 * 			MTM_ID_ALREADY_EXISTS  - the room is is already exist
 * 			MTM_SUCCESS
 */
MtmErrorCode roomAdd(EscapeTechnion escapeTechnion, char* email, int id, int price, int num_ppl,
		char* working_hrs, int difficulty);

/**
 *  this function get escapeTechnion and faculty and room_id. with the given
 *  params this function remove the room from the set of rooms in the escapeTechnion
 *  escapeTechnion
 *
 *  @param EscapeTechnion the entire system.
 *  @param faculty that the room belongs to
 *  @param id of room
 *
 *  @return MTM_INVALID_PARAMETER  if param is invalid,
 * 			MTM_ID_DOES_NOT_EXIST   - the room_id is not exist in the system
 * 			MTM_RESERVATION_EXISTS - the room has resrvations
 * 			MTM_SUCCESS
 */
MtmErrorCode roomRemove(EscapeTechnion escapeTechnion, TechnionFaculty faculty, int id);

/**
 *  this function get escapeTechnion and faculty and email, skil level.
 *  with the given params this function add an escaper to the system.
 *
 *  @param EscapeTechnion the entire system.
 *  @param char* email email of escaper
 *  @param faculty faculty of escaper
 *  @param skill_level the escaper skill level
 *
 *  @return MTM_INVALID_PARAMETER  if param is invalid,
 * 			MTM_EMAIL_ALREADY_EXISTS if the email in escapeTechnion already
 *  									exist.
 * 			MTM_SUCCESS
 */
MtmErrorCode escaperAdd(EscapeTechnion escapeTechnion, char* email, TechnionFaculty faculty,
		int skill_level);

/**
 *  this function get escapeTechnion and email.
 *  with the given params this function remove the escaper with that email
 *  from the set of escapers that the system save.
 *
 *  @param EscapeTechnion the entire system.
 *  @param char* email email of escaper
 *
 *  @return MTM_INVALID_PARAMETER  if param is invalid,
 * 			MTM_CLIENT_EMAIL_DOES_NOT_EXIST if the email doesn't belong to
 * 						any escaper in the escapeTechnion Object
 * 			MTM_SUCCESS
 */
MtmErrorCode escaperRemove(EscapeTechnion escapeTechnion, char* email);

/**
 *  this function get escapeTechnion and other params.
 *  with the given params the funcion make an order to the given escaper,
 *  into a given room, in a faculty and in the given time.
 *
 *  @param EscapeTechnion the entire system.
 *  @param char* email email of escaper
 *  @param faculty faculty of room
 *  @param id id of room
 *  @param char* time - day-hour - days to the order and hour in the day
 *  @param int num_ppl
 *
 *  @return MTM_INVALID_PARAMETER  if param is invalid,
 * 			MTM_CLIENT_EMAIL_DOES_NOT_EXIST
 * 			MTM_ID_DOES_NOT_EXIST
 * 			MTM_CLIENT_IN_ROOM
 * 			MTM_ROOM_NOT_AVAILABLE
 * 			MTM_SUCCESS
 */
MtmErrorCode escaperOrder(EscapeTechnion eEscapeTechnion, char* email, TechnionFaculty faculty,
		int id, char* time, int num_ppl);

/**
 *  this function get escapeTechnion and email and number of people.
 *  and create an order to the best room for this certain situations according
 *  to a formula of the exercise.
 *
 *  this function find the soonest time available in the room that it find
 *
 *  @param EscapeTechnion the entire system.
 *  @param char* email email of escaper
 *  @param int num_ppl
 *
 *  @return MTM_INVALID_PARAMETER  if param is invalid,
 * 			MTM_CLIENT_EMAIL_DOES_NOT_EXIST
 * 			MTM_NO_ROOMS_AVAILABLE
 * 			MTM_SUCCESS
 */
MtmErrorCode escaperRecommend(EscapeTechnion escapeTechnion, char* email, int num_ppl);

/**
 * this function advance a day in the system. with this action it print to
 * a given OutputChannel all the orders the system had this current day.
 *
 * @param EscapeTechnion the entire system.
 * @param FILE* outputChannel to print into
 *
 * @return	MTM_NULL_PARAMETER if outputChannel is NULL
 * 			MTM_OUT_OF_MEMROY
 * 			MTM_SUCCESS
 */
MtmErrorCode reportDay(EscapeTechnion escapeTechnion, FILE* OutputChannel);

/**
 * this function print into the given outputChannel the faculty with the
 * highest profit, according to a certain sort.
 *
 * @param EscapeTechnion the entire system.
 * @param FILE* outputChannel to print into
 *
 * @return	MTM_NULL_PARAMETER if outputChannel is NULL
 * 			MTM_OUT_OF_MEMROY
 * 			MTM_SUCCESS
 */
MtmErrorCode reportBest(EscapeTechnion escapeTechnion, FILE* OutputChannel);

/**
 * this function return a copy of Set of companies that the escapeTechnion
 * contains
 *
 * helpful for certain situations like tests.
 */
Set getCompaniesSet(EscapeTechnion escapeTechnion);

/**
 * this function return a copy of Set of escapers that the escapeTechnion
 * contains
 *
 * helpful for certain situations like tests.
 */
Set getEscapersSet(EscapeTechnion escapeTechnion) ;

/**
 * this function return a copy of Set of orders that the escapeTechnion
 * contains
 *
 * helpful for certain situations like tests.
 */
List getOrderList(EscapeTechnion escapeTechnion) ;
#endif /* ESCAPE_TECHNION_H_ */
