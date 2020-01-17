# quantization
Project related with my first-year academic course. Created on 2 September 2019.

PL description:

Treść zadania:

"Celem zadania jest napisanie programu opisującego zachowanie cząstki w pewnym wyimaginowanym świecie kwantowym. Cząstka może przebywać w czterech stanach kwantowych, oznaczanych liczbami 0, 1, 2 i 3. Kwantowa historia cząstki jest to niepusty ciąg kolejnych stanów kwantowych, w jakich cząstka przebywała, ale tylko niektóre kwantowe historie cząstki są dopuszczalne. Dopuszczalnej kwantowej historii cząstki można przypisać skwantowaną energię. Energię tę można zmieniać. Niedopuszczalna kwantowa historia cząstki nie może mieć przypisanej energii. Energie dwóch dopuszczalnych kwantowych historii cząstki mogą zostać zrównane, co oznacza, że zmiana energii dla jednej z tych historii powoduje też zmianę energii drugiej z nich. Relacja zrównania energii przypisanych historiom jest równoważnością."

Opis działania: 

"Po uruchomieniu programu nie są dopuszczalne żadne kwantowe historie cząstki, zatem żadnej historii nie jest przypisana energia i żadne dwie energie nie są zrównane. W czasie działania program czyta ze standardowego wejścia i wykonuje następujące polecenia:

    DECLARE history – Powoduje, że każda kwantowa historia cząstki, będąca prefiksem podanej jako parametr history kwantowej historii cząstki, staje się dopuszczalna.

    REMOVE history – Powoduje, że każda kwantowa historia cząstki, mająca prefiks podany jako parametr history, przestaje być dopuszczalna.

    VALID history – Sprawdza, czy podana kwantowa historia cząstki jest dopuszczalna.

    ENERGY history energy – Jeśli podana w parametrze history kwantowa historia cząstki jest dopuszczalna i historia ta nie ma przypisanej energii, to przypisuje jej wartość energii podanej jako parametr energy. Jeśli ta kwantowa historia cząstki ma już przypisaną energię, to modyfikuje wartość tej energii.

    ENERGY history – Jeśli podana w parametrze history kwantowa historia cząstki jest dopuszczalna i historia ta ma przypisaną energię, to wypisuje wartość tej energii.

    EQUAL history_a history_b – Jeśli podane w parametrach history_a i history_b kwantowe historie cząstki są dopuszczalne, to: (a) jeśli chociaż jedna z nich ma przypisaną energię, zrównuje ich energie i domyka relację równoważności; (b) jeśli obie historie przed wykonaniem tego polecenia mają przypisane energie, to po wykonaniu polecenia energia przypisana tym historiom jest średnią arytmetyczną tych energii (z ewentualnym zaokrągleniem w dół); (c) jeśli obie historie są identyczne lub mają już zrównane energie, niczego nie zmienia."
