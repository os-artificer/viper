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

#ifndef _VIPER_OPTION_VALUE_H_
#define _VIPER_OPTION_VALUE_H_

#include <iostream>
#include <string>
#include <variant>

namespace viper::option {

class Value final
{
public:
    Value(int val);
    Value(float val);
    Value(double val);
    Value(bool val);
    Value(const char* val);
    Value(const std::string& val);

    Value()             = default;
    Value(const Value&) = default;
    Value(Value&&)      = default;
    virtual ~Value()    = default;

public:
    Value& operator=(int val);
    Value& operator=(float val);
    Value& operator=(double val);
    Value& operator=(bool val);
    Value& operator=(const char* val);
    Value& operator=(const std::string& val);

    Value& operator=(const Value&) = default;
    Value& operator=(Value&&)      = default;

public:
    bool        IsInt() const;
    bool        IsFloat() const;
    bool        IsDouble() const;
    bool        IsBool() const;
    bool        IsString() const;
    std::string TypeName() const;

    operator int() const;
    operator float() const;
    operator double() const;
    operator bool() const;
    operator std::string() const;
    operator const char*() const;

public:
    template <typename T>
    T GetValue() const
    {
        return std::get<T>(_value);
    };

public:
    friend std::ostream& operator<<(std::ostream& os, const Value& val);
    friend std::ostream& operator<<(std::ostream& os, Value* val);

private:
    std::variant<int, float, double, bool, std::string> _value;
};
} // namespace viper::option
#endif
