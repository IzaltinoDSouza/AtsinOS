OSNAME     = "AtsinOS"
GCCPARAMS  = -m32 -std=gnu17 -ffreestanding -w -I"include/" -Wall -Wextra
ASPARAMS   = --32
LDPARAMS   = -melf_i386 -nostdlib --allow-multiple-definition
 
objects = obj/boot.o \
		  obj/kernel.o \
		  obj/memory.o \
		  obj/math.o \
		  obj/timer.o \
		  obj/keyboard.o \
		  obj/io.o \
		  obj/graphics.o \
		  obj/demos/game01.o \

obj/%.o: src/%.c
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/boot/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

kernel.bin: src/boot/linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

$(OSNAME).iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "$(OSNAME)" {'           >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin'      >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$(OSNAME).iso iso
	rm -rf iso
	
.PHONY: install
install: kernel.bin
	sudo cp $< /boot/kernel.bin

.PHONY: clean
clean:
	rm -rf obj kernel.bin $(OSNAME).iso
	
.PHONY: run
run: $(OSNAME).iso
	qemu-system-x86_64 -m 256M -boot d -cdrom $<
	
.PHONY: all	
all:
	make clean
	make
	make run
