#include "./inputs.h"

bool InputHandler::is_input_down(const char key)  {
    return (GetAsyncKeyState(key) & 0b1);
}