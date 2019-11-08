/**
 * @brief It defines a space
 *
 * Added descriptions
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"

typedef struct _Link Link;

Link* link_create(Id id);

STATUS link_destroy(Link* link);

Id link_get_id(Link* link);

STATUS link_set_name(Link* link, char* name);

const char * link_get_name(Link* link);

STATUS link_set_space1(Link* link, Id from);

Id link_get_space1(Link* link);

STATUS link_set_space2(Link* link, Id to);

Id link_get_space2(Link* link);

STATUS link_set_open(Link* link, BOOL open);

BOOL link_get_open(Link* link);

Id link_get_to(Link* link, Id current_id);

STATUS link_print(Link *link);

#endif
