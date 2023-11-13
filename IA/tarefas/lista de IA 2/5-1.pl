movie('Amnésia', 'Suspense', 'Nolan', 2000, 113).
movie('Babel', 'Drama', 'Iñarritu', 2006, 142).
movie('Capote', 'Drama', 'Miller', 2005, 98).
movie('Casablanca', 'Romance', 'Curtiz', 1942, 102).
movie('Matrix', 'Ficção', 'Wachowski', 1999, 136).
movie('Rebecca', 'Suspense', 'Hitchcock', 1940, 130).
movie('Shrek', 'Aventura', 'Adamson', 2001, 90).
movie('Sinais', 'Ficção', 'Shyamalan', 2002, 106).
movie('Spartacus', 'Ação', 'Kubrick', 1960, 184).
movie('Superman', 'Aventura', 'Donner', 1978, 143).
movie('Titanic', 'Romance', 'Cameron', 1997, 194).
movie('Tubarão', 'Suspense', 'Spielberg', 1975, 124).
movie('Volver', 'Drama', 'Almodóvar', 2006, 121).

find_director(MovieName,Director) :- movie(MovieName,_,Director,_,_).
find_by_genre(Genre, MovieName) :- movie(MovieName,Genre,_,_,_).
find_movie_details(MovieName, Genre, Director, Year, Duration) :-
    movie(MovieName, Genre, Director, Year, Duration).


duration_less_than(Time,Name) :- 
    movie(Name,_,_,_,Duration),
    Duration =< Time.


classico(Name):-
    movie(Name,_,_,Y,_),
    Y =< 1980.


genero(Name,G):-
    movie(Name,Fg,_,_,_),
    G = Fg.

