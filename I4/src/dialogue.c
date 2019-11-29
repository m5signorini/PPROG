
#define MAX_FEEDBACK 500

struct _Dialogue {
  char feedback[MAX_FEEDBACK + 1];  /*!< Feeback of the actual command.*/
  char last_feedback[MAX_FEEDBACK + 1];  /*!< Feeback of the last command.*/
  STATUS last_status;   /*!< Status value of the last command.*/
};

//cambiar last_feedback por last_command para que sea mas facil comparar

Dialogue* dialogue_create() {
  Dialogue* dialogue=NULL;

  dialogue = (dialogue*)malloc(sizeof(Dialogue));
  if (dialogue==NULL) {
    return NULL;
  }

  memset(dialogue->feedback, 0, MAX_FEEDBACK + 1);
  memset(dialogue->last_feedback, 0, MAX_FEEDBACK + 1);

  return dialogue;
}

char* dialogue_get_feedback (T_Command cmd, STATUS status, Dialogue* feedback) {

  if (!feedback) {
    return NULL;
  }

  if (cmd==NO_CMD) {
      if (dialogue->last_status == ERROR) {
        if (strcmp(dialogue->last_feedback,"Try a command.")==0) {
          strcpy(dialogue->feedback,"You have done this before without success.");
          return dialogue->feedback;
        }
      }
      else {
          strcpy(dialogue->feedback,"Try a command.");
          strcpy(dialogue->last_feedback, "Try a command.");
          return dialogue->feedback;
      }

  }

  else if (cmd==UNKNOWN) {

  }

  else if (cmd==EXIT) {

  }

  else if (cmd==NEXT) {

  }

  else if (cmd==BACK) {

  }

  else if (cmd==RIGHT) {

  }

  else if (cmd==LEFT) {

  }

  else if (cmd==UP) {

  }

  else if (cmd==DOWN) {

  }

  else if (cmd==MOVE) {

  }

  else if (cmd==TAKE) {

  }

  else if (cmd==DROP) {

  }

  else if (cmd==ROLL) {

  }

  else if (cmd==INSPECT) {

  }

  else if (cmd==TURNON) {

  }


  else if (cmd==TURNOFF) {

  }

  else {
    return NULL;
  }
}

char* dialogue_no_cmd (char* feedback) {

}
