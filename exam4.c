/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:18:38 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/23 17:28:43 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */





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
    cmds->pipe = 0;
    cmds->end = 0;
    cmds->next = NULL;
}

void parse_cmds(int argc, char **argv, t_cmd *cmds)
{
    int i;
    int k;
    t_cmd   *temp;

    i = 0; 
    temp = cmds;
    k = 0;
    while (i < argc - 1)
    {
        while(argv[i + 1] && (strcmp(argv[i + 1], "|") != 0 && strcmp(argv[i + 1], ";") != 0))
        {
            printf("entrou no primeiro while parser\n");
            if (!cmds->args)
            {
                while (argv[i + 1] && strcmp(argv[i + 1], "|") != 0 && strcmp(argv[i + 1], ";") != 0)
                {
                    printf("entrou no segundo while parser\n");
                    k++;    
                }    
                
                cmds->args = malloc ((k + 1) * sizeof(char *));
            }
            k = 0;
            cmds->args[k++] = ft_strdup(argv[i + 1]);
            printf("chamou cmds->args[k++] = ft_strdup(argv[i]);\n");
            if (argv[i + 1] && (strcmp(argv[i + 1], "|") == 0 || strcmp(argv[i + 1], ";") == 0))
                cmds->args[k] = NULL;
            i++;
        }
        k = 0;
        if (argv[i + 1] && strcmp(argv[i + 1], "|") == 0)
        {
            cmds->pipe = 1;
            temp->next = malloc(sizeof(t_cmd));
            init_cmds(temp->next);
            temp = temp->next;
            i++;
        }
        else if (argv[i + 1] && strcmp(argv[i + 1], ";") == 0)
        {
            cmds->end = 1;
            if (argv[i + 2])
            {
                temp->next = malloc(sizeof(t_cmd));
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

    int i = 0;
    t_cmd   *cmds;
    if (envp)
        envp = envp;
    if (argc == 1)
        return (0);
    cmds = malloc(sizeof(t_cmd));
    init_cmds(cmds);
    parse_cmds(argc, argv, cmds);
    while (cmds->args[i])
        printf ("%s\n", cmds->args[i]);
    // cmds = cmds->next;
    return (0);
}