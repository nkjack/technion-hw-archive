void storeRegs() {
    CodeBuffer::instance().emit("#prologue: saving regs");
    //int size = countUsed(scopes.back()) * 4;
    int size = //number of used local parameters*4
    if(size){
        CodeBuffer::instance().emit("subu $sp, $sp, "+intToString(size));
    }
      
    for (int i = 0; i < 18; ++i) {
    //    if (scopes.back()[i] == true) {
        if (/*ourscope*/.back()[i] == true) {
            //std::string sw = "sw $" +intToString(i + 8) + ", "+intToString(size-4*i) + "($sp)";
            std::string emitStoreReg = "sw $" +intToString(i + /*LowerBound (8)*/) + ", "+intToString(size-4*i) + "($sp)";
            CodeBuffer::instance().emit(emitStoreReg);
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


addu $fp, $sp, 0
jal <funcLabel>
addu $sp, $fp, 0