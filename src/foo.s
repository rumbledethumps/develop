; Copyright (c) 2023 Rumbledethumps
;
; SPDX-License-Identifier: BSD-3-Clause
; SPDX-License-Identifier: Unlicense

; Generic variadic call to RP6502 RIA
; int __cdecl__ foo (unsigned char op, ...);

.include        "rp6502.inc"

.export		_foo, _foo_nowait
.importzp	sp
.import		addysp

.code

.proc	_foo

        jsr _foo_nowait

        ; wait for completion
busy:   bit RIA_BUSY
        bmi busy

        ; return result
        lda RIA_A
        ldx RIA_X
        rts

.endproc

.proc	_foo_nowait

        ; skip op argument
        dey

        ; save variadic size in X
        tya
        tax

        ; copy stack
copy:   dey
        lda (sp),y
        sta RIA_VSTACK
        tya
        bne copy

        ; recover variadic size
        txa
        tay

        ; begin RIA operation
        lda (sp),y
        sta RIA_OP
        iny

        ; remove args from stack and return
        jmp addysp

.endproc
