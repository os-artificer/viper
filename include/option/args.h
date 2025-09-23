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

#ifndef _VIPER_OPTION_ARG_H_
#define _VIPER_OPTION_ARG_H_

#include "value.h"

#include <map>
#include <memory>
#include <string>

namespace viper::option {

class Args final
{
public:
    Args() = default;
    /**
     * @brief key: arg name value: the value of the name
     */
    Args(const std::map<std::string, std::shared_ptr<Value>>& vars);

public:
    void Set(const std::string& name, std::shared_ptr<Value> val);
    void Set(const std::string& name, const Value& val);
    void Set(const std::string& name, int val);
    void Set(const std::string& name, float val);
    void Set(const std::string& name, double val);
    void Set(const std::string& name, bool val);
    void Set(const std::string& name, const std::string& val);
    bool Exist(const std::string& name);
    int  Count() const;

    std::shared_ptr<Value> Get(const std::string& name) const;

private:
    std::map<std::string, std::shared_ptr<Value>> _vars;
};

} // namespace viper::option

#endif
