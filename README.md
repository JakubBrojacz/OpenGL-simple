# Grafika projekt 5 - Wyścigówka w Sponzie

## Sterowanie

### Kamera

Przełącznie trybu kamery za pomocą przycisków:\
`Z` - Kamera na samochodzie\
`X` - Kamera stacjonarna\
`C` - Kamera w centrum sponzy, podąża za wyścigówką\
`V` - Tryb wolny kamery. Poruszanie za pomocą klawiszy `WASD` i myszy

### Mgła

Przełącznie mgły za pomocą przycisków:\
`F` - Początek mgły; Mgła zaczyna się zbierać. Może to potrwać kilka sekund\
`G` - Koniec mgły; Mgła zaczyna ustępować. Może to potrwać kilka sekund

### Cieniowanie i oświetlenie

Przełącznie lightningu za pomocą przycisków:\
`B` - Blinn lightning\
`P` - Phong lightning

Przełącznie shadingu za pomocą przycisków:\
`H` - Phong shading\
`J` - Gouraud shading

Przy zmianie shadingu lightning zmienia się automatycznie na Blinna.

### Poruszanie światłem na wyścigówce

Poruszać światłem na wyścigówce można strzałkami na klawiaturze.

### Cykl dnia i nocy

Cykl jest stały, nie można go zmienić. Cały cykl trwa około 100 sekund.

## Rozwiązania techniczne

### Język

Cały projekt napisany jest w `C++`. Kompilowanie działa w `Visual Studio 2019` w trybie Debug dla x86. Nie testowałem innych konfiguracji.

### Modele

Do wczytania modeli korzystałem z biblioteki [assimp](http://www.assimp.org/)\
Model wyścigówki stworzyony przez Dil Afroze Ahmad.\
Model sponzy przez Morgan McGuire.

### Tutoriale

Przy pisaniu programu korzystałem z [learnOpenGl](https://learnopengl.com/) i książki Davida Wolffa "OpenGL 4.0 Shading Language Cookbook".