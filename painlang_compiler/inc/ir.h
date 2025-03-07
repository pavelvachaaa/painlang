#ifndef IR_H
#define IR_H

#include <stdlib.h>
#include "ast.h"

typedef enum
{
    IR_ASSIGN,       // x = y
    IR_ADD,          // x = y + z
    IR_SUBTRACT,     // x = y - z
    IR_MULTIPLY,     // x = y * z
    IR_DIVIDE,       // x = y / z
    IR_LABEL,        // L1:
    IR_JUMPFALSE,    // if x == 0 goto L
    IR_JUMPTRUE,     // if x != 0 goto L
    IR_JUMP,         // goto L
    IR_LESS_THAN,    // x = y < z
    IR_GREATER_THAN, // x = y > z
    IR_EQUALS,       // x = y == z
    IR_NOT_EQUALS,   // x = y != z
    IR_LESS_EQ,      // x = y <= z
    IR_GREATER_EQ,   // x = y >= z
    IR_PRINT,        // print x
    IR_PARAM,        // param x
    IR_RETURN        // return x
} IROp;

typedef enum
{
    OPERAND_NONE,
    OPERAND_LITERAL,
    OPERAND_VARIABLE,
    OPERAND_TEMP, // t1, ...
    OPERAND_LABEL
} OperandType;

typedef struct
{
    OperandType type;
    union
    {
        int literal;
        char *variable;
        int temp_number;
        int label_number;
    } value;
    int is_initialized;

} IROperand;

typedef struct
{
    IROp op;
    IROperand result;
    IROperand arg1;
    IROperand arg2;
} IRInstruction; // TAC

typedef struct
{
    IRInstruction *instructions;
    int instruction_count;
    int temp_counter;
    int label_counter;
} IRProgram;

void ir_init(IRProgram *program);

IROperand ir_literal(int value);
IROperand ir_variable(const char *name, int is_initialized);
IROperand ir_temp(IRProgram *program);
IROperand ir_label(IRProgram *program);
IROperand ir_none();

int ir_new_label(IRProgram *program);

void ir_add_instruction(IRProgram *program, IROp op, IROperand result, IROperand arg1, IROperand arg2);

// Pro IR z AST
IROperand generate_expression_ir(ASTNode *node, IRProgram *program);
void generate_statement_ir(ASTNode *node, IRProgram *program);
IROperand generate_condition_ir(ASTNode *node, IRProgram *program);

// Pro dev účely
void generate_ir_from_ast(ASTNode *node, IRProgram *program);
void output_ir_to_file(IRProgram *program, const char *filename);
void generate_nasm_from_ir(IRProgram *program, const char *output_file);

void ir_free(IRProgram *program);

#endif // IR_H