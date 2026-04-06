# only install first time 
install.packages("survival")
install.packages("survminer")
library(survival)
library(survminer)


# now we will analyze a mystery cancer together

# load in data check directory
myst_df <- read.csv("mystery_cancer.csv")
# create an "overall survival" variable that is equal to days_to_death
# for dead patients, and to days_to_last_follow_up for patients who
# are still alive
# this creates a number higher value means higher chance fo surviving
# see powerpoint for details
myst_df$overall_survival <- ifelse(myst_df$deceased,
                                   myst_df$days_to_death,
                                   myst_df$days_to_last_followup)  
head(myst_df)  
library(survival)  
# create survivorship model
# add fit based on another category in this case gender

fit <- survfit(Surv(overall_survival, deceased) ~ gender, data=myst_df)


library(survminer)
ggsurvplot(fit, data=myst_df, pval=T, title= "MYSTERY")
# if p is > than 0.05 no difference in suitability between gender 
# interested in how plot is made?
?Surv
?survfit

# count up # in each group
library(tidyverse)
table(myst_df$gender)

# build models with other features including stage ethnicity age groups?  
unique(myst_df$ethnicity)
table(myst_df$ethnicity) # get sample size this could be important! 
# do we have a large enough sample from each subgroup?
fit = survfit(Surv(overall_survival, deceased) ~ ethnicity, data=myst_df)
ggsurvplot(fit, data=myst_df, pval=T,title= "MYSTERY")
# create a box plot if you want to investigate things further 
ggplot(data = myst_df, aes(x=ethnicity, overall_survival))+
  geom_boxplot()+
  geom_jitter(width = 0.25, height = 0, colour = "blue", shape = 21)+
  ggtitle("MYSTERY")
# clean plot up
# warning issues?
summary(myst_df$overall_survival)
# 548 NAs...
# your goals for today:

# Investigate three real data sets from TCGA:
# TCGA-LUSC , TCGA-KIRC, TCGA-LGG

ggsave("test.jpeg")



# QUESTIONS STARTING NOW

# build models with other features including stage ethnicity age groups?  
lusc <- read.csv("clin_TCGA_LUSC.csv")
lusc$overall_survival <- ifelse(lusc$deceased,
                                lusc$days_to_death,
                                lusc$days_to_last_followup)  
unique(lusc$gender)
table(lusc$gender) # get sample size this could be important! 
# do we have a large enough sample from each subgroup?
fit = survfit(Surv(overall_survival, deceased) ~ gender, data=lusc)
ggsurvplot(fit, data=lusc, pval=T,title= "TCGA-LUSC")

# clean plot up
# warning issues?
summary(lusc$overall_survival)


fit = survfit(Surv(overall_survival, deceased) ~ gender, data = lusc)
      ggsurvplot(fit, data = lusc, pval=T, title = "TCGA-LUSC")


kirc <- read.csv("clin_TCGA_KIRC.csv")
kirc$overall_survival <- ifelse(kirc$deceased,
                                kirc$days_to_death,
                                kirc$days_to_last_followup)  
unique(kirc$gender)
table(kirc$gender) # get sample size this could be important! 
# do we have a large enough sample from each subgroup?
fit = survfit(Surv(overall_survival, deceased) ~ gender, data=kirc)
ggsurvplot(fit, data=kirc, pval=T,title= "TCGA-KIRC")

# clean plot up
# warning issues?
summary(kirc$overall_survival)


fit = survfit(Surv(overall_survival, deceased) ~ gender, data = kirc)
      ggsurvplot(fit, data = kirc, pval=T, title = "TCGA-KIRC")
      
      
      
      
#LGG
      
      
      
      lgg <- read.csv("clin_TCGA_LGG.csv")
      lgg$overall_survival <- ifelse(lgg$deceased,
                                     lgg$days_to_death,
                                     lgg$days_to_last_followup)  
      unique(lgg$gender)
      table(lgg$gender) # get sample size this could be important! 
      # do we have a large enough sample from each subgroup?
      fit = survfit(Surv(overall_survival, deceased) ~ gender, data=lgg)
      ggsurvplot(fit, data=lgg, pval=T,title= "TCGA-LGG")
      
      # clean plot up
      # warning issues?
      summary(lgg$overall_survival)
      
      
      fit = survfit(Surv(overall_survival, deceased) ~ gender, data = lgg)
      ggsurvplot(fit, data = lgg, pval=T, title = "TCGA-LGG")
      
      # QUESTIONS STARTING NOW

# build models with other features including stage ethnicity age groups?  
lusc <- read.csv("clin_TCGA_LUSC.csv")
lusc$overall_survival <- ifelse(lusc$deceased,
                                lusc$days_to_death,
                                lusc$days_to_last_followup)  
unique(lusc$gender)
table(lusc$gender) # get sample size this could be important! 
# do we have a large enough sample from each subgroup?
fit = survfit(Surv(overall_survival, deceased) ~ gender, data=lusc)
ggsurvplot(fit, data=lusc, pval=T,title= "TCGA-LUSC")

# clean plot up
# warning issues?
summary(lusc$overall_survival)


fit = survfit(Surv(overall_survival, deceased) ~ gender, data = lusc)
      ggsurvplot(fit, data = lusc, pval=T, title = "TCGA-LUSC")


kirc <- read.csv("clin_TCGA_KIRC.csv")
kirc$overall_survival <- ifelse(kirc$deceased,
                                kirc$days_to_death,
                                kirc$days_to_last_followup)  
unique(kirc$gender)
table(kirc$gender) # get sample size this could be important! 
# do we have a large enough sample from each subgroup?
fit = survfit(Surv(overall_survival, deceased) ~ gender, data=kirc)
ggsurvplot(fit, data=kirc, pval=T,title= "TCGA-KIRC")

# clean plot up
# warning issues?
summary(kirc$overall_survival)


fit = survfit(Surv(overall_survival, deceased) ~ gender, data = kirc)
      ggsurvplot(fit, data = kirc, pval=T, title = "TCGA-KIRC")
      
      
      
      
#LGG
      
      
      
      lgg <- read.csv("clin_TCGA_LGG.csv")
      lgg$overall_survival <- ifelse(lgg$deceased,
                                     lgg$days_to_death,
                                     lgg$days_to_last_followup)  
      unique(lgg$gender)
      table(lgg$gender) # get sample size this could be important! 
      # do we have a large enough sample from each subgroup?
      fit = survfit(Surv(overall_survival, deceased) ~ gender, data=lgg)
      ggsurvplot(fit, data=lgg, pval=T,title= "TCGA-LGG")
      
      # clean plot up
      # warning issues?
      summary(lgg$overall_survival)
      
      
      fit = survfit(Surv(overall_survival, deceased) ~ gender, data = lgg)
      ggsurvplot(fit, data = lgg, pval=T, title = "TCGA-LGG")
     
      
       
      # ETHNICITY 
      
      # build models with other features including stage ethnicity age groups?  
      lusc <- read.csv("clin_TCGA_LUSC.csv")
      lusc$overall_survival <- ifelse(lusc$deceased,
                                      lusc$days_to_death,
                                      lusc$days_to_last_followup)  
      unique(lusc$ethnicity)
      table(lusc$ethnicity) # get sample size this could be important! 
      # do we have a large enough sample from each subgroup?
      fit = survfit(Surv(overall_survival, deceased) ~ ethnicity, data=lusc)
      ggsurvplot(fit, data=lusc, pval=T,title= "TCGA-LUSC")
      
      # clean plot up
      # warning issues?
      summary(lusc$overall_survival)
      
      
      fit = survfit(Surv(overall_survival, deceased) ~ ethnicity, data = lusc)
      ggsurvplot(fit, data = lusc, pval=T, title = "TCGA-LUSC")
      
      
      kirc <- read.csv("clin_TCGA_KIRC.csv")
      kirc$overall_survival <- ifelse(kirc$deceased,
                                      kirc$days_to_death,
                                      kirc$days_to_last_followup)  
      unique(kirc$ethnicity)
      table(kirc$ethnicity) # get sample size this could be important! 
      # do we have a large enough sample from each subgroup?
      fit = survfit(Surv(overall_survival, deceased) ~ ethnicity, data=kirc)
      ggsurvplot(fit, data=kirc, pval=T,title= "TCGA-KIRC")
      
      # clean plot up
      # warning issues?
      summary(kirc$overall_survival)
      
      
      fit = survfit(Surv(overall_survival, deceased) ~ ethnicity, data = kirc)
      ggsurvplot(fit, data = kirc, pval=T, title = "TCGA-KIRC")
      
      
      
      
      #LGG
      
      
      
      lgg <- read.csv("clin_TCGA_LGG.csv")
      lgg$overall_survival <- ifelse(lgg$deceased,
                                     lgg$days_to_death,
                                     lgg$days_to_last_followup)  
      unique(lgg$ethnicity)
      table(lgg$ethnicity) # get sample size this could be important! 
      # do we have a large enough sample from each subgroup?
      fit = survfit(Surv(overall_survival, deceased) ~ ethnicity, data=lgg)
      ggsurvplot(fit, data=lgg, pval=T,title= "TCGA-LGG")
      
      # clean plot up
      # warning issues?
      summary(lgg$overall_survival)
      
      
      fit = survfit(Surv(overall_survival, deceased) ~ ethnicity, data = lgg)
      ggsurvplot(fit, data = lgg, pval=T, title = "TCGA-LGG")
      
      
    
      # PART 3 STARTING NOW
      
      # build box plots with ethnicity and stage
      
      
      # LUSC ETHNICITY
      
      lusc <- read.csv("clin_TCGA_LUSC.csv")
      lusc$overall_survival <- ifelse(lusc$deceased,
                                      lusc$days_to_death,
                                      lusc$days_to_last_followup)
      unique(lusc$ethnicity)
      table(lusc$ethnicity) # get sample size this could be important!
      
      # create a box plot
      ggplot(data = lusc, aes(x=ethnicity, y=overall_survival))+
        geom_boxplot()+
        geom_jitter(width = 0.25, height = 0, colour = "blue", shape = 21)+
        ggtitle("TCGA-LUSC")+
        labs(x = "Ethnicity", y = "Overall Survival (days)")
      
      # clean plot up
      summary(lusc$overall_survival)
      
      
      
      # KIRC ETHNICITY
      
      kirc <- read.csv("clin_TCGA_KIRC.csv")
      kirc$overall_survival <- ifelse(kirc$deceased,
                                      kirc$days_to_death,
                                      kirc$days_to_last_followup)
      unique(kirc$ethnicity)
      table(kirc$ethnicity) # get sample size this could be important!
      
      # create a box plot
      ggplot(data = kirc, aes(x=ethnicity, y=overall_survival))+
        geom_boxplot()+
        geom_jitter(width = 0.25, height = 0, colour = "blue", shape = 21)+
        ggtitle("TCGA-KIRC")+
        labs(x = "Ethnicity", y = "Overall Survival (days)")
      
      # clean plot up
      summary(kirc$overall_survival)
      
      
      
      # KIRC STAGE
      
      kirc <- read.csv("clin_TCGA_KIRC.csv")
      kirc$overall_survival <- ifelse(kirc$deceased,
                                      kirc$days_to_death,
                                      kirc$days_to_last_followup)
      unique(kirc$stage_event_pathologic_stage)
      table(kirc$stage_event_pathologic_stage) # get sample size this could be important!
      
      # create a box plot
      ggplot(data = kirc, aes(x=stage_event_pathologic_stage, y=overall_survival))+
        geom_boxplot()+
        geom_jitter(width = 0.25, height = 0, colour = "blue", shape = 21)+
        ggtitle("TCGA-KIRC")+
        labs(x = "Cancer Stage", y = "Overall Survival (days)")
      
      # clean plot up
      summary(kirc$overall_survival)
      
      
      