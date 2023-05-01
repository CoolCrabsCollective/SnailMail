//
// Created by Alexander Winter on 2023-05-01.
//

#ifndef LD53_CLIENT_SCORESAVER_H
#define LD53_CLIENT_SCORESAVER_H

#include <vector>
#include <string>

struct Score {
    int levelNumber;
    int delivered;
    int missed;
    float score;
};

bool operator>(const Score& score1, const Score& score2);
bool operator>=(const Score& score1, const Score& score2);

class ScoreSaver {
    std::string scoreDirectory;
public:
    ScoreSaver(std::string scoreDirectory);

    void saveScore(const Score& score);

    bool hasScore(int levelNumber) const;

    Score loadScoreForLevel(int levelNumber) const;

    std::vector<Score> loadAllScores() const;
};


#endif //LD53_CLIENT_SCORESAVER_H
