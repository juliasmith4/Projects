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
  geom_point(color = "firebrick", shape = "diamond", size = 3) +
  geom_smooth(method = "lm", color = "purple") +geom_line()+
  xlab("Year") +
  ylab("Annual Mean Temperature (Celcius)") +
  ggtitle("Global Annual Temperature Over Time") + geom_point(color = "firebrick", shape = "diamond", size = 2)+theme(axis.title.x = element_text(vjust = 0, size = 20),plot.title = element_text(size = 20),axis.title.y = element_text(vjust = 0, size = 20), axis.text = element_text(color = "purple", size = 20)) 







#part 2

#read in library 
library(tidyverse)


dat <- read.csv("finches_data_for_lab.csv")

#check data class (type of object)

class(dat)

class(dat$band_id)
class(dat$drought_survival)
class(dat$body_mass_g)

class(dat$wing_length_mm)
class(dat$tarsus_length_mm)
class(dat$beak_length_mm)


class(dat$beak_depth_mm)
class(dat$beak_width_mm)
head(dat)


#summarize numeric data easily 



summary(dat$beak_width_mm)
summary(dat$beak_depth_mm)

summary(dat$beak_length_mm)
summary(dat$body_mass_g)
summary(dat$wing_length_mm)
summary(dat$tarsus_length_mm)
summary(dat$drought_survival)


#standard deviation



library(dplyr)
head(dat)
all_means_sd<- dat %>%
  group_by(drought_survival)%>%
  summarise(avg_winglength=mean(wing_length_mm), sd_winglength = sd(wing_length_mm),
            avg_depth = mean(beak_depth_mm), sd_depth = sd(beak_depth_mm), 
            avg_tarsus = mean(tarsus_length_mm), sd_tarsus = sd(tarsus_length_mm),
            avg_mass = mean(body_mass_g), sd_mass = sd(body_mass_g),
            avg_width = mean(beak_width_mm), sd_width = sd(beak_width_mm),
            avg_beakLength = mean(beak_length_mm), sd_beakLength = sd(beak_length_mm))


library(ggplot2)
ggplot(data = all_means_sd, 
       aes(x = drought_survival, 
           y = avg_depth)) + 
  geom_col(fill = "pink") +
  ylab("Mean Beak Depth (mm)") +
  xlab("Drought Survival") + theme_classic() +  
  geom_errorbar(aes(ymin = avg_depth - sd_depth, 
                    ymax = avg_depth + sd_depth),width = 0.2) 

