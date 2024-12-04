<details>
 <summary>
  EV Charger
 </summary>

## Introducere
 Proiectul de față își propune să simuleze funcționarea unei stații de încărcare pentru un vehicul electric, utilizând LED-uri și butoane pentru a ilustra diferitele stadii ale procesului de încărcare. Această simulare are scopul de a reproduce cât mai fidel procesele care au loc într-o stație de încărcare reală, de la inițierea încărcării, monitorizarea progresului, până la finalizarea acesteia, asigurându-se că toate componentele sunt sincronizate corect.

## Componente
> 4x LED-uri (pentru a simula procentul de încărcare)
> 
> 1x LED RGB (pentru starea de liber sau ocupat)
> 
> 2x Butoane (pentru start încărcare și stop încărcare)
> 
> 9x Rezistoare (7x 220ohm, 2x 1K)
> 
> Breadboard
> 
> Linii de legătură

## Descriere
 Proiectul presupune simularea unei stații de încărcare pentru vehicule electrice. Stația utilizează un LED RGB pentru a indica disponibilitatea (verde pentru liber, roșu pentru ocupat), și patru LED-uri simple care reprezintă progresul încărcării în procente (25%, 50%, 75%, 100%). Încărcarea se simulează prin aprinderea progresivă a LED-urilor, cu LED-ul curent clipind la intervale de 3 secunde. Un buton de start inițiază procesul de încărcare, iar un buton de stop poate forța oprirea încărcării și resetarea stației la starea liberă.

## Schema Electrica
<p>
  <img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_1/tinkercad.png" width="300"/>
</p>

## Montaj Electric
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
> 
> 1x LED RGB (pentru a semnaliza dacă cuvântul corect e scris greșit sau nu)
> 
> 2x Butoane (pentru start/stop rundă și pentru selectarea dificultății)
> 
> 5x Rezistoare (3x 220/330 ohm, 2x 1000 ohm)
> 
> Breadbord
> 
> Fire de legătură

## Schema Electrica
<p>
  <img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_2/Thinkercad.png" width="300"/>
</p>

## Montaj electric
![Montaj 1](https://github.com/mariaxadina/Robotica/blob/main/Tema_2/montaj_1.jpg)
![Montaj 2](https://github.com/mariaxadina/Robotica/blob/main/Tema_2/montaj_2.jpg)
![Montaj 3](https://github.com/mariaxadina/Robotica/blob/main/Tema_2/montaj_3.jpg)

## Flow
Jocul este în repaus. LED-ul RGB are culoarea albă.

Se alege dificultatea jocului folosind butonul de dificultate, iar în terminal va apărea “Easy/Medium/Hard mode on!”.

Se apasă butonul de start/stop.

LED-ul clipește timp de 3 secunde, iar în terminal se va afișa numărătoarea înversă: 3, 2, 1.

LED-ul devine verde și încep să apară cuvinte de tastat.

La tastarea corectă, următorul cuvânt apare imediat. Dacă nu se tasteaza cuvântul în timpul stabilit de dificultate, va apărea un nou cuvânt.

O greșeală face LED-ul să devină roșu. Pentru a corecta cuvântul, se va folosi tasta BackSpace.

Dupa 30 de secunde, runda se termină, iar în terminal se va afișa scorul: numărul total de cuvinte scrise corect.

Jocul se poate opri oricând cu butonul de start/stop.

## Video
[Video](https://github.com/mariaxadina/Robotica/blob/main/Tema_2/video.mov?raw=true)

Proiect realizat de:

Topliceanu Maria-Adina

Grupa 362
</details>
<details>
  <summary>Quick Game</summary>

## Descriere
Această temă reprezintă un joc competitiv de reflex pentru doi jucători. Scopul fiecărui jucător este să apese cât mai rapid butonul asociat culorii afișate pe LED-ul RGB. Punctajul este afișat pe un LCD și actualizat pe parcursul jocului. La final, jocul indică câștigătorul și scorul final.

## Componente utilizate
- *6x LED-uri* (2 grupuri de câte 3 LED-uri, fiecare grup având culori diferite)
- *2x LED RGB* (1 pentru fiecare jucător)
- *6x butoane* (3 pentru fiecare jucător)
- *1x LCD*
- *1x servomotor*
- *2x Breadboard*
- *Fire de legătură*
- *2x Arduino Uno*

## Cerințe
1. *Inițializare*
   - La pornirea jocului, un mesaj de bun venit este afișat pe LCD.
   - Jocul poate fi pornit printr-un buton dedicat sau apăsarea unui buton dintre cele existente.

2. *Desfășurarea Rundelor*
   - Fiecare jucător are 3 butoane și un LED RGB. LED-ul RGB afișează o culoare, iar jucătorul trebuie să apese rapid butonul corespunzător.
   - Răspunsul corect aduce puncte, iar răspunsul mai rapid oferă punctaj mai mare.
   - La finalul fiecărei runde, punctajul este actualizat pe LCD.

3. *Finalizarea Jocului*
   - Servomotorul indică progresul jocului. O rotație completă marchează sfârșitul jocului.
   - LCD-ul afișează câștigătorul și scorul final, apoi revine la ecranul de start.
  
## Bonusuri implementate
- *Animație pe LCD* la pornirea jocului.
- *Numele jucătorilor* introduse prin interfața serială.

## Poze cu implementarea pe breadboard
<p>
  <img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_3/media/1.JPG?raw=true" width="300"/>
  <img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_3/media/2.JPG?raw=true" width="300"/>
  <img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_3/media/3.JPG?raw=true" width="300"/>
  <img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_3/media/4.JPG?raw=true" width="300"/>
  <img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_3/media/5.JPG?raw=true" width="300"/>
</p>

## Schema electrică
<img src="https://github.com/mariaxadina/Robotica/blob/main/Tema_3/media/schema.jpg?raw=true" width="300"/>

## Video
[Video](https://github.com/mariaxadina/Robotica/blob/main/Tema_3/media/video.mp4?raw=true)

## Publicare
Codul proiectului se găsește pe GitHub și include toate detaliile necesare pentru replicarea proiectului.

</details>

