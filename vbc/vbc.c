#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Tree node definition
typedef struct node {
    enum { ADD, MULTI, VAL } type;
    int val;
    struct node *l, *r;
} node;

// Memory-safe node creation
node *new_node(node n)
{
    node *out = calloc(1, sizeof(node));
    if (!out)
        exit(1);
    *out = n;
    return out;
}

// Tree destructor
void destroy_tree(node *tree)
{
    if (!tree)
        return;
    destroy_tree(tree->l);
    destroy_tree(tree->r);
    free(tree);
}

// Evaluate tree recursively
int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return eval_tree(tree->l) + eval_tree(tree->r);
        case MULTI:
            return eval_tree(tree->l) * eval_tree(tree->r);
        case VAL:
            return tree->val;
    }
    return 0;
}

// Error handler
void unexpected(char c)
{
    if (c == '\0')
        printf("Unexpected end of input\n");
    else
        printf("Unexpected token '%c'\n", c);
    exit(1);
}

// Helpers to consume tokens
int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

void expect(char **s, char c)
{
    if (!accept(s, c))
        unexpected(**s);
}

void expect_end(char **s)
{
    if (**s != '\0')
        unexpected(**s);
}

// Forward declarations
node *parse_expr(char **s);
node *parse_term(char **s);
node *parse_factor(char **s);

// factor = digit | (expr)
node *parse_factor(char **s)
{
    node *res;

    if (isdigit(**s))
        return new_node((node){.type = VAL, .val = *(*s)++ - '0'});

    if (accept(s, '('))
    {
        res = parse_expr(s);
        expect(s, ')');
        return res;
    }

    unexpected(**s);
    return NULL;
}

// term = factor {* factor}
node *parse_term(char **s)
{
    node *left = parse_factor(s);

    while (accept(s, '*'))
    {
        node *right = parse_factor(s);
        left = new_node((node){.type = MULTI, .l = left, .r = right});
    }
    return left;
}

// expr = term {+ term}
node *parse_expr(char **s)
{
    node *left = parse_term(s);

    while (accept(s, '+'))
    {
        node *right = parse_term(s);
        left = new_node((node){.type = ADD, .l = left, .r = right});
    }
    return left;
}

// Main entry point
int main(int ac, char **av)
{
    if (ac != 2)
        return (1);

    char *s = av[1];
    node *tree = parse_expr(&s);
    expect_end(&s);
    int res = eval_tree(tree);
    printf("%d\n", res);
    destroy_tree(tree);
    return (0);
}
