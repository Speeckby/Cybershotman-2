#include "../include/helper.h"

std::unordered_map<std::string, bool> getButton(u32 held, u32 down) {
    std::unordered_map<std::string, bool> buttonStates;

    // Vérifie chaque bouton et définit la valeur correspondante dans le dictionnaire
    buttonStates["Home"] = down & WPAD_BUTTON_HOME;
    buttonStates["A"] = down & WPAD_BUTTON_A;
    buttonStates["B"] = down & WPAD_BUTTON_B;
    buttonStates["1"] = down & WPAD_BUTTON_1;
    buttonStates["2"] = down & WPAD_BUTTON_2;
    buttonStates["Minus"] = down & WPAD_BUTTON_MINUS;
    buttonStates["Plus"] = down & WPAD_BUTTON_PLUS;
    buttonStates["Up"] = held & WPAD_BUTTON_UP;
    buttonStates["Down"] = held & WPAD_BUTTON_DOWN;
    buttonStates["Left"] = held & WPAD_BUTTON_LEFT;
    buttonStates["Right"] = held & WPAD_BUTTON_RIGHT;
    buttonStates["Z"] = down & WPAD_NUNCHUK_BUTTON_Z;
    buttonStates["C"] = down & WPAD_NUNCHUK_BUTTON_C;

    return buttonStates;
}
