# ut_computer_architecture
CPU by verilog and Assembler by C++

![block diagram](https://user-images.githubusercontent.com/18254663/42187783-3e05194a-7e8c-11e8-8edc-e667f98788ac.jpg "block diagram")

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

## How to simulate CPU
1. Assemble test assembly code
```
$ ./assembler/bin/assembler computer/sample.asm > computer/sample.bnr
```

2. Compile all verilog files on Modelsim (be careful to compile order)

3. Simulate on Modelsim
```
vsim work.test_computer
run
```
