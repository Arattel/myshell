

| Executable | Description |
| ----------- | ----------- |
| mycat | Mycat program |
| mycat_c_functions| C functions instead of syscalls |
| Productivity comparison.ipynb| Jupyter Notebook with timing comparison for syscalls and c functions on different file sizes|


### Difference between syscalls and c standard library functions

Basically, C standard library functions(fopen, fread, fwrite, etc.) are wrappers for system calls, while open, read, 
write are system calls themselves. Main differences include: C functions cannot be interrupted and
syscalls are executed in kernel mode, while c functions are executed in user mode. 