#ifndef _SYMBOLTABLE_
#define _SYMBOLTABLE_

#include <vector>

using namespace std;

class SymbolTableEntry{
    
    public:
        string name;
        string type;
        string value;
        int offset;
    
        SymbolTableEntry(string name, string type, int offset, string value) : name(name), type(type), offset(offset), 
                        value(value){}
    
        //void setValue(string value)

};

class SymbolTable{
    public:
        vector<SymbolTableEntry> table;
        
        void insertEntry(string name, string type, int offset, string value){
            SymbolTableEntry entry(name, type, offset, value);
            this->table.push_back(entry);
        }

};


class FunctionTableEntry{
    
    public:
        string name;
        string retType;
        vector<string> argsTypes;

        FunctionTableEntry(string name, string retType) : name(name), retType(retType){}

        void insertArg(string argType){
            this->argsTypes.push_back(argType);
        }
        
};


    class FunctionTable{
    public:
        vector<FunctionTableEntry> table;

        void insertEntry(string name, string retType, vector<string> argsTypes){
            FunctionTableEntry entry(name, retType);
            for(int i=0; i<argsTypes.size(); i++){
                entry.insertArg(argsTypes[i]);
            }

            this->table.push_back(entry);
        }
    };

#endif






















