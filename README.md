# TEST TASK

## build
- Programs both can be build by `make` command, or separately by `build_program_1` and `build_program_2` from `src` directory. Programs executable files will be saved in their own directories on the same names.
- `make clear` to remove both programs executable files.

## Program_1
- Thread 1: Awaits user unput, check its correctness and put correct data into buffer
- Thread2 : Take data from buffer, make some processing over the data and get number which send by unix domain socket to program_2

## Program_2
- Awaits data from program_1, and once it got one, check this on some condition and show correspondigg message