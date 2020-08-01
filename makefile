path=/home/hideonatc/Documents/forfun/
all:$(f)
	g++ $(f).cpp -o $(f)
	$(path)$(f)
	rm $(f)
sfml:$(f)
	g++ $(f).cpp -o $(f) -L usr/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
	./$(f)
	rm $(f)
git:
	git add *
	git commit -m --all
	git push origin master