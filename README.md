# Virtual Machine
My approach to creating a simple stack-based virtual machine

# Building

It's pretty easy to set this thing up, as I provide you with a simple Python script that automatically runs cmake and make.

```sh
$ python3 ./build.py
```
> Note that this was only tested on Arch-Linux.

# Instructions
- push (push onto the stack)
- pop (pop the first element on the stack)
- add (adds the last 2 elements on the stack together and removes them)
- syscall (runs a system call)

# System Calls
- 0 (Prints the last entry on the stack)
