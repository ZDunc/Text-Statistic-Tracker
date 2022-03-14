# Text-Statistic-Tracker
Character, Word, and Number Usage Statistics Tracker using Unordered Map (STL Implementation)

## tracker.cpp Data Structure Analysis --

### Reading the input set - O(n)
	The program loops while (cin.get(c)) and will loop for however many
	characeters are read until end of file

### Storing the chars/words/nums in chosen containers & Setting their tracking variables - O(log n)
	Inserts to maps are O(log n), which seemed to be the most efficient
	storage method. Setting their tracking variables happens during
	inserts, so as a whole should still be around O(log n)

### Looking up the final tracking variables on char/word/num frequencies - O(n)
	This is the inside for loop of the two-layed for loops to decide and
	print the top 10 chars/ints/words. Since it is iterating through
	each entry in a map, it will always iterate n times

### Deciding on Top 10 - O(n)
	You could argue that deciding on the top 10 chars/ints/words is O(n^2)   
  	because of a for loop embedded in another for loop, but I would argue
  	that since the number of iterations for the first for loop is
  	ALWAYS going to be 10 or less iterations, a set number of times, 
  	it is more effective to consider the inside for loop iterating
  	through the char/word/num map, making the complexity 10*O(n) or 
  	simply O(n). In actuality, though, it should be a bit larger than O(n).
