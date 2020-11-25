								.model flat,c
								.const
								align 16
;; ======================================= packed double precision floating point =========================================

plus_1_pd						real8	1.0,1.0
;; ======================================= packed single precision floating point =========================================

plus_1_ps						real4	1.0,1.0,1.0,1.0
;; =========================================================== GENERAL ===========================================================

int_neg_mask_ps					dword	80000000h,80000000h,80000000h,80000000h
int_neg_mask_pd					qword	8000000000000000h,8000000000000000h
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

;;				extern "C" bool div_sse_ps(float const* x, float const* y, int n, float* out);
div_sse_ps						proc
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
								divps xmm0,xmm1
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
div_sse_ps						endp

;;				extern "C" bool div_sse_pd(double const* x, double const* y, int n, double* out);
div_sse_pd						proc
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
								divpd xmm0,xmm1
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
div_sse_pd						endp

;;				extern "C" bool add_sse_ps(float const* x, float const* y, int n, float* out);
add_sse_ps						proc
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
								addps xmm0,xmm1
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
add_sse_ps						endp

;;				extern "C" bool add_sse_pd(double const* x, double const* y, int n, double* out);
add_sse_pd						proc
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
								addpd xmm0,xmm1
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
add_sse_pd						endp

;;				extern "C" bool sub_sse_ps(float const* x, float const* y, int n, float* out);
sub_sse_ps						proc
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
								subps xmm0,xmm1
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
sub_sse_ps						endp

;;				extern "C" bool sub_sse_pd(double const* x, double const* y, int n, double* out);
sub_sse_pd						proc
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
								subpd xmm0,xmm1
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
sub_sse_pd						endp

;;			extern "C" bool neg_sse_pd(double const* x, int n, double* out);
neg_sse_pd						proc
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

								and ecx,0fffffffeh

					@@:			movapd xmm0,xmmword ptr [ebx]
								xorpd xmm0,xmmword ptr [int_neg_mask_pd]
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
neg_sse_pd						endp

;;			extern "C" bool neg_sse_ps(float const* x, int n, float* out);
neg_sse_ps						proc
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

								and ecx,0fffffffeh

					@@:			movaps xmm0,xmmword ptr [ebx]
								xorps xmm0,xmmword ptr [int_neg_mask_ps]
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
neg_sse_ps						endp

;;			extern "C" bool inv_sse_pd(double const* x, int n, double* out);
inv_sse_pd						proc
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

								and ecx,0fffffffeh

					@@:			movapd xmm0,xmmword ptr [ebx]
								movapd xmm1,xmmword ptr [plus_1_pd]
								divpd xmm1,xmm0
								movapd xmmword ptr [edx],xmm1

								add ebx,16
								add edx,16
								sub ecx,2
								jnz @B

								mov eax,1

				Done:			pop ebx
								mov esp,ebp
								pop ebp
								ret
inv_sse_pd						endp

;;			extern "C" bool inv_sse_ps(float const* x, int n, float* out);
inv_sse_ps						proc
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

								and ecx,0fffffffeh

					@@:			movaps xmm0,xmmword ptr [ebx]
								movaps xmm1,xmmword ptr [plus_1_ps]
								divps xmm1,xmm0
								movaps xmmword ptr [edx],xmm1

								add ebx,16
								add edx,16
								sub ecx,4
								jnz @B

								mov eax,1

				Done:			pop ebx
								mov esp,ebp
								pop ebp
								ret
inv_sse_ps						endp
								end
