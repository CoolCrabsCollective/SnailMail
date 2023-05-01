//
// Created by Alexander Winter on 2023-05-01.
//

#include "ScoreSaver.h"
#include "WIZ/util/FileUtil.h"
#include <string>
#include <fstream>
#include <cstring>
#include <iostream>

ScoreSaver::ScoreSaver(std::string scoreDirectory) : scoreDirectory(scoreDirectory) {
    if(wiz::ensure_directory(scoreDirectory) != 0)
        throw std::runtime_error("Failed to create directory " + scoreDirectory + " for scores");
}

bool operator>(const Score& score1, const Score& score2) {
    if(score1.delivered > score2.delivered)
        return true;
    if(score1.delivered < score2.delivered)
        return false;

    return score1.score > score2.score;
}
bool operator>=(const Score& score1, const Score& score2) {
    return !(score2 > score1);
}

void ScoreSaver::saveScore(const Score& score) {
    if(hasScore(score.levelNumber) && loadScoreForLevel(score.levelNumber) >= score)
        return;

    std::string fileName = scoreDirectory + "level_" + std::to_string(score.levelNumber) + ".score";
    std::ofstream file;
    file.open(fileName, std::ios::out);

    if(file.fail())
        throw std::runtime_error("Failed to open file " + fileName + " for saving score");

    file.write((char*)&score.levelNumber, 4);
    file.write((char*)&score.delivered, 4);
    file.write((char*)&score.missed, 4);
    file.write((char*)&score.score, 4);
    file.flush();
    file.close();
}

bool ScoreSaver::hasScore(int levelNumber) const {
    std::string fileName = scoreDirectory + "level_" + std::to_string(levelNumber) + ".score";

    struct stat buffer;
    return (stat (fileName.c_str(), &buffer) == 0);
}

Score ScoreSaver::loadScoreForLevel(int levelNumber) const {
    std::string fileName = scoreDirectory + "level_" + std::to_string(levelNumber) + ".score";
    std::ifstream file(fileName);

    if(file.fail()) {
        std::cerr << strerror(errno) << std::endl;
        throw std::runtime_error("Failed to open file " + fileName + " for loading score: ");
    }

    Score score;

    file.read((char*)&score.levelNumber, 4);
    file.read((char*)&score.delivered, 4);
    file.read((char*)&score.missed, 4);
    file.read((char*)&score.score, 4);

    file.close();

    return score;
}
