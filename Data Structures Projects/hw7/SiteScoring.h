



//Keyword Density Score = (Number of Times Keyword Appears in this One Document) / (Total Content Length of this One Document * Keyword Density Across All Documents)



double returnKeyDens();



//backlinks score = ( 1.0 / (1 + doc_1->outgoingLinks) + 1.0 / (1 + doc_2->outgoingLinks) + ... + 1.0 / (1 + doc_N->outgoingLinks) );
double returnBackScore();


//page score = (0.5 * keywords density score + 0.5 * backlinks score); [formula 1]
double returnPageScore();


// /backlinks score = ( 1.0 / (1 + doc_1->outgoingLinks) + 1.0 / (1 + doc_2->outgoingLinks) + ... + 1.0 / (1 + doc_N->outgoingLinks) );
double getBackScore();

