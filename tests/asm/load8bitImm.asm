;
; Load 8 bit registers test
;
; @author Natesh Narain
;

		org $150
	
start:
		ld A,1
		ld B,2
		ld C,3
		ld D,4
		ld E,5
		ld H,6
		ld L,7
		
		halt
