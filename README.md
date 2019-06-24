# Wstęp

Naszym zadaniem było napisanie programu do obsługi drukarki 3D, oraz napisanie programu generującego zadany ruch tej drukarki.

# Użądzenie

Drukarką użytą do testów jest **Kossel linear plus** firmy **Anycubic**. Na zajęciach używana była starsza wersja tej drukarki, ale ponieważ mamy dostęp do nowszej wersji to postanowiliśmy pisać program właśnie na tej. Nowsza wersja różni się między innymi łożyskami na ramie do przesuwania głowicą, oraz końcówką do auto levelingu, która bardzo ułatwia kalibracje drukarki.

# Arduino

Sterownikiem drukarki jest klon Arduino MEGA. Do pisania programu posłużyło środowisko **Arduino IDE**. Klon płytki nie sprawiał żadnych problemów i był w pełni kompatybilny z orginałem.

## Komunikacja

Komunikacja z drukarką odbywa się za pomocą **serialportu**, na częstotlimości 115200. Dane do drukarki na temat ruch są przesyłane w następującej formie:
$$
a \quad 'krokx' \quad b \quad 'kroky' \quad c \quad 'krokz'
$$
gdzie zmienne krok mówią o ilości kroków do wykonania, dla konkretnego silnika.

## Ruch silników krokowych

Aby silniki krokowe mogły się poruszać należy wygenerować im zadaną ilość impulsów, która następnie przerabiana jest na ilość kroków wykonanych przez silnik. Nie można przesadzić z ilością impulsów w jednostce czasu, ponieważ silnik może wtedy zacząć "gubić kroki".  Do generacji impulsów zostały użyte **delay**. Lepszym rozwiązaniem było by użycie timerów, ale autorom kodu się nie chciało.

# Matlab

Kod w matlabie ma za zadanie generować trajektorie ruch głowicy, w celu drukowania jakiegoś obiektu. My testowo zrobiliśmy drukowanie trójkąta. Matlab jest również odpowiedzialny z levelowanie głowicy nad stołem.

# Instrukcja obsługi

## 1. Załadować program do Arduino

Poprzez **Arduino IDE** załadować do Arduino MEGA program "NielinioweUklady Steroania_Druk3D.ino". Drukarka zacznie się automatycznie poziomować oraz ustawiać temperaturę 200 stopni.

## 2. Uruchomienie skryptu Init

W Matlabie należy uruchomić skrypt "init.m" w celu otwarcia portu szeregowego między drukarką, a matlabem. Po tej czynności drukarka się zresetuje i zacznie ponownie się ustawiać do pozycji bazowej oraz ustawiać temperaturę głowicy.

## 3. Levelowanie

Po ustawieniu się drukarki i nagrzaniu głowicy, należy ustawić głowice ręcznie tuż nad blatem. Trzeba to robić z matlaba poprzez stworzony obiekt w skrypcie "Init.m", aby nie zresetować drukarki. 

## 4. Uruchomienie programu Druk

Po zlevelowaniu drukarki należy uruchomić program druk, który zacznie drukować trójkąt.

