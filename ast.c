/**
 * Abstract Syntax Tree building functions for parser
 * of the C Programming Language (ISO/IEC 9899:2018).
 *
 * @authors: Denis Chernikov, Vladislav Kuleykin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

AST_NODE *ast_root = NULL;

// TODO node building functions

void ast_free(AST_NODE *root) {
    // TODO content free
//    for (int i = 0; i < root->children_number; ++i)
//    {
//        ast_free(root->children[i]);
//    }
//    free(root);
}

/// Convert enum AST_NODE_TYPE to string.
///
/// \param type Enum value to convert
/// \return Actual string representation of a value
char *ast_type_to_str(AST_NODE_TYPE type)
{
    switch (type)
    {
        default: return NULL;  // TODO
    }
}

/// Repeat given source `n' times.
///
/// \param n Number of repetitions
/// \param str String pattern to repeat
/// \return `str' repeated `n' times
char *mult(int n, char *str)
{
    if (n < 0)
    {
        return NULL;
    }
    if (n == 0)
    {
        return "";
    }
    if (n == 1)
    {
        return str;
    }
    size_t src_len = strlen(str);
    size_t res_len = src_len * n;
    char *res = (char *) malloc(sizeof(char) * res_len);
    int i;
    for (i = 0; i < res_len; ++i)
    {
        res[i] = str[i % src_len];
    }
    return res;
}

char *ast_to_json(AST_NODE *root, int shift, char *tab) {
    int i;
    char **children = (char **) malloc(sizeof(char *) * root->children_number);
    for (i = 0; i < root->children_number; ++i)
    {
        children[i] = ast_to_json(root->children[i], shift + 2, tab);
    }

    char *conc_children = "";  // TODO concatenation with ",\n"
    if (!conc_children)
    {
        fprintf(stderr,
            "FATAL ERROR! Memory for JSON concatenation cannot be allocated!\n");
        exit(-1);
    }
    for (i = 0; i < root->children_number; ++i)
    {
        free(children[i]);
    }
    free(children);

    char *json = (char *) malloc(/* TODO */);
    if (!json)
    {
        fprintf(stderr,
            "FATAL ERROR! Memory for JSON representation cannot be allocated!\n");
        exit(-1);
    }
    char *act_tab = mult(shift, tab);
    int res = sprintf(json,  // TODO content JSON
                      "%s{\n"
                      "%s%s\"type\": \"%s\",\n"
                      "%s%s\"children_number\": %d,\n"
                      "%s%s\"children\": [\n"
                      "%s"
                      "%s%s]"
                      "%s}",
                      act_tab,
                      act_tab, tab, ast_type_to_str(root->type),
                      act_tab, tab, root->children_number,
                      act_tab, tab,
                      conc_children,
                      act_tab, tab,
                      act_tab);
    free(conc_children);
    free(act_tab);
    if (res < 0)
    {
        fprintf(stderr,
            "FATAL ERROR! String formatting cannot be applied!\n");
        exit(-1);
    }
    return json;
}
