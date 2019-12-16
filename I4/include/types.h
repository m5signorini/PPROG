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
#define IMG_SIZE 70
#define IMG_NUM 30
#define MAX_DESC 128

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
