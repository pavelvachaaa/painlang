#ifndef IR_H
#define IR_H

#include <stdlib.h>
#include "../ast/ast.h"
#include "types.h"

typedef enum
{
    IR_ASSIGN,   // x = y
    IR_ADD,      // x = y + z
    IR_SUBTRACT, // x = y - z
    IR_MULTIPLY, // x = y * z
    IR_DIVIDE,   // x = y / z
    IR_LOGICAL_AND,
    IR_LOGICAL_OR,
    IR_LOGICAL_NOT,
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
    IR_PROLOGUE,
    IR_EPILOGUE,
    IR_PARAM,

    IR_CALL,
    IR_RETURN,
    IR_ARG

} IROp;

typedef enum
{
    OPERAND_NONE,
    OPERAND_LITERAL,
    OPERAND_VARIABLE,
    OPERAND_TEMP, // t1, ...
    OPERAND_LABEL,
    OPERAND_STRING_LITERAL, //"more"
    OPERAND_BOOLEAN_LITERAL

} OperandType;

typedef struct
{
    OperandType type;
    DataType data_type; // Když je operandtype variable -> ztratím informaci o datovém typu a musím se ptát symboltable
    union
    {
        int literal;
        char *variable;
        int temp_number;
        int label_number;
        char *string_literal;
        uint8_t boolean_literal;
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
    SymbolTable *symbol_table; // TODO: možná to pak čerpat jen z AST typů..
    int instruction_count;
    int temp_counter;
    int label_counter;
    // TODO: Pak smazat asi
    int current_param_index; // pozice parametru
    int current_arg_index;   // argumentu
    char *current_function;  // V jaké funkci jsem
} IRProgram;

void ir_init(IRProgram *program, SymbolTable *table);

IROperand ir_boolean_literal(uint8_t value);
IROperand ir_string_literal(const char *value);
IROperand ir_literal(int value);
IROperand ir_variable(const char *name, int is_initialized, DataType data_type);
IROperand ir_temp(IRProgram *program, DataType type);
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
void generate_nasm_from_ir(IRProgram *program, SymbolTable *table, const char *output_file);

void ir_free(IRProgram *program);

#endif // IR_H