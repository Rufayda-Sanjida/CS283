#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dshlib.h"

/*
 *  build_cmd_list
 *    cmd_line:     the command line from the user
 *    clist *:      pointer to clist structure to be populated
 *
 *  This function builds the command_list_t structure passed by the caller
 *  It does this by first splitting the cmd_line into commands by spltting
 *  the string based on any pipe characters '|'.  It then traverses each
 *  command.  For each command (a substring of cmd_line), it then parses
 *  that command by taking the first token as the executable name, and
 *  then the remaining tokens as the arguments.
 *
 *  NOTE your implementation should be able to handle properly removing
 *  leading and trailing spaces!
 *
 *  errors returned:
 *
 *    OK:                      No Error
 *    ERR_TOO_MANY_COMMANDS:   There is a limit of CMD_MAX (see dshlib.h)
 *                             commands.
 *    ERR_CMD_OR_ARGS_TOO_BIG: One of the commands provided by the user
 *                             was larger than allowed, either the
 *                             executable name, or the arg string.
 *
 *  Standard Library Functions You Might Want To Consider Using
 *      memset(), strcmp(), strcpy(), strtok(), strlen(), strchr()
 */

void print_dragon() {
    printf("                                                                        @%%%%%%%%                        \n");
    printf("                                                                     %%%%%%%%%%%%                         \n");
    printf("                                                                    %%%%%%%%%%%%                          \n");
    printf("                                                                 %% %%%%%%%%%%%%%%           @              \n");
    printf("                                                                %%%%%%%%%%%%%%%%%%%%        %%%%%%%%%%%%%%           \n");
    printf("                                       %%%%%%%%%%%%%%  %%%%%%%%@         %%%%%%%%%%%%%%%%%%%%%%%%@    %%%%%%%%%%%%  @%%%%%%%%        \n");
    printf("                                  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%      %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%          \n");
    printf("                                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   %%%%%%%%%%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%           \n");
    printf("                               %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%     %%%%%%            \n");
    printf("                             %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@ @%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        %%%%            \n");
    printf("                            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                \n");
    printf("                            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%              \n");
    printf("                            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@%%%%%%%%%%%%@              \n");
    printf("      %%%%%%%%%%%%%%%%@           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%         %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%      %%%%                \n");
    printf("    %%%%%%%%%%%%%%%%%%%%%%%%%%         %%%%@%%%%%%%%%%%%%%%%%%%%%%%%           %%%%%%%%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%      @%%                \n");
    printf("  %%%%%%%%%%%%%%%%%%%%   %%%%%%        %%%%%%%%%%%%%%%%%%%%%%%%%%%%            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                        \n");
    printf(" %%%%%%%%%%%%%%%%%%       %%         %%%%%%%%%%%%%%%%%%%%%%%%%%             %%%%%%%%%%%%%%%%%%%%%%%%@%%%%%%%%%%%%%%%%%%%%%%                       \n");
    printf("%%%%%%%%%%%%%%%%%%@                %% %%%%%%%%%%%%%%%%%%%%%%%%%%            @%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                     \n");
    printf("%%%%%%%%%%%%%%%%@                 %%%%@%%%%%%%%%%%%%%%%%%%%%%%%            @%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                  \n");
    printf("%%%%%%%%%%%%%%@                   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%              \n");
    printf("%%%%%%%%%%%%%%%%%%%%                  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%          %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%      %%%%%%%%  \n");
    printf("%%%%%%%%%%%%%%%%%%@                   @%%%%%%%%%%%%%%%%%%%%%%%%%%%%         %%%%%%%%%%%%%%%%%%%%%%%%@ %%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   %%%%%%%%%%%%%%%%\n");
    printf("%%%%%%%%%%%%%%%%%%%%                  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        %%%%%%%%%%%%%%%%%%%%%%%%%%      %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%\n");
    printf("%%%%%%%%%%%%%%%%%%@%%%%@                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@       %%%%%%%%%%%%%%%%%%%%%%%%%%%%     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  %%%%\n");
    printf(" %%%%%%%%%%%%%%%%%%%%                  %% %%%%%%%%%%%%%%%%%%%%%%%%%%%%@        %%%%%%%%%%%%%%%%%%%%%%%%%%%%   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% %%%%\n");
    printf("  %%%%%%%%%%%%%%%%%%%%%%%%  @           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  %%%%%% \n");
    printf("   %%%%%%%%%%%%%%%%%%%%%%%%%% %%%%  %%  %%@ %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%          %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    %%%%%% \n");
    printf("    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%           @%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    %%%%%%%%%%%%%% \n");
    printf("     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%              %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        %%%%%%   \n");
    printf("      @%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%               \n");
    printf("        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                      %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  %%%%%%%%%%%%%%          \n");
    printf("           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  @%%%%%%%%%%%%%%%%%%         \n");
    printf("              %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%           @%%@%%                  @%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   %%%%%%        \n");
    printf("                  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        %%%%%%%%%%%%%%%%%%%%                    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    %%         \n");
    printf("                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                      %%%%%%%%%%%%%%%%%%%%%%%%%%%%            \n");
    printf("                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  %%%%%%%% %%%%%%                      %%%%%%%%%%%%%%%%%%%%  %%%%%%@          \n");
    printf("                     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% %%%%%%%%%%%% %%%%                          %%%%%%%%%%%%%%%%%%%%%%%%%%@          \n");    
    printf("                                                                                 %%%%%%%%%%%%%%@        \n");
}


int build_cmd_list(char *cmd_line, command_list_t *clist) {
    memset(clist, 0, sizeof(command_list_t));
    clist->num = 0;

    char *saveptr;
    char *command_segment = strtok_r(cmd_line, PIPE_STRING, &saveptr);

    while (command_segment != NULL) {
        if (clist->num >= CMD_MAX) {
            return ERR_TOO_MANY_COMMANDS;
        }


        while (isspace(*command_segment)) {
            command_segment++;
        }

        char *arg_saveptr;
        char *token = strtok_r(command_segment, " \t", &arg_saveptr);

        if (token != NULL) {
            if (strlen(token) >= EXE_MAX) {
                return ERR_CMD_OR_ARGS_TOO_BIG;
            }

            strncpy(clist->commands[clist->num].exe, token, EXE_MAX - 1);
            clist->commands[clist->num].exe[EXE_MAX - 1] = '\0';

            if (strcmp(token, "dragon") == 0) {
                print_dragon();
                return OK;
            }

            char argument_buffer[ARG_MAX] = "";
            while ((token = strtok_r(NULL, " \t", &arg_saveptr)) != NULL) {
                if (strlen(argument_buffer) + strlen(token) + 2 >= ARG_MAX) {
                    return ERR_CMD_OR_ARGS_TOO_BIG;
                }
                if (argument_buffer[0] != '\0') {
                    strcat(argument_buffer, " ");
                }
                strcat(argument_buffer, token);
            }

            strcpy(clist->commands[clist->num].args, argument_buffer);
            clist->num++;
        }

        command_segment = strtok_r(NULL, PIPE_STRING, &saveptr);
    }

    return OK;
}
