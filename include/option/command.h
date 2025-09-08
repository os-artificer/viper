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

#ifndef _VIPER_OPTION_COMMAND_H_
#define _VIPER_OPTION_COMMAND_H_

#include "option/flag.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace viper::option {

using RunFunc = std::function<int(int argc, char* argv[])>;

class Command final : public std::enable_shared_from_this<Command>
{
public:
    /// Constructor
    Command() = default;

    /// Deconstructor.
    ~Command();

    /// Add a flag for this command.
    template <typename T>
    void AddFlag(std::shared_ptr<Flag<T>> flag) {};

    /// Add a child command for this command.
    void AddCommand(std::shared_ptr<Command> cmd);

    /// Print the usage for a command.
    void Usage();

    /// Print the help message for a command.
    void Help();

    /// Execute the command.
    int Execute(int argc, char* argv[]);

public:
    /// Use is the one-line usage message.
    std::string _use;

    /// Short is the short description shown in the 'help' output.
    std::string _short;

    /// Long is the long message shown in the 'help <this-command>' output.
    std::string _long;

    /// Typically the actual work function. Most commands will only implement this.
    RunFunc _run = nullptr;

private:
    /// Flags are the flags of this command.
    std::vector<std::shared_ptr<Flag<int>>>         _flagInts;
    std::vector<std::shared_ptr<Flag<bool>>>        _flagBools;
    std::vector<std::shared_ptr<Flag<double>>>      _flagDoubles;
    std::vector<std::shared_ptr<Flag<std::string>>> _flagStrs;

    /// Parent is the parent of this command.
    std::shared_ptr<Command> _parent = nullptr;

    /// SubCmds is the child commands of this command.
    std::vector<std::shared_ptr<Command>> _subCmds;
};

} // namespace viper::option

#endif
