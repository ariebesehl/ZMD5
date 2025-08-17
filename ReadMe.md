# ZMD5



Minimalist command-line tool for MD5-hashing files



![ZMD5](https://github.com/ariebesehl/ZMD5/blob/main/doc/cover-lmde6.png "ZMD5 running in LMDE 6")

![ZMD5](https://github.com/ariebesehl/ZMD5/blob/main/doc/cover-win7.png "ZMD5 running in Windows 7")



## Installation

1) Download release v20240211 for Linux, release v20200511 for Windows systems
2) Extract to directory/folder of your choice (*optional*: add a `PATH` variable to use utility from everywhere)
3) Open a command-line terminal, and type `ZMD5 <filepath>` to get the MD5 hash of `<filepath>`



## Requirements

1) Windows operating system (Tested on Windows 7 and Windows 10 systems)
2) Linux operating system (Tested on Linux Mint Debian Edition/LMDE 6 'Faye')



## Features

1) Lightweight
2) Accepts wildcard and input from `stdin`
3) *Significantly* faster compared to built-in `certutil -hashfile <filename> MD5` in Windows (~55% faster at 32.93s vs. 52.21s with 16 GiB of data) / Slightly *slower* compared to `md5sum <filename>` in GNU/Linux operating systems (ca. 0-5% worse `time` values)
4) Valid hashes directed to `stdout` following `<MD5 hash>\t<filepath> (<filesize> bytes)\n` convention
5) MOTD and error messages directed to `stderr`



## Notes

1) This software was intended to be a native `md5sum` for Windows operating systems and it did this well
2) In Linux, it doesn't manage to beat `md5sum` in speed or features, but it saves typing three letters, although that's nothing a bash alias couldn't fix either

## Examples

`ZMD5 test-1m.txt` Hash `test-1m.txt` and display the hash in the command-line terminal.

`ZMD5 * > hashes.txt` Hash all files in current directory and store them in `hashes.txt`. Note: This will only output *valid* hashes into the text-file, error messages will be displayed in the command-line terminal.

`ZMD5 < test-warmup.txt` Read `test-warmup.txt` into `stdin` and direct this into `ZMD5` to compute the hash.



## License

Copyright (C) 2020-2025 Andreas Riebesehl a.k.a. cr4qsh0t

This work is licensed under: This work is presently unlicensed.
