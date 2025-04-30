#include <stdio.h>
#include "instruction_printer.h"

void print_operand(IROperand operand)
{
    switch (operand.type)
    {
    case OPERAND_LITERAL:
        printf("OPERAND_LITERAL(%d) ", operand.value.literal);
        break;
    case OPERAND_VARIABLE:
        printf("%s %d ", operand.value.variable, operand.data_type);
        break;
    case OPERAND_STRING_LITERAL:
        printf("'%s'", operand.value.string_literal);
        break;
    case OPERAND_BOOLEAN_LITERAL:
        operand.value.boolean_literal ? printf("true") : printf("false");
        break;
    case OPERAND_TEMP:
        printf("t%d", operand.value.temp_number);
        break;
    case OPERAND_LABEL:
        printf("L%d", operand.value.label_number);
        break;
    case OPERAND_NONE:
        printf("_");
        break;
    }
}

void print_ir_instruction(IRInstruction instr)
{
    printf("[");
    switch (instr.op)
    {
    case IR_ASSIGN:
        print_operand(instr.result);
        printf(" = ");
        print_operand(instr.arg1);
        break;
    case IR_ADD:
        print_operand(instr.result);
        printf(" = ");
        print_operand(instr.arg1);
        printf(" + ");
        print_operand(instr.arg2);
        break;
    case IR_SUBTRACT:
        print_operand(instr.result);
        printf(" = ");
        print_operand(instr.arg1);
        printf(" - ");
        print_operand(instr.arg2);
        break;
    case IR_MULTIPLY:
        print_operand(instr.result);
        printf(" = ");
        print_operand(instr.arg1);
        printf(" * ");
        print_operand(instr.arg2);
        break;
    case IR_DIVIDE:
        print_operand(instr.result);
        printf(" = ");
        print_operand(instr.arg1);
        printf(" / ");
        print_operand(instr.arg2);
        break;
    case IR_LABEL:
        print_operand(instr.result);
        printf(":");
        break;
    case IR_JUMPFALSE:
        printf("if ");
        print_operand(instr.arg1);
        printf(" == 0 goto ");
        print_operand(instr.result);
        break;
    case IR_JUMPTRUE:
        printf("if ");
        print_operand(instr.arg1);
        printf(" != 0 goto ");
        print_operand(instr.result);
        break;
    case IR_JUMP:
        printf("goto ");
        print_operand(instr.result);
        break;
    case IR_PRINT:
        printf("print ");
        print_operand(instr.arg1);
        break;
    case IR_RETURN:
        printf("return ");
        print_operand(instr.arg1);
        break;
    case IR_CALL:
        print_operand(instr.result);
        printf(" = call ");
        print_operand(instr.arg1);
        printf(" with ");
        print_operand(instr.arg2);
        break;
    case IR_PARAM:
        printf("param ");
        print_operand(instr.arg1);
        break;
    case IR_ARG:
        printf("arg ");
        print_operand(instr.result);
        break;
    case IR_PROLOGUE:
        printf("prologue");
        break;
    case IR_EPILOGUE:
        printf("epilogue");
        break;
    default:
        printf("UNKNOWN_OP");
        break;
    }
    printf("]");

    printf("\n");
}