# controlled_overflow - writeup

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

## solution

In this task we should exploit the buffer overflow vulnerability to overwrite the value of the local variable `key` with `0x3030303030303030` in order the get the flag.
