path=/home/hideonatc/Documents/forfun/
SFML=-L usr/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
cpp:$(f).cpp
	g++	$(f).cpp	-o $(f)
	$(path)$(f)
	rm	$(f)
sf:$(s).cpp
	g++	$(s).cpp -o $(s) $(SFML)
	./$(s)
	rm	$(s)
git:
	git add *
	git commit -m --all
	git push origin master
