
#include "../include/helper.h"

std::unordered_map<std::string, bool> getButton(u32 pressed) {
    std::unordered_map<std::string, bool> buttonStates;

    // Vérifie chaque bouton et définit la valeur correspondante dans le dictionnaire
    if (pressed & WPAD_BUTTON_HOME)
        buttonStates["Home"] = true;
    if (pressed & WPAD_BUTTON_A)
        buttonStates["A"] = true;
    if (pressed & WPAD_BUTTON_B)
        buttonStates["B"] = true;
    if (pressed & WPAD_BUTTON_1)
        buttonStates["1"] = true;
    if (pressed & WPAD_BUTTON_2)
        buttonStates["2"] = true;
    if (pressed & WPAD_BUTTON_MINUS)
        buttonStates["Minus"] = true;
    if (pressed & WPAD_BUTTON_PLUS)
        buttonStates["Plus"] = true;
    if (pressed & WPAD_BUTTON_UP)
        buttonStates["Up"] = true;
    if (pressed & WPAD_BUTTON_DOWN)
        buttonStates["Down"] = true;
    if (pressed & WPAD_BUTTON_LEFT)
        buttonStates["Left"] = true;
    if (pressed & WPAD_BUTTON_RIGHT)
        buttonStates["Right"] = true;
    if (pressed & WPAD_NUNCHUK_BUTTON_Z)
        buttonStates["Z"] = true;
    if (pressed & WPAD_NUNCHUK_BUTTON_C)
        buttonStates["C"] = true;

    return buttonStates;
}
