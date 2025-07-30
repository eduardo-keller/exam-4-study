#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

// expr   = term { + term }*
// term   = factor { * factor }*
// factor = number | '(' expr ')'

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}
!!!!!!!!!!!!!
int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

//...

// node    *parse_expr(char *s)
// {
//     //...

//     if (*s) 
//     {
//         destroy_tree(ret);
//         return (NULL);
//     }
//     return (ret);
// }

node	*parse_expr(char **s);

node	*parse_factor(char **s)
{
	node	*new;
	
	if(isdigit(**s))
	{
		node n = {.type = VAL, .val = **s - '0', .l = NULL, .r = NULL};
		(*s)++;
		return (new_node(n));
	}
	if(accept(s, '('))
	{
		new = parse_expr(s);
		if(!expect(s, ')'))
		{
			destroy_tree(new);
			return (NULL);
		}
		return (new);
	}
	unexpected(**s);
	return (NULL);
}

node	*parse_term(char **s)
{
	node	*left;
	node	*right;

	left = parse_factor(s);
	if (!left)
		return (NULL);

	while(accept(s, '*'))
	{
		right = parse_factor(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		node n = {.type = MULTI, .l = left, .r = right};
		left = new_node(n);
		if (!left)
			return (NULL);
	}
	return (left);
}

node	*parse_expr(char **s)
{
	node	*left;
	node	*right;
	
	left = parse_term(s);
	if (!left)
		return (NULL);

	while(accept(s, '+'))
	{
		right = parse_term(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		node n = {.type = ADD, .l = left, .r = right};
		left = new_node(n);
		if (!left)
			return (NULL);
	}
	if(**s)
	{
		unexpected(**s);
		destroy_tree(left);
		return (NULL);
	}
	return (left);
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
	return (0);
}

int main(int argc, char **argv)
{
    char *s;
	
	if (argc != 2)
        return (1);
	s = argv[1];
    node *tree = parse_expr(&s);
    if (!tree)
        return (1);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
	return (0);
}