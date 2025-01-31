# Eight Queens

[Eight Queens](https://en.wikipedia.org/wiki/Eight_queens_puzzle) Puzzle is a puzzle where on a typical 8x8 chessboard, you have to place Eight Queens that can't threaten one-another.

![demo](./demo.gif)

## Run

### Nix

- Run using Nix:

  ```bash
  nix run .
  ```

  _OPTIONAL_ build using CMake in NixOS:

- Go into `Nix` development shell

  ```bash
  nix develop
  ```

- Follow the steps for `CMake`

### CMake

- Make a temporary directory called `build/`:

  ```bash
  mkdir build/
  ```

- Go into the temporary directory:

  ```bash
  cd build
  ```

- Run `CMake` to generate a `Makefile` and other stuff for `make`

  ```bash
  cmake ..
  ```

- Run `make` to build and run the project

  ```bash
  make
  ```
