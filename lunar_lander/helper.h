#ifndef HELPER_H
#define HELPER_H

#define LOG(argument) std::cout << argument << '\n'

constexpr glm::mat4 IDENTITY_MAT = glm::mat4(1.0f);

constexpr float STANDARD_COORDINATES[] =
{
    // Triangle 1
    0.0f, 1.0f,  // Lower left
    1.0f, 1.0f,  // Lower right
    1.0f, 0.0f,  // Upper right
    // Triangle 2
    0.0f, 1.0f,  // Lower left
    1.0f, 0.0f,  // Upper right
    0.0f, 0.0f   // Upper left
};

constexpr char MAT_SEP = '\t';

#endif
