/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Graphics.hpp"

Graphics::Graphics(int width, int height, const char *title, bool precharge)
    : width(width), height(height), title(title), precharge(precharge),
    window(sf::VideoMode(width, height), title), currentScene(nullptr), prepared(false)
{
    if (!window.isOpen()) {
        throw GraphicsException("Failed to create window");
    }
    EventSystem::getInstance()->triggerEvents("window_opened", nullptr);
    prepared = true;
    window.setFramerateLimit(60);
    sortedObjects.reserve(100);
}

Graphics::~Graphics() {
    close();
}

void Graphics::addAndSortObject(IObject *object) {
    float zValue = 0.0f;
    
    for (auto& component : object->getComponents()) {
        if (auto* transform = dynamic_cast<Transform *>(component)) {
            zValue = transform->getPosition().z;
            break;
        }
    }

    auto insertPos = sortedObjects.begin();
    for (; insertPos != sortedObjects.end(); ++insertPos) {
        float currentZValue = 0.0f;

        for (auto& component : (*insertPos)->getComponents()) {
            if (auto* transform = dynamic_cast<Transform *>(component)) {
                currentZValue = transform->getPosition().z;
                break;
            }
        }
        if (zValue < currentZValue) {
            break;
        }
    }

    sortedObjects.insert(insertPos, object);
}

void Graphics::clear() {
    window.clear(sf::Color::Black);
}

void Graphics::present() {
    window.display();
}

std::string Graphics::keyToString(sf::Keyboard::Key key) {
    static const std::unordered_map<sf::Keyboard::Key, std::string> keyMap = {
        {sf::Keyboard::Unknown, "unknown"},
        {sf::Keyboard::A, "a"},
        {sf::Keyboard::B, "b"},
        {sf::Keyboard::C, "c"},
        {sf::Keyboard::D, "d"},
        {sf::Keyboard::E, "e"},
        {sf::Keyboard::F, "f"},
        {sf::Keyboard::G, "g"},
        {sf::Keyboard::H, "h"},
        {sf::Keyboard::I, "i"},
        {sf::Keyboard::J, "j"},
        {sf::Keyboard::K, "k"},
        {sf::Keyboard::L, "l"},
        {sf::Keyboard::M, "m"},
        {sf::Keyboard::N, "n"},
        {sf::Keyboard::O, "o"},
        {sf::Keyboard::P, "p"},
        {sf::Keyboard::Q, "q"},
        {sf::Keyboard::R, "r"},
        {sf::Keyboard::S, "s"},
        {sf::Keyboard::T, "t"},
        {sf::Keyboard::U, "u"},
        {sf::Keyboard::V, "v"},
        {sf::Keyboard::W, "w"},
        {sf::Keyboard::X, "x"},
        {sf::Keyboard::Y, "y"},
        {sf::Keyboard::Z, "z"},
        {sf::Keyboard::Num0, "0"},
        {sf::Keyboard::Num1, "1"},
        {sf::Keyboard::Num2, "2"},
        {sf::Keyboard::Num3, "3"},
        {sf::Keyboard::Num4, "4"},
        {sf::Keyboard::Num5, "5"},
        {sf::Keyboard::Num6, "6"},
        {sf::Keyboard::Num7, "7"},
        {sf::Keyboard::Num8, "8"},
        {sf::Keyboard::Num9, "9"},
        {sf::Keyboard::Escape, "escape"},
        {sf::Keyboard::LControl, "left-control"},
        {sf::Keyboard::LShift, "left-shift"},
        {sf::Keyboard::LAlt, "left-alt"},
        {sf::Keyboard::LSystem, "left-system"},
        {sf::Keyboard::RControl, "right-control"},
        {sf::Keyboard::RShift, "right-shift"},
        {sf::Keyboard::RAlt, "right-alt"},
        {sf::Keyboard::RSystem, "right-system"},
        {sf::Keyboard::Menu, "menu"},
        {sf::Keyboard::LBracket, "left-bracket"},
        {sf::Keyboard::RBracket, "right-bracket"},
        {sf::Keyboard::SemiColon, "semicolon"},
        {sf::Keyboard::Comma, "comma"},
        {sf::Keyboard::Period, "period"},
        {sf::Keyboard::Quote, "quote"},
        {sf::Keyboard::Slash, "slash"},
        {sf::Keyboard::BackSlash, "backslash"},
        {sf::Keyboard::Tilde, "tilde"},
        {sf::Keyboard::Equal, "equal"},
        {sf::Keyboard::Dash, "dash"},
        {sf::Keyboard::Space, "space"},
        {sf::Keyboard::Return, "enter"},
        {sf::Keyboard::BackSpace, "backspace"},
        {sf::Keyboard::Tab, "tab"},
        {sf::Keyboard::PageUp, "page-up"},
        {sf::Keyboard::PageDown, "page-down"},
        {sf::Keyboard::End, "end"},
        {sf::Keyboard::Home, "home"},
        {sf::Keyboard::Insert, "insert"},
        {sf::Keyboard::Delete, "delete"},
        {sf::Keyboard::Add, "add"},
        {sf::Keyboard::Subtract, "subtract"},
        {sf::Keyboard::Multiply, "multiply"},
        {sf::Keyboard::Divide, "divide"},
        {sf::Keyboard::Left, "left-arrow"},
        {sf::Keyboard::Right, "right-arrow"},
        {sf::Keyboard::Up, "up-arrow"},
        {sf::Keyboard::Down, "down-arrow"},
        {sf::Keyboard::Numpad0, "numpad-0"},
        {sf::Keyboard::Numpad1, "numpad-1"},
        {sf::Keyboard::Numpad2, "numpad-2"},
        {sf::Keyboard::Numpad3, "numpad-3"},
        {sf::Keyboard::Numpad4, "numpad-4"},
        {sf::Keyboard::Numpad5, "numpad-5"},
        {sf::Keyboard::Numpad6, "numpad-6"},
        {sf::Keyboard::Numpad7, "numpad-7"},
        {sf::Keyboard::Numpad8, "numpad-8"},
        {sf::Keyboard::Numpad9, "numpad-9"},
        {sf::Keyboard::F1, "f1"},
        {sf::Keyboard::F2, "f2"},
        {sf::Keyboard::F3, "f3"},
        {sf::Keyboard::F4, "f4"},
        {sf::Keyboard::F5, "f5"},
        {sf::Keyboard::F6, "f6"},
        {sf::Keyboard::F7, "f7"},
        {sf::Keyboard::F8, "f8"},
        {sf::Keyboard::F9, "f9"},
        {sf::Keyboard::F10, "f10"},
        {sf::Keyboard::F11, "f11"},
        {sf::Keyboard::F12, "f12"},
        {sf::Keyboard::Pause, "pause"}
    };

    auto it = keyMap.find(key);
    if (it != keyMap.end()) {
        return it->second;
    } else {
        return "unknown-key";
    }
}

void Graphics::catchEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            close();
        } if (event.type == sf::Event::KeyPressed) {
            std::string keyName = keyToString(event.key.code);
            EventSystem::getInstance()->triggerEvents(keyName + "_pressed", nullptr);
        } if (event.type == sf::Event::KeyReleased) {
            std::string keyName = keyToString(event.key.code);
            EventSystem::getInstance()->triggerEvents(keyName + "_released", nullptr);
        }
    }
}

void Graphics::render(const std::function<void(IObject *)> &updateFunction) {
    if (!prepared) {
        return;
    }
    clear();

    const std::vector<IObject *> objects = currentScene->getObjects();
    for (auto *object : objects) {
        addAndSortObject(object);
    }
    for (auto *object : sortedObjects) {
        for (auto& component : object->getComponents()) {
            updateFunction(object);
            if (auto* graphicsComponent = dynamic_cast<IGraphicsComponent *>(component)) {
                graphicsComponent->render(&window);
            }
        }
    }

    present();
}

void Graphics::close() {
    EventSystem::getInstance()->triggerEvents("window_closed", nullptr);
    window.close();
    prepared = false;
}

void Graphics::setScene(IScene *scene) {
    currentScene = scene;
    sortedObjects.clear();
}
