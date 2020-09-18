#ifndef REGISTERS_H_
#define REGISTERS_H_

#include <iostream>
#include <vector>
#include <string>
#include "bp.hpp"

std::string its(int num);

class RegistersScopes {

	std::vector<std::vector<bool> > scopes;

public:
	  RegistersScopes() : scopes() {
		scopes.push_back(initRegisterScope());
	}

  std::vector<bool> initRegisterScope(){
    std::vector<bool> registers;
    for(int i=0;i<18;i++){
      registers.push_back(false);
    }
    return registers;
  }
  
	int allocReg() {
 
       for(int i=0;i<18;i++){
         if(scopes.back()[i] == false)
           {
           scopes.back()[i] = true;
           CodeBuffer::instance().emit("#saving regs " + its(i+8));
           return i+8;
           }
       }
		return -1;
	}

  int countUsed(std::vector<bool> registers){
    int count = 0;
    for(int i=0;i<18;i++)
      if(registers[i] == true)
        count++;
    return count;
  }
	void deallocReg(int reg) {
		scopes.back()[reg - 8] = false;
	}

	void storeRegs() {
   CodeBuffer::instance().emit("#saving regs");
    int size = countUsed(scopes.back()) * 4;
    if(size)
      CodeBuffer::instance().emit("subu $sp, $sp, "+its(size));
      
		for (int i = 0; i < 18; ++i) {
			if (scopes.back()[i] == true) {
        std::string sw = "sw $" +its(i + 8) + ", "+its(size-4*i) + "($sp)";
        CodeBuffer::instance().emit(sw);
			}
		}
   		scopes.push_back(initRegisterScope());
	}

	void restoreRegs() {
    CodeBuffer::instance().emit("#restoring regs");
		scopes.pop_back();
		int accumlated_size = 4;

		for (int i = 17; i >= 0; i--) {
			if (scopes.back()[i] == true) {
		        std::string lw = "lw $" + its(i + 8) + ", " + its(accumlated_size) + "($sp)";
		        CodeBuffer::instance().emit(lw);
				accumlated_size += 4;
			}
		}
   
   if(!countUsed(scopes.back()))
      CodeBuffer::instance().emit("addu $sp, $sp, $0");
    else
      CodeBuffer::instance().emit("addu $sp, $sp, " + its(countUsed(scopes.back())*4));
	}

	void storeFPRA() {
    CodeBuffer::instance().emit("#saving FPRA");
	  CodeBuffer::instance().emit("sw $fp, 0($sp)");
		CodeBuffer::instance().emit("subu $sp, $sp, 4");
		CodeBuffer::instance().emit("sw $ra, 0($sp)");
		CodeBuffer::instance().emit("subu $sp, $sp, 4");
	}

	void restoreRAFP() {
    CodeBuffer::instance().emit("#restoring RAFP");
		CodeBuffer::instance().emit("lw $ra, 4($sp)");
		CodeBuffer::instance().emit("addu $sp, $sp, 4");
		CodeBuffer::instance().emit("lw $fp, 4($sp)");
		CodeBuffer::instance().emit("addu $sp, $sp, 4");
	}
 
};
std::string its(int num) {
	std::stringstream res;
	res << num;
	return res.str();
}

#endif /* REGISTERS_H_ */