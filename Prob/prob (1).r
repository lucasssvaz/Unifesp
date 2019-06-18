tabela = read.csv("Data.csv",header = T)

summary(tabela[1:3])
quant <- tabela[4:13]

cor_quant <- colSums(quant)

total_camisetas <- sum(cor_quant)
freq_camisetas <- prop.table(cor_quant)

total_camisetas
freq_camisetas

lbls <- labels(freq_camisetas)
pct <- round(freq_camisetas/sum(freq_camisetas)*100)
lbls <- paste(lbls, pct)
lbls <- paste(lbls,"%",sep="")
pie(freq_camisetas,labels = lbls, col=rainbow(length(lbls)),
    main="Porcentagens pedidas de cada cor")