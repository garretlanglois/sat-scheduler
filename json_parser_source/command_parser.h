#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

//
typedef struct command_t{
    char *commandId; //Unique command id, this will be created in the front-end
    char *issuedBy;
    char *issuedAt; //Timestamp of when the command was issued
    char *priority; //Priority in execution
    char *jwt; //JWT token issued by keycloak
    char *operation; //Operation name from the "payload" object
    double deltaV; //example parameter for payload
    char *axis; //exmaple parameter for payload 
} command_t;

//Parse the command JSON string and returns 0 on success.
int parse_command(const char *json_str, command_t **cmd_out);

void free_memory(command_t *cmd);

#endif