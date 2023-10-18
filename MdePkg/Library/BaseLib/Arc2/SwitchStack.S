/** @file
  ARC switch stack implementation.

  Copyright (c) 2023 Basemark Oy

  Author: Aliaksei Katovich @ basemark.com

  Released under the BSD-2-Clause License
**/

.align 4

.global InternalSwitchStackAsm
.section .text.InternalSwitchStackAsm, "ax"
.type InternalSwitchStackAsm, %function

InternalSwitchStackAsm:
	mov	%sp, %r2
	mov	%fp, %sp
	bl	EntryPoint__
	; Something went wrong, freeze CPU
	sleep

.global CpuPause
.section .text.CpuPause, "ax"
.type CpuPause, %function

CpuPause2:
	nop
	; return
	j_s	[blink]
	nop_s

CpuPause:
	nop_s
	sleep
