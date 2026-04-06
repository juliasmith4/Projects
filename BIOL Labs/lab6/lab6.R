#read in library 

library(tidyverse)

dat <- read.csv("global_temps.csv")

#check data class 

class(dat)

class(dat$year)
class(dat$annual_temp_c)

x <- (dat$year)
y <- (dat$annual_temp_c)

# linear regression model

summary(x)
summary(y)

model <- lm(y ~ x)
model
summary(model)

library(ggplot2)
ggplot(data = dat, 
       aes(x = year, 
           y = annual_temp_c)) + 
  geom_point(color = "blue") +
  geom_smooth(method = "lm", color = "purple") +
  xlab("Year") +
  ylab("Annual Mean Temperature (Celcius)") +
  ggtitle("Global Annual Temperature Over Time") +
  theme_classic()



library(dplyr)

dat_1951 <- dat %>%
  filter(year >= 1951)


head(dat_1951)


x <- (dat_1951$year)
y <- (dat_1951$annual_temp_c)

summary(x)
summary(y)

model_1951 <- lm(y ~ x)
model_1951
summary(model_1951)

library(ggplot2)

ggplot(data = dat_1951, 
       aes(x = year, 
           y = annual_temp_c)) + 
  geom_point(color = "pink") +
  geom_smooth(method = "lm", color = "yellow") +
  xlab("Year") +
  ylab("Annual Mean Temperature (Celcius)") +
  ggtitle("Global Annual Temperature (1951–Present)") +
  theme_classic()






library(tidyverse)

# reading CO2 data
co2_data <- read.csv("combo.csv")

# data
head(co2_data)
class(co2_data$year)
class(co2_data$annual_co2_ppm)


x <- co2_data$year
y <- co2_data$annual_co2_ppm

summary(x)
summary(y)

model_co2 <- lm(y ~ x)
model_co2
summary(model_co2)

library(ggplot2)

ggplot(co2_data, aes(x = year, y = annual_co2_ppm)) +
  geom_point( color = "green") +
  geom_smooth(method = "lm", color = "purple") +
  xlab("Year") +
  ylab(" CO2(ppm)") +
  ggtitle("CO2 Concentration") +
  theme_classic()



library(tidyverse)

# reading CO2 data
co2_data <- read.csv("combo.csv")

# data
head(co2_data)
class(co2_data$annual_temp_c)
class(co2_data$annual_co2_ppm)


y <- co2_data$annual_temp_c
x <- co2_data$annual_co2_ppm

summary(x)
summary(y)

model_co2 <- lm(y ~ x)
model_co2
summary(model_co2)

library(ggplot2)

ggplot(co2_data, aes(y = annual_temp_c, x = annual_co2_ppm)) +
  geom_point( color = "orange") +
  geom_smooth(method = "lm", color = "grey") +
  ylab("Annual temperature (celcius)") +
  xlab(" CO2(ppm)") +
  ggtitle("CO2 Concentration") +
  theme_classic()



