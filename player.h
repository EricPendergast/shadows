#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    // 'direction_lr' specifies the direction the player is trying to move and
    // 'jump' specifies whether the player just tried to jump.
    void move(int direction_lr, bool jump);
    void draw();
private:
    float x = 0;
    float y = 0;
    float dx = 0;
    float dy = 0;
};

#endif
