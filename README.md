# przetwarzanie-rownolegle

 Streszczenie 
  * Problem polega na wyliczeniu wag dla grafu przy pomocy którego będzie można łatwo dokonać sekwencjonowania DNA. Wagi są liczone na podstawie pokrycia się końca i początku dwóch nukleotydów które pobierane są z pliku. Operacja ta jest wykonywana dla każdego pliku w folderze.

 Użyte technologie: 
  * OpenMP
  * OpenCL

----

 Opis problemu 
Rozwiązanie problemu sekwencjonowania łańcuchów DNA poprzez wyznaczenie najkrótszej ścieżki w grafie skierowanym, ważonym. Oligonukleotydy odpowiadają wierzchołkom, a łuki obrazują wspólną sekwencję oligonukleotydów między początkiem oligonukleotydu X i końcem oligonukleotydu Y. Wagi w grafie wynikają z długości wspólnej sekwencji nukleotydów, im dłuższa wspólna sekwencja tym mniejszy koszt. Warto, aby waga była nieliniowo, najlepiej kwadratowo zależna od długości części wspólnej. Pozwoli to priorytetować połączenia większej liczby podciągów o dłuższych wspólnych częściach, nad łączeniem mniejszej ilości podciągów z krótką częścią wspólną. Zrównoleglony algorytm ma za zadanie wyliczeni tych wag grafu do późniejszego przeszukiwania grafu w celu znalezienia optymalnej ścieżki.

n - liczba oligonukleotydów
l - długość olginukleotydów

Na podstawie wspólnych elementów podciągów tworzymy graf z łukami o wagach w(x,y) wyliczonych jako kwadrat różnicy długości oligonukleotydu, i długości części wspólnej nukleotydów k(x,y) tak więc w(x,y)=(l - k(x,y))².
