Scriptname PIRVR_Holotape extends ReferenceAlias

Holotape Property PPIRVR_Holotape Auto Const Mandatory
ObjectReference Property PlayerRef Auto Const Mandatory

Event OnInit()
    PlayerRef.AddItem(PPIRVR_Holotape, 1, true)
    RegisterForMenuOpenCloseEvent("PipboyMenu")
EndEvent

Event OnPlayerLoadGame()
    if (PlayerRef.GetItemCount(PPIRVR_Holotape) == 0)
        PlayerRef.AddItem(PPIRVR_Holotape, 1, true)
    Endif
    RegisterForMenuOpenCloseEvent("PipboyMenu")
EndEvent
