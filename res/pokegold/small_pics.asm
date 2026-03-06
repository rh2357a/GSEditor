SECTION "GSEditor_GetOverworldSpritePalette", ROMX[$4334], BANK[$5]
    jp GSEditor_NewGetOverworldSpritePalette

SECTION "GSEditor_NewGetOverworldSpritePalette", ROMX[$7bd0], BANK[$5]
GSEditor_NewGetOverworldSpritePalette::
    ld a, c
    push af
    call $42cb
    jr c, .is_pokemon

    ld hl, $47e3
    dec a
    ld c, a
    ld b, $0
    ld a, $6
    call $3241
    pop af
    ld c, [hl]
    ret

.is_pokemon
    pop af

    cp $80
    jr c, .normal
    cp $e0
    jr z, .breed_1

.breed_2
    ld a, [$dd8d]
    jr .normal

.breed_1
    ld a, [$dd54]
    jr .normal

.normal
    ld hl, $7ace ; pal_ids
    dec a
    ld e, a
    ld d, $0
    add hl, de
    ld c, [hl]
    ret

SECTION "GSEditor_GetOverworldPokemonIcon", ROMX[$6783], BANK[$23]
    jp GSEditor_NewGetOverworldPokemonIcon

SECTION "GSEditor_PartyMenuPokemonIconData", ROMX[$68ae], BANK[$23]
    ld de, $6a6c

SECTION "GSEditor_PartyMenuPokemonIcon", ROMX[$68b6], BANK[$23]
    call GSEditor_NewPartyMenuPokemonIcon

SECTION "GSEditor_EggSmallPictureId", ROMX[$696a], BANK[$23]
    ld a, $fc
    ret

SECTION "GSEditor_SmallPicturesHacking", ROMX[$6c6c], BANK[$23]
GSEditor_NewGetOverworldPokemonIcon::
    ld a, e
    push af

    call $695c
    ld l, a
    ld h, $0
    add hl, hl
    ld de, $6a6c
    add hl, de
    ldi a, [hl]
    ld e, a
    ld d, [hl]

    pop af
    cp $80
    jr nc, .second

.first
    ld bc, $7c08
    ret

.second
    ld bc, $7d08
    ret

GSEditor_NewPartyMenuPokemonIcon::
    ld a, [$c5be]
    cp $80
    jr nc, .second

.first
    ld bc, $7c08
    ret

.second
    ld bc, $7d08
    ret
