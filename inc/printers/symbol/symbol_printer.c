#include "symbol_table.h";

void print_symbol_table(SymbolTable *table)
{
    if (table == NULL)
    {
        fprintf(stderr,"Error: Symbol table is NULL\n");
        return;
    }

    printf("\n===== SYMBOL TABLE =====\n");
    printf("Current scope level: %d\n", table->current_scope);
    printf("Total variables: %d\n", table->count);
    printf("Total functions: %d\n", table->countF);

    if (table->count > 0)
    {
        printf("\n--- VARIABLES ---\n");
        printf("%-20s | %-10s | %-10s | %-8s | %-8s | %-8s | %-15s | %-7s\n",
               "Name", "Type", "Data Type", "Value", "Init", "Used", "Modified Loop", "Scope");
        printf("--------------------|-----------|-----------|---------|---------|---------|-----------------|---------\n");

        for (int i = 0; i < table->count; i++)
        {
            SymbolEntry *entry = &table->entries[i];

            char *symbol_type;
            switch (entry->type)
            {
            case SYMBOL_VAR:
                symbol_type = "VAR";
                break;
            case SYMBOL_PARAM:
                symbol_type = "PARAM";
                break;
            case SYMBOL_ARG:
                symbol_type = "ARG";
                break;
            default:
                symbol_type = "UNKNOWN";
                break;
            }

            char *data_type;
            switch (entry->data_type)
            {
            case TYPE_NUMBER:
                data_type = "NUM";
                break;
            case TYPE_STRING:
                data_type = "STRING";
                break;
            case TYPE_BOOLEAN:
                data_type = "BOOL";
                break;
            case TYPE_UNKNOWN:
                data_type = "UNKOWN";
                break;
            case TYPE_VOID:
                data_type = "VOID";
                break;
            default:
                data_type = "UNKNOWN";
                break;
            }

            char value_str[50] = "N/A";
            if (entry->is_initialized)
            {
                switch (entry->data_type)
                {
                case TYPE_NUMBER:
                    sprintf(value_str, "%d", entry->value);
                    break;
                case TYPE_BOOLEAN:
                    sprintf(value_str, "%s", entry->boolean_value ? "true" : "false");
                    break;
                case TYPE_STRING:
                    if (entry->string_value)
                    {
                        snprintf(value_str, 50, "\"%s\"", entry->string_value);
                        if (strlen(entry->string_value) > 10)
                        {
                            strcpy(&value_str[12], "...");
                        }
                    }
                    else
                    {
                        strcpy(value_str, "NULL");
                    }
                    break;
                default:
                    break;
                }
            }

            printf("%-20s | %-10s | %-10s | %-8s | %-8s | %-8s | %-15s | %-7d\n",
                   entry->name,
                   symbol_type,
                   data_type,
                   value_str,
                   entry->is_initialized ? "Yes" : "No",
                   entry->is_used ? "Yes" : "No",
                   entry->is_modified_in_loop ? "Yes" : "No",
                   entry->scope_level);
        }
    }

    if (table->countF > 0)
    {
        printf("\n--- FUNCTIONS ---\n");
        printf("%-20s | %-15s | %-15s\n", "Name", "Return Type", "Param Count");
        printf("--------------------|-----------------|----------------\n");

        for (int i = 0; i < table->countF; i++)
        {
            FunctionEntry *func = &table->functions[i];

            char *return_type;
            switch (func->return_type)
            {
            case TYPE_NUMBER:
                return_type = "INT";
                break;
            case TYPE_STRING:
                return_type = "STRING";
                break;
            case TYPE_BOOLEAN:
                return_type = "BOOL";
                break;
            case TYPE_VOID:
                return_type = "VOID";
                break;
            default:
                return_type = "UNKNOWN";
                break;
            }

            printf("%-20s | %-15s | %-15d\n",
                   func->name,
                   return_type,
                   func->number_of_params);
        }
    }

    printf("\n======================\n");
}