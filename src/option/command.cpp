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

namespace viper::option {

Command::~Command()
{
    _subCmds.clear();
    _flagBools.clear();
    _flagDoubles.clear();
    _flagInts.clear();
    _flagStrs.clear();
}

template <>
void Command::AddFlag<int>(std::shared_ptr<Flag<int>> flag)
{
    flag->_valueType = "int";
    _flagInts.push_back(flag);
}
template <>
void Command::AddFlag<bool>(std::shared_ptr<Flag<bool>> flag)
{
    flag->_valueType = "bool";
    _flagBools.push_back(flag);
}

template <>
void Command::AddFlag<double>(std::shared_ptr<Flag<double>> flag)
{
    flag->_valueType = "double";
    _flagDoubles.push_back(flag);
}

template <>
void Command::AddFlag<std::string>(std::shared_ptr<Flag<std::string>> flag)
{
    flag->_valueType = "string";
    _flagStrs.push_back(flag);
}

void Command::AddCommand(std::shared_ptr<Command> cmd)
{
    cmd->_parent = shared_from_this();
    _subCmds.push_back(cmd);
}

void Command::Usage()
{
    // Print the short description.
    if (!_short.empty())
    {
        printf("%s\n", _short.c_str());
    }

    // Print the usage message.
    printf("\nUsage:\n");
    printf("  %-2s [flags]\n", _use.c_str());
    printf("  %-2s [command]\n", _use.c_str());

    // Print the long description.
    if (!_long.empty())
    {
        printf("\n%s\n", _long.c_str());
    }

    // Print the subcommands.
    printf("\nCommands:\n");
    for (const auto& cmd : _subCmds)
    {
        printf("  %s\t%s\n", cmd->_use.c_str(), cmd->_short.c_str());
    }

    // Print the flags.
    printf("\nFlags:\n");
    for (const auto& flag : _flagInts)
    {
        printf("  -%s, --%-8s %8s  %8s (default: %d)\n", flag->_shorthand.c_str(), flag->_name.c_str(),
               flag->_valueType.c_str(), flag->_usage.c_str(), flag->_value);
    }

    for (const auto& flag : _flagBools)
    {
        printf("  -%s, --%-8s %8s  %8s (default: %s)\n", flag->_shorthand.c_str(), flag->_name.c_str(),
               flag->_valueType.c_str(), flag->_usage.c_str(), flag->_value ? "true" : "false");
    }

    for (const auto& flag : _flagDoubles)
    {
        printf("  -%s, --%-8s %8s  %8s (default: %g)\n", flag->_shorthand.c_str(), flag->_name.c_str(),
               flag->_valueType.c_str(), flag->_usage.c_str(), flag->_value);
    }

    for (const auto& flag : _flagStrs)
    {
        printf("  -%s, --%-8s %8s  %8s (default: %s)\n", flag->_shorthand.c_str(), flag->_name.c_str(),
               flag->_valueType.c_str(), flag->_usage.c_str(), flag->_value.c_str());
    }
}

void Command::Help()
{
    Usage();
    printf("\nUse \"%s [command] --help\" for more information about a given command.\n",
           _use.c_str());
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
        // TODO:
        printf("arg: %s \n", args[i].data());
        continue;
    }

    // If there are subcommands, find the subcommand to execute.
    if (!_subCmds.empty())
    {
        std::string subCmdName = argv[0];
        for (const auto& cmd : _subCmds)
        {
            if (cmd->_use == subCmdName)
            {
                return cmd->Execute(argc - 1, argv + 1);
            }
        }

        Usage();
        return -1;
    }

    // If there is no subcommand, run the command.
    if (_run)
    {
        return _run(argc, argv);
    }

    // If there is no run method, print the usage.
    Usage();

    return -1;
}

} // namespace viper::option
