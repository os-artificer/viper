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

#ifndef _VIPER_TEXT_STRINGS_H_
#define _VIPER_TEXT_STRINGS_H_

#include <string>
#include <string_view>
#include <vector>

namespace viper::text {

bool                     StartWith(std::string_view sv, std::string_view prefix);
bool                     Contains(std::string_view sv, std::string_view substr);
std::vector<std::string> Split(std::string_view sv, char delimiter);
std::vector<std::string> Split(std::string_view str, std::string_view delimiter);
std::string              ToLower(const std::string& str);

/**
 * @brief Convert the string to a boolean value with the following rules.
 * @param str "true" = > true
 *                1  =>  true
 *           "false" =>  false
 *                0  =>  false
 * @throw std::invalid_argument
 */
bool ToBool(const std::string& str);

} // namespace viper::text

#endif
