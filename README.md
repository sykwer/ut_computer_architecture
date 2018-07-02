# ut_computer_architecture
CPU by verilog and Assembler by C++

## How to run assembler
```
$ mkdir -p assembler/bin
$ cd assembler/bin
$ cmake ..
$ make
$ cd ..
$ ./bin/assembler sample.asm > sample.bnr
```

## How to install Modelsim on VM
Type in commands below, after downloading Quartus-lite-18.0.0.614-linux.tar from http://dl.altera.com/?edition=lite
```
$ vagrant up
$ vagrant reload
$ vagrant scp Quartus-lite-18.0.0.614-linux.tar :/home/vagrant/
$ vagrant ssh

# After logged into VM...

$ tar -xvf Quartus-lite-18.0.0.614-linux.tar
$ ./setup.sh
```

## How to start Quartus and Modelsim
```
$ vagrant up
$ vagrant ssh

# After logged into VM...

$ ~/intelFPGA_lite/18.0/quartus/bin/quartus
$ ~/intelFPGA_lite/18.0/modelsim_ase/linuxaloem/vsim
```
