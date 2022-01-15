
; Basic Arithmetic
_main:
    ; 3 + 4 ; Pushing the result to the stack and
    ; removing 3 and 4 from the stack
    push 3 push 4 iadd

    ; Top of the stack + 4
    push 4 iadd 

    ; Printing the result (top of the stack)
    syscall 1