path=/home/hideonatc/Documents/forfun/
all:$(f)
	g++ $(f).cpp -o $(f)
	$(path)$(f)
	rm $(f)
git:
	git add *
	git commit -m --all
	git push origin master