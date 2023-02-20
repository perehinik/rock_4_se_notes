# Creating hello world kernel module

This is my first file created using ROCK 4 SBC :).
Here is the procedure of creating simple kernel module:

1.Get headers file name:
```
apt-cache search linux-headers-\`uname -r\`
```

2.Install headers:
```
sudo apt-get install kmod linux-headers-4.4.194-11-rk3399-rockchip-g1bb08d49cc40
```

3.Install gcc, g++, make:
```
sudo apt install libssl-dev  build-essential
```

4.Recompile dependent libraries:
```
cd /usr/src/linux-headers-$(uname -r)
make scripts
```

5.Build kernel module from hello-1 directory:
```
sudo make
```

6.Load module:
```
sudo insmod hello-1.ko
```

7.Check if module loaded:
```
sudo lsmod | grep hello
```

8.Remove module
```
sudo rmmod hello_1
```

9.Check kernel log:
```
sudo journalctl --since "1 hour ago" | grep kernel
```
