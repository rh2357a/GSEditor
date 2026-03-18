SECTION "GSEditor_TrainerCard_Cleanup", ROMX[$57d5], BANK[$2]
    ds $5814 - $57d5

SECTION "GSEditor_TrainerCard_NewPalettes", ROMX[$57d5], BANK[$2]
GSEditor_TrainerCard_NewPalettes:
    ld hl, .ids
.loop
    ld a, [hl+]
    cp -1
    jr z, $5814 ; .done
    push hl
    call $5baa
    call $5aab
    pop hl
    jr .loop
.ids
    db 12, 1, 3, 2, 4, 7, 6, 5
    db -1
