#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "ir.h"
#include "instruction_printer.h"

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

void generate_function_start(FILE *file, IRInstruction *instr)
{
    char func_name[64];
    sprintf(func_name, "%s", instr->result.value.variable);
    int param_count = instr->arg1.value.literal;

    fprintf(file, "%s:\n", func_name);
    fprintf(file, "    push rbp\n");
    fprintf(file, "    mov rbp, rsp\n");

    fprintf(file, "    sub rsp, 64\n"); // Alokuj 64 bajtů
}

void generate_function_end(FILE *file, IRInstruction *instr)
{
    fprintf(file, "    ; Function epilogue\n");
    fprintf(file, "    mov rsp, rbp\n");
    fprintf(file, "    pop rbp\n");
    fprintf(file, "    ret\n");
}

void generate_param(FILE *file, IRInstruction *instr)
{
    // Get parameter index from result.value.literal
    int param_index = instr->result.value.literal;
    const char *reg_names[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};

    if (instr->arg1.type == OPERAND_VARIABLE)
    {
        char *param_name = instr->arg1.value.variable;

        if (param_index < 6)
        {
            // Registr do lokální
            fprintf(file, " ; Parametr %s v registru %s\n", param_name, reg_names[param_index]);
            fprintf(file, " mov [%s], %s\n", param_name, reg_names[param_index]);
        }
        else
        {
            // STACK neotestováno pořádně!!!
            int stack_offset = (param_index - 6) * 8 + 16;
            fprintf(file, " ; Parametr %s ze stacku [rbp+%d]\n", param_name, stack_offset);
            fprintf(file, " mov rax, [rbp+%d]\n", stack_offset);
            fprintf(file, " mov [%s], rax\n", param_name);
        }
    }
    else if (instr->arg1.type == OPERAND_LITERAL)
    {
        int literal_value = instr->arg1.value.literal;

        if (param_index < 6)
        {
            fprintf(file, " ; Hodnota %d z registru %s\n", literal_value, reg_names[param_index]);
            fprintf(file, " mov %s, %d\n", reg_names[param_index], literal_value);
        }
        else
        {
            int stack_offset = (param_index - 6) * 8 + 16;
            fprintf(file, " ; Hodnota %d pushnutá na stack\n", literal_value);
            fprintf(file, " mov rax, %d\n", literal_value);
            fprintf(file, " mov [rbp+%d], rax\n", stack_offset);
        }
    }
    else
    {
        printf("Type: %d\n", instr->arg1.type);
        print_ir_instruction(*instr);
    }
}

void generate_arg(FILE *file, IRInstruction *instr)
{
    int arg_index = instr->arg2.value.literal;

    print_ir_instruction(*instr);


    if (instr->arg1.type != OPERAND_NONE)
    {
        generate_load_operand(file, instr->arg1);
    }
    else if (instr->result.type != OPERAND_NONE)
    {
        generate_load_operand(file, instr->result);
    }
    else
    {
        fprintf(file, " ; ERROR: Neplatný operand \n");
        return;
    }

    const char *reg_names[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    if (arg_index < 6)
    {
        fprintf(file, "     ; Argument %d v registru %s\n", arg_index, reg_names[arg_index]);
        fprintf(file, "     mov %s, rax\n", reg_names[arg_index]);
    }
    else
    {
      // Všechno po 6 argumentu je zásobník už..
        fprintf(file, "     ; Argument %d pushnutý na stack\n", arg_index);
        fprintf(file, "     push rax\n");
    }
}

void generate_call(FILE *file, IRInstruction *instr)
{
    char *func_name = instr->arg1.value.variable;
    int arg_count = instr->arg2.value.literal;

    fprintf(file, "    ; Align stack 16 bytes \n");
    // Kolik vís bude na stacku??
    int stack_args = arg_count > 6 ? arg_count - 6 : 0;
    // 16 byte alingment na sudý/lichý počty argumentů
    if (stack_args % 2 == 1)
    {
        fprintf(file, "    sub rsp, 8\n");
    }

    fprintf(file, "    ; Call function %s\n", func_name);
    fprintf(file, "    call %s\n", func_name);

    // Musíme vyčistit staack, když se tam pushovalo
    if (stack_args > 0)
    {
        fprintf(file, "    ; Mažu %d argumentů ze stacku\n", stack_args);
        fprintf(file, "    add rsp, %d\n", stack_args * 8 + (stack_args % 2 == 1 ? 8 : 0));
    }

    char result_str[64];
    get_nasm_operand(instr->result, result_str, 1);
    fprintf(file, "    ; Ulož hodnotu z rax\n");
    fprintf(file, "    mov %s, rax\n", result_str);
}

static void generate_return(FILE *file, IRInstruction *instr)
{
    // V raxu by měla potom být hodnota returnnu
    if (instr->arg1.type != OPERAND_NONE)
    {
        generate_load_operand(file, instr->arg1);
    }
    else
    {
        fprintf(file, "    ; Void return (rax = 0)\n");
        fprintf(file, "    xor rax, rax\n");
    }

    fprintf(file, "    ; Return from function\n");
    fprintf(file, "    mov rsp, rbp\n");
    fprintf(file, "    pop rbp\n");
    fprintf(file, "    ret\n");
}

void generate_nasm_from_ir(IRProgram *program, SymbolTable *table, const char *output_file)
{

    FILE *file = fopen(output_file, "w");
    if (!file)
    {
        perror("hell nawh");
        return;
    }

    VariableList variables;
    init_variable_list(&variables);

    // Funkce, která se zpracovává (Pak hodit do IRProgramu)
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
        // Nechceme proměnné labely pro funkce (pak se to cyklí jak debil)
        FunctionEntry *entry = lookup_function(table, variables.variables[i]);
        if (entry)
        {
            continue;
        }

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
            strcpy(current_function, instr->result.value.variable);
            break;
        case IR_EPILOGUE:
            fprintf(file, "    ; IR: end function %s\n", result_str);
            strcpy(current_function, "");
            break;
        case IR_PARAM:
            fprintf(file, "    ; IR: param %s\n", arg1_str);
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

        case IR_PARAM:
            generate_param(file, instr);
            break;

        case IR_ARG:
            generate_arg(file, instr);
            break;

        case IR_PROLOGUE:
            generate_function_start(file, instr);
            break;

        case IR_EPILOGUE:
            generate_function_end(file, instr);
            break;

        case IR_CALL:
            generate_call(file, instr);
            break;

        case IR_RETURN:
            generate_return(file, instr);
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

    fprintf(file, "    ; Ukončit program \n");
    fprintf(file, "    mov rax, 0\n");
    fprintf(file, "    mov rsp, rbp\n");
    fprintf(file, "    pop rbp\n");
    fprintf(file, "    ret\n");

    fclose(file);
    free_variable_list(&variables);

    printf("Output: %s\n", output_file);
}