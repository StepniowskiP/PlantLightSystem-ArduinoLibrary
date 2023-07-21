#include "CommandMap.h"

CommandMap::CommandMap() {}
CommandMap::~CommandMap() {}

CommandMap::CommandMap(const char *cmd, uint8_t cmd_value)
{
    _cmd = cmd;
    _cmd_value = cmd_value;
}

uint8_t CommandMap::get_cmd_value()
{
    return _cmd_value;
}

const char *CommandMap::get_cmd()
{
    return _cmd;
}