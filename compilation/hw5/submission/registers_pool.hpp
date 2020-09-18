#ifndef REGISTERS_POOL_H_
#define REGISTERS_POOL_H_

#include <iostream>
#include "bp.hpp"
#include <vector>
#include <string>
#include <sstream>

#define R_BOUND_MIN 8
#define R_BOUND_MAX 25
#define R_AMOUNT 18

std::vector<bool> initializeScopeRegisters(){
    std::vector<bool> all_registers;
    for(int i=0;i<R_AMOUNT;i++){
      all_registers.push_back(false);
    }
    return all_registers;
}

int countRegistersUsed(std::vector<bool> all_registers){
	int counter = 0;
	for(int i=0;i<R_AMOUNT;i++)
	  if(all_registers[i] == true)
	    counter++;
	return counter;
}

std::string intToString(int integer) {
	std::stringstream ss;
	ss << integer;
	return ss.str();
}

// 17 register in each scope
class RegistersPool {
	std::vector<std::vector<bool> > scopes;
public:
	RegistersPool() : scopes() {
		scopes.push_back(initializeScopeRegisters());
	}

	void deallocateRegister(int register_orig_num) {
		scopes.back()[register_orig_num - R_BOUND_MIN] = false;
	}

	int allocateRegister() {
 
       for(int i=0;i<R_AMOUNT;i++){
         if(scopes.back()[i] == false)
           {
           scopes.back()[i] = true;
           return R_BOUND_MIN+i;
           }
       }
		return -1;
	}

	void storeRegsInUse() {
	   	CodeBuffer::instance().emit("#Prologue: saving regs");
	    int sizeOfAllRegisters = countRegistersUsed(scopes.back()) * 4;
	    if(sizeOfAllRegisters > 0){

	      	CodeBuffer::instance().emit("subu $sp, $sp, " + intToString(sizeOfAllRegisters));
	      
			for (int i = 0; i < R_AMOUNT; ++i) {
				if (scopes.back()[i] == true) {
					// sw $s0, 4($sp)
			        CodeBuffer::instance().emit("sw $" +intToString(i + R_BOUND_MIN) + ", "+intToString(sizeOfAllRegisters-4*(i+1)) + "($sp)");
				}
			}
		}
		scopes.push_back(initializeScopeRegisters());
	}

	void restoreRegsInUse() {
    	CodeBuffer::instance().emit("#Epilogue: saving regs");
		
		scopes.pop_back();
		int size = 0;

		for (int i = R_AMOUNT - 1; i >= 0; i--) {
			if (scopes.back()[i] == true) {
        		CodeBuffer::instance().emit("lw $" + intToString(R_BOUND_MIN + i) + ", " + intToString(size) + "($sp)");
				size += 4;
			}
		}
		
		// CodeBuffer::instance().emit("addu $sp, $sp, " + intToString(size));   
		if(countRegistersUsed(scopes.back()) == 0){
			// CodeBuffer::instance().emit("addu $sp, $sp, $0");
		}
	    else{
	    	CodeBuffer::instance().emit("addu $sp, $sp, " + intToString(countRegistersUsed(scopes.back())*4));
	    }
	}

	void storeFramePointerReturnAddress() {
 		CodeBuffer::instance().emit("#saving $fp and $ra");
		CodeBuffer::instance().emit("subu $sp, $sp, 4");
		CodeBuffer::instance().emit("sw $fp, 0($sp)");
		CodeBuffer::instance().emit("subu $sp, $sp, 4");
		CodeBuffer::instance().emit("sw $ra, 0($sp)");
		
	}

	void restoreReturnAddressFramePointer() {
		CodeBuffer::instance().emit("#restoring $ra and $fp");
		CodeBuffer::instance().emit("lw $ra, ($sp)");
		CodeBuffer::instance().emit("addu $sp, $sp, 4");
		CodeBuffer::instance().emit("lw $fp, ($sp)");
		CodeBuffer::instance().emit("addu $sp, $sp, 4");
	}

	void jumpAndLink(string funcLabel){ 
		CodeBuffer::instance().emit("addu $fp, $sp, 0");
		CodeBuffer::instance().emit("jal "+ funcLabel);
		CodeBuffer::instance().emit("addu $sp, $fp, 0");
	}


 
};


#endif /* REGISTERS_POOL_H_ */