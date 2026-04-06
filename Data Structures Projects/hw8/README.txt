HOMEWORK 8: Youtube Comments


NAME:  Julia Smith 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

I did not talk to anyone else about this assignment, however I did use online resources such as Geeks for Geeks, W3 Schools, BroCode and Code Beauty on Youtube, and other various youtube videos in order to further my understanding of C++ content, specifically trees. 





Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  8


MISC. COMMENTS TO GRADER:
(optional, please be concise!)


## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?


I first started with drawing an outline and sketching my thinking process on paper. I found the concept of understanding the trees, planning out my classes, and constructing the main file to come quickly to me. 

I first had problems with connecting the classes together, that took a bit for me to do. I also searched through W3 schools and Geeks 4 Geeks in order to better understand trees and tree nodes in order to do this. Eventually it all came together and wasn't that difficult. Once my structures were set I ran into things such as updating reply and like count because this is what I forgot to do initially until I submitted it to submitty. After reviewing my code, I found that I was basing the reply count based on those in the children vector and the ones actually displayed, but as the FAQ said it is based off of the reply count and some aren't displayed. Thus, I created more vars and functions to do this. I also made a make new reply comment so that every time I updated the reply count it wasn't the ones already counted from the json file. I think the development and testing process for this homework went well for me and I found myself having success when running into issues and resolving them. I also had to add a destructor at the end after seeing memory leakage. 