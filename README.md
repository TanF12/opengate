# OPENGATE

**OpenGate Include** provides an **Automatic Gate System**  
When a player approaches the gate, it opens automatically  
without the need to type commands or press buttons.

## Demonstration

🎥 | [Watch on YouTube](https://youtu.be/NexNcZS4BEU?si=jopC68YlkFwErGUg) // Trash Quality 😡

## Syntax

```pawn
CreateAutoGate(
        modelid, // Object Model 
        Float:closeX, Float:closeY, Float:closeZ, Float:closeRX, Float:closeRY, Float:closeRZ, // Gate Position
        move[], // Direction of Movement: "left", "right", "up", "down", "forward", "backward"
        Float:movement, // How Many Meters Will the Gate Move 
        Float:range = 10.0, // Distance to Open the Gate 
        speed = 2, // Opening Speed
        autoclose_time = 5000, // Time to Auto Close
        bool:auto_open = true // Automatically Open to Anyone (true) or (false) Only With Condition 
    )
```

> Movement Options
* up
* down
* left
* right
* forward
* backward

# Usage Examples

Open Gate for Anyone
```pawn
public OnGameModeInit()
{
    CreateAutoGate(980, 1803.3665, -1722.0623, 13.5428, 0.0, 0.0, 0.0, "up", 3.8526, 10.0, 2, 5000, true);
    return 1;
}
```

 Open Gate Only for Players Meeting a Condition
```pawn
new myGate;

public OnGameModeInit()
{
    myGate = CreateAutoGate(980, 1803.3665, -1722.0623, 13.5428, 0.0, 0.0, 0.0, "up", 3.8526, 10.0, 2, 5000, false);
    return 1;
}

public OnPlayerUpdate(playerid)
{
    // Example condition: PlayerInfo[playerid][pEmprego] == 1
    if(PlayerInfo[playerid][pEmprego] == 1)
    {
        OpenManualGate(myGate, playerid);
    }
    return 1;
}
```
--------------------------------------------------------------------------------------------------------------

Features:
Automatic gate opening/closing
Supports custom open/close positions
Configurable opening range, speed, and auto-close time
Can restrict opening to specific players or condition
Fully compatible with SA-MP/open.mp scripting

--------------------------------------------------------------------------------------------------------------

Creators: Crazy_ArKzX & Tommy

--------------------------------------------------------------------------------------------------------------






