#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include <memory>
#include <vector>

using namespace std;

#if defined(_WIN32) || defined(_WIN64)
    #ifdef COMMAND_PARSER_EXPORTS
        #define COMMAND_API __declspec(dllexport)
    #else   
        #define COMMAND_API __declspec(dllimport)
    #endif
#else
    #define COMMAND_API __attribute__((visibility("default")))
#endif


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


/* Error codes*/

enum ErrorCode {
    SUCCESS = 0,
    ERR_INCORRECT_FORMAT = 1,
    ERR_MISSING_FIELD = 2,
    ERR_INVALID_TYPE = 3,
    ERR_PARSE_FAILURE = 4,
    ERR_INVALID_COMMAND = 5,
};

extern COMMAND_API const vector<string> requiredFields;


class COMMAND_API Command {
    public:
        string commandId;

};

//Parse the command JSON string and returns 0 on success.
int parse_command(const char *json_str, command_t **cmd_out);

void free_memory(command_t *cmd);

#endif