#pragma once
#include <string>

class Movie {
private:
    std::string title;
    std::string language;
    int durationMin;

public:
    Movie(std::string title, std::string language, int durationMin) {
        this->title = title;
        this->language = language;
        this->durationMin = durationMin;
    }

    std::string getTitle() const { return title; }
    std::string getLanguage() const { return language; }
    int getDuration() const { return durationMin; }
};
