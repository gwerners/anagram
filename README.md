# anagram
Anagram solver for large number of characters and large dictionaries

I was toying with anagram solvers on the web and had an idea: instead of searching for words, words combinations or character combinations, I should just subtract the number of characters a word have from my target group of words and call again the function until no character is left.

*"I am lord Voldemort" = "Tom Marvolo Riddle"*

I made this software as I could'nt use the online anagram solvers because my complete name is larger (25 letters) than the online solvers could handle.


The main.cpp have two different implementations of my idea: one in plain c++ and the other using c++ and SIMD AVX-256 (faster). The compilation uses two different projects, so you could comment the SIMD version if your computer don't have avx2.

I hope you find it amusing as I did :-D

Gabriel Wernersbach Farinas


# usage

run:

  **anagram dictionary stringWithoutSpacesToSearchForAnagramsInLowerCase**

Only letters from a to z are allowed!

The dictionary must be a text file with a sorted list of words to use in the search. Every char must be lowercase! One word on each line. The size of the string to search for anagrams is not limited, but longer strings will cost more time to solve or may have no solution for the given dictionary.

note: the provided dictionaries are just for example and are not a full list of possible words. Words must not contain orthographic signals, just only letters without accentuation.
_______________________________________________________________________________
Some benchmarks:

running simd version.

**anagram_SIMD ./dict/pt-Br_dictionary.txt gabrielfarinas**

real	0m0,004s

user	0m0,008s

sys	0m0,002s

total anagrams generated: **904** ./build/gabrielfarinas_simd.txt
_______________________________________________________________________________

**anagram_SIMD ./dict/pt-Br_dictionary.txt gabrielwernersbachfarinas**

real	0m1,476s

user	0m9,020s

sys	0m0,316s

total anagrams generated: **64984** ./build/gabrielwernersbachfarinas.txt
_______________________________________________________________________________

running cpp version.

**anagram ./dict/pt-Br_dictionary.txt gabrielfarinas**

real	0m0,006s

user	0m0,023s

sys	0m0,000s

total anagrams generated: **904** ./build/gabrielfarinas.txt
_______________________________________________________________________________

**anagram ./dict/pt-Br_dictionary.txt gabrielwernersbachfarinas**

real	0m6,479s

user	0m41,376s

sys	0m1,308s

total anagrams generated: **64984** ./build/gabrielwernersbachfarinas.txt
_______________________________________________________________________________


And of course, the famous anagram in Harry Potter (dictionary contains only the wanted words...):

running cpp version.

**anagram minimal.txt tommarvoloriddle**

real	0m0,002s

user	0m0,000s

sys	0m0,004s

famous anagram(words are sorted):

**am i lord voldemort**


I also did a benchmark using the dictionary us_dictionary.txt with 142.810 words:
(this dictionary was generated using words from a free online dictionary and running the script makeUsDict.bash to fix the letters and remove invalid words)


**anagram_SIMD us_dictionary.txt gabrielfarinas**

real	0m3,202s

user	0m22,314s

sys	0m0,694s

total anagrams generated: **2675981** ./build/big.txt
_______________________________________________________________________________

