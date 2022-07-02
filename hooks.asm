SilentFile PROTO C
pModuleBase  PROTO C
minusOne  PROTO C
minusOne32Int PROTO C
.code

HookSilentGetter PROC
	mov [rsp + 28h], r9
	push rcx
	mov rcx, qword ptr [pModuleBase]
	add rcx, 5A38518h
	mov rcx, qword ptr [rcx]
	cmp rcx, qword ptr [rsp]
	pop rcx
	jnz Done
	mov edx, dword ptr [minusOne32Int]
	mov dword ptr [r8], edx	
	mov rdx, qword ptr [SilentFile]
	Done:
	ret
HookSilentGetter ENDP



HookVoiceDuration PROC
	push rcx
	mov ecx, dword ptr [minusOne]
	mov dword ptr [rsi+390h], ecx
	mov rcx, qword ptr [pModuleBase]
	add rcx, 5A38518h
	mov rcx, qword ptr [rcx]
	cmp rcx, rsi
	pop rcx
	jnz Done
	mov dword ptr [rsi+38Ch], 38d1b717h
	mov dword ptr [rsi+390h], 38d1b717h
	Done:
	or dword ptr [rsi+2D0h], 10000000h
	ret
HookVoiceDuration ENDP

HookTimerSet PROC
	push rcx
	mov rcx, qword ptr [pModuleBase]
	add rcx, 37433F8h
	mulss xmm0, dword ptr [rcx]
	movss dword ptr [rsi+38Ch], xmm0
	mov rcx, qword ptr [pModuleBase]
	add rcx, 5A38518h
	mov rcx, qword ptr [rcx]
	cmp rcx, rsi
	pop rcx
	jnz Done
	mov dword ptr [rsi+38Ch], 38d1b717h
	Done:
	ret
HookTimerSet ENDP

HookYetAnotherTimer PROC
	mov qword ptr [rsp + 88h], rbp
	mov qword ptr [rsp + 80h], rdi
	push rcx
	mov rcx, qword ptr [pModuleBase]
	add rcx, 59D6FD0h
	mov rcx, qword ptr [rcx]
	cmp rcx, rsi
	pop rcx
	jnz Done
	movss xmm0, dword ptr [minusOne]
	Done:
	ret
HookYetAnotherTimer ENDP

HookVoiceDurationALT PROC
	push rcx
	mov ecx, dword ptr [minusOne]
	mov dword ptr [rsi+390h], ecx
	mov rcx, qword ptr [pModuleBase]
	add rcx, 59D6FD0h
	mov rcx, qword ptr [rcx]
	cmp rcx, rsi
	pop rcx
	jnz Done
	mov dword ptr [rsi+38Ch], 38d1b717h
	mov dword ptr [rsi+390h], 38d1b717h
	Done:
	or dword ptr [rsi+2D0h], 10000000h
	ret
HookVoiceDurationALT ENDP
END

