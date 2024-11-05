<details>
 <summary>
  EV Charger
 </summary>

## Introducere
 Proiectul de față își propune să simuleze funcționarea unei stații de încărcare pentru un vehicul electric, utilizând LED-uri și butoane pentru a ilustra diferitele stadii ale procesului de încărcare. Această simulare are scopul de a reproduce cât mai fidel procesele care au loc într-o stație de încărcare reală, de la inițierea încărcării, monitorizarea progresului, până la finalizarea acesteia, asigurându-se că toate componentele sunt sincronizate corect.

## Componente
> 4x LED-uri (pentru a simula procentul de încărcare)
> 1x LED RGB (pentru starea de liber sau ocupat)
> 2x Butoane (pentru start încărcare și stop încărcare)
> 9x Rezistoare (7x 220ohm, 2x 1K)
> Breadboard
> Linii de legătură

## Descriere
 Proiectul presupune simularea unei stații de încărcare pentru vehicule electrice. Stația utilizează un LED RGB pentru a indica disponibilitatea (verde pentru liber, roșu pentru ocupat), și patru LED-uri simple care reprezintă progresul încărcării în procente (25%, 50%, 75%, 100%). Încărcarea se simulează prin aprinderea progresivă a LED-urilor, cu LED-ul curent clipind la intervale de 3 secunde. Un buton de start inițiază procesul de încărcare, iar un buton de stop poate forța oprirea încărcării și resetarea stației la starea liberă.

## Schema Electrica
<p>
  <img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_1/tinkercad.png" width="300"/>
</p>

## Montaj electric
<p>
  <img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_1/image00001.jpeg" width="300"/>
  <img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_1/image00002.jpeg" width="300"/>
  <img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_1/image00003.jpeg" width="300"/>
</p>

## Flow
Starea stației este ‘liberă’. Loader-ul este stins, iar led-ul pentru disponibilitate este verde.
Se apasă butonul pentru start.
Led-ul pentru disponibilitate se face roșu, iar încărcarea începe prin aprinderea primului LED L1.
Led-ul 1 clipește timp de 3s, celelalte fiind stinse.
Dupa încărcarea primului procent de 25% led-ul rămâne aprins și se trece la următorul led, care va începe să clipească.
La finalizarea încărcării toate led-urile vor clipi simultan de 3 ori, iar apoi se vor stinge, pentru a semnaliza finalizarea procesului.
Led-ul pentru disponibilitate se face verde.
Dacă oricând de la pornirea încărcării până la finalizarea acesteia este apăsat lung (min 1s) butonul de stop, încărcarea se întrerupe prin animația de final (toate led-urile clipesc de 3 ori), iar led-ul pentru disponibilitate devine verde.

## Video
[Video](https://github.com/mariaxadina/Robotica---Proiect-1/blob/main/Tema1_ATMEGA328P/IMG_0393.mov?raw=true)

Proiect realizat de:
Topliceanu Maria-Adina
Grupa 362
</details>

<details>
 <summary>
  TypeRacer Game
 </summary>
 
 ## Introducere
> Acest proiect este un joc de tastare controlat printr-un buton start/stop și un buton de setare a dificultății, care testează viteza și acuratețea utilizatorului în introducerea de cuvinte. LED-ul RGB servește drept indicator vizual al stării jocului, schimbând culoarea în funcție de situațiile specifice, iar un dicționar de cuvinte permite afișarea aleatorie a cuvintelor de tastat.

 ## Componente
> Arduino UNO (ATmega328P microcontroller)
> 1x LED RGB (pentru a semnaliza dacă cuvântul corect e scris greșit sau nu)
> 2x Butoane (pentru start/stop rundă și pentru selectarea dificultății)
> 5x Rezistoare (3x 220/330 ohm, 2x 1000 ohm)
> Breadbord
> Fire de legătură

## Schema Electrica
<p>
  <img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_2/Thinkercad.png" width="300"/>
</p>

## Montaj electric
![Montaj 1](https://github.com/mariaxadina/Robotica/blob/main/Tema_2/montaj_1.jpg)
![Montaj 2](https://github.com/mariaxadina/Robotica/blob/main/Tema_2/montaj_2.jpg)
![Montaj 3](https://github.com/mariaxadina/Robotica/blob/main/Tema_2/montaj_3.jpg)

### Video
[Video](https://github.com/mariaxadina/Robotica/blob/main/Tema_2/video.mov?raw=true)

</details>
