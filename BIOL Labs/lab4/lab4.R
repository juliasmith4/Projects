# Read the CSV
library(tidyverse)




#FIRST IMAGE



dat <- read.csv("firstarea.csv")



dat$Area <- round(dat$Area, 6)

ggplot(dat, aes(x = Area, fill = Area)) +
  geom_histogram(fill = "black") + 
  theme_classic() +
  xlab("Area (um)") 
  

dat2 <- read.csv("firstlength.csv")



# Round 
dat2$Length <- round(dat2$Length, 6)

ggplot(dat2, aes(x = Length, fill = Length)) +
  geom_histogram(fill = "green") + 
  theme_classic() +
  xlab("Length (um)")



#SECOND IMAGE



dat3 <- read.csv("secondarea.csv")



# Round 
dat3$Area <- round(dat3$Area, 6)

ggplot(dat3, aes(x = Area, fill = Area)) +
  geom_histogram(fill = "yellow")  +
  theme_classic() +
  xlab("Area (um)")
   
  

dat4 <- read.csv("secondlength.csv")



# Round 
dat4$Length <- round(dat4$Length, 6)

ggplot(dat4, aes(x = Length, fill = Length)) +
  geom_histogram(fill = "magenta")  +
  theme_classic() +
  xlab("Length (um)") 
   



#THIRD IMAGE



dat5 <- read.csv("thirdarea.csv")



# Round 
dat5$Area <- round(dat5$Area, 6)

ggplot(dat5, aes(x = Area,fill = Area)) +
  geom_histogram(fill = "lavender")  +
  theme_classic() +
  xlab("Area (um)") 


dat6 <- read.csv("thirdlength.csv")



# Round 
dat6$Length <- round(dat6$Length, 6)

ggplot(dat6, aes(x = Length,fill = Length)) +
  geom_histogram(fill = "lightblue") +
  theme_classic() +
  xlab("Length (um)") 
  



