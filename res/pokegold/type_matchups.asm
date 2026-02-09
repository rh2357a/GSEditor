SECTION "GSEditor_BattleCommand_Stab", ROMX[$4890], BANK[$d]
GSEditor_BattleCommand_Stab:
    gse@homecall2 GSEditor_NewBattleCommand_Stab
    ret
    gse@fardw GSEditor_TypeMatchups
    gse@fardw GSEditor_WeatherTypeModifiers
    gse@fardw GSEditor_WeatherMoveModifiers

SECTION "GSEditor_CheckTypeMatchup", ROMX[$4923], BANK[$d]
GSEditor_CheckTypeMatchup:
    gse@homecall2 GSEditor_NewCheckTypeMatchup
    ret

SECTION "GSEditor_DoWeatherModifiers", ROMX[$7df8], BANK[$3e]
GSEditor_DoWeatherModifiers:
    gse@homecall2 GSEditor_NewDoWeatherModifiers
    ret

SECTION "GSEditor_HackingCodes", ROMX[$47d4], BANK[$7f]
GSEditor_HackingFlags::
    db $fe, $ff ; TypeMatchups

GSEditor_NewDoWeatherModifiers::
    ld de, GSEditor_WeatherTypeModifiers
    ld a, [$cbf0]
    ld b, a
    ld a, [$d20e]
    ld c, a

.check_weather_type
    ld a, [de]
    inc de

    cp $ff
    jr z, .done_weather_types

    cp b
    jr nz, .next_weather_type

    ld a, [de]
    cp c
    jr z, .apply_modifier

.next_weather_type
    inc de
    inc de
    jr .check_weather_type

.done_weather_types
    ld de, GSEditor_WeatherMoveModifiers

    ld a, $d
    call $3bd0
    ld c, a

.check_weather_move
    ld a, [de]
    inc de

    cp $ff
    jr z, .done

    cp b
    jr nz, .next_weather_move

    ld a, [de]
    cp c
    jr z, .apply_modifier

.next_weather_move
    inc de
    inc de
    jr .check_weather_move

.apply_modifier
    xor a
    ldh [$ffb6], a
    ld a, [$d1fe]
    ldh [$ffb7], a
    ld a, [$d1ff]
    ldh [$ffb8], a

    inc de
    ld a, [de]
    ldh [$ffb9], a

    call $325c

    ld a, $a
    ldh [$ffb9], a
    ld b, 4
    call $3267

    ldh a, [$ffb6]
    and a
    ld bc, $ffff
    jr nz, .update

    ldh a, [$ffb7]
    ld b, a
    ldh a, [$ffb8]
    ld c, a
    or b
    jr nz, .update

    ld bc, 1

.update
    ld a, b
    ld [$d1fe], a
    ld a, c
    ld [$d1ff], a

.done
    ret

GSEditor_NewBattleCommand_Stab::
    ld hl, GSEditor_TypeMatchups

.loop
    ld a, [hli]

    cp $ff
    jr z, .end

    cp $fe
    jr nz, .skip_foresight

    ld a, 5
    call $3bd0
    bit 3, a
    jr nz, .end
    jr .loop

.skip_foresight
    cp b
    jr nz, .skip_type
    ld a, [hl]
    cp d
    jr z, .got_matchup
    cp e
    jr z, .got_matchup
    jr .skip_type

.got_matchup
    push hl
    push bc
    inc hl
    ld a, [$cb4b]
    and $80
    ld b, a
    ld a, [hl]
    and a
    jr nz, .not_immune
    inc a
    ld [$cb4d], a
    xor a

.not_immune
    ldh [$ffb9], a
    add b
    ld [$cb4b], a

    xor a
    ldh [$ffb6], a

    ld hl, $d1fe
    ld a, [hli]
    ldh [$ffb7], a
    ld a, [hld]
    ldh [$ffb8], a
    call $325c

    ldh a, [$ffb6]
    ld b, a
    ldh a, [$ffb7]
    or b
    ld b, a
    ldh a, [$ffb8]
    or b
    jr z, .ok

    ld a, $a
    ldh [$ffb9], a
    ld b, 4
    call $3267
    ldh a, [$ffb7]
    ld b, a
    ldh a, [$ffb8]
    or b
    jr nz, .ok

    ld a, 1
    ldh [$ffb8], a

.ok
    ldh a, [$ffb7]
    ld [hli], a
    ldh a, [$ffb8]
    ld [hl], a
    pop bc
    pop hl

.skip_type
    inc hl
    inc hl
    jr .loop

.end
    call GSEditor_BattleCheckTypeMatchup
    ld a, [$d20e]
    ld b, a
    ld a, [$cb4b]
    and $80
    or b
    ld [$cb4b], a
    ret

GSEditor_BattleCheckTypeMatchup:
	ld hl, $d1ca
	ldh a, [$ffe6]
	and a
	jr z, GSEditor_NewCheckTypeMatchup
	ld hl, $cb2a
GSEditor_NewCheckTypeMatchup::
    push hl
    push de
    push bc
    ld a, $f
    call $3bd0
    ld d, a
    ld b, [hl]
    inc hl
    ld c, [hl]
    ld a, $a
    ld [$d20e], a
    ld hl, GSEditor_TypeMatchups
.loop
    ld a, [hli]
    cp $ff
    jr z, .end
    cp $fe
    jr nz, .next
    ld a, 5
    call $3bd0
    bit 3, a
    jr nz, .end
    jr .loop

.next
    cp d
    jr nz, .nope
    ld a, [hli]
    cp b
    jr z, .yup
    cp c
    jr z, .yup
    jr .nope_2

.nope
    inc hl
.nope_2
    inc hl
    jr .loop

.yup
    xor a
    ldh [$ffb5], a
    ldh [$ffb6], a
    ldh [$ffb7], a
    ld a, [hli]
    ldh [$ffb8], a
    ld a, [$d20e]
    ldh [$ffb9], a
    call $325c
    ld a, 10
    ldh [$ffb9], a
    push bc
    ld b, 4
    call $3267
    pop bc
    ldh a, [$ffb8]
    ld [$d20e], a
    jr .loop

.end
    pop bc
    pop de
    pop hl
    ret
