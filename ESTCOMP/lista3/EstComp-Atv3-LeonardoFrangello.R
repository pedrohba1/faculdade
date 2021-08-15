# Grupo - 
# Leonardo Frangello - 11721BCC029
# Gabriel José Bueno Otsuka - 11721BCC018
# Thaynara - 11711BCC039
# Pedro Henrique Bufulin de Almeida - 11711BCC028

# 1) 
contador <- 100000
for (iterador in 1:100000) {
  sorteio <- sample(1:4, size = 4, replace = F)
  indexSorteio <- 1
  for (valorSorteio in sorteio) {
    if (indexSorteio == valorSorteio) {
      contador <- contador - 1
      break
    }
    indexSorteio <- indexSorteio + 1
  }
}

resultado <- contador/100000

probAmigoOculto <- function(n) {
  contador <- 100000
  for (iterador in 1:100000) {
    sorteio <- sample(1:n, size = n, replace = F)
    indexSorteio <- 1
    for (valorSorteio in sorteio) {
      if (indexSorteio == valorSorteio) {
        contador <- contador - 1
        break
      }
      indexSorteio <- indexSorteio + 1
    }
  }
  
  return (contador/100000)
}

# 2)

contador <- 0
for (iterador in 1:100000) {
  lance1 <- sample(1:6, size = 1, replace = T)
  lance2 <- sample(1:6, size = 1, replace = T)
  
      if (lance1 + lance2 == 7 || lance1 + lance2 == 11) {
        contador <- contador + 1
          }
}

resultado <- contador/100000

# 3) 

bolas <- c("preta","branca","vermelha")
contador <- 0

for (i in 1:100000) {
  dado <- sample(1:6, size = 1, replace = TRUE)  
  if (dado == 5) {
    if(sample(bolas, size = 1, prob = c(6/13, 4/13, 3/13))  == "vermelha") {
      contador <- contador + 1
    }
  } else if (dado == 1 || dado == 4 || dado == 6) {
    if(sample(bolas, size = 1, prob = c(3/10, 2/10, 5/10)) == "vermelha") {
      contador <- contador + 1
    }
  } else {
    if(sample(bolas, size = 1, prob = c(4/8, 2/8, 2/8)) == "vermelha") {
      contador <- contador + 1
    }
  }
}

resultado <- contador/100000

# 4) 
contador <- 0

for (i in 1:100000) {
  dado1 <- sample(1:6, 1)
  dado2 <- sample(1:6, 1)
  
  soma <- dado1 + dado2
  
  if(soma == 7 || soma == 11) {
    contador <- contador + 1
  } else if (soma != 2 || soma != 3 || soma != 12) {
    while(TRUE) {
      dado1 <- sample(1:6, 1)
      dado2 <- sample(1:6, 1)
      soma2 <- dado1 + dado2
      if (soma2 == 7) {
        break
      } else if (soma2 == soma) {
        contador <- contador + 1
        break
      }
    } 
  }  
}

resultado <- contador/100000

#5)

e = 2.718281828459045235360287
a <- runif(100000, -1, 2)
resultado1 <- sum((1/sqrt(2*pi)) * (e**(-a*a/2)))/100000


b <- runif(100000, 0, pi)
resultado2 <- sum(cos(b) ** 2)/100000
