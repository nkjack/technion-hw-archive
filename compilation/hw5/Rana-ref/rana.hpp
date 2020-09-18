
  #include <iostream>
	#include <sstream>
	#include <stdlib.h>
	#include <string>
	#include <map>
 #include <vector>
   using namespace std;
   
typedef struct{
  char* name;
	int offset;
  const char* type;
  char* value;
  int index;
}ID_Node;

typedef struct{
  const char* type;
  const char* value;
  int lineno;
  int reg;
  const char* label;
  vector<int>* truelist;
  vector<int>* falselist;
  vector<int>* bpbreak;
	vector<int>* bpcontinue;
}exp_t;

typedef struct{
  const char* value;
}op_t;

typedef struct{
  const char* label;
}bp_t;

typedef struct{
  const char* name;
  int index;
  vector<string>* mem_names;
  vector<string>* mem_types;
}struct_info;

typedef struct : exp_t{
  const char* name;
  const char* retType;
  vector<string>* param_names;
  vector<string>* param_types;
}function_info;

typedef struct{
  vector<string>* actual_types;
}explist_info;

typedef struct{
	vector<int>* next;
	vector<int>* bpbreak;
	vector<int>* bpcontinue;
}statement_info;
	
typedef union{
  ID_Node id;
  exp_t exp;
  op_t op;
  const char* type;
  const char* name;
  const char* value;
  statement_info statement;
  struct_info struct_types;
  function_info function_types;
  explist_info explist_types;
  bp_t bp_label;
}yystype;
  #define YYSTYPE yystype