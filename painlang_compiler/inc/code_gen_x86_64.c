#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "ir.h"

typedef struct
{
    char **variables;
    int count;
} VariableList;

typedef struct
{
    char *name;
    int param_count;
    int label;
} FunctionInfo;

typedef struct
{
    FunctionInfo *functions;
    int count;
} FunctionInfoList;

void init_function_info_list(FunctionInfoList *list)
{
    list->functions = NULL;
    list->count = 0;
}

void add_function_info(FunctionInfoList *list, const char *name, int param_count, int label)
{
    list->count++;
    list->functions = realloc(list->functions, list->count * sizeof(FunctionInfo));
    list->functions[list->count - 1].name = strdup(name);
    list->functions[list->count - 1].param_count = param_count;
    list->functions[list->count - 1].label = label;
}

FunctionInfo *get_function_info(FunctionInfoList *list, const char *name)
{
    for (int i = 0; i < list->count; i++)
    {
        if (strcmp(list->functions[i].name, name) == 0)
        {
            return &list->functions[i];
        }
    }
    return NULL;
}

void init_variable_list(VariableList *list)
{
    list->variables = NULL;
    list->count = 0;
}

int is_variable_in_list(VariableList *list, const char *var_name)
{
    for (int i = 0; i < list->count; i++)
    {
        if (strcmp(list->variables[i], var_name) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void add_variable_to_list(VariableList *list, const char *var_name)
{
    if (is_variable_in_list(list, var_name))
    {
        return;
    }

    list->count++;
    list->variables = realloc(list->variables, list->count * sizeof(char *));
    list->variables[list->count - 1] = strdup(var_name);
}

void free_variable_list(VariableList *list)
{
    for (int i = 0; i < list->count; i++)
    {
        free(list->variables[i]);
    }
    free(list->variables);
    list->variables = NULL;
    list->count = 0;
}

void free_function_info_list(FunctionInfoList *list)
{
    for (int i = 0; i < list->count; i++)
    {
        free(list->functions[i].name);
    }
    free(list->functions);
    list->functions = NULL;
    list->count = 0;
}

/// @brief  Pro komentáře ve finalní assembly
/// @param operand
/// @param buffer
static void get_operand_as_string(IROperand operand, char *buffer)
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
}

static void get_nasm_operand(IROperand operand, char *buffer, int is_dest)
{
    switch (operand.type)
    {
    case OPERAND_LITERAL:
        sprintf(buffer, "%d", operand.value.literal);
        break;
    case OPERAND_VARIABLE:
        sprintf(buffer, "[%s]", operand.value.variable);
        break;
    case OPERAND_TEMP:
        sprintf(buffer, "[t%d]", operand.value.temp_number);
        break;
    case OPERAND_LABEL:
        sprintf(buffer, "L%d", operand.value.label_number);
        break;
    case OPERAND_NONE:
        sprintf(buffer, "");
        break;
    }
}

static void generate_load_operand(FILE *file, IROperand operand)
{
    char operand_str[64];
    get_nasm_operand(operand, operand_str, 0);

    if (operand.type == OPERAND_LITERAL)
    {
        fprintf(file, "    ; Načti konstantu %s\n", operand_str);
        fprintf(file, "    mov rax, %s\n", operand_str);
    }
    else if (operand.type == OPERAND_VARIABLE || operand.type == OPERAND_TEMP)
    {
        fprintf(file, "    ; Načti proměnnou %s\n", operand_str);
        fprintf(file, "    mov rax, %s\n", operand_str);
    }
}

static void generate_store_operand(FILE *file, IROperand operand)
{
    char operand_str[64];
    get_nasm_operand(operand, operand_str, 1);

    if (operand.type == OPERAND_VARIABLE || operand.type == OPERAND_TEMP)
    {
        fprintf(file, "    ; Ulož do %s\n", operand_str);
        fprintf(file, "    mov %s, rax\n", operand_str);
    }
}

static void generate_assignment(FILE *file, IRInstruction *instr)
{
    generate_load_operand(file, instr->arg1);
    generate_store_operand(file, instr->result);
}

static void generate_function_prologue(FILE *file, IRInstruction *instr)
{
    char func_name[64];
    sprintf(func_name, "%s", instr->result.value.variable);
    int param_count = instr->arg1.value.literal;

    fprintf(file, "%s:\n", func_name);
    fprintf(file, "    ; Function prologue for %s with %d parameters\n", func_name, param_count);
    fprintf(file, "    push rbp\n");
    fprintf(file, "    mov rbp, rsp\n");

    // Reserve space for local variables (can be adjusted based on needs)
    fprintf(file, "    sub rsp, 64\n"); // Reserve 64 bytes for local vars

    // Save callee-saved registers
    fprintf(file, "    push rbx\n");
    fprintf(file, "    push r12\n");
    fprintf(file, "    push r13\n");
    fprintf(file, "    push r14\n");
    fprintf(file, "    push r15\n");

    // Handle parameters (in x86_64 calling convention, first 6 args in registers)
    // rdi, rsi, rdx, rcx, r8, r9, then stack
    for (int i = 0; i < param_count && i < 6; i++)
    {
        // Store register arguments to stack locations
        switch (i)
        {
        case 0:
            fprintf(file, "    mov [rbp-%d], rdi\n", (i + 1) * 8);
            break;
        case 1:
            fprintf(file, "    mov [rbp-%d], rsi\n", (i + 1) * 8);
            break;
        case 2:
            fprintf(file, "    mov [rbp-%d], rdx\n", (i + 1) * 8);
            break;
        case 3:
            fprintf(file, "    mov [rbp-%d], rcx\n", (i + 1) * 8);
            break;
        case 4:
            fprintf(file, "    mov [rbp-%d], r8\n", (i + 1) * 8);
            break;
        case 5:
            fprintf(file, "    mov [rbp-%d], r9\n", (i + 1) * 8);
            break;
        }
    }

    // Parameters beyond the 6th are on the stack and can be accessed relative to rbp
}

static void generate_function_epilogue(FILE *file, IRInstruction *instr)
{
    char func_name[64];
    sprintf(func_name, "%s", instr->result.value.variable);

    fprintf(file, "%s_epilogue:\n", func_name);
    fprintf(file, "    ; Function epilogue for %s\n", func_name);

    // Restore callee-saved registers in reverse order
    fprintf(file, "    pop r15\n");
    fprintf(file, "    pop r14\n");
    fprintf(file, "    pop r13\n");
    fprintf(file, "    pop r12\n");
    fprintf(file, "    pop rbx\n");

    // Function return - restore stack and return
    fprintf(file, "    mov rsp, rbp\n");
    fprintf(file, "    pop rbp\n");
    fprintf(file, "    ret\n");
}

static void generate_function_call(FILE *file, IRInstruction *instr)
{
    char result_str[64];
    get_nasm_operand(instr->result, result_str, 1);

    char func_name[64];
    sprintf(func_name, "%s", instr->arg1.value.variable);

    int param_count = instr->arg2.value.literal;

    fprintf(file, "    ; Calling function %s with %d parameters\n", func_name, param_count);

    // In this simplified model, we assume parameters were pushed using IR_PARAM instructions
    // before this call instruction, so we don't need to handle them here

    // The x86_64 calling convention uses registers for the first 6 arguments
    // We'll make the actual call
    fprintf(file, "    call %s\n", func_name);

    // After return, the result is in rax, move it to the result variable
    fprintf(file, "    mov %s, rax\n", result_str);
}

static void generate_parameter(FILE *file, IRInstruction *instr)
{
    char arg_str[64];
    get_nasm_operand(instr->arg1, arg_str, 0);

    // We're building a list of parameters in reverse order in ir.c
    // so we push them here in the right order

    // Using static counter to track which parameter this is
    static int param_index = 0;

    fprintf(file, "    ; Loading parameter %d\n", param_index);

    // Load the parameter value
    if (instr->arg1.type == OPERAND_LITERAL)
    {
        fprintf(file, "    mov rax, %s\n", arg_str);
    }
    else
    {
        fprintf(file, "    mov rax, %s\n", arg_str);
    }

    // Place in appropriate register according to x86_64 calling convention
    switch (param_index)
    {
    case 0:
        fprintf(file, "    mov rdi, rax\n");
        break;
    case 1:
        fprintf(file, "    mov rsi, rax\n");
        break;
    case 2:
        fprintf(file, "    mov rdx, rax\n");
        break;
    case 3:
        fprintf(file, "    mov rcx, rax\n");
        break;
    case 4:
        fprintf(file, "    mov r8, rax\n");
        break;
    case 5:
        fprintf(file, "    mov r9, rax\n");
        break;
    default:
        // Parameters beyond the 6th go on the stack
        fprintf(file, "    push rax\n");
    }

    param_index++;

    // Reset param_index after a call instruction
    // This needs to be coordinated with the IR_CALL handler
}

static void generate_return(FILE *file, IRInstruction *instr)
{
    char arg1_str[64];
    get_nasm_operand(instr->arg1, arg1_str, 0);

    fprintf(file, "    ; Return statement\n");

    // Load return value into rax
    if (instr->arg1.type == OPERAND_LITERAL)
    {
        fprintf(file, "    mov rax, %s\n", arg1_str);
    }
    else
    {
        fprintf(file, "    mov rax, %s\n", arg1_str);
    }

    // Jump to function epilogue
    // We need to determine the current function name
    // This requires tracking the current function context
    fprintf(file, "    jmp current_function_epilogue\n");
}

static void generate_add(FILE *file, IRInstruction *instr)
{
    generate_load_operand(file, instr->arg1);

    char arg2_str[64];
    get_nasm_operand(instr->arg2, arg2_str, 0);

    if (instr->arg2.type == OPERAND_LITERAL)
    {
        fprintf(file, "    ; Sečti konstantu %s\n", arg2_str);
        fprintf(file, "    add rax, %s\n", arg2_str);
    }
    else
    {
        fprintf(file, "    ; Sečti proměnnou %s\n", arg2_str);
        fprintf(file, "    add rax, %s\n", arg2_str);
    }

    generate_store_operand(file, instr->result);
}

static void generate_subtract(FILE *file, IRInstruction *instr)
{
    generate_load_operand(file, instr->arg1);

    char arg2_str[64];
    get_nasm_operand(instr->arg2, arg2_str, 0);

    if (instr->arg2.type == OPERAND_LITERAL)
    {
        fprintf(file, "    ; Odečti konstantu %s\n", arg2_str);
        fprintf(file, "    sub rax, %s\n", arg2_str);
    }
    else
    {
        fprintf(file, "    ; Odečti proměnnou %s\n", arg2_str);
        fprintf(file, "    sub rax, %s\n", arg2_str);
    }

    generate_store_operand(file, instr->result);
}

static void generate_multiply(FILE *file, IRInstruction *instr)
{
    generate_load_operand(file, instr->arg1);

    char arg2_str[64];
    get_nasm_operand(instr->arg2, arg2_str, 0);

    if (instr->arg2.type == OPERAND_LITERAL)
    {
        fprintf(file, "    ; Vynásob konstantu %s\n", arg2_str);
        fprintf(file, "    mov rbx, %s\n", arg2_str);
        fprintf(file, "    imul rax, rbx\n");
    }
    else
    {
        fprintf(file, "    ; Vynásob konstantu %s\n", arg2_str);
        fprintf(file, "    imul rax, %s\n", arg2_str);
    }

    generate_store_operand(file, instr->result);
}

static void generate_divide(FILE *file, IRInstruction *instr)
{
    generate_load_operand(file, instr->arg1);

    char arg2_str[64];
    get_nasm_operand(instr->arg2, arg2_str, 0);

    fprintf(file, "    ; Vynuluj \n");
    fprintf(file, "    xor rdx, rdx\n");

    if (instr->arg2.type == OPERAND_LITERAL)
    {
        fprintf(file, "    ; Vyděl konstantou %s\n", arg2_str);
        fprintf(file, "    mov rbx, %s\n", arg2_str);
        fprintf(file, "    idiv rbx\n");
    }
    else
    {
        fprintf(file, "    ; Vyděl proměnnou %s\n", arg2_str);
        fprintf(file, "    mov rbx, %s\n", arg2_str);
        fprintf(file, "    idiv rbx\n");
    }

    // Store result
    generate_store_operand(file, instr->result);
}

static void generate_comparison(FILE *file, IRInstruction *instr, const char *comparison_op)
{
    generate_load_operand(file, instr->arg1);

    char arg2_str[64];
    get_nasm_operand(instr->arg2, arg2_str, 0);

    fprintf(file, "    ; Porovnej\n");
    fprintf(file, "    mov rbx, %s\n", arg2_str);
    fprintf(file, "    cmp rax, rbx\n");
    fprintf(file, "    %s al\n", comparison_op);
    fprintf(file, "    movzx rax, al\n");

    generate_store_operand(file, instr->result);
}

static void generate_greater_than(FILE *file, IRInstruction *instr)
{
    generate_comparison(file, instr, "setg");
}

static void generate_less_than(FILE *file, IRInstruction *instr)
{
    generate_comparison(file, instr, "setl");
}

static void generate_equals(FILE *file, IRInstruction *instr)
{
    generate_comparison(file, instr, "sete");
}

static void generate_not_equals(FILE *file, IRInstruction *instr)
{
    generate_comparison(file, instr, "setne");
}

static void generate_greater_eq(FILE *file, IRInstruction *instr)
{
    generate_comparison(file, instr, "setge");
}

static void generate_less_eq(FILE *file, IRInstruction *instr)
{
    generate_comparison(file, instr, "setle");
}

static void generate_jump_false(FILE *file, IRInstruction *instr)
{
    char arg1_str[64];
    get_nasm_operand(instr->arg1, arg1_str, 0);

    char label_str[64];
    sprintf(label_str, "L%d", instr->result.value.label_number);

    fprintf(file, "    ; Skoč když false\n");
    fprintf(file, "    mov rax, %s\n", arg1_str);
    fprintf(file, "    cmp rax, 0\n");
    fprintf(file, "    je %s\n", label_str);
}

static void generate_jump(FILE *file, IRInstruction *instr)
{
    char label_str[64];
    sprintf(label_str, "L%d", instr->result.value.label_number);

    fprintf(file, "    ; Skoč \n");
    fprintf(file, "    jmp %s\n", label_str);
}

static void generate_print(FILE *file, IRInstruction *instr)
{
    char arg1_str[64];
    get_nasm_operand(instr->arg1, arg1_str, 0);

    fprintf(file, "    ; Vypiš hodnotu \n");
    fprintf(file, "    mov rsi, %s\n", arg1_str);
    fprintf(file, "    mov rdi, format_int\n");
    fprintf(file, "    xor rax, rax\n"); // Clear rax for printf
    fprintf(file, "    call printf wrt ..plt\n");
}

void generate_nasm_from_ir(IRProgram *program, const char *output_file)
{
    FILE *file = fopen(output_file, "w");
    if (!file)
    {
        perror("hell nawh");
        return;
    }

    VariableList variables;
    init_variable_list(&variables);

    // Track function context
    char current_function[64] = "";

    // Vytvoření seznamu proměnných
    for (int i = 0; i < program->instruction_count; i++)
    {
        IRInstruction *instr = &program->instructions[i];

        // Konstanty
        if (instr->result.type == OPERAND_VARIABLE)
        {
            add_variable_to_list(&variables, instr->result.value.variable);
        }
        if (instr->arg1.type == OPERAND_VARIABLE)
        {
            add_variable_to_list(&variables, instr->arg1.value.variable);
        }
        if (instr->arg2.type == OPERAND_VARIABLE)
        {
            add_variable_to_list(&variables, instr->arg2.value.variable);
        }

        // Pomocné proměnné
        if (instr->result.type == OPERAND_TEMP)
        {
            char temp_name[32];
            sprintf(temp_name, "t%d", instr->result.value.temp_number);
            add_variable_to_list(&variables, temp_name);
        }
        if (instr->arg1.type == OPERAND_TEMP)
        {
            char temp_name[32];
            sprintf(temp_name, "t%d", instr->arg1.value.temp_number);
            add_variable_to_list(&variables, temp_name);
        }
        if (instr->arg2.type == OPERAND_TEMP)
        {
            char temp_name[32];
            sprintf(temp_name, "t%d", instr->arg2.value.temp_number);
            add_variable_to_list(&variables, temp_name);
        }
    }

    fprintf(file, "; Profesionální NASM z IR vygenerováno PainGenem  \n");
    fprintf(file, "section .data\n");
    fprintf(file, "    format_int db \"%%d\", 10, 0  ; Formát pro print \n\n");

    // Konstnatní
    fprintf(file, "section .bss\n");
    for (int i = 0; i < variables.count; i++)
    {
        fprintf(file, "    %s resq 1\n", variables.variables[i]);
    }

    // Pomocný
    for (int i = 0; i < program->temp_counter; i++)
    {
        char temp_name[32];
        sprintf(temp_name, "t%d", i);
        if (!is_variable_in_list(&variables, temp_name))
        {
            fprintf(file, "    %s resq 1\n", temp_name);
        }
    }

    fprintf(file, "\nsection .text\n");
    fprintf(file, "    global main\n");
    fprintf(file, "    extern printf\n\n");

    // We'll check if we need to generate a main function or if one is defined in the program
    int has_main = 0;
    for (int i = 0; i < program->instruction_count; i++)
    {
        IRInstruction *instr = &program->instructions[i];
        if (instr->op == IR_PROLOGUE && strcmp(instr->result.value.variable, "main") == 0)
        {
            has_main = 1;
            break;
        }
    }

    // If no main function is defined, create a default entry point
    if (!has_main)
    {
        fprintf(file, "main:\n");
        fprintf(file, "    push rbp\n");
        fprintf(file, "    mov rbp, rsp\n\n");
    }

    // Vezmi každou instrukci z lineární IR a generuj instrukce
    for (int i = 0; i < program->instruction_count; i++)
    {
        IRInstruction *instr = &program->instructions[i];

        // Jelikož jsem trochu debil vypíšu si to do komentářu
        char result_str[64], arg1_str[64], arg2_str[64];
        get_operand_as_string(instr->result, result_str);
        get_operand_as_string(instr->arg1, arg1_str);
        get_operand_as_string(instr->arg2, arg2_str);

        switch (instr->op)
        {
        case IR_PROLOGUE:
            fprintf(file, "    ; IR: function %s(%s)\n", result_str, arg1_str);
            // Track current function
            strcpy(current_function, instr->result.value.variable);
            break;
        case IR_EPILOGUE:
            fprintf(file, "    ; IR: end function %s\n", result_str);
            strcpy(current_function, "");
            break;
        case IR_CALL:
            fprintf(file, "    ; IR: %s = call %s, %s\n", result_str, arg1_str, arg2_str);
            break;
        case IR_PARAM:
            fprintf(file, "    ; IR: param %s\n", arg1_str);
            break;
        case IR_RETURN:
            fprintf(file, "    ; IR: return %s\n", arg1_str);
            break;
        case IR_ASSIGN:
            fprintf(file, "    ; IR: %s = %s\n", result_str, arg1_str);
            break;
        case IR_ADD:
            fprintf(file, "    ; IR: %s = %s + %s\n", result_str, arg1_str, arg2_str);
            break;
        case IR_SUBTRACT:
            fprintf(file, "    ; IR: %s = %s - %s\n", result_str, arg1_str, arg2_str);
            break;
        case IR_MULTIPLY:
            fprintf(file, "    ; IR: %s = %s * %s\n", result_str, arg1_str, arg2_str);
            break;
        case IR_DIVIDE:
            fprintf(file, "    ; IR: %s = %s / %s\n", result_str, arg1_str, arg2_str);
            break;
        case IR_GREATER_THAN:
            fprintf(file, "    ; IR: %s = %s > %s\n", result_str, arg1_str, arg2_str);
            break;
        case IR_LESS_THAN:
            fprintf(file, "    ; IR: %s = %s < %s\n", result_str, arg1_str, arg2_str);
            break;
        case IR_EQUALS:
            fprintf(file, "    ; IR: %s = %s == %s\n", result_str, arg1_str, arg2_str);
            break;
        case IR_NOT_EQUALS:
            fprintf(file, "    ; IR: %s = %s != %s\n", result_str, arg1_str, arg2_str);
            break;
        case IR_LESS_EQ:
            fprintf(file, "    ; IR: %s = %s <= %s\n", result_str, arg1_str, arg2_str);
            break;
        case IR_GREATER_EQ:
            fprintf(file, "    ; IR: %s = %s >= %s\n", result_str, arg1_str, arg2_str);
            break;
        case IR_LABEL:
            fprintf(file, "    ; IR: L%d:\n", instr->result.value.literal);
            break;
        case IR_JUMPFALSE:
            fprintf(file, "    ; IR: if %s == 0 goto L%d\n", arg1_str, instr->result.value.label_number);
            break;
        case IR_JUMP:
            fprintf(file, "    ; IR: goto L%d\n", instr->result.value.label_number);
            break;
        case IR_PRINT:
            fprintf(file, "    ; IR: print %s\n", arg1_str);
            break;
        default:
            fprintf(file, "    ; IR: Neznám tě %d\n", instr->op);
            break;
        }

        switch (instr->op)
        {
        case IR_PROLOGUE:
            generate_function_prologue(file, instr);
            break;

        case IR_EPILOGUE:
            generate_function_epilogue(file, instr);
            break;

        case IR_CALL:
            generate_function_call(file, instr);
            break;

        case IR_PARAM:
            generate_parameter(file, instr);
            break;

        case IR_RETURN:
            // Update the return instruction with current function name
            fprintf(file, "    ; Return from function %s\n", current_function);
            fprintf(file, "    mov rax, %s\n", arg1_str);
            fprintf(file, "    jmp %s_epilogue\n", current_function);
            break;

        case IR_LABEL:
            fprintf(file, "L%d:\n", instr->result.value.literal);
            break;

        case IR_ASSIGN:
            generate_assignment(file, instr);
            break;

        case IR_ADD:
            generate_add(file, instr);
            break;

        case IR_SUBTRACT:
            generate_subtract(file, instr);
            break;

        case IR_MULTIPLY:
            generate_multiply(file, instr);
            break;

        case IR_DIVIDE:
            generate_divide(file, instr);
            break;

        case IR_GREATER_THAN:
            generate_greater_than(file, instr);
            break;

        case IR_LESS_THAN:
            generate_less_than(file, instr);
            break;

        case IR_EQUALS:
            generate_equals(file, instr);
            break;

        case IR_NOT_EQUALS:
            generate_not_equals(file, instr);
            break;

        case IR_GREATER_EQ:
            generate_greater_eq(file, instr);
            break;

        case IR_LESS_EQ:
            generate_less_eq(file, instr);
            break;

        case IR_JUMPFALSE:
            generate_jump_false(file, instr);
            break;

        case IR_JUMP:
            generate_jump(file, instr);
            break;

        case IR_PRINT:
            generate_print(file, instr);
            break;

        default:
            fprintf(file, "    ; Neznám tě o: %d\n", instr->op);
            break;
        }

        fprintf(file, "\n");
    }

    // If we created a default main, close it
    if (!has_main)
    {
        fprintf(file, "    ; Ukončit program \n");
        fprintf(file, "    mov rax, 0\n");
        fprintf(file, "    mov rsp, rbp\n");
        fprintf(file, "    pop rbp\n");
        fprintf(file, "    ret\n");
    }

    fclose(file);
    free_variable_list(&variables);

    printf("Output: %s\n", output_file);
}