;
; Arquivo kernel.inc
;
; Descri��o:
;     Arquivo principal do Kernel do System4Nora.
;     Kernel Base. 
;     Arquivo principal do Kernel em assembly do sistema de 32bit.
;
;     *IMPORTANTE: 
;     O Kernel oferecer� recursos para as aplica��es.
;     Os recursos oferecidos pelo Kernel est�o distribuidos
;     por todo o System4Nora, nos 4 arquivos, inclusive
;     poder� voltar para o modo real de 16 bit, e oferecer servi�os
;     da biblioteca de 16 bit do Boot Manager.
;     
;     O Kernel Base cont�m m�dulos do tipo MB e processos do tipo PB. 
;     Kernel do tipo h�brido.
;
;     Obs: A inicial 'Ki' deve ser usado para fun��es de m�dulos internos.
;          Incluidos em tempo de compila��o.
;          MB - M�dulos inclu�dos no Kernel Base.
;
;     Obs: A inicial 'Ke' deve ser usado para fun��es de m�dulos externos.
;          Incluidos na hora do carregamento do sistema.
;          M0 - M�dulos em ring0. 
;
;     Threads do sistema: (User Mode threads). 
;         Idle: Window Station 0, Desktop 0.
;        Shell: Window Station 0, Desktop 0.
; Task Manager: Window Station 0, Desktop 0.
;
;
; Desktop 0: 
;     (Logon, recursos de ligar e desligar.)
;      + Background.
;      + Main Window.
;      + Navigation Bar. 
;      + Usa o procedimento de janela do sistema, ou da Main Window.
;      + No desktop 0 o Task Switch ainda est� desligado.
;
; Desktop 1:
;     + Background. 
;     + Shell.
;     + Task Manager.
;     + Outros app.
;     + Liga o Task Switch.
;
;  Desktop 2:
;       (@todo) Setup.
;
;
;  Desktop 3:
;      (@todo).
;
; Observa��es:
; ============
; + A �rea de Kernel Mode s�o os primeiros 4MB, onde virtual = f�sico.
; + O Kernel est� em 0x00100000 f�sico. Isso permite reescrever onde 
;   ficavam o Boot Manager, o Boot Loader e outras posi��es abaixo do Kernel. 
;   Mas algumas posi��es devem ser preservadas, como 0x000B8000 ou IVT 0:0. 
;   Com isso o Kernel pode usar endere�os legais abaixo de 1MB, como: 0xBEEF ou 0xCAFE.
; + � exclusivo do Kernel sujar a �rea abaixo de 1MB.
; + O entrypoint do Kernel agora � 0xC0001000 l�gico.
; 
; @todo:
; ======
;     + Pode-se criar um arquivo de log de inicializa��o.
;     � um bom jeito de ver a concatena��o da inicializa��o e a 
; distribui��o dos recursos na mem�ria.
;
; Client/Server:
; ==============
;     3Tier - Three-tier architecture.
;
;     + Presentation tier - User interface.
;     + Application tier  - Logic.
;     + Data tier         - Data bank.
;
;
; @todo:
;     O Kernel do System4Nora atender� requests intenos. 
;
; Vers�o 2015.
; 



;------------------------------------
; Kernel_Main:
;     Fun��o principal do Kernel do System4Nora.
;
;kMain:
Kernel_Main:

	mov esi, msg_kernel_testing
	call os_output
	
	;@todo:
	;systemStartUp:
	;init_video
	;set_up_cursor
	;KiInitRuntime
	;init
	;init_arquitecture_independent
	;init_arquitecture_dependent
	;debug:
	
    ;
	; IDT.
	;
	
	;cli
	;call setup_idt          ;Aponta tudo para uma isr s�. 'unhandled_int'.
	;call setup_faults       ;Configura vetores de faults e exceptions.
	;call setup_vectors      ;Configura outros vetores.
	;lidt [_IDT_register] 

	;
	; GDT.
	;
	
	;lgdt [_GDT_register] 
	
	
	;
	; LDT.
	;
	
	xor ax, ax  			
	lldt ax	
	
	
	;
	; TR.
	;
	
	;
    ; ??
    ; Flush TSS:
    ;     Load the index of our TSS structure.
	;     The index is 0x28, as it is the 5th selector and 
	; each is 8 bytes long, but we set the bottom two bits (making 0x2B)
    ; so that it has an RPL of 3, not zero.
    ;     Load 0x2B into the task state register.
 	;
	;mov eax, dword tss0
	;mov word [gdt6], tss0_end - tss0 - 1
	;mov [gdt6 + 2], ax
	;shr eax, 16
	;mov [gdt6 + 4], al
	;mov [gdt6 + 7], ah
	
	;carrega TR.
	;mov ax, word 0x2B     ;28+3. 
	;ltr ax  
   	
	
	
	;
	; Debug.
	;
	
	;Debug: Disable break points.
	xor	eax, eax
	mov	dr7, eax
	
	;Segmentos.
	;mov ax, word 0x10   
	;mov ds, ax		 
	;mov es, ax
	
	
	;Stack	(atualiza o ponteiro para a variavel global).
	;xor	eax, eax
	;mov dword [_kernel_stack_start], 0xC03FFFF0  
	;mov eax, dword [_kernel_stack_start] 
	;mov esp, eax 
		 
	;TIMER.
	;xor	eax, eax
	;mov al, byte 0x36
	;mov dx, word 0x43
	;out dx, al	
	;mov eax, dword 11930  ;timer frequency 100 HZ 
	;mov dx, word 0x40
	;out dx, al
	;mov al, ah
	;out dx, al
	
	;PIC.
	;cli
	;xor	eax, eax
	;mov al, 00010001b    ;begin PIC 1 initialization.
	;out 0x20, al
	;mov al, 00010001b    ;begin PIC 2 initialization.
	;out 0xA0, al	
	;mov al, 0x20	     ;IRQ 0-7: interrupts 20h-27h.
	;out 0x21, al
	;mov al, 0x28	     ;IRQ 8-15: interrupts 28h-2Fh.
	;out 0xA1, al
	;mov al, 4
	;out 0x21, al
	;mov al, 2
	;out 0xA1, al
	
	;mov al, 00010001b    ;11 sfnm 80x86 support.
	;out 0x21, al
	;out 0xA1, al

    ;mascara todas as interrup��es.
	;cli                                               
	;mov  al, 255					                  
	;out  0xa1, al                                   
	;out  0x21, al    
	
	;unmask the timer interrupt.
	;mov dx, word 0x21
	;in  al, dx
	;and al, byte 0xfe
	;out dx, byte al

	;unmask all interrupts.	
	;mov  al, 0					                  
	;out  0xa1, al                                   
	;out  0x21, al    

	;desbilita as interrup��es. #IMPORTANTE.
	;cli	
	
	
    ; 
	; * Muda o status do kernel.
	;
	;   @todo: Porque mudou para um se KeMain() muda para 0?
	;          +deletar isso. 
	;
	
	;mov dword [_KernelStatus], dword 1	
	
	
    ;
    ; @todo:
    ;     A inicial "_Ke" deve ser substituida.
	;     pois ser� usada pra chamar m�dulos externos. 
    ;
	
	;Chamara rotinas de inicializa��o.
    ;call _KeMain
	;; call _kMain @todo: Criar esse extern.	

	
    ;
	; Checa o retorno. Se n�o terminou de forma normal, halt system.
	;
	
	;cmp eax, 0
	;jne _halt_kernel
	
	;
	; @todo: e o processo IDLE.BIN?
	;        Quando ele foi iniciado. 
	;
	
	;
	; Ok. Start Idle thread.
	;
	
	
	
    call System4Nora_Browser  ;kernel mode.
	;jmp $		


	;
	; @todo: Chamar a fun��o Start Idle que dar� um spawn.
	;

	;jmp _KeStartIdle   ;user mode
	;;jmp _StartIdle   @todo criar esse extern.	
		
	jmp $
	
	
    ;
    ; OBS:
 	;    _KeMain em C n�o retorna pra esse ponto.
	;
	;    O c�digo em C executa a primeira tarefa 
	; efetuando um iret para o aplicativo em que est� em user mode.	
    ;

	
;_halt_kernel:	
    hlt
	jmp $
;    jmp _halt_kernel
   	
	
	
;
; Vari�veis para salvar o contexto.
;

_contextSS      dd 0    ;User mode.
_contextESP     dd 0    ;User mode.
_contextEFLAGS  dd 0    ;
_contextCS      dd 0    ;
_contextEIP     dd 0    ;
_contextDS   dd 0       ;
_contextES   dd 0       ;
_contextFS   dd 0       ;
_contextGS   dd 0       ;
_contextEAX  dd 0       ;
_contextEBX  dd 0       ;
_contextECX  dd 0       ;
_contextEDX  dd 0       ;
_contextESI  dd 0       ;
_contextEDI  dd 0       ;
_contextEBP  dd 0       ;	
	
	
;-------------------------------------------
; kernel_irq0:
;     Irq 0, Irq handler for Timer interrupt.
;     Rotina de tratamento de tempo para o Kernel do System4Nora.
;
;    Task Switch.
;    � aqui que acontece a troca de contexto.
;
;    @todo: O kernel precisa habilitar essa handler.
;
;
global kernel_irq0
kernel_irq0:
	;
    cli	
	;
	;stack
	pop dword [_contextEIP]       ;eip (DOUBLE).
	pop dword [_contextCS]        ;cs  (DOUBLE).
	pop dword [_contextEFLAGS]    ;eflags (DOUBLE).
	pop dword [_contextESP] 	  ;esp - user mode (DOUBLE).
	pop dword [_contextSS]        ;ss  - user mode (DOUBLE).
    ;
	;registers 
	mov dword [_contextEDX], edx    ;edx.		
	mov dword [_contextECX], ecx    ;ecx.	 
	mov dword [_contextEBX], ebx    ;ebx.	 
	mov dword [_contextEAX], eax    ;eax.
	;
	mov dword [_contextEBP], ebp    ;ebp.
	mov dword [_contextEDI], edi    ;edi.
	mov dword [_contextESI], esi    ;esi.	
	;segments
	xor eax, eax
    mov ax, gs
	mov word [_contextGS], ax	
    mov ax, fs
	mov word [_contextFS], ax	
    mov ax, es
	mov word [_contextES], ax	
    mov ax, ds
	mov word [_contextDS], ax	
	
	;
	; Preparando os registradores, para funcionarem em kernel mode.
	;
	
	xor eax, eax
	mov ax, word 0x10    ;Kernel mode segment.
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax              
	
	;todo: cr3, stack ...
	;
	;cr3
    ;mov eax, cr3
    ;mov dword [_contextCR3], eax ;todo, criar a vari�vel.    
	
	
	;
    ; Chama as rotinas em C.
    ; 	
	
	
	;
	; As rotinas em executar�o servi�os oferecidos pelo kernel
	; ou pelos seus modulos ou drivers.
	; Durante a execu��o dessas rotinas, as interrup��es podem
	; por um instante serem habilitadas novamente, se isso aacontecer
	; n�o queremos que a interrup��o de timer irq1 chame essas rotinas
	; em c novamente. Ent�o desabilitaremos a rechamada dessas fun��es
	; enquanto elas estivere em execu��o e habilitaremos novamnete ao sairmos delas.
	;
	;
	;	
	
	;
	; @todo: Chamar timer e task switch.
	;
	
	;chamada � modulo externo.
	;call _KeTimer            	
	;Chamada ao m�dulo interno.
	;call _KiTimer           ;Rotinas de timer. #N�O envolvendo task switch.  	
    ;call _KiTaskSwitch 	    ;Task switch. Troca a tarefa a ser executada.
	
	;segments
	xor eax, eax
	mov ax, word [_contextDS]
	mov ds, ax
	mov ax, word [_contextES]
	mov es, ax
	mov ax, word [_contextFS]
	mov fs, ax
	mov ax, word [_contextGS]
	mov gs, ax
	
	;
	;registers 
	mov esi, dword [_contextESI]    ;esi.
	mov edi, dword [_contextEDI]    ;edi.
	mov ebp, dword [_contextEBP]    ;ebp.
	;
	mov eax, dword [_contextEAX]    ;eax.
	mov ebx, dword [_contextEBX]    ;ebx.
	mov ecx, dword [_contextECX]    ;ecx.
	mov edx, dword [_contextEDX]    ;edx.

	;
	;stack
	push dword [_contextSS]        ;ss  - user mode.
	push dword [_contextESP]       ;esp - user mode.
	push dword [_contextEFLAGS]    ;eflags.
	push dword [_contextCS]        ;cs.
	push dword [_contextEIP]       ;eip.

	;
    ;EOI - sinal.
    mov al, 20h
    out 20h, al  
 	
	mov eax, dword [_contextEAX]    ;eax. (Acumulador).	
	
	;( N�o precisa 'sti', pois as flags da pilha habilitam as interrup��es ).
	
	sti      
    iretd	
	
	
	
;-----------------------------------------------------
; _int200:
;
;    Interrup��o de SISTEMA.
;
; eax = ;arg1 (numero)
; ebx = ;arg2 (arg2)
; ecx = ;arg3 (arg3)
; edx = ;arg4 (arg4)
; ...  
;
;++
global _int200
_int200:    
    pushad  
		
	;...
    push dword edx    ;arg4.
    push dword ecx    ;arg3. 
    push dword ebx    ;arg2. 
    push dword eax    ;arg1 = {n�mero}.
	
	call _system_services
    
	;Pega o retorno.
	mov dword [.int200_ret], eax    
    
	pop eax	
    pop eax
    pop eax
    pop eax 
    
	popad	
	
    mov al, 0x20
    out 0x20, al
    
	;
	; Coloca o valor do retorno em eax.
	;
	
	mov eax, dword [.int200_ret] 
	
	sti
	
	iretd
	
.int200_ret: dd 0
;--  


	
;----------------------------------------------------
; all_faults:
;     As faltas s�o tratadas em kernel mode, 
;     tem que ajustar os registradores para isso.
;
;
;   @todo: Enviar o n�mero a falta para uma vari�vel global.
;
kernel_all_faults:
    
	;d,c,b,a
	mov dword [_contextEDX], edx	
	mov dword [_contextECX], ecx	
	mov dword [_contextEBX], ebx	
	mov dword [_contextEAX], eax
		
	;ebp,edi,esi
	mov eax, ebp
	mov dword [_contextEBP], eax
	mov eax, edi
	mov dword [_contextEDI], eax
	mov eax, esi
	mov dword [_contextESI], eax

	;gs,fs,es,ds
	xor eax, eax	
    mov ax, gs
	mov word [_contextGS], ax	
    mov ax, fs
	mov word [_contextFS], ax	
    mov ax, es
	mov word [_contextES], ax	
    mov ax, ds
	mov word [_contextDS], ax	
		
	;(DOUBLE), eip,cs,eflags,esp,ss 
	pop eax
	mov dword [_contextEIP], eax	
	pop eax
	mov dword [_contextCS], eax	
	pop eax
	mov dword [_contextEFLAGS], eax		
	pop eax
	mov dword [_contextESP], eax	
	pop eax
	mov dword [_contextSS], eax		
    
	; Load the Kernel Data Segment descriptor!
    xor eax, eax
	mov ax, word 0x10   
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
	
	;
	; Chama a rotina em C.
	;
	
	;push dword [save_fault_number]    ;Passa o argumento via pilha. 
	;call _faults 
	
	mov esi, msg_kernel_all_faults
	call os_output
	
	jmp $
	
	
	
;----------------------------------------------
; request:
;     Atende requests internos.
;     Obs: A rotina de request no System4Nora
;          n�o trata rotinas de multitarefa.	
;
request:

    ;mov eax, [kernel_request]

    ;//0 - request sem motivo, (a vari�vel foi negligenciada).
    ;case KR_NONE:
	
	;//1 - tratar o tempo das tarefas de acordo com o tipo.  
	;case KR_TIME:

    ;//7 - tick do timer.
	;case KR_TIMER_TICK:	
	
	
	;//8 - limite de funcionamento do kernel.
    ;case KR_TIMER_LIMIT:
	

	;//9 - checa se ha tarefas para serem inicializadas e da spawn nelas.	
	;case KR_CHECK_INITIALIZED:
  
    ;Continua ...
	
.Done:	

    ;@todo:
    ;mov [kernel_request],  0;    //Zera o request
	
    mov eax, 0
    RET	
	
	
	
	
  
	
	
	
;---------------------------------------
; _system_services:
;
;   Servi�os oferecidos pela interru��o de sistema (int 200)
;	
; eax = ;arg1 (numero)
; ebx = ;arg2 (arg2)
; ecx = ;arg3 (arg3)
; edx = ;arg4 (arg4)
;
_system_services:
    
	;
	;@todo: Oferecer recursos. aproveitar o que tem feito em assembly.
	;
	
	RET
	

;
; Kernel messages.
;	
	
msg_kernel_testing    db 'BM Kernel test',13,10,0
msg_kernel_all_faults db '* BM HALT fault',13,10,0	
	
;
; fim.
;


	
	