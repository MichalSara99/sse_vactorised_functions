							.model flat,c
							.const
							align 16
two_o_pi					real8   0.6366197723675813430755350,0.6366197723675813430755350
pi							real8   3.1415926535897932384626433,3.1415926535897932384626433
two_pi						real8	6.2831853071795864769252866,6.2831853071795864769252866
one							real8   1.0,1.0
m_two						real8  -2.0,-2.0
m_twelve					real8  -12.0,-12.0
m_thirty					real8  -30.0,-30.0
m_fiftysix					real8  -56.0,-56.0
m_ninty						real8  -90.0,-90.0
m_onethirtytwo				real8  -132.0,-132.0
absMask						qword   7fffffffffffffffh,7fffffffffffffffh
minusMask					qword   8000000000000000h,8000000000000000h
int_one						dword	1h,1h,1h,1h
							.code
;;		extern "C" bool pcos_sse_(double const* x, int n, double* out);

pcos_sse_					proc
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

							mov eax,ecx
							and ecx,0fffffffeh

							xorpd xmm7,xmm7

					@@:		movapd xmm7,xmmword ptr [one]
							movapd xmm1,xmmword ptr [ebx]
							movapd xmm3,xmm1
							divpd xmm3,xmmword ptr [two_pi]
							roundpd xmm3,xmm3,0011b
							mulpd xmm3,xmmword ptr [two_pi]
							subpd xmm1,xmm3
							andpd xmm1,xmmword ptr [absMask]        
							movapd xmm2,xmm1						;; xmm2 = x
							mulpd xmm1,xmmword ptr [two_o_pi]
							cvttpd2dq xmm3,xmm1
							paddw xmm3,xmmword ptr [int_one]
							psrlw xmm3,1							;; xmm3
							cvtdq2pd xmm4,xmm3						;; xmm4 = 0,1,1,2
							pand xmm3,xmmword ptr [int_one]
							cvtdq2pd xmm3,xmm3
							xorpd xmm3,xmmword ptr [minusMask] 
							cvtpd2dq xmm3,xmm3
							por xmm3,xmmword ptr [int_one]
							cvtdq2pd xmm6,xmm3						;; xmm6 = 1,-1

							mulpd xmm4,xmmword ptr [pi]
							subpd xmm4,xmm2
							movapd xmm1,xmm4

							mulpd xmm1,xmm1
							movapd xmm2,xmm1
							movapd xmm0,xmmword ptr [m_two]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							mulpd xmm1,xmm2
							movapd xmm0,xmmword ptr [m_twelve]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							mulpd xmm1,xmm2
							movapd xmm0,xmmword ptr [m_thirty]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							mulpd xmm1,xmm2
							movapd xmm0,xmmword ptr [m_fiftysix]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
						    mulpd xmm1,xmm2
							movapd xmm0,xmmword ptr [m_ninty]
							divpd xmm1,xmm0
							addpd xmm7,xmm1
							mulpd xmm1,xmm2
						    movapd xmm0,xmmword ptr [m_onethirtytwo]
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
pcos_sse_					endp


							end
