//
// Created by cedric on 4/29/23.
//

#ifndef LD53_CLIENT_TICKABLE_H
#define LD53_CLIENT_TICKABLE_H
//
// Created by Alexander Winter🤤 on 2022-04-02.
//

class Tickable {
public:
    virtual ~Tickable() = default;

    virtual void tick(float delta) = 0;
};


#endif //LD53_CLIENT_TICKABLE_H
