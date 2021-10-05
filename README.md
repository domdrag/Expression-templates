# Diplomski_vs_code

Predložni izrazi (expression templates)

Klase spremnika (eng. *container classes*) predstavljaju posebnu vrstu klasa dizajniranih da spremaju kolekciju nekakvih objekata. Takve klase imaju široko područje primjene, od biblioteka matrica u znastvenom računanju do reprezentacije grafova u modeliranju. Često su skupovi podataka koje instance takvih klasa spremaju ogromni veličinom stoga je nužno obratiti pozornost na efikasnost operacija nad tim podacima. Naime, ukoliko programer ne obrati pažnju na performanse, kao što ćemo pokazati u ovom radu, dolazi do nepotrebnog kopiranja unutar memorije. Ako su skupovi podataka preveliki ta kopiranja oduzimaju puno vremena pa samim time efikasnost algoritma neće biti zadovoljavajuća. 

Tema ovog rada upravo opisuje jednu od tehnika u programskom jeziku C++ kojom se sprječava nepotrebno kopiranje, ali i smanjuje broj čitanja odnosno zapisavanja memorijskih lokacija. Navedenu tehniku nazivamo predložni izrazi (eng. *expression templates*). Tehnika spada pod metaprogramiranje pa prvo dajemo uvod u metaprogramiranje i metaprogramiranje predlošcima. Zatim stvaramo biblioteku vektora i pripadnih operacija naivnim pristupom i uočavamo propuste u samom izvođenju i efikasnosti. Probleme rješavamo pomoću predložnih izraza. Također pokazujemo kako tehniku iskoristiti u implementaciji matrica i matričnih operacija. Na kraju uspoređujemo učinkovitosti dobivenih implementacija sa Eigen bibliotekom koja također koristi predložne izraze, ali i brojne druge tehnike optimizacija.

# Pokretanje programa - main.exe
