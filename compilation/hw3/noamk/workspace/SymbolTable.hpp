#ifndef _SYMBOLTABLE_
#define _SYMBOLTABLE_

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// functions to implement
// Maketable(parent) - create a new table which is a son of a parent in the tree
// insert(table, name, type, offset) - insert variable to symbol table
// push, pop, top


enum EntryType { VARIABLE, FUNCTION };
enum Types {INT, BYTE, BOOL, STRING};
enum RetTypes { INT, BYTE, BOOL, STRING, VOID };

Types strToTypes(string s){
    if s == "INT"
        return Types.INT;
    else if s == "BYTE"
        return Types.BYTE;
    else if s == "BOOL"
        return Types.BOOL;
    else if s == "STRING"
        return Types.STRING;
    else{
        // error

    }
}

RetTypes strToRetTypes(string s){
    if s == "INT"
        return RetTypes.INT;
    else if s == "BYTE"
        return RetTypes.BYTE;
    else if s == "BOOL"
        return RetTypes.BOOL;
    else if s == "STRING"
        return RetTypes.STRING;
    else if s == "VOID"
        return RetTypes.VOID;
    else{
        // error
        
    }
}

string retTypeToStr(RetTypes rettype){
    if rettype == RetTypes.INT
        return "INT";
    else if rettype == RetTypes.BYTE
        return "BYTE";
    else if rettype == RetTypes.BOOL
        return "BOOL";
    else if rettype == RetTypes.STRING
        return "STRING";
    else if rettype == RetTypes.VOID
        return "VOID";
    else{
        // error
        
    }
}


string typeToStr(Types arg){
    if arg == Types.INT
        return "INT";
    else if arg == Types.BYTE
        return "BYTE"
    else if arg == Types.BOOL
        return "BOOL"
    else if arg == Types.STRING
        return "STRING"
    else {
        // error
    }
       
}


class TableEntry {
    public:
        string name;
        EntryType entry_type;
        int offset;

        Types type; // for VARIABLE
        
        RetTypes ret_type; // for function
        vector<Types> args_types; // for function

        // for variable
        TableEntry(string name, EntryType entry_type, int offset, Types type) : 
        name(name), entry_type(entry_type), offset(offset), type(type) {}

        // for function      
        TableEntry(string name, EntryType entry_type, int offset, RetTypes ret_type, 
            vector<Types> arguments) : 
        name(name), entry_type(entry_type), offset(offset), ret_type(ret_type), 
        args_types(arguments) {}        

}

class Table {
    public:
        vector<TableEntry*> entries;

        Table(){}

        void insertVariable(string name, Types type, int offset) {
            this->entries.push_back(new TableEntry(name, 
                                                    EntryType.VARIABLE,
                                                    offset,
                                                    type))
        }
        void insertFunction(string name, int offset, RetTypes ret_type, vector<Types> arguments){
            this->entries.push_back(new TableEntry(name,
                                                    EntryType.FUNCTION,
                                                    offset,
                                                    ret_type,
                                                    arguments));
        }

        bool containsVariable(string name){
            for (int i=0; i < entries.size(); i++){
                if ((entries[i]->name == name) && (entries[i]->EntryType == EntryType.VARIABLE)){
                    return true;
                }
            }
            return false;   
        }

        bool containsFunction(string name){
            for (int i=0; i < entries.size(); i++){
                if ((entries[i]->name == name) && (entries[i]->EntryType == EntryType.FUNCTION)){
                    return true;
                }
            }
            return false;   
        }

        Types getVariableType(string name){
            for (int i=0; i < entries.size(); i++){
                if ((entries[i]->name == name) && (entries[i]->entry_type == EntryType.VARIABLE)){
                    return entries[i]->args_types;
                }
            }  
        }

        RetTypes getFunctionRetType(string name){
            for (int i=0; i < entries.size(); i++){
                if ((entries[i]->name == name) && (entries[i]->entry_type == EntryType.FUNCTION)){
                    return entries[i]->ret_type;
                }
            }  
        }

        vector<Types> getFunctionArgs(string name){
            for (int i=0; i < entries.size(); i++){
                if ((entries[i]->name == name) && (entries[i]->entry_type == EntryType.FUNCTION)){
                    return entries[i]->ret_type;
                }
            }  
        }
}


class SymbolTable {
    public:
        vector<Table*> tables;

        void maketable(){
            tables.push_back(new Table());
        }

        void insert_variable(string name, Types type, int offset){
            // to top table
            tables.back()->insertVariable(name, type, offset);
            
        }

        void insert_function(string name, RetTypes retType, int offset, vector<Types> arguments){
            tables.back()->insertFunction(name, offset , retType, args);
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
            return tables.back()
        }

        bool checkIfIdExists(string name){
            bool found = false;
            for (int i=0; tables.size(); ++i){
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
            for (int i=0; tables.size(); ++i){
                if (tables[i]->containsVariable(name)){
                    found=true;
                }
            }
            return found;
        }

        bool checkIfFunctionExists(string name){
            bool found = false;
            for (int i=0; tables.size(); ++i){
                if (tables[i]->containFunction(name)){
                    found=true;
                }
            }
            return found;
        }

        Types getIdType(string name){
            for (int i=0; tables.size(); ++i){
                if (tables[i]->containsVariable(name)){
                    return tables[i]->getVariableType(name);
                }
            }   
        }

        RetTypes getFunctionRetType(string name){
            for (int i=0; tables.size(); ++i){
                if (tables[i]->containsFunction(name)){
                    return tables[i]->getFunctionRetType(name);
                }
            } 
        }

        vector<Types> getFunctionArgs(string name){
            for (int i=0; tables.size(); ++i){
                if (tables[i]->containsFunction(name)){
                    return tables[i]->getFunctionArgs(name);
                }
            } 
        }

}


#endif






















