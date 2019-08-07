
# cliotp
## A simple, experimental console OTP client based on libcotp.

======

### Dependencies:
- [libcotp](https://github.com/paolostivanin/libcotp)
- [libjsoncpp](https://github.com/open-source-parsers/jsoncpp/)

### Compiling:
#### Linux
```
gcc main.cpp -lstdc++ /usr/lib64/libjsoncpp.so /usr/lib64/libcotp.so -std=c++17 -o cliotp
```
#### Windows
```
gcc main.cpp -lstdc++ -std=c++17 -o cliotp.exe
```
