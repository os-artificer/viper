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

#ifndef _VIPER_OPTION_FLAG_H_
#define _VIPER_OPTION_FLAG_H_

#include <string>

namespace viper::option {

template <typename T>
class Flag final
{
public:
    Flag(const std::string& name)
        : _name(name) {}

    Flag(const std::string& name, const std::string& shorthand)
        : _name(name), _shorthand(shorthand) {}

    Flag(const std::string& name, const std::string& shorthand, const std::string& usage)
        : _name(name), _shorthand(shorthand), _usage(usage) {}

    Flag(const std::string& name, const std::string& shorthand, const std::string& usage, const T& value)
        : _name(name), _shorthand(shorthand), _usage(usage), _value(value) {}

public:
    /// name as it appears on command line
    std::string _name;

    /// one-letter abbreviated flag
    std::string _shorthand;

    /// help message
    std::string _usage;

    /// value type name
    std::string _valueType;

    /// value as set
    T _value;
};

} // namespace viper::option

#endif
