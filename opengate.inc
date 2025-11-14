/*
    OpenGate Include
    This include provides an Automatic Gate System
    Where, when approaching the gate,
    it opens without the need to type commands or press buttons.
    
    Creators: Crazy_ArKzX & Tommy
    
    CreateAutoGate(
    modelid, // Object Model
    Float:closeX, Float:closeY, Float:closeZ, Float:closeRX, Float:closeRY, Float:closeRZ // Closed Gate Position
    Float:openX, Float:openY, Float:openZ, Float:openRX, Float:openRY, Float:openRZ // Open Gate Position
    Float:range = 10.0 // Distance to Open the Gate
    speed = 2 // Gate Opening Speed
    autoclose_time = 5000 // Time to Automatically Close the Gate
    bool:auto_open = true) // Opens Automatically for Anyone (true) or (false) to open only if the player meets a specific condition or performs a certain action
    
    USE DestroyAllAutoGates(); In OnGameModeExit!!! 
*/

#if defined _opengate_included
    #endinput
#endif
#define _opengate_included
#if !defined MAX_GATES
    #define MAX_GATES 1000
#endif
#tryinclude <streamer>
#if !defined _streamer_included
    #error "Streamer Plugin Required!"
#endif

enum _0x4A2B {
    bool:_0x1E3F,
    _0x9C4D,
    _0x7B1A,
    Float:_0x3D8E[6],
    Float:_0x6F2C[6],
    Float:_0x8A3B,
    _0x2E7D,
    _0x5C9A,
    bool:_0x4D1F,
    _0x9E3A,
    bool:_0x7C2D
}

static _0xB4E1[MAX_GATES][_0x4A2B];

stock Float:_0x3F8D(Float:_0x1, Float:_0x2, Float:_0x3, Float:_0x4, Float:_0x5, Float:_0x6) 
{
    new Float:_0x7 = _0x4 - _0x1;
    new Float:_0x8 = _0x5 - _0x2;
    new Float:_0x9 = _0x6 - _0x3;
    return (_0x7 * _0x7) + (_0x8 * _0x8) + (_0x9 * _0x9);
}

stock CreateAutoGate(_0xA, Float:_0xB, Float:_0xC, Float:_0xD, Float:_0xE, Float:_0xF, Float:_0x10, Float:_0x11, Float:_0x12, Float:_0x13, Float:_0x14, Float:_0x15, Float:_0x16, Float:_0x17 = 10.0, _0x18 = 2, _0x19 = 5000, bool:_0x1A = true)
{
    new _0x1B = -1;
    for(new _0x1C = 0; _0x1C < MAX_GATES; _0x1C++) 
    {
        if(!_0xB4E1[_0x1C][_0x1E3F]) 
        {
            _0x1B = _0x1C;
            break;
        }
    }
    if(_0x1B == -1) return -1;  
    _0xB4E1[_0x1B][_0x9C4D] = CreateDynamicObject(_0xA, _0xB, _0xC, _0xD, _0xE, _0xF, _0x10);
    if(_0xB4E1[_0x1B][_0x9C4D] == INVALID_STREAMER_ID) return -1;  
    _0xB4E1[_0x1B][_0x3D8E][0] = _0xB;
    _0xB4E1[_0x1B][_0x3D8E][1] = _0xC;
    _0xB4E1[_0x1B][_0x3D8E][2] = _0xD;
    _0xB4E1[_0x1B][_0x3D8E][3] = _0xE;
    _0xB4E1[_0x1B][_0x3D8E][4] = _0xF;
    _0xB4E1[_0x1B][_0x3D8E][5] = _0x10;
    _0xB4E1[_0x1B][_0x6F2C][0] = _0x11;
    _0xB4E1[_0x1B][_0x6F2C][1] = _0x12;
    _0xB4E1[_0x1B][_0x6F2C][2] = _0x13;
    _0xB4E1[_0x1B][_0x6F2C][3] = _0x14;
    _0xB4E1[_0x1B][_0x6F2C][4] = _0x15;
    _0xB4E1[_0x1B][_0x6F2C][5] = _0x16;
    _0xB4E1[_0x1B][_0x8A3B] = _0x17;
    _0xB4E1[_0x1B][_0x2E7D] = _0x18;
    _0xB4E1[_0x1B][_0x5C9A] = _0x19;
    _0xB4E1[_0x1B][_0x4D1F] = false;
    _0xB4E1[_0x1B][_0x9E3A] = -1;
    _0xB4E1[_0x1B][_0x7C2D] = _0x1A;
    _0xB4E1[_0x1B][_0x1E3F] = true;
    _0xB4E1[_0x1B][_0x7B1A] = CreateDynamicCircle(_0xB, _0xC, _0x17);
    Streamer_SetIntData(STREAMER_TYPE_AREA, _0xB4E1[_0x1B][_0x7B1A], E_STREAMER_EXTRA_ID, _0x1B);
    return _0x1B;
}

stock DestroyAutoGate(_0x1D) 
{
    if(_0x1D < 0 || _0x1D >= MAX_GATES || !_0xB4E1[_0x1D][_0x1E3F]) return 0;
    DestroyDynamicObject(_0xB4E1[_0x1D][_0x9C4D]);
    DestroyDynamicArea(_0xB4E1[_0x1D][_0x7B1A]);
    if(_0xB4E1[_0x1D][_0x9E3A] != -1) 
    {
        KillTimer(_0xB4E1[_0x1D][_0x9E3A]);
        _0xB4E1[_0x1D][_0x9E3A] = -1;
    }
    _0xB4E1[_0x1D][_0x1E3F] = false;
    return 1;
}

stock OpenAutoGate(_0x1E) 
{
    if(_0x1E < 0 || _0x1E >= MAX_GATES || !_0xB4E1[_0x1E][_0x1E3F] || _0xB4E1[_0x1E][_0x4D1F]) return 0;
    MoveDynamicObject(_0xB4E1[_0x1E][_0x9C4D], _0xB4E1[_0x1E][_0x6F2C][0], _0xB4E1[_0x1E][_0x6F2C][1], _0xB4E1[_0x1E][_0x6F2C][2], _0xB4E1[_0x1E][_0x2E7D], _0xB4E1[_0x1E][_0x6F2C][3], _0xB4E1[_0x1E][_0x6F2C][4], _0xB4E1[_0x1E][_0x6F2C][5]);
    _0xB4E1[_0x1E][_0x4D1F] = true;
    if(_0xB4E1[_0x1E][_0x9E3A] != -1) 
    {
        KillTimer(_0xB4E1[_0x1E][_0x9E3A]);
    }
    _0xB4E1[_0x1E][_0x9E3A] = SetTimerEx("AutoGateCloseTimer", _0xB4E1[_0x1E][_0x5C9A], false, "i", _0x1E);
    return 1;
}

stock OpenManualGate(_0x1F, _0x20) 
{
    if(_0x1F < 0 || _0x1F >= MAX_GATES || !_0xB4E1[_0x1F][_0x1E3F]) return 0;
    if(_0xB4E1[_0x1F][_0x4D1F]) return 0;
    new Float:_0x21, Float:_0x22, Float:_0x23;
    GetPlayerPos(_0x20, _0x21, _0x22, _0x23);
    new Float:_0x24 = _0x3F8D(_0x21, _0x22, _0x23, _0xB4E1[_0x1F][_0x3D8E][0], _0xB4E1[_0x1F][_0x3D8E][1], _0xB4E1[_0x1F][_0x3D8E][2]);
    new Float:_0x25 = _0xB4E1[_0x1F][_0x8A3B] * _0xB4E1[_0x1F][_0x8A3B];
    if(_0x24 > _0x25) return 0;
    return OpenAutoGate(_0x1F);
}

stock CloseAutoGate(_0x26) 
{
    if(_0x26 < 0 || _0x26 >= MAX_GATES || !_0xB4E1[_0x26][_0x1E3F] || !_0xB4E1[_0x26][_0x4D1F]) return 0;
    MoveDynamicObject(_0xB4E1[_0x26][_0x9C4D], _0xB4E1[_0x26][_0x3D8E][0], _0xB4E1[_0x26][_0x3D8E][1], _0xB4E1[_0x26][_0x3D8E][2], _0xB4E1[_0x26][_0x2E7D], _0xB4E1[_0x26][_0x3D8E][3], _0xB4E1[_0x26][_0x3D8E][4], _0xB4E1[_0x26][_0x3D8E][5]);
    _0xB4E1[_0x26][_0x4D1F] = false;
    if(_0xB4E1[_0x26][_0x9E3A] != -1) 
    {
        KillTimer(_0xB4E1[_0x26][_0x9E3A]);
        _0xB4E1[_0x26][_0x9E3A] = -1;
    }
    return 1;
}

stock IsAutoGateOpen(_0x27) 
{
    if(_0x27 < 0 || _0x27 >= MAX_GATES || !_0xB4E1[_0x27][_0x1E3F]) return 0;
    return _0xB4E1[_0x27][_0x4D1F];
}

forward AutoGateCloseTimer(_0x28);
public AutoGateCloseTimer(_0x28) 
{
    _0xB4E1[_0x28][_0x9E3A] = -1;
    new bool:_0x29 = false;
    foreach(new _0x2A : Player) 
    {
        if(IsPlayerInDynamicArea(_0x2A, _0xB4E1[_0x28][_0x7B1A])) 
        {
            _0x29 = true;
            break;
        }
    }
    if(!_0x29) 
    {
        CloseAutoGate(_0x28);
    } else {
        _0xB4E1[_0x28][_0x9E3A] = SetTimerEx("AutoGateCloseTimer", _0xB4E1[_0x28][_0x5C9A], false, "i", _0x28);
    }
    return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
    #undef OnPlayerEnterDynamicArea
#else
    #define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea OG_OnPlrEnterDynArea
#if defined OG_OnPlrEnterDynArea
    forward OG_OnPlrEnterDynArea(playerid, areaid);
#endif
#if defined _ALS_OnPlayerLeaveDynamicArea
    #undef OnPlayerLeaveDynamicArea
#else
    #define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea OG_OnPlrLeaveDynArea
#if defined OG_OnPlrLeaveDynArea
    forward OG_OnPlrLeaveDynArea(playerid, areaid);
#endif
public OnPlayerEnterDynamicArea(playerid, areaid) 
{
    new _0x2D = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);
    if(_0x2D >= 0 && _0x2D < MAX_GATES && _0xB4E1[_0x2D][_0x1E3F]) 
    {
        if(_0xB4E1[_0x2D][_0x7C2D]) 
        {
            if(!_0xB4E1[_0x2D][_0x4D1F]) 
            {
                OpenAutoGate(_0x2D);
            }
        }
    }
    #if defined OG_OnPlrEnterDynArea 
        return OG_OnPlrEnterDynArea(playerid, areaid);
    #else
        return 1;
    #endif
}

public OnPlayerLeaveDynamicArea(playerid, areaid) 
{
    new _0x30 = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);
    if(_0x30 >= 0 && _0x30 < MAX_GATES && _0xB4E1[_0x30][_0x1E3F]) 
    {
        new bool:_0x31 = false;
        foreach(new _0x32 : Player) 
        {
            if(_0x32 != playerid && IsPlayerInDynamicArea(_0x32, areaid)) 
            {
                _0x31 = true;
                break;
            }
        }
        if(!_0x31 && _0xB4E1[_0x30][_0x4D1F] && _0xB4E1[_0x30][_0x9E3A] == -1) 
        {
            _0xB4E1[_0x30][_0x9E3A] = SetTimerEx("AutoGateCloseTimer", _0xB4E1[_0x30][_0x5C9A], false, "i", _0x30);
        }
    }
    #if defined OG_OnPlrLeaveDynArea
        return OG_OnPlrLeaveDynArea(playerid, areaid);
    #else
        return 1;
    #endif
}

stock DestroyAllAutoGates() 
{
    for(new _0x33 = 0; _0x33 < MAX_GATES; _0x33++) 
    {
        if(_0xB4E1[_0x33][_0x1E3F]) DestroyAutoGate(_0x33);
    }
    return 1;
}