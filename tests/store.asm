_main:
    push 5      ; Stack: [5]
    store 1     ; Memory: [5] Stack: []

    push 9      ; Stack: [9]
    store 2     ; Memory: [5, 9] Stack: []

    push 1      ; Stack: [1]
    load 1      ; Stack: [1, 5] Memory: [5, 9]
    iadd        ; Stack: [6] Memory: [5, 9]

    syscall 1