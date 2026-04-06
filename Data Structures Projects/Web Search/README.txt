HOMEWORK 7: Search Engine


NAME:  Julia Smith 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.


I did not talk to anyone else about this assignment, however I did use online resources such as Geeks for Geeks, W3 Schools, BroCode and Code Beauty on Youtube, and other various youtube videos in order to further my understanding of C++ content. 



Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  11


MISC. COMMENTS TO GRADER:
(optional, please be concise!)


## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?



In the process of testing, I learned that my code wont construct a snippet correctly with search like "Kendall Jenner Devin". I think it is because it won't pick up "Kendall Jenner and Devin" because of the and. I am still in the process of debugging it but this is something in the testing process I have to figure out. Multiple words within a search that are not going to be directly followed by each other. I also have to rework my page scoring to fit the FAQ section of the GitHub. I found it most challenging to debug the page scoring section of my code. I don't know necessarily where the bug error is, whether it is because of the backlinks and incoming links or if it is because of the scoring itself, but I used gdb and printing to cout to try to figure out where the issue is. I didn't end up finding out but I tried things such as analyzing the out1 testcase and whether I had to use the body content, the full content, including and not including the html, etc. I tried all different combinations and tried to analyze test cases in order to complete the testing process. Thus, I think a big part of this assignment for me was testing and development. I  went through different versions of classes and structure in order to better help me understand, and I tried different methods to debug. ** After going through my code and using methods such as printing the content and looking through each of my helper functions I found that my issue lied in the directories and splitting of words. When I was splitting the words it would sometimes combine words because of getting rid of the non alnum chars, thus when i fixed this in the code and also fixed the directories (because it would incorrectly impact the score because some paths weren't being recognized) then the scoring changed and i was able to match the expected output. This assignment for me handled a lot with going over my code and noticing the impacts of the helper functions in the overall program because when I was focusing on crawl and the score building itself, the real issue was with one of the first functions i wrote. 



 