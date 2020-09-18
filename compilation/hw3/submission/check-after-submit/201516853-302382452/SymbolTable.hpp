#ifndef __SYMBOLTABLE_H
#define __SYMBOLTABLE_H

#include <vector>
#include <string>
#include <algorithm>
#include "output.hpp"

using namespace output;
using namespace std;

class TableEntry {
    public:
        string name;
        string entry_type;
        int offset;

        string type; // for VARIABLE
        string ret_type; // for function
        vector<string> args_types; // for function

        // for variable
        TableEntry(string name, string entry_type, int offset, string type) : 
        name(name), entry_type(entry_type), offset(offset), type(type) {}

        // for function      
        TableEntry(string name, string entry_type, int offset, string ret_type, 
            vector<string> arguments) : 
        name(name), entry_type(entry_type), offset(offset), ret_type(ret_type), 
        args_types(arguments) {}        

};

class Table {
    public:
        vector<TableEntry*> entries;

        Table(){}

        void insertVariable(string name, string type, int offset) {
            this->entries.push_back(new TableEntry(name, 
                                                    "VARIABLE",
                                                    offset,
                                                    type));
        }
        void insertFunction(string name, int offset, string ret_type, vector<string> arguments){
            this->entries.push_back(new TableEntry(name,
                                                    "FUNCTION",
                                                    offset,
                                                    ret_type,
                                                    arguments));
        }

        void insertFunctionPrint(){
            std::vector<string> v;
            v.push_back("STRING");
            this->entries.push_back(new TableEntry("print",
                                                    "FUNCTION",
                                                    0,
                                                    "VOID",
                                                    v));
        }

        void insertFunctionPrintI(){
            std::vector<string> v;
            v.push_back("INT");
            this->entries.push_back(new TableEntry("printi",
                                                    "FUNCTION",
                                                    0,
                                                    "VOID",
                                                    v));
        }

        bool containsVariable(string name){
            for (int i=0; i < entries.size(); i++){
                // cout << entries[i]->name << endl;
                // cout << entries[i]->entry_type << endl;
                if ((entries[i]->name == name) && (entries[i]->entry_type == "VARIABLE")){
                    return true;
                }
            }
            return false;   
        }

        bool containsFunction(string name){
            for (int i=0; i < entries.size(); i++){
                if ((entries[i]->name == name) && (entries[i]->entry_type == "FUNCTION")){
                    return true;
                }
            }
            return false;   
        }

        string getVariableType(string name){
            for (int i=0; i < entries.size(); i++){
                if ((entries[i]->name == name) && (entries[i]->entry_type == "VARIABLE")){
                    return entries[i]->type;
                }
            }  
        }

        string getFunctionRetType(string name){
            for (int i=0; i < entries.size(); i++){
                if ((entries[i]->name == name) && (entries[i]->entry_type == "FUNCTION")){
                    return entries[i]->ret_type;
                }
            }  
        }

        vector<string>& getFunctionArgs(string name){
            for (int i=0; i < entries.size(); i++){
                if ((entries[i]->name == name) && (entries[i]->entry_type == "FUNCTION")){
                    return entries[i]->args_types;
                }
            }  
        }
};


class SymbolTable {
    public:
        vector<Table*> tables;

        SymbolTable(){}

        void maketable(){
            tables.push_back(new Table());
        }

        void insertVariable(string name, string type, int offset){
            // to top table
            tables.back()->insertVariable(name, type, offset);
            
        }

        void insertFunction(string name, string retType, int offset, vector<string> arguments){
            tables.back()->insertFunction(name, offset , retType, arguments);
        }

        void insertFunctionPrint(){
            tables.back()->insertFunctionPrint();
        }

        void insertFunctionPrintI(){
            tables.back()->insertFunctionPrintI();
        }


        bool pop(){
            if (tables.size() == 0){
                return false;
            }
            else{
                tables.pop_back();
                return true;
            }
        }

        Table& top(){
            return *tables.back();
        }

        bool checkIfIdExists(string name){
            bool found = false;
            for (int i=0; i<tables.size(); ++i){
                if (tables[i]->containsVariable(name)){
                    found=true;
                }
                if (tables[i]->containsFunction(name)){
                    found=true;
                }
            }
            return found;
        }

        bool checkIfVariableExists(string name){
            bool found = false;
            for (int i=0; i < tables.size(); ++i){
                if (tables[i]->containsVariable(name)){
                    found=true;
                }
            }
            return found;
        }

        bool checkIfFunctionExists(string name){
            bool found = false;
            for (int i=0; i<tables.size(); ++i){
                if (tables[i]->containsFunction(name)){
                    found=true;
                }
            }
            return found;
        }

        string getIdType(string name){
            for (int i=0; i<tables.size(); ++i){
                if (tables[i]->containsVariable(name)){
                    return tables[i]->getVariableType(name);
                }
            }   
        }

        string getFunctionRetType(string name){
            for (int i=0; i<tables.size(); ++i){
                if (tables[i]->containsFunction(name)){
                    return tables[i]->getFunctionRetType(name);
                }
            } 
        }

        vector<string>& getFunctionArgs(string name){
            for (int i=0; i<tables.size(); ++i){
                if (tables[i]->containsFunction(name)){
                    return tables[i]->getFunctionArgs(name);
                }
            } 
        }

};


#endif






















