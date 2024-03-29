/**
* @brief It implements the dialogue for friendlier messages to the user
*
*
* @file dialogue.c
* @author Gonzalo
* @version 3.0
* @date 5-12-2019
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dialogue.h"

#define MAX_FEEDBACK 500

struct _Dialogue {
  char feedback[MAX_FEEDBACK + 1];  /*!< Feeback of the actual command.*/
  char last_cmd;  /*!< Feeback of the last command.*/
  STATUS last_status;   /*!< Status value of the last command.*/
  char description[MAX_DESC + 1]; /*!< Description of a space.*/
  DIRECTION dir; /*!< Direction of the move command.*/
};


STATUS dialogue_set_last_cmd(Dialogue* feedback, T_Command cmd) {
  if (!feedback) {
    return ERROR;
  }

  feedback->last_cmd = cmd;

  return OK;
}

STATUS dialogue_set_direction(Dialogue* feedback, DIRECTION dir) {
  if (!feedback) {
    return ERROR;
  }

  feedback->dir = dir;

  return OK;
}

STATUS dialogue_set_description(Dialogue* feedback, const char* desc) {
  if (!feedback || !desc) {
    return ERROR;
  }
  strncpy(feedback->description, desc, MAX_DESC);
  return OK;
}

STATUS dialogue_set_last_status(Dialogue* feedback, STATUS status) {
  if (!feedback) {
    return ERROR;
  }

  feedback->last_status = status;

  return OK;
}

STATUS dialogue_set_feedback(Dialogue* feedback, const char* string) {
  if (!feedback || !string) {
    return ERROR;
  }

  strcpy(feedback->feedback, string);

  return OK;
}

const char* dialogue_get_feedback(Dialogue* feedback) {
  if (!feedback) {
    return NULL;
  }

  return feedback->feedback;
}

T_Command dialogue_get_last_cmd(Dialogue* feedback) {
  if (!feedback) {
    return NO_CMD;
  }

  return feedback->last_cmd;
}

DIRECTION dialogue_get_direction(Dialogue* feedback) {
  if (!feedback) {
    return NO_DIR;
  }

  return feedback->dir;
}

char* dialogue_get_description(Dialogue* feedback) {
  if (!feedback) {
    return NULL;
  }

  return feedback->description;
}

STATUS dialogue_get_last_status(Dialogue* feedback) {
  if (!feedback) {
    return ERROR;
  }

  return feedback->last_status;
}

Dialogue* dialogue_create() {
  Dialogue* dialogue=NULL;

  dialogue = (Dialogue*)malloc(sizeof(Dialogue));
  if (dialogue==NULL) {
    return NULL;
  }

  memset(dialogue->feedback, 0, MAX_FEEDBACK + 1);
  memset(dialogue->description, 0, MAX_DESC + 1);
  dialogue->dir = N;
  dialogue->last_cmd = NO_CMD;
  dialogue->last_status = ERROR;

  return dialogue;
}

STATUS dialogue_destroy(Dialogue* dialogue) {
  if (!dialogue) {
    return ERROR;
  }

  free(dialogue);

  return OK;
}

STATUS dialogue_produce(T_Command cmd, STATUS status, Dialogue* feedback) {
  char str[MAX_FEEDBACK + 1];

  if (!feedback) {
    return ERROR;
  }

  memset(str, 0, MAX_FEEDBACK + 1);

  if (cmd==NO_CMD) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == NO_CMD) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"Try a command.");
        dialogue_set_last_cmd(feedback, NO_CMD);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
  }

  else if (cmd==UNKNOWN) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == UNKNOWN) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"Learn how to write please...");
        dialogue_set_last_cmd(feedback, UNKNOWN);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
  }

  else if (cmd==EXIT) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == EXIT) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't exit the game.");
        dialogue_set_last_cmd(feedback, EXIT);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      dialogue_set_feedback(feedback,"You've exit the game.");
      dialogue_set_last_cmd(feedback, EXIT);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==NEXT  || (cmd==MOVE && feedback->dir == S)) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == NEXT) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't go forward.");
        dialogue_set_last_cmd(feedback, NEXT);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      sprintf(str, "You've moved forward. You are now in ");
      strcat(str, feedback->description);
      dialogue_set_feedback(feedback, str);
      dialogue_set_last_cmd(feedback, NEXT);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==BACK  || (cmd==MOVE && feedback->dir == N)) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == BACK) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't go back.");
        dialogue_set_last_cmd(feedback, BACK);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      sprintf(str, "You've moved backwards. You are now in ");
      strcat(str, feedback->description);
      dialogue_set_feedback(feedback, str);
      dialogue_set_last_cmd(feedback, BACK);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==RIGHT  || (cmd==MOVE && feedback->dir == E)) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == RIGHT) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't go to the right.");
        dialogue_set_last_cmd(feedback, RIGHT);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      sprintf(str, "You've moved to the right. You are now in ");
      strcat(str, feedback->description);
      dialogue_set_feedback(feedback, str);
      dialogue_set_last_cmd(feedback, RIGHT);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==LEFT || (cmd==MOVE && feedback->dir == W)) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == LEFT) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't go to the left.");
        dialogue_set_last_cmd(feedback, LEFT);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      sprintf(str, "You've moved to the left. You are now in ");
      strcat(str, feedback->description);
      dialogue_set_feedback(feedback, str);
      dialogue_set_last_cmd(feedback, LEFT);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==UP || (cmd==MOVE && feedback->dir == U)) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == UP) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't go up.");
        dialogue_set_last_cmd(feedback, UP);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      sprintf(str, "You've moved above. You are now in ");
      strcat(str, feedback->description);
      dialogue_set_feedback(feedback, str);
      dialogue_set_last_cmd(feedback, UP);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==DOWN || (cmd==MOVE && feedback->dir == D)) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == DOWN) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't go down.");
        dialogue_set_last_cmd(feedback, DOWN);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      sprintf(str, "You've moved down. You are now in ");
      strcat(str, feedback->description);
      dialogue_set_feedback(feedback, str);
      dialogue_set_last_cmd(feedback, DOWN);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==TAKE) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == TAKE) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't take this object.");
        dialogue_set_last_cmd(feedback, TAKE);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      sprintf(str, "You've taken the object ");
      strcat(str, feedback->description);
      dialogue_set_feedback(feedback, str);
      dialogue_set_last_cmd(feedback, TAKE);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==DROP) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == DROP) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't drop this object.");
        dialogue_set_last_cmd(feedback, DROP);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      sprintf(str, "You've dropped the object ");
      strcat(str, feedback->description);
      dialogue_set_feedback(feedback, str);
      dialogue_set_last_cmd(feedback, DROP);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==ROLL) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == ROLL) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't roll the die.");
        dialogue_set_last_cmd(feedback, ROLL);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      dialogue_set_feedback(feedback,"You've rolled the die.");
      dialogue_set_last_cmd(feedback, ROLL);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==INSPECT) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == INSPECT) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't inspect this.");
        dialogue_set_last_cmd(feedback, INSPECT);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      dialogue_set_feedback(feedback,feedback->description);
      dialogue_set_last_cmd(feedback, INSPECT);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==TURNON) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == TURNON) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't turn on this object.");
        dialogue_set_last_cmd(feedback, TURNON);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      dialogue_set_feedback(feedback,"You've turned on the object.");
      dialogue_set_last_cmd(feedback, TURNON);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }


  else if (cmd==TURNOFF) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == TURNOFF) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't turn off this object.");
        dialogue_set_last_cmd(feedback, TURNOFF);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      dialogue_set_feedback(feedback,"You've turned off the object.");
      dialogue_set_last_cmd(feedback, TURNOFF);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==SAVE) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == SAVE) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't save the game.");
        dialogue_set_last_cmd(feedback, SAVE);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      dialogue_set_feedback(feedback,"You've saved the game.");
      dialogue_set_last_cmd(feedback, SAVE);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==LOAD) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == LOAD) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't load the game.");
        dialogue_set_last_cmd(feedback, LOAD);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      dialogue_set_feedback(feedback,"You've loaded the game.");
      dialogue_set_last_cmd(feedback, LOAD);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==ACCUSE) {
    //Error
    if (status == ERROR) {
      if (feedback->last_status == ERROR && feedback->last_cmd == ACCUSE) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't accuse that.");
        dialogue_set_last_cmd(feedback, ACCUSE);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      dialogue_set_feedback(feedback,"You've accused someone.");
      dialogue_set_last_cmd(feedback, ACCUSE);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  return ERROR;
}
