#ifndef APP_H
#define APP_H

#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <Windows.h>
using json = nlohmann::json;

class App {
private:
    std::unordered_map<char, unsigned int> pressedKeys;

    void loadData();
    void saveData();
    void keyPressed(char key);

public:
    App();
    ~App();

    void run();
};

#endif
