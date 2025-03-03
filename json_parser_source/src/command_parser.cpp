#include "command_parser.h"
#include "rapidjson/document.h"

#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <stdexcept>

using namespace rapidjson;
using namespace std;

const vector<string> requiredFields = {"commandId", "issuedBy", "issuedAt", "oprationn"};

//Constructor with default value for example deltaV passedd in
Command::Command() : deltaV(0.0) {}

//Custom constructor
Command::Command(const std::string& jsonStr) : deltaV(0.0) {
    auto cmd = parseCommand(jsonStr);
    *this = move(*cmd);
}

Command::~Command() = default;

Command& Command::operator=(const Command&) = default;

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