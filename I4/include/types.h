/**
 * @brief It defines common types
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 10000
#define NO_ID -1
#define IMG_SIZE 80
#define IMG_NUM 30
#define MAX_DESC 500
#define DIE_MIN 1
#define DIE_MAX 7
#define GUILTY_ID 666
#define VICTORY_ID 777
#define DEFEAT_ID 888

typedef long Id;

typedef enum {
  FALSE, TRUE
} BOOL;

typedef enum {
  ERROR, OK
} STATUS;

typedef enum {
  N, S, E, W, U, D, NO_DIR
} DIRECTION;

#endif
