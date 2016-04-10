/****************************************************************
 * This is the cpp file for the EditDistance class.
 * It will do all the work of the EditDistance Algorithm 
 * and get called by a driver class. 
 *
 * Author/copyright: Dion de Jong
 * Date: 13 September  2014
 *
**/

#include "EditDistance.h"

EditDistance::EditDistance()
{
}

EditDistance::~EditDistance()
{
}

/****************************************************************
* Function to run the EditDistance Algorithm.
*
* After initializing the first row and column (since these values
* are padded) we run a double loop to go through the entire vector. 
* This double loop compares the values of the numbers above, to the
* left, and diagonally up and to the left. If values of the sentences
* at that point in the vector are different, we substitute for a cost of 2. 
* If there is a blank space for one of the sentences, we insert or delete for a 
* cost of 1. If the values are the same, we keep the value. The lowest
* value is then taken and put into the vector at the current spot. We
* then return the completed EditDistance matrix. 
*
* Parameters:
* No parameters.
*
* Output: displays the completed Edit Distance Matrix through
* Cout
*
* Returns: None
**/
void EditDistance::computeDistances()
{
   std::vector<int> tempVector;
   int leftVal = 0; 
   int upVal = 0; 
   int diagVal = 0; 
   int vecVal1 = 0; 
    
   //initialize the first row and column. 
   for (unsigned int i = 0; i < sentence1.size(); ++i)
   {
     dist[0][i] = i; 
   } 

   for (unsigned int i = 0; i < sentence2.size(); ++i)
   {
     dist[i][0] = i; 
   }
 
   //populate the matrix with values through comparison as described above. 
   for(unsigned int i = 1; i <sentence2.size(); ++i)
   {
     for (unsigned int j = 1; j <sentence1.size(); ++j) 
     { 
       //if the values are equal, the words are the same, therefore there is no cost. 
       if (sentence1[j].compare(sentence2[i]) == 0)
       {
         diagVal = dist[i-1][j-1]; 
       }
       //otherwise, the values in each line do not equal, and require a cost of 2 if we must substitute one word for another. 
       else 
       { 
           diagVal = dist[i-1][j-1] + COSTSUBSTITUTION;  
       }

      //create and compare final values of each comparison  
      leftVal = dist[i][j-1] + COSTINSERTION;
      upVal = dist[i-1][j] + COSTINSERTION;
      vecVal1 =  min(diagVal, min(upVal, leftVal));
      dist[i][j] = vecVal1;

      Utils::logStream << "Intermediate Matrix \n"; 
      
      Utils::logStream << toString(); 
     }  
   }
  Utils::logStream << "Leaving computeDistances()";
  cout << toString(); 
 
}

/****************************************************************
* Function to initialize the EditDistance program.
*
* This function takes in the input file's sentences
* and puts them into two separate string vectors to be
* called later in the ComputeDistances function. It also 
* adds 'padding' to the first space in the vector and any
* at the end of the shorter sentence so that they are the same
* lengths. 
*
* Parameters:
* Reference to a Scanner object created in the Main class. 
*
* Output: none except the tracing/logging information that
* could disappear in a "real" implementation
*
* Returns: none
**/
void EditDistance::initialize(Scanner& scanner)
{
  ScanLine scanLine; 
  string temp = "";
  string firstSentence = ""; 
  string secondSentence = ""; 
  std::vector<int> tempVector;

  //pad the first value in each string vector with DUMMYSTRING
  this->sentence1.push_back(DUMMYSTRING); 
  this->sentence2.push_back(DUMMYSTRING);

  //store the two lines using scanner
  while(scanner.hasNext()) 
  {
    firstSentence = scanner.nextLine(); 
    secondSentence = scanner.nextLine(); 
  } 
    
  //use scanLine to scan token by token and split the lines into string arrays
  scanLine.openString(firstSentence); 
  while(scanLine.hasMoreData())
  {  
    temp = scanLine.next(); 
    this->sentence1.push_back(temp); 
  }  
    
  scanLine.openString(secondSentence);
  while(scanLine.hasMoreData())
  {
   temp = scanLine.next(); 
   this->sentence2.push_back(temp); 
  } 

  //if there is a size difference among the two vectors, pad the shorter one to the same length. 
  if(sentence1.size() > sentence2.size())
  {   
    for (unsigned int i = sentence2.size() ; i < sentence1.size(); ++i) 
    {
      this->sentence2.push_back(DUMMYSTRING); 
    } 
  } 
  
  else if(sentence1.size() < sentence2.size()) 
  { 
    for (unsigned int j = sentence1.size(); j < sentence2.size(); j++)
    { 
      this->sentence1.push_back(DUMMYSTRING); 
    }   
  } 
  //populate the 2D vector with dummy values so that it can be manipulate in the ComputeDistances function.
  for (unsigned int k = 0; k < sentence1.size(); ++k) 
  {
    for (unsigned int l = 0; l < sentence2.size(); ++l) 
    {
      tempVector.push_back(DUMMYDISTANCE); 
    }
   
    dist.push_back(tempVector); 
    tempVector.clear();  
   }
   
} 

/****************************************************************
* Function to convert the sentences and matrix to a string so 
* that they can be output and look presentable. 
*
* This function converts and formats every neccessary part of 
* data for the output of the program. It creates the spaced 
* EditDistance matrix, as well as presenting the sentences. 
*
* Parameters:
* None. 
*
* Output: None
*
* Returns:
* A string value of all the data and the matrix which have been
* formatted properly. 
**/

string EditDistance::toString()
{
   string finalString = "";  
   int vecValue = 0;

   finalString += "First Sentence:  \n"; 
   for (unsigned int i = 0; i < sentence1.size(); ++i)
   {
     finalString += Utils::Format(sentence1[i]) + "  |  ";
   }
  
   finalString += "\n";
   finalString += "Sentence Two: ";  
   finalString += "\n";
 
   for(unsigned int j = 0; j < sentence2.size(); ++j)
   {
     finalString += Utils::Format(sentence2[j]) + "  |  "; 
   }

   finalString += "\nDistance Matrix: \n          "; 

   for (unsigned int i = 0; i < sentence1.size(); ++i)
   {
     finalString += Utils::Format(sentence1[i],9); 
   }
 
   finalString += "\n";

   for(unsigned int k = 0; k < sentence1.size(); ++k) 
   {
     finalString += Utils::Format(sentence2[k],9);
     for(unsigned int l = 0; l < sentence2.size(); ++l) 
     {
       vecValue = dist[k][l];
       finalString += Utils::Format(vecValue,9); 
     }
   finalString += "\n";   
   } 

   return finalString;
}
