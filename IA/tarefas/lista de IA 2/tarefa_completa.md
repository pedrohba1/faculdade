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

Abaixo, temos os alunos em X, e os professores em Y. O exercício pediu os professores de X, mas eu só mudei a notação.
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


**b)**  A regra é: `universitario_da(X,Y) :- frequenta(X,Y).`

Abaixo, em X temos os alunos e em Y as faculdades. Aqui, novamente, mudei somente a notação. 

```pl
?- universitario_da(X,Y).
X = joao,
Y = puc ;
X = maria,
Y = puc ;
X = joel,
Y = ufrj.
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

