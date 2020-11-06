							.model flat,c
							.const
							align 16
;;	================================================ packed double-precision floating-point ================================================
two_o_pi_pd					real8   0.6366197723675813430755350,0.6366197723675813430755350
pi_pd						real8   3.1415926535897932384626433,3.1415926535897932384626433
half_pi_pd					real8	1.5707963267948966192313216,1.5707963267948966192313216
two_pi_pd					real8	6.2831853071795864769252866,6.2831853071795864769252866
one_pd						real8   1.0,1.0
m_ccoeff_pd					real8	-2.0,-2.0,-12.0,-12.0,-30.0,-30.0,-56.0,-56.0,-90.0,-90.0,-132.0,-132.0
absMask_pd					qword   7fffffffffffffffh,7fffffffffffffffh
minusMask_pd				qword   8000000000000000h,8000000000000000h
;;	================================================ packed single-precision floating-point ================================================
two_o_pi_ps					real4   0.6366197723675813430755350,0.6366197723675813430755350,0.6366197723675813430755350,0.6366197723675813430755350
pi_ps						real4   3.1415926535897932384626433,3.1415926535897932384626433,3.1415926535897932384626433,3.1415926535897932384626433
half_pi_ps					real4	1.5707963267948966192313216,1.5707963267948966192313216,1.5707963267948966192313216,1.5707963267948966192313216
two_pi_ps					real4	6.2831853071795864769252866,6.2831853071795864769252866,6.2831853071795864769252866,6.2831853071795864769252866
one_ps						real4   1.0,1.0,1.0,1.0
m_ccoeff_ps					real4	-2.0,-2.0,-2.0,-2.0,-12.0,-12.0,-12.0,-12.0,-30.0,-30.0,-30.0,-30.0,-56.0,-56.0,-56.0,-56.0,-90.0,-90.0,-90.0,-90.0
absMask_ps					dword   7fffffffh,7fffffffh,7fffffffh,7fffffffh
minusMask_ps				dword   80000000h,80000000h,80000000h,80000000h
;;	============================================================== general ==============================================================
int_one						dword	1h,1h,1h,1h
							.code
;;		extern "C" bool cos_sse_pd(double const* x, int n, double* out);

cos_sse_pd					proc
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

							lea eax,[m_ccoeff_pd]
							and ecx,0fffffffeh

							xorpd xmm7,xmm7

					@@:		movapd xmm7,xmmword ptr [one_pd]
							movapd xmm1,xmmword ptr [ebx]
							movapd xmm3,xmm1
							divpd xmm3,xmmword ptr [two_pi_pd]
							roundpd xmm3,xmm3,0011b
							mulpd xmm3,xmmword ptr [two_pi_pd]
							subpd xmm1,xmm3
							andpd xmm1,xmmword ptr [absMask_pd]        
							movapd xmm2,xmm1						;; xmm2 = x
							mulpd xmm1,xmmword ptr [two_o_pi_pd]
							cvttpd2dq xmm3,xmm1
							paddw xmm3,xmmword ptr [int_one]
							psrlw xmm3,1							;; xmm3
							cvtdq2pd xmm4,xmm3						;; xmm4 = 0,1,1,2
							pand xmm3,xmmword ptr [int_one]
							cvtdq2pd xmm3,xmm3
							xorpd xmm3,xmmword ptr [minusMask_pd] 
							cvtpd2dq xmm3,xmm3
							por xmm3,xmmword ptr [int_one]
							cvtdq2pd xmm6,xmm3						;; xmm6 = 1,-1

							mulpd xmm4,xmmword ptr [pi_pd]
							subpd xmm4,xmm2
							movapd xmm1,xmm4

							mulpd xmm1,xmm1
							movapd xmm2,xmm1
							movapd xmm0,xmmword ptr [eax]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							mulpd xmm1,xmm2
							movapd xmm0,xmmword ptr [eax+16]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							mulpd xmm1,xmm2
							movapd xmm0,xmmword ptr [eax+32]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							mulpd xmm1,xmm2
							movapd xmm0,xmmword ptr [eax+48]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
						    mulpd xmm1,xmm2
							movapd xmm0,xmmword ptr [eax+64]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							mulpd xmm1,xmm2
						    movapd xmm0,xmmword ptr [eax+80]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							
							mulpd xmm7,xmm6
							movapd xmmword ptr [edx],xmm7

							add ebx,16
							add edx,16
							sub ecx,2
							jnz @B

							mov eax,1

				Done:		pop ebx
							mov esp,ebp
							pop ebp
							ret
cos_sse_pd					endp

;;		extern "C" bool cos_sse_ps(float const* x, int n, float* out);

cos_sse_ps					proc
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

							lea eax,[m_ccoeff_ps]
							and ecx,0fffffffeh

							xorps xmm7,xmm7

					@@:		movaps xmm7,xmmword ptr [one_ps]
							movaps xmm1,xmmword ptr [ebx]
							movaps xmm3,xmm1
							divps xmm3,xmmword ptr [two_pi_ps]
							roundps xmm3,xmm3,0011b
							mulps xmm3,xmmword ptr [two_pi_ps]
							subps xmm1,xmm3
							andps xmm1,xmmword ptr [absMask_ps]        
							movaps xmm2,xmm1						;; xmm2 = x
							mulps xmm1,xmmword ptr [two_o_pi_ps]
							cvttps2dq xmm3,xmm1
							paddw xmm3,xmmword ptr [int_one]
							psrlw xmm3,1							;; xmm3
							cvtdq2ps xmm4,xmm3						;; xmm4 = 0,1,1,2
							pand xmm3,xmmword ptr [int_one]
							cvtdq2ps xmm3,xmm3
							xorps xmm3,xmmword ptr [minusMask_ps] 
							cvtps2dq xmm3,xmm3
							por xmm3,xmmword ptr [int_one]
							cvtdq2ps xmm6,xmm3						;; xmm6 = 1,-1

							mulps xmm4,xmmword ptr [pi_ps]
							subps xmm4,xmm2
							movaps xmm1,xmm4

							mulps xmm1,xmm1
							movaps xmm2,xmm1
							movaps xmm0,xmmword ptr [eax]
							divps xmm1,xmm0
							addps xmm7,xmm1
							mulps xmm1,xmm2
							movaps xmm0,xmmword ptr [eax+16]
							divps xmm1,xmm0
							addps xmm7,xmm1
							mulps xmm1,xmm2
							movaps xmm0,xmmword ptr [eax+32]
							divps xmm1,xmm0
							addps xmm7,xmm1
							mulps xmm1,xmm2
							movaps xmm0,xmmword ptr [eax+48]
							divps xmm1,xmm0
							addps xmm7,xmm1
						    mulps xmm1,xmm2
							movaps xmm0,xmmword ptr [eax+64]
							divps xmm1,xmm0
							addps xmm7,xmm1
							
							mulps xmm7,xmm6
							movaps xmmword ptr [edx],xmm7

							add ebx,16
							add edx,16
							sub ecx,4
							jnz @B

							mov eax,1

				Done:		pop ebx
							mov esp,ebp
							pop ebp
							ret
cos_sse_ps					endp

;;		extern "C" bool sin_sse_pd(double const* x, int n, double* out);
sin_sse_pd					proc

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

							lea eax,[m_ccoeff_pd]
							and ecx,0fffffffeh
							
							xorpd xmm7,xmm7

					@@:		movapd xmm7,xmmword ptr [one_pd]
							movapd xmm1,xmmword ptr [ebx]
							movapd xmm5,xmmword ptr [half_pi_pd]
							subpd xmm5,xmm1
							movapd xmm3,xmm5
							divpd xmm3,xmmword ptr [two_pi_pd]
							roundpd xmm3,xmm3,0011b
							mulpd xmm3,xmmword ptr [two_pi_pd]
							subpd xmm5,xmm3
							andpd xmm5,xmmword ptr [absMask_pd]        
							movapd xmm2,xmm5						;; xmm2 = x
							mulpd xmm5,xmmword ptr [two_o_pi_pd]
							cvttpd2dq xmm3,xmm5
							paddw xmm3,xmmword ptr [int_one]
							psrlw xmm3,1							;; xmm3
							cvtdq2pd xmm4,xmm3						;; xmm4 = 0,1,1,2
							pand xmm3,xmmword ptr [int_one]
							cvtdq2pd xmm3,xmm3
							xorpd xmm3,xmmword ptr [minusMask_pd] 
							cvtpd2dq xmm3,xmm3
							por xmm3,xmmword ptr [int_one]
							cvtdq2pd xmm6,xmm3						;; xmm6 = 1,-1

							mulpd xmm4,xmmword ptr [pi_pd]
							subpd xmm4,xmm2
							movapd xmm1,xmm4

							mulpd xmm1,xmm1
							movapd xmm2,xmm1
							movapd xmm0,xmmword ptr [eax]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							mulpd xmm1,xmm2
							movapd xmm0,xmmword ptr [eax+16]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							mulpd xmm1,xmm2
							movapd xmm0,xmmword ptr [eax+32]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							mulpd xmm1,xmm2
							movapd xmm0,xmmword ptr [eax+48]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
						    mulpd xmm1,xmm2
							movapd xmm0,xmmword ptr [eax+64]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							mulpd xmm1,xmm2
						    movapd xmm0,xmmword ptr [eax+80]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							
							mulpd xmm7,xmm6
							movapd xmmword ptr [edx],xmm7

							add ebx,16
							add edx,16
							sub ecx,2
							jnz @B

							mov eax,1

				Done:		pop ebx
							mov esp,ebp
							pop ebp
							ret
sin_sse_pd					endp

;;		extern "C" bool sin_sse_ps(float const* x, int n, float* out);
sin_sse_ps					proc
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

							lea eax,[m_ccoeff_ps]
							and ecx,0fffffffeh
							
							xorpd xmm7,xmm7

					@@:		movaps xmm7,xmmword ptr [one_ps]
							movaps xmm1,xmmword ptr [ebx]
							movaps xmm5,xmmword ptr [half_pi_ps]
							subps xmm5,xmm1
							movaps xmm3,xmm5
							divps xmm3,xmmword ptr [two_pi_ps]
							roundps xmm3,xmm3,0011b
							mulps xmm3,xmmword ptr [two_pi_ps]
							subps xmm5,xmm3
							andps xmm5,xmmword ptr [absMask_ps]        
							movaps xmm2,xmm5						;; xmm2 = x
							mulps xmm5,xmmword ptr [two_o_pi_ps]
							cvttps2dq xmm3,xmm5
							paddw xmm3,xmmword ptr [int_one]
							psrlw xmm3,1							;; xmm3
							cvtdq2ps xmm4,xmm3						;; xmm4 = 0,1,1,2
							pand xmm3,xmmword ptr [int_one]
							cvtdq2ps xmm3,xmm3
							xorps xmm3,xmmword ptr [minusMask_ps] 
							cvtps2dq xmm3,xmm3
							por xmm3,xmmword ptr [int_one]
							cvtdq2ps xmm6,xmm3						;; xmm6 = 1,-1

							mulps xmm4,xmmword ptr [pi_ps]
							subps xmm4,xmm2
							movaps xmm1,xmm4

							mulps xmm1,xmm1
							movaps xmm2,xmm1
							movaps xmm0,xmmword ptr [eax]
							divps xmm1,xmm0
							addps xmm7,xmm1
							mulps xmm1,xmm2
							movaps xmm0,xmmword ptr [eax+16]
							divps xmm1,xmm0
							addps xmm7,xmm1
							mulps xmm1,xmm2
							movaps xmm0,xmmword ptr [eax+32]
							divps xmm1,xmm0
							addps xmm7,xmm1
							mulps xmm1,xmm2
							movaps xmm0,xmmword ptr [eax+48]
							divps xmm1,xmm0
							addps xmm7,xmm1
						    mulps xmm1,xmm2
							movaps xmm0,xmmword ptr [eax+64]
							divps xmm1,xmm0
							addps xmm7,xmm1
							
							mulps xmm7,xmm6
							movaps xmmword ptr [edx],xmm7

							add ebx,16
							add edx,16
							sub ecx,4
							jnz @B

							mov eax,1

				Done:		pop ebx
							mov esp,ebp
							pop ebp
							ret
sin_sse_ps					endp
							end
