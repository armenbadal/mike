#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>


namespace mike {

using namespace std;

class dependency {
public:
    virtual filesystem::file_time_type last_update() const = 0;
    size_t dependants() { return _dependants; }

protected:
    size_t _dependants{0};
};


class file : public dependency {
public:
    file(const filesystem::path& p);

    const filesystem::path& path() const;

    filesystem::file_time_type last_update() const override;

private:
    filesystem::path _path;
};


class rule : public dependency {
public:
    rule(const filesystem::path& goal, 
         const vector<string>& dependencies,
         const vector<string>& commands);

    const filesystem::path& goal() const;
    const vector<string>& dependencies() const;
    const vector<string>& commands() const;

    filesystem::file_time_type last_update() const override;

    void execute();

private:
    filesystem::path _goal;
    vector<string> _dependencies;
    vector<string> _commands;
};

} // namespace mike
