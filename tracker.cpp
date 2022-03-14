// Zach Duncan

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
  // STL Map class will store characters, words, and numbers from standard input
  unordered_map<char,pair<int, bool>> charMap;
  unordered_map<string, pair<pair<int, int>, bool>> wordMap;
  unordered_map<string, pair<pair<int, int>, bool>> numMap;

  //To help understand the map:
  //<string, pair<                    >  // string for word or num, pair
  //              pair<        >, bool   // pair, bool for whether it has been counted in top 10 or not
  //                   int, int          // num of word/num usages, num order that word was placed in the map

  bool isWord = false; // boolean flags
  bool isNumber = false;
  string thisWord = ""; // empty strings used when encountering a word or number
  string thisNumber = "";
  int wordCount = 0; // count of UNIQUE words (not repeated)
  int numCount = 0; // count of UNIQUE nums (not repeated)
  int charCount = 0; // count of UNIQUE chars (not repeated)

  char c;                 // CURRENT CHARACTER c
  while (cin.get(c))      // read in character by character until EOF
  {
    // Insert current character into map----------------------------------------
    if(charMap.find(c) == charMap.end())
    {
      charMap.insert(pair<char, pair<int, bool>>(c, make_pair(1, false)));
      charCount++;
      //cout << c;
    }
    else {
      charMap[c].first++; //----------------------------------------------------
      //cout << c;
    }

    c = tolower(c);                   // convert to lowercase

    // Check if character is a number or a letter
    if (static_cast<int>(c) > 47 &&  static_cast<int>(c) < 58) // number
    {
      isWord = false; // Set flags accordingly
      isNumber = true;
      string temp(1, c);
      thisNumber.append(temp); // append to thisNumber string
    }
    else if (static_cast<int>(c) > 96 &&  static_cast<int>(c) < 123) // letter
    {
      isWord = true;
      isNumber = false; // set flags accordingly
      string temp(1, c);
      thisWord.append(temp); // append to thisWord string
    }
    else // neither
    {
      isWord = false; // set flags accordingly
      isNumber = false;
    }

    // Check boolean flags if we need to add a word or number to map
    if ((isNumber == false) && (thisNumber != "")) // Would be true if last iteration had a number
    {                                              // which would append to thisNumber string
      if(numMap.find(thisNumber) == numMap.end()) // if number not yet in map
      {
        numMap.insert(pair<string, pair<pair<int, int>, bool>>(thisNumber, make_pair(make_pair(1, numCount), false)));
        numCount++;
      }
      else // number already found in map, increment frequency of occurence for that number
        numMap[thisNumber].first.first++;

      thisNumber = ""; // reset to empty string
    }

    if ((isWord == false) && (thisWord != "")) // works in same manner as checking isNumber
    {
      if(wordMap.find(thisWord) == wordMap.end())
      {
        wordMap.insert(pair<string, pair<pair<int, int>, bool>>(thisWord, make_pair(make_pair(1, wordCount), false)));
        wordCount++;
      }
      else
        wordMap[thisWord].first.first++;

      thisWord = ""; // reset to empty string
    }


  } // End of while loop (reading from cin)-------------------------------------

  // If a remaining word or number to add to maps
  if (isWord == true) // SAME CHECK AS THE ONE IN WHILE LOOP
  {
    if(wordMap.find(thisWord) == wordMap.end())
    {
      wordCount++;
      wordMap.insert(pair<string, pair<pair<int, int>, bool>>(thisWord, make_pair(make_pair(1, wordCount), false)));
    }
    else
      wordMap[thisWord].first.first++;
  }
  if (isNumber == true) // SAME CHECK AS THE ONE IN WHILE LOOP
  {
    if(numMap.find(thisNumber) == numMap.end())
    {
      numCount++;
      numMap.insert(pair<string, pair<pair<int, int>, bool>>(thisNumber, make_pair(make_pair(1, numCount), false)));
    }
    else
      numMap[thisNumber].first.first++;
  }

  //PRINT CHAR------------------------------------------------------------------
  //for(auto itr = charMap.begin(); itr != charMap.end(); itr++)
  //{
  //  cout << itr -> first << ": " << itr->second.first << "\n";
  //}
  // cout << "\n";

  int n = static_cast<int>(charMap.size()); // size of map
  if (n > 10) // only printing top ten chars, so if size is larger than that, adjust
    n = 10;
  cout << "Total " << charCount << " different characters, " << n << " most used characters:\n";

  for (int i = 0; i < n; i++) // 10 or less iterations
  {
    int max = 0; // maxmimum frequency found within map (how many times a char appeared)
    char maxChar = '~'; // '~" is ASCII value of 126, will undoubtedly be replaced by character of a smaller ASCII value
                        // maxChar is the char that hold the maximum frequency
    for(auto itr = charMap.begin(); itr != charMap.end(); itr++) // iterate through charMap
    {
      if (itr->second.second == true) // if char is set to true, exlude it from consideration
        continue;
      if (itr->second.first > max || (itr->second.first == max && (static_cast<int>(itr->first) < static_cast<int>(maxChar))))
      {
        max = itr->second.first; // update max and maxChar
        maxChar = itr->first;
      }
    }
    charMap[maxChar].second = true; // set the maxChar to true so it doesn't show up again

    cout << "No. " << i << ": ";
    if(maxChar == '\n') // will not print out '\n' or '\t' without these conditions
			cout << "\\n" << "\t\t" << max;
		else if(maxChar == '\t')
			cout << "\\t" << "\t\t" << max;
		else // printing for any other character
			cout << maxChar << "\t\t" << max;
    cout << "\n";
  }

  cout << "\n";

  //PRINT WORD------------------------------------------------------------------
  //for(auto itr = wordMap.begin(); itr != wordMap.end(); ++itr)
  //{
  //  cout << itr -> first << ": " << itr->second.first.first << "\n";
  //}
  // cout << "\n";

  int n2 = static_cast<int>(wordMap.size()); //refer to comments in PRINT CHAR
  if (n2 > 10)
    n2 = 10;
  cout << "Total " << wordCount << " different words, " << n2 << " most used words:\n";

  for (int i = 0; i < n2; i++)
  {
    int max = 0;
    string maxWord = "";

    for(auto itr = wordMap.begin(); itr != wordMap.end(); itr++)
    {
      if (itr->second.second == true)
        continue;
      if (itr->second.first.first > max || maxWord.empty() ||
         (itr->second.first.first == max && (itr->second.first.second < wordMap[maxWord].first.second)))
      {  // different conditions than Print Char section - also checking which num was encoundtered first
          max = itr->second.first.first;
          maxWord = itr->first;
      }
    }
    wordMap[maxWord].second = true;

    cout << "No. " << i << ": ";
    cout << maxWord << "\t\t" << max;
    cout << "\n";
  }

  cout << "\n";

  //PRINT NUM------------------------------------------------------------------
  //for(auto itr = numMap.begin(); itr != numMap.end(); ++itr)
  //{
  //  cout << itr -> first << ": " << itr->second.first.first << "\n";
  //}

  int n3 = static_cast<int>(numMap.size()); // refer to comments in PRINT CHAR
  if (n3 > 10)
    n3 = 10;
  cout << "Total " << numCount << " different numbers, " << n3 << " most used numbers:\n";

  for (int i = 0; i < n3; i++)
  {
    int max = 0;
    string maxNum = "";

    for(auto itr = numMap.begin(); itr != numMap.end(); itr++)
    {
      if (itr->second.second == true)
        continue;
      if (itr->second.first.first > max || maxNum.empty() ||
         (itr->second.first.first == max && (itr->second.first.second < numMap[maxNum].first.second)))
      {  // different conditions than Print Char section - also checking which num was encoundtered first
          max = itr->second.first.first;
          maxNum = itr->first;
      }
    }
    numMap[maxNum].second = true;

    cout << "No. " << i << ": ";
    cout << maxNum << "\t\t" << max;
    cout << "\n";
  }

  return 0;
}
