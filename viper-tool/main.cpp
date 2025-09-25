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

#include <functional>
#include <iostream>

#ifndef VERSION
#define VERSION "unknown"
#endif

#ifndef GIT_COMMIT_ID
#define GIT_COMMIT_ID ""
#endif

static int VersionCmd(const viper::option::Args& args)
{
    std::cout << "Version: " << VERSION << "\n"
              << "CommitID: " << GIT_COMMIT_ID << "\n"
              << std::endl;

    return 0;
}

int main(int argc, char* argv[])
{
    auto rootCmd    = std::make_shared<viper::option::Command>();
    rootCmd->_use   = "viper-tool";
    rootCmd->_short = "Viper Tool";

    auto versionCmd    = std::make_shared<viper::option::Command>();
    versionCmd->_use   = "version";
    versionCmd->_short = "show viper lib version information";
    versionCmd->_run   = std::bind(VersionCmd, std::placeholders::_1);

    rootCmd->AddCommand(versionCmd);

    return rootCmd->Execute(argc, argv);
}
