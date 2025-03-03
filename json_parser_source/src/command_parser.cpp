#include "command_parser.h"
#include "rapidjson/document.h"
#include <cstdlib>
#include <cstring>
#include <unordered_map>

using namespace rapidjson;
using namespace std;

Document document; 


string covertErrorCode(ErrorCode code) {
    static const unordered_map<ErrorCode,std::string> errorMessages = {
        {SUCCESS, "Success"},
        {ERR_INCORRECT_FORMAT, "Incorrect format in command parser"},
        {ERR_MISSING_FIELD, "Required field is missing"},
        {ERR_INVALID_TYPE, "Field has invalid data type"},
        {ERR_PARSE_FAILURE, "JSON parsing failed"},
        {ERR_INVALID_COMMAND, "Invalid command structure"}
    };

    auto it = errorMessages.find(code);
    if (it != errorMessages.end()) {
        return it->second;
    }
    return "Unkown error";
}

ErrorCode parseJson(const char* json, rapidjson::Document& document) {
    
    document.Parse(json);

    if (document.HasParseError()) {
        return ERR_PARSE_FAILURE;
    }

    if (!document.IsObject()) {
        return ERR_INCORRECT_FORMAT;
    }


    //Check to see that it has the required fields
    for (const char* field : requiredFields) {
        if (!document.HasMember(field)) {
            return ERR_MISSING_FIELD;
        }
    }

    if (!document["commandId"].IsString() ||
        !document["issuedBy"].IsString() ||
        !document["issuedAt"].IsString() ||
        !document["operation"].IsString()) {
            return ERR_INVALID_TYPE;
    }

    return SUCCESS;

}