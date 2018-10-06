/**
 * Entry point for parer for C Programming Language
 * (ISO/IEC 9899:2018).
 *
 * @authors: Denis Chernikov, Vladislav Kuleykin
 */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "y.tab.h"
#include "typedef_name.h"

extern FILE *yyin;  // Flex input

/// Program entry point.
int main(int argc, char *argv[])
{
    yydebug = 1;  // Set 0 for no debug info. TODO remove in production

    if (argc < 2)
    {
        printf("Usage: %s <out_file> OR %s <in_file> <out_file>",
                argv[0], argv[0]);
        return 1;
    }

    char *in_name = argc > 2 ? argv[1] : NULL;
    char *out_name = argc > 2 ? argv[2] : argv[1];

    yyin = in_name != NULL ? fopen(in_name, "r") : stdin;
    if (!yyin)
    {
        fprintf(stderr, "Cannot open for reading: %s\n", in_name);
        return 2;
    }

    int yyres = yyparse();
    if (argc > 2) fclose(yyin);
    free_typedef_name();
    astnode *astroot = 0;  // TODO get AST root
    if (yyres || !astroot)
    {
        fprintf(stderr, "Parsing failed! No output will be provided.\n");
        return 3;
    }

    char *json = ast_to_json(astroot);
    ast_free(astroot);
    if (!json)
    {
        fprintf(stderr, "JSON generation failure!\n");
        return 4;
    }

    FILE *out = fopen(argv[2], "w");
    if (!out)
    {
        fprintf(stderr, "Cannot open for writing: %s\n", out_name);
        free(json);
        return 5;
    }

    fputs(json, out);
    fclose(out);
    free(json);

    return 0;
}
