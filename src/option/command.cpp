/**
 * Copyright 2025 viper authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/

#include "option/command.h"
#include "libs/strings/strings.h"

#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string_view>

namespace viper::option {

Command::~Command()
{
    _subCmds.clear();
    _flagBools.clear();
    _flagDoubles.clear();
    _flagInts.clear();
    _flagStrs.clear();
}

template <typename T>
static void PrintFlags(const std::vector<std::shared_ptr<Flag<T>>>& flags)
{
    for (const auto& flag : flags)
    {
        std::cout << "  -" << flag->_shorthand
                  << ", --" << std::left << std::setw(8) << flag->_name
                  << std::right << std::setw(8) << flag->_valueType << " "
                  << std::setw(8) << flag->_usage
                  << " (default: " << flag->_value << ")"
                  << std::endl;
    }
}

template <>
void PrintFlags(const std::vector<std::shared_ptr<Flag<bool>>>& flags)
{
    for (const auto& flag : flags)
    {
        std::cout << "  -" << flag->_shorthand
                  << ", --" << std::left << std::setw(8) << flag->_name
                  << std::right << std::setw(8) << flag->_valueType << " "
                  << std::setw(8) << flag->_usage
                  << " (default: " << (flag->_value ? "true" : "false") << ")"
                  << std::endl;
    }
}

static void PrintCommands(const std::map<std::string, std::shared_ptr<Command>>& cmds)
{
    for (const auto& cmd : cmds)
    {
        std::cout << std::left
                  << std::setw(4)
                  << " "
                  << cmd.second->_use
                  << "\t"
                  << cmd.second->_short
                  << std::endl;
    }
}

template <>
void Command::AddFlag<int>(std::shared_ptr<Flag<int>> flag)
{
    _flagMaxWith = std::max(_flagMaxWith, static_cast<int>(flag->_name.length()));

    flag->_valueType = "int";
    _flagInts.push_back(flag);
}
template <>
void Command::AddFlag<bool>(std::shared_ptr<Flag<bool>> flag)
{
    _flagMaxWith = std::max(_flagMaxWith, static_cast<int>(flag->_name.length()));

    flag->_valueType = "bool";
    _flagBools.push_back(flag);
}

template <>
void Command::AddFlag<double>(std::shared_ptr<Flag<double>> flag)
{
    _flagMaxWith = std::max(_flagMaxWith, static_cast<int>(flag->_name.length()));

    flag->_valueType = "double";
    _flagDoubles.push_back(flag);
}

template <>
void Command::AddFlag<std::string>(std::shared_ptr<Flag<std::string>> flag)
{
    _flagMaxWith = std::max(_flagMaxWith, static_cast<int>(flag->_name.length()));

    flag->_valueType = "string";
    _flagStrs.push_back(flag);
}

void Command::AddCommand(std::shared_ptr<Command> cmd)
{
    _commandMaxWith = std::max(_commandMaxWith, static_cast<int>(cmd->_use.length()));

    cmd->_parent        = shared_from_this();
    _subCmds[cmd->_use] = cmd;
}

void Command::Usage()
{
    // Print the short description.
    if (!_short.empty())
    {
        std::cout << _short << std::endl;
    }

    // Print the usage message.
    if (_subCmds.empty() && HasFlags())
    {
        return;
    }

    std::cout << "Usage:" << std::endl;
    std::cout << std::left
              << std::setw(4)
              << " "
              << _use;

    if (HasFlags() && !_subCmds.empty())
    {
        std::cout << " [flags] | [command]";
    }
    else if (_subCmds.empty())
    {
        std::cout << " [flags]";
    }
    else
    {
        std::cout << " [command]";
    }

    std::cout << std::endl;

    // Print the long description.
    if (!_long.empty())
    {
        std::cout << _long << std::endl;
    }

    // Print the subcommands.
    if (!_subCmds.empty())
    {
        std::cout << "Commands:" << std::endl;
        PrintCommands(_subCmds);
    }

    if (HasFlags())
    {
        std::cout << "Flags:" << std::endl;
        PrintFlags(_flagInts);
        PrintFlags(_flagBools);
        PrintFlags(_flagDoubles);
        PrintFlags(_flagStrs);
    }
}

void Command::Help()
{
    Usage();

    if (!_subCmds.empty())
    {
        std::cout << std::endl
                  << "Use \""
                  << _use
                  << " [command] --help\" for more information about a given command."
                  << std::endl;
    }
}

int Command::Execute(int argc, char* argv[])
{
    if (argc < 1)
    {
        Usage();
        return -1;
    }

    std::vector<std::string_view> args(argv, argv + argc);
    for (size_t i = 1; i < args.size(); ++i)
    {
        // --option(long option)
        if (libs::strings::StartWith(args[i], "--"))
        {
            std::string_view flag = args[i];
            std::string_view value;

            if (flag == "--help")
            {
                Help();
                return 0;
            }

            if (libs::strings::Contains(flag, "="))
            {
                auto parts = libs::strings::Split(flag, "=");
                flag       = parts[0];
                value      = parts[1];

                std::cout << "flags: " << flag << " value: " << value << std::endl;
                continue;
            }

            if (i + 1 < args.size() && !libs::strings::StartWith(args[i + 1], "-"))
            {
                value = args[++i];
            }

            std::cout << "flags: " << flag << " value: " << value << std::endl;
            continue;
        }

        // -o (short option)
        if (libs::strings::StartWith(args[i], "-"))
        {
            std::string_view flag = args[i];
            std::string_view value;

            if (flag == "-h")
            {
                Help();
                return 0;
            }

            if (libs::strings::Contains(flag, "="))
            {
                auto parts = libs::strings::Split(flag, "=");
                flag       = parts[0];
                value      = parts[1];

                std::cout << "flags: " << flag << " value: " << value << std::endl;
                continue;
            }

            if (i + 1 < args.size() && !libs::strings::StartWith(args[i + 1], "-"))
            {
                value = args[++i];
            }

            continue;
        }

        // subcommand
        std::string_view cmdName = args[i];

        if (cmdName == "help")
        {
            std::string_view value;
            if (i + 1 < args.size())
            {
                value = args[++i];
            }

            auto it = _subCmds.find(std::string(value));
            if (it == _subCmds.end())
            {
                std::cerr << "Unknown command: " << value << std::endl;
                return -1;
            }

            it->second->Help();
            return 0;
        }

        auto it = _subCmds.find(std::string(cmdName));
        if (it != _subCmds.end())
        {
            auto cmd = it->second;
            return cmd->Execute(static_cast<int>(args.size() - i), argv + i);
        }

        std::cerr << "Unknown command: " << cmdName << std::endl;
        Usage();
        return -1;
    }

    // If there is no subcommand, run the command.
    if (_run)
    {
        return _run(argc, argv);
    }

    Usage();
    return 0;
}

void Command::Help(std::string_view cmdName)
{
    auto it = _subCmds.find(std::string(cmdName));
    if (it != _subCmds.end())
    {
        auto cmd = it->second;
        cmd->Usage();
        return;
    }

    std::cerr << "Unknown command: " << cmdName << std::endl;
    Usage();
}

bool Command::HasFlags()
{
    return (!_flagBools.empty() || !_flagStrs.empty() || _flagDoubles.empty() || _flagInts.empty());
}

} // namespace viper::option
