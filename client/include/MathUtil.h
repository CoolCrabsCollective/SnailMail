//
// Created by Alexander Winter on 2023-01-07.
//

#ifndef LD52_CLIENT_MATHUTIL_H
#define LD52_CLIENT_MATHUTIL_H

#include <string>
#include <sstream>
#include "SFML/System/Vector2.hpp"

namespace MathUtil {
    inline sf::Vector2f toFloat(sf::Vector2i intVec) {
        return sf::Vector2f { static_cast<float>(intVec.x), static_cast<float>(intVec.y) };
    }
    inline sf::Vector2f toFloat(sf::Vector2u intVec) {
        return sf::Vector2f { static_cast<float>(intVec.x), static_cast<float>(intVec.y) };
    }

    inline constexpr const float pow2(float x) {
        return x * x;
    }

    inline std::string toHexString(int number) {
        std::stringstream stream;
        stream << std::hex << number;
        return stream.str();
    }

    bool segmentsIntersect(sf::Vector2f p0, sf::Vector2f p1,
                           sf::Vector2f p2, sf::Vector2f p3) {
        float s1_x, s1_y, s2_x, s2_y;
        s1_x = p1.x - p0.x;     s1_y = p1.y - p0.y;
        s2_x = p3.x - p2.x;     s2_y = p3.y - p2.y;

        float s, t;
        s = (-s1_y * (p0.x - p2.x) + s1_x * (p0.y - p2.y)) / (-s2_x * s1_y + s1_x * s2_y);
        t = ( s2_x * (p0.y - p2.y) - s2_y * (p0.x - p2.x)) / (-s2_x * s1_y + s1_x * s2_y);

        return s >= 0 && s <= 1 && t >= 0 && t <= 1;
    }

    float pointSegmentDistanceSquared(sf::Vector2f point, sf::Vector2f lineStart, sf::Vector2f lineEnd) {
        float A = point.x - lineStart.x;
        float B = point.y - lineStart.y;
        float C = lineEnd.x - lineStart.x;
        float D = lineEnd.y - lineStart.y;

        float dot = A * C + B * D;
        float len_sq = C * C + D * D;
        float param = -1;
        if (len_sq != 0) //in case of 0 length line
            param = dot / len_sq;

        float xx, yy;

        if (param < 0) {
            xx = lineStart.x;
            yy = lineStart.y;
        }
        else if (param > 1) {
            xx = lineEnd.x;
            yy = lineEnd.y;
        }
        else {
            xx = lineStart.x + param * C;
            yy = lineStart.y + param * D;
        }

        float dx = point.x - xx;
        float dy = point.y - yy;
        return dx * dx + dy * dy;
    }

    float pointSegmentDistance(sf::Vector2f point, sf::Vector2f lineStart, sf::Vector2f lineEnd) {
        return sqrt(pointSegmentDistanceSquared(point, lineStart, lineEnd));
    }
}

#endif //LD52_CLIENT_MATHUTIL_H