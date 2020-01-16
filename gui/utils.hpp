#pragma once

std::string vec2str(const std::vector <std::string> &vec) {
    std::string str;
    for (auto item : vec) {
        str += item + "\n";
    }
    return str;
}