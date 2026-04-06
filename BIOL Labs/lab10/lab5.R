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


ggplot(data = all_means_sd, 
       aes(x = drought_survival, 
           y = avg_winglength)) + 
  geom_col(fill = "orange") +
  ylab("Mean Wing Length (mm)") +
  xlab("Drought Survival") + theme_classic() + 
  geom_errorbar(aes(ymin = avg_winglength - sd_winglength, 
  ymax = avg_winglength + sd_winglength),width = 0.2)




ggplot(data = all_means_sd, 
       aes(x = drought_survival, 
           y = avg_tarsus)) + 
  geom_col(fill = "purple") +
  ylab("Mean Tarsus Length (mm)") +
  xlab("Drought Survival") + theme_classic() + geom_errorbar(aes(
    ymin = avg_tarsus - sd_tarsus, 
  ymax = avg_tarsus + sd_tarsus),width = 0.2)

ggplot(data = all_means_sd, 
       aes(x = drought_survival, 
           y = avg_mass)) + 
  geom_col(fill = "red") +
  ylab("Mean Mass (g)") +
  xlab("Drought Survival") + theme_classic() +  
  geom_errorbar(aes(ymin = avg_mass - sd_mass, ymax = avg_mass + sd_mass),
  width = 0.2) 



#t test bar plot

t.test(dat$body_mass_g ~ dat$drought_survival)
t.test(dat$wing_length_mm ~ dat$drought_survival)
t.test(dat$tarsus_length_mm ~ dat$drought_survival)
t.test(dat$beak_depth_mm ~ dat$drought_survival)




ggplot(data = dat, aes(x = beak_depth_mm, y = wing_length_mm)) + geom_point(size = 3) + xlab("Beak Depth (mm)") + ylab("Wing Length (mm)")

reg <- lm(dat$beak_depth_mm ~ dat$wing_length_mm)

summary(reg)
