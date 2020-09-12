# platform-io-libraries
Useful object-oriented libraries to be used in your Platform IO projects.

Each library is on a separate branch, so in order to use it as a dependency library in your Platform IO project, add it in your __platform.ini__ file under your environment settings.
Dependency entry format: __\<repositoryUrl>\#\<branchName>__. See example below

```
[env:uno]
platform = atmelavr
board = uno
framework = arduino
lib_deps =
    https://github.com/DanN91/platform-io-libraries#BuzzerPlayer
```
