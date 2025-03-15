#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ir.h"
#include "../printers/ir/instruction_printer.h"

IROperand generate_function_call_ir(ASTNode *node, IRProgram *program);

void ir_init(IRProgram *program, SymbolTable *table)
{
    program->instructions = NULL;
    program->symbol_table = table;
    program->instruction_count = 0;
    program->temp_counter = 0;
    program->label_counter = 0;
}

IROperand ir_literal(int value)
{
    IROperand operand;
    operand.type = OPERAND_LITERAL;
    operand.value.literal = value;
    operand.is_initialized = 1;
    return operand;
}

IROperand ir_boolean_literal(uint8_t value)
{
    IROperand operand;
    operand.type = OPERAND_BOOLEAN_LITERAL;
    operand.value.boolean_literal = value;
    operand.is_initialized = 1;
    return operand;
}

IROperand ir_string_literal(const char *value)
{
    IROperand operand;
    operand.type = OPERAND_STRING_LITERAL;
    operand.value.string_literal = strdup(value);
    operand.is_initialized = 1;
    return operand;
}

IROperand ir_variable(const char *name, int is_initialized, DataType data_type)
{
    IROperand operand;
    operand.type = OPERAND_VARIABLE;
    operand.data_type = data_type;
    operand.value.variable = strdup(name);
    operand.is_initialized = is_initialized;
    return operand;
}

IROperand ir_temp(IRProgram *program, DataType type)
{
    IROperand operand;
    operand.type = OPERAND_TEMP;
    operand.value.temp_number = program->temp_counter++;
    operand.is_initialized = 0;
    operand.data_type = type;
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

IROp unary_op_to_ir_op(UnaryOpType op)
{
    switch (op)
    {
    case OP_LOGICAL_NOT:
        return IR_LOGICAL_NOT;
    default:
        return IR_LOGICAL_NOT;
    }
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
    case OP_LOGICAL_AND:
        return IR_LOGICAL_AND;
    case OP_LOGICAL_OR:
        return IR_LOGICAL_OR;
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

    case NODE_BOOLEAN:
    {
        return ir_boolean_literal(node->data.boolean.value);
    }
    break;
    case NODE_STRING:
    {
        return ir_string_literal(node->data.string.value);
    }

    case NODE_VARIABLE:
    {
        SymbolEntry *entry = lookup_variable_all_scopes(program->symbol_table, node->data.variable.name);
        DataType type = TYPE_UNKNOWN;
        if (entry)
        {
            type = entry->data_type;
        }
        return ir_variable(node->data.variable.name, 0, type);
    }

    case NODE_BINARY_OP:
    {
        printf("[INFO] NODE_BINARY_OP called \n");

        IROperand left = generate_expression_ir(node->data.binary_op.left, program);
        IROperand right = generate_expression_ir(node->data.binary_op.right, program);

        IROperand result = ir_temp(program, left.data_type);

        IROp op = binary_op_to_ir_op(node->data.binary_op.op);
        ir_add_instruction(program, op, result, left, right);

        return result;
    }

    case NODE_UNARY_OP:
    {
        IROperand value = generate_expression_ir(node->data.unary_op.value, program);
        IROperand result = ir_temp(program, value.data_type);

        IROp op = unary_op_to_ir_op(node->data.unary_op.op);
        ir_add_instruction(program, op, value, result, ir_none());

        return result;
    }
    break;

    case NODE_FUNCTION_CALL:
    {
        // Zde bude hnodta z RAX
        IROperand result = generate_function_call_ir(node, program);

        IROperand *args = malloc(sizeof(IROperand) * node->data.function_call.argument_count);
        for (int i = 0; i < node->data.function_call.argument_count; i++)
        {
            args[i] = generate_expression_ir(node->data.function_call.arguments[i], program);
        }

        free(args);
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
        IROperand result = ir_temp(program, left.data_type);

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

void generate_function_declaration_ir(ASTNode *node, IRProgram *program)
{
    if (!node || node->type != NODE_FUNCTION_DECLARATION)
        return;

    // Entry point funkce
    ir_add_instruction(program, IR_LABEL, ir_literal(ir_new_label(program)), ir_none(), ir_none());

    char *func_name = strdup(node->data.function_declaration.name);
    int param_count = node->data.function_declaration.param_count;
    DataType return_type = node->data.function_declaration.return_type;
    ir_add_instruction(program, IR_PROLOGUE, ir_variable(func_name, 0, return_type), ir_literal(param_count), ir_none());

    // V RESULtu JE INDEX parametru!!! (důležite pro codegen)
    for (int i = 0; i < param_count; i++)
    {
        char *param_name = node->data.function_declaration.param_names[i];
        ir_add_instruction(program, IR_PARAM, ir_literal(i), ir_variable(param_name, 0, node->data.function_declaration.param_types[i]), ir_none());
    }

    if (node->data.function_declaration.body)
    {
        generate_statement_ir(node->data.function_declaration.body, program);
    }

    ir_add_instruction(program, IR_EPILOGUE, ir_variable(func_name, 0, return_type), ir_none(), ir_none());
    free(func_name);
}

IROperand generate_function_call_ir(ASTNode *node, IRProgram *program)
{
    if (!node || node->type != NODE_FUNCTION_CALL)
        return ir_none();

    // INDEX ARGUMENTU JE V ARG2 DULEZITY PRO CODEGEN!!!
    // LITERAL NEBO VAR NAME JE v resultu
    for (int i = 0; i < node->data.function_call.argument_count; i++)
    {
        IROperand arg_value = generate_expression_ir(node->data.function_call.arguments[i], program);
        ir_add_instruction(program, IR_ARG, arg_value, ir_none(), ir_literal(i));
    }

    // Výsledek funkce bude v tomhle tempu
    FunctionEntry *function = lookup_function(program->symbol_table, node->data.function_call.func_name);
    IROperand result = ir_temp(program, function->return_type);

    ir_add_instruction(program, IR_CALL, result,
                       ir_variable(node->data.function_call.func_name, 0, TYPE_UNKNOWN),
                       ir_literal(node->data.function_call.argument_count));

    return result;
}

void generate_return_ir(ASTNode *node, IRProgram *program)
{
    if (!node || node->type != NODE_RETURN)
        return;

    IROperand expr = generate_expression_ir(node->data.return_statement.expr, program);
    ir_add_instruction(program, IR_RETURN, ir_none(), expr, ir_none());
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
            IROperand init_value = generate_expression_ir(node->data.var_declaration.init_expr, program);
            IROperand var = ir_variable(node->data.var_declaration.var_name, 1, node->type_annotation);
            ir_add_instruction(program, IR_ASSIGN, var, init_value, ir_none());
        }

        break;
    }

    case NODE_FUNCTION_CALL:
        generate_function_call_ir(node, program);
        break;

    case NODE_RETURN:
        generate_return_ir(node, program);
        break;
    case NODE_ASSIGNMENT:
    {

        IROperand expr = generate_expression_ir(node->data.assignment.value, program);

        SymbolEntry *entry = lookup_variable_all_scopes(program->symbol_table, node->data.assignment.var_name);
        DataType type = TYPE_UNKNOWN;
        if (entry)
        {
            type = entry->data_type;
        }

        IROperand var = ir_variable(node->data.assignment.var_name, 1, type);

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
    {
        int start_label = ir_new_label(program);
        int end_label = ir_new_label(program);

        // TODO: Pozor deklarace vs assingment
        generate_statement_ir(node->data.for_loop.init_expression, program);
        // Label na začátek loopu
        ir_add_instruction(program, IR_LABEL, ir_literal(start_label), ir_none(), ir_none());

        // Když už neplatí popdmínka skoč dopiči
        IROperand condition = generate_condition_ir(node->data.for_loop.condition, program);
        ir_add_instruction(program, IR_JUMPFALSE, ir_literal(end_label), condition, ir_none());

        // Tělo loopu
        generate_statement_ir(node->data.for_loop.body, program);

        // TODO: Do gramatiky pak přidat += a ++
        generate_statement_ir(node->data.for_loop.update, program);

        ir_add_instruction(program, IR_JUMP, ir_literal(start_label), ir_none(), ir_none());

        // Label na vyskočení z loopu
        ir_add_instruction(program, IR_LABEL, ir_literal(end_label), ir_none(), ir_none());

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
    }

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
    // Skočíme za všechny funkční deklarace
    int entry_label = ir_new_label(program);
    ir_add_instruction(program, IR_JUMP, ir_literal(entry_label), ir_none(), ir_none());

    // Přesuneme veškeré funkce, co máme a dáme je na začátek
    for (int i = 0; i < node->data.statement_list.statement_count; i++)
    {
        ASTNode *stmt = node->data.statement_list.statements[i];
        if (stmt->type == NODE_FUNCTION_DECLARATION)
        {
            generate_function_declaration_ir(stmt, program);
        }
    }

    // Label pro start
    ir_add_instruction(program, IR_LABEL, ir_literal(entry_label), ir_none(), ir_none());

    // Vygenerujeme zbytek
    for (int i = 0; i < node->data.statement_list.statement_count; i++)
    {
        ASTNode *stmt = node->data.statement_list.statements[i];
        if (stmt->type != NODE_FUNCTION_DECLARATION)
        {
            generate_statement_ir(stmt, program);
        }
    }
}

char *get_operand_string(IROperand operand, char *buffer)
{
    // printf("VOLEEE: %d \n", operand.type);
    switch (operand.type)
    {

    case OPERAND_LITERAL:
        sprintf(buffer, "%d", operand.value.literal);
        break;
    case OPERAND_STRING_LITERAL:
        sprintf(buffer, "'%s'", strdup(operand.value.string_literal));
        break;
    case OPERAND_BOOLEAN_LITERAL:
        if (operand.value.boolean_literal)
        {
            sprintf(buffer, "true");
        }
        else
        {
            sprintf(buffer, "false");
        }
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
        case IR_PROLOGUE:
            fprintf(file, "function %s(%d):\n", // počet argumentů..
                    instr->result.value.variable,
                    instr->arg1.value.literal);
            break;

        case IR_CALL:
            fprintf(file, "%s = call %s, %d\n",
                    get_operand_string(instr->result, result_str),
                    get_operand_string(instr->arg1, arg1_str),
                    instr->arg2.value.literal);
            break;

        case IR_EPILOGUE:
            fprintf(file, "end function %s\n",
                    instr->result.value.variable);
            break;

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
        case IR_ARG:
            fprintf(file, "arg %s\n", get_operand_string(instr->result, arg1_str));
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