# binpatcher

`binpatcher` is a command-line tool for searching and replacing binary blocks in files.

## Usage

```sh
binpatcher -i <input_file> -o <output_file> -s <search_block_file> -r <replace_block_file>
```

### Options

- `-h`: Display this help message and exit.
- `-i <input_file>`: Path to the input file.
- `-o <output_file>`: Path to the output file.
- `-s <search_block_file>`: Path to the binary file containing the block to search for.
- `-r <replace_block_file>`: Path to the binary file containing the block to replace with.

## Example

To search for a specific binary block in `input.bin` and replace it with another block from `replace.bin`, saving the result to `output.bin`, use:

```sh
binpatcher -i input.bin -o output.bin -s search.bin -r replace.bin
```

## Installation

### Requirements

- `cmake` (version 3.10 or higher)
- `gcc` (GNU Compiler Collection)

### Build and Install

To compile and install `binpatcher`, follow these steps:

1. Create a build directory:
   ```sh
   mkdir build
   cd build
   ```

2. Configure the project with CMake:
   ```sh
   cmake ..
   ```

3. Compile the project:
   ```sh
   make
   ```

4. Install the executable:
   ```sh
   sudo make install
   ```

To uninstall:

```sh
sudo xargs rm < install_manifest.txt
```

### License

This software is provided under the terms of the MIT License. You are free to use, modify, and distribute this software, subject to the conditions and limitations of the MIT License. For more details, please see the LICENSE file included with this software.

### Contact and Support

- Report bugs to: splintergu@gmail.com
- Home page: [binpatcher on GitHub](https://github.com/SplinterGU/binpatcher)