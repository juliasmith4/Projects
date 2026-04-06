# Lab 6 - JavaScript and jQuery

## In this lab, we are going to work with jQuery and continue work on our personal websites

### Lab guidance (setup)

\---

1. Download and extract the zip file from LMS into a folder on your local machines
a. *outside* of your repository into a temporary folder.
2. Checkout a development branch on your class website's production repository
a. name it anything you want, e.g. lab06
3. Copy the lab 6 files from your temporary folder to the appropriate place in your development branch

\---

### Lab specifics (jQuery)

1. There are 5 files included in the assignment repository

> lab6.css,  
lab6.html,  
lab6.js,  
a minimized jQuery file, and this  
readme.md file

2. Follow the instructions in the JavaScript file for this lab
3. When you have finished completing the instructions for lab 6 that are in the lab6.js file, and your lab6.html works as expected...







&#x20;Problem 5 (10 pts) - what happens when you click on the new li?  Why? (Explain in your readme file)

&#x20;  //   ie if it works as after #3 above, why? if it doesn't, why not?  How would you fix it?

&#x20;  //   If it doesm't work - fix it.

&#x20;  //   (Note that you need to look up the appropriate jQuery method - discussed in class - to do this)





The click on the new li doesn't work as of right now because I appended a list item on click and when the page doesn't reload, it doesnt work. After going to W3 schools and the presentation from Monday's lecture, I  decided that I need to 

&#x20;  make it so it is .on click not just click 

&#x20;   $("li").click(function () 

&#x20; {

&#x20;   $(this).toggleClass("red");

});

this is the old version. The change I made made it so that instead of doing nothing when I clicked on the added list objects, it worked just like the other ones because I hadded the parent on for the click event. 









\---

### Lab 6 guidance (Completion and Submission)

1. Create a landing lage for your lab (it must match the style of your website)
a. make sure to describe the lab and what we did  
b. make sure to link to your solution
2. Update your projects page to link to your lab landing page
3. don't forget to include a readme  
a. make sure to include links to your homepage, your lab page, and your github repo
4. test your website in your development environment.

\---

1. Once tested, Stage your code, test again, and Merge it into Production.
2. Deploy to your server.
3. Test again
4. Submit your zip of your repo to LMS - make sure it includes the correct links

