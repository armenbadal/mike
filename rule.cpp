#include "rule.h"

namespace mike {

file::file(const filesystem::path& p)
    : _path{p}
{}


const filesystem::path& file::path() const
{
    return _path;
}


filesystem::file_time_type file::last_update() const
{
    if( !filesystem::exists(_path) )
        return {};

    return filesystem::last_write_time(_path);
}


rule::rule(const filesystem::path& goal,
           const vector<string>& dependencies,
           const vector<string>& commands)
    : _goal{goal},
      _dependencies{dependencies},
      _commands{commands}
{}


const filesystem::path& rule::goal() const
{
    return _goal;
}


const vector<string>& rule::dependencies() const
{
    return _dependencies;
}


const vector<string>& rule::commands() const
{
    return _commands;
}


filesystem::file_time_type rule::last_update() const
{
    return filesystem::last_write_time(_goal);
}


void rule::execute()
{
    const auto gwt = filesystem::exists(_goal)
        ? filesystem::last_write_time(_goal)
        : filesystem::file_time_type::clock::now() - chrono::days{1};

    bool to_run = false;
    for( const auto& d : _dependencies ) {
        //const auto dwt = d->last_update();
        //if( dwt > gwt ) {
        //    to_run = true;
        //    break;
        //}
    }

    if( !to_run )
        return;

    //system(_command.c_str());
}

} // namespace mike
