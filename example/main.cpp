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

#include "viper_option.h"

#include <cstdio>
#include <memory>

int main(int argc, char* argv[])
{
    auto cfgFlag  = std::make_shared<viper::option::Flag<viper::option::Value>>("config", "c", "config file", "config.yaml");
    auto portFlag = std::make_shared<viper::option::Flag<viper::option::Value>>("port", "p", "listen port", 8080);

    auto rootCmd = std::make_shared<viper::option::Command>();

    rootCmd->_use   = "example";
    rootCmd->_short = "example cli tool";

    rootCmd->AddFlag(cfgFlag);
    rootCmd->AddFlag(portFlag);

    rootCmd->_run = [&](const viper::option::Args& args) -> int {
        printf("\nHello Root,  argc:%d !\n", args.Count());
        std::cout << "flag-config: " << cfgFlag->_value << std::endl;
        std::cout << "flag-port: " << portFlag->_value.GetValue<int>() << std::endl;

        std::cout << "arg-config: " << args.Get("config") << std::endl;
        std::cout << "arg-port: " << args.Get("port") << std::endl;
        std::cout << "undefined: " << args.Get("undefined") << std::endl;

        return 0;
    };

    auto versionCmd = std::make_shared<viper::option::Command>();

    versionCmd->_use   = "version";
    versionCmd->_short = "show version information";
    versionCmd->_run   = [](const viper::option::Args& args) -> int {
        printf("\n Hello World, Test Version, argc:%d !\n", args.Count());
        return 0;
    };

    rootCmd->AddCommand(versionCmd);

    auto testCmd = std::make_shared<viper::option::Command>();

    auto testCfgFlag = std::make_shared<viper::option::Flag<viper::option::Value>>("config", "c", "test config file", "test-cfg.yaml");

    testCmd->_use   = "test";
    testCmd->_short = "example test";
    testCmd->AddFlag(testCfgFlag);

    testCmd->_run = [](const viper::option::Args& args) -> int {
        printf("\n Hello World, Example Test, argc:%d !\n", args.Count());
        std::cout << " Test Cfg File: " << args.Get("config") << std::endl;
        return 0;
    };

    rootCmd->AddCommand(testCmd);

    return rootCmd->Execute(argc, argv);
}
