#include <SFML/Graphics.hpp>
#include "StringAlgorithms.h"
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

void visualizeStringSearch(const std::string &text, const std::string &pattern, std::vector<int> (*searchAlgorithm)(const std::string&, const std::string&)) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "String Search Visualization");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    sf::Text textDisplay;
    textDisplay.setFont(font);
    textDisplay.setCharacterSize(24);
    textDisplay.setFillColor(sf::Color::White);
    textDisplay.setPosition(10, 50);

    sf::Text patternDisplay;
    patternDisplay.setFont(font);
    patternDisplay.setCharacterSize(24);
    patternDisplay.setFillColor(sf::Color::Red);

    sf::Text messageDisplay;
    messageDisplay.setFont(font);
    messageDisplay.setCharacterSize(24);
    messageDisplay.setFillColor(sf::Color::Green);
    messageDisplay.setPosition(10, 10);

    size_t textLength = text.length();
    size_t patternLength = pattern.length();

    std::vector<int> matches;

    for (size_t i = 0; i <= textLength - patternLength; ++i) {
        bool match = true;
        std::string displayString = text;

        for (size_t j = 0; j < patternLength; ++j) {
            if (text[i + j] != pattern[j]) {
                match = false;
            }
            // Highlight the current comparison characters
            displayString[i + j] = toupper(displayString[i + j]);
            textDisplay.setString(displayString);
            patternDisplay.setString(pattern);
            patternDisplay.setPosition(10 + (i * 15), 100);

            window.clear();
            window.draw(textDisplay);
            window.draw(patternDisplay);
            window.display();

            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            if (!match) break;
        }

        if (match) {
            matches.push_back(i);

            // If a match is found, highlight it
            std::string finalDisplayString;
            for (size_t k = 0; k < textLength; ++k) {
                if (k >= i && k < i + patternLength) {
                    finalDisplayString += "[" + std::string(1, text[k]) + "]";
                } else {
                    finalDisplayString += text[k];
                }
            }
            textDisplay.setString(finalDisplayString);
            window.clear();
            window.draw(textDisplay);
            window.display();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    // After searching the whole text, display the results
    std::string resultMessage;
    if (matches.empty()) {
        resultMessage = "No occurrences found.";
    } else {
        resultMessage = "Occurrences found at indexes: ";
        for (int index : matches) {
            resultMessage += std::to_string(index) + " ";
        }
    }

    messageDisplay.setString(resultMessage);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(textDisplay);
        window.draw(messageDisplay);
        window.display();
    }
}

int main() {
    std::string text = "this is a simple example, or is it ?";
    std::string pattern = "is";
    int choice;

    std::cout << "Choose the string search algorithm to visualize:\n";
    std::cout << "1. Naive String Search\n";
    std::cout << "2. KMP Search\n";
    std::cin >> choice;

    switch (choice) {
        case 1:
            visualizeStringSearch(text, pattern, StringAlgorithms::naiveStringSearch);
            break;
        case 2:
            visualizeStringSearch(text, pattern, StringAlgorithms::KMPSearch);
            break;
        default:
            std::cerr << "Invalid choice!\n";
            return 1;
    }

    return 0;
}
