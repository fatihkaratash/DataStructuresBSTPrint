# Derleme ve bağlantı hedefleri
all: dizin derle bagla calistir

# Derleme aşaması
derle:
	g++ -c -I"./include" ./src/main.cpp -o ./lib/main.o
	g++ -c -I"./include" ./src/LinkedList.cpp -o ./lib/LinkedList.o
	g++ -c -I"./include" ./src/BST.cpp -o ./lib/BST.o
	g++ -c -I"./include" ./src/BSTNode.cpp -o ./lib/BSTNode.o

# Bağlantı aşaması
bagla:
	g++ ./lib/main.o ./lib/LinkedList.o ./lib/BST.o ./lib/BSTNode.o -o ./bin/program.exe

# Çalıştırma aşaması
calistir:
	.\bin\program.exe

# Temizleme aşaması
temizle:
	del /Q .\lib\*.o
	del /Q .\bin\program.exe

# Dizin oluşturma
dizin:
	if not exist lib mkdir lib
	if not exist bin mkdir bin
