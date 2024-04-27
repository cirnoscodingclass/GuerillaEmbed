  AREA |.text|, CODE, READONLY

divide PROC

        EXPORT divide

        ENTRY

        UDIV R0, R0, R1 // for 4/7 = 0

        BX LR

        ENDP

        

        ALIGN

        END