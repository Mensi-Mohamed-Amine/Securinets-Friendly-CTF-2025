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

In this task we are given a binary that spawn a shell and using `cat flag` we can solve the task and get our flag.

![Alt text](img/4.png)
