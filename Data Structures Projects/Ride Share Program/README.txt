HOMEWORK 2: Ride Sharing


NAME:  Julia Smith 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

I did not talk to any other students about this assignment. 
Resources Used:
Lecture Notes, https://www.geeksforgeeks.org/, https://www.w3schools.com/, Bro Code YouTube channel, https://www.youtube.com/watch?v=0wOM4lmDAWc, 

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10


MISC. COMMENTS TO GRADER:
(optional, please be concise!)


## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

During development, my main issues I encountered were with the writing to the outputs, managing the null arguments in the constructors when the rider wouldnt have a driver and vice versa. Thus, it took some time and rearranging of my code in order to make everything fit. I used to call request inside of cancel which was a major bug for a long time since it messed with the files, so I had to rearrange my code and write functions in order to make everything work. I had to research a lot about looping through vectors of objects and handling files inside my program. I referred to my resources for these. As I mentioned earlier, I faced errors with the null arguments, the intended outputs being incorrect due to file handling, and making sure every scenario was handled properly. Thus, these were the challenges I faced in this assignment and what was most difficult for me, just when I would think my code is completed,I forgot to write something for one of the scenarios listed or it was mishandled, or the file wasn't written in properly. What finally clicked for me was writing a function for the writing to the files when handling the cancels and the requests because originally I had them inside of the functions but it was smarter to not have that because of managing the outputs. Another clicked moment was handling the null arguments and figuring out if the drivers had a rider and if the rider had a driver without causing an error with comparing to null. Overall, I think the development process for me went well and even though it took time and a lot of reconstruction I think my original layout isn't that different from my end layout and I learned a lot from the testing process.