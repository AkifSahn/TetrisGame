run:tetris.out
	./tetris.out

tetris.out:*.cpp *.hpp
	c++ -o tetris.out *.cpp

clean:
	rm tetris.out

