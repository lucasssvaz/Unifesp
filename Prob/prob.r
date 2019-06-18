library(tidyverse)
setwd("~/Desktop/Link to Google Drive/Unifesp/Git/Unifesp/Prob")

tabela <- read.csv("Data.csv", header = T, fileEncoding = "latin1")
tab_tam_cor <- read.csv("Tam_Cor.csv", header = T, fileEncoding = "latin1")
tab_pape_cor <- read.csv("Pape_Cor.csv", header = T, fileEncoding = "latin1")

pape <- tabela %>% slice(1:20)
normal <- tabela %>% slice(21:200)

quant_all <- tabela[4:13]
quant_pape <- pape[4:13]
quant_normal <- normal[4:13]

cor_all <- colSums(quant_all)
cor_pape <- colSums(quant_pape)
cor_normal <- colSums(quant_normal)

total_all <- sum(cor_all)
freq_all <- prop.table(cor_all)

total_pape <- sum(cor_pape)
freq_pape <- prop.table(cor_pape)

total_normal <- sum(cor_normal)
freq_normal <- prop.table(cor_normal)


lbls <- labels(freq_normal)
pct <- round(freq_normal/sum(freq_normal)*100)
lbls <- paste(lbls, pct)
lbls <- paste(lbls,"%",sep="")
pie(freq_normal,labels = lbls, col=rainbow(length(lbls)),
    main="Porcentagens pedidas de cada cor (Normal)")


lbls <- labels(freq_pape)
pct <- round(freq_pape/sum(freq_pape)*100)
lbls <- paste(lbls, pct)
lbls <- paste(lbls,"%",sep="")
pie(freq_pape,labels = lbls, col=rainbow(length(lbls)),
    main="Porcentagens pedidas de cada cor (PAPE)")


lbls <- labels(freq_all)
pct <- round(freq_all/sum(freq_all)*100)
lbls <- paste(lbls, pct)
lbls <- paste(lbls,"%",sep="")
pie(freq_all,labels = lbls, col=rainbow(length(lbls)),
    main="Porcentagens pedidas de cada cor (Tudo)")


chisq.test(tab_tam_cor)
chisq.test(tab_pape_cor)
