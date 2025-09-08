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
#include "option/flag.h"

#include <cstdio>
#include <memory>

int main(int argc, char* argv[])
{
    auto rootCmd = std::make_shared<viper::option::Command>();

    rootCmd->_use   = "example";
    rootCmd->_short = "example cli tool";

    rootCmd->AddFlag(std::make_shared<viper::option::Flag<std::string>>("config", "c", "config file", "config.yaml"));
    rootCmd->AddFlag(std::make_shared<viper::option::Flag<int>>("port", "p", "listen port", 8080));

    auto versionCmd = std::make_shared<viper::option::Command>();

    versionCmd->_use   = "version";
    versionCmd->_short = "show version information";
    versionCmd->_run   = [](int argc, char* argv[]) -> int {
        printf("\n Hello World, Test Version!\n");
        return 0;
    };

    rootCmd->AddCommand(versionCmd);

    return rootCmd->Execute(argc, argv);
}