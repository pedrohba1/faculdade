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

