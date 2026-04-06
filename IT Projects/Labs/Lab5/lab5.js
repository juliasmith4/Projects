// check form after user submits 
function validateForm() {

    //each element of the thing
    var firstName = document.getElementById("firstName").value.trim();
    var lastName = document.getElementById("lastName").value.trim();
        var organization = document.getElementById("org").value.trim(); // changed to match HTML
    var title = document.getElementById("title").value.trim();

    var nickname = document.getElementById("pseudonym").value.trim(); // changed to match HTML
    var comments = document.getElementById("comments").value.trim();

    //arr for the warnings and add to it if there are any 
    const warning = [];

    // checkng if any field is empty
    if (firstName === "" ) {
        warning.push( "Please enter first name\n");
    }

    if (lastName === "" ) {
        warning.push( "Please enter last name\n");
    }
 if (title === "" ) {
        warning.push( "Please enter title\n");
    }
     if (organization === "" ) {
        warning.push( "Please enter organization\n");
    }
    if (nickname === "" ) {
        warning.push( "Please enter nickname\n");
    }

    if (comments === "" || comments === "Please enter your comments" ) {
        warning.push( "Please enter comments\n");
    }

    //if it has elements then print 
    if (warning.length > 0) {
        alert(warning.join("")); 
        // show all warnings
        return false; 
        // prevent form submission
    }

    // if everything is filled out it can be successful
    alert("Form submitted successfully!");
    //return to end
    return true;
}

// clear default text when user clicks text area
function clearComments() {
    var commentsBox = document.getElementById("comments");

    if (commentsBox.value === "Please enter your comments") {
        commentsBox.value = "";
    }
}

// put the default text back if nothing was entered
function restoreComments() {

    //comments 
    var commentsBox = document.getElementById("comments");

    if (commentsBox.value.trim() === "") {
        commentsBox.value = "Please enter your comments";
    }
}

// nickname show
function showNickname() {

    
  var firstName = document.getElementById("firstName").value.trim();
  var lastName = document.getElementById("lastName").value.trim();
  var nickname = document.getElementById("pseudonym").value.trim();

  //  not empty
  if (!firstName || !lastName || !nickname) {
    alert("Please fill in First Name, Last Name, and Nickname first.");
    return;
  }

  // show nickname alert
  alert(firstName + " " + lastName + " is " + nickname);

} 