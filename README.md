# AtsinOS

AtsinOS is a very simple operating system designed for 2D games.

![AtsinOS Screenshot](https://github.com/IzaltinoDSouza/AtsinOS/blob/main/AtsinOS.png?raw=true)

## Road Map

- [x] Draw pixels: Implement pixel drawing and display on the screen.
- [x] Fill rectangle: Draw and fill rectangles with color.
- [ ] Draw rectangle: Add functionality to draw rectangle borders with color.
- [ ] Draw image: Implement drawing of images using pixel arrays/pointers.
- [ ] Timer : Get time and Delay
- [x] Get key from keyboard
- [ ] Memory Allocation
- [ ] Double buffer
- [ ] Read from disk : flat disk layout or user define layout
- [ ] Add qoi image support : used for texture

## Getting Started

To get started with AtsinOS (NOTE only build on Linux), follow these steps:

1. Clone the repository
```bash
	git clone https://github.com/AtsinOS
```
2. Download qemu-system, xorriso
```bash
	sudo apt install qemu-system-x86-64 xorriso
```
3. Build and run the AtsinOS project.
```bash
	make run
```

## License

AtsinOS is licensed under the [GNU GENERAL PUBLIC LICENSE](https://github.com/IzaltinoDSouza/AtsinOS/blob/main/LICENSE).
