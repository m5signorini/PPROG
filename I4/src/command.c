/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 19-12-2014
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <strings.h>
#include "command.h"

#define CMD_LENGHT 30

char* cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Next", "Back", "Right", "Left", "Up", "Down", "Move", "Take", "Drop", "Roll", "Inspect", "Turnon", "Turnoff"};
char* short_cmd_to_str[N_CMD] = {"","","e","n","b", "r", "l", "u", "dw", "m", "t","d", "rl", "i", "ton", "toff"};


T_Command command_get_user_input() {
  T_Command cmd = NO_CMD;
  char input[CMD_LENGHT] = "";
  int i = UNKNOWN - NO_CMD + 1;

  if (scanf("%s", input) > 0) {
    cmd = UNKNOWN;
    while(cmd == UNKNOWN && i < N_CMD){
      if (!strcasecmp(input,short_cmd_to_str[i]) || !strcasecmp(input, cmd_to_str[i])) {
        cmd = i + NO_CMD;
      }
      else {
         i++;
      }
    }
  }

  return cmd;
}
