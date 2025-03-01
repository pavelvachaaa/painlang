#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static int label_counter = 0;

// Generování návěští
static char *generate_label()
{
    char *label = malloc(20); 
    sprintf(label, "L%d", label_counter++);
    return label;
}

static void generate_expression(FILE *fp, ASTNode *node);
static void generate_statements(FILE *fp, ASTNode *node);

static void generate_variable(FILE *fp, const char *var_name)
{
    fprintf(fp, "    ; Load variable %s\n", var_name);
    fprintf(fp, "    mov rax, [%s]\n", var_name);
}

static void generate_number(FILE *fp, int value)
{
    fprintf(fp, "    ; Load constant %d\n", value);
    fprintf(fp, "    mov rax, %d\n", value);
}

static void generate_binary_op(FILE *fp, ASTNode *node)
{
    generate_expression(fp, node->data.binary_op.right);
    fprintf(fp, "    push rax\n");

    generate_expression(fp, node->data.binary_op.left);

    fprintf(fp, "    pop rbx\n");

    switch (node->data.binary_op.op)
    {
    case OP_ADD:
        fprintf(fp, "    add rax, rbx\n");
        break;
    case OP_SUBTRACT:
        fprintf(fp, "    sub rax, rbx\n");
        break;
    case OP_MULTIPLY:
        fprintf(fp, "    imul rax, rbx\n");
        break;
    case OP_DIVIDE:
        // Tady to jsem ukradl z nějakoho zapovězeného fóra nevím co se děje kámo
        fprintf(fp, "    push rdx\n");
        fprintf(fp, "    cdq\n");
        fprintf(fp, "    idiv rbx\n");
        fprintf(fp, "    pop rdx\n");
        break;
    }
}

static void generate_expression(FILE *fp, ASTNode *node)
{
    switch (node->type)
    {
    case NODE_NUMBER:
        generate_number(fp, node->data.number.value);
        break;
    case NODE_VARIABLE:
        generate_variable(fp, node->data.variable.name);
        break;
    case NODE_BINARY_OP:
        generate_binary_op(fp, node);
        break;
    default:
        fprintf(stderr, "Error: Unexpected node type in expression\n");
        break;
    }
}

static void generate_condition(FILE *fp, ASTNode *node, const char *true_label, const char *false_label)
{
    generate_expression(fp, node->data.condition.left);
    fprintf(fp, "    push rax\n");
    generate_expression(fp, node->data.condition.right);
    fprintf(fp, "    mov rbx, rax\n");
    fprintf(fp, "    pop rax\n");
    fprintf(fp, "    cmp rax, rbx\n");

    switch (node->data.condition.op)
    {
    case COND_EQUALS:
        fprintf(fp, "    je %s\n", true_label);
        break;
    case COND_NOT_EQUALS:
        fprintf(fp, "    jne %s\n", true_label);
        break;
    case COND_GREATER_THAN:
        fprintf(fp, "    jg %s\n", true_label);
        break;
    case COND_LESS_THAN:
        fprintf(fp, "    jl %s\n", true_label);
        break;
    case COND_GREATER_OR_EQUALS:
        fprintf(fp, "    jge %s\n", true_label);
        break;
    case COND_LESS_OR_EQUALS:
        fprintf(fp, "    jle %s\n", true_label);
        break;
    }

    fprintf(fp, "    jmp %s\n", false_label);
}

static void generate_if_statement(FILE *fp, ASTNode *node)
{
    char *true_label = generate_label();
    char *false_label = generate_label();
    char *end_label = generate_label();

    generate_condition(fp, node->data.if_statement.condition, true_label, false_label);

    // True block
    fprintf(fp, "%s:\n", true_label);
    generate_statements(fp, node->data.if_statement.if_block);
    fprintf(fp, "    jmp %s\n", end_label);

    // False block 
    fprintf(fp, "%s:\n", false_label);
    if (node->data.if_statement.else_block)
    {
        generate_statements(fp, node->data.if_statement.else_block);
    }

    // End of if statement
    fprintf(fp, "%s:\n", end_label);

    free(true_label);
    free(false_label);
    free(end_label);
}

static void generate_print(FILE *fp, ASTNode *node)
{
    generate_expression(fp, node->data.print.expr);

    fprintf(fp, "    ; Print value in rax\n");
    fprintf(fp, "    mov rsi, rax\n");
    fprintf(fp, "    mov rdi, format_int\n");

    // wrt ..plt -> with reference to 
    fprintf(fp, "    call printf wrt ..plt\n");
    fprintf(fp, "    add rsp, 8\n");
}

static void generate_var_declaration(FILE *fp, ASTNode *node)
{
    fprintf(fp, "    ; Declare variable %s\n", node->data.var_declaration.var_name);

    if (node->data.var_declaration.init_expr)
    {
        generate_expression(fp, node->data.var_declaration.init_expr);
        fprintf(fp, "    mov [%s], rax\n", node->data.var_declaration.var_name);
    }
    else
    {
        fprintf(fp, "    mov dword [%s], 0\n", node->data.var_declaration.var_name);
    }
}

static void generate_assignment(FILE *fp, ASTNode *node)
{
    fprintf(fp, "    ; Assign to %s\n", node->data.assignment.var_name);

    generate_expression(fp, node->data.assignment.value);

    fprintf(fp, "    mov [%s], rax\n", node->data.assignment.var_name);
}

static void generate_statements(FILE *fp, ASTNode *node)
{
    if (!node)
        return;

    if (node->type != NODE_STATEMENT_LIST)
    {
        fprintf(stderr, "Error: Expected statement list\n");
        return;
    }

    for (int i = 0; i < node->data.statement_list.statement_count; i++)
    {
        ASTNode *stmt = node->data.statement_list.statements[i];
        if (!stmt)
            continue;

        switch (stmt->type)
        {
        case NODE_PRINT:
            generate_print(fp, stmt);
            break;
        case NODE_VAR_DECLARATION:
            generate_var_declaration(fp, stmt);
            break;
        case NODE_ASSIGNMENT:
            generate_assignment(fp, stmt);
            break;
        case NODE_IF:
            generate_if_statement(fp, stmt);
            break;
        case NODE_STATEMENT_LIST:
            generate_statements(fp, stmt);
            break;
        default:
            fprintf(stderr, "Warning: Unhandled statement type\n");
            break;
        }
    }
}

void generate_nasm_code(ASTNode *root, const char *output_file)
{
    FILE *fp = fopen(output_file, "w");
    if (!fp)
    {
        perror("Error opening output file");
        return;
    }

    fprintf(fp, "; Generated NASM code\n");
    fprintf(fp, "section .data\n");
    fprintf(fp, "    format_int db \"%%d\", 10, 0  ; Format for printf\n");

    fprintf(fp, "section .bss\n");
    fprintf(fp, "    ; Variables are declared here\n");
    // Protraverzujeme strom a najdeme všechny proměnné 
    if (root->type == NODE_PROGRAM || root->type == NODE_STATEMENT_LIST)
    {
        for (int i = 0; i < root->data.statement_list.statement_count; i++)
        {
            ASTNode *stmt = root->data.statement_list.statements[i];
            if (stmt->type == NODE_VAR_DECLARATION)
            {
                fprintf(fp, "    %s resq 1\n", stmt->data.var_declaration.var_name); // For 8-byte variables (pointers, 64-bit integers)

            }
        }
    }



    fprintf(fp, "section .text\n");
    fprintf(fp, "    global main\n");
    fprintf(fp, "    extern printf\n\n");

    fprintf(fp, "main:\n");
    fprintf(fp, "    push rbp\n");
    fprintf(fp, "    mov rbp, rsp\n\n");

    if (root)
    {
        generate_statements(fp, root);
    }

    fprintf(fp, "\n    ; Return from main\n");
    fprintf(fp, "    mov rax, 0\n");
    fprintf(fp, "    mov rsp, rbp\n");
    fprintf(fp, "    pop rbp\n");
    fprintf(fp, "    ret\n");

    fclose(fp);
    printf("Generated NASM code in %s\n", output_file);
}