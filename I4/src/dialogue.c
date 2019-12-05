
#define MAX_FEEDBACK 500

struct _Dialogue {
  char feedback[MAX_FEEDBACK + 1];  /*!< Feeback of the actual command.*/
  char last_cmd;  /*!< Feeback of the last command.*/
  STATUS last_status;   /*!< Status value of the last command.*/
};


STATUS dialogue_set_last_cmd(Dialogue* feedback, T_Command cmd) {
  if (!feedback) {
    return ERROR;
  }

  feedback->last_cmd = cmd;

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
    return ERROR;
  }

  return feedback->feedback;
}

T_Command dialogue_get_last_cmd(Dialogue* feedback) {
  if (!feedback) {
    return ERROR;
  }

  return feedback->last_cmd;
}

STATUS dialogue_get_last_status(Dialogue* feedback) {
  if (!feedback) {
    return ERROR;
  }

  return feedback->last_status;
}

Dialogue* dialogue_create() {
  Dialogue* dialogue=NULL;

  dialogue = (dialogue*)malloc(sizeof(Dialogue));
  if (dialogue==NULL) {
    return NULL;
  }

  memset(dialogue->feedback, 0, MAX_FEEDBACK + 1);
  dialogue->last_cmd = NO_CMD;

  return dialogue;
}

STATUS dialogue_get_feedback(T_Command cmd, STATUS status, Dialogue* feedback) {

  if (!feedback) {
    return ERROR;
  }

  if (cmd==NO_CMD) {
    //Error
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == NO_CMD) {
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
      if (feedback->last_status == ERROR) {
        if (feedback->last_cmd == UNKNOWN) {
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
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == EXIT) {
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

  else if (cmd==NEXT) {
    //Error
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == NEXT) {
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
      dialogue_set_feedback(feedback,"You've moved forward.");
      dialogue_set_last_cmd(feedback, NEXT);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==BACK) {
    //Error
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == BACK) {
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
      dialogue_set_feedback(feedback,"You've moved backwards.");
      dialogue_set_last_cmd(feedback, BACK);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==RIGHT) {
    //Error
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == RIGHT) {
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
      dialogue_set_feedback(feedback,"You've moved to the right.");
      dialogue_set_last_cmd(feedback, RIGHT);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==LEFT) {
    //Error
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == LEFT) {
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
      dialogue_set_feedback(feedback,"You've moved to the left.");
      dialogue_set_last_cmd(feedback, LEFT);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==UP) {
    //Error
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == UP) {
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
      dialogue_set_feedback(feedback,"You've moved above.");
      dialogue_set_last_cmd(feedback, UP);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==DOWN) {
    //Error
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == DOWN) {
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
      dialogue_set_feedback(feedback,"You've moved down.");
      dialogue_set_last_cmd(feedback, DOWN);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==MOVE) {

  }

  else if (cmd==TAKE) {
    //Error
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == TAKE) {
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
      dialogue_set_feedback(feedback,"You've taken the object.");
      dialogue_set_last_cmd(feedback, TAKE);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==DROP) {
    //Error
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == DROP) {
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
      dialogue_set_feedback(feedback,"You've dropped the object.");
      dialogue_set_last_cmd(feedback, DROP);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==ROLL) {
    //Error
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == ROLL) {
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
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == INSPECT) {
        dialogue_set_feedback(feedback,"You have done this before without success.");
        return OK;
      }
      else {
        dialogue_set_feedback(feedback,"You can't inspect it.");
        dialogue_set_last_cmd(feedback, INSPECT);
        dialogue_set_last_status(feedback, ERROR);
        return OK;
      }
    }
    //Success
    else {
      dialogue_set_feedback(feedback,"You've inspected it with success.");
      dialogue_set_last_cmd(feedback, INSPECT);
      dialogue_set_last_status(feedback, OK);
      return OK;
    }
  }

  else if (cmd==TURNON) {
    //Error
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == TURNON) {
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
    if (feedback->last_status == ERROR) {
      if (feedback->last_cmd == TURNOFF) {
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

  else {
    return NULL;
  }
}
