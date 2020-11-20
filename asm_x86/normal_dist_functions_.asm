							.model flat,c
							.const
							align 16

;; ======================================= packed double precision floating point for EXP =========================================

log2e_pd					real8	1.44269504088896341,1.44269504088896341
one_pd						real8   1.0,1.0

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

one_o_sqrttwopi_pd			real8	0.39894228040143287,0.39894228040143287
poly_pd						real8	0.226,0.226
							real8	0.64,0.64
							real8	0.33,0.33
							real8	3.0,3.0
;; ======================================= packed single precision floating point for EXP =========================================

log2e_ps					real4	1.442695041,1.442695041,1.442695041,1.442695041
one_ps						real4   1.0,1.0,1.0,1.0

c1_ps						real4	0.693359375,0.693359375,0.693359375,0.693359375
c2_ps						real4	-2.12194440e-4,-2.12194440e-4,-2.12194440e-4,-2.12194440e-4

m_ecoef_ps					real4	1.9875691500e-4,1.9875691500e-4,1.9875691500e-4,1.9875691500e-4
							real4	1.3981999507e-3,1.3981999507e-3,1.3981999507e-3,1.3981999507e-3
							real4	8.3334519073e-3,8.3334519073e-3,8.3334519073e-3,8.3334519073e-3
							real4	4.1665795894e-2,4.1665795894e-2,4.1665795894e-2,4.1665795894e-2
							real4	1.6666665459e-1,1.6666665459e-1,1.6666665459e-1,1.6666665459e-1
							real4	5.0000001201e-1,5.0000001201e-1,5.0000001201e-1,5.0000001201e-1
plus_0p5_ps					real4	0.5,0.5,0.5,0.5
minus_0p5_ps				real4	-0.5,-0.5,-0.5,-0.5
one_o_sqrttwopi_ps			real4	0.3989422804014,0.3989422804014,0.3989422804014,0.3989422804014
poly_ps						real4	0.226,0.226,0.226,0.226
							real4	0.64,0.64,0.64,0.64
							real4	0.33,0.33,0.33,0.33
							real4	3.0,3.0,3.0,3.0
;; =========================================================== GENERAL ===========================================================
int_tentwothree				dword	3ffh,3ffh,3ffh,3ffh
int_onetwoseven				dword	7fh,7fh,7fh,7fh
int_float_abs_mask_ps		dword	7fffffffh,7fffffffh,7fffffffh,7fffffffh
int_double_abs_mask_pd		qword	7fffffffffffffffh,7fffffffffffffffh

							.code

;;		extern "C" bool norm_cdf_sse_ps(float const* x, int n, float* out);
norm_cdf_sse_ps				proc
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
							xorps xmm7,xmm7

				  @@:		movaps xmm0,xmmword ptr [ebx]						;; x = xmm0

							movaps xmm6,xmm0
							cmpltps xmm6,xmm7								
							cvtdq2ps xmm6,xmm6									;; ind = xmm6
							andps xmm6,xmmword ptr [int_float_abs_mask_ps]		;; x = xmm0
							andps xmm0,xmmword ptr [int_float_abs_mask_ps]
							movaps xmm1,xmm0
							mulps xmm1,xmm1									;; x*x = xmm1

							movaps xmm5,xmmword ptr [poly_ps + 48]
							addps xmm5,xmm1
							sqrtps xmm5,xmm5
							mulps xmm5,xmmword ptr [poly_ps + 32]
							addps xmm5,xmmword ptr [poly_ps]
							movaps xmm3,xmm0
							mulps xmm3,xmmword ptr [poly_ps + 16]
							addps xmm5,xmm3

							movaps xmm0,xmm1
							mulps xmm0,xmmword ptr [minus_0p5_ps]

							movaps xmm1,xmm0							
							mulps xmm1,xmmword ptr [log2e_ps]			
							addps xmm1,xmmword ptr [plus_0p5_ps]			;; fx = xmm1
							roundps xmm2,xmm1,0001b							;; tmp = xmm2
							movaps xmm3,xmm2
							cmpps xmm3,xmm1,0eh							
							andps xmm3,xmmword ptr [one_ps]					;; mask = xmm3
							movaps xmm4,xmm2
							subps xmm4,xmm3									;; fx = xmm4
							movaps xmm1,xmm4
							mulps xmm1,xmmword ptr [c1_ps]					;; tmp = xmm1
							movaps xmm2,xmm4
							mulps xmm2,xmmword ptr [c2_ps]					;; z = xmm2
							subps xmm0,xmm1									;; x = xmm0
							subps xmm0,xmm2
							movaps xmm2,xmm0
							mulps xmm2,xmm2									;; z = xmm2

							movaps xmm1,xmmword ptr [m_ecoef_ps]			;; y = xmm1
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
							addps xmm1,xmmword ptr [one_ps]

							cvttps2dq xmm3,xmm4
							paddd xmm3,xmmword ptr [int_onetwoseven]
							pslld xmm3,23
							mulps xmm3,xmm1

							divps xmm3,xmm5
							mulps xmm3,xmmword ptr [one_o_sqrttwopi_ps]
							movaps xmm4,xmmword ptr [one_ps]
							subps xmm4,xmm3
							subps xmm6,xmm4
							andps xmm6,xmmword ptr [int_float_abs_mask_ps]
							movaps xmmword ptr [edx],xmm6
							
							add ebx,16
							add edx,16
							sub ecx,4
							jnz @B

							mov eax,1

				Done:		pop ebx
							mov esp,ebp
							pop ebp
							ret
norm_cdf_sse_ps				endp
							end