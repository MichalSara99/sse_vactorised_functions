								.model flat,c
								.const
								align 16
;; =========================================================== GENERAL ===========================================================

int_abs_mask_ps					dword	7fffffffh,7fffffffh,7fffffffh,7fffffffh	
int_abs_mask_pd					qword	7fffffffffffffffh,7fffffffffffffffh

								.code
;;				extern "C" bool mul_sse_ps(float const* x, float const* y, int n, float* out);
mul_sse_ps						proc
								push ebp
								mov ebp,esp
								push esi
								push edi
								
								xor eax,eax

								mov ecx,[ebp + 16]
								cmp ecx,4
								jl Done

								mov esi,[ebp + 8]
								test esi,0fh
								jnz Done

								mov edi,[ebp + 12]
								test edi,0fh
								jnz Done

								mov edx,[ebp + 20]
								test edx,0fh
								jnz Done

								and ecx,0fffffffeh

					@@:			movaps xmm0,xmmword ptr [esi]
								movaps xmm1,xmmword ptr [edi]
								mulps xmm0,xmm1
								movaps xmmword ptr [edx],xmm0
								add esi,16
								add edi,16
								add edx,16
								sub ecx,4
								jnz @B

								mov eax,1

				Done:			pop edi
								pop esi
								mov esp,ebp
								pop ebp
								ret
mul_sse_ps						endp

;;				extern "C" bool mul_sse_pd(double const* x, double const* y, int n, double* out);
mul_sse_pd						proc
								push ebp
								mov ebp,esp
								push esi
								push edi
								
								xor eax,eax

								mov ecx,[ebp + 16]
								cmp ecx,2
								jl Done

								mov esi,[ebp + 8]
								test esi,0fh
								jnz Done

								mov edi,[ebp + 12]
								test edi,0fh
								jnz Done

								mov edx,[ebp + 20]
								test edx,0fh
								jnz Done

								and ecx,0fffffffeh

					@@:			movapd xmm0,xmmword ptr [esi]
								movapd xmm1,xmmword ptr [edi]
								mulpd xmm0,xmm1
								movapd xmmword ptr [edx],xmm0
								add esi,16
								add edi,16
								add edx,16
								sub ecx,2
								jnz @B

								mov eax,1

				Done:			pop edi
								pop esi
								mov esp,ebp
								pop ebp
								ret
mul_sse_pd						endp

;;			extern "C" bool abs_sse_ps(float const* x, int n, float* out);
abs_sse_ps						proc
								push ebp
								mov ebp,esp
								push ebx
		
								xor eax,eax

								mov ecx,[ebp + 12]
								cmp ecx,4
								jl Done

								mov ebx,[ebp + 8]
								test ebx,0fh
								jnz Done

								mov edx,[ebp + 16]
								test edx,0fh
								jnz Done

					@@:			movaps xmm0,xmmword ptr [ebx]
								andps xmm0,xmmword ptr [int_abs_mask_ps]
								movaps xmmword ptr [edx],xmm0
								add ebx,16
								add edx,16
								sub ecx,4
								jnz @B


								mov eax,1
								
				Done:			pop ebx
								mov esp,ebp
								pop ebp
								ret
abs_sse_ps						endp

;;			extern "C" bool abs_sse_pd(double const* x, int n, double* out);
abs_sse_pd						proc
								push ebp
								mov ebp,esp
								push ebx
		
								xor eax,eax

								mov ecx,[ebp + 12]
								cmp ecx,2
								jl Done

								mov ebx,[ebp + 8]
								test ebx,0fh
								jnz Done

								mov edx,[ebp + 16]
								test edx,0fh
								jnz Done

					@@:			movapd xmm0,xmmword ptr [ebx]
								andpd xmm0,xmmword ptr [int_abs_mask_ps]
								movapd xmmword ptr [edx],xmm0
								add ebx,16
								add edx,16
								sub ecx,2
								jnz @B


								mov eax,1
								
				Done:			pop ebx
								mov esp,ebp
								pop ebp
								ret
abs_sse_pd						endp
								end
