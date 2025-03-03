#include "command_parser.h"
#include "rapidjson/document.h"

#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <stdexcept>

using namespace rapidjson;
using namespace std;

const vector<string> requiredFields = {"commandId", "issuedBy", "issuedAt", "operation"};

//Constructor with default value for example deltaV passedd in
Command::Command() : deltaV(0.0) {}

//Custom constructor
Command::Command(const std::string& jsonStr) : deltaV(0.0) {
    auto cmd = parseCommand(jsonStr);
    *this = move(*cmd);
}

Command::~Command() = default;

Command& Command::operator=(const Command&) = default;


//Cpp implementation for easy use
unique_ptr<Command> parseCommand(const string& jsonStr) {
    if (jsonStr.empty()) {
        throw invalid_argument("Empty JSON string");
    }

    Document document; 

    document.Parse(jsonStr.c_str());

    if (document.HasParseError()) {
        throw runtime_error(
            "JSON parse error"
        );
    }

    if (!document.IsObject()) {
        throw runtime_error(
            "JSON is not an object"
        );
    }


    //Need to check required fields
    for (const auto& field : requiredFields) {
        if (!document.HasMember(field.c_str())) {
            throw runtime_error("Missing required field: " + field);
        }
    }

    auto cmd = make_unique<Command>();


    //These are the mandatory ones
    cmd->commandId = document["commandId"].GetString();
    cmd->issuedBy = document["issuedBy"].GetString();
    cmd->issuedAt = document["issuedAt"].GetString();
    cmd->operation = document["operation"].GetString();

    //Copy optional string fields if they exist

    if (document.HasMember("priority") && document["priority"].IsString()) {
        cmd->priority = document["priority"].GetString();
    }
    
    if (document.HasMember("jwt") && document["jwt"].IsString()) {
        cmd->jwt = document["jwt"].GetString();
    }
    
    if (document.HasMember("axis") && document["axis"].IsString()) {
        cmd->axis = document["axis"].GetString();
    }
    
    // Copy numeric fields if they exist
    if (document.HasMember("deltaV")) {
        if (document["deltaV"].IsNumber()) {
            cmd->deltaV = document["deltaV"].GetDouble();
        } else {
            throw std::runtime_error("Field deltaV must be a number");
        }
    }
    
    return cmd;

}

//C function so that it can be used by other software as a dll

extern "C" COMMAND_API int parse_command(const char *json_str, command_t **cmd_out) {
    if (!json_str || !cmd_out) {
        return ERR_MISSING_FIELD;
    }

    try {
        auto cppCommand = parseCommand(json_str);

        command_t *cmd = (command_t*)(malloc(sizeof(command_t)));

        if (!cmd) {
            return ERR_MEMORY_ALLOCATION;
        }

        memset(cmd, 0, sizeof(command_t));

        // Copy data from C++ object to C struct
        cmd->commandId = strdup(cppCommand->commandId.c_str());
        cmd->issuedBy = strdup(cppCommand->issuedBy.c_str());
        cmd->issuedAt = strdup(cppCommand->issuedAt.c_str());
        cmd->priority = cppCommand->priority.empty() ? nullptr : strdup(cppCommand->priority.c_str());
        cmd->jwt = cppCommand->jwt.empty() ? nullptr : strdup(cppCommand->jwt.c_str());
        cmd->operation = strdup(cppCommand->operation.c_str());
        cmd->deltaV = cppCommand->deltaV;
        cmd->axis = cppCommand->axis.empty() ? nullptr : strdup(cppCommand->axis.c_str());
        
        *cmd_out = cmd;
        return SUCCESS;
    } catch (const exception& e) {
        return ERR_PARSE_FAILURE;
    }

}

extern "C" COMMAND_API void free_memory(command_t *cmd) {
    if (cmd) {
        free(cmd->commandId);
        free(cmd->issuedBy);
        free(cmd->issuedAt);
        free(cmd->priority);
        free(cmd->jwt);
        free(cmd->operation);
        free(cmd->axis);
        free(cmd);
    }
}

string errorCodeToString(ErrorCode code) {
    switch (code) {
        case SUCCESS:
            return "Success";
        case ERR_INCORRECT_FORMAT:
            return "Incorrect format in command parser";
        case ERR_MISSING_FIELD:
            return "Required field is missing";
        case ERR_INVALID_TYPE:
            return "Field has invalid data type";
        case ERR_PARSE_FAILURE:
            return "JSON parsing failed";
        case ERR_MEMORY_ALLOCATION:
            return "Memory allocation failed";
        default:
            return "Unknown error";
    }
}