#include "app.h"

App::App() {
    loadData();
}

App::~App() {
    saveData();
}

void App::loadData() {
    json jsonData;
    std::ifstream file("data/keys.json");
    if (file.is_open()) {
        file >> jsonData;
        file.close();
    } else throw std::runtime_error("Can't open keys.json");

    for (const auto& [key, value] : jsonData.items()) if (key.size() == 1) pressedKeys[key[0]] = value.get<unsigned int>();
}

void App::saveData() {
    json data;
    for (const auto& [key, value] : pressedKeys) data[std::string(1, key)] = value;

    std::ofstream file("data/keys.json");
    if (file.is_open()) {
        file << data.dump(2);
        if (file.fail()) throw std::runtime_error("Can't write data in keys.json");
    } else throw std::runtime_error("Can't open keys.json");
    file.close();
}

void App::run() {
    std::unordered_map<char, bool> lastKeyState;
    auto start = std::chrono::system_clock::now();

    while (true) {
        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
        if (elapsed >= 300) {
            saveData();
            start = now;
        }

        for (int i = 65; i < 91; i++) {
            if (GetAsyncKeyState(i) & 0x8000) {
                if (!lastKeyState[i]) keyPressed(i);
                lastKeyState[i] = true;
            } else lastKeyState[i] = false;
        }
        Sleep(16);
    }
}

void App::keyPressed(char key) {
    std::cout << key << std::endl;
    if (pressedKeys.find(key) != pressedKeys.end()) pressedKeys[key]++;
    else pressedKeys[key] = 1;
}
