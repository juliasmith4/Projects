# this is code for you
library(ggplot2)
library(dplyr)
# check working directory!
# read in your data set as a csv
# this is an example data set you need to create your own spread sheet from the 
# student data sheet and load that in instead!


dat <- read.csv("student_data_sheet.csv")


head(dat)






# first figure cpg island map 
# this is tricky to figure out so here is the bare bones code go ahead and modify it make it look nice for your data
# this 'maps' the location for each sequence


# first identify data
ggplot(data = dat)+
  
  # next we want to make a segment from the start to the end with the 
  #sequence number being the y axis
  geom_segment(aes(x = start_site, y = Sequence, xend = end_site, yend = Sequence), color = "blue", linewidth=5)+
  # just make a nice theme 
  

  theme_classic()+
  # change x axis label
  xlab("Site Location")+
  ylim(0,15) 


# you should add axis labels change colors etc
# save plot and add to word document with caption and 
# bullet point take away


# Create box and whisker plot for GC content and length 
# try to figure this out on your own and refer to powerpoint
# hint use geom_boxplot()
# leave x blank and make y = to your variable of choice
# modify graphs to make them look nice
# paste into word document




ggplot(data = dat, aes( y = Sequence)) + 
   geom_boxplot( color = "pink",weight = 5, fill = "turquoise")+
  theme_classic()+
  xlab("") + ylab("Sequence")






# length box plot


ggplot(data = dat, aes( y = length)) + 
  geom_boxplot( color = "purple",weight = 5, fill = "green")+
  theme_classic()+
  xlab("") + ylab("Length")










# GC content box plot



ggplot(data = dat, aes( y = GC_content)) + 
  geom_boxplot( color = "magenta", fill = "yellow")+
  theme_classic()+
  xlab("") + ylab("GC_Content")







# calculate summary statistics for 
# gc content and length
# find the mean median min max did you learn a function to return all of this information?
# put this into a table add to word doc 
# make the table in microsoft word or excel




class(dat$length)
class(dat$start_site)
class(dat$Sequence)
class(dat$GC_content)




#preview of data  - column names 


head(dat)
str(dat)

head(dat)
#summarize numeric data easily 
summary(dat$length)

summary(dat$GC_content)
#save data as csv









