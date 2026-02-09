MACRO gse@homecall
    ldh a, [$fff9]
    push af
    ld a, BANK(\1)
    rst $10
    call \1
    pop af
    rst $10
ENDM

MACRO gse@homecall2
    dec sp
    push hl
    push af
    push hl
    ld hl, sp + 6
    ld [hl], BANK(\1)
    dec hl
    ld [hl], HIGH(\1)
    dec hl
    ld [hl], LOW(\1)
    pop hl
    pop af
    call $2e73
    inc sp
    inc sp
    inc sp
ENDM

MACRO? gse@dbw
    db \1
    dw \2
ENDM

MACRO? gse@fardw
    db BANK(\1)
    dw \1
ENDM

MACRO? gse@pic_
    db LOW((BANK(\1) == $1f) * $f4 \
      +(BANK(\1) == $20) * $f4 \
      +(BANK(\1) == $2e) * $f1 \
      +(BANK(\1)))
    dw \1
ENDM

MACRO? gse@pic
    gse@pic_ GSEditor_\1_Image_\2
ENDM

MACRO? gse@pics
    gse@pic_ GSEditor_\1_FrontImage_\2
    gse@pic_ GSEditor_\1_BackImage_\2
ENDM
