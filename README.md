# Dotenv for C++

 <img src="https://user-images.githubusercontent.com/87577447/223471093-0c3dedd0-780d-40d2-a507-1e07df441909.png" alt="dotenv" align="right" width="200" />

<div align="center">

A lightweight C++ library for loading and parsing environment variables from a `.env` file with JavaScript-like variable expansion.

[![Build status](https://ci.appveyor.com/api/projects/status/0yh7hmtp0xu98b31?svg=true)](https://ci.appveyor.com/project/harshfeudal/dotenv)
[![Release](https://img.shields.io/github/v/release/harshfeudal/dotenv?color=brightgreen)](https://github.com/harshfeudal/dotenv/releases/latest)
[![GitHub issues](https://img.shields.io/github/issues/harshfeudal/dotenv)](https://github.com/harshfeudal/dotenv/issues)
[![GitHub license](https://img.shields.io/github/license/harshfeudal/dotenv?color=brightgreen)](https://github.com/harshfeudal/dotenv/blob/master/MIT_LICENSE.md)
<br />
[![GitHub stars](https://img.shields.io/github/stars/harshfeudal/dotenv?color=ff69b4)](https://github.com/harshfeudal/dotenv/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/harshfeudal/dotenv?color=ff69b4)](https://github.com/harshfeudal/dotenv/network)

</div>

### 📝 About this repository
- This project is owned by [@harshfeudal](https://github.com/harshfeudal).
- A header-only C++ library perfect for managing configuration variables, such as tokens for a Discord bot using [D++](https://dpp.dev/). Use with `.gitignore` to keep your `.env` file secure.

### 🚨 Usage
1. Download the `dotenv` folder containing `dotenv.h`.
2. Include and use it in your project like this:

`main.cpp`
```cpp
#include <dotenv/dotenv.h>
#include <iostream>

int main() {
    Dotenv env;
    
    // Load your .env file
    if (!env.load(".env")) {
        std::cerr << "Failed to load .env file" << std::endl;
        return 1;
    }

    // Read your .env variable
    std::string my_var = env.get("MY_VAR");
    std::cout << "The variable is: " << my_var << std::endl;

    // Get with default value
    std::string missing_var = env.get("MISSING", "default value");
    std::cout << "Missing variable: " << missing_var << std::endl;

    return 0;
}
```

**Note:** If you would like to use the non-OOP version, please include only `dotenv-alt.h`. It provides a set of functions instead of a class-based interface. This can be useful for simpler use cases or when you prefer a procedural approach.

### ✨ Library features
1. **Formatted Strings:** Supports escape sequences in double-quoted values:

```env
SENTENCE="\n\"Hello World\"\n\t- Hello 2025 -"
```

Outputs:

```console
The sentence is:
"Hello World"
    - Hello 2025 -
```

2. **Comments:** Ignores content after `#` when not in quotes:

```env
TOKEN="WW91ckRpc2NvcmRCb3RUb2tlbg=="    # Your Discord bot token
```

3. **Header-Only:** Just include `dotenv.h` - no additional linking required!

4. **Variable Expansion:** JavaScript-like variable substitution:
- `$KEY` or `${KEY}` expands to the value of KEY
- `\$KEY` escapes the expansion
- `${KEY:-default}` uses "default" if KEY is unset

Example:

```env
HOST=localhost
URL=$HOST:8080
SAFE=\$HOST
FALLBACK=${UNSET:-default}
```

5. **Quote Support:** Supports single (`'`), double (`"`), and backtick (`` ` ``) quotes. Only double-quoted values process escapes.

6. **Empty Values:** Handles empty variables:

### 👷 Support Platform
- Microsoft Windows 10/11 `x64/x86`
- Visual Studio platform `x64/x86`
- C++17 ISO/IEC `14882`

### 💎 Contribution and Pull Request
Contributions are welcome! Please:

- Test your changes thoroughly
- Submit a pull request

Don't worry about mistakes - we'll work together to refine it

### 📚 Download
Get the latest version [here](https://github.com/harshfeudal/dotenv/releases/latest).

### 🤝 Support me
Please leave a star if you like it. Thank you!