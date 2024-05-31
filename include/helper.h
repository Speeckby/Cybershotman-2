#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include <unordered_map>
#include <wiiuse/wpad.h>
#include <string>

std::unordered_map<std::string, bool> getButton(u32 held, u32 down);

#endif // HELPER_H_INCLUDED
