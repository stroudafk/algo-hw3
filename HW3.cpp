#include <stack>
#include <queue>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <queue>
#include <utility>
#include <iostream>

typedef std::pair<double, std::pair<int, int>> mp; //min pair

/*
 * Add your key ideas to this comment.
 * How did you approach the problem?
 * Why does your code work?
 *
 We know that if the recipe is larger than the bucket, no houses can be made.
 We also know that is recipe is length zero to throw and invalid argument exception.

 After dealing with those cases, we can step through all the elements in the recipe's hash map and see if the bucket has enough letters to fulfill the recipe's requirements. I do this by comparing the result of the bucket's quantity of the given element for the loop divided by the recipe's quantity. Being integers, the result will truncate any extra decimal points, so if the bucket quantity is smaller than the recipe's, it will be 0.

 I can only make as many houses as my most lacking resource (or character), so per iteration I only need to change if this next element's configuration will yield less than any of the previous ones. If it yields more, I don't really care anyway because it's bottlenecked.
 */
int countLegoHouses(std::string recipe, std::string bucket) {
  if(recipe.length() == 0){
    throw std::invalid_argument("Recipe cannot be of length 0.");
  }
  if(recipe.length() > bucket.length()){
    return 0;
  }

  std::unordered_map<int,int> rMap;
  std::unordered_map<int,int> bMap;

  for(int i=0; i<recipe.length(); i++){
    rMap[recipe[i]]++;
  }
  for(int i=0; i<bucket.length(); i++){
    bMap[bucket[i]]++;
  }
  std::unordered_map<int,int>::iterator it = rMap.begin();
  int houses = INT_MAX;
  while(it != rMap.end()){
    houses = (bMap[it->first]/it->second < houses) ? bMap[it->first]/it->second : houses;
    it++;
  }

  return houses;
}

/*
 * Add your key ideas to this comment.
 * How did you approach the problem?
 * Why does your code work?
 *
Since the definition of an anagram is for two words to consist of the same letters arranged in a different order, you can tell if two words are anagrams by checking if they are equal strings when sorted. 

I used a hash map to find the most frequent string in a set of sorted strings, and the most frequent string was the largest group of anagrams.

 */
std::vector<std::string> findLargestAnagroup(const std::vector<std::string>& words) {
  std::vector<std::string> sorted(words.size());
  std::unordered_map<std::string, int> wordMap;

  for(int i=0; i<words.size(); i++){
    sorted[i] = words[i];
    std::sort (sorted[i].begin(), sorted[i].end());
    wordMap[sorted[i]]++;
    //should I search for/update the max here instead?
  }
  std::pair<std::string, int> max = {"", 0};
  std::unordered_map<std::string, int>::iterator it = wordMap.begin();

  while(it != wordMap.end()){
    if(it->second > max.second){
      max.first = it->first;
      max.second = it->second;
    }
    it++;
  }
  std::vector<std::string> anagroup;
  for(int i=0; i<sorted.size(); i++){
    if(sorted[i] == max.first){
      anagroup.push_back(words[i]);
    }
  }
  //what do we do when there is only one? is a group considered more than 1?
  return anagroup;
}

/*
 * Add your key ideas to this comment.
 * How did you approach the problem?
 * Why does your code work?
 *
 This one actually gave me a lot of trouble. Next time I would have started by recording all the information I knew I would need. The first few times, I tried combinations of iterators, but quickly discarded the idea, as I didn't know the extent to which an iterator would know what container it's in. Next, I tried variations of vectors or hash maps to record which value and where the most recently 'removed' element was to keep from going out of bounds. I finally settled on a priority queue of pairs so that I could store all that information *together* (which was my first fault).

 Another thing I had trouble with was that I didn't stop to consider the part of a pair in a priority heap that would actually be considered when balancing, and I initally had my coordinates and the values swapped. Conveniently, (or by design), this meant the first basic test case threw the negative value (which is the smallest) into the second to last position, rather than the very first. I assumed for a moment that it might be an issue with priority queues and negative doubles (I've encountered a similar issue before with greater int just for one specific circumstance), but when I narrowed it down to just the first insertion of the m first elements, my priority heap wasn't acting as expected then either.

 Lastly, I thought my cases in the while would compensate for the empty list, but I forgot to consider my adding to the heap the first time around. 

 */
std::vector<double> mergeSortedLists(const std::vector<std::vector<double>>& sortedVecs) {
  std::vector<double> minVals;

  std::priority_queue <mp, std::vector<mp>, std::greater<mp>> minq;
  
  for(int i=0; i<sortedVecs.size(); i++){
    if(sortedVecs[i].size() > 0){
      minq.push({sortedVecs[i][0], {i, 0}});
    }
  }
  
  while(!minq.empty()){
    
    minVals.push_back(minq.top().first);
    
    int rows = minq.top().second.first, cols = minq.top().second.second;
    minq.pop();
    
    if( cols+1 < sortedVecs[rows].size()){
      minq.push({sortedVecs[rows][cols+1], {rows, cols+1}});
    }
  }
  
  return minVals;
}