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

    fprintf(file, "main:\n");
    fprintf(file, "    push rbp\n");
    fprintf(file, "    mov rbp, rsp\n\n");

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

    fprintf(file, "    ; Ukončit program \n");
    fprintf(file, "    mov rax, 0\n");
    fprintf(file, "    mov rsp, rbp\n");
    fprintf(file, "    pop rbp\n");
    fprintf(file, "    ret\n");

    fclose(file);
    free_variable_list(&variables);

    printf("Output: %s\n", output_file);
}