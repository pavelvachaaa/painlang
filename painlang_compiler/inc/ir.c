#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "ir.h"

void ir_init(IRProgram *program)
{
    program->instructions = NULL;
    program->instruction_count = 0;
    program->temp_counter = 0;
    program->label_counter = 0;
}

IROperand ir_literal(int value)
{
    IROperand operand;
    operand.type = OPERAND_LITERAL;
    operand.value.literal = value;
    return operand;
}

IROperand ir_variable(const char *name)
{
    IROperand operand;
    operand.type = OPERAND_VARIABLE;
    operand.value.variable = strdup(name);
    return operand;
}

IROperand ir_temp(IRProgram *program)
{
    IROperand operand;
    operand.type = OPERAND_TEMP;
    operand.value.temp_number = program->temp_counter++;
    return operand;
}

IROperand ir_label(IRProgram *program)
{
    IROperand operand;
    operand.type = OPERAND_LABEL;
    operand.value.label_number = program->label_counter++;
    return operand;
}

IROperand ir_none()
{
    IROperand operand;
    operand.type = OPERAND_NONE;
    return operand;
}

int ir_new_label(IRProgram *program)
{
    return program->label_counter++;
}

void ir_add_instruction(IRProgram *program, IROp op, IROperand result, IROperand arg1, IROperand arg2)
{
    program->instruction_count++;
    program->instructions = realloc(program->instructions, program->instruction_count * sizeof(IRInstruction));

    program->instructions[program->instruction_count - 1].op = op;
    program->instructions[program->instruction_count - 1].result = result;
    program->instructions[program->instruction_count - 1].arg1 = arg1;
    program->instructions[program->instruction_count - 1].arg2 = arg2;
}

IROp binary_op_to_ir_op(BinaryOpType op)
{
    switch (op)
    {
    case OP_ADD:
        return IR_ADD;
    case OP_SUBTRACT:
        return IR_SUBTRACT;
    case OP_MULTIPLY:
        return IR_MULTIPLY;
    case OP_DIVIDE:
        return IR_DIVIDE;
    default:
        return IR_ADD;
    }
}

// Trochu opičácký, ale nějak to přeložit musíme
// ano slyšel jsem o hashmapě
IROp cond_op_to_ir_op(CondOpType op)
{
    switch (op)
    {
    case COND_EQUALS:
        return IR_EQUALS;
    case COND_NOT_EQUALS:
        return IR_NOT_EQUALS;
    case COND_GREATER_THAN:
        return IR_GREATER_THAN;
    case COND_LESS_THAN:
        return IR_LESS_THAN;
    case COND_GREATER_OR_EQUALS:
        return IR_GREATER_EQ;
    case COND_LESS_OR_EQUALS:
        return IR_LESS_EQ;
    default:
        return IR_EQUALS;
    }
}

IROperand generate_expression_ir(ASTNode *node, IRProgram *program)
{
    if (!node)
        return ir_none();

    switch (node->type)
    {
    case NODE_NUMBER:
    {
        return ir_literal(node->data.number.value);
    }

    case NODE_VARIABLE:
    {
        return ir_variable(node->data.variable.name);
    }

    case NODE_BINARY_OP:
    {
        IROperand left = generate_expression_ir(node->data.binary_op.left, program);
        IROperand right = generate_expression_ir(node->data.binary_op.right, program);
        IROperand result = ir_temp(program);

        IROp op = binary_op_to_ir_op(node->data.binary_op.op);
        ir_add_instruction(program, op, result, left, right);

        return result;
    }

    default:
        fprintf(stderr, "To by tu být nemělo: %d\n", node->type);
        return ir_none();
    }
}

IROperand generate_condition_ir(ASTNode *node, IRProgram *program)
{
    if (!node)
        return ir_none();

    if (node->type == NODE_CONDITION)
    {
        IROperand left = generate_expression_ir(node->data.condition.left, program);
        IROperand right = generate_expression_ir(node->data.condition.right, program);
        IROperand result = ir_temp(program);

        IROp op = cond_op_to_ir_op(node->data.condition.op);
        ir_add_instruction(program, op, result, left, right);

        return result;
    }
    else if (node->type == NODE_NUMBER)
    {
        return ir_literal(node->data.number.value);
    }
    else
    {
        return generate_expression_ir(node, program);
    }
}

void generate_statement_ir(ASTNode *node, IRProgram *program)
{
    if (!node)
        return;

    switch (node->type)
    {
    case NODE_VAR_DECLARATION:
    {
        if (node->data.var_declaration.init_expr)
        {
            IROperand expr = generate_expression_ir(node->data.var_declaration.init_expr, program);
            IROperand var = ir_variable(node->data.var_declaration.var_name);

            ir_add_instruction(program, IR_ASSIGN, var, expr, ir_none());
        }
        break;
    }

    case NODE_ASSIGNMENT:
    {
        IROperand expr = generate_expression_ir(node->data.assignment.value, program);
        IROperand var = ir_variable(node->data.assignment.var_name);

        ir_add_instruction(program, IR_ASSIGN, var, expr, ir_none());
        break;
    }

    case NODE_PRINT:
    {
        IROperand expr = generate_expression_ir(node->data.print.expr, program);
        ir_add_instruction(program, IR_PRINT, ir_none(), expr, ir_none());
        break;
    }

    case NODE_IF:
    {
        IROperand condition = generate_condition_ir(node->data.if_statement.condition, program);

        int else_label = ir_new_label(program);
        int end_label = ir_new_label(program);

        // skoč do else nebo přeskoč
        ir_add_instruction(program, IR_JUMPFALSE, ir_literal(else_label), condition, ir_none());

        if (node->data.if_statement.if_block)
        {
            generate_statement_ir(node->data.if_statement.if_block, program);
        }

        if (node->data.if_statement.else_block)
        {
            ir_add_instruction(program, IR_JUMP, ir_literal(end_label), ir_none(), ir_none());
        }

        ir_add_instruction(program, IR_LABEL, ir_literal(else_label), ir_none(), ir_none());

        if (node->data.if_statement.else_block)
        {
            generate_statement_ir(node->data.if_statement.else_block, program);
            ir_add_instruction(program, IR_LABEL, ir_literal(end_label), ir_none(), ir_none());
        }

        break;
    }

    case NODE_FOR_LOOP:
        // TODO: Pozor může tam být assingment i declaration
        // IROperand iP = ir_variable(node->data.for_loop.init_expression->data.assignment.var_name);
        // int startLoop = ir_new_label(program);
        
    // Tkahle nějak by se dala zakodovat for loop;
    // i = 0
    // L1:
    // if i >= 10 goto L2
    // print i
    // i = i + 1
    // goto L1
    // L2:
        break;

    case NODE_STATEMENT_LIST:
    {
        for (int i = 0; i < node->data.statement_list.statement_count; i++)
        {
            generate_statement_ir(node->data.statement_list.statements[i], program);
        }
        break;
    }

    default:
        fprintf(stderr, "Neznám node: %d\n", node->type);
        break;
    }
}

void generate_ir_from_ast(ASTNode *node, IRProgram *program)
{
    if (!node)
        return;

    if (node->type == NODE_PROGRAM || node->type == NODE_STATEMENT_LIST)
    {
        for (int i = 0; i < node->data.statement_list.statement_count; i++)
        {
            generate_statement_ir(node->data.statement_list.statements[i], program);
        }
    }
    else
    {
        generate_statement_ir(node, program);
    }
}

char *get_operand_string(IROperand operand, char *buffer)
{
    switch (operand.type)
    {
    case OPERAND_LITERAL:
        sprintf(buffer, "%d", operand.value.literal);
        break;
    case OPERAND_VARIABLE:
        sprintf(buffer, "%s", operand.value.variable);
        break;
    case OPERAND_TEMP:
        sprintf(buffer, "t%d", operand.value.temp_number);
        break;
    case OPERAND_LABEL:
        sprintf(buffer, "L%d", operand.value.label_number);
        break;
    case OPERAND_NONE:
        sprintf(buffer, "_");
        break;
    }
    return buffer;
}

void output_ir_to_file(IRProgram *program, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "mrdej to");
        return;
    }

    char result_str[64], arg1_str[64], arg2_str[64];

    for (int i = 0; i < program->instruction_count; i++)
    {
        IRInstruction *instr = &program->instructions[i];

        switch (instr->op)
        {
        case IR_LABEL:
            fprintf(file, "L%d:\n", instr->result.value.literal);
            break;

        case IR_ASSIGN:
            fprintf(file, "%s = %s\n",
                    get_operand_string(instr->result, result_str),
                    get_operand_string(instr->arg1, arg1_str));
            break;

        case IR_ADD:
            fprintf(file, "%s = %s + %s\n",
                    get_operand_string(instr->result, result_str),
                    get_operand_string(instr->arg1, arg1_str),
                    get_operand_string(instr->arg2, arg2_str));
            break;

        case IR_SUBTRACT:
            fprintf(file, "%s = %s - %s\n",
                    get_operand_string(instr->result, result_str),
                    get_operand_string(instr->arg1, arg1_str),
                    get_operand_string(instr->arg2, arg2_str));
            break;

        case IR_MULTIPLY:
            fprintf(file, "%s = %s * %s\n",
                    get_operand_string(instr->result, result_str),
                    get_operand_string(instr->arg1, arg1_str),
                    get_operand_string(instr->arg2, arg2_str));
            break;

        case IR_DIVIDE:
            fprintf(file, "%s = %s / %s\n",
                    get_operand_string(instr->result, result_str),
                    get_operand_string(instr->arg1, arg1_str),
                    get_operand_string(instr->arg2, arg2_str));
            break;

        case IR_JUMPFALSE:
            fprintf(file, "if %s == 0 goto L%d\n",
                    get_operand_string(instr->arg1, arg1_str),
                    instr->result.value.literal);
            break;

        case IR_JUMPTRUE:
            fprintf(file, "if %s != 0 goto L%d\n",
                    get_operand_string(instr->arg1, arg1_str),
                    instr->result.value.literal);
            break;

        case IR_JUMP:
            fprintf(file, "goto L%d\n", instr->result.value.literal);
            break;

        case IR_LESS_THAN:
            fprintf(file, "%s = %s < %s\n",
                    get_operand_string(instr->result, result_str),
                    get_operand_string(instr->arg1, arg1_str),
                    get_operand_string(instr->arg2, arg2_str));
            break;

        case IR_GREATER_THAN:
            fprintf(file, "%s = %s > %s\n",
                    get_operand_string(instr->result, result_str),
                    get_operand_string(instr->arg1, arg1_str),
                    get_operand_string(instr->arg2, arg2_str));
            break;

        case IR_EQUALS:
            fprintf(file, "%s = %s == %s\n",
                    get_operand_string(instr->result, result_str),
                    get_operand_string(instr->arg1, arg1_str),
                    get_operand_string(instr->arg2, arg2_str));
            break;

        case IR_NOT_EQUALS:
            fprintf(file, "%s = %s != %s\n",
                    get_operand_string(instr->result, result_str),
                    get_operand_string(instr->arg1, arg1_str),
                    get_operand_string(instr->arg2, arg2_str));
            break;

        case IR_LESS_EQ:
            fprintf(file, "%s = %s <= %s\n",
                    get_operand_string(instr->result, result_str),
                    get_operand_string(instr->arg1, arg1_str),
                    get_operand_string(instr->arg2, arg2_str));
            break;

        case IR_GREATER_EQ:
            fprintf(file, "%s = %s >= %s\n",
                    get_operand_string(instr->result, result_str),
                    get_operand_string(instr->arg1, arg1_str),
                    get_operand_string(instr->arg2, arg2_str));
            break;

        case IR_PRINT:
            fprintf(file, "print %s\n", get_operand_string(instr->arg1, arg1_str));
            break;

        case IR_PARAM:
            fprintf(file, "param %s\n", get_operand_string(instr->arg1, arg1_str));
            break;

        case IR_RETURN:
            fprintf(file, "return %s\n", get_operand_string(instr->arg1, arg1_str));
            break;
        }
    }

    fclose(file);
}

void ir_free(IRProgram *program)
{
    for (int i = 0; i < program->instruction_count; i++)
    {
        IRInstruction *instr = &program->instructions[i];

        if (instr->result.type == OPERAND_VARIABLE)
        {
            free(instr->result.value.variable);
        }
        if (instr->arg1.type == OPERAND_VARIABLE)
        {
            free(instr->arg1.value.variable);
        }
        if (instr->arg2.type == OPERAND_VARIABLE)
        {
            free(instr->arg2.value.variable);
        }
    }

    free(program->instructions);
    program->instructions = NULL;
    program->instruction_count = 0;
    program->temp_counter = 0;
    program->label_counter = 0;
}