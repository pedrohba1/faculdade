# Exercício 1 

#a 

x <- 1:20

#b

x <- 20:1

#c

x <- c(1:20, 20:1)

#d

a <- seq(3, 36, 3)
a
b <- seq(1,34, 3)
b
c = 0.1^(a)*0.2^(b)

print(c)

#e
f <- c(rep(c(4,6,3),10),4)


#f
e <- rep(4:6, times=10)


#exercício 2
zercicio_2 <- function(x) {
  result <- exp(x)*cos(x)
  return(result)
}

s <- seq(from = 3, to = 6, by=0.1)

l <- zercicio_2(s)

#exercício 3
#a

zercicio_3a <- function(i) {
  result <- i^3 + 4*(i^2)
  return(result)
}

s <- 10:100
somatorio <- zercicio_3a(s)
total <- sum(somatorio)
total

#b
zercicio_3b <- function(i) {
  
result <- ((2^i) /i) + ((3^i) / (i^2))
  return(result)
}

s <- 10:25
somatorio <- zercicio_3b(s)
total <- sum(somatorio)
total

#Exercício 4
xVec <- sample(0:999, 250, replace=T)
yVec <- sample(0:999, 250, replace=T)

#a

impar <- function (x){
        if(x %% 2 == 0){
           return (FALSE) 
        }
        else {
            return (TRUE)
        }
}

novoVect <- vector()

for(i in xVec) {
    if(impar(i)){
        novoVect<-c(novoVect, i)
    }
}

novoVect

#b
subVect <- vector()
for (i in 2:250){
    subVect <- c(subVect, yVec[i] - xVec[i-1] )
}

subVect

#c
cosVect <- vector()
for (i in 2:250){
    item <- (sin(yVec[i]))/(cos(xVec[i-1]))
    
    cosVect <- c(cosVect, item )
}

print(cosVect, digit=3)

#d
dVect <- vector()
for (i in 3:250){
    item <- (xVec[i-2] + 2*xVec[i-1] + xVec[i])
    dVect <- c(dVect, item )
}

dVect

#e
eVect <- vector()
for (i in 1:249){
    item <- exp((-xVec[i]) + 1) / (xVec[i] + 10)
    eVect<- c(eVect, item)
}

sum(dVect)

#Exercício 5
#a
yIndexes <- vector()
y <- vector()
for (i in yVec){
    if(i> 600){
        y <- c(y,i)
        yIndexes <- c(yIndexes, match(i, yVec))
    }
}

print("os índices são esses")
print(yIndexes, max.levels=1)

#b

print("os valores em si são esses")
print(y, max.levels=1)

#c

v <- vector()
for (i in xVec){
    if(i> 600){
        index <- match(i, yVec)
        if(!is.na(index))
            v <- c(v,yVec[index])
        }
}

#d
x <- vector()

for (i in 1:length(xVec)){
    item <- abs( xVec[i] - mean(xVec))^(1/2) 
    x <- c(x,item)
}
print(x, max.levels=1)

#e
y <- vector()
yMax <- max(yVec)

for(i in yVec){
    if(abs(yMax - i) <= 200 )
    y <- c(y,i)
}
length(y)

#f
x <- vector()
for(i in xVec){
    if(i %% 2 ==0){
        x <- c(x,i)
    }
}

length(x)

#g
sort(xVec)


#h
y <- vector()
sequencia <- seq(1, 250, 2)
y <- yVec[sequencia]
y


#Execício 6
par <- seq(2, 38, 2)
impar <- seq(3,39,2)

tudo <- vector()
tudo <- c(tudo,1)
tudo

for(i in 1:length(par)){
    temp <- vector()
    for(i in 1:i){
        item <- par[i]/impar[i] 
        temp <- c(temp, item)
    }

    tudo <- c(tudo, prod(temp))
}
sum(tudo)