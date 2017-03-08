object = jpeg_imio.c image.c

test: test.c ${object}
	gcc -o test test.c ${object} -lm -ljpeg

clear:
	rm -rf test