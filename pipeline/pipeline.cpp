#include "pipeline"
#include <queue>

/*
//fetch
input: fd
output: string
// decode
tokenizing
// loadOpcode
input: tokens
output: instruction + operands
//execute
input: instruction,operands[]
output: temp_result
//store_res
///store
*/


Pipeline &Pipeline::getInstance() {

}

Pipeline::Pipeline() : ticks(0), tasks(std::queue<Task>(0)) {
    // Some initializations
}

void Pipeline::initTable() {
    instructionTable["mov"] = commandDecomposed(mov, 2, 1);
    //add more instructions
}

void Pipeline::fetch() {
    // TODO:: Get instruction from memory[pc]
    // May be we need class Instruction
}

void Pipeline::decode() {
    // TODO:: translate received instruction to ... hz
}

void Pipeline::loadOpcode() {
    // TODO:: find opcode in opcode table
}

void Pipeline::execute() {
    // TODO:: refresh everything: ticks, regs, mem
}

void Pipeline::storeRes() {
    // TODO:: Write in memory
}
