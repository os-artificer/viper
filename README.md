# Viper
A cool toolkit for C++ programmers.

# Develop Environment
- gcc-14.2.0(c++17)
- cmake-3.30.3
# Supported OS
- Linux

# Features
- CLI flag kits.

# Building
``` shell
git clone https://github.com/os-artificer/viper.git
cd viper
mkdir build
cmake ..
cmake --build .
cmake --build . --target install
```

# Example
## Flags Usage
[Detailed usage examples of the flag.](./example/main.cpp)

``` shell
# Show the help information for the example.
./bin/example -h
example cli tool

Usage:
    example [flags] | [command]

Commands:
    help	Help about any command
    test	example test
    version	show version information

Flags:
  -c, --config    string config file (default: config.yaml)
  -p, --port         int listen port (default: 8080)


# Show the help information for the test command. 
./bin/example test --help
example test

Usage:
    test [flags]

Flags:
  -c, --config    string test config file (default: test-cfg.yaml)

# Another way to show the help information for the test command. 
./bin/example help test
example test

Usage:
    test [flags]

Flags:
  -c, --config    string test config file (default: test-cfg.yaml)

# Execute the test command with the new config value.
./bin/example test -c test-config.json

 Hello World, Example Test, argc:1 !
 Test Cfg File: test-config.json
```
