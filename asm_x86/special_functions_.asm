							.model flat,c
							.const
							align 16

;; ======================================= packed double precision floating point for ERFC =========================================

log2e_pd					real8	1.44269504088896341,1.44269504088896341
plus_1_pd					real8   1.0,1.0

c1_pd						real8	6.93145751953125e-1,6.93145751953125e-1
c2_pd						real8	1.42860682030941723212e-6,1.42860682030941723212e-6

m_ecoef_pd					real8	2.51929868958558990100e-8,2.51929868958558990100e-8
							real8	2.77143029724764708572e-7,2.77143029724764708572e-7
							real8	2.75568408339931215724e-6,2.75568408339931215724e-6							
							real8	2.48011454027599465130e-5,2.48011454027599465130e-5
							real8	1.98412706284313544001e-4,1.98412706284313544001e-4
							real8	1.38888894619673011407e-3,1.38888894619673011407e-3
							real8	8.33333333269606253027e-3,8.33333333269606253027e-3
							real8	4.16666666633079258298e-2,4.16666666633079258298e-2
							real8	0.16666666666668912253462,0.16666666666668912253462
							real8	0.50000000000007198509320,0.50000000000007198509320
							real8	0.99999999999999976925988,0.99999999999999976925988
							real8	0.99999999999999975002240,0.99999999999999975002240
tentwothree					real8	1023.0,1023.0
plus_a_pd					real8	2.7889,2.7889
plus_a_m_1_pd				real8	1.7889,1.7889
plus_pi_pd					real8	3.14159265358979323846264,3.14159265358979323846264
minus_1_pd					real8	-1.0,-1.0
;; ======================================= packed single precision floating point for ERFC =========================================

log2e_ps					real4	1.442695041,1.442695041,1.442695041,1.442695041
plus_1_ps					real4   1.0,1.0,1.0,1.0

c1_ps						real4	0.693359375,0.693359375,0.693359375,0.693359375
c2_ps						real4	-2.12194440e-4,-2.12194440e-4,-2.12194440e-4,-2.12194440e-4

m_ecoef_ps					real4	1.9875691500e-4,1.9875691500e-4,1.9875691500e-4,1.9875691500e-4
							real4	1.3981999507e-3,1.3981999507e-3,1.3981999507e-3,1.3981999507e-3
							real4	8.3334519073e-3,8.3334519073e-3,8.3334519073e-3,8.3334519073e-3
							real4	4.1665795894e-2,4.1665795894e-2,4.1665795894e-2,4.1665795894e-2
							real4	1.6666665459e-1,1.6666665459e-1,1.6666665459e-1,1.6666665459e-1
							real4	5.0000001201e-1,5.0000001201e-1,5.0000001201e-1,5.0000001201e-1
zero_point_five				real4	0.5,0.5,0.5,0.5
plus_a_ps					real4	2.7889,2.7889,2.7889,2.7889
plus_a_m_1_ps				real4	1.7889,1.7889,1.7889,1.7889
plus_pi_ps					real4	3.1415926535897,3.1415926535897,3.1415926535897,3.1415926535897
minus_1_ps					real4	-1.0,-1.0,-1.0,-1.0
;; =========================================================== GENERAL ===========================================================
int_tentwothree				dword	3ffh,3ffh,3ffh,3ffh
int_onetwoseven				dword	7fh,7fh,7fh,7fh

							.code

;;		extern "C" bool erfc_sse_pd(double const* x, int n, double* out);
erfc_sse_pd					proc
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

				 @@:		movapd xmm0,xmmword ptr [ebx]			;; x = xmm0
							mulpd xmm0,xmm0
							movapd xmm5,xmm0
							mulpd xmm0,xmmword ptr [minus_1_pd]
							movapd xmm1,xmmword ptr [log2e_pd]
							mulpd xmm1,xmm0							;; a = xmm1
							movapd xmm2,xmm1						;; a = xmm2
							xorpd xmm7,xmm7
							cmpltpd xmm2, xmm7
							movapd xmm6,xmmword ptr [plus_1_pd]
							andpd xmm2,xmm6							;; p = xmm2
							subpd xmm1,xmm2							;; a = xmm1
							cvttpd2dq xmm7, xmm1					;; k = xmm7
							cvtdq2pd xmm2, xmm7						;; p = xmm2

							movapd xmm3,xmmword ptr [c1_pd]
							movapd xmm4,xmmword ptr [c2_pd]
							movapd xmm6,xmm2

							mulpd xmm6,xmm3							;; a = xmm6
							subpd xmm0,xmm6							;; x = xmm0
							movapd xmm6,xmm2

							mulpd xmm6,xmm4							;; a = xmm6
							subpd xmm0,xmm6							;; x = xmm0

							movapd xmm3,xmmword ptr [m_ecoef_pd]
							movapd xmm4,xmmword ptr [m_ecoef_pd + 16]
							movapd xmm6,xmm0
							mulpd xmm6,xmm3
							addpd xmm6,xmm4							;; a = xmm6

							movapd xmm3,xmmword ptr [m_ecoef_pd + 32]
							movapd xmm4,xmmword ptr [m_ecoef_pd + 48]
							mulpd xmm6,xmm0
							addpd xmm6,xmm3
							mulpd xmm6,xmm0
							addpd xmm6,xmm4							;; a = xmm6	

							movapd xmm3,xmmword ptr [m_ecoef_pd + 64]
							movapd xmm4,xmmword ptr [m_ecoef_pd + 80]
							mulpd xmm6,xmm0
							addpd xmm6,xmm3
							mulpd xmm6,xmm0
							addpd xmm6,xmm4							;; a = xmm6	

							movapd xmm3,xmmword ptr [m_ecoef_pd + 96]
							movapd xmm4,xmmword ptr [m_ecoef_pd + 112]
							mulpd xmm6,xmm0
							addpd xmm6,xmm3
							mulpd xmm6,xmm0
							addpd xmm6,xmm4							;; a = xmm6	

							movapd xmm3,xmmword ptr [m_ecoef_pd + 128]
							movapd xmm4,xmmword ptr [m_ecoef_pd + 144]
							mulpd xmm6,xmm0
							addpd xmm6,xmm3
							mulpd xmm6,xmm0
							addpd xmm6,xmm4							;; a = xmm6	

							movapd xmm3,xmmword ptr [m_ecoef_pd + 160]
							movapd xmm4,xmmword ptr [m_ecoef_pd + 176]
							mulpd xmm6,xmm0
							addpd xmm6,xmm3
							mulpd xmm6,xmm0
							addpd xmm6,xmm4							;; a = xmm6	

							paddd xmm7,xmmword ptr [int_tentwothree]
							pslld xmm7,20
							pshufd xmm7, xmm7, 01110010b
							mulpd xmm6,xmm7

							mulpd xmm5,xmmword ptr [plus_pi_pd]
							movapd xmm0,xmm5
							movapd xmm1,xmmword ptr [plus_a_pd]
							mulpd xmm1,xmm1
							addpd xmm0,xmm1
							sqrtpd xmm0,xmm0
							sqrtpd xmm5,xmm5
							mulpd xmm5,xmmword ptr [plus_a_m_1_pd]
							addpd xmm5,xmm0
							movapd xmm0,xmmword ptr [plus_a_pd]
							divpd xmm0,xmm5
							mulpd xmm0,xmm6

							movapd xmmword ptr [edx],xmm0
							
							add ebx,16
							add edx,16
							sub ecx,2
							jnz @B
								
							mov eax,1

				Done:		pop ebx
							mov esp,ebp
							pop ebp
							ret
erfc_sse_pd					endp

;;		extern "C" bool erfc_sse_ps(float const* x, int n, float * out);
erfc_sse_ps					proc
							push ebp
							mov ebp,esp
							push ebx

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

				  @@:		movaps xmm0,xmmword ptr [ebx]				;; x = xmm0

				  			mulps xmm0,xmm0
							movaps xmm5,xmm0
							mulps xmm0,xmmword ptr [minus_1_ps]
							movaps xmm1,xmm0							
							mulps xmm1,xmmword ptr [log2e_ps]			
							addps xmm1,xmmword ptr [zero_point_five]	;; fx = xmm1
							roundps xmm2,xmm1,0001b						;; tmp = xmm2
							movaps xmm3,xmm2
							cmpps xmm3,xmm1,0eh							
							andps xmm3,xmmword ptr [plus_1_ps]				;; mask = xmm3
							movaps xmm4,xmm2
							subps xmm4,xmm3								;; fx = xmm4
							movaps xmm1,xmm4
							mulps xmm1,xmmword ptr [c1_ps]				;; tmp = xmm1
							movaps xmm2,xmm4
							mulps xmm2,xmmword ptr [c2_ps]				;; z = xmm2
							subps xmm0,xmm1								;; x = xmm0
							subps xmm0,xmm2
							movaps xmm2,xmm0
							mulps xmm2,xmm2								;; z = xmm2

							movaps xmm1,xmmword ptr [m_ecoef_ps]		;; y = xmm1
							mulps xmm1,xmm0
							addps xmm1,xmmword ptr [m_ecoef_ps + 16]
							mulps xmm1,xmm0
							addps xmm1,xmmword ptr [m_ecoef_ps + 32]
							mulps xmm1,xmm0
							addps xmm1,xmmword ptr [m_ecoef_ps + 48]
							mulps xmm1,xmm0
							addps xmm1,xmmword ptr [m_ecoef_ps + 64]
							mulps xmm1,xmm0
							addps xmm1,xmmword ptr [m_ecoef_ps + 80]
							mulps xmm1,xmm2
							addps xmm1,xmm0
							addps xmm1,xmmword ptr [plus_1_ps]

							cvttps2dq xmm3,xmm4
							paddd xmm3,xmmword ptr [int_onetwoseven]
							pslld xmm3,23
							mulps xmm3,xmm1

							mulps xmm5,xmmword ptr [plus_pi_ps]
							movaps xmm0,xmm5
							movaps xmm1,xmmword ptr [plus_a_ps]
							mulps xmm1,xmm1
							addps xmm0,xmm1
							sqrtps xmm0,xmm0
							sqrtps xmm5,xmm5
							mulps xmm5,xmmword ptr [plus_a_m_1_ps]
							addps xmm5,xmm0
							movaps xmm0,xmmword ptr [plus_a_ps]
							divps xmm0,xmm5
							mulps xmm0,xmm3

							movaps xmmword ptr [edx],xmm0
							
							add ebx,16
							add edx,16
							sub ecx,4
							jnz @B

				Done:		pop ebx
							mov esp,ebp
							pop ebp
							ret
erfc_sse_ps					endp

;;		extern "C" bool erf_sse_pd(double const* x, int n, double* out);
erf_sse_pd					proc
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

				 @@:		movapd xmm0,xmmword ptr [ebx]			;; x = xmm0
							mulpd xmm0,xmm0
							movapd xmm5,xmm0
							mulpd xmm0,xmmword ptr [minus_1_pd]
							movapd xmm1,xmmword ptr [log2e_pd]
							mulpd xmm1,xmm0							;; a = xmm1
							movapd xmm2,xmm1						;; a = xmm2
							xorpd xmm7,xmm7
							cmpltpd xmm2, xmm7
							movapd xmm6,xmmword ptr [plus_1_pd]
							andpd xmm2,xmm6							;; p = xmm2
							subpd xmm1,xmm2							;; a = xmm1
							cvttpd2dq xmm7, xmm1					;; k = xmm7
							cvtdq2pd xmm2, xmm7						;; p = xmm2

							movapd xmm3,xmmword ptr [c1_pd]
							movapd xmm4,xmmword ptr [c2_pd]
							movapd xmm6,xmm2

							mulpd xmm6,xmm3							;; a = xmm6
							subpd xmm0,xmm6							;; x = xmm0
							movapd xmm6,xmm2

							mulpd xmm6,xmm4							;; a = xmm6
							subpd xmm0,xmm6							;; x = xmm0

							movapd xmm3,xmmword ptr [m_ecoef_pd]
							movapd xmm4,xmmword ptr [m_ecoef_pd + 16]
							movapd xmm6,xmm0
							mulpd xmm6,xmm3
							addpd xmm6,xmm4							;; a = xmm6

							movapd xmm3,xmmword ptr [m_ecoef_pd + 32]
							movapd xmm4,xmmword ptr [m_ecoef_pd + 48]
							mulpd xmm6,xmm0
							addpd xmm6,xmm3
							mulpd xmm6,xmm0
							addpd xmm6,xmm4							;; a = xmm6	

							movapd xmm3,xmmword ptr [m_ecoef_pd + 64]
							movapd xmm4,xmmword ptr [m_ecoef_pd + 80]
							mulpd xmm6,xmm0
							addpd xmm6,xmm3
							mulpd xmm6,xmm0
							addpd xmm6,xmm4							;; a = xmm6	

							movapd xmm3,xmmword ptr [m_ecoef_pd + 96]
							movapd xmm4,xmmword ptr [m_ecoef_pd + 112]
							mulpd xmm6,xmm0
							addpd xmm6,xmm3
							mulpd xmm6,xmm0
							addpd xmm6,xmm4							;; a = xmm6	

							movapd xmm3,xmmword ptr [m_ecoef_pd + 128]
							movapd xmm4,xmmword ptr [m_ecoef_pd + 144]
							mulpd xmm6,xmm0
							addpd xmm6,xmm3
							mulpd xmm6,xmm0
							addpd xmm6,xmm4							;; a = xmm6	

							movapd xmm3,xmmword ptr [m_ecoef_pd + 160]
							movapd xmm4,xmmword ptr [m_ecoef_pd + 176]
							mulpd xmm6,xmm0
							addpd xmm6,xmm3
							mulpd xmm6,xmm0
							addpd xmm6,xmm4							;; a = xmm6	

							paddd xmm7,xmmword ptr [int_tentwothree]
							pslld xmm7,20
							pshufd xmm7, xmm7, 01110010b
							mulpd xmm6,xmm7

							mulpd xmm5,xmmword ptr [plus_pi_pd]
							movapd xmm0,xmm5
							movapd xmm1,xmmword ptr [plus_a_pd]
							mulpd xmm1,xmm1
							addpd xmm0,xmm1
							sqrtpd xmm0,xmm0
							sqrtpd xmm5,xmm5
							mulpd xmm5,xmmword ptr [plus_a_m_1_pd]
							addpd xmm5,xmm0
							movapd xmm0,xmmword ptr [plus_a_pd]
							divpd xmm0,xmm5
							mulpd xmm0,xmm6

							movapd xmm1,xmmword ptr [plus_1_pd]
							subpd xmm1,xmm0
							movapd xmmword ptr [edx],xmm1
							
							add ebx,16
							add edx,16
							sub ecx,2
							jnz @B
								
							mov eax,1

				Done:		pop ebx
							mov esp,ebp
							pop ebp
							ret
erf_sse_pd					endp

;;		extern "C" bool erf_sse_ps(float const* x, int n, float * out);
erf_sse_ps					proc
							push ebp
							mov ebp,esp
							push ebx

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

				  @@:		movaps xmm0,xmmword ptr [ebx]				;; x = xmm0

				  			mulps xmm0,xmm0
							movaps xmm5,xmm0
							mulps xmm0,xmmword ptr [minus_1_ps]
							movaps xmm1,xmm0							
							mulps xmm1,xmmword ptr [log2e_ps]			
							addps xmm1,xmmword ptr [zero_point_five]	;; fx = xmm1
							roundps xmm2,xmm1,0001b						;; tmp = xmm2
							movaps xmm3,xmm2
							cmpps xmm3,xmm1,0eh							
							andps xmm3,xmmword ptr [plus_1_ps]				;; mask = xmm3
							movaps xmm4,xmm2
							subps xmm4,xmm3								;; fx = xmm4
							movaps xmm1,xmm4
							mulps xmm1,xmmword ptr [c1_ps]				;; tmp = xmm1
							movaps xmm2,xmm4
							mulps xmm2,xmmword ptr [c2_ps]				;; z = xmm2
							subps xmm0,xmm1								;; x = xmm0
							subps xmm0,xmm2
							movaps xmm2,xmm0
							mulps xmm2,xmm2								;; z = xmm2

							movaps xmm1,xmmword ptr [m_ecoef_ps]		;; y = xmm1
							mulps xmm1,xmm0
							addps xmm1,xmmword ptr [m_ecoef_ps + 16]
							mulps xmm1,xmm0
							addps xmm1,xmmword ptr [m_ecoef_ps + 32]
							mulps xmm1,xmm0
							addps xmm1,xmmword ptr [m_ecoef_ps + 48]
							mulps xmm1,xmm0
							addps xmm1,xmmword ptr [m_ecoef_ps + 64]
							mulps xmm1,xmm0
							addps xmm1,xmmword ptr [m_ecoef_ps + 80]
							mulps xmm1,xmm2
							addps xmm1,xmm0
							addps xmm1,xmmword ptr [plus_1_ps]

							cvttps2dq xmm3,xmm4
							paddd xmm3,xmmword ptr [int_onetwoseven]
							pslld xmm3,23
							mulps xmm3,xmm1

							mulps xmm5,xmmword ptr [plus_pi_ps]
							movaps xmm0,xmm5
							movaps xmm1,xmmword ptr [plus_a_ps]
							mulps xmm1,xmm1
							addps xmm0,xmm1
							sqrtps xmm0,xmm0
							sqrtps xmm5,xmm5
							mulps xmm5,xmmword ptr [plus_a_m_1_ps]
							addps xmm5,xmm0
							movaps xmm0,xmmword ptr [plus_a_ps]
							divps xmm0,xmm5
							mulps xmm0,xmm3

							movaps xmm1,xmmword ptr [plus_1_ps]
							subps xmm1,xmm0
							movaps xmmword ptr [edx],xmm1
							
							add ebx,16
							add edx,16
							sub ecx,4
							jnz @B

				Done:		pop ebx
							mov esp,ebp
							pop ebp
							ret
erf_sse_ps					endp
							end
