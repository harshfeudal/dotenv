# Dotenv for C++

 <img src="https://user-images.githubusercontent.com/87577447/223471093-0c3dedd0-780d-40d2-a507-1e07df441909.png" alt="dotenv" align="right" width="200" />

<div align="center">

This library support loading environment variables from a `.env` file and reading them like what `.json` does but more simply!

[![Build status](https://ci.appveyor.com/api/projects/status/0yh7hmtp0xu98b31?svg=true)](https://ci.appveyor.com/project/harshfeudal/dotenv)
[![Release](https://img.shields.io/github/v/release/harshfeudal/dotenv?color=brightgreen)](https://github.com/harshfeudal/dotenv/releases/latest)
[![GitHub issues](https://img.shields.io/github/issues/harshfeudal/dotenv)](https://github.com/harshfeudal/dotenv/issues)
[![GitHub license](https://img.shields.io/github/license/harshfeudal/dotenv?color=brightgreen)](https://github.com/harshfeudal/dotenv/blob/master/MIT_LICENSE.md)
<br />
[![GitHub stars](https://img.shields.io/github/stars/harshfeudal/dotenv?color=ff69b4)](https://github.com/harshfeudal/dotenv/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/harshfeudal/dotenv?color=ff69b4)](https://github.com/harshfeudal/dotenv/network)

</div>

### 📝 About this repository
- This project is owned by [@harshfeudal](https://github.com/harshfeudal). You can join my Discord server [here](https://discord.gg/BAk2CXpRAT)!
- This library can be used for many different projects, currently, this library is enough to make a C++ Discord bot using [D++](https://dpp.dev/) for a safety token reader (you can use `.gitignore` to ignore `.env` file).

### 🚨 Usage
1. Download ONLY `dotenv` folder (make sure that it contains `dotenv.h` inside). Simple right?
2. Include it in your project like this:

`main.cpp`
```cpp
#include <dotenv/dotenv.h>
#include <iostream>

int main() {
    // Load your .env file
	dotenv::load(".env");

    // Read your .env variable
    char* my_var;
    size_t envValueSize;
    _dupenv_s(&my_var, &envValueSize, "MY_VAR");

    // Read it
    std::cout << "The variable is: " << my_var << std::endl;

    // Remember to free it
    free(my_var);
}
```

* Some notice update: You can also use `std::getenv("YOUR_ENV_VAR")`.
However, some compiler like MSVC doesn't allow you to use that, and they recommend you to replace as `_dupenv_s`.
You can also use other methods if you find a new one! If you are not using MSVC, you can do like below (recommend):

```cpp
#include <dotenv/dotenv.h>
#include <iostream>
int main() {
    // Load your .env file
	dotenv::load(".env");

    // Read your .env variable
    const char* my_var = std::getenv("MY_VAR");

    // Read it
    std::cout << "The variable is: " << my_var << std::endl;
}
```

... and compare it to your `.env` file:

`.env`

```env
MY_VAR="Hello World!"
```

Done! Simple right (I think)?

### ✨ Library features
1. Somehow you really want to skip a line (or do whatever you want) like this:
```console
The sentence is:
"Hello World"
    - Hello 2023 -
```

... so, with this library feature, to do this, you can just do this in your `.env` file:
```env
SENTENCE="\n\"Hello World\"\n\t- Hello 2023 -"
```

and it will work as expected!

2. Or, you really want to make a comment like this:
```env
TOKEN="WW91ckRpc2NvcmRCb3RUb2tlbg=="    # Your Discord bot token
```

With this library feature, your comment will be ignored after the `#` mark! Comments begin where a `#` exists, so if your value contains a `#` please wrap it in quotes.

3. This library just includes __only a header file (`dotenv.h`)__!

4. Very similar to what Javascript does; The expansion engine roughly has the following rules:

    - `$KEY` will expand any env with the name `KEY`
    - `${KEY}` will expand any env with the name `KEY`
    - `\$KEY` will escape the `$KEY` rather than expand
    - `${KEY:-default}` will first attempt to expand any env with the name `KEY`. If not one, then it will return default

5. If you decide to make an empty variable like this:
```env
EMPTY=
```

... so remember to have a space like this:
```env
EMPTY= # A space after the '=' symbol
```

### 👷 Support platform
 - Microsoft Windows 10 `x64/x86`
 - Visual Studio platform `x64/x86`
 - C++ 17 `ISO/IEC 14882`

### 🤝 Support me
 - Please leave me a star if you like it. Thank you very much!
 - You can probably help me develop this project too by DMing me on my [Discord profile](https://discord.com/users/622450109317251088).

### 💎 Contribution and Pull Request
  I'd probably be glad to see if you have anything new to help and support me. To do that, please make one and before you do that, just make sure you've tested the code. I won't bite you if you do it wrong, but just make sure that you have to test it clearly before I merge it.

### 📚 Download
You can download the latest version [here](https://github.com/harshfeudal/dotenv/releases/latest).

<div align="center">
    <span>
            - © 2023 Harshfeudal. All rights reserved. -
    </span>
</div>
