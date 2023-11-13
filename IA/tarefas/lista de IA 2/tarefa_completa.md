# Exercícios completos


### Questão 1)

```pl
% fatos
especie(joao, passaro).
especie(pedro, peixe).
especie(maria, minhoca).
especie(eu, humano).
especie(chuck_norris, gato).

gosta_de(passaro, minhoca).
gosta_de(gato, peixe).
gosta_de(gato, passaro).

gosta_de(chuck_norris, eu).
gosta_de(eu,chuck_norris).

% Regras
% Amigos gostam uns dos outros: 
amigo(X,Y) :- gosta_de(Y,X), gosta_de(X,Y).

% O meu gato come tudo que gosta, exceto pessoas.
come(gato, X) :- gosta_de(gato, X), not(especie(X,humano)).    

```

Nisso, podemos testar no interpretador o seguinte para ver se as regras funcionam:
```pl
?- come(gato,eu).
false.

?- come(gato,peixe).
true.

?- amigo(chuck_norris,eu).
true.

?- amigo(eu,chuck_norris).
true.
```


### Questão 2)

**a)** A regra é: `aluno_de(X,Y) :- aluno(X,Z), professor(Y,Z).`

Abaixo, temos os alunos em X, e os professores em Y. O exercício pediu os professores de X, mas eu só mudei a variável.
```
?- aluno_de(X,Y).
X = joao,
Y = carlos ;
X = maria,
Y = carlos ;
X = joel,
Y = pedro ;
X = joel,
Y = ana_paula.
```


**b)**  A regra é: `associado_a(X,Y) :- frequenta(X,Y); funcionario(X,Y).`

Abaixo, em X temos os alunos e funcionários e em Y as faculdades. Aqui, novamente, mudei somente a notação. 

```pl
?- associado_a(X,puc).
X = joao ;
X = maria ;
X = ana_paula ;
X = carlos.
```


### Questão 3)

Acredito que essa questão esteja ambígua em relação à notação normal do Prolog. Porém, vou assumir que `x,y,z` são variáveis, que de acordo com a definição do Prologo deveriam ser em letras maiúsculas, `P,Q` predicados.

Para o primeiro par de sentenças: 
`P(A,B,B), P(x,y,z)`

Podendo ele ser escrito assim em Prolog: `p(X,Y,Z) = p(a,b,b).`

Nesse caso, há a seguinte unificação:
```
X = a,
Y = Z, Z = b.
```

Ou seja, na notação do exercício, `A` unifica com `x` e `z` unifica com `y` que unifica com `B`.


Para a segunda sentença: `P(x,y), Q(A,B)`.

Nesse caso, não há unificador geral, porque os predicados P e Q são diferentes.

Para a terceira sentença: `Q(y,G(A,B)), Q(G(x,z),y)`

Nesse caso, é possível fazer as seguintes unificações (seguindo a notação do exercício):

```
y = G(A,B),
x = A,
z = B
```

Para a última sentença: `P(f(x),y,g(B)), P(f(y),A,z)`

A seguinte unificação é a mais geral:

```
x = y,
y = a,
z = g(a)

```

### Questão 5)

CATÁLOGO DE FILMES:

| Título      | Gênero     | Diretor     | Ano  | Min. |
|-------------|------------|-------------|------|------|
| Amnésia     | Suspense   | Nolan       | 2000 | 113  |
| Babel       | Drama      | Iñarritu    | 2006 | 142  |
| Capote      | Drama      | Miller      | 2005 | 98   |
| Casablanca  | Romance    | Curtiz      | 1942 | 102  |
| Matrix      | Ficção     | Wachowski   | 1999 | 136  |
| Rebecca     | Suspense   | Hitchcock   | 1940 | 130  |
| Shrek       | Aventura   | Adamson     | 2001 | 90   |
| Sinais      | Ficção     | Shyamalan   | 2002 | 106  |
| Spartacus   | Ação       | Kubrick     | 1960 | 184  |
| Superman    | Aventura   | Donner      | 1978 | 143  |
| Titanic     | Romance    | Cameron     | 1997 | 194  |
| Tubarão     | Suspense   | Spielberg   | 1975 | 124  |
| Volver      | Drama      | Almodóvar   | 2006 | 121  |

Representação em Prolog:

```pl
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
```

### Questão 5.1)

**a)** Fiz uma regra geral para encontrar o nome dos diretores e com ela posso 
encontrar o diretor do filme "Titanic":
```pl
find_director(MovieName,Director) :- movie(MovieName,_,Director,_,_).

# Exemplo de uso da regra:
?- find_director('Titanic', D).
D = 'Cameron'.

```

**b)** A seguinte regra pode ser usada para encontrar filmes de suspense:

```pl
find_by_genre(Genre, MovieName) :- movie(MovieName,Genre,_,_,_).

# a regra funcionando abaixo:
?- find_by_genre('Drama',M).
M = 'Babel' ;
M = 'Capote' ;
M = 'Volver'.

```
Ela também pode ser usada para encontrar qualquer gênero de filme.

**c)**  Usando a mesma regra do item **a)**:
```pl
?- find_director(M, 'Donner').
M = 'Superman'.
```

**d)**  Fiz uma função mais completa para pegar todos os detalhes necessário de um filme:
```pl

find_movie_details(MovieName, Genre, Director, Year, Duration) :-
    movie(MovieName, Genre, Director, Year, Duration).

# resposta: 

?- find_movie_details('Sinais',_,_,A,_).
A = 2002.
```


**e)** A seguinte função filtra os filmes por duração:

```pl


duration_less_than(Time,Name) :- 
    movie(Name,_,_,_,Duration),
    Duration =< Time.

# aplicando a função:

?- duration_less_than(100,X).
X = 'Capote' ;
X = 'Shrek' ;
```

### Questão 5.2)

```pl

classico(Name):-
    movie(Name,_,_,Y,_),
    Y =< 1980.

# aplicando a regra na base de conhecimento:
?- classico(X).
X = 'Casablanca' ;
X = 'Rebecca' ;
X = 'Spartacus' ;
X = 'Superman' ;
X = 'Tubarão' ;
```


### Questão 5.3)

```pl

genero(Name,G):-
    movie(Name,Fg,_,_,_),
    G = Fg.

# o predicado aplicado: 

?- genero(X,'Drama').
X = 'Babel' ;
X = 'Capote' ;
X = 'Volver'.

```

### questão 5.4)

```
# aplicando as duas regras em conjunto:

?- genero(X,'Suspense'), classico(X).
X = 'Rebecca' ;
X = 'Tubarão' ;
```

