/**
 * @brief It defines a textual graphic engine
 *
 * @file graphic_engine.h
 * @author Martin Sanchez Signorini
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
* graphic_engine_crete Creates a graphic engine allocating memory for it
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @return the graphic engine created
*/
Graphic_engine* graphic_engine_create();

/**
* @brief Destroys a graphic engine previously created
*
* graphic_engine_destroy Destroys a graphic engine freeing its memory previously allocated
*
* @date 15/01/2019
* @author: Martin Sanchez Signorini
*
* @param ge the graphic engine to destroy
*/
void graphic_engine_destroy(Graphic_engine *ge);

/**
* @brief Displays the game
*
* graphic_engine_paint_game paints the graphics of the game 
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param ge the graphic engine 
* @param game the game that the graphic engine is going to use
*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

/**
* @brief
*
* graphic_engine_write_command
*
* @date 19/09/2019
* @author: Martin Sanchez Signorini
*
* @param ge
* @param str
* @return
*/
void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif
