/*
    OpenGate Include
    This include provides an Automatic Gate System
    Where, when approaching the gate,
    it opens without the need to type commands or press buttons.
    
    Creator: Crazy_ArKzX
    Contributors: ddx60hz, HaShira_Caos, PortalSamp (utils)
    
    CreateAutoGate(
    modelid, // Object Model
    Float:closeX, Float:closeY, Float:closeZ, Float:closeRX, Float:closeRY, Float:closeRZ // Closed Gate Position
    Float:openX, Float:openY, Float:openZ, Float:openRX, Float:openRY, Float:openRZ // Open Gate Position
    Float:range = 10.0 // Distance to Open the Gate
    speed = 2 // Gate Opening Speed
    autoclose_time = 5000 // Time to Automatically Close the Gate
    bool:auto_open = true) // Opens Automatically for Anyone (true) or (false) to open only if the player meets a specific condition or performs a certain action
*/

#if defined _open_gate_included
    #endinput
#endif
#define _open_gate_included

#if !defined MAX_GATES
    #define MAX_GATES 1000
#endif
#if !defined GATE_CHECK
    #define GATE_CHECK 1000
#endif

enum _E_G{ bool:_a, _b, Float:_c[6], Float:_d[6], _e, _f, _g, _h, bool:_i, _j, _k, bool:_l };

static _XGate[_Y = MAX_GATES][_Z = _E_G];
static g1[MAX_GATES][_E_G];
static gT = -1;
static gA = 0;

#define _EX(i)   g1[i][_a]
#define _OBJ(i)  g1[i][_b]
#define _CP(i)   g1[i][_c]
#define _OP(i)   g1[i][_d]
#define _R(i)    g1[i][_e]
#define _RSQ(i)  g1[i][_f]
#define _S(i)    g1[i][_g]
#define _ACT(i)  g1[i][_h]
#define _OPEN(i) g1[i][_i]
#define _CT(i)   g1[i][_j]
#define _LC(i)   g1[i][_k]
#define _AUTO(i) g1[i][_l]

stock Float:GetDistanceSq(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
    new Float:dx = x2 - x1;
    new Float:dy = y2 - y1;
    new Float:dz = z2 - z1;
    return (dx*dx)+(dy*dy)+(dz*dz);
}

stock CreateAutoGate(modelid, Float:cx, Float:cy, Float:cz, Float:crx, Float:cry, Float:crz, Float:ox, Float:oy, Float:oz, Float:orx, Float:ory, Float:orz, Float:range = 10.0, speed = 2, autoclose_time = 5000, bool:auto_open = true)
{
    new slot = -1;
    for(new i = 0; i < MAX_GATES; i++) if(! _EX(i)) { slot = i; break; }
    if(slot == -1) return -1;
    _OBJ(slot) = CreateObject(modelid, cx, cy, cz, crx, cry, crz);
    if(_OBJ(slot) == INVALID_OBJECT_ID) return -1;
    _CP(slot)[0]=cx; _CP(slot)[1]=cy; _CP(slot)[2]=cz; _CP(slot)[3]=crx; _CP(slot)[4]=cry; _CP(slot)[5]=crz;
    _OP(slot)[0]=ox; _OP(slot)[1]=oy; _OP(slot)[2]=oz; _OP(slot)[3]=orx; _OP(slot)[4]=ory; _OP(slot)[5]=orz;
    _R(slot)=range; _RSQ(slot)=range*range; _S(slot)=speed; _ACT(slot)=autoclose_time; _OPEN(slot)=false; _CT(slot)=-1; _LC(slot)=0; _AUTO(slot)=auto_open;
    _EX(slot)=true; gA++;
    if(gA==1 && gT==-1) gT = SetTimer("AutoGateCheck", GATE_CHECK, true);
    return slot;
}

stock DestroyAutoGate(gateid)
{
    if(gateid<0||gateid>=MAX_GATES||!_EX(gateid)) return 0;
    DestroyObject(_OBJ(gateid));
    if(_CT(gateid) != -1){ KillTimer(_CT(gateid)); _CT(gateid) = -1; }
    _EX(gateid) = false; gA--;
    if(gA==0 && gT!=-1){ KillTimer(gT); gT = -1; }
    return 1;
}

stock OpenAutoGate(gateid)
{
    if(gateid<0||gateid>=MAX_GATES||!_EX(gateid)||_OPEN(gateid)) return 0;
    MoveObject(_OBJ(gateid),_OP(gateid)[0],_OP(gateid)[1],_OP(gateid)[2], _S(gateid),_OP(gateid)[3],_OP(gateid)[4],_OP(gateid)[5]);
    _OPEN(gateid)=true;
    if(_CT(gateid)!=-1) KillTimer(_CT(gateid));
    _CT(gateid)=SetTimerEx("AutoGateCloseTimer", _ACT(gateid), false, "i", gateid);
    return 1;
}

stock OpenManualGate(gateid, playerid)
{
    if(gateid<0||gateid>=MAX_GATES||!_EX(gateid)) return 0;
    if(_OPEN(gateid)) return 0;
    new Float:px,py,pz;
    GetPlayerPos(playerid, px, py, pz);
    new Float:ds = GetDistanceSq(px,py,pz, _CP(gateid)[0],_CP(gateid)[1],_CP(gateid)[2]);
    if(ds > _RSQ(gateid)) return 0;
    return OpenAutoGate(gateid);
}

stock CloseAutoGate(gateid)
{
    if(gateid<0||gateid>=MAX_GATES||!_EX(gateid)||!_OPEN(gateid)) return 0;
    MoveObject(_OBJ(gateid),_CP(gateid)[0],_CP(gateid)[1],_CP(gateid)[2],_S(gateid),_CP(gateid)[3],_CP(gateid)[4],_CP(gateid)[5]);
    _OPEN(gateid)=false;
    if(_CT(gateid)!=-1){ KillTimer(_CT(gateid)); _CT(gateid)=-1; }
    return 1;
}

stock IsAutoGateOpen(gateid)
{
    if(gateid<0||gateid>=MAX_GATES||!_EX(gateid)) return 0;
    return _OPEN(gateid);
}

forward AutoGateCheck();
public AutoGateCheck()
{
    if(gA==0) return 1;
    new Float:px,py,pz; new tick = GetTickCount();
    for(new i=0;i<MAX_GATES;i++)
    {
        if(!_EX(i)) continue;
        if(!_AUTO(i)) continue;
        new bool:near=false;
        foreach(new playerid : Player)
        {
            if(GetPlayerVirtualWorld(playerid)!=0) continue;
            GetPlayerPos(playerid, px, py, pz);
            new Float:ds = GetDistanceSq(px,py,pz,_CP(i)[0],_CP(i)[1],_CP(i)[2]);
            if(ds <= _RSQ(i)){ near=true; if(!_OPEN(i)) OpenAutoGate(i); break; }
        }
        if(!near && _OPEN(i) && _CT(i)==-1) _CT(i)=SetTimerEx("AutoGateCloseTimer",_ACT(i),false,"i",i);
        _LC(i)=tick;
    }
    return 1;
}

#if !defined foreach
forward AutoGateCheckFallback();
public AutoGateCheckFallback()
{
    if(gA==0) return 1;
    new Float:px,py,pz; new maxp = GetMaxPlayers();
    for(new i=0;i<MAX_GATES;i++)
    {
        if(!_EX(i)) continue;
        if(!_AUTO(i)) continue;
        new bool:near=false;
        for(new playerid=0; playerid<maxp; playerid++)
        {
            if(!IsPlayerConnected(playerid)) continue;
            GetPlayerPos(playerid, px, py, pz);
            new Float:ds = GetDistanceSq(px,py,pz,_CP(i)[0],_CP(i)[1],_CP(i)[2]);
            if(ds <= _RSQ(i)){ near=true; if(!_OPEN(i)) OpenAutoGate(i); break; }
        }
        if(!near && _OPEN(i) && _CT(i)==-1) _CT(i)=SetTimerEx("AutoGateCloseTimer",_ACT(i),false,"i",i);
    }
    return 1;
}
#endif

forward AutoGateCloseTimer(gateid);
public AutoGateCloseTimer(gateid)
{
    _CT(gateid) = -1;
    CloseAutoGate(gateid);
    return 1;
}

public OnGameModeExit()
{
    if(gT!=-1){ KillTimer(gT); gT = -1; }
    for(new i=0;i<MAX_GATES;i++) if(_EX(i)) DestroyAutoGate(i);
    #if defined AutoGate_OnGameModeExit
        return AutoGate_OnGameModeExit();
    #else
        return 1;
    #endif
}
#if defined _ALS_OnGameModeExit
    #undef OnGameModeExit
#else
    #define _ALS_OnGameModeExit
#endif
#define OnGameModeExit AutoGate_OnGameModeExit
#if defined AutoGate_OnGameModeExit
    forward AutoGate_OnGameModeExit();
#endif