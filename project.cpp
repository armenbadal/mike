#include "project.h"

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include <fstream>
#include <unordered_map>

namespace mike {

project::project(const filesystem::path& setup_file)
{
    load(setup_file);
    verify_rules();
}

const auto setup_schema = R"json(
{
    "type": "object",
    "properties": {
        "project": {
            "type": "string"
        },
        "files": {
            "type": "array",
            "items": {
                "type": "string"
            }
        },
        "rules": {
            "type": "array",
            "items": {
                "type": "object",
                "properties": {
                    "goal": {
                        "type": "string"
                    },
                    "dependencies": {
                        "type": "array",
                        "items": {
                            "type": "string"
                        }
                    },
                    "commands": {
                        "type": "array",
                        "items": {
                            "type": "string"
                        }
                    }
                },
                "additionalProperties": false
            }
        }
    },
    "additionalProperties": false
}
)json"_json;


void project::load(const filesystem::path& setup_file)
{
    ifstream in{setup_file};
    const auto setup_data = nlohmann::json::parse(in);
    nlohmann::json_schema::json_validator validator(setup_schema);
    validator.validate(setup_data);

    _name = setup_data["project"];

    for (const auto& p : setup_data["files"])
        _files.push_back(file{p});

    for( const auto& rr : setup_data["rules"] ) {
        string goal = rr["goal"].get<string>();
        vector<string> dependencies = rr["dependencies"];
        vector<string> commands = rr["commands"];
        _rules.push_back({goal, dependencies, commands});
    }
}


void project::verify_rules()
{

}


void project::build()
{
    detect_roots();
}

void project::detect_roots()
{

}

} // namespace mike
