# Мовшин Максим | БПИ213 | ДЗ-10
компиляция:
```
gcc receiver.c -o receiver && gcc sender.c -o sender
```

Ввод - Терминал 1:
```
./receiver
<enter sender pid>
<enter number to send>
```
Ввод - Терминал 2:
```
./sender
<enter receiver pid>
```
Пример вывода - sender:
```
Hello! I am sender. My pid is: 7716
Enter receiver pid and number to send
7735
-25
sending: -25
sending bit by bit...
11111111111111111111111111100111
```
Пример вывода - receiver:
```
Hello! I am receiver. My pid is: 7735
Enter sender pid
7716
11111111111111111111111111100111
answer: -25
Killed: 9
```
