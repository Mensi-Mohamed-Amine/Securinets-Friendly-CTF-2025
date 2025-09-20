# baby_pwntools - writeup

## description

![Alt text](img/1.png)

# binary information

```
$ file main
```

![Alt text](img/2.png)

```
$ pwn checksec main
```

![Alt text](img/3.png)

## solution

This task is pretty straightforward all we have to do is use `pwntools` python librayr which is a library designed for exploit development.
We should change the value of the local variable `secret` with `0x0` and we will get the flag.

![Alt text](img/4.png)
