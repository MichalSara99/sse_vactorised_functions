								.model flat,c
								.const

								align 16
;; ======================================= packed single precision floating point for EXP =========================================

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

;; =========================================================== GENERAL ===========================================================
int_min_norm				dword	800000h,800000h,800000h,800000h
int_one						dword	0ffffffffh,0ffffffffh,0ffffffffh,0ffffffffh	
int_mantisa					dword	7f800000h,7f800000h,7f800000h,7f800000h
int_onetwoseven				dword	7fh,7fh,7fh,7fh

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
								end