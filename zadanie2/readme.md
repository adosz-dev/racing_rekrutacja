# Zadanie 2

## a

Podpunkt a dotyczy problemu otoczki wypukłej (convex hull). Program najpierw znajduje punkt P0, który jest położony najniżej (jeżeli istnieje kilka takich punktów to wybiera ten położony najbardziej na lewo). Następnie sortuje resztę punktów według kąta między linią łączącą dany punkt i punkt P0 a osią OX przy pomocy funkcji atan2. Później program przechodzi do tworzenia stosu: 
- bierze 3 pierwsze punkty z posortowanej listy 
- deklaruje top i next: punkt top jest równy pierwszemu punktowi na stosie, a next — drugiemu. 
- przechodzi pętlą for przez listę, gdzie pętla loop sprawdza punkty na stosie: jeżeli skręt punktów next, top i punktu z indeksem i jest prawoskrętny lub prosty to znaczy, że top nie jest częścią otoczki, więc go usuwamy, a jeżeli jest lewoskrętny to pozostawiamy go. Po przejsciu pętli while dodajemy punkt z indeksem i na stos.

Program bierze pod uwagę, że jeżeli zostały podane 3 lub mniej punktów, to te punkty są tą otoczką.
