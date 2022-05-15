Do you remember those days when time passed very quickly when you played games like Chicken Invaders? It's time to bring those days back with AlienInvasionRetro! Embark on the ship and try to shoot down as many aliens as possible. Be careful, though, because they become more and more dangerous!

# Batch to build app
# For Linux

cmake -S standalone -B build/standalone \
cmake --build build/standalone --config Release
cmake --build build/standalone --config Release \ 
(Or just run the build_release.sh script) \
Install required dependencies if CMake throws errors \
Wait for the build... \
Copy everything from the "res" folder to "build/standalone" \
Run "build/standalone/AlienInvadersRetro" \
Have Fun!


# For Windows

cmake -S standalone -B build/standalone \
cmake --build build/standalone --config Release \ 
(Or just run the build_release.bat script) \
Install required dependencies if CMake throws errors \
Wait for the build... \
Copy everything from the "res" folder to "build/standalone" \
Run "build/standalone/AlienInvadersRetro" \
Have Fun!

# Romanian

Cu toții știm că un joc bun are în spate o poveste la fel de interesantă. Acum avem ocazia să readucem copilăria la viață, deoarece are loc lansarea AsteroidInvasion, un joc scris in C++ ce are rolul de a încuraja evoluția tehnologiei, mai ales în contextul dezvoltării astronomiei, care a ajuns sa acapareze interesul publicului larg. Adoptând un design minimalist, este gata să intre în interesul tinerilor (nu atât de tineri).

Care este povestea?

Este anul 3042, un an in care tehnologia a devenit atât de dezvoltată încât am ajuns să cunoaștem cum să ne apărăm de intemperiile aduse de spațiul cosmic. Banda de asteroizi dintre Jupiter și Marte s-a destabilizat din cauza unui experiment eșuat de modificare a forței gravitaționale ce a afectat direct planeta Marte, iar asteroizii au fost deviați către Pământ! Este misiunea ta să pleci cu naveta spațială în misiune pentru a-i distruge înainte sa treacă de event horizon-ul Pământului – zona unde un impact devine inevitabil. Asteroizii nu sunt obișnuiți! Pentru a se apăra de eventuale atacuri extraterestre, urmașii lui Elon Musk au plasat pe asteroizi lasere distrugătoare, a căror menire e să gonească invadatorii care vor să colonizeze planeta Jupiter – au considerat că plasarea laserelor pe asteroizi este mai eficientă. De asemenea, pentru a se apăra, asteroizii au implementate motoare ce execută mișcări de autoapărare. Momentan nu mai funcționează atât de bine, ele executând mișcări haotice – Sistemul de control a fost decuplat. Rezistă cât mai mult în fața rocilor spațiale și acumulează un scor cât mai mare!

(Documentatia completa este in repository)

Link de prezentare pe YouTube: https://youtu.be/-r2QbY7F5tA
