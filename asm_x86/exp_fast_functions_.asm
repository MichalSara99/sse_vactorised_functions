							.model flat,c
							.const
							align 16
;; ======================================= Double-precision floating-point constants =========================================
log2e_pd					real8	1.44269504088896341,1.44269504088896341

c1_pd						real8	6.93145751953125e-1,6.93145751953125e-1
c2_pd						real8	1.42860682030941723212e-6,1.42860682030941723212e-6

m_ecoef_pd					real8	8.43303738444730998138e-3,8.43303738444730998138e-3
							real8	4.21902068347366333044e-2,4.21902068347366333044e-2
							real8	0.16665184176328485367,0.16665184176328485367
							real8	0.49995083513496057406,0.49995083513496057406
							real8	1.00000058571014555295,1.00000058571014555295
							real8	1.00000068337676053288,1.00000068337676053288
tentwothree					real8	1023.0,1023.0
one_pd						real8   1.0,1.0
;;	====================================== Single-precision floating-point constants ==========================================
log2e_ps					real4	1.442695041,1.442695041,1.442695041,1.442695041

c0_ps						real4	0.3371894346,0.3371894346,0.3371894346,0.3371894346
c1_ps						real4	0.657636276,0.657636276,0.657636276,0.657636276
c2_ps						real4	1.00172476,1.00172476,1.00172476,1.00172476
;;	==================================================== GENERAL ==============================================================
int_tentwothree				dword	3ffh,3ffh,3ffh,3ffh

							.code
;;		extern "C" bool exp_fast_sse_ps(float const* x, int n, float* out);
exp_fast_sse_ps				proc
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

				 @@:		movaps xmm0,xmmword ptr [ebx]			;; x = xmm0	(ps)	
							mulps xmm0,xmmword ptr [log2e_ps]		;; t = xmm0
							roundps xmm1,xmm0,0001b					;; e = xmm1	(ps)
							cvtps2dq xmm2,xmm1						;; i = xmm2 (int)
							subps xmm0,xmm1							;; f = xmm0

							movaps xmm1,xmmword ptr [c0_ps]
							mulps xmm1,xmm0
							addps xmm1,xmmword ptr [c1_ps]
							mulps xmm1,xmm0
							addps xmm1,xmmword ptr [c2_ps]			;; p = xmm1
							pslld xmm2,23
							paddd xmm2,xmm1
							movaps xmmword ptr [edx],xmm2
							
							add ebx,16
							add edx,16
							sub ecx,4
							jnz @B
								
							mov eax,1

				Done:		pop ebx
							mov esp,ebp
							pop ebp
							ret
exp_fast_sse_ps				endp

;;		extern "C" bool exp_fast_sse_pd(double const* x, int n, double* out);
exp_fast_sse_pd				proc
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
							movapd xmm1,xmmword ptr [log2e_pd]
							mulpd xmm1,xmm0							;; a = xmm1
							movapd xmm2,xmm1						;; a = xmm2
							xorpd xmm7,xmm7
							cmpltpd xmm2, xmm7
							movapd xmm6,xmmword ptr [one_pd]
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

							paddd xmm7,xmmword ptr [int_tentwothree]
							pslld xmm7,20
							pshufd xmm7, xmm7, 01110010b
							mulpd xmm6,xmm7

							movapd xmmword ptr [edx],xmm6
							
							add ebx,16
							add edx,16
							sub ecx,2
							jnz @B
								
							mov eax,1

				Done:		pop ebx
							mov esp,ebp
							pop ebp
							ret
exp_fast_sse_pd				endp
							end
						