MACRO? dbw
    db \1
    dw \2
ENDM

MACRO? dbpic
    db LOW((BANK(\1) == $1f) * $f4 \
      +(BANK(\1) == $20) * $f4 \
      +(BANK(\1) == $2e) * $f1 \
      +(BANK(\1)))
    dw \1
ENDM


; 빌드 전용

MACRO? gsepic
    dbpic GSEditor_\1_Image_\2
ENDM

MACRO? gsepics
    dbpic GSEditor_\1_FrontImage_\2
    dbpic GSEditor_\1_BackImage_\2
ENDM
