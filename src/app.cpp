#include "app.h"

App::App(int argc, char** argv) {
    decodeArgs(argc, argv);
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
    for (const auto& [key, value] : pressedKeys) {
        std::string strKey = keyToString(key);
        if (strKey != "UNKNOWN") data[strKey] = value;
    }

    std::ofstream file("data/keys.json");
    if (file.is_open()) {
        file << data.dump(2);
        if (file.fail()) throw std::runtime_error("Can't write data in keys.json");
    } else throw std::runtime_error("Can't open keys.json");
    file.close();
}

void App::decodeArgs(int argc, char** argv) {
    if (argc > 1) for (int i = 0; i < argc - 1; i++) {
        std::string arg = argv[i];
        std::string nextArg = argv[i + 1];
        if (arg != "-d") continue;

        try {
            delay = std::stoi(nextArg);
        } catch (const std::invalid_argument&) {
            throw std::runtime_error("Arg is not an integer");
        } catch (const std::out_of_range&) {
            throw std::runtime_error("Value is out of range");
        }
    } else delay = 60;
}

void App::run() {
    std::unordered_map<char, bool> lastKeyState;
    auto start = std::chrono::system_clock::now();

    while (true) {
        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
        if (elapsed >= delay) {
            saveData();
            start = now;
        }

        for (int vkCode = 0; vkCode <= 255; vkCode++) {
            if (GetAsyncKeyState(vkCode) & 0x8000) {
                if (!lastKeyState[vkCode]) keyPressed(vkCode);
                lastKeyState[vkCode] = true;
            } else lastKeyState[vkCode] = false;
        }
        Sleep(16);
    }
}

void App::keyPressed(char key) {
    if (pressedKeys.find(key) != pressedKeys.end()) pressedKeys[key]++;
    else pressedKeys[key] = 1;
}

std::string App::keyToString(int vkCode) {
    if (vkCode >= 'A' && vkCode <= 'Z') return std::string(1, static_cast<char>(vkCode));
    if (vkCode >= '0' && vkCode <= '9') return std::string(1, static_cast<char>(vkCode));
    switch (vkCode) {
        case VK_SPACE: return "SPACE";
        case VK_RETURN: return "ENTER";
        case VK_BACK: return "BACKSPACE";
        case VK_TAB: return "TAB";
        case VK_SHIFT: return "SHIFT";
        case VK_CONTROL: return "CTRL";
        case VK_MENU: return "ALT";
        case VK_ESCAPE: return "ESCAPE";
        case VK_LEFT: return "LEFT_ARROW";
        case VK_RIGHT: return "RIGHT_ARROW";
        case VK_UP: return "UP_ARROW";
        case VK_DOWN: return "DOWN_ARROW";
        case VK_NUMPAD0: return "NUMPAD_0";
        case VK_NUMPAD1: return "NUMPAD_1";
        case VK_NUMPAD2: return "NUMPAD_2";
        case VK_NUMPAD3: return "NUMPAD_3";
        case VK_NUMPAD4: return "NUMPAD_4";
        case VK_NUMPAD5: return "NUMPAD_5";
        case VK_NUMPAD6: return "NUMPAD_6";
        case VK_NUMPAD7: return "NUMPAD_7";
        case VK_NUMPAD8: return "NUMPAD_8";
        case VK_NUMPAD9: return "NUMPAD_9";
        default: return "UNKNOWN";
    }
}
