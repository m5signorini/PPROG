/**
 * @brief It defines a screen
 *
 *Added descriptions
 * @file screen.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 11-01-2017
 * @copyright GNU Public License
 */

#ifndef __SCREEN__
#define __SCREEN__

#define MAP_W (48+65)
#define MAP_H (21+50)
#define SCREEN_MAX_STR (80+80)

typedef struct _Area Area;

/**
* @brief It initialize a screen manager
*
* screen_init Initializes a screen manager and it reserves
* memory for it
*
* @date 19/09/2019
* @author: Profesores PPROG
*/
void  screen_init();

/**
* @brief It destroys a screen manager
*
* screen_destroy Destroys a screen manager and it fress the memory
* previously reserved
*
* @date 19/09/2019
* @author: Profesores PPROG
*/
void  screen_destroy();

/**
* @brief It gives colour to the screen created
*
* screen_paint gives the colours to the screen
* previously reserved
*
* @date 19/09/2019
* @author: Profesores PPROG
*/
void  screen_paint();

/**
* @brief Gets and replaces line with null
*
* screen_gets gets and replaces line with null
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param *str string used in the gets
*/
void  screen_gets(char *str);

/**
* @brief Creates an areain the screen
*
* screen_area_init Creates a particular area
* in the screen previously created
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param x position respect to a particular axis
* @param y position respect to a particuar axis
* @param width width of the area that is going to be created
* @param height height of the area that is going to be created
* @return the area finally created
*/
Area* screen_area_init(int x, int y, int width, int height);

/**
* @brief Destroys an area previously created
*
* screen_area_destroys Destroys a particular area
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param area the area that has to be destroyed
*/
void  screen_area_destroy(Area* area);

/**
* @brief Clears the elements of an Area's variable type
*
* screen_area_clear Clears the elements of a particular area of the screeen
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param area the area that is going to be cleared
*/
void  screen_area_clear(Area* area);

/**
* @brief Resets the cursor of an Area's variable type
*
* screen_area_rest_cursor Resets the cursor of the given area
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param area the area which cursor is reseted
*/
void  screen_area_reset_cursor(Area* area);

/**
* @brief Puts a created area in a screen
*
* screen_area_puts Puts the area previously created in the screen
*
* @date 19/09/2019
* @author: Profesores PPROG
*
* @param area the area which is going to be added to the screen
* @param *str the special characters of the area are replaced by this characters
*/
void  screen_area_puts(Area* area, char *str);

#endif
