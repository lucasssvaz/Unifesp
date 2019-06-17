4+9
6**3
9*4+2/67
x = 10
y = x/10^2

z = c(4,2,3)
z[1]
z[2] = 666
z
z[1] = 333
z[3] = 999
z

a = seq(0,1,by=0.05)
a

help(seq)
help(plot)
help(runif)
b = runif(21)

plot(a,b)
help(spline)
help(xspline)
help(lines)
xspline(a,b,shape=0.5)
lines(spline(a,b, method='n', n=250))

mat = matrix(b,nrow = 3, ncol = 7, byrow = T)
mat

mat2 = matrix(runif(21),nrow = 7,ncol = 3, byrow = T)

matR = mat2%*%mat

matR*matR

help(predict)

tabela = read.csv2("C:\\Users\\lucas\\Downloads\\dados.csv",header = T)
tabela

summary(tabela)

names(tabela)

tabela$idade_mes

fa = table(tabela$est_civil)
fr = prop.table(fa)

fac = cumsum(fr)
fac

tabela2 = cbind(fa,fr,fac,porcent=100*fr)
tabela2

fa = table(tabela$idade_ano)
fr = prop.table(fa)
fr

fac = cumsum(fr)
fac

tabela3 = cbind(fa,fr,fac,porcent=100*fr)
tabela3

fa = table(tabela$salario)
fr = prop.table(fa)
fr

fac = cumsum(fr)
fac

tabela4 = cbind(fa,fr,fac,porcent=100*fr)
tabela4

range(tabela$salario)
nclass.Sturges(tabela$salario)
nclass.scott(tabela$salario)
nclass.FD(tabela$salario)

fa = table(cut(tabela$salario,seq(range(tabela$salario)[1],range(tabela$salario)[2], l = nclass.Sturges(tabela$salario)+1)))

fa = table(cut(tabela$salario,seq(range(tabela$salario)[1]-0.01,range(tabela$salario)[2], l = nclass.Sturges(tabela$salario)+1)))

fr = prop.table(fa)
fr

tabela5 = cbind(fa,fr)
tabela5

cont = table(tabela$est_civil,tabela$filhos)
cont

par(mfrow=c(1,2))
barplot(table(tabela$filhos),main="Filhos")
barplot(table(tabela$filhos),main="Filhos",col = 'red')

par(mfrow=c(1,1))
pie(table(tabela$instrucao))

par(mfrow=c(1,3))
hist(tabela$salario)
hist(tabela$salario,nclass = 5)
hist(tabela$salario,nclass = 5, col = 'orange')