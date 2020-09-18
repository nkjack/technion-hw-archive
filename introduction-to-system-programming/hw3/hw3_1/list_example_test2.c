#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "test_utilities.h"
#include "list_mtm1.h"

typedef struct Date_t* Date;
struct Date_t{
    int day;
    int month;
    int year;
};
/*////////////////////////////////////////////////////////////
 *
 * date functions
 */
void freeDate(void* date){
    free(date);
}

void* copyDate(void* date){
    Date newDate=malloc(sizeof(*newDate));
    Date copy=(Date)date;
    newDate->day=copy->day;
    newDate->month=copy->month;
    newDate->year=copy->year;
    return newDate;
}

int date_compare(ListElement first,ListElement second){
    Date date1=(Date)first;
    Date date2=(Date)second;
    return (((date1->year)*12*(date1->month)*30)+(date1->day))-(((date2->year)*12*(date2->month)*30)+(date2->day));
}

bool isASameMonth(ListElement date, ListFilterKey month) {
    Date date1=(Date)date;
    return (date1->month==*(int*)month);
}

Date dateCreate(int day, int month, int year){
    Date newDate=malloc(sizeof(*newDate));
    newDate->day=day;
    newDate->month=month;
    newDate->year=year;
    return newDate;
}
/*////////////////////////////////////////////////////////////
 *
 * string functions
 */
void freeString(void* str){
    free(str);
}
void* copyString(void* str){
    char* newStr=malloc(sizeof(*newStr)*(strlen((char*)str)+1));
    strcpy(newStr,(char*)str);
    return newStr;
}

int string_compare(ListElement first,ListElement second){
    return strlen((char*)first)-strlen((char*)second);
//	return strcmp((char*)first,(char*)second);
}


bool isShorterThan(ListElement str, ListFilterKey length) {
    return strlen((char*)str) < *(int*) length;
}
/////////////////////////////////////////////////////////////
/*///////////////////////////////////////////////////////////
 *
 * int functions
 */
void freeInt(void* num){
    free(num);
}
void* copyInt(void* num){
    int* newInt=malloc(sizeof(*newInt));
    *newInt=*(int*)num;
    return newInt;
}

int int_compare(ListElement first,ListElement second){
    return *(int*)first-*(int*)second;
}


bool isAFactor(ListElement num, ListFilterKey numFactorizing) {
    return ((*(int*)num)%(*(int*)numFactorizing)==0);
}

/**
 * List of tests, one for each function is usually a good thumb rule.
 */
////////////////////////////////////////FOR STRING///////////////////////////////////
static bool testListCreate() {
    List list=listCreate(copyString,freeString);
    ASSERT_TEST(list != NULL); //creation succeeded
    ASSERT_TEST(listInsertLast(NULL,"ohad")== LIST_NULL_ARGUMENT); //insertion due to NULL argument
    ASSERT_TEST(listInsertLast(list,"ohad")==LIST_SUCCESS);//insertion succeeded
    ASSERT_TEST(listGetSize(NULL)== -1);//get size failure
    ASSERT_TEST(listGetSize(list)== 1);//get size after first insertion
    ASSERT_TEST(listInsertLast(list,"shaked")==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)== 2);
    List list1=listCopy(list);//if you are using copy with listCreat it's checking creation as well
    ASSERT_TEST(listGetSize(list1)== 2);
    listDestroy(list);
    list=NULL;
    ASSERT_TEST(listGetSize(list)== -1);
    ASSERT_TEST(listGetSize(list1)== 2);
    listDestroy(list1);
    list1=NULL;
    return true;
}

////////////////////////////////////////FOR INT///////////////////////////////////
static bool testListCreateInt() {
    List list=listCreate(copyInt,freeInt);
    ASSERT_TEST(list != NULL); //creation succeeded
    int *num=malloc(sizeof(int)),*num2=malloc(sizeof(int));
    *num=1;
    *num2=2;
    ASSERT_TEST(listInsertLast(NULL,num)== LIST_NULL_ARGUMENT); //insertion due to NULL argument
    ASSERT_TEST(listInsertLast(list,num)==LIST_SUCCESS);//insertion succeeded
    ASSERT_TEST(listGetSize(NULL)== -1);//get size failure
    ASSERT_TEST(listGetSize(list)== 1);//get size after first insertion
    ASSERT_TEST(listInsertLast(list,num2)==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)== 2);
    List list1=listCopy(list);//if you are using copy with listCreat it's checking creation as well
    ASSERT_TEST(listGetSize(list1)== 2);
    listDestroy(list);
    list=NULL;
    ASSERT_TEST(listGetSize(list)== -1);
    ASSERT_TEST(listGetSize(list1)== 2);
    listDestroy(list1);
    list1=NULL;
    freeInt(num);
    freeInt(num2);
    return true;
}

////////////////////////////////////////FOR DATE///////////////////////////////////
static bool testListCreateDate() {
    List list=listCreate(copyDate,freeDate);
    ASSERT_TEST(list != NULL); //creation succeeded
    Date date1=dateCreate(20,11,1992);
    Date date2=dateCreate(13,5,1993);
    ASSERT_TEST(listInsertLast(NULL,date1)== LIST_NULL_ARGUMENT); //insertion due to NULL argument
    ASSERT_TEST(listInsertLast(list,date1)==LIST_SUCCESS);//insertion succeeded
    ASSERT_TEST(listGetSize(NULL)== -1);//get size failure
    ASSERT_TEST(listGetSize(list)== 1);//get size after first insertion
    ASSERT_TEST(listInsertLast(list,date2)==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)== 2);
    List list1=listCopy(list);//if you are using copy with listCreat it's checking creation as well
    ASSERT_TEST(listGetSize(list1)== 2);
    listDestroy(list);
    list=NULL;
    ASSERT_TEST(listGetSize(list)== -1);
    ASSERT_TEST(listGetSize(list1)== 2);
    listDestroy(list1);
    list1=NULL;
    freeDate(date1);
    freeDate(date2);
    return true;
}
////////////////////////////////////////FOR STRING///////////////////////////////////
static bool testListCopy() {
    List list=listCreate(copyString,freeString);
    List list1=listCopy(NULL);// checks for NULL argument
    ASSERT_TEST(list1==NULL);
    list1=listCopy(list);
    ASSERT_TEST(listGetSize(list1)== 0);//checks whether the copy succeeded
    listDestroy(list1);
    ASSERT_TEST(list != NULL);
    ASSERT_TEST(listInsertLast(list,"ohad")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"shaked")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"go")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"list")==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)== 4);
    list1=listCopy(list);
    ASSERT_TEST(listGetSize(list1)== 4);
    ListElement temp=listGetFirst(list1);
    ListElement temp1=listGetFirst(list);//from now on I check if the order is good and there is no extra link in the list
    ASSERT_TEST(strcmp((char*)temp,(char*)temp1)==0);
    listRemoveCurrent(list1);
    temp=listGetFirst(list1);
    temp1=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,(char*)temp1)==0);
    listRemoveCurrent(list);
    temp1=listGetFirst(list);
    temp1=listGetNext(list);
    temp=listGetNext(list1);
    ASSERT_TEST(strcmp((char*)temp,(char*)temp1)==0);
    ASSERT_TEST(listGetSize(list)== 3);
    ASSERT_TEST(listGetSize(list1)== 3);
    listDestroy(list);
    listDestroy(list1);
    return true;
}

////////////////////////////////////////FOR INT///////////////////////////////////
static bool testListCopyInt() {
    List list=listCreate(copyInt,freeInt);
    List list1=listCopy(NULL);// checks for NULL argument
    ASSERT_TEST(list1==NULL);
    list1=listCopy(list);
    ASSERT_TEST(listGetSize(list1)== 0);//checks whether the copy succeeded
    listDestroy(list1);
    ASSERT_TEST(list != NULL);
    int *num=malloc(sizeof(int)),*num2=malloc(sizeof(int)),*num3=malloc(sizeof(int)),*num4=malloc(sizeof(int));
    *num=1;
    *num2=2;
    *num3=3;
    *num4=4;
    ASSERT_TEST(listInsertLast(list,num)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num2)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num3)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num4)==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)== 4);
    list1=listCopy(list);
    ASSERT_TEST(listGetSize(list1)== 4);
    ListElement temp=listGetFirst(list1);
    ListElement temp1=listGetFirst(list);//from now on I check if the order is good and there is no extra link in the list
    ASSERT_TEST(int_compare(temp,temp1)==0);
    listRemoveCurrent(list1);
    temp=listGetFirst(list1);
    temp1=listGetNext(list);
    ASSERT_TEST(int_compare(temp,temp1)==0);
    listRemoveCurrent(list);
    temp1=listGetFirst(list);
    temp1=listGetNext(list);
    temp=listGetNext(list1);
    ASSERT_TEST(int_compare(temp,temp1)==0);
    ASSERT_TEST(listGetSize(list)== 3);
    ASSERT_TEST(listGetSize(list1)== 3);
    listDestroy(list);
    listDestroy(list1);
    freeInt(num);
    freeInt(num2);
    freeInt(num3);
    freeInt(num4);
    return true;
}

////////////////////////////////////////FOR STRING///////////////////////////////////
static bool testListGetSize() {
    List list=NULL;
    ASSERT_TEST(listGetSize(list)==-1);//checks NULL argument
    list=listCreate(copyString,freeString);
    ASSERT_TEST(listGetSize(list)==0);
    ASSERT_TEST(listInsertLast(list,"ohad")==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)==1);
    ASSERT_TEST(listInsertLast(list,"ohad")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"ohad")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"ohad")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"ohad")==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)==5); //checks that duplicate values are counted
    listGetFirst(list);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_INVALID_CURRENT);//checks current==NULL///FAILS HERE!! TODO:debug
    listGetFirst(list);
    listGetNext(list);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)==3);
    ASSERT_TEST(listClear(list)==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)==0);
    listDestroy(list);
    list=NULL;
    ASSERT_TEST(listGetSize(list)==-1);

    return true;
}

////////////////////////////////////////FOR INT///////////////////////////////////
static bool testListGetSizeInt() {
    List list=NULL;
    ASSERT_TEST(listGetSize(list)==-1);//checks NULL argument
    list=listCreate(copyInt,freeInt);
    int *num=malloc(sizeof(int)),*num2=malloc(sizeof(int)),*num3=malloc(sizeof(int)),
            *num4=malloc(sizeof(int)),*num5=malloc(sizeof(int));
    *num=1;
    *num2=1;
    *num3=1;
    *num4=1;
    *num5=1;
    ASSERT_TEST(listInsertLast(list,num)==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)==1);
    ASSERT_TEST(listInsertLast(list,num2)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num3)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num4)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num5)==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)==5); //checks that duplicate values are counted
    listGetFirst(list);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_INVALID_CURRENT);//checks current==NULL
    listGetFirst(list);
    listGetNext(list);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)==3);
    ASSERT_TEST(listClear(list)==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)==0);
    listDestroy(list);
    list=NULL;
    ASSERT_TEST(listGetSize(list)==-1);
    freeInt(num);
    freeInt(num2);
    freeInt(num3);
    freeInt(num4);
    freeInt(num5);
    return true;
}

////////////////////////////////////////FOR STRING///////////////////////////////////
static bool testListGetFirst() {
    List list=NULL;
    ListElement temp=listGetFirst(list);
    ASSERT_TEST(temp==NULL);//checks NULL argument
    list=listCreate(copyString,freeString);
    temp=listGetFirst(list);
    ASSERT_TEST(temp==NULL);//checks handling with empty list
    ASSERT_TEST(listInsertLast(list,"ohad")==LIST_SUCCESS);
    temp=listGetFirst(list);
    ListElement temp1=listGetCurrent(list);
    ASSERT_TEST(strcmp((char*)temp,(char*)temp1)==0);
    listDestroy(list);
    return true;
}

////////////////////////////////////////FOR INT///////////////////////////////////
static bool testListGetFirstInt() {
    List list=NULL;
    ListElement temp=listGetFirst(list);
    ASSERT_TEST(temp==NULL);//checks NULL argument
    list=listCreate(copyInt,freeInt);
    temp=listGetFirst(list);
    ASSERT_TEST(temp==NULL);//checks handling with empty list
    int *num=malloc(sizeof(int));
    *num=1;
    ASSERT_TEST(listInsertLast(list,num)==LIST_SUCCESS);
    temp=listGetFirst(list);
    ListElement temp1=listGetCurrent(list);
    ASSERT_TEST(strcmp((char*)temp,(char*)temp1)==0);
    listDestroy(list);
    freeInt(num);
    return true;
}


////////////////////////////////////////FOR STRING///////////////////////////////////
static bool testListGetNext() {
    List list=NULL;
    ListElement temp=listGetNext(list);
    ASSERT_TEST(temp==NULL);
    list=listCreate(copyString,freeString);
    ASSERT_TEST(listInsertLast(list,"ohad")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"shaked")==LIST_SUCCESS);
    temp=listGetNext(list);
    ASSERT_TEST(temp==NULL);//checks NULL argument
    temp=listGetFirst(list);
    ASSERT_TEST(strcmp((char*)temp,"ohad")==0);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"shaked")==0);
    temp=listGetNext(list);//checks handling the end of the list
    ASSERT_TEST(temp==NULL);
    listGetFirst(list);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    temp=listGetFirst(list);
    ASSERT_TEST(strcmp((char*)temp,"shaked")==0);
    temp=listGetNext(list);
    ASSERT_TEST(temp==NULL);//checks that there is no extra link on list to get next from after removing first link
    listDestroy(list);
    return true;
}


////////////////////////////////////////FOR INT///////////////////////////////////
static bool testListGetNextInt() {
    List list=NULL;
    ListElement temp=listGetNext(list);
    ASSERT_TEST(temp==NULL);
    list=listCreate(copyInt,freeInt);
    int *num=malloc(sizeof(int)),*num2=malloc(sizeof(int));
    *num=12;
    *num2=150;
    ASSERT_TEST(listInsertLast(list,num)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num2)==LIST_SUCCESS);
    temp=listGetNext(list);
    ASSERT_TEST(temp==NULL);//checks NULL argument
    temp=listGetFirst(list);
    int bla=12;
    ASSERT_TEST(int_compare(temp,&bla)==0);
    temp=listGetNext(list);
    bla=150;
    ASSERT_TEST(int_compare(temp,&bla)==0);
    temp=listGetNext(list);//checks handling the end of the list
    ASSERT_TEST(temp==NULL);
    listGetFirst(list);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    temp=listGetFirst(list);
    ASSERT_TEST(int_compare(temp,&bla)==0);
    temp=listGetNext(list);
    ASSERT_TEST(temp==NULL);//checks that there is no extra link on list to get next from after removing first link
    listDestroy(list);
    freeInt(num);
    freeInt(num2);
    return true;
}


static bool testListInsertFirst() {
    List list=NULL;
    ASSERT_TEST(listInsertFirst(list,"kimchi")==LIST_NULL_ARGUMENT);//NULL argument
    list=listCreate(copyString,freeString);
    ASSERT_TEST(listInsertFirst(list,"ohad")==LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(list,"shaked")==LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(list,"kimchi")==LIST_SUCCESS);
    ListElement temp=listGetFirst(list);//gonna check order if insertion was good
    ASSERT_TEST(strcmp((char*)temp,"kimchi")==0);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    temp=listGetFirst(list);
    ASSERT_TEST(strcmp((char*)temp,"shaked")==0);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"ohad")==0);
    listDestroy(list);
    return true;
}

static bool testListInsertLast() {
    List list=NULL;
    ASSERT_TEST(listInsertLast(list,"kimchi")==LIST_NULL_ARGUMENT);
    list=listCreate(copyString,freeString);
    ASSERT_TEST(listInsertLast(list,"ohad")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"kimchi")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"shaked")==LIST_SUCCESS);
    ListElement temp=listGetFirst(list);
    ASSERT_TEST(strcmp((char*)temp,"ohad")==0);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    listGetFirst(list);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"shaked")==0);
    ASSERT_TEST(listInsertLast(list,"ohad")==LIST_SUCCESS);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"ohad")==0);
    listDestroy(list);
    return true;
}


////////////////////////////////////////FOR STRING///////////////////////////////////
static bool testListInsertBeforeCurrent() {
    List list=NULL;
    ASSERT_TEST(listInsertBeforeCurrent(list,"kimchi")==LIST_NULL_ARGUMENT);
    list=listCreate(copyString,freeString);
    ASSERT_TEST(listInsertLast(list,"ohad")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"shaked")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"the")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"kings")==LIST_SUCCESS);
    ListElement temp=listGetFirst(list);
    ASSERT_TEST(strcmp((char*)temp,"ohad")==0);
    listGetNext(list);
    listGetNext(list);
    ASSERT_TEST(listInsertBeforeCurrent(list,"aren't")==LIST_SUCCESS);
    temp=listGetFirst(list);
    ASSERT_TEST(strcmp((char*)temp,"ohad")==0);
    listGetNext(list);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"aren't")==0);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    ASSERT_TEST(listInsertBeforeCurrent(list,"wait, what?")==LIST_INVALID_CURRENT);
    temp=listGetFirst(list);
    ASSERT_TEST(strcmp((char*)temp,"ohad")==0);
    listGetNext(list);
    temp=listGetNext(list);
    ASSERT_TEST(listInsertBeforeCurrent(list,"ARE")==LIST_SUCCESS);
    temp=listGetFirst(list);
    ASSERT_TEST(strcmp((char*)temp,"ohad")==0);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"shaked")==0);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"ARE")==0);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"the")==0);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"kings")==0);
    temp=listGetNext(list);
    ASSERT_TEST(temp==NULL);
    ASSERT_TEST(listInsertBeforeCurrent(list,"that's more like it")==LIST_INVALID_CURRENT);
    listDestroy(list);
    return true;
}

////////////////////////////////////////FOR INT///////////////////////////////////
static bool testListInsertBeforeCurrentInt() {
    List list=NULL;
    ASSERT_TEST(listInsertBeforeCurrent(list,"kimchi")==LIST_NULL_ARGUMENT);
    list=listCreate(copyInt,freeInt);
    int *num=malloc(sizeof(int)),*num2=malloc(sizeof(int)),*num3=malloc(sizeof(int)),
            *num4=malloc(sizeof(int));
    *num=1;
    *num2=3;
    *num3=3;
    *num4=7;
    ASSERT_TEST(listInsertLast(list,num)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num2)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num3)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num4)==LIST_SUCCESS);
    ListElement temp=listGetFirst(list);
    int bla=1;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    listGetNext(list);
    listGetNext(list);
    *num=6;
    ASSERT_TEST(listInsertBeforeCurrent(list,num)==LIST_SUCCESS);
    temp=listGetFirst(list);
    ASSERT_TEST(int_compare(&bla,temp)==0);
    listGetNext(list);
    temp=listGetNext(list);
    bla=6;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    ASSERT_TEST(listInsertBeforeCurrent(list,num)==LIST_INVALID_CURRENT);
    temp=listGetFirst(list);
    bla=1;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    listGetNext(list);
    temp=listGetNext(list);
    *num=2;
    ASSERT_TEST(listInsertBeforeCurrent(list,num)==LIST_SUCCESS);
    temp=listGetFirst(list);
    bla=1;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(list);
    bla=3;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(list);
    bla=2;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(list);
    bla=3;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(list);
    bla=7;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(list);
    ASSERT_TEST(temp==NULL);
    ASSERT_TEST(listInsertBeforeCurrent(list,num3)==LIST_INVALID_CURRENT);
    listDestroy(list);
    freeInt(num);
    freeInt(num2);
    freeInt(num3);
    freeInt(num4);
    return true;
}


static bool testListInsertAfterCurrent() {
    List list=NULL;
    ASSERT_TEST(listInsertAfterCurrent(list,"kimchi")==LIST_NULL_ARGUMENT);
    list=listCreate(copyString,freeString);
    ASSERT_TEST(listInsertLast(list,"are")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"we")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"really")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"again?")==LIST_SUCCESS);
    ListElement temp=listGetFirst(list);
    listGetNext(list);
    temp=listGetNext(list);
    ASSERT_TEST(listInsertAfterCurrent(list,"together")==LIST_SUCCESS);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    ASSERT_TEST(listInsertAfterCurrent(list,"like")==LIST_INVALID_CURRENT);
    listGetFirst(list);
    listGetNext(list);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"together")==0);
    listGetNext(list);
    ASSERT_TEST(listInsertAfterCurrent(list,"NOPE")==LIST_SUCCESS);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"NOPE")==0);
    listDestroy(list);
    return true;
}


static bool testListRemoveCurrent() {
    List list=NULL;
    ASSERT_TEST(listRemoveCurrent(list)==LIST_NULL_ARGUMENT);//kimchi
    list=listCreate(copyString,freeString);
    ASSERT_TEST(listInsertLast(list,"no")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"ideas")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"right")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"now")==LIST_SUCCESS);
    ListElement temp=listGetFirst(list);
    listGetNext(list);
    listGetNext(list);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_INVALID_CURRENT);
    listGetFirst(list);
    listGetNext(list);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"now")==0);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)==2);
    listGetFirst(list);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_SUCCESS);
    temp=listGetFirst(list);
    ASSERT_TEST(strcmp((char*)temp,"ideas")==0);
    ASSERT_TEST(listGetSize(list)==1);
    listDestroy(list);
    return true;
}

////////////////////////////////////////FOR STRING///////////////////////////////////
static bool testListSort() {
    List list=NULL;
    ASSERT_TEST(listSort(list,string_compare)==LIST_NULL_ARGUMENT);//kimchi
    list=listCreate(copyString,freeString);
    ASSERT_TEST(listSort(list,NULL)==LIST_NULL_ARGUMENT);
    ASSERT_TEST(listInsertLast(list,"extazy")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"alcohol")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"green")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"hash")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"coc")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"MD")==LIST_SUCCESS);
    ASSERT_TEST(listSort(list,string_compare)==LIST_SUCCESS);
    ListElement temp=listGetFirst(list);
    ASSERT_TEST(strcmp((char*)temp,"MD")==0);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"coc")==0);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"hash")==0);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"green")==0);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"extazy")==0);
    temp=listGetNext(list);
    ASSERT_TEST(strcmp((char*)temp,"alcohol")==0);
    temp=listGetNext(list);
    listDestroy(list);
    return true;
}

////////////////////////////////////////FOR INT///////////////////////////////////
static bool testListSortInt() {
    List list=NULL;
    ASSERT_TEST(listSort(list,int_compare)==LIST_NULL_ARGUMENT);//kimchi
    list=listCreate(copyInt,freeInt);
    ASSERT_TEST(listSort(list,NULL)==LIST_NULL_ARGUMENT);//NULL argument
    int *num=malloc(sizeof(int)),*num2=malloc(sizeof(int)),*num3=malloc(sizeof(int)),
            *num4=malloc(sizeof(int)),*num5=malloc(sizeof(int)),*num6=malloc(sizeof(int));
    *num=50;
    *num2=13;
    *num3=3;
    *num4=8;
    *num5=7;
    *num6=49;
    ASSERT_TEST(listInsertLast(list,num)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num2)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num3)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num4)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num5)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num6)==LIST_SUCCESS);
    ASSERT_TEST(listSort(list,int_compare)==LIST_SUCCESS);
    ListElement temp=listGetFirst(list);
    int bla=3;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(list);
    bla=7;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(list);
    bla=8;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(list);
    bla=13;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(list);
    bla=49;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(list);
    bla=50;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(list);
    listDestroy(list);
    freeInt(num);
    freeInt(num2);
    freeInt(num3);
    freeInt(num4);
    freeInt(num5);
    freeInt(num6);
    return true;
}

////////////////////////////////////////FOR DATE///////////////////////////////////
static bool testListSortDate() {
    List list=NULL;
    ASSERT_TEST(listSort(list,date_compare)==LIST_NULL_ARGUMENT);//kimchi
    list=listCreate(copyDate,freeDate);
    ASSERT_TEST(listSort(list,NULL)==LIST_NULL_ARGUMENT);
    Date date1=dateCreate(2,5,1958);
    Date date2=dateCreate(13,8,2015);
    Date date3=dateCreate(2,2,1933);
    Date date4=dateCreate(13,8,2008);
    Date date5=dateCreate(13,8,2004);
    Date date6=dateCreate(13,8,2007);
    ASSERT_TEST(listInsertLast(list,date1)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,date2)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,date3)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,date4)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,date5)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,date6)==LIST_SUCCESS);
    ASSERT_TEST(listSort(list,date_compare)==LIST_SUCCESS);
    ListElement temp=listGetFirst(list);
    ASSERT_TEST(date_compare(temp,date3)==0);
    temp=listGetNext(list);
    ASSERT_TEST(date_compare(temp,date1)==0);
    temp=listGetNext(list);
    ASSERT_TEST(date_compare(temp,date5)==0);
    temp=listGetNext(list);
    ASSERT_TEST(date_compare(temp,date6)==0);
    temp=listGetNext(list);
    ASSERT_TEST(date_compare(temp,date4)==0);
    temp=listGetNext(list);
    ASSERT_TEST(date_compare(temp,date2)==0);
    temp=listGetNext(list);
    listDestroy(list);
    freeDate(date1);
    freeDate(date2);
    freeDate(date3);
    freeDate(date4);
    freeDate(date5);
    freeDate(date6);
    return true;
}

static bool testListClear() {
    List list=NULL;
    ASSERT_TEST(listClear(list)==LIST_NULL_ARGUMENT);//kimchi
    list=listCreate(copyString,freeString);
    ASSERT_TEST(listClear(list)==LIST_SUCCESS);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_INVALID_CURRENT);
    ASSERT_TEST(listInsertLast(list,"no")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"ideas")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"right")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"now")==LIST_SUCCESS);
    ASSERT_TEST(listGetSize(list)==4);
    ASSERT_TEST(listClear(list)==LIST_SUCCESS);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_INVALID_CURRENT);
    ASSERT_TEST(listGetSize(list)==0);
    ASSERT_TEST(listInsertLast(list,"no")==LIST_SUCCESS);
    ASSERT_TEST(listClear(list)==LIST_SUCCESS);
    ASSERT_TEST(listRemoveCurrent(list)==LIST_INVALID_CURRENT);
    ASSERT_TEST(listGetSize(list)==0);
    listDestroy(list);
    return true;
}

static bool testListDestroy() {
    List list=NULL;
    list=listCreate(copyString,freeString);
    ASSERT_TEST(listInsertLast(list,"seriously...")==LIST_SUCCESS);
    listDestroy(list);
    return true;
}


////////////////////////////////////////FOR STRING///////////////////////////////////
static bool testListFilter() {
    List list=NULL;
    int length=5;
    list=listFilter(list,isShorterThan,&length);
    ASSERT_TEST(list==NULL);//kimchi
    list=listCreate(copyString,freeString);
    List filtered=listFilter(list,NULL,&length);
    ASSERT_TEST(filtered==NULL);
    ASSERT_TEST(listInsertLast(list,"extazy")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"alcohol")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"green")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"hash")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"coc")==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,"MD")==LIST_SUCCESS);
    filtered=listFilter(list,isShorterThan,&length);
    listGetFirst(filtered); // TODO - WHAT THE HELL? I ADDED THIS
    ListElement temp=listGetCurrent(filtered);
    ASSERT_TEST(listGetSize(filtered)==3);
    ASSERT_TEST(strcmp((char*)temp,"hash")==0);
    temp=listGetNext(filtered);
    ASSERT_TEST(strcmp((char*)temp,"coc")==0);
    temp=listGetNext(filtered);
    ASSERT_TEST(strcmp((char*)temp,"MD")==0);
    temp=listGetNext(filtered);
    ASSERT_TEST(temp==NULL);
    ASSERT_TEST(listSort(filtered,string_compare)==LIST_SUCCESS);
    temp=listGetFirst(filtered);
    ASSERT_TEST(strcmp((char*)temp,"MD")==0);
    temp=listGetNext(filtered);
    ASSERT_TEST(strcmp((char*)temp,"coc")==0);
    temp=listGetNext(filtered);
    ASSERT_TEST(strcmp((char*)temp,"hash")==0);
    listDestroy(filtered);
    listDestroy(list);
    return true;
}

////////////////////////////////////////FOR INT///////////////////////////////////
static bool testListFilterInt() {
    List list=NULL;
    int factor=7;
    list=listFilter(list,isAFactor,&factor);
    ASSERT_TEST(list==NULL);//kimchi
    list=listCreate(copyInt,freeInt);
    List filtered=listFilter(list,NULL,&factor);
    int *num=malloc(sizeof(int)),*num2=malloc(sizeof(int)),*num3=malloc(sizeof(int)),
            *num4=malloc(sizeof(int)),*num5=malloc(sizeof(int)),*num6=malloc(sizeof(int));
    *num=50;
    *num2=13;
    *num3=3;
    *num4=8;
    *num5=7;
    *num6=49;
    ASSERT_TEST(listInsertLast(list,num)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num2)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num3)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num4)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num5)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,num6)==LIST_SUCCESS);
    filtered=listFilter(list,isAFactor,&factor);
    listGetFirst(filtered);//TODO - I ADDED IT
    ListElement temp=listGetCurrent(filtered);
    ASSERT_TEST(listGetSize(filtered)==2);
    int bla=7;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(filtered);
    bla=49;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(filtered);
    ASSERT_TEST(temp==NULL);
    ASSERT_TEST(listSort(filtered,int_compare)==LIST_SUCCESS);
    temp=listGetFirst(filtered);
    bla=7;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    temp=listGetNext(filtered);
    bla=49;
    ASSERT_TEST(int_compare(&bla,temp)==0);
    listDestroy(filtered);
    listDestroy(list);
    freeInt(num);
    freeInt(num2);
    freeInt(num3);
    freeInt(num4);
    freeInt(num5);
    freeInt(num6);
    return true;
}

////////////////////////////////////////FOR DATE///////////////////////////////////
static bool testListFilterDate() {
    List list=NULL;
    int month=8;
    list=listFilter(list,isShorterThan,&month);
    ASSERT_TEST(list==NULL);//kimchi
    list=listCreate(copyDate,freeDate);
    List filtered=listFilter(list,NULL,&month);
    ASSERT_TEST(filtered==NULL);
    Date date1=dateCreate(2,5,1958);
    Date date2=dateCreate(13,8,2015);
    Date date3=dateCreate(2,2,1933);
    Date date4=dateCreate(13,8,2008);
    Date date5=dateCreate(13,8,2004);
    Date date6=dateCreate(13,8,2007);
    ASSERT_TEST(listInsertLast(list,date1)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,date2)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,date3)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,date4)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,date5)==LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(list,date6)==LIST_SUCCESS);
    filtered=listFilter(list,isASameMonth,&month);
    ListElement temp=listGetFirst(filtered);
    ASSERT_TEST(date_compare(temp,date2)==0);
    temp=listGetNext(filtered);
    ASSERT_TEST(date_compare(temp,date4)==0);
    temp=listGetNext(filtered);
    ASSERT_TEST(date_compare(temp,date5)==0);
    temp=listGetNext(filtered);
    ASSERT_TEST(date_compare(temp,date6)==0);
    listDestroy(list);
    listDestroy(filtered);
    freeDate(date1);
    freeDate(date2);
    freeDate(date3);
    freeDate(date4);
    freeDate(date5);
    freeDate(date6);
    return true;
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    RUN_TEST(testListCreate);
    RUN_TEST(testListCopy);
    RUN_TEST(testListGetSize);
    RUN_TEST(testListGetFirst);
    RUN_TEST(testListGetNext);
    RUN_TEST(testListInsertFirst);
    RUN_TEST(testListInsertLast);
    RUN_TEST(testListInsertBeforeCurrent);
    RUN_TEST(testListInsertAfterCurrent);
    RUN_TEST(testListRemoveCurrent);
    RUN_TEST(testListSort);
    RUN_TEST(testListClear);
    RUN_TEST(testListDestroy);
    RUN_TEST(testListFilter);
    RUN_TEST(testListCreateInt);
    RUN_TEST(testListCopyInt);
    RUN_TEST(testListGetSizeInt);
    RUN_TEST(testListGetFirstInt);
    RUN_TEST(testListGetNextInt);
    RUN_TEST(testListInsertBeforeCurrentInt);
    RUN_TEST(testListSortInt);
    RUN_TEST(testListFilterInt);
    RUN_TEST(testListCreateDate);
    RUN_TEST(testListSortDate);
    RUN_TEST(testListFilterDate);
    return 0;
}
