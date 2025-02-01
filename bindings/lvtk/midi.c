// Copyright 2022 Michael Fisher <mfisher@lvtk.org>
// SPDX-License-Identifier: ISC

/// MIDI utilities.
// @author Michael Fisher
// @module lvtk.midi

#include "bindings.h"
#include "packed.h"
#include <lauxlib.h>

/// Messages
// @section messages

static int f_msg3bytes (lua_State* L, uint8_t status) {
    LvtkPacked msg = { .packed = 0x00 };
    msg.bytes.b1   = status | (uint8_t) (lua_tointeger (L, 1) - 1);
    msg.bytes.b2   = (uint8_t) lua_tointeger (L, 2);
    msg.bytes.b3   = (uint8_t) lua_tointeger (L, 3);
    msg.bytes.b4   = 0x00;
    lua_pushinteger (L, msg.packed);
    return 1;
}

/// Make a controller message
// @function controller
// @int channel MIDI Channel
// @int controller Controller number
// @int value Controller Value
// @return MIDI message packed as Integer
// @within Messages
static int f_controller (lua_State* L) {
    return f_msg3bytes (L, 0xb0);
}

/// Make a note on message
// @function noteon
// @int channel MIDI Channel
// @int note Note number 0-127
// @int velocity Note velocity 0-127
// @return MIDI message packed as Integer
// @within Messages
static int f_noteon (lua_State* L) {
    return f_msg3bytes (L, 0x90);
}

/// Make a regular note off message
// @function noteoff
// @int channel MIDI Channel
// @int note Note number
// @return MIDI message packed as Integer
// @within Messages

/// Make a note off message with velocity
// @function noteoff
// @int channel MIDI Channel
// @int note Note number
// @int velocity Note velocity
// @return MIDI message packed as Integer
// @within Messages
static int f_noteoff (lua_State* L) {
    if (lua_gettop (L) == 2)
        lua_pushinteger (L, 0x00);
    return f_msg3bytes (L, 0x80);
}

static int f_tohertz (lua_State* L) {
    lua_pushinteger (L, 0);
    return 0;
}

static int f_clamp (lua_State* L) {
    lua_Integer value = lua_tointeger (L, 1);
    if (value < 0)
        value = 0;
    else if (value > 127)
        value = 127;
    lua_pushinteger (L, value);
    return 0;
}

static const luaL_Reg midi_f[] = {
    { "controller", f_controller },
    { "noteon", f_noteon },
    { "noteoff", f_noteoff },
    { "tohertz", f_tohertz },
    { "clamp", f_clamp },
    { NULL, NULL }
};

LUI_LUALIB
int luaopen_lui_midi (lua_State* L) {
    luaL_newlib (L, midi_f);
    return 1;
}
