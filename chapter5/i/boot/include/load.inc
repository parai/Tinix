
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                               load.inc
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                                                     Forrest Yu, 2005
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


BaseOfLoader		equ	 09000h	; LOADER.BIN �����ص���λ�� ----  �ε�ַ
OffsetOfLoader		equ	  0100h	; LOADER.BIN �����ص���λ�� ---- ƫ�Ƶ�ַ

BaseOfLoaderPhyAddr	equ	BaseOfLoader * 10h	; LOADER.BIN �����ص���λ�� ---- ������ַ (= BaseOfLoader * 10h)


BaseOfKernelFile	equ	 08000h	; KERNEL.BIN �����ص���λ�� ----  �ε�ַ
OffsetOfKernelFile	equ	     0h	; KERNEL.BIN �����ص���λ�� ---- ƫ�Ƶ�ַ

BaseOfKernelFilePhyAddr	equ	BaseOfKernelFile * 10h
KernelEntryPointPhyAddr	equ	030400h	; ע�⣺1�������� MAKEFILE �в��� -Ttext ��ֵ���!!
					;       2�����Ǹ���ַ���ǽ����Ǹ�ƫ�ƣ���� -Ttext ��ֵΪ 0x400400��������ֵҲӦ���� 0x400400��

PageDirBase		equ	200000h	; ҳĿ¼��ʼ��ַ:		2M
PageTblBase		equ	201000h	; ҳ����ʼ��ַ:			2M + 4K
