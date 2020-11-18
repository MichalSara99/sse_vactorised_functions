								.model flat,c
								.const

								align 16
;; ======================================= packed single precision floating point for LOG =========================================

sqrthf_ps					real4	0.707106781186547524,0.707106781186547524,0.707106781186547524,0.707106781186547524
one_ps						real4   1.0,1.0,1.0,1.0
one_half_ps					real4	0.5,0.5,0.5,0.5

log_q1_ps					real4	-2.12194440e-4,-2.12194440e-4,-2.12194440e-4,-2.12194440e-4
log_q2_ps					real4	0.693359375,0.693359375,0.693359375,0.693359375

m_lcoef_ps					real4	7.0376836292e-2,7.0376836292e-2,7.0376836292e-2,7.0376836292e-2
							real4	-1.1514610310e-1,-1.1514610310e-1,-1.1514610310e-1,-1.1514610310e-1
							real4	1.1676998740e-1,1.1676998740e-1,1.1676998740e-1,1.1676998740e-1							
							real4	-1.2420140846e-1,-1.2420140846e-1,-1.2420140846e-1,-1.2420140846e-1
							real4	1.4249322787e-1,1.4249322787e-1,1.4249322787e-1,1.4249322787e-1
							real4	-1.6668057665e-1,-1.6668057665e-1,-1.6668057665e-1,-1.6668057665e-1
							real4	2.0000714765e-1,2.0000714765e-1,2.0000714765e-1,2.0000714765e-1
							real4	-2.4999993993e-1,-2.4999993993e-1,-2.4999993993e-1,-2.4999993993e-1
							real4	3.3333331174e-1,3.3333331174e-1,3.3333331174e-1,3.3333331174e-1

;; ======================================= packed double precision floating point for LOG =========================================

sqrthf_pd					real8	2.8853900817779268,2.8853900817779268
one_pd						real8   1.0,1.0

log_q_pd					real8	1.4426950408889634,1.4426950408889634

m_lcoef_pd					real8	0.3333333333333333,0.3333333333333333
							real8	0.2,0.2
							real8	0.14285714285714285,0.14285714285714285						
							real8	0.1111111111111111,0.1111111111111111

;; =========================================================== GENERAL ===========================================================
int_min_norm				dword	800000h,800000h,800000h,800000h
int_one						dword	0ffffffffh,0ffffffffh,0ffffffffh,0ffffffffh	
int_mantisa					dword	7f800000h,7f800000h,7f800000h,7f800000h
int_onetwoseven				dword	7fh,7fh,7fh,7fh
int_tentwothree				dword	3ffh,3ffh,3ffh,3ffh
int_sixfourtwozero			dword	0h,2h,4h,6h

qint_twentyfourseven		qword	7ffh,7ffh
qint_tentwothree			qword	3ffh,3ffh

								.code
;;			extern "C" bool log_sse_ps(float const* in_aligned_16, int n, float* out_aligned_16);

log_sse_ps						proc
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
								movaps xmm1,xmm0
								cmpps xmm1,xmm7,02h									;; inval_mask = xmm1
								
								maxps xmm0,xmmword ptr [int_min_norm]				;; x = xmm0
								movaps xmm2,xmm0									
								psrld xmm2,23										;; imm0 = xmm2

								movaps xmm3,xmmword ptr [int_mantisa]
								pandn xmm3,xmmword ptr [int_one]

								andps xmm0,xmm3
								orps xmm0,xmmword ptr [one_half_ps]

								psubd xmm2,xmmword ptr [int_onetwoseven]
								cvtdq2ps xmm3,xmm2									
								addps xmm3,xmmword ptr [one_ps]						;; e = xmm3

								movaps xmm4,xmm0
								cmpps xmm4,xmmword ptr [sqrthf_ps],01h				;; mask = xmm4
								movaps xmm5,xmm0
								andps xmm5,xmm4										;; tmp = xmm5

								subps xmm0,xmmword ptr [one_ps]
								andps xmm4,xmmword ptr [one_ps]
								subps xmm3,xmm4
								addps xmm0,xmm5

								movaps xmm2,xmm0
								mulps xmm2,xmm2										;; z = xmm2
								movaps xmm4,xmmword ptr [m_lcoef_ps]				;; y = xmm4

								mulps xmm4,xmm0
								addps xmm4,xmmword ptr [m_lcoef_ps + 16]
								mulps xmm4,xmm0
								addps xmm4,xmmword ptr [m_lcoef_ps + 32]
								mulps xmm4,xmm0
								addps xmm4,xmmword ptr [m_lcoef_ps + 48]
								mulps xmm4,xmm0
								addps xmm4,xmmword ptr [m_lcoef_ps + 64]
								mulps xmm4,xmm0
								addps xmm4,xmmword ptr [m_lcoef_ps + 80]
								mulps xmm4,xmm0
								addps xmm4,xmmword ptr [m_lcoef_ps + 96]
								mulps xmm4,xmm0
								addps xmm4,xmmword ptr [m_lcoef_ps + 112]
								mulps xmm4,xmm0
								addps xmm4,xmmword ptr [m_lcoef_ps + 128]
								mulps xmm4,xmm0
								mulps xmm4,xmm2

								movaps xmm5,xmm3
								mulps xmm5,xmmword ptr [log_q1_ps]
								addps xmm4,xmm5

								movaps xmm5,xmm2
								mulps xmm5,xmmword ptr [one_half_ps]
								subps xmm4,xmm5

								movaps xmm5,xmm3
								mulps xmm5,xmmword ptr [log_q2_ps]
								addps xmm0,xmm4
								addps xmm0,xmm5
								orps xmm0,xmm1

								movaps xmmword ptr [edx],xmm0

								add ebx,16
								add edx,16
								sub ecx,4
								jnz @B

								mov eax,1

					Done:		pop ebx
								mov esp,ebp
								pop ebp
								ret
log_sse_ps						endp

;;			extern "C" bool log_sse_pd(double const* x, int n, double* out);

log_sse_pd						proc
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

								xorpd xmm7,xmm7
								xorpd xmm6,xmm6

								movdqa xmm7,xmmword ptr [qint_twentyfourseven]
								psllq xmm7,52
								movdqa xmm6,xmmword ptr [qint_tentwothree]
								psllq xmm6,52

					   @@:		movapd xmm0,xmmword ptr [ebx]
								movapd xmm1,xmm0

								xorpd xmm5,xmm5
								cmplepd xmm1,xmm5									;; neg_mask = xmm1

								movdqa xmm2,xmm7
								pand xmm2,xmm0
								psrlq xmm2,52										;; exps64 = xmm2
								movdqa xmm3,xmmword ptr [int_sixfourtwozero]		;; gTo32bitExp = xmm3

								vpermilps xmm3,xmm2,xmm3							
								movdqa xmm4,xmmword ptr [int_tentwothree]
								psubd xmm3,xmm4
								cvtdq2pd xmm3,xmm3									;; expsPD = xmm3

								movapd xmm5,xmm7
								andnpd xmm5,xmm0
								orpd xmm5,xmm6										;; y = xmm5

								movapd xmm2,xmm5
								subpd xmm5,xmmword ptr [one_pd]
								addpd xmm2,xmmword ptr [one_pd]

								divpd xmm5,xmm2										;; t = xmm5
								movapd xmm2,xmm5
								mulpd xmm2,xmm2										;; t2 = xmm2

								movapd xmm4,xmm5
								mulpd xmm4,xmm2										;; t3 = xmm4
								movapd xmm0,xmmword ptr [m_lcoef_pd]
								vfmadd213pd xmm0,xmm4,xmm5							
								movapd xmm5,xmm0									;; terms01 = xmm5
								mulpd xmm4,xmm2										;; t5 = xmm4

								movapd xmm0,xmmword ptr [m_lcoef_pd + 16]
								vfmadd213pd xmm0,xmm4,xmm5							
								movapd xmm5,xmm0									;; terms012 = xmm5
								mulpd xmm4,xmm2										;; t7 = xmm4

								movapd xmm0,xmmword ptr [m_lcoef_pd + 32]
								vfmadd213pd xmm0,xmm4,xmm5
								movapd xmm5,xmm0									;; terms0123 = xmm5
								mulpd xmm4,xmm2										;; t9 = xmm4

								movapd xmm0,xmmword ptr [m_lcoef_pd + 48]
								vfmadd213pd xmm0,xmm4,xmm5
								movapd xmm5,xmm0									;; terms01234 = xmm5

								mulpd xmm5,xmmword ptr [sqrthf_pd]
								addpd xmm5,xmm3
								divpd xmm5,xmmword ptr [log_q_pd]
								orpd xmm5,xmm1

								movapd xmmword ptr [edx],xmm5

								add ebx,16
								add edx,16
								sub ecx,2
								jnz @B

								mov eax,1

					Done:		pop ebx
								mov esp,ebp
								pop ebp
								ret
log_sse_pd						endp
								end