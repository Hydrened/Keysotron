#ifndef APP_H
#define APP_H

#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <Windows.h>
using json = nlohmann::json;

class App {
private:
    unsigned int delay;
    std::unordered_map<int, int> pressedKeys;

    void loadData();
    void saveData();

    void decodeArgs(int argc, char** argv);

    void keyPressed(char key);
    std::string keyToString(int vkCode);
    
public:
    App(int argc, char** argv);
    ~App();

    void run();
};

#endif
