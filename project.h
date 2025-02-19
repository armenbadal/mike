#pragma once

#include "rule.h"

#include <filesystem>
#include <vector>

namespace mike {

using namespace std;

class project {
public:
    explicit project(const filesystem::path& setup_file);

    void build();

private:
    void load(const filesystem::path& setup_file);
    void verify_rules();
    void detect_roots();

    string _name;
    vector<file> _files;
    vector<rule> _rules;
};

} // namespace mike
