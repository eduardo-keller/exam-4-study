#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
// |

typedef struct s_cmd
{
    char    **args;
    int     pipe;
    int     end;
    struct s_cmd    *next;
}   t_cmd;

char    *ft_strdup(char *str)
{
    char    *new;
    int i;
    //int len = 0;

    i = 0;
    while (str[i])
        i++;
    new = malloc(i + 1);
    i = 0;
    while (str[i])
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

void init_cmds(t_cmd *cmds)
{
    printf("entrou no init\n");
    cmds->pipe = 0;
    cmds->end = 0;
    cmds->next = NULL;
}

// int parse_cmds(int argc, char **argv, t_cmd *cmds)
// {
//     int i;
//     int k;
//     t_cmd   *temp;

//     i = 1; 
//     temp = cmds;
//     while(i < argc)
//     {
//         if (strcmp(argv[i], "|") == 0)
//         {
//             cmds->pipe = 1;
//             temp->next = malloc(sizeof(t_cmd *));
//             init_cmds(temp->next);
//             temp = temp->next;
//             i++;
//         }
//         else if (strcmp(argv[i], ";") == 0)
//         {
//             cmds->end = 1;
//             if (argv[i + 1])
//             {
//                 temp->next = malloc(sizeof(t_cmd *));
//                 init_cmds(temp->next);
//                 temp = temp->next;
//                 i++;
//             }
//         }
//         else
//         {
//             if (!cmds->args)
//             {
//                 k = i;
//                 while (strcmp(argv[k], "|") != 0 && strcmp(argv[k], ";") != 0)
//                     k++;
//                 cmds->args = malloc ((k - i + 1) * sizeof(char *));
//             }
//             k = 0;
//             cmds->args[k++] = ft_strdup(argv[i]);
//             if (strcmp(argv[i + 1], "|") == 0 || strcmp(argv[i + 1], ";") == 0)
//                 cmds->args[k] = NULL;
//             printf("%s\n", );
//             i++;
//         }
//     }
//     return (0);
// }

void parse_cmds(int argc, char **argv, t_cmd *cmds)
{
    int i;
    int k;
    t_cmd   *temp;

    i = 1; 
    temp = cmds;
    k = 0;
    printf("entrou no parser\n");
    while (i < argc)
    {
        while(argv[i] && (strcmp(argv[i], "|") != 0 || strcmp(argv[i], ";") != 0))
        {
            if (!cmds->args)
            {
                k = i;
                while (strcmp(argv[k], "|") != 0 && strcmp(argv[k], ";") != 0)
                    k++;
                cmds->args = malloc ((k - i + 1) * sizeof(char *));
            }
            
            cmds->args[k++] = ft_strdup(argv[i]);
            if (strcmp(argv[i + 1], "|") == 0 || strcmp(argv[i + 1], ";") == 0)
                cmds->args[k] = NULL;
            i++;
        }
        if (argv[i] && strcmp(argv[i], "|") == 0)
        {
            cmds->pipe = 1;
            temp->next = malloc(sizeof(t_cmd *));
            init_cmds(temp->next);
            temp = temp->next;
            i++;
        }
        else if (argv[i] && strcmp(argv[i], ";") == 0)
        {
            cmds->end = 1;
            if (argv[i + 1])
            {
                temp->next = malloc(sizeof(t_cmd *));
                init_cmds(temp->next);
                temp = temp->next;
                i++;
            }
        }
    }
}

//./exam4 ls -l | grep mini ;

int main(int argc, char **argv, char **envp)
{

    t_cmd   *cmds;
    if (envp)
        envp = envp;
    if (argc == 1)
        return (0);
    // printf("%i\n", argc);
    // printf("%s\n", argv[1]);
    // printf("entrou na main\n");
    cmds = malloc(sizeof(t_cmd *));
    init_cmds(cmds);
    parse_cmds(argc, argv, cmds);
    printf("%s %s %i %i\n", cmds->args[0], cmds->args[1], cmds->pipe, cmds->end);
    cmds = cmds->next;
    printf("%s %s %i %i\n", cmds->args[0], cmds->args[1], cmds->pipe, cmds->end);
    return (0);
}