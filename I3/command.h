/**
 * @brief It implements the command interpreter
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 19-12-2014
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#define N_CMD

typedef enum enum_Command {
  NO_CMD = -1,
  UNKNOWN,
  EXIT,
  NEXT,
  BACK,
  RIGHT,
  LEFT,
  TAKE,
  DROP,
  ROLL,
  INSPECT} T_Command;

/**
* @brief Gets the user input for the command
*
* get_user_input scans the input and return the specified command
*
* @date 25/10/2019
* @author: Profesores PPROG
*
* @return the command scanned
*/
T_Command command_get_user_input();

#endif
