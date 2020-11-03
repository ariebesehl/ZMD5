# ZMD5



Minimalist command-line tool for MD5-hashing files



![ZMD5](https://github.com/ariebesehl/ZMD5/blob/main/__screenshot.png "")



## Installation

1) Download https://github.com/ariebesehl/ZMD5/raw/main/__latest.zip

2) Extract to folder of your choice (*optional*: add a `PATH` variable to use utility from everywhere)

3) Open a command-line terminal, and type `ZMD5 <filepath>` to get the MD5 hash of `<filepath>`



## Requirements

1) Windows operating system (Tested on Windows 7 and Windows 10 systems)



## Features

1) Lightweight

2) Accepts wildcard and input from `stdin`

3) *Significantly* faster compared to built-in `certutil -hashfile <filename> MD5`

4) Valid hashes directed to `stdout` following `<MD5 hash>\t<filepath> (<filesize> bytes)\n` convention

5) MOTD and error messages directed to `stderr`



## Examples

`ZMD5 test-1m.txt` Hash `test-1m.txt` and display the hash in the command-line terminal.

`ZMD5 * > hashes.txt` Hash all files in current directory and store them in `hashes.txt`. Note: This will only output *valid* hashes into the text-file, error messages will be displayed in the command-line terminal.

`ZMD5 < test-warmup.txt` Read `test-warmup.txt` into `stdin` and direct this into `ZMD5` to compute the hash.



## License

Copyright (C) 2020 Andreas Riebesehl a.k.a. cr4qsh0t

This work is licensed under: This work is presently unlicensed.
