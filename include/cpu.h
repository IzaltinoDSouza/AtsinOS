#pragma once

#include <types.h>
#include <log.h>

typedef enum
{
	FPU_FEATURE       = 0b00000000000000000000000000000001,
	VME_FEATURE       = 0b00000000000000000000000000000010,
	DE_FEATURE        = 0b00000000000000000000000000000100,
	PSE_FEATURE       = 0b00000000000000000000000000001000,
	TSC_FEATURE       = 0b00000000000000000000000000010000,
	MSR_FEATURE       = 0b00000000000000000000000000100000,
	PAE_FEATURE       = 0b00000000000000000000000001000000,
	MCE_FEATURE       = 0b00000000000000000000000010000000,
	CX_FEATURE        = 0b00000000000000000000000100000000,
	APIC_FEATURE      = 0b00000000000000000000001000000000,
	//RESERVED0_FEATURE = 0b00000000000000000000010000000000,
	SEP_FEATURE       = 0b00000000000000000000100000000000,
	MTRR_FEATURE      = 0b00000000000000000001000000000000,
	PGE_FEATURE       = 0b00000000000000000010000000000000,
	MCA_FEATURE       = 0b00000000000000000100000000000000,
	CMOV_FEATURE      = 0b00000000000000001000000000000000,
	PAT_FEATURE       = 0b00000000000000010000000000000000,
	PSE36_FEATURE     = 0b00000000000000100000000000000000,
	PSN_FEATURE       = 0b00000000000001000000000000000000,
	CLFSH_FEATURE     = 0b00000000000010000000000000000000,
	//RESERVED1_FEATURE = 0b00000000000100000000000000000000,
	DS_FEATURE        = 0b00000000001000000000000000000000,
	ACPI_FEATURE      = 0b00000000010000000000000000000000,
	MMX_FEATURE       = 0b00000000100000000000000000000000,
	FXSR_FEATURE      = 0b00000001000000000000000000000000,
	SSE_FEATURE       = 0b00000010000000000000000000000000,
	SSE2_FEATURE      = 0b00000100000000000000000000000000,
	SS_FEATURE        = 0b00001000000000000000000000000000,
	HTT_FEATURE       = 0b00010000000000000000000000000000,
	TM_FEATURE        = 0b00100000000000000000000000000000,
	//RESERVED2_FEATURE = 0b01000000000000000000000000000000,
	PBE_FEATURE       = 0b10000000000000000000000000000000,
}CPU_EDX_FEATURES_BITS;

typedef enum
{
  SSE3_FEATURE         = 0b00000000000000000000000000000001,
  PCLMULQDQ_FEATURE    = 0b00000000000000000000000000000010,
  DTES64_FEATURE       = 0b00000000000000000000000000000100,
  MONITOR_FEATURE      = 0b00000000000000000000000000001000,
  DS_CPL_FEATURE       = 0b00000000000000000000000000010000,
  VMX_FEATURE          = 0b00000000000000000000000000100000,
  SMX_FEATURE          = 0b00000000000000000000000001000000,
  EIST_FEATURE         = 0b00000000000000000000000010000000,
  TM2_FEATURE          = 0b00000000000000000000000100000000,
  SSSE3_FEATURE        = 0b00000000000000000000001000000000,
  CNXT_ID_FEATURE      = 0b00000000000000000000010000000000,
  SDBG_FEATURE         = 0b00000000000000000000100000000000,
  FMA_FEATURE          = 0b00000000000000000001000000000000,
  CMPXCHG16_FEATURE    = 0b00000000000000000010000000000000,
  xTPR_FEATURE         = 0b00000000000000000100000000000000,
  PDCM_FEATURE         = 0b00000000000000001000000000000000,
  //RESERVED1_FEATURE    = 0b00000000000000010000000000000000,
  PCID_FEATURE         = 0b00000000000000100000000000000000,
  DCA_FEATURE          = 0b00000000000001000000000000000000,
  SSE4_1_FEATURE       = 0b00000000000010000000000000000000,
  SSE4_2_FEATURE       = 0b00000000000100000000000000000000,
  x2APIC_FEATURE       = 0b00000000001000000000000000000000,
  MOVBE_FEATURE        = 0b00000000010000000000000000000000,
  POPCNT_FEATURE       = 0b00000000100000000000000000000000,
  TSC_DEADLINE_FEATURE = 0b00000001000000000000000000000000,
  AESNI_FEATURE        = 0b00000010000000000000000000000000,
  XSAVE_FEATURE        = 0b00000100000000000000000000000000,
  OSXSAVE_FEATURE      = 0b00001000000000000000000000000000,
  AVX_FEATURE          = 0b00010000000000000000000000000000,
  F16C_FEATURE         = 0b00100000000000000000000000000000,
  RDRAND_FEATURE       = 0b01000000000000000000000000000000,
  //NOT_USED_FEATURE     = 0b10000000000000000000000000000000,
}CPU_ECX_FEATURES_BITS;
										 
const char * cpu_edx_features_name[32] = {"fpu\0","vme\0","de\0","pse\0","tsc\0","msr\0",
									 "pae\0","mce\0","cx\0","apic\0","\0","sep\0","mtrr\0","pge\0","mca\0",
									 "cmov\0","pat\0","pse36\0","psn\0","clfsh\0","\0","ds\0","acpi\0",
									 "mmx\0","fxsr\0","sse\0","sse2\0","ss\0","htt\0","tm\0","\0","pbe\0"};

const char * cpu_ecx_features_name[32] = {"sse3","pclmulqdq","dtes64","monitor","ds-cpl","vmx",
										 "smx","eist","tm2","ssse3","cnxt-id","sdbg""fma","cmpxchg16",
										 "xtpr","pdcm","\0","pcid","dca","sse4_1","sse4_2",
										 "x2apic","movbe","popcnt","tsc-deadline","aesni","xsave","osxsave",
										 "avx","f16c","rdrand","\0"};

static void cpu_show_all_features()
{
	u32 ecx;
	u32 edx;
	__asm__ volatile("mov eax,1\n"
	    			 "cpuid\n"
	    			 :"=c"(ecx),"=d" (edx)
	    			 :
	    			 :"eax","ebx"
	    			 );

	u32 add_new_line = 8;
	u32 count_for_newline = 1;
	for(u32 i = 0;i < 32;++i)
	{
		if(edx >> i & 0xb1 && cpu_edx_features_name[i] != '\0')
		{
			uart_write_string(cpu_edx_features_name[i]);
			uart_write_ascii(' ');
			count_for_newline += 1;
		}
		if(count_for_newline % add_new_line == 0) uart_write_ascii('\n');
		
	}
	count_for_newline = 1;
	for(u32 i = 0;i < 32;++i)
	{
		if(ecx >> i & 0xb1 && cpu_ecx_features_name[i] != '\0')
		{
			uart_write_string(cpu_ecx_features_name[i]);
			uart_write_ascii(' ');
			count_for_newline += 1;
		}
		if(count_for_newline % add_new_line == 0) uart_write_ascii('\n');
	}
	uart_write_ascii('\n');
}

static void cpu_enable_sse2()
{
	u32 ecx;
	u32 edx;
	__asm__ volatile("mov eax,1\n"
	    			 "cpuid\n"
	    			 :"=c"(ecx),"=d" (edx)
	    			 :
	    			 :"eax","ebx"
	    			 );
	if(edx & SSE2_FEATURE)
	{
		//enable sse2
		__asm__ volatile ("mov eax,cr0");
		__asm__ volatile ("and ax,0xFF8"); //clear coprocessor emulation
		__asm__ volatile ("or ax,0b11");
		__asm__ volatile ("mov cr0,eax");
		__asm__ volatile ("mov cr0,eax");
		__asm__ volatile ("mov eax,cr4");
		__asm__ volatile ("or ax,3 << 9");
		__asm__ volatile ("mov cr4,eax");
		__asm__ volatile ("fxsave [_floats_save_region]");
		__asm__("pxor xmm0,xmm0");
		log_info("sse2 was enable");
	}
}


static void cpu_info()
{
	log_info("cpu info");
	
	char vendedor_indentification[14]; //3 * sizeof(u32) + 2 (for "\n\0") 
	__asm__ volatile("mov eax,0\n"
	    			 "cpuid\n"
	    			 "mov dword ptr [%0],ebx\n"
	    			 "mov dword ptr [%1],edx\n"
	    			 "mov dword ptr [%2],ecx\n"
	    			 :"=m"(vendedor_indentification[0]),
	    			  "=m" (vendedor_indentification[4]),
	    			  "=m" (vendedor_indentification[8])
	    			 :
	    			 :"eax","ebx","edx","ecx"
	    			 );
	vendedor_indentification[12] = '\n';
	vendedor_indentification[13] = '\0';
	uart_write_string((const char*)&vendedor_indentification[0]);
	cpu_show_all_features();
	
	cpu_enable_sse2();
}
