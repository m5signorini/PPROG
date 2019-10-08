/**
 * @brief It defines a textual graphic engine
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 18-01-2017
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"

typedef struct _Graphic_engine Graphic_engine;

/**
* @brief Creates a graphic engine
*
* graphic_engine_crete Creates a graphic engine for the game reserving memory for it
*
* @date 19/09/2019
* @author: Instructors
*
* @return the graphic engine created
*/
Graphic_engine* graphic_engine_create();

/**
* @brief Destroys a graphic engine previously created
*
* graphic_engine_destroy Destroys a graphic engine freeing its memory previosly reserved
*
* @date 15/01/2019
* @author: Instructors
*
* @param coffee the coffee whose price is computed
* @param size the size of the input coffee
* @return the price in Euro of the input coffee
*/
void graphic_engine_destroy(Graphic_engine *ge);

/**
* @brief It gives colour to the graphic engine created
*
*graphic_engine_paint_game Giuves colour to the graphic engine for the game
*
* @date 19/09/2019
* @author: Instructors
*
* @param ge the graphic engine the is going to be painted
* @param game the game whose graphic engine is going to be painted
*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

/**
* @brief
*
* graphic_engine_write_command
*
* @date 19/09/2019
* @author: Instructors
*
* @param ge
* @param str
* @return
*/
void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif
